#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QTimer>
#include <QMainWindow>
#include "camera.h"
#include "csbigimg.h"
#include "csbigcam.h"
#include "showimg.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void cameraSetup();
    void init();
    void openImage();
    void getImage();
    void menuExit();
    void helpmanuale();
    void helptecsupp();
    void helpdevel();
    void helpversion();
    void closeConnection();
    void openConnection();
    void progBar(double timeEx);
    void prova();


private:
    void loadParameters();
    Ui::MainWindow *ui;
    cameraControl *cc;
    ImageViewer *w;
    CSBIGImg *pSbigImage;
    CSBIGCam *pSbigCam;
    QImage image;
    QPixmap pm;
    QString filename;
    QTimer *t;
    int progress;


};


#endif // MAINWINDOW_H*//
