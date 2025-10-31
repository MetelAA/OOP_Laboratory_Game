//
// Created by Artem on 30.10.2025.
//

#include "EnemyDefenceTowerController.h"
#include <iostream>
void EnemyDefenceTowerController::doMove(GameMaster &gameMaster) {
    std::cout << "Ход, EnemyDefenceTower: " << &this->manager << std::endl;

    if (this->manager.isCoolDowned()){
        this->manager.standOnCoolDown();


    }else{
        this->manager.doCoolDownStep();
    }
}
