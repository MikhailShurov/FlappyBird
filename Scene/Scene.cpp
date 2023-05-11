//
// Created by mikhail on 10/05/23.
//

#include "Scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) {
    setSceneRect(-144, -256, 288, 512);

    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap("./img/background_night.png"));
    background->setPos(
            QPointF(0, 0) - QPointF(background->boundingRect().width() / 2, background->boundingRect().height() / 2));
    addItem(background);

    bird_ = new Bird();
    addItem(bird_);

//    pillarGroup_ = new Pillar();
//    addItem(pillarGroup_);
    spawnPillars();
}

void Scene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        bird_->shootUp();
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        bird_->shootUp();
    }
}

void Scene::spawnPillars() {
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [=]() {
        pillarGroup_ = new Pillar();
        addItem(pillarGroup_);
    });
    timer_->start(800);
}