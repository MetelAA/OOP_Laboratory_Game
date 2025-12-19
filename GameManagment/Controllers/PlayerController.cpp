//
// Created by Artem on 09.10.2025.
//

#include <iostream>
#include "PlayerController.h"
#include "../GameMaster.h"
#include "../../Entities/Creatures/Attacks/Spels/BuffSpellSpell.h"

bool PlayerController::doMove(GameMaster& gameMaster, PlayerAction* action) {
    std::cout << "Ход Player: " << &this->manager << std::endl;
    if (this->manager.isCreatureDisabled()){
        std::cout << "Player: " << &this->manager << " disabled -> disabled -> пропускает ход, тк замедлена с предыдущего хода" << std::endl;
        this->manager.enableCreature();
        return false;
    }
    std::cout << "Если хотите выйти и сохранить игру нажмиту \"c\"" << std::endl;
    std::string c;
    c = Constants::getInput<std::string>();
    if (c == "c"){
        gameMaster.save();
        return false;
    }
    while(true){
        std::cout << "Вы хотите переместиться? (y\\n): "<< std::endl;
        std::string yn;
        yn = Constants::getInput<std::string>();
        if (yn == "y"){
            std::cout << "Введите координаты на которые хотите перейти (сначала x потом y): "<< std::endl;
            int x, y;
            //перепутано специально
            y = Constants::getInput<int>();
            x = Constants::getInput<int>();
            x--;
            y--;
            //должен быть определён вектор дистанций и посчитан как в CompControlledCreature и провека. Сейчас без(
            std::cout << "PlayerController  перемещается в x: " << x << " y: " << y << std::endl;
            this->manager.moveTo({x,y});
            gameMaster.redraw();
            break;
        }else if(yn == "n"){
            break;
        }else{
            continue;
        }
        std::cout << std::endl;
    }




    while(true){
        std::cout << << std::endl;
        std::string acs;
        acs = Constants::getInput<std::string>();
        if (acs == "a"){
            attackTypeSelect();
            attack();
            break;
        }else if(acs == "c"){
            spellActivities();
            break;
        }else if(acs == "s"){
            break;
        }else{
            continue;
        }
        std::cout << std::endl;
    }
    
    return false;
}

void PlayerController::attackTypeSelect() {
    while(true){
        std::cout << std::endl;
        std::string yn;
        yn = Constants::getInput<std::string>();
        if (yn == "y"){
            this->manager.changeAttackType();
            std::cout << "тип атаки изменён на " << this->manager.getAttackTypeStr() << std::endl;
        }else if(yn == "n"){
            break;
        }else{
            continue;
        }
        std::cout << std::endl;
    }

}

void PlayerController::attack() {
    //также без проверок и тд....
    std::cout << " "<< std::endl;
    int x, y;
    //перепутано специально
    y = Constants::getInput<int>();
    x = Constants::getInput<int>();
    x--;
    y--;
    this->manager.attack({x, y}, this->manager.getAttackType());
    std::cout << "Player аттакует сущность в клетке по координатам " << x << " " << y << std::endl;
}


const std::map<SpellType, std::string> enumTypeToStrType = {
        {SpellType::DirectDamageSpell, "DirectDamageSpell"},
        {SpellType::BuffNextUsedSpell, "BuffNextUsedSpell"},
        {SpellType::AreaDamageSpell, "AreaDamageSpell"},
        {SpellType::SummoningSpell, "SummoningSpell"},
        {SpellType::CreateTrapSpell, "CreateTrapSpell"}
};
void PlayerController::spellActivities() {
    std::cout << "В вашей руке: ";
    if(this->manager.getSpells().size() == 0){
        std::cout << "пусто, применять нечего" << std::endl;
        return;
    }
    for (int i = 0; i < this->manager.getSpells().size(); ++i) {
        std::cout << enumTypeToStrType.at(this->manager.getSpells().at(i)->getSpellType()) << ", ";
    }
    std::cout << std::endl;

    while(true){
        std::cout << "Выберете номер заклинания для применения (от 1 до n)" << std::endl;
        int pos = Constants::getInput<int>();
        if (pos <= 0 || pos > this->manager.getSpells().size()){
            std::cout << "не корректное значение!" << std::endl;
            continue;
        }
        pos--;
        Spell* spell = this->manager.getSpells().at(pos).get();
        switch(spell->getSpellType()){
            case SpellType::DirectDamageSpell:
            case SpellType::AreaDamageSpell:
            case SpellType::SummoningSpell:
            case SpellType::CreateTrapSpell:{
                std::cout << "На какие координаты применять заклинание? ";
                std::cout << "Введите координаты которые хотите атаковать (сначала x потом y): "<< std::endl;
                int x, y;
                //перепутано специально
                y = Constants::getInput<int>();
                x = Constants::getInput<int>();
                x--;
                y--;
                try{
                    this->manager.getSpellHand().useSpellWithAIMBinding(pos, this->field, this->manager.getEntityCoords(), {x,y});
                }catch (...){
                    std::cout << "Не возможно применить данный тип заклинания на такую дистанцию!" << std::endl;
                }
            }
                break;
            case SpellType::BuffNextUsedSpell:
                this->manager.getSpellHand().useSpellWithoutAnyCoordsBinding(pos);
                break;

        }
        break;
    }



}
