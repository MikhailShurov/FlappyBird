#include "AI.h"
#include <fstream>
#include <random>
#include <cmath>
#include <QDebug>

AI::AI() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-30.0, 30.0);
    weights = {dis(gen), dis(gen), dis(gen)};
}

void AI::activate(double input1, double input2, double input3) {
    double sum = weights[0] * input1 + weights[1] * input2 + weights[2] * input3;
    double output = tanh(sum);
}

std::vector<double> AI::getWeights() {
    return weights;
}

void AI::setWeights(std::vector<double> newWeights) {
    this->weights = newWeights;
}



bool AI::needJump(double input1, double input2, double input3) {
    double sum = weights[0] * input1 + weights[1] * input2 + weights[2] * input3;
    double output = tanh(sum);
    return output > 0;
}