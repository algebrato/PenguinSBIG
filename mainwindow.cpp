#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageview.h"
#include "camera.h"
#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QLabel>
#include <QTimer>
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QComboBox>
#include <string>
#include <libusb.h>
#include "lpardrv.h"
#include <csbigcam.h>
#include <csbigimg.h>
#include "showimg.h"
#include <iostream>
#include <fitsio.h>
#include <fitsio2.h>






QTimer *timer=(QTimer *)0;
namespace Ui{
class MainWindow;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(515,465);
    loadParameters();
    timer = new QTimer(this);
    timer->start(1000);
    QString yoda = "/home/stefanomandelli/yoda.png";
    /*QImage imm(yoda);
    ui->label_imm->setPixmap(QPixmap::fromImage(imm));
    ui->label_imm->resize(ui->label_imm->pixmap()->size());*/
    //FileMenu
    connect(ui->actionOpen, SIGNAL(activated()), this, SLOT(openImage()));
    connect(ui->Exit, SIGNAL(activated()), this, SLOT(menuExit()));
    connect(ui->actionAbout_Dev, SIGNAL(activated()), this, SLOT(helpdevel()));
    connect(ui->actionVersion, SIGNAL(activated()), this, SLOT(helpversion()));

    //CameraMenu
    connect(ui->cameraSetup, SIGNAL(activated()), this, SLOT(cameraSetup()));

