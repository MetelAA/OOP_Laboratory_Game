//
// Created by Artem on 20.11.2025.
//

#ifndef LABAOOP2_RENDERER_H
#define LABAOOP2_RENDERER_H


#include <vector>
#include <memory>
#include "../Entities/Entity.h"
#include "../GameField/Field.h"

class Player;

class Renderer {
public:
    Renderer(const Field &field, const std::vector<std::shared_ptr<Entity>> &entities,
             const std::shared_ptr<Player> &player) : field(field), entities(entities), player(player) {}

    void draw();
    void prepareConsole();
    void displayLegend();
    void displayEntitiesInfo();
    void clearDisplay();
    void displayPlayerInfo();

private:
    const Field& field;
    const std::vector<std::shared_ptr<Entity>>& entities;
    const std::shared_ptr<Player> player;

    const std::string WALL = "■";        // Черный квадрат
    const std::string ENEMY = "●";       // Черный круг
    const std::string ENEMY_TOWER = "▲"; // Черный треугольник
    const std::string SPAWNER = "♦";     // Черный ромб
    const std::string ALLY = "A";        // Белый круг
    const std::string EXIT = "→";        // Стрелка вправо
    const std::string TRAP = "×";        // Крестик
    const std::string PLAYER = "◎";      // Круг в круге
    const std::map<EntityType, std::string> entityTypeToCharS = {
            {EntityType::PlayerEnt, PLAYER},
            {EntityType::EnemyDefenceTower, ENEMY_TOWER},
            {EntityType::EnemyEnt, ENEMY},
            {EntityType::Ally, ALLY},
            {EntityType::EnemySpawnerBuildingEnt, SPAWNER}
    };
    const std::map<CellEventType, std::string> cellEventTypeToCharS = {
            {CellEventType::TrapEvent, TRAP},
            {CellEventType::SlowingEvent, " "}
    };
    const std::map<EntityType, std::string> entityTypeToStr = {
            {EntityType::PlayerEnt, "Player"},
            {EntityType::EnemyDefenceTower, "Tower"},
            {EntityType::EnemyEnt, "Enemy"},
            {EntityType::Ally, "Ally"},
            {EntityType::EnemySpawnerBuildingEnt, "Spawner"}
    };

    void drawGridRounded(const std::vector<std::vector<std::string>>& grid);

};


#endif //LABAOOP2_RENDERER_H
