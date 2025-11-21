//
// Created by Artem on 09.10.2025.
//

#ifndef LABA1_PLAYERCONTROLLER_H
#define LABA1_PLAYERCONTROLLER_H
#include <utility>

#include "../EntityManagers/CreatureManagers/PlayerManager.h"

class PlayerController {
public:
    PlayerController(Field &field, PlayerManager manager) : manager(std::move(manager)), field(field) {}

    void doMove(GameMaster& gameMaster);

protected:
    PlayerManager manager;
    Field& field;

    void attackTypeSelect();
    void attack();
    void spellActivities();
};


#endif //LABA1_PLAYERCONTROLLER_H
