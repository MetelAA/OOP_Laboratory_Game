//
// Created by Artem on 02.10.2025.
//

#include "EnemyManager.h"

void EnemyManager::doMove() {
    std::vector<EnemyManager::DataToMove> availablePlaces = canMoveTo(); //тут логика выбора кого стукать
    bool hasEntityToAttack = false;
    for(EnemyManager::DataToMove place : availablePlaces){
        if (this->field.getFieldCells()[place.x][place.y].hasEntityInCell())
            hasEntityToAttack = true;
    }

    EnemyManager::DataToMove moveTo;
    if (hasEntityToAttack){
        int minSteps = INT_MAX;
        for(EnemyManager::DataToMove place : availablePlaces){
            if (this->field.getFieldCells()[place.x][place.y].hasEntityInCell() && minSteps > place.stepsCount){
                minSteps = place.stepsCount;
            }
        }

        for
    }else{
        int maxSteps = 0; //ищем наиболее удалённую точку
        for(EnemyManager::DataToMove place : availablePlaces){
            if (place.stepsCount > maxSteps){
                maxSteps = place.stepsCount;
                moveTo = place;
            }
        }
    }

}

std::vector<EnemyManager::DataToMove> EnemyManager::canMoveTo() {
    std::vector<EnemyManager::DataToMove> availableCoordinates;

    //алгоритм обхода графа?


    return availableCoordinates;
}

void EnemyManager::moveTo(std::pair<int, int> coordinates) {

}
