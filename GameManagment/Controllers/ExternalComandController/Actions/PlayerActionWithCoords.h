//
// Created by Artem on 17.12.2025.
//

#ifndef LABAOOP2_PLAYERACTIONWITHCOORDS_H
#define LABAOOP2_PLAYERACTIONWITHCOORDS_H

#include "PlayerAction.h"

class PlayerActionWithCoords : public PlayerAction {
public:
    PlayerActionWithCoords(ActionType type, int x, int y) : PlayerAction(type), x(x), y(y) {}
    int x, y;
};


#endif //LABAOOP2_PLAYERACTIONWITHCOORDS_H
