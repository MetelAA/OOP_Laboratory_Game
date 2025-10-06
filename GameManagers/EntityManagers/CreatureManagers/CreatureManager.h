//
// Created by Artem on 02.10.2025.
//

#ifndef LABA1_CREATUREMANAGER_H
#define LABA1_CREATUREMANAGER_H
#include "../../../Entities/Creatures/Creature.h"
#include "../../../GameField/Field.h"
#include "../EntityManager.h"

class CreatureManager : public EntityManager{
public:
    explicit CreatureManager(Field &field) : EntityManager(field) {}

protected:

};


#endif //LABA1_CREATUREMANAGER_H
