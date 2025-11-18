//
// Created by Artem on 05.10.2025.
//

#ifndef LABA1_ENEMYSPAWNER_H
#define LABA1_ENEMYSPAWNER_H

#include "../model/CompControlledCreatureModel.h"
#include "../Entities/Creatures/CompControlledCreature.h"
#include "../GameField/Field.h"
#include "../GameField/Cell.h"
#include "../Exceptions/Notifications/CellImpassableNotification.h"
#include "../Exceptions/CoordinateException.h"
#include "../Exceptions/SpawnEntityException.h"
#include "../GameManagment/EntityManagers/CreatureManagers/CompControlledCreatureManager.h"
#include "../GameManagment/GameMaster.h"


class EnemySpawner {
public:
    EnemySpawner(const CompControlledCreatureModel &enemyModel, Field &field, GameMaster& gameMaster) : enemyModel(enemyModel), field(field), gameMaster(gameMaster) {}

    CompControlledCreatureManager* createEnemy(int x, int y);

protected:
    const CompControlledCreatureModel enemyModel;
    Field& field;
    GameMaster& gameMaster;
};


#endif //LABA1_ENEMYSPAWNER_H
