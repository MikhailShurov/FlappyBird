//
// Created by mikhail on 11/05/23.
//

#include "Pillar.h"
#include "../Bird/Bird.h"
#include "../Bird/BirdAI.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAI.h"
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>


Pillar::Pillar() : birdPass_(false) {
    topPillar = new QGraphicsPixmapItem(QPixmap("./img/topPillar.png"));
    bottomPillar_ = new QGraphicsPixmapItem(QPixmap("./img/bottomPillar.png"));

    topPillar->setPos(
            QPointF(0, 0) - QPointF(topPillar->boundingRect().width() / 2, topPillar->boundingRect().height() + 60));
    bottomPillar_->setPos(QPointF(0, 0) - QPointF(bottomPillar_->boundingRect().width() / 2, -60));

    addToGroup(topPillar);
    addToGroup(bottomPillar_);

    xAnimation_ = new QPropertyAnimation(this, "x", this);

    y_ = QRandomGenerator::global()->bounded(-100, 100);
    int startX = QRandomGenerator::global()->bounded(100);
    setPos(QPointF(0, 0) + QPointF(260 + startX, y_));

    xAnimation_->setStartValue(260 + startX);
    xAnimation_->setEndValue(-600);
    xAnimation_->setEasingCurve(QEasingCurve::Linear);
    xAnimation_->setDuration(4500);
    xAnimation_->start();

    connect(xAnimation_, &QPropertyAnimation::finished, [=]() {
        scene()->removeItem(this);
        delete this;
    });
}

qreal Pillar::x() const {
    return x_;
}

void Pillar::setX(const qreal &newX) {
    moveBy(newX - x_, 0);
    checkIfBirdPass();
    collideWithBird();
    x_ = newX;
}

Pillar::~Pillar() noexcept {
    delete xAnimation_;
    delete topPillar;
    delete bottomPillar_;
}

void Pillar::collideWithBird() {
    QList<QGraphicsItem*> currentCollides = topPillar->collidingItems();
    currentCollides.append(bottomPillar_->collidingItems());
    for(auto* item : currentCollides) {
        if (dynamic_cast<Bird*>(item) != nullptr) {
            emit(stopGame());
        } else if (dynamic_cast<BirdAI*>(item) != nullptr) {
            BirdAI* bird = dynamic_cast<BirdAI*>(item);
            emit(destroyBird(bird));
        }
    }
}

void Pillar::stopPillar() {
    xAnimation_->stop();
}

void Pillar::checkIfBirdPass() {
    if (this->mapToScene(QPointF(0, 0)).x() < 0 && !birdPass_) {
        birdPass_ = true;
        QGraphicsScene* scene_ = scene();

        if (dynamic_cast<Scene*>(scene_) == nullptr) {
            SceneAI* scene1 = dynamic_cast<SceneAI*>(scene_);
            scene1->incrementScore();
        } else {
            Scene* scene1 = dynamic_cast<Scene*>(scene_);
            scene1->incrementScore();
        }
    }
}

int Pillar::getTopOfInterval() const {
    return y_ + 60;
}

int Pillar::getBottomOfInterval() const {
    return y_ - 60;
}