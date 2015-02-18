#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QWidget>

namespace Ui {
class imageInfo;
}

class imageInfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit imageInfo(QWidget *parent = 0);
    ~imageInfo();
    
private:
    Ui::imageInfo *ui;

};

#endif // IMAGEINFO_H
