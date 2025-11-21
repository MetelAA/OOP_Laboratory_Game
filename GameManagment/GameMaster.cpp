//
// Created by Artem on 24.09.2025.
//

#include "GameMaster.h"
#include "../GameSetup/Utils/JsonParser.h"
#include "../GameRender/Renderer.h"
#include "../GameSetup/Utils/ReadRightJson.h"
#include "../GameSetup/GameSetup.h"
#include <chrono>
#include <thread>

bool GameMaster::startGame(const std::string& json) {
    std::cout << "GameMaster startGame: started" << std::endl;
    std::map<std::string, std::string> gameMap = JsonParser::parseJsonWithNestedObj(json);
    this->level = std::stoi(gameMap.at("level"));
    std::cout << "GameMaster startGame: started to deserialize field" << std::endl;
    std::map<std::string, std::string> fieldMap = JsonParser::parseJsonWithNestedObj(gameMap.at("field"));
    this->field = Field::deserialize(fieldMap);
    std::cout << "GameMaster startGame: field deserialized successfully" << std::endl;

    std::cout << "GameMaster startGame: creating factories" << std::endl;
    this->enemySpawner = std::unique_ptr<EnemySpawner>(new EnemySpawner(this->enemyModel, *this->field, *this));
    this->allySpawner = std::unique_ptr<AllySpawner>(new AllySpawner(this->allyModel, *this->field, *this));
    this->spellFactory = std::unique_ptr<SpellFactory>(new SpellFactory(*allySpawner.get()));
    std::cout << "GameMaster startGame: factories created" << std::endl;
    std::cout << "GameMaster startGame:  started to deserialize player" << std::endl;
    std::map<std::string, std::string> playerMap = JsonParser::parseJsonWithNestedObj(gameMap.at("player"));
    this->player = std::shared_ptr<Player>(Player::deserialize(playerMap, *spellFactory.get()));
    std::cout << "GameMaster startGame: player deserialized successfully" << std::endl;

    std::cout << "GameMaster startGame: detecting Entities in field to contrast their controllers and managers" << std::endl;
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
    std::cout << "GameMaster startGame: contrasted successfully" << std::endl;

    {
        std::cout << "GameMaster startGame: contrast PlayerController" << std::endl;
        PlayerManager manager(*this->field, player);
        PlayerController* controller = new PlayerController(*this->field, manager);
        this->playerController = std::unique_ptr<PlayerController>(controller);

        player->getSpellHand().addSpell(this->spellFactory->createSpell(SpellType::DirectDamageSpell));
    }
    this->field->getFieldCells()[this->player->getXCoordinate()][this->player->getYCoordinate()].addEntityInCell(this->player);
    std::cout << "GameMaster startGame: PlayerController contrasted successfully and playerEnt added to the field" << std::endl;

    renderer = new Renderer(*this->field, this->entities, this->player);

    renderer->prepareConsole();
    if (this->level == 1){
        upgradeEntity();
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
    std::cout << "GameMaster: playerController hod!" << std::endl;
    this->playerController->doMove(*this);
    checkEntitiesAfterMove();
    waiterToContinue();
    if (this->player->getXCoordinate() == (this->field->getHeight()-1) && this->player->getYCoordinate() == (this->field->getWidth()-1)){
        std::cout << "Уровень: " << this->level << " пройден!" << std::endl;
        this->level++;
        return;
    }

    if (this->isSaved)
        return;

    for(std::shared_ptr<AllyController> alc : this->allyControllers){
        std::cout << "GameMaster: AllyController hod!" << " ally id: " << (&alc) << std::endl;
        alc->doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }

    for(std::shared_ptr<EnemyController> enc : this->enemyControllers){
        std::cout << "GameMaster: Enemy hod!" << " enemyController id: " << (&enc) << std::endl;
        enc->doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }

    for(std::shared_ptr<EnemyDefenceTowerController> dfc : this->defenceTowerControllers){
        std::cout << "GameMaster: defenceTower hod!" << " defenceTowerController id: " << (&dfc) << std::endl;
        dfc->doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
    }

    for(std::shared_ptr<EnemySpawnerBuildingController> esc : this->enemySpawnerBuildingControllers){
        std::cout << "GameMaster: spawnerBuilding hod!" << " spawnerBuildingController id: " << (&esc) << std::endl;
        esc->doMove(*this);
        checkEntitiesAfterMove();
        waiterToContinue();
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

void GameMaster::waiterToContinue(){
    std::cout << "Введите символ для продолжения!" << std::endl;
    std::string c = Constants::getInput<std::string>();
    std::cout << "────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────" << std::endl;
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

void GameMaster::addAllyController(AllyController *controller) {
    this->allyControllers.push_back(std::shared_ptr<AllyController>(controller));
}

void GameMaster::addEnemyController(EnemyController *controller) {
    this->enemyControllers.push_back(std::shared_ptr<EnemyController>(controller));
}

void GameMaster::save() {
    std::cout << "Сохраняем игру!" << std::endl;
    this->isSaved = true;
    std::string res;
    res+="{";
    res+="level:" + std::to_string(this->level) + ",";
    res+="field:" + this->field->serialize() + ",";
    res+="player:" + this->player->serialize() +"}";

    try{
        ReadRightJson::write(res, "../save.txt");
        std::cout << "Игра успешно сохранена" << std::endl;
    }catch (const UnexpectedBehaviorException& e){
        std::cout << "Error when writing save" << std::endl;
    }
}

void GameMaster::upgradeEntity() {
    bool flag = true;
    while(flag){
        std::cout << "Что вы хотите улучшить (требуется 1 очко), у вас: " << this->player->getScore() << ":\n1.Урон\n2.Дальность хода\n3.Здоровье\n(введите цифру от 1 до 3х или 0 чтобы отказаться от выбора)" << std::endl;
        int num = Constants::getInput<int>();
        switch(num){
            case 0:
                flag = false;
            break;
            case 1:
                this->player->setLongRangeAttack(LongRangeAttack(this->player->getLongRangeAttack().getDamage() + 1, this->player->getLongRangeAttack().getRange()+1));
                this->player->setCloseRangeAttack(CloseRangeAttack(this->player->getCloseRangeAttack().getDamage() + 2));
                this->player->setScore(this->player->getScore()-1);
                flag = false;
            break;
            case 2:
                this->player->setStepRange(this->player->getStepRange()+1);
                this->player->setScore(this->player->getScore()-1);
                flag = false;
            break;
            case 3:
                this->player->changeHealthPoints(2);
                this->player->setScore(this->player->getScore()-1);
                flag = false;
            break;
            default:
                std::cout << "Введённая цифра не в диапазоне от одного до трёх!" << std::endl;
                continue;
        }
    }
}
