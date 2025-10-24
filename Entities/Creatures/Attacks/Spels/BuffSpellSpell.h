//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_BUFFSPELLSPELL_H
#define LABAOOP2_BUFFSPELLSPELL_H

#include "Spell.h"

class BuffSpellSpell : public Spell{
    BuffSpellSpell(): Spell(SpellType::BuffNextUsedSpell){};
};


#endif //LABAOOP2_BUFFSPELLSPELL_H
