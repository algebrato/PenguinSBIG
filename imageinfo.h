#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QWidget>
#include "csbigcam.h"
#include "csbigimg.h"

namespace Ui {
class imageInfo;
}

class imageInfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit imageInfo(QWidget *parent = 0);
    ~imageInfo();

    void setImage(CSBIGImg *image);

private slots:
    void loadHeader();




    
private:
    Ui::imageInfo *ui;
    CSBIGImg *pSbigImage;


};

#endif // IMAGEINFO_H
