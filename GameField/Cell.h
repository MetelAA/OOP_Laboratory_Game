//
// Created by Artem on 24.09.2025.
//

#ifndef LABA1_CELL_H
#define LABA1_CELL_H

#include "../Entities/Entity.h"
#include "CellType.h"
#include "../Exceptions/Notifications/NoEntityInCellNotification.h"
#include "CellEvents/CellEvent.h"
#include "CellEvents/SlowingCellEvent.h"
#include <memory>
#include "CellEvents/TrapCellEvent.h"
#include "../Exceptions/UnexpectedBehaviorException.h"



class Cell {
public:
    Cell(CellType type) : type(type){
        entityInCell = nullptr;
        event = nullptr;
    }

    Cell(CellType type, std::unique_ptr<Entity> entityInCell, std::unique_ptr<CellEvent> event) : type(type),
                                                                                         entityInCell(std::move(entityInCell)),
                                                                                         event(std::move(event)) {}


    Cell(Cell&& other) noexcept : type(other.type){
        this->entityInCell = other.entityInCell;
        other.entityInCell = nullptr;
        this->event = std::move(other.event);
    }

    Cell& operator=(Cell&& other) noexcept {
        if (this != &other){
            this->type = other.type;
            this->entityInCell = other.entityInCell;
            other.entityInCell = nullptr;
            this->event = std::move(other.event);
        }
        return *this;
    }

    Cell(const Cell& other): type(other.type){
        if (other.hasCellEvent()){
            this->event = std::move(other.event->clone());
        }else{
            this->event = nullptr;
        }
        if (other.hasEntityInCell()){
            this->entityInCell = std::move(other.entityInCell->clone());
        }else{
            this->entityInCell = nullptr;
        }
    }

    Cell& operator=(const Cell& other){
        if (this != &other){
            this->type = other.type;
            if (other.hasCellEvent()){
                this->event = std::move(other.event->clone());
            }else{
                this->event = nullptr;
            }
            if (other.hasEntityInCell()){
                this->entityInCell = std::move(other.entityInCell->clone());
            }else{
                this->entityInCell = nullptr;
            }
        }
        return *this;
    }




    virtual CellType getCellType() const noexcept final;

    virtual void addEntityInCell(std::shared_ptr<Entity> entity) noexcept final;

    virtual void clearCell() noexcept final;

    virtual bool hasEntityInCell() const noexcept final;

    virtual void damageEntityInCell(int damage) const final;

    virtual Entity& getEntityInCell() noexcept final;
    virtual const Entity& getEntityInCell() const noexcept final;

    virtual EntityType getEntityInCellType() const final;

    virtual void setCellEvent(std::unique_ptr<CellEvent> cellEvent) const final;

    virtual bool hasCellEvent() const final;

    virtual void impactOnCreatureByCellEvent() const final; //к этому моменту creature уже должно быть перемещено в эту клетку

protected:
    CellType type;
    std::shared_ptr<Entity>  entityInCell;
    mutable std::unique_ptr<CellEvent> event;
};


#endif //LABA1_CELL_H
