//
// Created by mikhail on 14/05/23.
//

#ifndef FLAPPYBIRD_SCENEAI_H
#define FLAPPYBIRD_SCENEAI_H


#include "../Bird/BirdAI.h"
#include "../Pillar/Pillar.h"
#include <QGraphicsScene>
#include <QTimer>

class SceneAI: public  QGraphicsScene{
public:
    explicit SceneAI(QObject *parent = nullptr);
    void createNewGeneration();
    void incrementScore();
signals:
    void recreateGeneration();
private:
    const int EPOCH = 50;
    QList<BirdAI*> birds_;
    Pillar* pillarGroup_;
    QTimer* timer_;
    int score_;
    QList<QPair<BirdAI*, int>> lastEpochResults_;
protected:
    void spawnPillars();
public slots:
    void printBirdScoreToConsole(BirdAI*, int);
};


#endif //FLAPPYBIRD_SCENEAI_H
