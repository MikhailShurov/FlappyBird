//
// Created by mikhail on 14/05/23.
//

#include "AI.h"
#include <cmath>
#include <random>

AI::AI(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < 3; ++ i) {
        weights_.append(dis(gen));
    }
}

AI::AI(const QList<double> &newWeights) {
    weights_ = newWeights;
}

QList<double> AI::getWeights() const {
    return weights_;
}

bool AI::activate(double &x) {
    double normalized = 1 / (1 + exp(-x));
    if (normalized >= 0.5) {
        return true;
    } else {
        return false;
    }
}

bool AI::needJump(double &distanceX, double &distanceTopY, double &distanceBottomY) {
    double result = distanceX*weights_[0] + distanceTopY*weights_[1] + distanceBottomY*weights_[2];
    return activate(result);
}