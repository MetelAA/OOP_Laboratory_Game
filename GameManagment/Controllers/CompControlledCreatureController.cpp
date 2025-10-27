//
// Created by Artem on 23.10.2025.
//

#include "CompControlledCreatureController.h"

void CompControlledCreatureController::computeAndDoMove(std::map<EntityType, bool>& typesToAttack, std::vector<EntityType>& priorityOfAttack) {
    std::string headerCout = (std::string("type") + (manager.getEntityType() == EntityType::EnemyEnt ? "enemy " : "ally ")) + ", id: " + std::to_string((long long)&this->manager);

    std::cout << "Ход CompControlledCreature " << headerCout;

    if (manager.isCreatureDisabled()){
        std::cout << "CompControlledCreature: " << headerCout << " disabled -> пропускает ход, тк замедлена с предыдущего хода" << std::endl;
        this->manager.freeCreature();
        return;
    }

    std::stack<Constants::XYPair> trip;

    std::vector<EntityCoordsWithNearestPositionToAttackFrom> nearestHostileEntitiesCoordinates;
    std::vector<std::vector<int>> distances(this->field.getHeight(), std::vector<int>(this->field.getWidth(), -1));
    std::queue<Constants::XYPair> queue;
    queue.push(this->manager.getEntityCoords());
    distances[manager.getEntityCoords().x][manager.getEntityCoords().y] = 0;

    while (!queue.empty()) {
        Constants::XYPair tempCoords = queue.front();
        queue.pop();

        std::vector<Constants::XYPair> nearEntitiesToAttack = this->field.hasNearEntityOfSomeTypesWithAChance(typesToAttack,
                                                                                                              tempCoords.x,
                                                                                                              tempCoords.y, this->manager.getChanceToDetectHostile());
        if (!nearEntitiesToAttack.empty()) {
            for (Constants::XYPair entityCoordinates: nearEntitiesToAttack) {
                if (distances[entityCoordinates.x][entityCoordinates.y] == -1) {
                    distances[entityCoordinates.x][entityCoordinates.y] = -2; //условный статус код чтобы туда больше некто не заглядывал и ничего не добавлял
                    nearestHostileEntitiesCoordinates.push_back({tempCoords, entityCoordinates});
                }
            }
        }

        for (Constants::dxdy dxdy: Constants::dxdys) {
            if (this->field.canMoveToOrSpawnOnNoExcept(tempCoords.x + dxdy.x, tempCoords.y + dxdy.y) &&
                distances[tempCoords.x + dxdy.x][tempCoords.y + dxdy.y] == -1) {
                distances[tempCoords.x + dxdy.x][tempCoords.y + dxdy.y] = distances[tempCoords.x][tempCoords.y] + 1;
                queue.push({tempCoords.x + dxdy.x, tempCoords.y + dxdy.y});
            }
        }
    }

    if (nearestHostileEntitiesCoordinates.empty()){
        int moveStepRange = rand() % (this->manager.getStepRange()); //если противник не нашёл взгялядом некаких целей, то он ходит на рандомную (от 0 до максимальной дальности) позицию
        std::vector<Constants::XYPair> availableCoordinates;
        for (int x = 0; x < distances.size(); ++x) { //добавляем все координаты до которых можем дойти исходя из дальности хода = moveStepRange
            for (int y = 0; y < distances[0].size(); ++y) {
                if (distances[x][y] == moveStepRange && this->field.canMoveToOrSpawnOn(x, y)){
                    availableCoordinates.push_back({x, y});
                }
            }
        }

        if (availableCoordinates.empty()){
            std::cout << "CompControlledCreature " << headerCout << " некого не нашла, ходить тоже не хочет, короче ход здесь постоит(, завершает ход!" << std::endl;
            return;
        }

        Constants::XYPair priorityCoords = availableCoordinates.at(rand() % availableCoordinates.size());
        while(priorityCoords.x != manager.getEntityCoords().x && priorityCoords.y != manager.getEntityCoords().y){
            for(Constants::dxdy dxdy : Constants::dxdys){
                if (distances[priorityCoords.x + dxdy.x][priorityCoords.y + dxdy.y] == (distances[priorityCoords.x][priorityCoords.y] - 1)){
                    trip.push(priorityCoords);
                    priorityCoords.x= priorityCoords.x + dxdy.x;
                    priorityCoords.y = priorityCoords.y + dxdy.y;
                }
            }
        }
        try {
            moveTo(trip, headerCout);
        }catch (UniversalStringException& exp){
            std::cout << "CompControlledCreature " << headerCout << " попало на замедляющую клетку, завершает ход!" << std::endl;
            return;
        }
    }else{
        EntityCoordsWithNearestPositionToAttackFrom priorityEnemy = chooseByPriority(nearestHostileEntitiesCoordinates, distances, priorityOfAttack);
        bool canAttack = this->manager.getStepRange() >= distances[priorityEnemy.attackFromCoordinates.x][priorityEnemy.attackFromCoordinates.y];
        Constants::XYPair priorityEnemyAttackFromCoords = priorityEnemy.attackFromCoordinates;

        while(priorityEnemyAttackFromCoords.x != manager.getEntityCoords().x && priorityEnemyAttackFromCoords.y != manager.getEntityCoords().y){
            for(Constants::dxdy dxdy : Constants::dxdys){
                if (distances[priorityEnemyAttackFromCoords.x + dxdy.x][priorityEnemyAttackFromCoords.y + dxdy.y] == (distances[priorityEnemyAttackFromCoords.x][priorityEnemyAttackFromCoords.y] - 1)){
                    if (this->manager.getStepRange() >= distances[priorityEnemyAttackFromCoords.x][priorityEnemyAttackFromCoords.y]){
                        trip.push(priorityEnemyAttackFromCoords);
                    }
                    priorityEnemyAttackFromCoords.x= priorityEnemyAttackFromCoords.x + dxdy.x;
                    priorityEnemyAttackFromCoords.y = priorityEnemyAttackFromCoords.y + dxdy.y;
                }
            }
        }

        try {
            moveTo(trip, headerCout);
        }catch (SlowingCellNotification& exp){
            std::cout << "CompControlledCreature " << headerCout << " попало на замедляющую клетку, завершает ход!" << std::endl;
            return;
        }

        if (canAttack) {
            manager.attack(priorityEnemy.entityCoordinates);
            std::cout  << "CompControlledCreature " << headerCout <<  " аттакует сущность в клетке по координатам " + std::to_string(priorityEnemy.entityCoordinates.x) + " " + std::to_string(priorityEnemy.entityCoordinates.y);
        }
    }
    std::cout << "CompControlledCreature " << headerCout <<  " штатно завершае ход";
}

