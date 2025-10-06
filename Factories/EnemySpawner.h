//
// Created by Artem on 05.10.2025.
//

#ifndef LABA1_ENEMYSPAWNER_H
#define LABA1_ENEMYSPAWNER_H
#include "../model/EnemyModel.h"
#include "../Entities/Creatures/Enemy.h"
#include "../GameField/Field.h"
#include "../Exceptions/CellImpassableException.h"
#include "../Exceptions/CoordinateException.h"
#include "../Exceptions/SpawnEntityException.h"


class EnemySpawner {
public:
    EnemySpawner(EnemyModel &enemyModel, Field &field) : enemyModel(enemyModel), field(field) {}

    Enemy& createEnemy(int x, int y);

protected:
    EnemyModel& enemyModel;
    Field& field;
};


#endif //LABA1_ENEMYSPAWNER_H
