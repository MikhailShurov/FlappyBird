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
//    qDebug() << weights;
}

AI::AI(std::vector<double> weights) {
    this->weights = weights;
    std::ofstream outfile("weights.txt", std::ios_base::app);
    for (int i = 0; i < weights.size(); i++) {
        outfile << weights[i] << " ";
    }
    outfile << "\n";
    outfile.close();
}

void AI::activate(double input1, double input2, double input3) {
    double sum = weights[0] * input1 + weights[1] * input2 + weights[2] * input3;
    double output = tanh(sum);
}

std::vector<double> AI::getWeights() {
    return weights;
}

void AI::setWeights(std::vector<double> weights) {
    this->weights = weights;
}

void AI::mutate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    int index = std::rand() % weights.size();
    double mutationAmount = dis(gen);
    weights[index] += mutationAmount;
    // Clamp weight to [-30, 30]
    if (weights[index] < -30.0) {
        weights[index] = -30.0;
    } else if (weights[index] > 30.0) {
        weights[index] = 30.0;
    }
}

std::pair<AI, AI> AI::crossover(AI parent1, AI parent2) {
    std::vector<double> parent1Weights = parent1.getWeights();
    std::vector<double> parent2Weights = parent2.getWeights();
    int crossoverPoint = std::rand() % parent1Weights.size();
    std::vector<double> child1Weights;
    std::vector<double> child2Weights;
    for (int i = 0; i < parent1Weights.size(); i++) {
        if (i <= crossoverPoint) {
            child1Weights.push_back(parent1Weights[i]);
            child2Weights.push_back(parent2Weights[i]);
        } else {
            child1Weights.push_back(parent2Weights[i]);
            child2Weights.push_back(parent1Weights[i]);
        }
    }
    if (std::rand() % 2 == 0) {
        child1Weights = parent1.getWeights();
        child2Weights = parent2.getWeights();
    }
    if (std::rand() % 2 == 0) {
        child1Weights = parent2.getWeights();
        child2Weights = parent1.getWeights();
    }
    return std::make_pair(AI(child1Weights), AI(child2Weights));
}

bool AI::needJump(double input1, double input2, double input3) {
    double sum = weights[0] * input1 + weights[1] * input2 + weights[2] * input3;
    double output = tanh(sum);
    return output > 0.5;
}