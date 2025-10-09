//
// Created by Artem on 05.10.2025.
//

#ifndef LABA1_ENEMYMODEL_H
#define LABA1_ENEMYMODEL_H


class EnemyModel {
public:
    int healthPoint, damage, stepCount;

    EnemyModel(int healthPoint, int damage, int stepCount) : healthPoint(healthPoint), damage(damage),
                                                             stepCount(stepCount) {}

};


#endif //LABA1_ENEMYMODEL_H
