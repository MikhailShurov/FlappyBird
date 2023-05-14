//
// Created by mikhail on 14/05/23.
//

#ifndef FLAPPYBIRD_AI_H
#define FLAPPYBIRD_AI_H


class AI {
public:
    AI();
//    bool needJump();
    int getEfficenty() const;
    void setEfficenty(const int&);
private:
    double * weights_ = new double[3];
    void activate();
    int efficenty_;
};


#endif //FLAPPYBIRD_AI_H
