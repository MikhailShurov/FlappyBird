#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>
#include "Scene/SceneAI.h"
#include "Scene/Scene.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    void setup();
    Scene* scene_;
    SceneAI* sceneAi_;
    QGraphicsView* view_;
protected:
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void changeScene(const int&);
};

#endif // MAINWINDOW_H
