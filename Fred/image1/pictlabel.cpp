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
    fusion1 = NULL;
    end_select = NULL;
    scaleFactor = 1;
    setCouperMode(false);
}

PictLabel::~PictLabel()
{
    delete principal;
}

void PictLabel::addImageToMerge(QImage *src)
{
    fusion1=principal;
    fusion1Selected=false;
    origin_position_relative_fusion1.setX(0);
    origin_position_relative_fusion1.setY(0);
    end_select = NULL;

    // Install background ; principal devient fusion1
    int totalWidth = fusion1->width() + src->width();
    int totalHeight = fusion1->height() + src->height();
    QRgb backgroundColor = qRgb(255,255,255);
    principal = new QImage(totalWidth,totalHeight,principal->format());
    for (int i=0; i< principal->height() ; i++) {
        for (int j=0; j<principal->width() ; j++) {
            principal->setPixel(j,i,backgroundColor);
        }
    }

    second = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            second->setPixel(j,i,src->pixel(j,i));
        }
    }
    origin_position_relative_second.setX(0);
    origin_position_relative_second.setY(0);
    mouse_origin.setX(0);
    mouse_origin.setY(0);
    mouseListenerState=21;
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
    drawImage();
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
        //rubberBand->setGeometry(QRect(resizeWithScaling(origin_select), event->pos()).normalized());
        rubberBand->setGeometry(QRect(rubberBand->geometry().topLeft(), event->pos()).normalized());
        break;
    case 12:
        break;
    }


}

void PictLabel::mousePressEvent ( QMouseEvent * event )
{
    switch(mouseListenerState){
    case 10:
        mouse_origin = resizeWithScaling(event->pos());
        colorPicked = principal->pixel(mouse_origin);
        signalNewPixelPicked();
        break;
    case 11:
        origin_select = resizeWithScaling(event->pos());
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(event->pos(), QSize()));
        rubberBand->show();
        break;
    case 12:
        mouse_origin = resizeWithScaling(event->pos());
        break;
    case 21:
        mouse_origin = resizeWithScaling(event->pos());
        break;
    case 22:
        mouse_origin = resizeWithScaling(event->pos());
        break;
    }
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
        moveSelection(event,second,origin_position_relative_second);
        break;
    case 21:
        moveSelection(event,second,origin_position_relative_second);
        break;
    case 22:
        moveSelection(event,fusion1,origin_position_relative_fusion1);
        break;
    }
}

void PictLabel::setSelection(QMouseEvent * event)
{
    end_select = new QPoint(resizeWithScaling(event->pos()));
    rubberBand->hide();
    TransfoCouleur *tc = new TransfoCouleur;
    second =tc->extractSubImage(principal,&origin_select,end_select);
    origin_position_relative_second.setX(0);
    origin_position_relative_second.setY(0);
    drawImage();
    delete rubberBand;
}

void PictLabel::moveSelection(QMouseEvent * event,QImage *imgToMove,QPoint &positionRelative)
{
    mouse_end = new QPoint(resizeWithScaling(event->pos()));
    int x_pos = positionRelative.x() + mouse_end->x() - mouse_origin.x();
    int y_pos = positionRelative.y() + mouse_end->y() - mouse_origin.y();
    if (x_pos < 0)
        x_pos = 0;
    if (y_pos < 0)
        y_pos = 0;
    int xMax = principal->width()-imgToMove->width();
    int yMax = principal->height()-imgToMove->height();
    if (x_pos > xMax)
        x_pos = xMax;
    if (y_pos > yMax)
        y_pos = yMax;
    positionRelative.setX(x_pos);
    positionRelative.setY(y_pos);
    drawImage();
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
    return mouse_origin;
}

void PictLabel::setScaleFactor(double scaleFactor)
{
    this->scaleFactor = scaleFactor;
}

QPoint PictLabel::resizeWithScaling(QPoint mousePointed)
{
    QPoint ret;
    int scaled = mousePointed.x()/scaleFactor;
    ret.setX(scaled);
    scaled = mousePointed.y()/scaleFactor;
    ret.setY(scaled);
    return ret;
}

void PictLabel::setCouperMode(bool couperMode)
{
    this->couperMode=couperMode;
}

void PictLabel::drawImage()
{
    QPainter p;
    //const QPixmap *dd = this->pixmap();
    QImage image2=*principal;//dd->toImage();
    p.begin(&image2);
    p.setPen(QColor(Qt::color0));
    p.setBrush(Qt::NoBrush);
    if (fusion1 != NULL)
    {
        const QImage imageFirstFusion1 = *fusion1;
        p.drawPixmap(origin_position_relative_fusion1.x(),
                     origin_position_relative_fusion1.y(),
                     fusion1->width(),
                     fusion1->height(),
                     QPixmap::fromImage(imageFirstFusion1));
    }

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
