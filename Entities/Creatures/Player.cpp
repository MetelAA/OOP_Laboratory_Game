//
// Created by Artem on 22.09.2025.
//

#include "Player.h"

LongRangeAttack Player::getLongRangeAttack() const noexcept {
    return longRangeAttack;
}

CloseRangeAttack Player::getCloseRangeAttack() const noexcept {
    return closeRangeAttack;
}
