//
// Created by Artem on 30.10.2025.
//

#ifndef LABAOOP2_ENEMYDEFENCETOWER_H
#define LABAOOP2_ENEMYDEFENCETOWER_H

#include <utility>

#include "Building.h"
#include "../Creatures/Attacks/Spels/DirectDamageSpell.h"
class EnemyDefenceTower : public Building{
public:
    EnemyDefenceTower(int xCoordinate, int yCoordinate, int healthPoint,
                      const DirectDamageSpell &spell, int attackRadius, int attackInterval) : Building(xCoordinate, yCoordinate, healthPoint, EntityType::EnemyDefenceTower),
                                                                                              spell(spell),
                                                                                              attackRadius(attackRadius),
                                                                                              attackInterval(attackInterval) {}

    virtual const DirectDamageSpell& getDamageSpell() const noexcept final;
    virtual int getAttackRadius() const noexcept final;
    virtual int getAttackInterval() const noexcept final;

    std::unique_ptr<Entity> clone() const override;

protected:
    DirectDamageSpell spell; //переделать по unip
    int attackRadius, attackInterval;
};


#endif //LABAOOP2_ENEMYDEFENCETOWER_H
