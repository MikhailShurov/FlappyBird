//
// Created by mikhail on 14/05/23.
//

#ifndef FLAPPYBIRD_AI_H
#define FLAPPYBIRD_AI_H

#include <vector>

class AI {
public:
    AI();
//    bool needJump();
    std::vector<double> getWeights() const;
private:
    std::vector<double> weights_;
    void activate();
};


#endif //FLAPPYBIRD_AI_H
