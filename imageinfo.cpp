#include "imageinfo.h"
#include "ui_imageinfo.h"
#include "csbigimg.h"
#include "csbigcam.h"
#include "iostream"


imageInfo::imageInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imageInfo)
{
    ui->setupUi(this);
    this->setFixedSize(400,320);
}

imageInfo::~imageInfo()
{
    delete ui;
}

void imageInfo::loadHeader(){
    struct tm tym;

    QString *Head = new QString(pSbigImage->GetCameraModel().c_str());
    QString wpix, hpix, timeEXp, filter, year, mounth, day;
    wpix.setNum(double(pSbigImage->GetWidth()), '%f',0);
    hpix.setNum(double(pSbigImage->GetHeight()), '%f',0);
    filter = pSbigImage->GetFilter().c_str();
    tym= pSbigImage->GetImageStartTime();
    year.setNum(double(tym.tm_year+1900), 'f', 0);
    mounth.setNum(double(tym.tm_mon+1), 'f',0);
    day.setNum(double(tym.tm_mday), 'f', 0);

    timeEXp.setNum(double(pSbigImage->GetExposureTime()), 'f', 3);
    *Head += "\nDimensione in Pixel: " + wpix.toAscii() + "x" + hpix.toAscii();
    *Head += "\nTempo di esposizione: "+ timeEXp.toAscii() + " sec.";
    *Head += "\nFiltro: " + filter.toAscii();
    *Head += "\nData inizio posa: " + day.toAscii() + "/" + mounth.toAscii() + "/" + year.toAscii();


    ui->label->setText(Head->toAscii());


}


void imageInfo::setImage(CSBIGImg *image){
    pSbigImage = image;
    loadHeader();
}
