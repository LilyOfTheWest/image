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
    principal = NULL;
    second = NULL;
    end_select = NULL;
}

PictLabel::~PictLabel()
{
    delete principal;
}

void PictLabel::addImage(QImage *src)
{
    QImage *image = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            image->setPixel(j,i,src->pixel(j,i));
        }
    }
    if (principal == NULL)
        principal = image;
    else
    {
        second = image;
        origin_position_relative_second.setX(0);
        origin_position_relative_second.setY(0);
        mouse_origin.setX(0);
        mouse_origin.setY(0);
        mouseListenerState=12;
    }
    drawImage();
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
        mouse_origin = event->pos();
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
        origin_select = event->pos();
        break;
    }
}

void PictLabel::drawImage()
{
    QPainter p;
    //const QPixmap *dd = this->pixmap();
    QImage image2=*principal;//dd->toImage();
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    if (end_select != NULL)
        p.drawRect(QRect(origin_select,*end_select));
    if (second != NULL)
    {
        const QImage imageSeconde = *second;
        p.drawPixmap(origin_position_relative_second.x(),
                     origin_position_relative_second.y(),
                     second->width(),
                     second->height(),
                     QPixmap::fromImage(imageSeconde));
    }
    p.end();
    const QImage image = image2;
    //    this->setPixmap(QPixmap::fromImage(image));
    this->setPixmap(QPixmap::fromImage(image));
}

/*void PictLabel::drawSelection ()
{
    QPainter p;
    //const QPixmap *dd = this->pixmap();
    QImage image2=*principal;//dd->toImage();
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    if (end_select != NULL)
        p.drawRect(QRect(origin_select,*end_select));
    if (second != NULL)
    {
        const QImage imageSeconde = *second;
        p.drawPixmap(origin_position_relative_second.x(),
                     origin_position_relative_second.y(),
                     second->width(),
                     second->height(),
                     QPixmap::fromImage(imageSeconde));
    }
    p.end();
    const QImage image = image2;
    //    this->setPixmap(QPixmap::fromImage(image));
    this->setPixmap(QPixmap::fromImage(image));
}*/

void PictLabel::setSelection(QMouseEvent * event)
{
    end_select = new QPoint(event->pos());
    rubberBand->hide();
    mouseListenerState=12;
    TransfoCouleur *tc = new TransfoCouleur;
    second =tc->extractSubImage(principal,&origin_select,end_select);
    origin_position_relative_second.setX(0);
    origin_position_relative_second.setY(0);
    drawImage();
    delete rubberBand;
}

void PictLabel::moveSelection(QMouseEvent * event)
{
    mouse_end = new QPoint(event->pos());
    int x_pos = origin_position_relative_second.x() + mouse_end->x() - mouse_origin.x();
    int y_pos = origin_position_relative_second.y() + mouse_end->y() - mouse_origin.y();
    if (x_pos < 0)
        x_pos = 0;
    if (y_pos < 0)
        y_pos = 0;
    origin_position_relative_second.setX(x_pos);
    origin_position_relative_second.setY(y_pos);
    drawImage();
}

void PictLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    switch(mouseListenerState){
    case 10:

        break;
    case 11:
        setSelection(event);
        break;

    case 12:
        moveSelection(event);
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

