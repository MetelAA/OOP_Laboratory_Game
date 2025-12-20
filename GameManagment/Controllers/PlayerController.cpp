//
// Created by Artem on 09.10.2025.
//

#include <iostream>
#include "PlayerController.h"
#include "../GameMaster.h"
#include "ExternalComandController/Actions/PlayerAction.h"
#include "../../Exceptions/Notifications/CantAttackOnCoordsNotification.h"

#include <cmath>

bool PlayerController::doMove(GameMaster& gameMaster, PlayerAction* action) {
    switch (action->type) {
        case ActionType::SaveGame: {
            gameMaster.saveGame();
        }
        break;
        case ActionType::Move: {
            PlayerActionWithCoords* playerAction = static_cast<PlayerActionWithCoords*>(action);

            if (this->field.canMoveToOrSpawnOnNoExcept(this->playerView.getXCoordinate(), this->playerView.getYCoordinate()) && canMoveOn({this->playerView.getXCoordinate(), this->playerView.getYCoordinate()}, playerAction->xy)){
                return true;
            }else{
                throw CoordinateException("Вы не можете перейти на клетку x/y:" + std::to_string(this->playerView.getXCoordinate()) + "/" + std::to_string(this->playerView.getYCoordinate()) + " клетка или за гарницами поля или недоступна!");
            }
        }
        break;
        case ActionType::Attack: {
            PlayerActionWithCoords* playerAction = static_cast<PlayerActionWithCoords*>(action);


            this->field.isCoordsAvailable(playerAction->xy.x, playerAction->xy.y); //швыряет ошибку CoordinateException (ненавижу плюсы!!!!!!!!!!)

            if(!this->field.getFieldCells()[playerAction->xy.x][playerAction->xy.y].hasEntityInCell())
                throw CantAttackOnCoordsNotification("Невозможно проатаковать по введённым координатам, там некого нету!");

            if (this->playerView.isCloseRangeAttackSelected()){
                Constants::dxdy dxdyEcs = {this->playerView.getXCoordinate() - playerAction->xy.x, this->playerView.getYCoordinate() - playerAction->xy.y};
                bool flag = false;
                for(Constants::dxdy pair : Constants::dxdys){
                    if (dxdyEcs == pair){
                        flag = true;
                        break;
                    }
                }

                if (!flag)
                    throw CantAttackOnCoordsNotification("Вы не можете атаковать ближней атакой сущности находящиеся дальше чем одна клетка от вас!");

                this->manager.attack(playerAction->xy, AttackType::CloseRange);
                return true;
            } else {
                int distance = std::pow(this->playerView.getXCoordinate() - playerAction->xy.x, 2) + std::pow(this->playerView.getYCoordinate() - playerAction->xy.y, 2);
                if(distance > std::pow(this->playerView.getLongRangeAttack().getRange(), 2))
                    throw CantAttackOnCoordsNotification("Вы не можете атаковать ближней атакой сущности находящиеся дальше чем дальность дальней атаки!");

                this->manager.attack(playerAction->xy, AttackType::LongRange);
                return true;
            }
        }
        break;
        case ActionType::UseSpell: {
            PlayerActionUseSpell* playerAction = static_cast<PlayerActionUseSpell*>(action);

            switch(this->manager.getSpellHand().getSpells()[playerAction->spellNum].get()->getSpellType()){
                case SpellType::DirectDamageSpell:
                case SpellType::AreaDamageSpell:
                case SpellType::SummoningSpell:
                case SpellType::CreateTrapSpell:
                    this->manager.getSpellHand().useSpellWithAIMBinding(playerAction->spellNum, this->field, this->manager.getEntityCoords(), playerAction->xy);
                    break;
                case SpellType::BuffNextUsedSpell:
                    this->manager.getSpellHand().useSpellWithoutAnyCoordsBinding(playerAction->spellNum);
                    break;
            }
        }
        break;
        case ActionType::Skip: {
            std::cout << "скипанули! УДАЛИТ Ь!!!!!";
        }
        break;
        case ActionType::ChangeAttackType: {
            bool isCloseRangeSelected = this->playerView.isCloseRangeAttackSelected();
            this->manager.changeAttackType();
            std::cout << "Тип атаки был изменён с " << (isCloseRangeSelected ? "ближней" : "дальней") << " на " << (isCloseRangeSelected ? "дальнюю" : "ближнюю") << std::endl;
        }
        break;
        case ActionType::UpgradePlayer: {
            PlayerUpgradeAction* playerAction = static_cast<PlayerUpgradeAction*>(action);
            this->manager.upgradePlayer(playerAction->upgradeType);
            std::cout << "Улучшение успешно произведено!" << std::endl;
        }
        return true;
        break;
        case ActionType::Continue:{
            std::cout << "продолжили! УДАЛИТ Ь!!!!!";
        }
        break;
    }
}

bool PlayerController::canMoveOn(Constants::XYPair moveFrom, Constants::XYPair moveTo) {
    std::vector<std::vector<int>> distances(this->field.getHeight(), std::vector<int>(this->field.getWidth(), -1));
    std::queue<Constants::XYPair> queue;
    queue.push(moveFrom);
    distances[manager.getEntityCoords().x][manager.getEntityCoords().y] = 0;

    while (!queue.empty()) {
        Constants::XYPair tempCoords = queue.front();
        queue.pop();
        for (Constants::dxdy dxdy: Constants::dxdys) {
            if (this->field.canMoveToOrSpawnOnNoExcept(tempCoords.x + dxdy.x, tempCoords.y + dxdy.y) && distances[tempCoords.x + dxdy.x][tempCoords.y + dxdy.y] == -1) {
                distances[tempCoords.x + dxdy.x][tempCoords.y + dxdy.y] = distances[tempCoords.x][tempCoords.y] + 1;
                queue.push({tempCoords.x + dxdy.x, tempCoords.y + dxdy.y});
            }
        }
    }

    return distances[moveTo.x][moveTo.y] <= this->playerView.getStepRange();
}
