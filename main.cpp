#include <QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include "mainwindow.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //prendere in considerazione il fatto di far partire qui il controllo temperatura
    return a.exec();
}
