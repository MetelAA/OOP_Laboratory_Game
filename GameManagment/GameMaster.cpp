//
// Created by Artem on 24.09.2025.
//

#include "GameMaster.h"
#include "../GameSetup/Utils/JsonParser.h"
#include "../GameRender/ConsoleRenderer.h"
#include "../GameSetup/Utils/ReadWrightJson.h"
#include "../GameSetup/GameSetup.h"
#include <chrono>
#include <memory>
#include <thread>
#include "../Logger/Logger.h"


bool GameMaster::startGame(const std::string& json) {
    Logger::tech("GameMaster startGame: started");
    std::map<std::string, std::string> gameMap = JsonParser::parseJsonWithNestedObj(json);
    this->level = std::stoi(gameMap.at("level"));
    Logger::tech("GameMaster startGame: started to deserialize field");
    std::map<std::string, std::string> fieldMap = JsonParser::parseJsonWithNestedObj(gameMap.at("field"));
    this->field = Field::deserialize(fieldMap);
    Logger::tech("GameMaster startGame: field deserialized successfully");

    Logger::tech("GameMaster startGame: creating factories");
    this->enemySpawner = std::unique_ptr<EnemySpawner>(new EnemySpawner(this->enemyModel, *this->field, *this));
    this->allySpawner = std::unique_ptr<AllySpawner>(new AllySpawner(this->allyModel, *this->field, *this));
    this->spellFactory = std::unique_ptr<SpellFactory>(new SpellFactory(*allySpawner.get()));
    Logger::tech("GameMaster startGame: factories created");
    Logger::tech("GameMaster startGame:  started to deserialize player");
    std::map<std::string, std::string> playerMap = JsonParser::parseJsonWithNestedObj(gameMap.at("player"));
    this->player = std::shared_ptr<Player>(Player::deserialize(playerMap, *spellFactory.get()));
    this->playerView = std::make_shared<PlayerView>(*player);
    Logger::tech("GameMaster startGame: player deserialized successfully");


    Logger::tech("GameMaster startGame: detecting Entities in field to contrast their controllers and managers");
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
                        EnemyController* controller = new EnemyController(*this->field, enemyManager);
                        this->enemyControllers.push_back(std::shared_ptr<EnemyController>(controller));
                    }
                        break;
                    case EntityType::EnemySpawnerBuildingEnt:{
                        std::shared_ptr<EnemySpawnerBuilding> building = std::dynamic_pointer_cast<EnemySpawnerBuilding>(entity);
                        EnemySpawnerBuildingManager manager(*this->field, building, *this->enemySpawner.get());
                        EnemySpawnerBuildingController* controller = new EnemySpawnerBuildingController(manager, *this->field);
                        this->enemySpawnerBuildingControllers.push_back(std::shared_ptr<EnemySpawnerBuildingController>(controller));
                    }
                        break;
                    case EntityType::Ally:{
                        std::shared_ptr<CompControlledCreature> ally = std::dynamic_pointer_cast<CompControlledCreature>(entity);
                        CompControlledCreatureManager allyManager(*this->field, ally);
                        AllyController* controller = new AllyController(*this->field, allyManager);
                        this->allyControllers.push_back(std::shared_ptr<AllyController>(controller));
                    }
                        break;
                    case EntityType::EnemyDefenceTower:{
                        std::shared_ptr<EnemyDefenceTower> tower = std::dynamic_pointer_cast<EnemyDefenceTower>(entity);
                        EnemyDefenceTowerManager manager(*this->field, tower);
                        EnemyDefenceTowerController* controller = new  EnemyDefenceTowerController(*this->field, manager);
                        this->defenceTowerControllers.push_back(std::shared_ptr<EnemyDefenceTowerController>(controller));
                    }
                        break;
                }
            }
        }
    }
    Logger::tech("GameMaster startGame: contrasted successfully");

    {
        Logger::tech("GameMaster startGame: contrast PlayerController");
        PlayerManager manager(*this->field, player);
        this->playerController = std::make_shared<PlayerController>(manager, *this->field, *playerView);

        //Заменить на чтение с файла!!!

//        InputKeysModel keysModel('c', 'y', 'n', 'a', 's', 'k', 'u');

//        ReadWrightJson::write(keysModel.serialize(), "../keysModel.txt");
        std::map<std::string, std::string> inputKeysJson = JsonParser::parseJsonWithNestedObj(ReadWrightJson::read("../keysModel.txt"));
        InputKeysModel keysModel = *InputKeysModel::deserialize(inputKeysJson);
        //--------------------------------


        this->gamerInputSpotter = std::make_unique<GamerInputSpotter>(*this->playerView, this->playerController, keysModel);
        player->getSpellHand().addSpell(this->spellFactory->createSpell(SpellType::DirectDamageSpell));
    }
    this->field->getFieldCells()[this->player->getXCoordinate()][this->player->getYCoordinate()].addEntityInCell(this->player);
    Logger::tech("GameMaster startGame: PlayerController contrasted successfully and playerEnt added to the field");

    renderer = new ConsoleRenderer(*this->field, this->entities, *playerView);

    renderer->prepareConsole();
    if (this->level == 1){
        gamerInputSpotter->upgradePlayer(*this);
    }
    renderer->draw();
    gameCycle();

    if (this->isSaved){
        return false;
    }
    if(!this->player->isAlive()){
        return false;
    }
    if (this->level == 2){
        std::cout << "Вы прошли игру!" << std::endl;
    }
    return true;
}

