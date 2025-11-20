//
// Created by Artem on 09.10.2025.
//

#ifndef LABA1_PLAYERCONTROLLER_H
#define LABA1_PLAYERCONTROLLER_H
#include <utility>

#include "../EntityManagers/CreatureManagers/PlayerManager.h"

class PlayerController {
public:
    PlayerController(const Field &field, PlayerManager manager) : manager(std::move(manager)), field(field) {}

    void doMove();

protected:
    PlayerManager manager;
    const Field& field;
};


#endif //LABA1_PLAYERCONTROLLER_H
