//
// Created by mikhail on 28/05/23.
//

#ifndef FLAPPYBIRD_MAINMENUSCENE_H
#define FLAPPYBIRD_MAINMENUSCENE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QDebug>

class MainMenuScene: public QGraphicsScene {
    Q_OBJECT
public:
    explicit MainMenuScene(QObject *parent = nullptr);
//    ~MainMenuScene();
private:
    QLabel* title_;
    QGraphicsPixmapItem* background_;
    const int width_ = 1920;
    const int height_ = 1080;
    QPushButton* classic_;
    QPushButton* ai_;
    QPushButton* trainedAi_;
    QHBoxLayout* hBoxLayout_;
    QWidget* widget_;
    void changeScene(const int&);
signals:
    void signalToChangeScene(const int&);
};


#endif //FLAPPYBIRD_MAINMENUSCENE_H
