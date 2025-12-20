//
// Created by Artem on 24.09.2025.
//

#include "GameSetup.h"
#include "../Constants/Constants.h"
#include "Utils/ReadRightJson.h"
#include "../GameManagment/GameMaster.h"
#include <iostream>
bool chooseSetupType();



void GameSetup::start() {
    std::cout << "Game setup starts!" << std::endl;
    std::string json;
    if (chooseSetupType()){
        try{
            json = ReadRightJson::read("../saveGame.txt");
        }catch (const UnexpectedBehaviorException& ex) {
            std::cout << "Can't open saveGame file, file damaged or not exist" << std::endl;
            start();
        }
    }else{
        json = ReadRightJson::read("../level0.txt");
    }
    GameMaster gm;
    if(gm.startGame(json)){
        setupLevelN("../level1.txt");
    }else{
        start();
    }

}

void GameSetup::setupLevelN(std::string fileName) {
    std::string json;
    json = ReadRightJson::read(fileName);
    GameMaster gm;
    gm.startGame(json);
}

bool chooseSetupType(){ //true - запуск с сохранения, false - запуск с нового уровня
    std::cout << "Choose game mod:\n1.New Game\n2.Saved game" << std::endl;
    int gm = Constants::getInput<int>();
    if (gm == 1){
        return false;
    }else if(gm == 2){
        return true;
    }else{
        std::cout << "Non correct value!" << std::endl;
        return chooseSetupType();
    }
}