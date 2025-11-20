//
// Created by Artem on 24.09.2025.
//

#include "GameMaster.h"
#include "../GameSetup/Utils/JsonParser.h"
#include "../GameRender/Renderer.h"
#include <chrono>
#include <thread>

void GameMaster::start(const std::string& json) {
    std::cout << "GameMaster start: started" << std::endl;
    std::map<std::string, std::string> gameMap = JsonParser::parseJsonWithNestedObj(json);
    this->level = std::stoi(gameMap.at("level"));
    std::cout << "GameMaster start: started to deserialize field" << std::endl;
    std::map<std::string, std::string> fieldMap = JsonParser::parseJsonWithNestedObj(gameMap.at("field"));
    this->field = Field::deserialize(fieldMap);
    std::cout << "GameMaster start: field deserialized successfully" << std::endl;

    std::cout << "GameMaster start: creating factories" << std::endl;
    this->enemySpawner = std::unique_ptr<EnemySpawner>(new EnemySpawner(this->enemyModel, *this->field, *this));
    this->allySpawner = std::unique_ptr<AllySpawner>(new AllySpawner(this->allyModel, *this->field, *this));
    this->spellFactory = std::unique_ptr<SpellFactory>(new SpellFactory(*allySpawner.get()));
    std::cout << "GameMaster start: factories created" << std::endl;
    std::cout << "GameMaster start:  started to deserialize player" << std::endl;
    std::map<std::string, std::string> playerMap = JsonParser::parseJsonWithNestedObj(gameMap.at("player"));
    this->player = std::shared_ptr<Player>(Player::deserialize(playerMap, *spellFactory.get()));
    std::cout << "GameMaster start: player deserialized successfully" << std::endl;

    std::cout << "GameMaster start: detecting Entities in field to contrast their controllers and managers" << std::endl;
    for (int x = 0; x < this->field->getHeight(); ++x) {
        for (int y = 0; y < this->field->getWidth(); ++y) {
            if (this->field->getFieldCells()[x][y].hasEntityInCell()){
                std::shared_ptr<Entity> entity = this->field->getFieldCells()[x][y].getEntityInCell();
                entities.push_back(entity);
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
                        EnemySpawnerBuildingManager manager(*this->field, building, *this->enemySpawner.get());
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
    std::cout << "GameMaster start: contrasted successfully" << std::endl;

    {
        std::cout << "GameMaster start: contrast PlayerController" << std::endl;
        PlayerManager manager(*this->field, player);
        PlayerController* controller = new PlayerController(*this->field, manager);
        this->playerController = std::unique_ptr<PlayerController>(controller);
    }
    this->field->getFieldCells()[this->player->getXCoordinate()][this->player->getYCoordinate()].addEntityInCell(this->player);
    std::cout << "GameMaster start: PlayerController contrasted successfully and playerEnt added to the field" << std::endl;

    renderer = new Renderer(*this->field, this->entities);

    renderer->draw();
    gameCycle();

    if (this->level == 2){
        //победитель по жизни абоба прайм статус!
    }
}

void GameMaster::gameCycle() {
    std::cout << "GameMaster: playerController hod!" << std::endl;
    this->playerController->doMove();
    checkEntitiesAfterMove();
    waiterToContinue();
    if (this->player->getXCoordinate() == (this->field->getHeight()-1) && this->player->getYCoordinate() == (this->field->getWidth()-1)){
        this->level++;
        return;
    }

    for(AllyController& alc : this->allyControllers){
        std::cout << "GameMaster: AllyController hod!" << " ally id: " << (&alc) << std::endl;
        alc.doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }

    for(EnemyController& enc : this->enemyControllers){
        std::cout << "GameMaster: Enemy hod!" << " enemyController id: " << (&enc) << std::endl;
        enc.doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }

    for(EnemyDefenceTowerController& dfc : this->defenceTowerControllers){
        std::cout << "GameMaster: defenceTower hod!" << " defenceTowerController id: " << (&dfc) << std::endl;
        dfc.doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }

    for(EnemySpawnerBuildingController& esc : this->enemySpawnerBuildingControllers){
        std::cout << "GameMaster: spawnerBuilding hod!" << " spawnerBuildingController id: " << (&esc) << std::endl;
        esc.doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }



    //дальнейший цикл!

}

void GameMaster::redraw() {
    this->renderer->clearDisplay();
    this->renderer->draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void GameMaster::waiterToContinue(){
    std::cout << "Введите символ для продолжения!" << std::endl;
    std::string c;
    std::cin >> c;
    std::cout << std::endl;
}

void GameMaster::checkEntitiesAfterMove() {
    bool hasDeleted = false;
    for(auto it = this->entities.begin(); it != this->entities.end(); ){
        if (!(*it)->isAlive()) {
            this->field->getFieldCells()[(*it)->getXCoordinate()][(*it)->getYCoordinate()].clearCell();
            it = this->entities.erase(it);
            hasDeleted = true;
        } else {
            ++it;
        }
    }
    if(hasDeleted)
        redraw();
}

void GameMaster::addAllyController(AllyController &controller) {
    this->allyControllers.push_back(controller);
}

void GameMaster::addEnemyController(EnemyController &controller) {
    this->enemyControllers.push_back(controller);
}
