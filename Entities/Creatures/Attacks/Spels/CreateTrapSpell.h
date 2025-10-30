//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_CREATETRAPSPELL_H
#define LABAOOP2_CREATETRAPSPELL_H

#include "SpellOnCoords.h"
#include "../../../../GameField/CellEvents/TrapCellEvent.h"
#include <memory>
#include <map>

class CreateTrapSpell : public SpellOnCoords {
public:
    CreateTrapSpell() : SpellOnCoords(SpellType::CreateTrapSpell) {} //инфа почему так в диркет дамаге
    void castSpell(int gradeLevel, const Field &field, Constants::XYPair from, Constants::XYPair to) const override;

    std::unique_ptr<Spell> clone() const override;

private:
    struct levelInfo{
        int damage;
    };
    const std::map<int, levelInfo> levels = {{0, {2}},
                                             {1, {4}},
                                             {2, {6}},
                                             {3, {8}}
    };
};


#endif //LABAOOP2_CREATETRAPSPELL_H
