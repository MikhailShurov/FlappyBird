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
    qDebug() << "new generation created";
    timer_ = new QTimer(this);

    int lower = -sceneRect().height() / 2.5;
    int upper = sceneRect().height() / 2.5;

    for (int i = 0; i < 15; ++ i) {
        int birdY = QRandomGenerator::global()->bounded(lower, upper);
        BirdAI* bird = new BirdAI();
        bird->setPos(QPointF(0, birdY));
        birds_.append(bird);
        addItem(bird);
    }

    startGame();
}

void SceneAI::spawnPillars() {
    connect(timer_, &QTimer::timeout, [=]() {
        bool deleteBird = false;
        connect(pillarGroup_, &Pillar::destroyBird, [=](BirdAI* birdAi) {
            printBirdScoreToConsole(birdAi);
        });


        if (birds_.size() == 0) {
            stopGame();
            deletePillars();
            createNewGeneration();
        }

        pillarGroup_ = new Pillar();
        addItem(pillarGroup_);
    });
}

void SceneAI::incrementScore() {
    ++score_;
}

void SceneAI::printBirdScoreToConsole(BirdAI* birdAi) {
    birdAi->fixEfficenty();
    qDebug() << "bird efficenty: " << QString::number(birdAi->getEfficenty());
    birds_.removeAll(birdAi);
    delete birdAi;
}

void SceneAI::stopGame() {
    QList<QGraphicsItem*> items = this->items();
    timer_->stop();
    for (auto* item : items) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar) {
            pillar->stopPillar();
        }
    }
}

void SceneAI::startGame() {
    timer_->start(1500);
    spawnPillars();
}

void SceneAI::deletePillars() {
    QList<QGraphicsItem*> items = this->items();
    for (auto* item : items) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar) {
            delete pillar;
        }
    }
}
