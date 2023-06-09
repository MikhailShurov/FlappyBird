//
// Created by mikhail on 10/05/23.
//

#ifndef FLAPPYBIRD_SCENE_H
#define FLAPPYBIRD_SCENE_H

#include "../Bird/Bird.h"
#include "../Pillar/Pillar.h"
#include <QGraphicsScene>
#include <QTimer>

class Scene: public  QGraphicsScene{
public:
    explicit Scene(QObject *parent = nullptr);
    void startGame();
    void restartGame();
    void stopGame();
    void incrementScore();

public slots:
    void printDataToConsole();

private:
    Bird* bird_;
    Pillar* pillarGroup_;
    enum class gameStatus {
        GameOn,
        GameOff,
        GameRestart
    };


    gameStatus gameStatus_;
    QGraphicsPixmapItem* background_;
    QTimer* timer_;
    QTimer* eachFrame_;
    int score_;
    Pillar* getClosestPillar();
    const int width_ = 1920;
    const int height_ = 1080;
protected:
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void spawnPillars();
};


#endif //FLAPPYBIRD_SCENE_H
