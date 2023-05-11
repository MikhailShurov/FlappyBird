//
// Created by mikhail on 11/05/23.
//

#include "Pillar.h"
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>


Pillar::Pillar() {
    topPillar = new QGraphicsPixmapItem(QPixmap("./img/topPillar.png"));
    bottomPillar_ = new QGraphicsPixmapItem(QPixmap("./img/bottomPillar.png"));

    topPillar->setPos(
            QPointF(0, 0) - QPointF(topPillar->boundingRect().width() / 2, topPillar->boundingRect().height() + 60));
    bottomPillar_->setPos(QPointF(0, 0) - QPointF(bottomPillar_->boundingRect().width() / 2, -60));

    addToGroup(topPillar);
    addToGroup(bottomPillar_);

    xAnimation_ = new QPropertyAnimation(this, "x", this);

    y_ = QRandomGenerator::global()->bounded(75);
    int startX = QRandomGenerator::global()->bounded(100);
    setPos(QPointF(0, 0) + QPointF(260 + startX, y_));

    xAnimation_->setStartValue(260 + startX);
    xAnimation_->setEndValue(-500);
    xAnimation_->setEasingCurve(QEasingCurve::Linear);
    xAnimation_->setDuration(2500);
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
    x_ = newX;
}

Pillar::~Pillar() noexcept {
    qDebug() << "You need to write destructor for Pillar";
}