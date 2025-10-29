//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_TRAPCELLEVENT_H
#define LABAOOP2_TRAPCELLEVENT_H

#include "CellEvent.h"

class TrapCellEvent : public CellEvent{
public:
    TrapCellEvent(int damage): CellEvent(CellEventType::TrapEvent), damage(damage){}

    void impactOnCreatureInCell(Creature &creature) override;

    std::unique_ptr<CellEvent> clone() const override;

private:
    int damage;
};


#endif //LABAOOP2_TRAPCELLEVENT_H
