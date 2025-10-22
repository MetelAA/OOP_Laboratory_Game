//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_CELL_H
#define LABA1_CELL_H

#include "../Entities/Entity.h"
#include "CellType.h"
#include "../Exceptions/Notifications/NoEntityInCellNotification.h"
//#include "../Entities/Creatures/Player.h"
//#include "../Entities/Creatures/Enemy.h"
//#include "../Entities/Buildings/EnemySpawnerBuilding.h"

class Cell {
public:
    Cell(CellType type) : type(type){
        entityInCell = nullptr;
    }

//    Cell(const Cell& other): type(other.type){
//        if (other.hasEntityInCell()){
//            switch (other.getEntityInCell().getCellType()) {
//                case EntityType::PlayerEnt:{
//                    const Player *otherPlayer = dynamic_cast<const Player*>(&other.getEntityInCell());
//                    Player* playerCopy = new Player(*otherPlayer);
//                    this->addEntityInCell(playerCopy);
//                }
//                    break;
//                case EntityType::EnemyEnt:{
//                    const Enemy *otherEnemy = dynamic_cast<const Enemy*>(&other.getEntityInCell());
//                    Enemy* enemyCopy = new Enemy(*otherEnemy);
//                    this->addEntityInCell(enemyCopy);
//                }
//                    break;
//                case EntityType::EnemyBuildingEnt:{
//                    const EnemySpawnerBuilding *otherEnemySpawnerBuilding = dynamic_cast<const EnemySpawnerBuilding*>(&other.getEntityInCell());
//                    EnemySpawnerBuilding* buildingCopy = new EnemySpawnerBuilding(*otherEnemySpawnerBuilding);
//                    this->addEntityInCell(buildingCopy);
//                }
//                    break;
//            }
//        }
//    }

    virtual CellType getCellType() const noexcept final;

    virtual void addEntityInCell(Entity *entity) noexcept final;

    virtual void clearCell() noexcept final;

    virtual bool hasEntityInCell() const noexcept final;

    virtual void damageEntityInCell(int damage) final;

    virtual Entity& getEntityInCell() const noexcept final;

    virtual EntityType getEntityInCellType() const final;

protected:
    CellType type;
    Entity *entityInCell;
};


#endif //LABA1_CELL_H
