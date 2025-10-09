//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_ENTITY_H
#define LABA1_ENTITY_H
#include "EntityType.h"

class Entity {
private:

public:
    Entity(int xCoordinate, int yCoordinate, int healthPoint, EntityType type) : xCoordinate(xCoordinate),
                                                                                 yCoordinate(yCoordinate),
                                                                                 healthPoints(healthPoint),
                                                                                 type(type) {
    }


    virtual int getXCoordinate() const noexcept final;

    virtual int getYCoordinate() const noexcept final;

    virtual EntityType getType() const noexcept final;

    virtual int getHealthPoints() const noexcept final;

    virtual void changeHealthPoints(int dHP) noexcept final;

    virtual bool isAlive() const noexcept final;

protected:
    int xCoordinate, yCoordinate, healthPoints;
    EntityType type;
};


#endif //LABA1_ENTITY_H
