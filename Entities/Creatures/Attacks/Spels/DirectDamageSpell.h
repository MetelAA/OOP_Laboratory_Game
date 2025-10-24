//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_DIRECTDAMAGESPELL_H
#define LABAOOP2_DIRECTDAMAGESPELL_H
#include "Spell.h"

class DirectDamageSpell : public Spell {
public:
    DirectDamageSpell(int damage, int range) : Spell(SpellType::DirectDamageSpell), damage(damage), range(range) {}

    virtual int getDamage() const noexcept final;
    virtual int getRange() const noexcept final;

private:
    int damage, range;
};


#endif //LABAOOP2_DIRECTDAMAGESPELL_H
