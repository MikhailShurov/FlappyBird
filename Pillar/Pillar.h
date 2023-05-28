//
// Created by mikhail on 11/05/23.
//

#ifndef FLAPPYBIRD_PILLAR_H
#define FLAPPYBIRD_PILLAR_H

#include "../Bird/BirdAI.h"
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>

class Pillar : public QObject, public QGraphicsItemGroup{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    Pillar();
    ~Pillar();
    qreal x() const;
    void stopPillar();
    int getTopOfInterval() const;
    int getBottomOfInterval() const;
signals:
    void stopGame();
    void destroyBird(BirdAI*);
    void pillarDeleted();
public slots:
    void setX(const qreal&);
private:
    qreal x_;
    int y_;
    bool birdPass_;
    QPropertyAnimation* xAnimation_;
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar_;
    void collideWithBird();
    void checkIfBirdPass();
};


#endif //FLAPPYBIRD_PILLAR_H
