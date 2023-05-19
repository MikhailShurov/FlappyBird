//
// Created by mikhail on 14/05/23.
//

#include "AI.h"
#include <cmath>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

AI::AI() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // generate 1-2 weights
    for (int i = 0; i < 4; ++i) {
        std::vector<double> neuronWeights;
        for (int j = 0; j < 3; ++j) {
            double weight = dis(gen);
            std::cout << weight << " ";
            neuronWeights.push_back(weight);
        }
        std::cout << "\n";
        weights_1_2.push_back(neuronWeights);
    }

    std::cout << "\n\n";

    // generate 2-3 weights
    for (int i = 0; i < 3; ++i) {
        std::vector<double> neuronWeights;
        for (int j = 0; j < 1; ++j) {
            double weight = dis(gen);
            std::cout << weight << " ";
            neuronWeights.push_back(weight);
        }
        std::cout << "\n";
        weights_2_3.push_back(neuronWeights);
    }

    std::cout << "\n\n";
}

double AI::activate(double &x) {
    double normalized = 1 / (1 + exp(-x));
    return normalized;
}

void AI::readfromFile() {
    std::ifstream fin("output.txt", std::ios::in);
    std::string str;
    while (std::getline(fin, str)) {
        std::vector<double> line;
        std::istringstream sstream(str);
        double x, top, bottom, ground;
        int answer;
        sstream >> x >> top >> bottom >> ground >> answer;
        line.push_back(x);
        line.push_back(top);
        line.push_back(bottom);
        line.push_back(ground);
        data.push_back(std::make_pair(line, answer));
    }
    std::cout << data.size() << " -- data size\n";
}

void AI::teachAI() {
    std::cout << data.size() << " -- data size\n";
    for (int e = 0; e < EPOCH; ++ e) {
        for (long long i = 0; i < data.size(); ++i) {
            hiddenNeuronValues.clear();
            double firstVal = 0, secondVal = 0, thirdVal = 0, answer = 0;
            for (int j = 0; j < weights_1_2.size(); ++j) {
                firstVal += weights_1_2[j][0] * data[i].first[j];
                secondVal += weights_1_2[j][1] * data[i].first[j];
                thirdVal += weights_1_2[j][2] * data[i].first[j];
            }

            hiddenNeuronValues.push_back(firstVal);
            hiddenNeuronValues.push_back(secondVal);
            hiddenNeuronValues.push_back(thirdVal);

            for (int j = 0; j < weights_2_3.size(); ++j) {
                for (int k = 0; k < weights_2_3[j].size(); ++k) {
                    answer += weights_2_3[j][k] * activate(firstVal);
                    answer += weights_2_3[j][k] * activate(secondVal);
                    answer += weights_2_3[j][k] * activate(thirdVal);
                }
            }

            answer = activate(answer);

            // Here we have 3 hidden neuron values and result
            // So we can calculate error

            double error = data[i].second - answer;                 // error
            double localGrad = error * (answer * (1 - answer));     // local gradient

            // Now we can fix all weights

            // Fixing last weights
            for (int j = 0; j < weights_2_3.size(); ++i) {
                for (int k = 0; k < weights_2_3[j].size(); ++k) {
                    weights_2_3[j][k] = weights_2_3[j][k] - LR * localGrad * hiddenNeuronValues[j];
                }
            }

            // calculate next-level local gradients
            double localGrad1, localGrad2, localGrad3;
            localGrad1 = localGrad * weights_2_3[0][0] * hiddenNeuronValues[0] * (1 - hiddenNeuronValues[0]);
            localGrad2 = localGrad * weights_2_3[1][0] * hiddenNeuronValues[1] * (1 - hiddenNeuronValues[1]);
            localGrad3 = localGrad * weights_2_3[2][0] * hiddenNeuronValues[2] * (1 - hiddenNeuronValues[2]);

            std::vector<double> localgrads;
            localgrads.push_back(localGrad1);
            localgrads.push_back(localGrad2);
            localgrads.push_back(localGrad3);

            for (int j = 0; j < weights_1_2.size(); ++j) {
                for (int k = 0; k < weights_1_2[j].size(); ++k) {
                    weights_1_2[j][k] = weights_1_2[j][k] - LR * data[i].first[j] * localgrads[j];
                }
            }
        }
    }

    // 3 for first, 3 for second etc
    for (int i = 0; i < weights_1_2.size(); ++ i) {
        for (int j = 0; j < weights_1_2[i].size(); ++ j) {
            std::cout << weights_1_2[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n\n";

    std::cout << weights_2_3.size() << "sizee\n";
    for (int i = 0; i < weights_2_3.size(); ++ i) {
        for (int j = 0; j < weights_2_3[i].size(); ++ j) {
            std::cout << weights_2_3[i][j] << " ";
        }
        std::cout << "\n";
    }
}