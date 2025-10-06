#ifndef LABA1_CREATURE_H
#define LABA1_CREATURE_H
#include "../Entity.h"
#include <string>
#include "../EntityType.h"

class Creature : public Entity {
private:

public:
    Creature(int xCoordinate, int yCoordinate, int healthPoint, EntityType type, bool isSlowedFlag) : Entity(
            xCoordinate, yCoordinate, healthPoint, type), isSlowedFlag(isSlowedFlag) {}

    virtual bool isSlowed() noexcept final;

    virtual void setXCoordinate(int x) noexcept final;

    virtual void setYCoordinate(int y) noexcept final;

protected:
    bool isSlowedFlag;
};


#endif