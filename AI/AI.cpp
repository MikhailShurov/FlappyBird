//
// Created by mikhail on 14/05/23.
//

#include "AI.h"
#include <QDebug>
#include <random>

AI::AI() : efficenty_(23){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < 3; ++ i) {
        weights_[i] = dis(gen);
    }
}

int AI::getEfficenty() const{
    return efficenty_;
}

void AI::setEfficenty(const int& newEfficenty) {
    efficenty_ = newEfficenty;
}