//
// Created by mikhail on 14/05/23.
//

#include "SceneAI.h"
#include "QRandomGenerator"
#include <QTimer>
#include <QDebug>


SceneAI::SceneAI(QObject *parent) : score_(0) {
    setSceneRect(-144, -256, 288, 512);

    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap("./img/background_night.png"));
    background->setPos(
            QPointF(0, 0) - QPointF(background->boundingRect().width() / 2, background->boundingRect().height() / 2));
    addItem(background);

    createNewGeneration();
}

void SceneAI::createNewGeneration() {

    int lower = -sceneRect().height() / 2.5;
    int upper = sceneRect().height() / 2.5;
    for (int i = 0; i < 10; ++ i) {
        int birdY = QRandomGenerator::global()->bounded(lower, upper);
        BirdAI* bird = new BirdAI();
        // Todo Написать функцию остановки игры, если birds_.size() == 0
        connect(bird, &BirdAI::saveEfficenty, this, &SceneAI::printBirdScoreToConsole);
        bird->setPos(QPointF(0, birdY));
        birds_.append(bird);
        addItem(bird);
    }

    spawnPillars();

    timer_->start(1500);
}

void SceneAI::spawnPillars() {
    timer_ = new QTimer(this);

    connect(timer_, &QTimer::timeout, [=]() {
        pillarGroup_ = new Pillar();
        connect(pillarGroup_, &Pillar::stopGame, [=]() {

        });

        addItem(pillarGroup_);
    });
}

void SceneAI::incrementScore() {
    ++score_;
}

void SceneAI::recreateGeneration() {
    createNewGeneration();
}

void SceneAI::printBirdScoreToConsole(BirdAI* birdAi, int score) {
    birds_.removeAll(birdAi);
    QString out = "Destroed some bird, birds_.size() = " + QString::number(birds_.size());
    qDebug() << out;
}
