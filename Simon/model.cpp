//By Calvin Nielson and Ryan Brooks

#include "model.h"
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <math.h>

Model::Model()
{
 highScore=0;
 moveIndex=0;
 level=1;
 QString filePath = QCoreApplication::applicationDirPath()+"/data.txt";
 file = new QFile(filePath);
 if(!file->exists()){
     file->open(QIODevice::WriteOnly);
     if(file->isOpen()){
        file->write(QString::number(level-1).toUtf8());
        file->close();
     }
 }
 else{
     file->open(QIODevice::ReadOnly);
     if(file->isOpen()){
         QTextStream in(&*file);
         highScore=in.readLine().toInt();
         file->close();
     }
 }
 emit SetHighScore(highScore);
 srand(time(NULL)); //give a seed to random
}

Model::~Model(){
    if(file->isOpen()){
        file->close();
    }
    delete(file);
}

//method used to add a random move to the cpu's list of moves
bool Model::AddRandMove(){
    cpuMoves.push_back(rand()%2 == 1);
}

//slot for making a red move
void Model::MoveRed(){
    Move(true);
}

//slot for making a blue move
void Model::MoveBlue(){
    Move(false);
}

//method that makes a move by
//move->red !move->blue
void Model::Move(bool move){
    CheckMove(move);
    if(moveIndex==cpuMoves.size()){ //if the last move has been made
        level++;
        moveIndex=0;
        CpuTurn(); //let the cpu move
        UpdateHighScore();
    }
}

//verifys if a move matches the computer's move
void Model::CheckMove(bool move){
    if(cpuMoves.at(moveIndex)==move){ //validate that the move was correct
        //update bar
        moveIndex++;
        emit updateProgress((double) moveIndex/((double)cpuMoves.size()));
    }
    else{
        emit preGame(level);
    }
}

// updates high score if level>highscore. writes to file
void Model::UpdateHighScore(){
    if(level-1>highScore){//score is equal to what levels you have completed i.e. level-1
        file->open(QIODevice::WriteOnly);
        if(file->isOpen()){
            file->write(QString::number(level-1).toUtf8());
            file->close();
        }
        highScore=level-1;
        emit SetHighScore(highScore);
    }
}

//initializes the cpu turn by emitting a cpu singal
void Model::CpuTurn(){
    //set cpu moves phase
    emit cpu(level);
    //wait then begin the turn
    QTimer::singleShot(500,this,SLOT(StartCpuTurn()));
}

//starts the cpu turn by adding a move and flashing buttons
void Model::StartCpuTurn(){
    emit updateProgress(0);
    //generate new move and display flashes
    AddRandMove();
    t=2000/sqrt((cpuMoves.size()+1));
    QTimer::singleShot(300,this,SLOT(BeginFlash()));
}

//begins flashing button at moveIndex in cpuMoves
void Model::BeginFlash(){
    if(moveIndex<cpuMoves.size()){
        emit FlashButton(cpuMoves.at(moveIndex));
        QTimer::singleShot(t,this,SLOT(EndFLash()));//wait so the flash is visible
    }
    else{
    moveIndex=0;
    emit player();
    }
}

//turns of the flash of any button
void Model::EndFLash(){
    emit ResetButtonFlash();
    moveIndex++;
    QTimer::singleShot(t/2,this,SLOT(BeginFlash()));//wait so there is a time between flashes
}

//resets the game to prepare for a new round, resets level, move index, clears cpu moves, generates new initial cpu moves
void Model::ResetGame(){
    emit SetHighScore(highScore);
    //reset vals
    cpuMoves.clear();
    moveIndex=0;
    level=1;
    emit updateProgress(0);
    //adds four defualt moves
    AddRandMove();
    AddRandMove();
    AddRandMove();
    AddRandMove();
    t=2000/sqrt((cpuMoves.size()+1));
    //set cpu turn
    emit cpu(level);
    //flash moves
    QTimer::singleShot(800,this,SLOT(BeginFlash()));
}
