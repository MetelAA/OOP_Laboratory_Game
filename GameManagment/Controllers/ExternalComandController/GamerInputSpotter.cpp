//
// Created by Artem on 17.12.2025.
//
#include "GamerInputSpotter.h"
#include "Actions/PlayerAction.h"
#include "Actions/PlayerActionWithCoords.h"
#include "Actions/PlayerActionUseSpell.h"
#include "Actions/PlayerUpgradeAction.h"
#include "Actions/UpgradesType.h"

void GamerInputSpotter::playerMove(GameMaster &master) {
    std::string c;
    c = Constants::getInputWithoutN("Если хотите выйти и сохранить игру нажмиту \"" + std::to_string(this->keysModel.saveGameKey) + "\"");
    if(c[0] == this->keysModel.saveGameKey) {
        try{
            this->controller->doMove(master,  new PlayerAction(ActionType::SaveGame));
        }catch(...){

        }
        return;
    }

    bool flag = true;
    while(flag) {
        char yn;
        yn = Constants::getInputWithoutN("Вы хотите переместиться? (" + std::to_string(this->keysModel.confirmActionKey) + "\\" + std::to_string(this->keysModel.dismissActionKey) +"): ");
        if(yn == this->keysModel.confirmActionKey) {
            std::pair<int, int> yx = Constants::readTwoInts(
                    "Введите координаты на которые хотите перейти (сначала x потом y): ");
            yx.first--;
            yx.second--;
            try{
               this->controller->doMove(master, new PlayerActionWithCoords(ActionType::Move, {yx.second, yx.first}));
               flag = false;
               continue;
            }catch(...){

            }
        }else if(yn == this->keysModel.dismissActionKey) {
            flag = false;
            continue;
        }
        std::cout << "Вы ввели не правильное значение!" << std::endl;
    }

    flag = true;
    while(flag){
        char acs = Constants::getInputWithoutN("Вы хотите атаковать, применить заклинание или пропустить ход? (" + std::to_string(this->keysModel.attackKey) + "\\" + std::to_string(this->keysModel.spellKey) + "\\" + this->keysModel.continueKey + "): ");
        if (acs == this->keysModel.attackKey) {
            flag = false;
            bool isChanged = false;
            changeAttackType(master, &isChanged);
            if (!isChanged)
                attackOnCoords(master);
        }else if (acs == this->keysModel.spellKey) {
            useSpell(master);
            flag = false;
        }else if (acs == this->keysModel.continueKey) {
            flag = false;
        }else {
            std::cout << "Вы ввели не правильное значение!" << std::endl;
        }
    }
}

void GamerInputSpotter::changeAttackType(GameMaster &master, bool* isChanged) {
    bool flag = true;
    while(flag) {
        char ny = Constants::getInputWithoutN("Вы хотите сменить тип атаки?" + std::to_string(this->keysModel.confirmActionKey) + "\\" + std::to_string(this->keysModel.dismissActionKey) +"): ");
        if (ny == this->keysModel.confirmActionKey) {
            try{
                this->controller->doMove(master, new PlayerAction(ActionType::ChangeAttackType));
                flag = false;
                *isChanged = true;
                continue;
            }catch(...){

            }
        } else if (ny == this->keysModel.dismissActionKey) {
            flag = false;
            continue;
        }
        std::cout << "Вы ввели не правильное значение!" << std::endl;
    }
}

void GamerInputSpotter::attackOnCoords(GameMaster &master) {
    bool flag = true;

    while(flag) {
        std::pair<int, int> yx = Constants::readTwoInts("Введите координаты которые хотите атаковать (сначала x потом y): ");
        yx.first--;
        yx.second--;
        try{
            this->controller->doMove(master, new PlayerActionWithCoords(ActionType::Attack, {yx.second, yx.first}));
            flag = false;
            continue;
        }catch(...){

        }
    }

}

