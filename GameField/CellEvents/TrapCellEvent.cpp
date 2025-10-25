//
// Created by Artem on 24.10.2025.
//

#include "TrapCellEvent.h"

void TrapCellEvent::impactOnCreatureInCell(Creature &creature) {
    creature.changeHealthPoints((-1) * this->damage);
}
