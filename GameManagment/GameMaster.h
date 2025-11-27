//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_GAMEMASTER_H
#define LABA1_GAMEMASTER_H


#include <string>
#include "../GameField/Field.h"
#include "../Entities/Creatures/Player.h"
#include "Controllers/AllyController.h"
#include "Controllers/EnemyController.h"
#include "Controllers/Building/EnemySpawnerBuildingController.h"
#include "Controllers/Building/EnemyDefenceTowerController.h"
#include "Controllers/PlayerController.h"
#include "../Model/EnemyDefenceTowerModel.h"
#include "../Model/EnemySpawnerBuildingModel.h"
#include "../GameRender/Renderer.h"

class GameMaster {
public:
    GameMaster() {};

    bool startGame(const std::string &json);

    void gameCycle();

    void redraw();

    void addEnemyController(EnemyController *controller, std::shared_ptr<Entity> entity);

    void addAllyController(AllyController *controller, std::shared_ptr<Entity> entity);

    void save();
private:
    int level;
    Field *field;
    std::shared_ptr<Player> player;
    bool isSaved = false;

    std::vector<std::shared_ptr<EnemyController>> enemyControllers;
    std::vector<std::shared_ptr<AllyController>> allyControllers;
    std::vector<std::shared_ptr<EnemySpawnerBuildingController>> enemySpawnerBuildingControllers;
    std::vector<std::shared_ptr<EnemyDefenceTowerController>> defenceTowerControllers;
    std::unique_ptr<PlayerController> playerController;

    std::vector<std::shared_ptr<Entity>> entities;

    std::unique_ptr<EnemySpawner> enemySpawner;
    std::unique_ptr<AllySpawner> allySpawner;
    std::unique_ptr<SpellFactory> spellFactory;

    Renderer *renderer;

    const CompControlledCreatureModel enemyModel{3, 2, 2, 70};
    const CompControlledCreatureModel allyModel{3, 2, 2, 70};
//    const EnemyDefenceTowerModel defenceTowerModel{3,3,3};
//    const EnemySpawnerBuildingModel spawnerBuildingModel{2,2};

    void waiterToContinue();
    void checkEntitiesAfterMove();
    void upgradeEntity();
};


#endif //LABA1_GAMEMASTER_H
