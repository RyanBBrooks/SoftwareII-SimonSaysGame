//By Calvin Nielson and Ryan Brooks

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include <QSound>
#include <QSignalMapper>

MainWindow::MainWindow(Model *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //initialize button colors
    ResetButtonColor();
    SetStatePreGame(-1);

    //buttons view->model
    QObject::connect(ui->redButton, &QPushButton::pressed, model, &Model::MoveRed);
    QObject::connect(ui->blueButton, &QPushButton::pressed, model, &Model::MoveBlue);
    QObject::connect(ui->startButton, &QPushButton::pressed, model, &Model::ResetGame);
    //model->view states
    QObject::connect(model, &Model::preGame, this, &MainWindow::SetStatePreGame);
    QObject::connect(model, &Model::cpu, this, &MainWindow::SetStateComputer);
    QObject::connect(model, &Model::player, this, &MainWindow::SetStatePlayer);
    //model->view flashes
    QObject::connect(model, &Model::FlashButton, this, &MainWindow::FlashButton);
    QObject::connect(model, &Model::ResetButtonFlash, this , &MainWindow::ResetButtonColor);
    //model->view progress
    QObject::connect(model, &Model::updateProgress, this, &MainWindow::SetProgressBar);
    //model->view set highscore
    QObject::connect(model, &Model::SetHighScore, this, &MainWindow::SetHighScore);
}

//changes the button color corresponding to move to represent a flash
void MainWindow::FlashButton(bool move){
    if(move){//red
      ui->redButton->setStyleSheet(QString("QPushButton:disabled{background-color:rgb(255,105,105);}"));
      QSound::play("qrc:/sounds/red.wav");
    }
    else{//blue
      ui->blueButton->setStyleSheet(QString("QPushButton:disabled{background-color:rgb(105,105,255);}"));
      QSound::play("qrc:/sounds/blue.wav");
    }
}

//resets the button colors to default
void MainWindow::ResetButtonColor(){
    ui->redButton->setStyleSheet(QString("QPushButton{background-color: rgb(200,30,30);} QPushButton:pressed{background-color:rgb(20,3,3);} QPushButton:disabled{background-color:rgb(150,80,80);}"));
    ui->blueButton->setStyleSheet(QString("QPushButton{background-color: rgb(30,30,200);} QPushButton:pressed{background-color:rgb(3,3,20);} QPushButton:disabled{background-color:rgb(80,80,150);}"));
}

//changes values to match the state during the players turn
void MainWindow::SetStatePlayer(){
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->loseLabel->setText("");
}

//changes values to match the state before the game
void MainWindow::SetStatePreGame(int level){
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    if(level>0){
        //set text for lose and level reached
        QSound::play("qrc:/sounds/failure.wav");
        ui->loseLabel->setText("You lose!");
        ui->levelLabel->setText("Level: "+QString::number(level));
    }
    //otherwise player hasnt lost yet
}

//changes values to match the state during the computers turn
void MainWindow::SetStateComputer(int level){
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->loseLabel->setText("");
    ui->levelLabel->setText("Level: "+QString::number(level));
    QSound::play("qrc:/sounds/nextLevel.wav");
}

//updates the progress bar
void MainWindow::SetProgressBar(double percentage){
    ui->progressBar->setValue(percentage*100);
}

void MainWindow::SetHighScore(int highScore){
    ui->highScoreLabel->setText("    High Score: "+QString::number(highScore));
}

MainWindow::~MainWindow()
{
    delete ui;
}
