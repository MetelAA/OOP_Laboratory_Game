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
    CreatureManager(Field &field, Entity *entity) : EntityManager(field, entity) {}

    virtual void moveTo(Constants::dxdy toCoordinates) = 0;
    virtual int getStepRange() = 0;


protected:

};


#endif //LABA1_CREATUREMANAGER_H
