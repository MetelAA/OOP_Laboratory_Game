#include <iostream>

#include "Entities/Entity.h"
#include "Entities/Creatures/Creature.h"
#include "Entities/Creatures/CompControlledCreature.h"
#include "Entities/Creatures/Player.h"
#include "GameSetup/JsonParser.h"
#include "Entities/Buildings/EnemyDefenceTower.h"
#include "GameSetup/Utils/ReadRightJson.h"
#include "GameSetup/GameSetup.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <map>
#include <windows.h>
#include <cstdlib> // для system()
#include "GameManagment/GameMaster.h"



int main() {

        int width = 8;
        int height = 9;
        std::vector<std::vector<Cell>> cells;

        for (int x = 0; x < height; ++x) {
            std::vector<Cell> line;
            for (int y = 0; y < width; ++y) {
                if(x == 0 && y == 3){
                    line.push_back(Cell(CellType::Impassable));
                }
                else if(x == 0 && y == (width-1)){
                    // Используем make_shared для создания в куче
                    auto creature = std::make_shared<CompControlledCreature>(x, y, 5, EntityType::EnemyEnt, false, 2, 0, 99);
                    Cell cell(CellType::Default, creature, nullptr);
                    line.push_back(cell);
                }
                else if (x == 1 && y == 4){
                    // Аналогично для EnemyDefenceTower
                    auto tower = std::make_shared<EnemyDefenceTower>(x, y, 8, 3, 2);
                    Cell cell(CellType::Default, tower, nullptr);
                    line.push_back(cell);
                }
                else if(x == 2 && y == 1){
                    auto event = std::make_unique<SlowingCellEvent>();
                    Cell cell(CellType::Default, nullptr, std::move(event));
                    line.push_back(cell);
                }
                else if(x == 4 && y == 1){
                    auto creature = std::make_shared<CompControlledCreature>(x, y, 5, EntityType::EnemyEnt, false, 2, 3, 99);
                    Cell cell(CellType::Default, creature, nullptr);
                    line.push_back(cell);
//                    line.push_back(Cell(CellType::Default, nullptr, nullptr));
                }
                else if (x == 4 && y == 4){
                    line.push_back(Cell(CellType::Impassable));
                }
                else {
                    line.push_back(Cell(CellType::Default, nullptr, nullptr));
                }
            }
            cells.push_back(line);
        }
        Field field(width, height, cells);
        std::string fieldJson = field.serialize();
//
//
//
//
//
//
//
//
//        std::vector<std::unique_ptr<Spell>> spels;
//        SpellHand hand(0, std::move(spels));
//
//        Player player(0, 0, 3, false, 2, CloseRangeAttack(3), LongRangeAttack(2,2), true, 0, hand);
//    std::string res;
//
//    res+="{";
//    res+="level:0,";
//    res+="field:" + fieldJson+=",";
//    res+="player:" + player.serialize()+"}";
//
//
//    GameMaster gm;
//    gm.start(res);
//



    GameSetup::start();























    //    std::string pl = player.serialize();
    //
    //    std::cout << pl << std::endl;
    //    std::map<std::string, std::string> mp = JsonParser::parseJsonWithNestedObj(fieldJson);
    //    Field* desField = Field::deserialize(mp);
    //    GameMaster gm;
    //    AllySpawner spawner({1,1,1,1}, field, gm);
    //    SpellFactory spellFactory(spawner);
    //
    //    std::map<std::string, std::string> jsonPLMap = JsonParser::parseJsonWithNestedObj(pl);
    //    Player* ds = Player::deserialize(jsonPLMap, spellFactory);
    //
    //    std::cout << (*ds).serialize() << std::endl;














//    ReadRightJson::write(fieldJson, "aboba.txt");
//

////
//    std::vector<std::string> cellsStrs = JsonParser::parseJsonArray(mp.at("cells"));
//    for(std::string s : cellsStrs){
//        std::cout << s << std::endl;
//    }
////

//
//    std::string cmp = (*desField).serialize();
//
//    std::cout << cmp << std::endl;
//    std::map<std::string, std::string> mp2 = JsonParser::parseJsonWithNestedObj(cmp);
//    std::vector<std::string> cellsStrs1 = JsonParser::parseJsonArray(mp2.at("cells"));
//    for(std::string s : cellsStrs1){
//        std::cout << s << std::endl;
//    }
//
//
//    for (int i = 0; i < cellsStrs.size(); ++i) {
//        if(cellsStrs[i] == cellsStrs1[i]){
//            std::cout << "true" << std::endl;
//        }else{
//            std::cout << "false" << std::endl;
//        }
//    }

//    std::string t = "[{type:Default,event:{},entityInCell:{}}, {}, {fdsfdsfds}, dsfs]";
//
//    std::vector<std::string> a = JsonParser::parseJsonArray(t);
//
//    for(auto s : a){
//        std::cout << s << " | ";
//    }


    return 0;
}