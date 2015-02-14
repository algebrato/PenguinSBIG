#include "imageview.h"
#include "ui_imageview.h"
#include "csbigcam.h"
#include "csbigimg.h"
#include "fitsio.h"
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <Qt>
#include <Qt3Support/Q3ScrollView>
#include <Qt3Support/Q3Painter>


ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);


}



void ImageView::setImage(CSBIGImg *pImg){
    pSbigImage = pImg;
    loadImage(QString::null, TRUE);
}



bool ImageView::loadImage(const QString& fileName, bool bAutoContrast /* = FALSE */){
    QImage image(pSbigImage->GetWidth(), pSbigImage->GetHeight(), QImage::Format_Indexed8);
    unsigned char *pDest;
    unsigned short *pVid;
    long back, range, vid;
    pSbigImage->AutoBackgroundAndRange();
    pDest=image.bits();
    back=pSbigImage->GetBackground();
    range=pSbigImage->GetRange();
    pVid=pSbigImage->GetImagePointer();


    std::cout<< "Back che viene sottratto: " << back << std::endl;
    std::cout<< "Range di divisione: " << range << std::endl;
    image.setNumColors(256);
    for (int i=0;i<pSbigImage->GetHeight();i++) {
        for (int j=0; j<pSbigImage->GetWidth();j++) {
            vid=*pVid++;
            //std::cout<< vid << "\t";
            vid-=back;
            if (vid<0) vid=0;
            else if (vid>=range) vid=255;
            else vid=(vid*255)/range;

            pDest[j]=vid;
            image.setPixel(j,i,vid);
        }
        //printf("\n");
        //pDest +=image.bytesPerLine();

    }

    cout<<image.pixel(1,1)<<endl;
    pm.convertFromImage(image);
    ui->labelImm->setPixmap(pm);
    ui->labelImm->resize(ui->labelImm->pixmap()->size());
    ui->scrollArea->setWidget(ui->labelImm);

}


ImageView::~ImageView()
{
    delete ui;
}
