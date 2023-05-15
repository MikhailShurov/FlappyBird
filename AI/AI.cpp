//
// Created by mikhail on 14/05/23.
//

#include "AI.h"
#include <vector>
#include <random>

AI::AI(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < 3; ++ i) {
        weights_.push_back(dis(gen));
    }
}

std::vector<double> AI::getWeights() const {
    return weights_;
}