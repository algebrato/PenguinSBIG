#include "imageview.h"
#include "ui_imageview.h"
#include "csbigcam.h"
#include "csbigimg.h"
#include "fitsio.h"
#include <iostream>
#include <QImage>
#include <QPixmap>


ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
}



void ImageView::setImage(CSBIGImg *pImg){
    pSbigImage = pImg;
    loadImage(QString::null, TRUE);
}

/*
 *    unsigned char *pDest;
    unsigned short *pVid;
    long back, range, vid;
pDest=image.bits();
    back=pSbigImg->GetBackground();
    range=pSbigImg->GetRange();
    pVid=pSbigImg->GetImagePointer();

    if (range < iMinRange ) range = iMinRange;
    for (int i=0;i<pSbigImg->GetHeight();i++) {
    for (int j=0; j<pSbigImg->GetWidth();j++) {
        vid=*pVid++;
        vid-=back;
        if (vid<0) vid=0;
        else if (vid>=range) vid=255;
        else vid=(vid*255)/range;
        pDest[j]=vid;
    }
    pDest+=image.bytesPerLine();
    }

    pixmap.convertFromImage(image,0);
    Picture->setPixmap(pixmap);
    */



bool ImageView::loadImage(const QString& fileName, bool bAutoContrast /* = FALSE */){
    QImage image(pSbigImage->GetWidth(), pSbigImage->GetHeight(), QImage::Format_Indexed8);
    unsigned char *pDest;
    unsigned short *pVid;
    long back, range, vid;
    pDest=image.bits();
    back=pSbigImage->GetBackground();
    range=pSbigImage->GetRange();
    pVid=pSbigImage->GetImagePointer();
    //pSbigImage->AutoBackgroundAndRange();

    image.setNumColors(256);
    pSbigImage->SetBackground(2048);

    for (int i=0;i<pSbigImage->GetHeight();i++) {
        for (int j=0; j<pSbigImage->GetWidth();j++) {
            vid=*pVid++;
            vid-=back;
            std::cout << vid << "\t" ;
            if (vid<0) vid=0;
            else if (vid>=range) vid=255;
            else vid=(vid*255)/range;

            pDest[j]=vid;
        }
        printf("\n");
        pDest +=image.bytesPerLine();
    }

    pm.convertFromImage(image,0);
    ui->labelImm->setPixmap(pm);
    ui->labelImm->resize(ui->labelImm->pixmap()->size());
}


ImageView::~ImageView()
{
    delete ui;
}
