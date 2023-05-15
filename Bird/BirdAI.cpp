//
// Created by mikhail on 14/05/23.
//

#include "BirdAI.h"

#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

BirdAI::BirdAI() : timeCreated_(std::time(nullptr)) {
    setPixmap(QPixmap("../img/bird_up.png"));
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [=]() {
        changePixmap();
    });
    timer_->start(130);

    ground_ = scenePos().y() + 220;

    ai_ = new AI();

    yAnimation_ = new QPropertyAnimation(this, "y", this);
    yAnimation_->setStartValue(scenePos().y());
    yAnimation_->setEndValue(ground_);
    yAnimation_->setEasingCurve(QEasingCurve::InQuad);
    yAnimation_->setDuration(1000);

    rotateAnimation_ = new QPropertyAnimation(this, "rotation", this);

//    yAnimation_->start();
//    rotateTo(90, 1000, QEasingCurve::InQuad);
}

BirdAI::~BirdAI() noexcept {
    // ToDo write destructor for BirdAI
//    delete yAnimation_;
//    delete rotateAnimation_;
//    delete timer_;
//    delete ai_;
}

qreal BirdAI::rotation() const {
    return rotation_;
}

qreal BirdAI::y() const {
    return y_;
}

void BirdAI::setRotation(const qreal &newRotation) {
    rotation_ = newRotation;
    QPointF birdCenter = boundingRect().center();

    QTransform qTransform;
    qTransform.translate(birdCenter.x(), birdCenter.y());
    qTransform.rotate(rotation_);
    qTransform.translate(-birdCenter.x(), -birdCenter.y());

    setTransform(qTransform);
}

void BirdAI::rotateTo(const qreal & newEnd, const int & duration, const QEasingCurve & curveType) {
    rotateAnimation_->setStartValue(rotation());
    rotateAnimation_->setEndValue(newEnd);
    rotateAnimation_->setEasingCurve(curveType);
    rotateAnimation_->setDuration(duration);

    rotateAnimation_->start();
}

void BirdAI::setY(const qreal &newY) {
    moveBy(0, newY - y_);
    y_ = newY;
}

void BirdAI::changePixmap() {
    if (currentState_ == State::Up) {
        setPixmap(QPixmap("./img/bird_up.png"));
        currentState_ = State::Down;
    } else {
        setPixmap(QPixmap("./img/bird_down.png"));
        currentState_ = State::Up;
    }
}

void BirdAI::shootUp() {
    yAnimation_->stop();
    rotateAnimation_->stop();

    qreal currentPos = y();
    yAnimation_->setStartValue(currentPos);
    qreal endValue = currentPos - scene()->sceneRect().height()/8;
    if (endValue < -scene()->sceneRect().height()/2) {
        endValue = -scene()->sceneRect().height()/2;
    }
    yAnimation_->setEndValue(endValue);
    yAnimation_->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation_->setDuration(300);
    connect(yAnimation_, &QPropertyAnimation::finished, [=](){
        goDown();
    });
    yAnimation_->start();

    rotateTo(-20, 300, QEasingCurve::OutQuad);
}

void BirdAI::goDown() {
    if (y() < ground_) {
        rotateAnimation_->stop();
        yAnimation_->stop();

        yAnimation_->setStartValue(y());
        yAnimation_->setEndValue(ground_);
        yAnimation_->setEasingCurve(QEasingCurve::InQuad);
        yAnimation_->setDuration(1000);
        yAnimation_->start();

        rotateTo(90, 1000, QEasingCurve::InQuad);
    }
}

void BirdAI::fixEfficenty() {
    efficenty_ = std::time(nullptr) - timeCreated_;
}

int BirdAI::getEfficenty() const {
    return efficenty_;
}