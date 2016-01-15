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
    mouseListenerState=0;
    principal = NULL;
    secondImg = NULL;
    firstImg = NULL;
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
    firstImgSelected=false;
    position_firstImg.setX(0);
    position_firstImg.setY(0);
    end_select = NULL;

    // Install background ; principal devient firstImg
    int totalWidth = firstImg->width() + src->width();
    int totalHeight = firstImg->height() + src->height();
    QRgb backgroundColor = qRgb(255,255,255);
    if (principal != NULL)
        delete principal;
    principal = new QImage(totalWidth,totalHeight,principal->format());
    for (int i=0; i< principal->height() ; i++) {
        for (int j=0; j<principal->width() ; j++) {
            principal->setPixel(j,i,backgroundColor);
        }
    }

    secondImg = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            secondImg->setPixel(j,i,src->pixel(j,i));
        }
    }
    position_secondImg.setX(0);
    position_secondImg.setY(0);
    mouse_origin.setX(0);
    mouse_origin.setY(0);
    mouseListenerState=21;
    drawImage();
}


void PictLabel::setPrincipal(QImage *src)
{
    // Install background ; principal devient firstImg
    QRgb backgroundColor = qRgb(255,255,255);
    if (principal != NULL)
        delete principal;
    principal = new QImage(src->width(),src->height(),src->format());
    firstImg = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            firstImg->setPixel(j,i,src->pixel(j,i));
            principal->setPixel(j,i,backgroundColor);
        }
    }
    drawImage();
}

QImage *PictLabel::getPrincipal()
{
    return firstImg;

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
    QPoint mouse_position = resizeWithScaling(event->pos());
    switch(mouseListenerState){
    case 10: // Pipette
        //colorPicked = principal->pixel(mouse_position);
        //if (isPicked(resizeWithScaling(event->pos()),firstImg,&position_firstImg)==true) {

        //}
        signalNewPixelPicked();
        break;
    case 11: // Select
        origin_select = mouse_position;
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(event->pos(), QSize()));
        rubberBand->show();
        break;
    case 12: // Deplace première image
        mouse_origin = resizeWithScaling(event->pos());
        break;
    case 18: // Deplace seconde image suite Couper/Copier
        mouse_origin = resizeWithScaling(event->pos());
        break;
    case 21: // Deplace seconde image
        mouse_origin = resizeWithScaling(event->pos());
        break;
    case 22: // Deplace première image
        mouse_origin = resizeWithScaling(event->pos());
        break;
    }
}

void PictLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    QPoint *mouse_end = new QPoint(resizeWithScaling(event->pos()));
    switch(mouseListenerState){
    case 10:

        break;
    case 11:
        setSelection(event);
        break;
    case 12:
        moveSelection(mouse_end,firstImg,position_firstImg);
        break;
    case 18:
        moveSelection(mouse_end,secondImg,position_secondImg);
        break;
    case 21:
        moveSelection(mouse_end,secondImg,position_secondImg);
        break;
    case 22:
        moveSelection(mouse_end,firstImg,position_firstImg);
        break;
    }
}

void PictLabel::setSelection(QMouseEvent * event)
{
    end_select = new QPoint(resizeWithScaling(event->pos()));
    rubberBand->hide();
    secondImg=NULL;
    delete rubberBand;
    drawImage();
}

void PictLabel::pasteSelection()
{
    if (end_select != NULL) {
        TransfoCouleur *tc = new TransfoCouleur;
        secondImg =tc->extractSubImage(firstImg,&origin_select,end_select);
        position_secondImg.setX(0);
        position_secondImg.setY(0);
        drawImage();
        mouseListenerState=18;
    }
}

bool PictLabel::isPicked(QPoint mousePosition,QImage *imgToMove,QPoint *positionRelative)
{
    return false;
}

void PictLabel::moveSelection(QPoint *mouse_end,QImage *imgToMove,QPoint &positionRelative)
{
    int x_pos = positionRelative.x() + mouse_end->x() - mouse_origin.x();
    int y_pos = positionRelative.y() + mouse_end->y() - mouse_origin.y();
    if (x_pos < -imgToMove->width())
        x_pos = 3-imgToMove->width();
    if (y_pos < -imgToMove->height())
        y_pos = 3-imgToMove->height();
    int xMax = principal->width()-3;
    int yMax = principal->height()-3;
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
    if (firstImg != NULL)
    {
        const QImage imageFirstFirstImg = *firstImg;
        p.drawPixmap(position_firstImg.x(),
                     position_firstImg.y(),
                     firstImg->width(),
                     firstImg->height(),
                     QPixmap::fromImage(imageFirstFirstImg));
    }

    if (end_select != NULL)
        p.drawRect(QRect(origin_select,*end_select));
    if (secondImg != NULL)
    {
        const QImage imageSecondImge = *secondImg;
        p.drawPixmap(position_secondImg.x(),
                     position_secondImg.y(),
                     secondImg->width(),
                     secondImg->height(),
                     QPixmap::fromImage(imageSecondImge));
    }
    p.end();
    const QImage image = image2;
    //    this->setPixmap(QPixmap::fromImage(image));
    this->setPixmap(QPixmap::fromImage(image));
}