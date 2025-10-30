//
// Created by Artem on 30.10.2025.
//

#ifndef LABAOOP2_SPELLWITHOUTCOORDS_H
#define LABAOOP2_SPELLWITHOUTCOORDS_H

#include "Spell.h"

class SpellWithoutCoords : public Spell{
public:
    explicit SpellWithoutCoords(SpellType type) : Spell(type) {}
    virtual void castSpell(int gradeLevel, const Field& field, Constants::XYPair from) const = 0;
};


#endif //LABAOOP2_SPELLWITHOUTCOORDS_H
