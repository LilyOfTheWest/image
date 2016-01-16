#include "imageresizer.h"

ImageResizer::ImageResizer(QObject *parent) : QObject(parent)
{

}

QImage *ImageResizer::extractSubImage(QImage *src,QPoint *origin_select,QPoint *end_select)
{
    int x_min = qMin(origin_select->x(),end_select->x());
    int x_max = qMax(origin_select->x(),end_select->x());
    int y_min = qMin(origin_select->y(),end_select->y());
    int y_max = qMax(origin_select->y(),end_select->y());
    QRgb color;
    int width = x_max-x_min;
    int height = y_max-y_min;
    QImage *ret = new QImage(width,height,src->format());
    for (int i=0; i<ret->height()  ; i++) {
        for (int j=0; j<ret->width(); j++) {
            color=src->pixel(j+x_min,i+y_min);
            ret->setPixel(j,i,color);
        }
    }
    return ret;
}

QImage *ImageResizer::rotateImage90(QImage *src,bool horaire)
{
    QRgb color;
    QImage *ret = new QImage(src->height(),src->width(),src->format());
    for (int i=0; i<src->height()  ; i++) {
        for (int j=0; j<src->width(); j++) {
            color = src->pixel(j,i);
            if (horaire == true)
                ret->setPixel(i,src->width()-1-j,color);
            else
                ret->setPixel(src->height()-1-i,j,color);
        }
    }
    return ret;
}

QImage *ImageResizer::rotateImage180(QImage *src)
{
    QRgb color;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i<src->height()  ; i++) {
        for (int j=0; j<src->width(); j++) {
            color = src->pixel(j,i);
            ret->setPixel(src->width()-1-j,src->height()-1-i,color);
        }
    }
    return ret;
}

