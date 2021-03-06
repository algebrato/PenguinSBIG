#include "mainwindow.h"
#include "ui_cameraControl.h"
#include "camera.h"
#include <QtGui>
#include <QTimer>
#include <stdio.h>
#include <stdlib.h>
#include "csbigcam.h"


QTimer *timer2=(QTimer *)0;
namespace Ui{
class cameraControl;
}

cameraControl::cameraControl(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::cameraControl)
{
    timer2 = new QTimer(this);
    timer2->start(1000);
    ui->setupUi(this);
    connect(ui->actionExit, SIGNAL(activated()), this, SLOT(close()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateTemp()));

}

void cameraControl::setCam(CSBIGCam *pCam){
    pSbigCam = pCam;
}

void cameraControl::updateTemp(){

}

void cameraControl::setTemp(){

}

cameraControl::~cameraControl()
{
    delete ui;
}
