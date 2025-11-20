//
// Created by Artem on 24.09.2025.
//

#include "GameMaster.h"
#include "../GameSetup/Utils/JsonParser.h"


void GameMaster::start(const std::string& json) {
    std::map<std::string, std::string> gameMap = JsonParser::parseJsonWithNestedObj(json);
    this->level = std::stoi(gameMap.at("level"));
    std::map<std::string, std::string> fieldMap = JsonParser::parseJsonWithNestedObj(gameMap.at("field"));
    this->field = Field::deserialize(fieldMap);

    EnemySpawner enemySpawner(this->enemyModel, *this->field, *this);
    AllySpawner allySpawner(this->allyModel, *this->field, *this);
    SpellFactory spellFactory(allySpawner);
    std::map<std::string, std::string> playerMap = JsonParser::parseJsonWithNestedObj(gameMap.at("player"));
    this->player = std::shared_ptr<Player>(Player::deserialize(playerMap, spellFactory));

    for (int x = 0; x < this->field->getHeight(); ++x) {
        for (int y = 0; y < this->field->getWidth(); ++y) {
            if (this->field->getFieldCells()[x][y].hasEntityInCell()){
                std::shared_ptr<Entity> entity = this->field->getFieldCells()[x][y].getEntityInCell();
                switch (entity->getType()) {
                    case EntityType::PlayerEnt:
                        break;
                    case EntityType::EnemyEnt:{
                        std::shared_ptr<CompControlledCreature> enemy = std::dynamic_pointer_cast<CompControlledCreature>(entity);
                        CompControlledCreatureManager enemyManager(*this->field, enemy);
                        EnemyController controller(*this->field, enemyManager);
                        this->enemyControllers.push_back(controller);
                    }
                        break;
                    case EntityType::EnemySpawnerBuildingEnt:{
                        std::shared_ptr<EnemySpawnerBuilding> building = std::dynamic_pointer_cast<EnemySpawnerBuilding>(entity);
                        EnemySpawnerBuildingManager manager(*this->field, building, enemySpawner);
                        EnemySpawnerBuildingController controller(manager, *this->field);
                        this->enemySpawnerBuildingControllers.push_back(controller);
                    }
                        break;
                    case EntityType::Ally:{
                        std::shared_ptr<CompControlledCreature> ally = std::dynamic_pointer_cast<CompControlledCreature>(entity);
                        CompControlledCreatureManager allyManager(*this->field, ally);
                        AllyController controller(*this->field, allyManager);
                        this->allyControllers.push_back(controller);
                    }
                        break;
                    case EntityType::EnemyDefenceTower:{
                        std::shared_ptr<EnemyDefenceTower> tower = std::dynamic_pointer_cast<EnemyDefenceTower>(entity);
                        EnemyDefenceTowerManager manager(*this->field, tower);
                        EnemyDefenceTowerController controller(*this->field, manager);
                        this->defenceTowerControllers.push_back(controller);
                    }
                        break;
                }
            }
        }
    }

    {
        PlayerManager manager(*this->field, player);
        PlayerController controller(*this->field, manager);
        this->playerController = std::unique_ptr<PlayerController>(&controller);
    }
    gameCycle();
}

void GameMaster::gameCycle() {
    
}

GameMaster::~GameMaster() {
    player = nullptr;
    playerController = nullptr;
    delete(this->field);
}



