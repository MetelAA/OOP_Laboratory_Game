//
// Created by Artem on 02.10.2025.
//

#include "PlayerManager.h"
#include "../../../Exceptions/Notifications/SlowingCellNotification.h"

void PlayerManager::moveTo(Constants::dxdy dxdy) {
    this->field.getFieldCells()[this->player->getXCoordinate() + dxdy.x][this->player->getYCoordinate() + dxdy.y].addEntityInCell(this->player);
    this->field.getFieldCells()[this->player->getXCoordinate()][this->player->getYCoordinate()].clearCell();
    this->player->setXCoordinate(this->player->getXCoordinate() + dxdy.x);
    this->player->setYCoordinate(this->player->getYCoordinate() + dxdy.y);

    if (this->field.getFieldCells()[dxdy.x][dxdy.y].hasCellEvent()){
        this->field.getFieldCells()[dxdy.x][dxdy.y].impactOnCreatureByCellEvent();
        if (this->isCreatureDisabled())
            throw SlowingCellNotification("Player on slowing cell!");
    }
}

void PlayerManager::attack(Constants::dxdy coords, AttackType type) { //должны гарантировать что мы в выбранной клетке есть сущность для атаки
    if (!this->field.getFieldCells()[coords.x][coords.y].hasEntityInCell())
        throw UnexpectedBehaviorException("In selected coords to attack must be a target to attack! But it nihchego netu");
    switch (type) {
        case AttackType::CloseRange: {
            //в случае с выбранной атакой ближнего боя мы не проверяем условие на то, что противник реально рядом, эта проверка в контроллереSPELLSSPELLS
            this->field.getFieldCells()[coords.x][coords.y].damageEntityInCell(this->player->getCloseRangeAttack().getDamage());
        }
            break;
        case AttackType::LongRange: {
            //также как в случае с ближней аткакой мы гарантируем что координаты в радиусе атаки
            this->field.getFieldCells()[coords.x][coords.y].damageEntityInCell(this->player->getLongRangeAttack().getDamage());
        }
            break;
    }
}

bool PlayerManager::isCloseRangeAttackSelected() const noexcept {
    return this->player->isCloseRangeAttackSelected();
}

int PlayerManager::getLongRangeAttackRange() const noexcept {
    return this->player->getLongRangeAttack().getRange();
}

void PlayerManager::changeAttackType() noexcept {
    this->player->changeSelectedAttackType();
}

std::string PlayerManager::getAttackTypeStr() noexcept {
    return this->player->isCloseRangeAttackSelected() ? "close range attack" : "long range attack";
}

AttackType PlayerManager::getAttackType() noexcept {
    return this->player->isCloseRangeAttackSelected() ? AttackType::CloseRange : AttackType::LongRange;
}

const std::vector<std::unique_ptr<Spell>>& PlayerManager::getSpells() noexcept {
    return this->player->getSpellHand().getSpells();
}

SpellHand &PlayerManager::getSpellHand() {
    return this->player->getSpellHand();
}
