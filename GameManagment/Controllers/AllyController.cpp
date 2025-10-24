//
// Created by Artem on 23.10.2025.
//

#include "AllyController.h"

void AllyController::doMove() {
    this->computeAndDoMove(typesToAttack, priorityOfAttack);
}
