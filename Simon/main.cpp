//By Calvin Nielson and Ryan Brooks

#include "mainwindow.h"
#include <QApplication>
#include <model.h>

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    Model model;
    QApplication a(argc, argv);
    MainWindow w(&model);
    w.show();
    return a.exec();
}
