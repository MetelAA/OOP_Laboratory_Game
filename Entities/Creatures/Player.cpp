//
// Created by Artem on 22.09.2025.
//

#include "Player.h"

LongRangeAttack &Player::getLongRangeAttack() noexcept {
    return longRangeAttack;
}

CloseRangeAttack &Player::getCloseRangeAttack() noexcept {
    return closeRangeAttack;
}
