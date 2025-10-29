//
// Created by Artem on 24.10.2025.
//

#include "TrapCellEvent.h"

void TrapCellEvent::impactOnCreatureInCell(Creature &creature) {
    creature.changeHealthPoints((-1) * this->damage);
}

std::unique_ptr<CellEvent> TrapCellEvent::clone() const {
    return std::make_unique<TrapCellEvent>(*this);
}
