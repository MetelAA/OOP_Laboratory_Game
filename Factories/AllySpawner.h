//
// Created by Artem on 23.10.2025.
//

#ifndef LABAOOP2_ALLYSPAWNER_H
#define LABAOOP2_ALLYSPAWNER_H
#include "../model/CompControlledCreatureModel.h"
#include "../Entities/Creatures/CompControlledCreature.h"
#include "../GameField/Field.h"
#include "../GameField/Cell.h"
#include "../Exceptions/Notifications/CellImpassableNotification.h"
#include "../Exceptions/CoordinateException.h"
#include "../Exceptions/SpawnEntityException.h"

class AllySpawner {
public:
    AllySpawner(CompControlledCreatureModel &enemyModel, Field &field) : enemyModel(enemyModel), field(field) {}

    CompControlledCreature& createAlly(int x, int y);

protected:
    CompControlledCreatureModel& enemyModel;
    Field& field;
};


#endif //LABAOOP2_ALLYSPAWNER_H
