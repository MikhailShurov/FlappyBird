//
// Created by mikhail on 10/05/23.
//

#ifndef FLAPPYBIRD_SCENE_H
#define FLAPPYBIRD_SCENE_H

#include "../Bird/Bird.h"
#include <QGraphicsScene>

class Scene: public  QGraphicsScene{
public:
    Scene(QObject *parent = nullptr);
private:
    Bird* bird_;
protected:
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
};


#endif //FLAPPYBIRD_SCENE_H