void GameMaster::gameCycle() {
    Logger::tech("GameMaster: playerController hod!");
    gamerInputSpotter->playerMove(*this);
    checkEntitiesAfterMove();
    gamerInputSpotter->waitingForContinueCommand(*this);
    if (this->player->getXCoordinate() == (this->field->getHeight()-1) && this->player->getYCoordinate() == (this->field->getWidth()-1)){
        std::cout << "Уровень: " << this->level << " пройден!" << std::endl;
        this->level++;
        return;
    }

    if (this->isSaved)
        return;

    for(std::shared_ptr<AllyController> alc : this->allyControllers){
        std::stringstream ss;
        ss << "GameMaster: AllyController hod!" << " ally id: " << (&alc);
        Logger::tech(ss.str());
        alc->doMove(*this);
        checkEntitiesAfterMove();
        gamerInputSpotter->waitingForContinueCommand(*this);
    }

    for(std::shared_ptr<EnemyController> enc : this->enemyControllers){
        std::stringstream ss;
        ss << "GameMaster: Enemy hod!" << " enemyController id: " << (&enc);
        Logger::tech(ss.str());
        enc->doMove(*this);
        checkEntitiesAfterMove();
        gamerInputSpotter->waitingForContinueCommand(*this);
    }

    for(std::shared_ptr<EnemyDefenceTowerController> dfc : this->defenceTowerControllers){
        std::stringstream ss;
        ss << "GameMaster: defenceTower hod!" << " defenceTowerController id: " << (&dfc);
        Logger::tech(ss.str());
        dfc->doMove(*this);
        checkEntitiesAfterMove();
        gamerInputSpotter->waitingForContinueCommand(*this);
    }

    for(std::shared_ptr<EnemySpawnerBuildingController> esc : this->enemySpawnerBuildingControllers){
        std::stringstream ss;
        ss << "GameMaster: spawnerBuilding hod!" << " spawnerBuildingController id: " << (&esc);
        Logger::tech(ss.str());
        esc->doMove(*this);
        checkEntitiesAfterMove();
        gamerInputSpotter->waitingForContinueCommand(*this);
    }


    if (!this->player->isAlive()){
        std::cout << "Вы погибли, игра окончена" << std::endl;
        return;
    }

    gameCycle();
}

void GameMaster::redraw() {
    this->renderer->clearDisplay();
    this->renderer->draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
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

    for(auto it = this->enemyControllers.begin(); it != this->enemyControllers.end(); ){
        if (!(*it)->isAlive()) {
            it = this->enemyControllers.erase(it);
        } else {
            ++it;
        }
    }
    for(auto it = this->allyControllers.begin(); it != this->allyControllers.end(); ){
        if (!(*it)->isAlive()) {
            it = this->allyControllers.erase(it);
        } else {
            ++it;
        }
    }
    for(auto it = this->enemySpawnerBuildingControllers.begin(); it != this->enemySpawnerBuildingControllers.end(); ){
        if (!(*it)->isAlive()) {
            it = this->enemySpawnerBuildingControllers.erase(it);
        } else {
            ++it;
        }
    }
    for(auto it = this->defenceTowerControllers.begin(); it != this->defenceTowerControllers.end(); ){
        if (!(*it)->isAlive()) {
            it = this->defenceTowerControllers.erase(it);
        } else {
            ++it;
        }
    }

    if(hasDeleted)
        redraw();
}

void GameMaster::addAllyController(AllyController *controller, std::shared_ptr<Entity> ent) {
    this->allyControllers.push_back(std::shared_ptr<AllyController>(controller));
    this->entities.push_back(ent);
}

void GameMaster::addEnemyController(EnemyController *controller, std::shared_ptr<Entity> entity) {
    this->enemyControllers.push_back(std::shared_ptr<EnemyController>(controller));
    this->entities.push_back(entity);
}

void GameMaster::saveGame() {
    std::cout << "Сохраняем игру!" << std::endl;
    this->isSaved = true;
    std::string res;
    res+="{";
    res+="level:" + std::to_string(this->level) + ",";
    res+="field:" + this->field->serialize() + ",";
    res+="player:" + this->player->serialize() +"}";

    try{
        ReadWrightJson::write(res, "../saveGame.txt");
        std::cout << "Игра успешно сохранена" << std::endl;
    }catch (const UnexpectedBehaviorException& e){
        std::cout << "Error when writing saveGame" << std::endl;
    }
}
