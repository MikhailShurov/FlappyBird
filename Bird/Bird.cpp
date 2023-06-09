//
// Created by mikhail on 10/05/23.
//

#include "Bird.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

Bird::Bird(const double& spawnY): y_(spawnY){
    setPixmap(QPixmap("../img/bird_up.png"));
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [=]() {
        changePixmap();
    });
    timer_->start(130);

    ground_ = 500;

    yAnimation_ = new QPropertyAnimation(this, "y", this);
    yAnimation_->setStartValue(scenePos().y());
    yAnimation_->setEndValue(ground_);
    yAnimation_->setEasingCurve(QEasingCurve::InQuad);
    yAnimation_->setDuration(1000);

    rotateAnimation_ = new QPropertyAnimation(this, "rotation", this);
}

void Bird::startBird() {
    yAnimation_->start();
    rotateTo(60, 700, QEasingCurve::Linear);
}

qreal Bird::rotation() const {
    return rotation_;
}

qreal Bird::y() const {
//    qDebug() << y_;
    return y_;
}

void Bird::setRotation(const qreal &newRotation) {
    rotation_ = newRotation;
    QPointF birdCenter = boundingRect().center();

    QTransform qTransform;
    qTransform.translate(birdCenter.x(), birdCenter.y());
    qTransform.rotate(rotation_);
    qTransform.translate(-birdCenter.x(), -birdCenter.y());

    setTransform(qTransform);
}

void Bird::rotateTo(const qreal & newEnd, const int & duration, const QEasingCurve & curveType) {
    rotateAnimation_->setStartValue(rotation());
    rotateAnimation_->setEndValue(newEnd);
    rotateAnimation_->setEasingCurve(curveType);
    rotateAnimation_->setDuration(duration);

    rotateAnimation_->start();
}

void Bird::setY(const qreal &newY) {
    moveBy(0, newY - y_);
    y_ = newY;
}

void Bird::changePixmap() {
    if (currentState_ == State::Up) {
        setPixmap(QPixmap("./img/bird_up.png"));
        currentState_ = State::Down;
    } else {
        setPixmap(QPixmap("./img/bird_down.png"));
        currentState_ = State::Up;
    }
}

void Bird::shootUp() {
    changeBirdStatus(birdStatus::fly);
    yAnimation_->stop();
    rotateAnimation_->stop();

    qreal currentPos = y();
    yAnimation_->setStartValue(currentPos);
    qreal endValue = currentPos - scene()->sceneRect().height()/15;
    if (endValue < -scene()->sceneRect().height()/2) {
        endValue = -scene()->sceneRect().height()/2;
    }
    yAnimation_->setEndValue(endValue);
    yAnimation_->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation_->setDuration(300);
    connect(yAnimation_, &QPropertyAnimation::finished, [=](){
        changeBirdStatus(birdStatus::fall);
        goDown();
    });
    yAnimation_->start();

    rotateTo(-30, 300, QEasingCurve::OutQuad);
}

void Bird::goDown() {
    if (y() < ground_) {
        rotateAnimation_->stop();
        yAnimation_->stop();

        yAnimation_->setStartValue(y());
        yAnimation_->setEndValue(ground_);
        yAnimation_->setEasingCurve(QEasingCurve::InQuad);
        yAnimation_->setDuration(1000);
        yAnimation_->start();

        rotateTo(60, 700, QEasingCurve::Linear);
    }
}

void Bird::stopBird() {
    timer_->stop();
}

void Bird::changeBirdStatus(birdStatus newBirdStatus) {
    birdStatus_ = newBirdStatus;
}