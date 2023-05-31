//
// Created by mikhail on 14/05/23.
//

#include "SceneAI.h"
#include "QRandomGenerator"
#include <QTimer>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>


SceneAI::SceneAI(QObject *parent, bool takeWeightsFromFile) : score_(0), gen_(1), needMutation_(true), takeFromFile_(takeWeightsFromFile) {
    setSceneRect(-width_/2, -height_/2, width_, height_);

    eachFrame_ = new QTimer(this);
    eachFrame_->setInterval(10);
    connect(eachFrame_, &QTimer::timeout, [=]() {
       checkBirdsJump();
    });
    eachFrame_->start();
    if (takeWeightsFromFile) {
        fall_ = false;
    }
    QPixmap backgroundPixmap("./img/caves.png");
    background_ = new QGraphicsPixmapItem(backgroundPixmap);
//    background_->setTransformationMode(Qt::SmoothTransformation);
//    background_->setPixmap(backgroundPixmap.scaled(backgroundPixmap.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    background_->setPos(
            QPointF(0, 0) - QPointF(background_->boundingRect().width() / 2, background_->boundingRect().height() / 2));
    addItem(background_);
    proxy_ = new QGraphicsProxyWidget();

    generation_ = new QLabel("GENERATION:");
    generation_->setStyleSheet("background-color:white;border:1px solid black");
    generation_->move(0, -400);
    generation_->resize(110, 20);
    proxy_ = addWidget(generation_);
    proxy_->setZValue(100);

    currentScore_ = new QLabel("SCORE:");
    currentScore_->setStyleSheet("background-color:white;border:1px solid black");
    currentScore_->move(0, -380);
    currentScore_->resize(110, 20);
    proxy_ = addWidget(currentScore_);
    proxy_->setZValue(100);

    alive_ = new QLabel();
    alive_->setStyleSheet("background-color:white;border:1px solid black");
    alive_->move(0, -360);
    alive_->resize(110, 20);
    proxy_ = addWidget(alive_);
    proxy_->setZValue(100);

    createNewGeneration();
}

void SceneAI::createNewGeneration() {
//    qDebug() << "new generation created";
    generation_->setText(QString("GENERATION: " + QString::number(gen_)));
    ++ gen_;

    timer_ = new QTimer(this);

    for (int i = 0; i < 70; ++ i) {
        int birdY = 0;
        BirdAI* bird = new BirdAI(birdY, fall_);
        if (!birdsWeights_.empty() && score_ > 0) {
            std::vector<double> firstParent = birdsWeights_.top();
            birdsWeights_.pop();
            std::vector<double> secondParent = birdsWeights_.top();
            birdsWeights_.push(firstParent);
            std::vector<double> children = crossover(firstParent, secondParent);
            bird->ai_->setWeights(children);
        }
        if (takeFromFile_) {
//            std::vector<double> weights = readFromFile();
            bird->ai_->setWeights({3.90802, -21.4343, 11.3567});
        }
        bird->setPos(QPointF(0, birdY));
        birds_.append(bird);
        addItem(bird);
    }
    alive_->setText(QString("ALIVE: ") + QString::number(birds_.size()));
    birdsWeights_.clear();
    score_ = 0;
    currentScore_->setText(QString("SCORE: 0"));
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

        connect(pillarGroup_, &Pillar::incrementScore, [=]() {
            incrementScore();
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
    if (score_ == 100) {
        needMutation_ = false;
    }
    currentScore_->setText(QString("SCORE: ") + QString::number(score_));
    if (score_ == 100) {
        qDebug() << "Ideal weights:" << birds_[0]->ai_->getWeights();
        std::ofstream outfile("IdealWeights.txt", std::ios_base::out);
        for (int i = 0; i < birds_[0]->ai_->getWeights().size(); i++) {
            outfile << birds_[0]->ai_->getWeights()[i] << " ";
        }
    }
}

void SceneAI::printBirdScoreToConsole(BirdAI* birdAi) {
    std::vector<double> weights = birdAi->ai_->getWeights();
    birdsWeights_.push(weights);
    birds_.removeAll(birdAi);
    alive_->setText(QString("ALIVE: ") + QString::number(birds_.size()));
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
    timer_->start(1700);
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
        if (pillar->scenePos().x() > -20) {
            closest = pillar;
            break;
        }
    }

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
    int mut = std::rand() % 5;
    if (mut == 0 && needMutation_) {
        mutate(child1Weights);
    }
    return child1Weights;
}

void SceneAI::mutate(std::vector<double> &child) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-0.5, 0.5);
    int index = std::rand() % child.size();
    double mutationAmount = dis(gen);
    child[index] += child[index] * mutationAmount;
    if (child[index] < -30.0) {
        child[index] = -30.0;
    } else if (child[index] > 30.0) {
        child[index] = 30.0;
    }
}

std::vector<double> SceneAI::readFromFile() {
    std::ifstream fin("IdealWeights.txt", std::ios::in);

    std::string line;
    std::getline(fin, line);
    std::istringstream sstream(line);
    double w1 = -1, w2 = -1, w3 = -1;
    sstream >> w1 >> w2 >> w3;
//    qDebug() << w1 << w2 << w3;
    return {w1, w2, w3};
}

SceneAI::~SceneAI() noexcept {
    stopGame();
    birds_.clear();
    QList<QGraphicsItem*> items = this->items();
    for (auto* item : items) {
        BirdAI* birdAi = dynamic_cast<BirdAI*>(item);
        if (birdAi) {
            delete birdAi;
        }
    }
    if (pillarGroup_ != nullptr) {
        delete pillarGroup_;
    }
    if (timer_ != nullptr) {
        delete timer_;
    }

    if (eachFrame_ != nullptr) {
        delete eachFrame_;
    }
    deletePillars();
    if (background_ != nullptr) {
        delete background_;
        background_ = nullptr;
    }
    if (generation_ != nullptr) {
        delete generation_;
        generation_ = nullptr;
    }
    if (currentScore_ != nullptr) {
        delete currentScore_;
        currentScore_ = nullptr;
    }
    if (alive_ != nullptr) {
        delete alive_;
        alive_ = nullptr;
    }
    if (proxy_ != nullptr) {
        delete proxy_;
        proxy_ = nullptr;
    }
}