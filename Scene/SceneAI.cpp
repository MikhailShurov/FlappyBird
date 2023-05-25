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
    int upper = 0;

    for (int i = 0; i < 20; ++ i) {
//        int birdY = QRandomGenerator::global()->bounded(lower, upper);
        int birdY = 0;
        BirdAI* bird = new BirdAI(birdY);
        if (!birdsWeights_.empty() && score_ > 0) {
            std::vector<double> firstParent = birdsWeights_.top();
            birdsWeights_.pop();
            std::vector<double> secondParent = birdsWeights_.top();
            birdsWeights_.push(firstParent);
            std::vector<double> children = crossover(firstParent, secondParent);
            bird->ai_->setWeights(children);
        }
        bird->setPos(QPointF(0, birdY));
        birds_.append(bird);
        addItem(bird);
    }
    birdsWeights_.clear();
//    qDebug() << score_;
    score_ = 0;
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

        addItem(pillarGroup_);
        if (birds_.size() == 0) {
            stopGame();
            deletePillars();
            createNewGeneration();
        }
    });
}

void SceneAI::incrementScore() {
    ++score_;
}

void SceneAI::printBirdScoreToConsole(BirdAI* birdAi) {
    std::vector<double> weights = birdAi->ai_->getWeights();
    birdsWeights_.push(weights);
//    birdAi->fixEfficenty();
    birds_.removeAll(birdAi);
    delete birdAi;
}

void SceneAI::stopGame() {
    allPillars_.clear();
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
        if (pillar->scenePos().x() > 0) {
            closest = pillar;
            break;
        }
    }
//    closest->changeColor();

    for (auto* bird : birds_) {
        if (bird->ai_->needJump(bird->scenePos().y(), abs(bird->scenePos().y() - closest->getTopOfInterval()), abs(bird->scenePos().y() + bird->boundingRect().height() - closest->getBottomOfInterval()))) {
            bird->shootUp();
        }
    }
}

std::vector<double> SceneAI::crossover(const std::vector<double>& parent1Weights, const std::vector<double>& parent2Weights) {
    int crossoverPoint = std::rand() % parent1Weights.size();
    std::vector<double> child1Weights;
    for (int i = 0; i < parent1Weights.size(); i++) {
        if (i <= crossoverPoint) {
            child1Weights.push_back(parent1Weights[i]);
        } else {
            child1Weights.push_back(parent2Weights[i]);
        }
    }
    if (std::rand() == 0) {
        child1Weights = parent1Weights;
    }
    int mut = std::rand() % 2;
    if (mut) {
        mutate(child1Weights);
    }
    return child1Weights;
}

void SceneAI::mutate(std::vector<double> &child) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    int index = std::rand() % child.size();
    double mutationAmount = dis(gen);
//    child[index] += child[index] * mutationAmount;
    child[index] += mutationAmount;
//    if (child[index] < -30.0) {
//        child[index] = -30.0;
//    } else if (child[index] > 30.0) {
//        child[index] = 30.0;
//    }
}