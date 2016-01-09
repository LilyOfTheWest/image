#ifndef PICTLABEL_H
#define PICTLABEL_H

#include <QWidget>

#include <QWidget>
#include <QLabel>
#include <QRubberBand>
#include <QImage>
#include <QStack>
#include "TransfoCouleur.h"

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
    void setPrincipal(QImage *principal);
    QImage *getPrincipal();
    QRgb getColorPicked();
    QPoint getPixelPicked();
    void setMouseListenerState(int mouseListenerStateVal);

signals:
    void signalNewPixelPicked();

public slots:

protected:
    /*virtual void enterEvent ( QEvent * event ) Q_DECL_OVERRIDE;
    virtual void leaveEvent ( QEvent * event ) Q_DECL_OVERRIDE;*/
    virtual void mouseMoveEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void mousePressEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent ( QMouseEvent * event ) Q_DECL_OVERRIDE;
    void saveTemp();
    void drawSelection ( QMouseEvent * event );

    QRubberBand *rubberBand;
    QPoint origin_select;
    QPoint end_select;
    QStack<QImage> *undo;
    QImage *principal;
    QImage *second;
    QPoint origin_position_relative_second;
    int mouseListenerState;
    QRgb colorPicked;
};

#endif // PICTLABEL_H
