//
// Created by Artem on 17.12.2025.
//

#ifndef LABAOOP2_PLAYERACTIONUSESPELL_H
#define LABAOOP2_PLAYERACTIONUSESPELL_H

#include "PlayerActionWithCoords.h"

class PlayerActionUseSpell : public PlayerActionWithCoords {
public:
    PlayerActionUseSpell(ActionType type, int x, int y, int spellNum) : PlayerActionWithCoords(type, x, y),
                                                                        spellNum(spellNum) {}

    int spellNum;
};


#endif //LABAOOP2_PLAYERACTIONUSESPELL_H
