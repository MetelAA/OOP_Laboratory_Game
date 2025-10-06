//
// Created by Artem on 06.10.2025.
//

#ifndef LABA1_ENTITYMANAGER_H
#define LABA1_ENTITYMANAGER_H


#include "../../Entities/Creatures/Creature.h"
#include "../../GameField/Field.h"

class EntityManager {
public:
    virtual bool checkEntityStatus() = 0;


    explicit EntityManager(Field &field) : field(field) {}

protected:
    Field &field;
};

#endif //LABA1_ENTITYMANAGER_H
