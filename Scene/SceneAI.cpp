//
// Created by mikhail on 14/05/23.
//

#include "SceneAI.h"
#include "QRandomGenerator"
#include <QTimer>
#include <QDebug>


SceneAI::SceneAI(QObject *parent) : score_(0) {
    setSceneRect(-144, -256, 288, 512);

    eachFrame_ = new QTimer(this);
    eachFrame_->setInterval(10);
    connect(eachFrame_, &QTimer::timeout, [=]() {
       checkBirdsJump();
    });
    eachFrame_->start();

    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap("./img/background_night.png"));
    background->setPos(
            QPointF(0, 0) - QPointF(background->boundingRect().width() / 2, background->boundingRect().height() / 2));
    addItem(background);

    createNewGeneration();
}

void SceneAI::createNewGeneration() {
//    qDebug() << "new generation created";
    timer_ = new QTimer(this);

    int lower = -sceneRect().height() / 2.5;
    int upper = sceneRect().height() / 2.5;

    for (int i = 0; i < 15; ++ i) {
        int birdY = QRandomGenerator::global()->bounded(lower, upper);
        BirdAI* bird = new BirdAI(birdY);
        bird->setPos(QPointF(0, birdY));
        birds_.append(bird);
        addItem(bird);
    }

    startGame();
}

void SceneAI::removeFirstPillar() {
    if (!allPillars_.empty()) {
        allPillars_.removeAt(0);
    }
}

void SceneAI::spawnPillars() {
    connect(timer_, &QTimer::timeout, [=]() {
        pillarGroup_ = new Pillar();
        allPillars_.push_back(pillarGroup_);
        connect(pillarGroup_, &Pillar::pillarDeleted, [=]() {
            removeFirstPillar();
        });
        connect(pillarGroup_, &Pillar::destroyBird, [=](BirdAI* birdAi) {
            printBirdScoreToConsole(birdAi);
        });


        if (birds_.size() == 0) {
            stopGame();
            deletePillars();
            createNewGeneration();
        }

        addItem(pillarGroup_);
    });
}

void SceneAI::incrementScore() {
    ++score_;
}

void SceneAI::printBirdScoreToConsole(BirdAI* birdAi) {
    birdAi->fixEfficenty();
    qDebug() << "bird efficenty: " << QString::number(birdAi->getEfficenty());
    birds_.removeAll(birdAi);
    delete birdAi;
}

void SceneAI::stopGame() {
    QList<QGraphicsItem*> items = this->items();
    timer_->stop();
    for (auto* item : items) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar) {
            pillar->stopPillar();
        }
    }
}

void SceneAI::startGame() {
    timer_->start(1000);
    spawnPillars();
}

void SceneAI::deletePillars() {
    allPillars_.clear();
    QList<QGraphicsItem*> items = this->items();
    for (auto* item : items) {
        Pillar* pillar = dynamic_cast<Pillar*>(item);
        if (pillar) {
            delete pillar;
        }
    }
}


void SceneAI::checkBirdsJump() {
    if (allPillars_.empty()) {
        return;
    }
    Pillar* closest;
    for (Pillar* pillar: allPillars_) {
        if (pillar->scenePos().x() > -50) {
            closest = pillar;
            break;
        }
    }

    for (auto* bird : birds_) {
        if (bird->ai_->needJump(bird->scenePos().y(), abs(bird->scenePos().y() - closest->getTopOfInterval()), abs(bird->scenePos().y() - closest->getBottomOfInterval()))) {
            bird->shootUp();
        }
    }
}