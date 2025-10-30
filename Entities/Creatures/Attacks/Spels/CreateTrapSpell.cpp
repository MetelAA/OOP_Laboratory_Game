//
// Created by Artem on 24.10.2025.
//

#include "CreateTrapSpell.h"
#include "../../../../Exceptions/Notifications/CantCastSpellOnCellNotification.h"
#include "../../../../Exceptions/UniversalStringException.h"
#include <iostream>

void CreateTrapSpell::castSpell(int gradeLevel, const Field &field, Constants::XYPair from, Constants::XYPair to) const {
    std::cout << "Применяем заклинание создания ловушки джокушкера" << std::endl;
    int level = gradeLevel < this->levels.size() ? gradeLevel : (this->levels.size()-1);

    try{
        field.isCoordsAvailable(to.x, to.y);
        field.isCellPassable(to.x, to.y);
    }catch (const UniversalStringException &e){ //тут два типа ошибок координатная и непроходимая, обе наследницы универсальной
        throw CantCastSpellOnCellNotification("Не получится применить заклинание так как: " + std::string(e.what()));
    }

    auto* trap = new TrapCellEvent(this->levels.at(level).damage);
    field.getFieldCells()[to.x][to.y].setCellEvent(std::make_unique<TrapCellEvent>(*trap));
    std::cout << "Создали ловушку по координатам x: " << to.x << " y: " << to.y << std::endl;
}

std::unique_ptr<Spell> CreateTrapSpell::clone() const {
    return std::make_unique<CreateTrapSpell>(*this);
}
