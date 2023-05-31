//
// Created by mikhail on 14/05/23.
//

#ifndef FLAPPYBIRD_BIRDAI_H
#define FLAPPYBIRD_BIRDAI_H

#include "../AI/AI.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class BirdAI: public QObject, public QGraphicsPixmapItem{
Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation);
    Q_PROPERTY(qreal y READ y WRITE setY);
public:
    BirdAI(const double &, bool = true);
    ~BirdAI();
    qreal rotation() const;
    qreal y() const;
    AI* ai_;
public slots:
    void setRotation(const qreal&);
    void setY(const qreal&);
    void rotateTo(const qreal&, const int&, const QEasingCurve&);
    void shootUp();
    void goDown();
    void fixEfficenty();
    int getEfficenty() const;
private:
    enum class State {
        Up,
        Down
    };
    void changePixmap();
    State currentState_;
    qreal rotation_;
    qreal y_;
    qreal ground_;
    QTimer* timer_;
    QPropertyAnimation* yAnimation_;
    QPropertyAnimation* rotateAnimation_;
    std::time_t timeCreated_;
    int efficenty_;
};

#endif //FLAPPYBIRD_BIRDAI_H
