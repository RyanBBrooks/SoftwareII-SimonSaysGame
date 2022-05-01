#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <QTimer>
#include <QFile>

class Model : public QObject
{
    Q_OBJECT
private:
    int t; //animation time interval
    int level;
    QFile *file;
    int moveIndex;
    int highScore;
    std::vector<bool> cpuMoves;
public:
    Model();
    ~Model();
    bool AddRandMove();
    void CheckMove(bool);
    void Move(bool);
    void CpuTurn();
    void UpdateHighScore();
public slots:
    void BeginFlash();
    void MoveRed();
    void MoveBlue();
    void ResetGame();
    void StartCpuTurn();
    void EndFLash();
signals:
    void updateProgress(double);
    void preGame(int);
    void player();
    void cpu(int);
    void FlashButton(bool);
    void ResetButtonFlash();
    void SetHighScore(int);

};

#endif // MODEL_H
