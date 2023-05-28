//
// Created by mikhail on 10/05/23.
//

#include "Scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QDebug>
#include <fstream>
#include <QApplication>

Scene::Scene(QObject *parent): score_(0){
    setSceneRect(-width_/2, -height_/2, width_, height_);
    eachFrame_ = new QTimer(this);
    connect(eachFrame_, &QTimer::timeout, this, &Scene::printDataToConsole);
    eachFrame_->setInterval(20);
    eachFrame_->start();

    QPixmap backgroundPixmap("./img/caves.png");
    background_ = new QGraphicsPixmapItem(backgroundPixmap);
//    background_->setTransformationMode(Qt::SmoothTransformation);
//    background_->setPixmap(backgroundPixmap.scaled(backgroundPixmap.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    background_->setPos(
            QPointF(0, 0) - QPointF(background_->boundingRect().width() / 2, background_->boundingRect().height() / 2));
    addItem(background_);

    bird_ = new Bird(0);

    addItem(bird_);
    gameStatus_ = gameStatus::GameOff;

    spawnPillars();
}

void Scene::startGame() {
    bird_->startBird();
    timer_->start(1500);
}

void Scene::keyPressEvent(QKeyEvent *event) {
    Pillar* pillar = getClosestPillar();
    if (pillar != nullptr) {
        std::ofstream fout("output.txt", std::ios::app);
        fout << pillar->scenePos().x() << " " << pillar->getTopOfInterval() << " " << pillar->getBottomOfInterval() << " " << bird_->y() << " 1\n";
    }
    if (gameStatus_ == gameStatus::GameOn) {
        if (event->key() == Qt::Key_Space) {
            bird_->shootUp();
        } else if (event->key() == Qt::Key_Escape) {
            QCoreApplication::quit();
        }
    } else if (gameStatus_ == gameStatus::GameOff){
        if ((event->key() == Qt::Key_Space)) {
            gameStatus_ = gameStatus::GameOn;
            bird_->shootUp();
            startGame();
        } else if (event->key() == Qt::Key_Escape) {
            QCoreApplication::quit();
        }
    } else {
        if (event->key() == Qt::Key_Space) {
            gameStatus_ = gameStatus::GameOff;
            restartGame();
        } else if (event->key() == Qt::Key_Escape) {
            QCoreApplication::quit();
        }
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (gameStatus_ == gameStatus::GameOn) {
        if(event->button() == Qt::LeftButton) {
            bird_->shootUp();
        }
    }
}

void Scene::restartGame() {
    score_ = 0;
    eachFrame_->setInterval(0);
    eachFrame_->start();
    QList<QGraphicsItem*> itemsOnScene = this->items();
    for (auto* item : itemsOnScene) {
        if (dynamic_cast<Bird*>(item) != nullptr || dynamic_cast<Pillar*>(item) != nullptr) {
            delete item;
        }
    }
    bird_ = new Bird(0);
    addItem(bird_);
    spawnPillars();
}

void Scene::stopGame() {
    eachFrame_->stop();
    gameStatus_ = gameStatus::GameRestart;
    bird_->stopBird();

    QList<QGraphicsItem*> items = this->items();
    timer_->stop();
    for (auto* item : items) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar) {
            pillar->stopPillar();
        }
    }
}

void Scene::spawnPillars() {
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [=]() {
        pillarGroup_ = new Pillar();

        connect(pillarGroup_, &Pillar::stopGame, [=]() {
            stopGame();
        });

        addItem(pillarGroup_);
    });
}

void Scene::incrementScore() {
    ++score_;
    qDebug() << score_;
}

Pillar* Scene::getClosestPillar() {
    QList<QGraphicsItem*> itemsOnScene = items();
    double x = 1000;
    Pillar* closestpillar = nullptr;
    for (auto* item : itemsOnScene) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar != nullptr) {
            if (pillar->scenePos().x() < x && pillar->scenePos().x() > -pillar->boundingRect().width() / 2) {
                closestpillar = pillar;
            }
        }
    }
    return closestpillar;
}

void Scene::printDataToConsole() {

    if (bird_->birdStatus_ != Bird::birdStatus::fly) {
        Pillar* pillar = getClosestPillar();
        if (pillar != nullptr) {
            std::ofstream fout("output.txt", std::ios::app);
            fout << pillar->scenePos().x() << " " << pillar->getTopOfInterval() << " " << pillar->getBottomOfInterval() << " " << bird_->y() << " 0\n";
//            qDebug() << pillar->scenePos().x() << pillar->getTopOfInterval() << pillar->getBottomOfInterval() << bird_->y() << "0";
        }
    }
}