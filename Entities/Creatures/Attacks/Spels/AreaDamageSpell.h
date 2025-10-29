//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_AREADAMAGESPELL_H
#define LABAOOP2_AREADAMAGESPELL_H
#include "Spell.h"
#include <map>
#include <memory>

class AreaDamageSpell : public Spell {
public:
    AreaDamageSpell() : Spell(SpellType::AreaDamageSpell) {}
    virtual int getDamage(int gradeLevel) const noexcept final;
    virtual int getRange(int gradeLevel) const noexcept final;
    virtual int getAreaRad(int gradeLevel) const noexcept final;

private:
    struct levelInfo{
        int damage, range, areaRad;
    };
    const std::map<int, levelInfo> levels = {{0, {1,   4, 2}},
                                             {1, {2,   4, 2}},
                                             {2, {3,   4, 3}},
                                             {3, {5, 6, 3}}
    };

};


#endif //LABAOOP2_AREADAMAGESPELL_H
