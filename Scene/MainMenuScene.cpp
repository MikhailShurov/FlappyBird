//
// Created by mikhail on 28/05/23.
//

#include "MainMenuScene.h"


MainMenuScene::MainMenuScene(QObject *parent) {
    setSceneRect(-width_/2, -height_/2, width_, height_);
    QPixmap backgroundPixmap("./img/caves.png");
    background_ = new QGraphicsPixmapItem(backgroundPixmap);

    background_->setPos(
            QPointF(0, 0) - QPointF(background_->boundingRect().width() / 2, background_->boundingRect().height() / 2));
    addItem(background_);

    title_ = new QLabel("Flappy Bird");
    title_->setFont(QFont("Arial", 46));
    QFont font = title_->font(); // получаем текущий шрифт QLabel
    font.setBold(true); // устанавливаем жирный шрифт
    title_->setFont(font);
    title_->setFixedSize(330, 100);
    title_->move(-title_->width()/2, -sceneRect().height()/5);
    title_->setStyleSheet("background-color: transparent;");
    addWidget(title_);

    widget_ = new QWidget();
    widget_->setStyleSheet("background-color: transparent;");
    hBoxLayout_ = new QHBoxLayout();

    classic_ = new QPushButton("Classic mode");
    classic_->setFixedSize(100, 100);
    classic_->setStyleSheet("background-color: #ff7420; border-radius: 25px; border: 2px solid brown;");
    connect(classic_, &QPushButton::clicked, [=]() {
        changeScene(1);
    });
    ai_ = new QPushButton("Train AI");
    ai_->setFixedSize(100, 100);
    ai_->setStyleSheet("background-color: #ff7420; border-radius: 25px; border: 2px solid brown;");
    connect(ai_, &QPushButton::clicked, [=]() {
        changeScene(2);
    });
    trainedAi_ = new QPushButton("Start trained AI");
    trainedAi_->setFixedSize(100, 100);
    trainedAi_->setStyleSheet("background-color: #ff7420; border-radius: 25px; border: 2px solid brown;");
    connect(trainedAi_, &QPushButton::clicked, [=]() {
        changeScene(3);
    });

    hBoxLayout_->addWidget(classic_);
    hBoxLayout_->addWidget(ai_);
    hBoxLayout_->addWidget(trainedAi_);
    widget_->setFixedSize(500, 150);
    widget_->setLayout(hBoxLayout_);
    widget_->move(-widget_->width()/2, widget_->height());
    addWidget(widget_);
}

void MainMenuScene::changeScene(const int& index) {
    emit(signalToChangeScene(index));
}