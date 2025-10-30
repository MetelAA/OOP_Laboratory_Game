//
// Created by Artem on 24.10.2025.
//

#include "AreaDamageSpell.h"
#include "../../../../Exceptions/Notifications/CantCastSpellOnCellNotification.h"
#include "../../../../Exceptions/CoordinateException.h"
#include <cmath>

void AreaDamageSpell::castSpell(int gradeLevel, const Field &field, Constants::XYPair from, Constants::XYPair to) const {
    levelInfo level = this->levels.at(this->levels.size() < gradeLevel ? gradeLevel : (this->levels.size() - 1));

    try{
        field.isCoordsAvailable(to.x, to.y);
    }catch (const CoordinateException &e){
        throw CantCastSpellOnCellNotification("Не получится применить заклинание так как: " + std::string(e.what()));
    }
    int distance = ceil(sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2)));
    if (distance > level.range){
        throw CantCastSpellOnCellNotification("Не получиться применить заклинание, цель слишком далеко!");
    }

    for(Constants::dxdy dxdy : damageCoords){
        try{
            int damageX = to.x + dxdy.x, damageY = to.y + dxdy.y;
            field.isCoordsAvailable(damageX, damageY);
            if(field.getFieldCells()[damageX][damageY].hasEntityInCell()){
                field.getFieldCells()[damageX][damageY].getEntityInCell().changeHealthPoints((-1) * level.damage);
            }
        }catch (const CoordinateException &e){}
    }

}
