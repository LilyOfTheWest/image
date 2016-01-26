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
#include "seamcarver.h"
#include "kernelconv.h"

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
    QImage *getImage1();
    QImage *getImage2();
    void closeImages();
    void setSelectedImage(QImage *selectImg);
    QRgb getColorPicked();
    QPoint getPixelPicked();
    void setScaleFactor(double scaleFactor);
    int getMouseListenerState();
    void setMouseListenerState(int mouseListenerStateVal);
    void setCouperMode(bool couperMode);
    void setSecondImgAsSelect(bool secondImgAsSelect);
    bool getSecondImgAsSelect();
    int getAlphaImg1();
    void setAlphaImg1(int value);
    int getAlphaImg2();
    void setAlphaImg2(int value);
    void pasteSelection();
    void validateTransfo();
    QString getNomImg();
    void setNomImg(QString nom);
    SeamCarver *getSeamCarver();
    void setNbSeamLinesToDisplay(int value);
    void setSeamLinesDisplayMode(bool value);
    bool getUndoVisibility();
    bool getValidateCancelVisibility();
    bool getCutCopyVisibility();
    void resizeSelectedImage(int newWidth, int newHeight);

signals:
    void signalNewPixelPicked();
    void signalResizingRequired();
    void signalRedisplayRequired();
    void signalUndoVivibility();
    void signalValidateCancelVivibility();

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
    void moveSelection(QPoint *mouse_end,QImage *imgToMove,QPoint &positionRelative);
    QPoint resizeWithScaling(QPoint mousePointed);
    void setPrincipalWithoutPrevSaved(QImage *src);

    QRubberBand *rubberBand;
    ImageResizer *resizer;
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
    QString nomImg;
    double scaleFactor;
    bool bCouperMode;
    bool bFirstImgSelected;
    bool bVisuSeamLines;
    int nbSeamLinesToDisplay;
    int alphaImg1;
    int alphaImg2;
    SeamCarver *sc;
    bool bValidateCancelVisibility;
    KernelConv *filtrePerso;
};

#endif // PICTLABEL_H
