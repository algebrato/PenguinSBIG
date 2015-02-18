#include "imageinfo.h"
#include "ui_imageinfo.h"

imageInfo::imageInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imageInfo)
{
    ui->setupUi(this);
}

imageInfo::~imageInfo()
{
    delete ui;
}
