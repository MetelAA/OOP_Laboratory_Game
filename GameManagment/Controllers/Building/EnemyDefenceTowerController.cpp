//
// Created by Artem on 30.10.2025.
//

#include "EnemyDefenceTowerController.h"
#include <iostream>
#include <cmath>

void EnemyDefenceTowerController::doMove(GameMaster &gameMaster) {
    std::cout << "Ход, EnemyDefenceTower: " << &this->manager << std::endl;

    if (this->manager.isCoolDowned()){

        std::vector<CreatureWithDistance> spottedEnemies;

        int attackRadius = this->manager.getAttackRadius();
        int minSpottedRadius = INT_MAX;
        for (int x = this->manager.getEntityCoords().x - attackRadius; x < this->manager.getEntityCoords().x + attackRadius; ++x) {
            for (int y = this->manager.getEntityCoords().y - attackRadius; y < this->manager.getEntityCoords().y + attackRadius; ++y) {
                try {
                    this->field.isCoordsAvailable(x, y);
                    if (this->field.getFieldCells()[x][y].hasEntityInCell() && this->typesToAttackWithPriority.count(this->field.getFieldCells()[x][y].getEntityInCellType()) > 0){
                        int rad = std::max(abs(x - this->manager.getEntityCoords().x), abs(y - this->manager.getEntityCoords().y));
                        minSpottedRadius = std::min(minSpottedRadius, rad);
                        spottedEnemies.push_back(CreatureWithDistance{this->field.getFieldCells()[x][y].getEntityInCellType(), rad, {x, y}});
                    }
                }catch (...) {}
            }
        }
        {
            std::vector<CreatureWithDistance> tmp;
            for(const CreatureWithDistance& creature : spottedEnemies){
                if (creature.distance == minSpottedRadius)
                    tmp.push_back(creature);
            }
            spottedEnemies = std::vector<CreatureWithDistance>(tmp);
        }

        if (!spottedEnemies.empty()){
            CreatureWithDistance priorityEnemy = spottedEnemies[0];

            for(const CreatureWithDistance& creature : spottedEnemies){
                if (this->typesToAttackWithPriority.at(priorityEnemy.creatureType) > this->typesToAttackWithPriority.at(priorityEnemy.creatureType)){
                    priorityEnemy = creature;
                }
            }

            this->manager.attackCoordinates(priorityEnemy.coords);
            this->manager.goToCoolDown();
        }else{
            std::cout << "EnemyDefenceTower: " << &this->manager << " no target to damage" << std::endl;
        }
    }else{
        std::cout << "EnemyDefenceTower: " << &this->manager << " on cool down" << std::endl;
        this->manager.doCoolDownStep();
    }
    std::cout << "EnemyDefenceTower: " << &this->manager << "закончило ход" << std::endl;
}
