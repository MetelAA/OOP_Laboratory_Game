//
// Created by Artem on 23.10.2025.
//

#include "AllySpawner.h"

std::shared_ptr<CompControlledCreature> AllySpawner::createAlly(int x, int y) {
    try{
        this->field.canMoveToOrSpawnOn(x, y);
        std::shared_ptr<CompControlledCreature> enemy = std::make_shared<CompControlledCreature>(CompControlledCreature(x, y, enemyModel.healthPoint, EntityType::Ally,
                                                                   false, enemyModel.damage, enemyModel.stepCount, enemyModel.chanceToDetectHostile));
        this->field.getFieldCells()[x][y].addEntityInCell(enemy);
        if(field.getFieldCells()[x][y].hasCellEvent()){
            field.getFieldCells()[x][y].impactOnCreatureByCellEvent();
        }
        return enemy;
    }catch (CellImpassableNotification& ex){
        throw SpawnEntityException(std::string("Can't spawn compControlledCreature Ally because: ") + ex.what());
    }catch (CoordinateException& ex){
        throw SpawnEntityException(std::string("Can't spawn compControlledCreature Ally because: ") + ex.what());
    }
}
