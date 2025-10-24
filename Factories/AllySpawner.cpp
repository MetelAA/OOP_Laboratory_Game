//
// Created by Artem on 23.10.2025.
//

#include "AllySpawner.h"

CompControlledCreature &AllySpawner::createAlly(int x, int y) {
    try{
        this->field.canMoveToOrSpawnOn(x, y);
        CompControlledCreature *enemy = new CompControlledCreature(x, y, enemyModel.healthPoint, EntityType::Ally,
                                                                   this->field.getFieldCells()[x][y].getCellType() == CellType::Slowing, enemyModel.damage, enemyModel.stepCount, enemyModel.chanceToDetectHostile);
        this->field.getFieldCells()[x][y].addEntityInCell(enemy);
        return *enemy;
    }catch (CellImpassableNotification& ex){
        throw SpawnEntityException(std::string("Can't spawn compControlledCreature Ally because: ") + ex.what());
    }catch (CoordinateException& ex){
        throw SpawnEntityException(std::string("Can't spawn compControlledCreature Ally because: ") + ex.what());
    }
}
