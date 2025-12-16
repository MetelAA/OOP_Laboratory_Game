#ifndef LABAOOP2_GAMERINPUTSPOTTER_H
#define LABAOOP2_GAMERINPUTSPOTTER_H

#include "../../../Model/InputKeysModel.h"
#include "../PlayerController.h"
#include "../../../Entities/Creatures/PlayerView.h"



class GamerInputSpotter {
public:
    GamerInputSpotter(const PlayerView &player, PlayerController &controller, const InputKeysModel &keysModel) : player(
            player), controller(controller), keysModel(keysModel) {}

    void playerMove(GameMaster& master);
    void waitingForContinueCommand(GameMaster& master);
    void upgradePlayer(GameMaster& master);

private:
    PlayerView player;
    PlayerController& controller;
    InputKeysModel keysModel;

};


#endif //LABAOOP2_GAMERINPUTSPOTTER_H