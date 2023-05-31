#include "MainWindow.h"
#include "Scene/Scene.h"
#include "Scene/SceneAI.h"
#include "Scene/MainMenuScene.h"
#include <QGraphicsView>
#include <QSizePolicy>
#include <QRegion>
#include <QGraphicsProxyWidget>


MainWindow::MainWindow()
{
   setup();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup() {

// MainMenu
    menuScene_ = new MainMenuScene(this);
    connect(menuScene_, &MainMenuScene::signalToChangeScene, [=](int index) {
        changeScene(index);
    });
    view_ = new QGraphicsView(menuScene_);
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
    QWidget* widget = new QWidget();
    widget->setFixedSize(100, 100);

    QHBoxLayout* layout = new QHBoxLayout();

    QPushButton* mainMenuButton = new QPushButton("Menu");
    mainMenuButton->setFixedSize(70, 70);
    QFont qFont = mainMenuButton->font();
    qFont.setBold(true);
    mainMenuButton->setFont(qFont);
    mainMenuButton->setStyleSheet("QPushButton{background-color:#ff7420; border-radius:20px; border: 4px solid brown} QPushButton:hover {background-color: #cd5700;}");

    layout->addWidget(mainMenuButton);

    widget->move(-960, -540);
    widget->setStyleSheet("background-color: transparent;");
    widget->setLayout(layout);

    connect(mainMenuButton, &QPushButton::clicked, [=]() {
        goToMainMenu();
    });
    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget();
    switch (index) {
        case 1:
            scene_ = new Scene(this);
            proxy = scene_->addWidget(widget);
            proxy->setZValue(100);
            view_->setScene(scene_);
            break;
        case 2:
            sceneAi_ = new SceneAI(this);
            proxy = sceneAi_->addWidget(widget);
            proxy->setZValue(100);
            view_->setScene(sceneAi_);
            break;
        case 3:
            trained_ = new SceneAI(this, true);
            proxy = trained_->addWidget(widget);
            proxy->setZValue(100);
            view_->setScene(trained_);
            break;
    }
}

void MainWindow::goToMainMenu() {
    view_->setScene(menuScene_);
//    if (scene_ != nullptr) {
//        delete scene_;
//        scene_ = nullptr;
//    }
//    if (sceneAi_ != nullptr) {
//        delete sceneAi_;
//        sceneAi_ = nullptr;
//    }
//    if (trained_ != nullptr) {
//        delete trained_;
//        trained_ = nullptr;
//    }
}