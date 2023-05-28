#include "MainWindow.h"
#include "Bird/Bird.h"
#include "Scene/Scene.h"
#include "Scene/SceneAI.h"
#include "Scene/MainMenuScene.h"
#include <QGraphicsView>
#include <QSizePolicy>
#include <QDebug>


MainWindow::MainWindow()
{
   setup();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup() {
// Classic mode

//    QGraphicsView* view = new QGraphicsView(scene);

// AI mode

//    QGraphicsView* view = new QGraphicsView(sceneAI);

// MainMenu
    MainMenuScene* menuScene = new MainMenuScene(this);
    connect(menuScene, &MainMenuScene::signalToChangeScene, [=](int index) {
        changeScene(index);
    });
    view_ = new QGraphicsView(menuScene);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view_);
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    }
}

void MainWindow::changeScene(const int& index) {
    switch (index) {
        case 1:
            scene_ = new Scene(this);
            view_->setScene(scene_);
            break;
        case 2:
            sceneAi_ = new SceneAI(this);
            view_->setScene(sceneAi_);
    }
}