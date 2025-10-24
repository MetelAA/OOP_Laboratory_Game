//
// Created by Artem on 02.10.2025.
//

#include "PlayerManager.h"

void PlayerManager::moveTo(Constants::dxdy dxdy) {
    this->field.getFieldCells()[this->player.getXCoordinate() + dxdy.x][this->player.getYCoordinate() + dxdy.y].addEntityInCell(&this->player);
    this->field.getFieldCells()[this->player.getXCoordinate()][this->player.getYCoordinate()].clearCell();
    this->player.setXCoordinate(this->player.getXCoordinate() + dxdy.x);
    this->player.setYCoordinate(this->player.getYCoordinate() + dxdy.y);
}

void PlayerManager::attack(Entity &attackWhom, AttackType type) {
    switch (type) {
        case AttackType::CloseRange:
            attackWhom.changeHealthPoints((-1) * this->player.getCloseRangeAttack().getDamage());
        case AttackType::LongRange:
            if (round(sqrt(pow(attackWhom.getXCoordinate() - this->player.getXCoordinate(), 2) + pow(attackWhom.getYCoordinate() - this->player.getYCoordinate(), 2))) <= this->player.getLongRangeAttack().getRange()){ //neto!
                attackWhom.changeHealthPoints((-1) * this->player.getLongRangeAttack().getDamage());
            }else{
                throw "CompControlledCreature is far away!";
            }
    }
}