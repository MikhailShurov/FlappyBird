//
// Created by mikhail on 14/05/23.
//

#ifndef FLAPPYBIRD_AI_H
#define FLAPPYBIRD_AI_H

#include <QList>

class AI {
public:
    AI();
    AI(const QList<double>&);
    bool needJump(double&, double&, double&);
    QList<double> getWeights() const;
private:
    QList<double> weights_;
    bool activate(double &);
};


#endif //FLAPPYBIRD_AI_H
