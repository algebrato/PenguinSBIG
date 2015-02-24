#ifndef CAMERA_H
#define CAMERA_H
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include "ui_cameraControl.h"
#include "csbigcam.h"


namespace Ui {
class cameraControl;
}

class cameraControl : public QDialog
{
    Q_OBJECT

public:
    explicit cameraControl(QDialog *parent = 0);
    ~cameraControl();

private slots:
    void setCam(CSBIGCam *pCam);
    void updateTemp();
    void setTemp();

private:
    Ui::cameraControl *ui;
    CSBIGCam *pSbigCam;
};


#endif // CAMERA_H
