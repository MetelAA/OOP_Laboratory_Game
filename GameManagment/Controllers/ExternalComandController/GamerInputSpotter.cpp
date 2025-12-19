//
// Created by Artem on 17.12.2025.
//
#include "GamerInputSpotter.h"
#include "Actions/PlayerAction.h"
#include "Actions/PlayerActionWithCoords.h"
#include "Actions/PlayerActionUseSpell.h"

void GamerInputSpotter::playerMove(GameMaster &master) {
    std::string c;
    c = Constants::getInputWithoutN("Если хотите выйти и сохранить игру нажмиту \"c\"");
    if(c[0] == this->keysModel.saveGameKey){
        try{
            this->controller.doMove(master,  new PlayerAction(ActionType::SaveGame));
        }catch(...){

        }
        return;
    }

    bool flag = true;
    while(flag){
        std::string yn;
        yn = Constants::getInput<std::string>("Вы хотите переместиться? (y\\n):");
        if(yn == "y"){
            std::pair<int, int> yx = Constants::readToInts("Введите координаты на которые хотите перейти (сначала x потом y): ");
            yx.first--;
            yx.second--;
            try{
               this->controller.doMove(master, new PlayerActionWithCoords(ActionType::Move, yx.second, yx.first));
               flag = false;
               continue;
            }catch(...){

            }
        }else if(yn == "n"){
            flag = false;
            continue;
        }
        std::cout << "Вы ввели не правильное значение!" << std::endl;
    }

    flag = true;
    while(flag){
        char acs = Constants::getInputWithoutN("Вы хотите атаковать, применить заклинание или пропустить ход? (a\\c\\s): ");
        switch (acs) {
            case 'a':{
                flag = false;
                bool isChanged = false;
                changeAttackType(master, &isChanged);
                if (!isChanged)
                    attackOnCoords(master);
            }
            break;
            case 'c':{

                flag = false;
            }
            break;
            case 's':
                flag = false;
            break;
            default:
                std::cout << "Вы ввели не правильное значение!" << std::endl;
                continue;
        }
    }
}

void GamerInputSpotter::changeAttackType(GameMaster &master, bool* isChanged) {
    bool flag = true;
    while(flag) {
        char ny = Constants::getInputWithoutN("Вы хотите сменить тип атаки(y\\n)?: ");
        if (ny == 'y') {
            try{
                this->controller.doMove(master, new PlayerAction(ActionType::ChangeAttackType));
                flag = false;
                *isChanged = true;
                continue;
            }catch(...){

            }
        } else if (ny == 'n') {
            flag = false;
            continue;
        }
        std::cout << "Вы ввели не правильное значение!" << std::endl;
    }
}

void GamerInputSpotter::attackOnCoords(GameMaster &master) {
    bool flag = true;

    while(flag){
        std::pair<int, int> yx = Constants::readToInts("Введите координаты которые хотите атаковать (сначала x потом y): ");
        yx.first--;
        yx.second--;
        try{
            this->controller.doMove(master, new PlayerActionWithCoords(ActionType::Attack, yx.second, yx.first));
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
    if(this->player.getSpellHand().getSpells().size() == 0){
        std::cout << "пусто, применять нечего" << std::endl;
        return;
    }
    for (int i = 0; i < this->player.getSpellHand().getSpells().size(); ++i) {
        std::cout << enumTypeToStrType.at(this->player.getSpellHand().getSpells().at(i)->getSpellType()) << ", ";
    }
    std::cout << std::endl;

    bool flag = true;
    while(flag){

    }
}

void GamerInputSpotter::waitingForContinueCommand(GameMaster &master) {

}

void GamerInputSpotter::upgradePlayer(GameMaster &master) {

}