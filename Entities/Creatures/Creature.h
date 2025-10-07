#ifndef LABA1_CREATURE_H
#define LABA1_CREATURE_H
#include "../Entity.h"
#include <string>
#include "../EntityType.h"

class Creature : public Entity {
private:

public:

    Creature(int xCoordinate, int yCoordinate, int healthPoint, EntityType type, bool isSlowedFlag, int stepRange)
            : Entity(xCoordinate, yCoordinate, healthPoint, type), isSlowedFlag(isSlowedFlag), stepRange(stepRange) {}

    virtual bool isSlowed() noexcept final;

    virtual void setXCoordinate(int x) noexcept final;

    virtual void setYCoordinate(int y) noexcept final;

    virtual int getStepRange() noexcept final;

protected:
    bool isSlowedFlag;
    int stepRange;
};


#endif