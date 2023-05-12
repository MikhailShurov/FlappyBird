//
// Created by mikhail on 10/05/23.
//

#include "Scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QDebug>

Scene::Scene(QObject *parent) {
    setSceneRect(-144, -256, 288, 512);

    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap("./img/background_night.png"));
    background->setPos(
            QPointF(0, 0) - QPointF(background->boundingRect().width() / 2, background->boundingRect().height() / 2));
    addItem(background);

    bird_ = new Bird();
    addItem(bird_);

    gameOn_ = false;

    spawnPillars();
}

void Scene::startGame() {
    bird_->startBird();
    timer_->start(1500);
}

void Scene::keyPressEvent(QKeyEvent *event) {
    if (gameOn_) {
        if (event->key() == Qt::Key_Space) {
            bird_->shootUp();
        }
    } else {
        if (event->key() != Qt::Key_unknown && event->key() != Qt::Key_Space) {
            gameOn_ = true;
            bird_->shootUp();
            startGame();
        }
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (gameOn_) {
        if(event->button() == Qt::LeftButton) {
            bird_->shootUp();
        }
    }
}

void Scene::stopGame() {
    gameOn_ = false;
    bird_->stopBird();

    QList<QGraphicsItem*> items = this->items();
    timer_->stop();
    for (auto* item : items) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar) {
            pillar->stopPillar();
        }
    }
}

void Scene::spawnPillars() {
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [=]() {
        pillarGroup_ = new Pillar();

        connect(pillarGroup_, &Pillar::stopGame, [=]() {
            stopGame();
        });
        addItem(pillarGroup_);
    });
}