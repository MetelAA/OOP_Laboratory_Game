//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_SLOWINGCELLEVENT_H
#define LABAOOP2_SLOWINGCELLEVENT_H

#include "CellEvent.h"

class SlowingCellEvent : public CellEvent{
public:
    explicit SlowingCellEvent(CellEventType type) : CellEvent(type) {}
    void impactOnCreatureInCell(Creature &creature) override;

    std::unique_ptr<CellEvent> clone() const override;

private:

};


#endif //LABAOOP2_SLOWINGCELLEVENT_H
