#include "mainwindow.h"
#include "ui_cameraControl.h"
#include "camera.h"
#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
namespace Ui{
class cameraControl;
}

cameraControl::cameraControl(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::cameraControl)
{
    ui->setupUi(this);
    connect(ui->actionExit, SIGNAL(activated()), this, SLOT(close()));
}

cameraControl::~cameraControl()
{
    delete ui;
}