CompControlledCreatureController::EntityCoordsWithNearestPositionToAttackFrom
CompControlledCreatureController::chooseByPriority(std::vector<EntityCoordsWithNearestPositionToAttackFrom> &enemyWithNearestPositionToAttack, std::vector<std::vector<int>>& distances, std::vector<EntityType>& priorityOfAttack) {
    std::vector<EntityCoordsWithNearestPositionToAttackFrom> nearestEnemies;
    int minRange = INT_MAX;
    for (EntityCoordsWithNearestPositionToAttackFrom position : enemyWithNearestPositionToAttack) {
        minRange = distances[position.attackFromCoordinates.x][position.attackFromCoordinates.y] ? distances[position.attackFromCoordinates.x][position.attackFromCoordinates.y] < minRange : minRange;
    }
    for (EntityCoordsWithNearestPositionToAttackFrom position : enemyWithNearestPositionToAttack) {
        if (distances[position.attackFromCoordinates.x][position.attackFromCoordinates.y] == minRange)
            nearestEnemies.push_back(position);
    }

    for (EntityType highestPriority: priorityOfAttack) {
        for (EntityCoordsWithNearestPositionToAttackFrom coords: nearestEnemies) {
            if (this->field.getFieldCells()[coords.entityCoordinates.x][coords.entityCoordinates.y].getEntityInCellType() ==
                highestPriority) {
                return coords;
            }
        }
    }
    throw UnexpectedBehaviorException("unexpected behavior: chooseByPriority");
}

void CompControlledCreatureController::moveTo(std::stack<Constants::XYPair> trip, std::string headerCout) {
    while(!trip.empty()){
        Constants::XYPair stepTo = trip.top();
        trip.pop();
        Constants::dxdy howToMove = {stepTo.x - manager.getEntityCoords().x, stepTo.y - manager.getEntityCoords().y};
        std::cout << "CompControlledCreature " << headerCout <<  " перемещается в x: " << stepTo.x << " y: " << stepTo.y << std::endl;
        manager.moveTo(howToMove);
        if (this->field.getFieldCells()[stepTo.x][stepTo.y].hasCellEvent()){
            this->field.getFieldCells()[stepTo.x][stepTo.y].impactOnCreatureByCellEvent();
            if (this->manager.isCreatureDisabled()){ //если ивент задизейблил нашу сущность, то проверяем и останавливаем дальнейшие ходы!
                throw SlowingCellNotification("compControlledCreature on slowing cell!");
            }
        }
    }
}