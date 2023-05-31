#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>
#include "Scene/SceneAI.h"
#include "Scene/Scene.h"
#include "Scene/MainMenuScene.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    void setup();
    Scene* scene_ = nullptr;
    SceneAI* sceneAi_ = nullptr;
    SceneAI* trained_ = nullptr;
    MainMenuScene* menuScene_ = nullptr;
    QGraphicsView* view_;
protected:
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void changeScene(const int&);
    void goToMainMenu();
};

#endif // MAINWINDOW_H
