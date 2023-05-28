#include "MainWindow.h"
#include "Scene/Scene.h"
#include "Scene/SceneAI.h"
#include "Scene/MainMenuScene.h"
#include <QGraphicsView>
#include <QSizePolicy>


MainWindow::MainWindow()
{
   setup();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup() {

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
            break;
        case 3:
            sceneAi_ = new SceneAI(this, true);
            view_->setScene(sceneAi_);
            break;
    }
}