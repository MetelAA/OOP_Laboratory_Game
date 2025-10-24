//
// Created by Artem on 08.10.2025.
//

#include "EnemyController.h"

void EnemyController::doMove() {
    this->computeAndDoMove(typesToAttack, priorityOfAttack);
}