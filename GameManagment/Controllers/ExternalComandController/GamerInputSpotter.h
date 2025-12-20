#ifndef LABAOOP2_GAMERINPUTSPOTTER_H
#define LABAOOP2_GAMERINPUTSPOTTER_H

#include "../../../Model/InputKeysModel.h"
#include "../PlayerController.h"
#include "../../../Entities/Creatures/PlayerView.h"


class GamerInputSpotter {
public:
    GamerInputSpotter(const PlayerView &player, const std::shared_ptr<PlayerController> &controller,
                      const InputKeysModel &keysModel) : player(player), controller(controller), keysModel(keysModel) {}

    void playerMove(GameMaster& master);
    void waitingForContinueCommand(GameMaster& master);
    void upgradePlayer(GameMaster& master);

private:
    PlayerView player;
    std::shared_ptr<PlayerController> controller;
    InputKeysModel keysModel;

    void changeAttackType(GameMaster& master, bool* isChanged);
    void attackOnCoords(GameMaster& master);
    void useSpell(GameMaster& master);
};


#endif //LABAOOP2_GAMERINPUTSPOTTER_H