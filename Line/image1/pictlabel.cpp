#include "pictlabel.h"
#include <QMouseEvent>
#include <QRubberBand>
#include <QPainter>
#include <QImage>
#include <QRgb>

PictLabel::PictLabel(QWidget *parent) :
    QLabel(parent),colorPicked(qRgb(0,0,0))
{
    origin_select.setX(0);
    origin_select.setY(0);
    mouseListenerState=11;
}

PictLabel::~PictLabel()
{
    delete principal;
}

void PictLabel::setPrincipal(QImage *src)
{
    principal = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            principal->setPixel(j,i,src->pixel(j,i));
        }
    }
}

QImage *PictLabel::getPrincipal()
{
    return principal;

}

/*void PictLabel::enterEvent ( QEvent * event )
{
}

void PictLabel::leaveEvent ( QEvent * event )
{
}*/

void PictLabel::mouseMoveEvent ( QMouseEvent * event )
{
    switch(mouseListenerState){
    case 10:

        break;
    case 11:
        rubberBand->setGeometry(QRect(origin_select, event->pos()).normalized());
        break;
    case 12:
        break;
    }


}

void PictLabel::mousePressEvent ( QMouseEvent * event )
{
    switch(mouseListenerState){
    case 10:
        origin_select = event->pos();
        colorPicked = principal->pixel(origin_select);
        signalNewPixelPicked();
        break;
    case 11:
        origin_select = event->pos();
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(origin_select, QSize()));
        rubberBand->show();
        break;
    case 12:
        break;
    }
}

void PictLabel::drawSelection ( QMouseEvent * event )
{
    end_select = event->pos();
    rubberBand->hide();
    delete rubberBand;
    QPainter p;
    const QPixmap *dd = this->pixmap();
    QImage image2=dd->toImage();
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    p.drawRect(QRect(origin_select,end_select));
    p.end();
    const QImage image = image2;
    this->setPixmap(QPixmap::fromImage(image));
}

void PictLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    switch(mouseListenerState){
    case 10:

        break;
    case 11:
        drawSelection (event);
        break;

    case 12:

        break;

    }
}

void PictLabel::saveTemp() {
    if (undo == NULL)
            undo = new QStack<QImage>();
    const QPixmap *dd = this->pixmap();
    QImage image2=dd->toImage();
    undo->push(image2);
}

void PictLabel::undoLast() {
    if (undo == NULL)
            return;
    if (undo->isEmpty())
            return;
    const QImage image = undo->pop();
    this->setPixmap(QPixmap::fromImage(image));
}

void PictLabel::setMouseListenerState(int mouseListenerStateVal)
{
    mouseListenerState=mouseListenerStateVal;
}

QRgb PictLabel::getColorPicked()
{
    return colorPicked;
}

QPoint PictLabel::getPixelPicked()
{
    return origin_select;
}

