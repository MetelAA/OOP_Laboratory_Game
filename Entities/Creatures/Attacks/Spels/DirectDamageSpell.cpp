//
// Created by Artem on 24.10.2025.
//

#include "DirectDamageSpell.h"
#include "../../../EntityType.h"
#include "../../../../Exceptions/Notifications/CantCastSpellOnCellNotification.h"
#include "../../../../Exceptions/CoordinateException.h"
#include <cmath>
#include <iostream>

void DirectDamageSpell::castSpell(int gradeLevel, const Field& field, Constants::XYPair from, Constants::XYPair to) const {
    std::cout << "Применяем заклинание урона в точку" << std::endl;
    levelInfo level = this->levels.at(gradeLevel < this->levels.size() ? gradeLevel : (this->levels.size() - 1));

    try{
        field.isCoordsAvailable(to.x, to.y);
    }catch (const CoordinateException &e){
        throw CantCastSpellOnCellNotification("Не получится применить заклинание так как: " + std::string(e.what()));
    }
    int distance = ceil(sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2)));
    if (distance > level.range){
        throw CantCastSpellOnCellNotification("Не получиться применить заклинание, цель слишком далеко!");
    }

    std::cout << "Прилёт в точку x: " << to.x << " y: " << to.y;
    if (field.getFieldCells()[to.x][to.y].hasEntityInCell()){
        switch (field.getFieldCells()[to.x][to.y].getEntityInCellType()) {
            case EntityType::EnemyEnt:
            case EntityType::EnemySpawnerBuildingEnt:
            {
                field.getFieldCells()[to.x][to.y].damageEntityInCell((-1) * level.damage);
                std::cout << "В коориднатах из строки выше прилетело по: " << Constants::entityTypeToString(field.getFieldCells()[to.x][to.y].getEntityInCellType());
            }
            default:
                throw CantCastSpellOnCellNotification("По координатам x: " + std::to_string(to.x) + " y: " + std::to_string(to.y) + " нету ничего вражеского");
        }
    }
}

std::unique_ptr<Spell> DirectDamageSpell::clone() const {
    return std::make_unique<DirectDamageSpell>(*this);
}
