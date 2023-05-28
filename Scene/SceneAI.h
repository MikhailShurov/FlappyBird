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
#include <QResizeEvent>
#include <QLabel>

class SceneAI: public  QGraphicsScene{
public:
    explicit SceneAI(QObject *parent = nullptr, bool = false);
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
    QGraphicsPixmapItem* background_;
    QLabel* generation_;
    QLabel* currentScore_;
    QLabel* alive_;
    int gen_ = 0;
    const int width_ = 1920;
    const int height_ = 1080;
    bool needMutation_;
    bool takeFromFile_;
    std::vector<double> readFromFile();
protected:
    void spawnPillars();
public slots:
    void checkBirdsJump();
    void removeFirstPillar();
    void printBirdScoreToConsole(BirdAI*);
};


#endif //FLAPPYBIRD_SCENEAI_H
