#ifndef AI_H
#define AI_H

#include <vector>

class AI {
public:
    AI();
    void activate(double input1, double input2, double input3);
    std::vector<double> getWeights();
    void setWeights(std::vector<double> weights);
    bool needJump(double input1, double input2, double input3);
private:
    std::vector<double> weights;
};

#endif