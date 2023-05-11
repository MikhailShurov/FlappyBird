//
// Created by mikhail on 10/05/23.
//

#ifndef FLAPPYBIRD_SCENE_H
#define FLAPPYBIRD_SCENE_H

#include "../Bird/Bird.h"
#include "../Pillar/Pillar.h"
#include <QGraphicsScene>
#include <QTimer>

class Scene: public  QGraphicsScene{
public:
    Scene(QObject *parent = nullptr);
private:
    Bird* bird_;
    Pillar* pillarGroup_;
protected:
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void spawnPillars();
    QTimer* timer_;
};


#endif //FLAPPYBIRD_SCENE_H
