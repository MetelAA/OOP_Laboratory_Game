#ifndef LABA1_CREATURE_H
#define LABA1_CREATURE_H
#include "../Entity.h"
#include <string>
#include "../EntityType.h"

class Creature : public Entity {
private:

public:

    Creature(int xCoordinate, int yCoordinate, int healthPoint, EntityType type, bool isDisabledFlag, int stepRange)
            : Entity(xCoordinate, yCoordinate, healthPoint, type), isDisabledFlag(isDisabledFlag), stepRange(stepRange) {}

    virtual bool isDisabled() noexcept final;

    virtual void setDisabledFlag(bool flag) noexcept final;

    virtual void setXCoordinate(int x) noexcept final;

    virtual void setYCoordinate(int y) noexcept final;

    virtual int getStepRange() const noexcept final;

protected:
    bool isDisabledFlag;
    int stepRange;
};


#endif