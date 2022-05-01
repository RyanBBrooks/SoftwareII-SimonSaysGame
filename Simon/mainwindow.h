#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model *model = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SetProgressBar(double);
    void SetStatePreGame(int);
    void SetStateComputer(int);
    void SetStatePlayer();
    void ResetButtonColor();
    void FlashButton(bool);
    void SetHighScore(int);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
