//
// Created by Artem on 08.10.2025.
//

#include "EnemyController.h"

void EnemyController::doMove(GameMaster& gameMaster) {
    this->computeAndDoMove(typesToAttack, priorityOfAttack, gameMaster);
}