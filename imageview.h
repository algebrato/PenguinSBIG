#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QMainWindow>
#include <csbigcam.h>
#include <csbigimg.h>
#include <QImage>
#include <QPixmap>
#include "imageinfo.h"

namespace Ui {
class ImageView;
}

class ImageView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();
    bool loadImage( const QString& , bool bAutoContrast = FALSE);
    void setImage (CSBIGImg *pImg);

private slots:
    void OpenImageInW();
    void getHeader();

    
private:
    Ui::ImageView *ui;
    CSBIGImg *pSbigImage;
    CSBIGCam *pSbigCam;
    QImage image;
    QPixmap pm;
    imageInfo *ImgInfo;
};

#endif // IMAGEVIEW_H
