//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_CELL_H
#define LABA1_CELL_H

#include "../Entities/Entity.h"
#include "CellType.h"
#include "../Exceptions/Notifications/NoEntityInCellNotification.h"
#include "CellEvents/CellEvent.h"
//#include "../Entities/Creatures/Player.h"
//#include "../Entities/Creatures/CompControlledCreature.h"
//#include "../Entities/Buildings/EnemySpawnerBuilding.h"

class Cell {
public:
    Cell(CellType type) : type(type){
        entityInCell = nullptr;
        event = nullptr;
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
//                    const CompControlledCreature *otherEnemy = dynamic_cast<const CompControlledCreature*>(&other.getEntityInCell());
//                    CompControlledCreature* enemyCopy = new CompControlledCreature(*otherEnemy);
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

    virtual Entity& getEntityInCell() noexcept final;

    virtual EntityType getEntityInCellType() const final;

    virtual void setCellEvent(CellEvent)

protected:
    CellType type;
    Entity *entityInCell;
    CellEvent* event;
};


#endif //LABA1_CELL_H
