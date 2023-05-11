#include "MainWindow.h"
#include "Bird/Bird.h"
#include "Scene/Scene.h"
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow()
{
   setup();
}

MainWindow::~MainWindow(){}

void MainWindow::setup() {
    Scene* scene = new Scene(this);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

