//
// Created by Artem on 23.10.2025.
//

#ifndef LABAOOP2_SPELL_H
#define LABAOOP2_SPELL_H

#include "SpellType.h"

class Spell {
public:
    virtual SpellType getSpellType() const noexcept final;

private:
    SpellType type;
};


#endif //LABAOOP2_SPELL_H
