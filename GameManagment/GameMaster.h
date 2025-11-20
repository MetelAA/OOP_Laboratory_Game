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

    void start(const std::string &json);

    void gameCycle();

    void redraw();

    void addEnemyController(EnemyController &controller);

    void addAllyController(AllyController &controller);

private:
    int level;
    Field *field;
    std::shared_ptr<Player> player;

    std::vector<EnemyController> enemyControllers;
    std::vector<AllyController> allyControllers;
    std::vector<EnemySpawnerBuildingController> enemySpawnerBuildingControllers;
    std::vector<EnemyDefenceTowerController> defenceTowerControllers;
    std::unique_ptr<PlayerController> playerController;

    std::vector<std::shared_ptr<Entity>> entities;

    std::unique_ptr<EnemySpawner> enemySpawner;
    std::unique_ptr<AllySpawner> allySpawner;
    std::unique_ptr<SpellFactory> spellFactory;

    Renderer *renderer;

    const CompControlledCreatureModel enemyModel{3, 3, 3, 70};
    const CompControlledCreatureModel allyModel{3, 3, 3, 70};
//    const EnemyDefenceTowerModel defenceTowerModel{3,3,3};
//    const EnemySpawnerBuildingModel spawnerBuildingModel{2,2};

    void waiterToContinue();
    void checkEntitiesAfterMove();
};


#endif //LABA1_GAMEMASTER_H
