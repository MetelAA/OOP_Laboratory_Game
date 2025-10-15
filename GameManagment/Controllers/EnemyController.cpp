//
// Created by Artem on 08.10.2025.
//

#include <queue>
#include <stack>
#include <iostream>
#include "EnemyController.h"

void EnemyController::doMove() {
    std::cout << "Ход Enemy id: " << &this->manager << std::endl;

    if (manager.isCreatureDisabled()){
        std::cout << "Enemy: " << &this->manager << "disabled -> пропускает ход" << std::endl;
        return;
    }

    std::stack<Constants::XYPair> trip;

    std::vector<EntityWithNearestPositionToAttackFrom> nearestHostileEntityCoordinates;
    std::vector<std::vector<int>> distances(this->field.getHeight(), std::vector<int>(this->field.getWidth(), -1));
    std::queue<Constants::XYPair> queue;
    queue.push(this->manager.getEntityCoords());
    distances[manager.getEntityCoords().x][manager.getEntityCoords().y] = 0;

    while (!queue.empty()) {
        Constants::XYPair tempCoords = queue.front();
        queue.pop();

        std::vector<Constants::XYPair> nearEntitiesToAttack = this->field.hasNearEntityOfSomeTypes(this->typesToAttack,
                                                                                                   tempCoords.x,
                                                                                                   tempCoords.y);
        if (!nearEntitiesToAttack.empty()) {
            for (Constants::XYPair entityCoordinates: nearEntitiesToAttack) {
                if (distances[entityCoordinates.x][entityCoordinates.y] == -1) {
                    distances[entityCoordinates.x][entityCoordinates.y] = -2; //условный статус код чтобы туда больше некто не заглядывал и ничего не добавлял
                    nearestHostileEntityCoordinates.push_back({tempCoords, entityCoordinates});
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

    EntityWithNearestPositionToAttackFrom priorityEnemy = chooseByPriority(nearestHostileEntityCoordinates, distances);

    bool canAttack = this->manager.getStepRange() >= distances[priorityEnemy.attackFromCoordinates.x][priorityEnemy.attackFromCoordinates.y];

    Constants::XYPair pair = priorityEnemy.attackFromCoordinates;
    while(pair.x != manager.getEntityCoords().x && pair.y != manager.getEntityCoords().y){
        for(Constants::dxdy dxdy : Constants::dxdys){
            if (this->field.canMoveToOrSpawnOn(pair.x + dxdy.x, pair.y + dxdy.y) && distances[pair.x + dxdy.x][pair.y + dxdy.y] == (distances[pair.x][pair.y] - 1)){
                if (this->manager.getStepRange() >= distances[pair.x][pair.y]){
                    trip.push(pair);
                }
                pair.x= pair.x + dxdy.x;
                pair.y = pair.y + dxdy.y;
            }
        }
    }



    while(!trip.empty()){
        Constants::XYPair stepTo = trip.top();
        trip.pop();
        Constants::dxdy howToMove = {stepTo.x - manager.getEntityCoords().x, stepTo.y - manager.getEntityCoords().y};
        std::cout << "Enemy: " << &this->manager << " перемещается в x: " << stepTo.x << " y: " << stepTo.y << std::endl;
        manager.moveTo(howToMove);
        if (this->field.getFieldCells()[stepTo.x][stepTo.y].getType() == CellType::Slowing){
            manager.disableCreature();
            std::cout << "Enemy: " << &this->manager << " попало на замедляющую клетку" << std::endl;
            return;
        }
    }

    if (canAttack) {
        manager.attack(field.getFieldCells()[priorityEnemy.entityCoordinates.x][priorityEnemy.entityCoordinates.y].getEntityInCell());
    }
}

EnemyController::EntityWithNearestPositionToAttackFrom
EnemyController::chooseByPriority(std::vector<EntityWithNearestPositionToAttackFrom> &enemyWithNearestPositionToAttack, std::vector<std::vector<int>>& distances) {
    std::vector<EntityWithNearestPositionToAttackFrom> nearestEnemies;
    int minRange = INT_MAX;
    for (EntityWithNearestPositionToAttackFrom position : enemyWithNearestPositionToAttack) {
        minRange = distances[position.attackFromCoordinates.x][position.attackFromCoordinates.y] ? distances[position.attackFromCoordinates.x][position.attackFromCoordinates.y] < minRange : minRange;
    }
    for (EntityWithNearestPositionToAttackFrom position : enemyWithNearestPositionToAttack) {
        if (distances[position.attackFromCoordinates.x][position.attackFromCoordinates.y] == minRange)
            nearestEnemies.push_back(position);
    }

    for (EntityType highestPriority: this->priorityOfAttack) {
        for (EntityWithNearestPositionToAttackFrom coords: nearestEnemies) {
            if (this->field.getFieldCells()[coords.entityCoordinates.x][coords.entityCoordinates.y].getEntityInCell().getType() ==
                highestPriority) {
                return coords;
            }
        }
    }
    throw ChooseEnemyPriorityException("unexpected behavior: chooseByPriority");
}


