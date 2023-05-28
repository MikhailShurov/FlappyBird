//
// Created by mikhail on 10/05/23.
//

#ifndef FLAPPYBIRD_BIRD_H
#define FLAPPYBIRD_BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation);
    Q_PROPERTY(qreal y READ y WRITE setY);

public:
    Bird(const double&);
    qreal rotation() const;
    qreal y() const;

    enum class birdStatus {
        fly,
        fall
    };
    birdStatus birdStatus_;

public slots:
    void setRotation(const qreal&);
    void setY(const qreal&);
    void rotateTo(const qreal&, const int&, const QEasingCurve&);
    void shootUp();
    void goDown();
    void startBird();
    void stopBird();

protected:
    void changeBirdStatus(birdStatus);
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
};


#endif //FLAPPYBIRD_BIRD_H
