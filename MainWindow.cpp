#include "MainWindow.h"
#include "Bird/Bird.h"
#include "Scene/Scene.h"
#include "Scene/SceneAI.h"
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow()
{
   setup();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup() {
// uncomment if you need usual mode
    Scene* scene = new Scene(this);
    QGraphicsView* view = new QGraphicsView(scene);

// AI mode
//    SceneAI* sceneAI = new SceneAI(this);
//    QGraphicsView* view = new QGraphicsView(sceneAI);
    setCentralWidget(view);
}

