#include "CreatureManager.h"

int CreatureManager::getStepRange() const noexcept {
    return this->creature->getStepRange();
}

bool CreatureManager::isCreatureDisabled() const noexcept {
    return this->creature->isDisabled();
}

void CreatureManager::disableCreature() noexcept {
    this->creature->setDisabledFlag(true);
}

void CreatureManager::freeCreature() noexcept {
    this->creature->setDisabledFlag(false);
}
