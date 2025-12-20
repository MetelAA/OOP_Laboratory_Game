//
// Created by Artem on 09.10.2025.
//

#ifndef LABA1_PLAYERCONTROLLER_H
#define LABA1_PLAYERCONTROLLER_H
#include <utility>

#include "../EntityManagers/CreatureManagers/PlayerManager.h"
#include "ExternalComandController/Actions/PlayerAction.h"
#include "../../Entities/Creatures/PlayerView.h"
#include "ExternalComandController/Actions/PlayerActionWithCoords.h"
#include "ExternalComandController/Actions/PlayerActionUseSpell.h"
#include "ExternalComandController/Actions/PlayerUpgradeAction.h"


class PlayerController {
public:
    PlayerController(const PlayerManager &manager, Field &field, const PlayerView &playerView) : manager(manager),
                                                                                                 field(field),
                                                                                                 playerView(playerView) {}

    bool doMove(GameMaster& gameMaster, PlayerAction* action);

protected:
    PlayerManager manager;
    Field& field;
    PlayerView playerView;

    bool canMoveOn(Constants::XYPair moveFrom, Constants::XYPair moveTo);
};


#endif //LABA1_PLAYERCONTROLLER_H
