//
// Created by Artem on 07.10.2025.
//

#ifndef LABA1_CONSTANTS_H
#define LABA1_CONSTANTS_H


#include <vector>
#include <iostream>
#include "../Entities/Creatures/Attacks/Spels/SpellType.h"
#include "../Entities/EntityType.h"
#include <limits>
#include <sstream>

class Constants {
public:
    struct XYPair{
        int x, y;
    };

    struct dxdy{ //нужна чтобы в некоторый контекст можно было передать именно её
        int x, y;
    };
    static inline const std::vector<Constants::dxdy> dxdys{{-1, 1},
                                                      {0,  1},
                                                      {1,  1},
                                                      {1,  0},
                                                      {1,  -1},
                                                      {0,  -1},
                                                      {-1, -1},
                                                      {-1, 0}};

    static const std::string spellTypeToString(SpellType type) {
        switch (type) {
            case SpellType::DirectDamageSpell: return "DirectDamageSpell";
            case SpellType::AreaDamageSpell: return "AreaDamageSpell";
            case SpellType::SummoningSpell: return "SummoningSpell";
            case SpellType::BuffNextUsedSpell: return "BuffNextUsedSpell";
            case SpellType::CreateTrapSpell: return "CreateTrapSpell";
            default: return "UnknownSpellType";
        }
    }
    static const std::string entityTypeToString(EntityType type) {
        switch (type) {
            case EntityType::PlayerEnt:        return "PlayerEnt";
            case EntityType::EnemyEnt:         return "EnemyEnt";
            case EntityType::EnemySpawnerBuildingEnt: return "EnemySpawnerBuildingEnt";
            case EntityType::Ally:             return "Ally";
            case EntityType::EnemyDefenceTower: return "EnemyDefenceTower";
            default:                           return "UnknownEntityType";
        }
    }

    template<typename T>
    static T getInput() {
        std::string line;
        while (true) {
            std::getline(std::cin, line);

            if constexpr (std::is_same_v<T, std::string>) {
                return line;
            } else {
                std::istringstream iss(line);
                T value;
                if (iss >> value && iss.eof()) {
                    return value;
                } else {
                    std::cout << "Error! Enter a correct value." << std::endl;
                }
            }
        }
    }
};


#endif //LABA1_CONSTANTS_H
