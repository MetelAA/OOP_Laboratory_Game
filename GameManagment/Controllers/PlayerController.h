//
// Created by Artem on 09.10.2025.
//

#ifndef LABA1_PLAYERCONTROLLER_H
#define LABA1_PLAYERCONTROLLER_H
#include <utility>

#include "../EntityManagers/CreatureManagers/PlayerManager.h"
#include "ExternalComandController/Actions/PlayerAction.h"
#include "ExternalComandController/Actions/PlayerActionWithCoords.h"
#include "ExternalComandController/Actions/PlayerActionUseSpell.h"


class PlayerController {
public:
    PlayerController(Field &field, PlayerManager manager) : manager(std::move(manager)), field(field) {}

    bool doMove(GameMaster& gameMaster, PlayerAction* action);

protected:
    PlayerManager manager;
    Field& field;

    void attackTypeSelect();
    void attack();
    void spellActivities();
};


#endif //LABA1_PLAYERCONTROLLER_H