    //MainForm Objects
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStat())); //forse non serve
    connect(ui->buttImage, SIGNAL(clicked()), this, SLOT(getImage()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuExit(){
    QFile fileSave(".salvataggi");

    fileSave.open(QIODevice::WriteOnly);
    QTextStream out(&fileSave);
    out << ui->ImgTypeCB->currentIndex() << "\n";
    out << ui->FrameTYPCB->currentIndex() << "\n";
    out << ui->exposureFld->text() << "\n";
    out << ui->comboBINN->currentIndex() << "\n";
    out << ui->comboFR->currentIndex()  << "\n";
    out << ui->comboDCM->currentIndex() << "\n";
    out << ui->linePth->text() ;
    fileSave.close();
}

void MainWindow::loadParameters(){
    QFile file(".salvataggi");
    QStringList dd;
    int k=0;
    if(file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            QString line = file.readLine();
            dd.append(line);
            k++;
        }
        ui->ImgTypeCB->setCurrentIndex(dd.at(0).toInt());
        ui->FrameTYPCB->setCurrentIndex(dd.at(1).toInt());
        ui->exposureFld->setText(dd.at(2));
        ui->comboBINN->setCurrentIndex(dd.at(3).toInt());
        ui->comboFR->setCurrentIndex(dd.at(4).toInt());
        ui->comboDCM->setCurrentIndex(dd.at(5).toInt());
        ui->linePth->setText(dd.at(6));
        file.close();
    }else{
        QMessageBox::information(0,"Load Parameters","Non e' stato trovato alcun file di salvataggio. Verranno caricati i parametri di default.");
    }




}

void MainWindow::openImage(){
    QString fileName = QFileDialog::getOpenFileName(this);
    CSBIGImg *newimg = new CSBIGImg;

    std::cout << fileName.toStdString() << std::endl;
    std::cout << newimg->GetRange() << std::endl;
    std::cout << newimg->GetBackground() << std::endl;

    /*APRI IMMAGINE*/
    if(newimg->OpenImage(fileName.toLatin1()) != SBFE_NO_ERROR){
        printf("Immagine NON APERTA\n");
        return;
    }else{
        printf("Immagine Aperta\n");
    }

    ImageView *w = new ImageView();
    w->show();
    w->setImage(newimg);
    newimg = new CSBIGImg;
}


void MainWindow::helpmanuale(){

}

void MainWindow::helptecsupp(){

}

void MainWindow::helpdevel(){
    QMessageBox::information(0,"Dev","Sviluppatori del Progetto:\n\nStefano Mandelli:\t linuxfree2@gmail.com ");

}



void MainWindow::helpversion(){
    QMessageBox::information(0,"Version","Penguin SBIG:\n\nVersion 0.0.00\n\nLast Update:8-02-2015");
}








void MainWindow::getImage(){
    PAR_ERROR err = CE_NO_ERROR;

    int rm = ui->comboBINN->currentIndex();
    /***************************************/
    bool bFastReadout;
    if(ui->comboFR->currentIndex()==0){
        bFastReadout=true;
    }else{
        bFastReadout=false;
    }
    /***************************************/
    bool bDualChannelMode;
    if(ui->comboDCM->currentIndex()==0){
        bDualChannelMode=true;
    }else{
        bDualChannelMode=false;
    }
    /***************************************/
    string filePath, filePathName, error;

    SBIG_DARK_FRAME df = (SBIG_DARK_FRAME)ui->FrameTYPCB->currentIndex();
    switch (df) {
    case 0: df = SBDF_LIGHT_ONLY; break;
    case 1: df = SBDF_DARK_ONLY; break;
    case 2: df = SBDF_DARK_ALSO; break;
    default: df = SBDF_LIGHT_ONLY; break;
    }



    SBIG_IMAGE_FORMAT fit= (SBIG_IMAGE_FORMAT)ui->ImgTypeCB->currentIndex();
    switch (fit) {
    case 0: fit = SBIF_FITS; break;
    case 1: fit = SBIF_COMPRESSED; break;
    default : fit = SBIF_FITS; break;
    }


    double timeEx;
    int numOfImage;
    int top, left, width, fullWidth, height, fullHeight;
    SBIG_FILE_ERROR ferr;
    OpenDeviceParams odp;


    //creo l'oggetto Immagine Sbig
    pSbigImage = new CSBIGImg;
    //creo l'oggetto Camera SBIG
    pSbigCam = new CSBIGCam(DEV_USB1);

    if((err = pSbigCam->EstablishLink()) != CE_NO_ERROR){
        QMessageBox::information(0, "Link Error", "Camera link is down");
        ui->labelStatus->setText("Link is DOWN!");
        return;

    }
    /*if((err=pSbigCam->OpenDriver()) != CE_NO_ERROR) {
        QMessageBox::information((QWidget*)0, "Link Error", "Error opening camera driver.");
        return;
    }
    if((err=pSbigCam->OpenDevice(odp)) != CE_NO_ERROR) {
        QMessageBox::information((QWidget*)0, "Link Error", "Error opening camera device.");
        return;
    }
    if((err=pSbigCam->EstablishLink()) != CE_NO_ERROR) {
        QMessageBox::information((QWidget*)0, "Link Error", "Error establishing link to camera.");
        return;
    }*/

    ui->labelStatus->setText("Link is UP!");
    pSbigCam->SetActiveCCD(CCD_IMAGING);
    pSbigCam->SetExposureTime(ui->exposureFld->text().toDouble());
    pSbigCam->SetReadoutMode(rm);
    pSbigCam->SetABGState(ABG_LOW7);
    pSbigCam->SetFastReadout(bFastReadout);
    pSbigCam->SetDualChannelMode(bDualChannelMode);
    pSbigCam->GetFullFrame(fullWidth,fullHeight);
    pSbigImage->AllocateImageBuffer(fullHeight,fullWidth);

    if((err = pSbigCam->GrabImage(pSbigImage,df)) != CE_NO_ERROR){
        QMessageBox::information((QWidget*)0, "Grab Error", "Error to grab image.");
        return;
    }
    QMessageBox::information((QWidget*)0, "Grab Image", "Image Grabbed");




    //STRINGA TOTALE
    pSbigImage->SaveImage("./Ciao", fit);


}



void MainWindow::init(){

}

void MainWindow::updateStat(){


}

void MainWindow::cameraSetup()
{
    cc = new cameraControl();
    cc->show();
}


