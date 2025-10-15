//
// Created by Artem on 09.10.2025.
//

#include <iostream>
#include "PlayerController.h"

void PlayerController::doMove() {
    std::cout << "Ход Player: " << &this->manager << std::endl;
    if (this->manager.isCreatureDisabled()){
        std::cout << "Player: " << &this->manager << " disabled -> пропусакет ход" << std::endl;
    }

    

}
