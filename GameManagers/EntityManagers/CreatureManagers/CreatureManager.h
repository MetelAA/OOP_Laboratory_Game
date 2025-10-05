//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_CREATUREMANAGER_H
#define LABA1_CREATUREMANAGER_H
#include "../../../Entities/Creatures/Creature.h"
#include "../../../GameField/Field.h"
#include "../../../Exceptions/CoordinateException.h"
#include "../../../GameField/CellType.h"
#include "../../../Exceptions/CellImpassableException.h"
#include "../../../Entities/EntityType.h"

class CreatureManager {
public:
    CreatureManager(Creature &creature, Field &field) : creature(creature), field(field) {}
    virtual void moveTo(int dx, int dy) = 0;

protected:
    Creature &creature;
    Field &field;
};


#endif //LABA1_CREATUREMANAGER_H