const std::map<SpellType, std::string> enumTypeToStrType = {
        {SpellType::DirectDamageSpell, "DirectDamageSpell"},
        {SpellType::BuffNextUsedSpell, "BuffNextUsedSpell"},
        {SpellType::AreaDamageSpell, "AreaDamageSpell"},
        {SpellType::SummoningSpell, "SummoningSpell"},
        {SpellType::CreateTrapSpell, "CreateTrapSpell"}
};

void GamerInputSpotter::useSpell(GameMaster &master) {
    std::cout << "В вашей руке: ";
    if(this->player.getSpellHand().getSpells().size() == 0) {
        std::cout << "пусто, применять нечего" << std::endl;
        return;
    }
    for (const auto & i : this->player.getSpellHand().getSpells()) {
        std::cout << enumTypeToStrType.at(i->getSpellType()) << ", ";
    }
    std::cout << std::endl;

    bool flag = true;
    int spellPos;
    while(flag) {
        int pos = Constants::getInput<int>("Выберете номер заклинания для применения (от 1 до n): ");
        if (pos <= 0 || pos > this->player.getSpellHand().getSpells().size()){
            std::cout << "не корректное значение!" << std::endl;
            continue;
        }
        pos--;
        spellPos = pos;
        flag = false;
    }

    flag = true;
    while(flag){
        switch(this->player.getSpellHand().getSpells()[spellPos]->getSpellType()) {
            case SpellType::DirectDamageSpell:
            case SpellType::AreaDamageSpell:
            case SpellType::SummoningSpell:
            case SpellType::CreateTrapSpell: {
                //перепутано специально
                std::pair<int, int> yx = Constants::readTwoInts(
                        "Введите координаты которые хотите атаковать (сначала x потом y): ");
                yx.first--;
                yx.second--;
                try{
                    this->controller->doMove(master, new PlayerActionUseSpell(ActionType::UseSpell, {yx.second, yx.first}, spellPos));
                    flag = false;
                    continue;
                }catch (...){

                }
            }
            break;
            case SpellType::BuffNextUsedSpell: {
                try {
                    this->controller->doMove(master, new PlayerActionUseSpell(ActionType::UseSpell, {1, -1}, spellPos));
                    flag = false;
                    continue;
                } catch (...) {

                }
            }
            break;
        }
    }


}

void GamerInputSpotter::waitingForContinueCommand(GameMaster &master) {
    bool flag = true;
    while(flag) {
        char cont = Constants::getInputWithoutN("Нажмите " + std::to_string(this->keysModel.continueKey) + " для продолжения: ");
        if (cont == this->keysModel.continueKey) {
            flag = false;
            try{
                this->controller->doMove(master, new PlayerAction(ActionType::Skip));
            }catch(...){}
        } else {
            std::cout << "Вы ввели неправильный символ!" << std::endl;
        }
    }
}

void GamerInputSpotter::upgradePlayer(GameMaster &master) {
    bool flag = true;
    while(flag) {
        std::cout << "Есть возможность улучшить игрока" << std::endl;
        int num = Constants::getInput<int>("Что вы хотите улучшить (требуется 1 очко), у вас: " + std::to_string(this->player.getScore()) + ":\n1.Урон\n2.Дальность хода\n3.Здоровье\n(введите цифру от 1 до 3х или 0 чтобы отказаться от выбора)");
        switch(num){
            case 0:
                flag = false;
                break;
            case 1:
                this->controller->doMove(master, new PlayerUpgradeAction(ActionType::UpgradePlayer, UpgradesType::UpdateDamage));
                flag = false;
                break;
            case 2:
                this->controller->doMove(master, new PlayerUpgradeAction(ActionType::UpgradePlayer, UpgradesType::UpdateMovementDistance));
                flag = false;
                break;
            case 3:
                this->controller->doMove(master, new PlayerUpgradeAction(ActionType::UpgradePlayer, UpgradesType::UpdateHealth));
                flag = false;
                break;
            default:
                std::cout << "Введённая цифра не в диапазоне от одного до трёх!" << std::endl;
                continue;
        }
    }
}