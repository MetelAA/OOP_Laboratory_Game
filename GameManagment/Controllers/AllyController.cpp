//
// Created by Artem on 23.10.2025.
//

#include "AllyController.h"

void AllyController::doMove(GameMaster& gameMaster) {
    this->computeAndDoMove(typesToAttack, priorityOfAttack, gameMaster);
}
