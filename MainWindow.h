#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    void setup();
};

#endif // MAINWINDOW_H
