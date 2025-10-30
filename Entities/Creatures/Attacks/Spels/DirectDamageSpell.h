//
// Created by Artem on 24.10.2025.
//

#ifndef LABAOOP2_DIRECTDAMAGESPELL_H
#define LABAOOP2_DIRECTDAMAGESPELL_H

#include <map>
#include "SpellOnCoords.h"

class DirectDamageSpell : public SpellOnCoords {
public:
    DirectDamageSpell() : SpellOnCoords(SpellType::DirectDamageSpell) {} //так как заклинание апгрейда накладывается на руку а не на другие заклинания, то фактически не имеет смысла иметь параметры в
    //инстансе заклинания опред типа, тк все заклинания опред типа на одном уровне одинаковые. По сути инстанс это просто показатель наличия заклинания в руке. Хардкод оправдан, ну или можно поменять
    //на получение SpellModel которая формируется из конфиг файла и тд, но как будто оверхэд) Я уже боюсь представить то кол-во json-ов что у меня будет, не надо пж)

    void castSpell(int gradeLevel, const Field& field, Constants::XYPair from, Constants::XYPair to) const override;

private:
    struct levelInfo{
        int damage, range;
    };
    const std::map<int, levelInfo> levels = {{0, {2,   4}},
                                       {1, {4,   4}},
                                       {2, {6,   4}},
                                       {3, {111, 111}}
                                    };
};


#endif //LABAOOP2_DIRECTDAMAGESPELL_H
