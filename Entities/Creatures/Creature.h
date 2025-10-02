#ifndef LABA1_CREATURE_H
#define LABA1_CREATURE_H
#include "../Entity.h"
#include <string>
#include "../EntityType.h"

class Creature : public Entity{
private:

public:
    Creature(int xCoordinate, int yCoordinate, int healthPoints, EntityType type) : Entity(xCoordinate, yCoordinate, type){
        this->healthPoints = healthPoints;
    }

    virtual bool isAlive() noexcept final;
    virtual void getHP(int dHealth) noexcept final;
    virtual void setXCoordinate(int x) noexcept final;
    virtual void setYCoordinate(int y) noexcept final;

protected:
    int healthPoints;
};


#endif