//
// Created by Artem on 24.10.2025.
//

#include "SlowingCellEvent.h"

void SlowingCellEvent::impactOnCreatureInCell(Creature &creature) {
    creature.setDisabledFlag(true);
}