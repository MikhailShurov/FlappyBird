//
// Created by mikhail on 11/05/23.
//

#ifndef FLAPPYBIRD_PILLAR_H
#define FLAPPYBIRD_PILLAR_H

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
signals:
    void stopGame();
public slots:
    void setX(const qreal&);
private:
    qreal x_;
    int y_;
    QPropertyAnimation* xAnimation_;
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar_;
    bool collideWithBird();
};


#endif //FLAPPYBIRD_PILLAR_H
