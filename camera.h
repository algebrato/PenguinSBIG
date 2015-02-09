#ifndef CAMERA_H
#define CAMERA_H
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include "ui_cameraControl.h"


namespace Ui {
class cameraControl;
}

class cameraControl : public QDialog
{
    Q_OBJECT

public:
    explicit cameraControl(QDialog *parent = 0);
    ~cameraControl();

private:
    Ui::cameraControl *ui;
};


#endif // CAMERA_H
