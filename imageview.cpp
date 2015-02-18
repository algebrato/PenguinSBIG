#include "imageview.h"
#include "ui_imageview.h"
#include "csbigcam.h"
#include "csbigimg.h"
#include "fitsio.h"
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <Qt>
#include <Qt3Support/Q3ScrollView>
#include <Qt3Support/Q3Painter>


ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(activated()), this, SLOT(OpenImageInW()));
    connect(ui->actionOpenH, SIGNAL(activated()), this, SLOT(getHeader()));

}


void ImageView::getHeader(){

}


void ImageView::setImage(CSBIGImg *pImg){
    pSbigImage = pImg;
    loadImage(QString::null, TRUE);
}


void ImageView::OpenImageInW(){
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
    pSbigImage = newimg;
    loadImage(QString::null, TRUE);
}




bool ImageView::loadImage(const QString& fileName, bool bAutoContrast /* = FALSE */){
    QImage image(pSbigImage->GetWidth(), pSbigImage->GetHeight(), QImage::Format_RGB888);
    unsigned char *pDest;
    unsigned short *pVid;
    long back, range, vid;
    pSbigImage->AutoBackgroundAndRange();
    pDest=image.bits();
    back=pSbigImage->GetBackground();
    range=pSbigImage->GetRange();
    pVid=pSbigImage->GetImagePointer();
    int h = pSbigImage->GetHeight();
    int w = pSbigImage->GetWidth();


    std::cout<< "Back che viene sottratto: " << back << std::endl;
    std::cout<< "Range di divisione: " << range << std::endl;
    image.setNumColors(256);
    for (int i=0;i<pSbigImage->GetHeight();i++) {
        for (int j=0; j<pSbigImage->GetWidth();j++) {
            vid=*pVid++;
            vid-=back;
            if (vid<0) vid=0;
            else if (vid>=range) vid=255;
            else vid=(vid*255)/range;

            pDest[j]=vid;
            image.setPixel(j,i,qRgb(vid,vid,vid));
        }

    }
    ui->labelImm->setPixmap(QPixmap::fromImage(image));
    ui->labelImm->resize(ui->labelImm->pixmap()->size());
    ui->scrollArea->setWidget(ui->labelImm);

}


ImageView::~ImageView()
{
    delete ui;
}
