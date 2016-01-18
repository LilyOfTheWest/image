#ifndef PICTLABEL_H
#define PICTLABEL_H

#include <QWidget>

#include <QWidget>
#include <QLabel>
#include <QRubberBand>
#include <QImage>
#include <QStack>
#include "transfocouleur.h"
#include "imageresizer.h"

/*QT_BEGIN_NAMESPACE
class QWidget;
class QLabel;
class QRubberBand;
class QImage;
//class QStack;
QT_END_NAMESPACE*/

class PictLabel : public QLabel
{
    Q_OBJECT

public:
    explicit PictLabel(QWidget *parent = 0);
    ~PictLabel();
    void undoLast();
    void setInitialContext();
    void setPrincipal(QImage *principal);
    void addImageToMerge(QImage *src);
    void drawImage();
    QImage *getPrincipal();
    QImage *getSelectedImage();
    void setSelectedImage(QImage *selectImg);
    QRgb getColorPicked();
    QPoint getPixelPicked();
    void setScaleFactor(double scaleFactor);
    void setMouseListenerState(int mouseListenerStateVal);
    void setCouperMode(bool couperMode);
    void pasteSelection();
    void validateTransfo();

signals:
    void signalNewPixelPicked();
    void signalResizingRequired();

public slots:

protected:
    /*virtual void enterEvent ( QEvent * event ) Q_DECL_OVERRIDE;
    virtual void leaveEvent ( QEvent * event ) Q_DECL_OVERRIDE;*/
    virtual void mouseMoveEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void mousePressEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    void saveTemp(QImage *svgFirstImg);
    void drawSelection ();
    void setSelection(QMouseEvent * event);
    bool isPicked(QPoint mousePosition,QImage *imgToMove,QPoint *positionRelative);
    void moveSelection(QPoint *mouse_end,QImage *imgToMove,QPoint &positionRelative);
    QPoint resizeWithScaling(QPoint mousePointed);
    void setPrincipalWithoutPrevSaved(QImage *src);

    QRubberBand *rubberBand;
    QPoint origin_select;
    QPoint *end_select;
    QPoint mouse_origin;
    QPoint *mouse_end;
    QList<QImage *> undo;
    QImage *principal;
    QImage *firstImg;
    QImage *secondImg;
    QImage *selectedImg;
    QPoint position_firstImg;
    QPoint position_secondImg;
    int mouseListenerState;
    QRgb colorPicked;
    double scaleFactor;
    bool couperMode;
    bool firstImgSelected;
};

#endif // PICTLABEL_H
