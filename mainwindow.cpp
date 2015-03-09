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
#include <list>
#include <iterator>

CSBIGCam *camera;
CSBIGImg *immagine;
ImageView *www;


bool link_status=false;



namespace Ui{
class MainWindow;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //www->show(); //non funziona sta roba
    progress=0;
    this->setFixedSize(670,465);
    loadParameters();
    camera = new CSBIGCam();
    immagine = new CSBIGImg();


    QString yoda = "/home/stefanomandelli/.PenguinSBIG/yoda_l_d.png";
    QImage imm(yoda);
    ui->label_imm->setPixmap(QPixmap::fromImage(imm));
    ui->label_imm->resize(ui->label_imm->pixmap()->size());
    //FileMenu
    connect(ui->actionOpen, SIGNAL(activated()), this, SLOT(openImage()));
    connect(ui->Exit, SIGNAL(activated()), this, SLOT(menuExit()));
    connect(ui->actionAbout_Dev, SIGNAL(activated()), this, SLOT(helpdevel()));
    connect(ui->actionVersion, SIGNAL(activated()), this, SLOT(helpversion()));

    //CameraMenu
    connect(ui->cameraSetup, SIGNAL(activated()), this, SLOT(cameraSetup()));

    //Bottoni
    connect(ui->estLink, SIGNAL(clicked()), this, SLOT(openConnection()));
    connect(ui->butshut, SIGNAL(clicked()), this, SLOT(closeConnection()));
    connect(ui->TestGrub, SIGNAL(clicked()), this, SLOT(getImage()));

    //testBarra
    connect(ui->butFocus, SIGNAL(clicked()), this, SLOT(provaLoop()));

}

void MainWindow::prova(){
    progress=0;
    double timeEx;
    timeEx=ui->exposureFld->text().toDouble();
    t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(progBar(timeEx)));
    t->start(1000);
    return;
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

    if(immagine) delete(immagine);
    if(camera) delete(camera);

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



void MainWindow::progBar(double timeEx){
    ui->progressBar->setValue(progress);
    progress += 1*(100/timeEx) ;
    if(progress > 100){
        progress = 100;
        t->stop();
    }
    std::cout<< progress << std::endl;
}



void MainWindow::provaLoop(){

    std::list<const char*> listaNomi = {"img1.FIT", "img2.FIT", "img3.FIT"};
    CSBIGImg *newimg = new CSBIGImg;

    ImageView *w = new ImageView();
    w->show();


    for(std::list<const char*>::iterator it = listaNomi.begin(); it!=listaNomi.end(); it++){
        std::cout << *it << std::endl;
        std::cout << std::endl;

        if(newimg->OpenImage(*it) != SBFE_NO_ERROR){
            printf("Immagine NON APERTA\n");
            return;
            //w->~ImageView();
            //delete(w);
        }else{
            printf("Immagine Aperta\n");
        }
        w->setImage(newimg);
        delete(newimg); //qui funziona anche senza perchè c'è OpenImage(*it) e non c'è il get pSgib... = immagine ... forse
        CSBIGImg *newimg = new CSBIGImg;
        sleep(1);
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


void MainWindow::closeConnection(){
    if(camera){
        camera->CloseDevice();
        camera->CloseDriver();

        QImage imm("/home/stefanomandelli/.PenguinSBIG/yoda_l_d.png");
        ui->label_imm->setPixmap(QPixmap::fromImage(imm));
        ui->label_imm->resize(ui->label_imm->pixmap()->size());
        link_status=false;
    }
}


void MainWindow::openConnection(){
    OpenDeviceParams odp;
    odp.deviceType = DEV_USB1;
    int err;


    if((err=camera->OpenDriver()) != CE_NO_ERROR){
        QMessageBox::information(0,"Error in OpenDriver","Errore nell'aprtura del Driver della camera.");
        link_status=false;
        return;
    }

    if((err=camera->OpenDevice(odp)) != CE_NO_ERROR){
            QMessageBox::information(0,"Error in OpenDevice","Errore nell'aprtura del dispositivo camera.");
            link_status=false;
            return;
    }

    if((err=camera->EstablishLink()) != CE_NO_ERROR){
            QMessageBox::information(0,"Error in Link Status","Errore nel collegamento.");
            link_status=false;
            return;
    }



    QString *cT = new QString(camera->GetCameraTypeString().c_str());
    *cT = "Link to: " + *cT + "on USB"; //non si vede tutta nella label sopra l'immagine.
    ui->lab_conn->setText(cT->toAscii());
    QImage imm("/home/stefanomandelli/.PenguinSBIG/yoda_l_u.png");
    ui->label_imm->setPixmap(QPixmap::fromImage(imm));
    ui->label_imm->resize(ui->label_imm->pixmap()->size());
    link_status=true;


    //UPDATE STATUS TEMPERATURA // Pensare di spostare questa parte (e la relativa parte di stabilizzazione delle temperatura, in una classe separata
    double ccdTemp, setpointTemp, percentTE;
    MY_LOGICAL enabled;
    QString qs, tem;
    camera->QueryTemperatureStatus(enabled, ccdTemp, setpointTemp, percentTE);
    qs.setNum(setpointTemp, 'f',2);
    ui->coolingSetpoint->setText(qs.toAscii());
    tem.setNum(ccdTemp, 'f', 2);
    ui->ccdTempLbl->setText(tem.toAscii());
}


void MainWindow::getImage(){ //Questa funzione è scritta totalmente a caso.... ripensarla per il loopfocus.
    if( link_status != true ){
        QMessageBox::information(0,"Error in Link Status","Errore nel collegamento.");
        return;
    }


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
    timeEx = ui->exposureFld->text().toDouble();

    camera->SetActiveCCD(CCD_IMAGING);
    camera->SetExposureTime(ui->exposureFld->text().toDouble());
    camera->SetReadoutMode(rm);
    camera->SetABGState(ABG_LOW7);
    camera->SetFastReadout(bFastReadout);
    camera->SetDualChannelMode(bDualChannelMode);
    camera->GetFullFrame(fullWidth,fullHeight);
    immagine->AllocateImageBuffer(fullHeight,fullWidth);

    if((err = camera->GrabImage(immagine,df)) != CE_NO_ERROR){
        QMessageBox::information((QWidget*)0, "Grab Error", "Error to grab image.");
        return;
    }
    progress=0;
    t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(progBar(timeEx)));
    t->start(1000);

    QMessageBox::information((QWidget*)0, "Grab Image", "Image Grabbed");
    www = new ImageView;
    www->show();
    www->setImage(immagine);


    QString *Tot = new QString(ui->linePth->text().toAscii());
    *Tot += ui->lineName->text().toAscii();
    if(fit == 0)
        *Tot +=".FITS";
    else
        *Tot +=".SBIG";

    immagine->SaveImage(Tot->toAscii(), fit);
    immagine = new CSBIGImg();

}



void MainWindow::cameraSetup()
{
    cc = new cameraControl();
    cc->show();
}


