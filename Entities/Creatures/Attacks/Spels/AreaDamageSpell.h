//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_AREADAMAGESPELL_H
#define LABAOOP2_AREADAMAGESPELL_H
#include "Spell.h"

class AreaDamageSpell : public Spell {
public:
    AreaDamageSpell(int damage, int range, int areaRad) : Spell(SpellType::AreaDamageSpell), damage(damage), range(range),
                                                                       areaRad(areaRad) {}
    virtual int getDamage() const noexcept final;
    virtual int getRange() const noexcept final;
    virtual int getAreaRad() const noexcept final;

private:
    int damage, range, areaRad;

};


#endif //LABAOOP2_AREADAMAGESPELL_H
