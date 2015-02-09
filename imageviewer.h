#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H
#include <QWidget>
#include <QImage>
#include <QScrollArea>

/*#include "csbigimg.h"
#include <QWidget>
#include <QImage>
#include <qscrollview.h>
#include <QScrollArea>


class QLabel;
class QMenuBar;
class QPopupMenu;
class MyScroller;
*/
class imageViewer : public QWidget
{
    Q_OBJECT
public:
    imageViewer(QWidget *parent=0, const char *name=0, int wFlags=0);
    ~imageViewer();

  /*  Q_OBJECT
public:
    imageViewer(QWidget *parent=0, const char *name=0, int wFlags=0);
    ~imageViewer();
    bool loadImage(const QString& , bool bAutoContrast = FALSE);
    void setImage(CSBIGImg *pImg);
protected:
    void resizeEvent(QResizeEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    void scale();
    bool convertEvent( QMouseEvent* e, int& x, int& y);
    CSBIGImg *pSbigImg;
    QString     filename;
    QImage image;
    QPixmap pm;
    MyScroller *msp;
    QMenuBar   *menubar;
    QPopupMenu  *file;
    QPopupMenu   *savepixmap;
    QPopupMenu  *edit;
    QPopupMenu *zoom;
    QWidget    *helpmsg;
    QLabel     *status;
    int         sp, sc, zz, ac, iv, si, sii;
    int pickx, picky;
    int imgZoom;
    bool videoInverted;
    void updateStatus();
    void setMenuItemFlags();
    bool  reconvertImage();
    void updateImageBits();
    void deltaZoom();
    void getZoomFactors(int &num, int&den);
    void createPalette();

private slots:
    void hFlip();
    void vFlip();
    void rot180();
    void showContrast();
    void showImageInfo();
    void zoom4To1();
    void zoom2To1();
    void zoom1To1();
    void zoom1To2();
    void zoom1To4();
    void autoContrast();
    void inverseVideo();
    void newWindow();
    void openFile();
    void savePixmap(int);
    void saveImage();
    void giveHelp();
    */
};

#endif // IMAGEVIEWER_H

