//
// Created by Artem on 24.09.2025.
//

#include "Cell.h"

CellType Cell::getCellType() const noexcept{
    return type;
}

bool Cell::hasEntityInCell() const noexcept{
    return this->entityInCell != nullptr;
}

void Cell::addEntityInCell(Entity *entity) noexcept {
    this->entityInCell = entity;
}

void Cell::clearCell() noexcept {
    this->entityInCell = nullptr;
}

void Cell::damageEntityInCell(int damage) {
    if (this->hasEntityInCell()){
        this->entityInCell->changeHealthPoints((-1) * damage);
        return;
    }
    throw NoEntityInCellNotification("В клетке нету сущности");
}

EntityType Cell::getEntityInCellType() const {
    if (this->hasEntityInCell()){
        return this->entityInCell->getType();
    }
    throw NoEntityInCellNotification("В клетке нету сущности");
}

Entity & Cell::getEntityInCell() const noexcept {
    return *this->entityInCell;
}

void Cell::setCellEvent(std::unique_ptr<CellEvent> cellEvent)  {
    this->event = std::move(cellEvent);
}

bool Cell::hasCellEvent() const {
    return this->event.get() != nullptr;
}

void Cell::impactOnCreatureByCellEvent() const{
    if (!this->hasEntityInCell()){
        throw UnexpectedBehaviorException("На момент вызова impactOnCreatureByCellEvent сущность уже должна быть перемещена в клетку");
    }
    if (this->getEntityInCellType() != EntityType::EnemyEnt || this->getEntityInCellType() != EntityType::PlayerEnt || this->getEntityInCellType() != EntityType::Ally){
        throw UnexpectedBehaviorException("К клетке должен быть наследник класса Creature");
    }
    Creature* creature = dynamic_cast<Creature*>(this->entityInCell);
    this->event.get()->impactOnCreatureInCell(*creature);//Вот он собсна ООП во плоти, стока по смыслу эквивалент нижнему(уже нет, удалил)! Это писал я, а не нейронка блеат!!!!! Свитч писать даже бы не пришлось если бы не удаление ловушек после получения урона
    switch (this->event.get()->getType()) {
        case CellEventType::SlowingEvent:
            break;
        case CellEventType::TrapEvent:
            this->event.reset(); //удаление ловушки после применения
            break;
    }
}