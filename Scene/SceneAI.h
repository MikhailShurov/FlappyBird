//
// Created by mikhail on 14/05/23.
//

#ifndef FLAPPYBIRD_SCENEAI_H
#define FLAPPYBIRD_SCENEAI_H


#include "../Bird/BirdAI.h"
#include "../Pillar/Pillar.h"
#include <QGraphicsScene>
#include <QTimer>
#include <vector>
#include <QStack>

class SceneAI: public  QGraphicsScene{
public:
    explicit SceneAI(QObject *parent = nullptr);
    void createNewGeneration();
    void incrementScore();
    void stopGame();
    void startGame();
    void deletePillars();
private:
    const int EPOCH = 50;
    QList<BirdAI*> birds_;
    Pillar* pillarGroup_;
    QList<Pillar*> allPillars_;
    QTimer* timer_;
    QTimer* eachFrame_;
    int score_;
    QList<QPair<QList<int>, int>> lastEpochResults_;
    QStack<std::vector<double>> birdsWeights_;
    void mutate(std::vector<double>&);
    std::vector<double> crossover(const std::vector<double>&, const std::vector<double>&);
protected:
    void spawnPillars();
public slots:
    void checkBirdsJump();
    void removeFirstPillar();
    void printBirdScoreToConsole(BirdAI*);
};


#endif //FLAPPYBIRD_SCENEAI_H
