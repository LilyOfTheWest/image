#include "qkernelconv.h"
#include <malloc.h>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QRgb>

QKernelConv::QKernelConv(QObject *parent) : QObject(parent)
{
    w=3;
    h=3;
    buf=(int*) malloc(w*h*sizeof(int));
    int i,j;
    for (i=0; i<h ; i++)
        for (j=0; j<w ; j++)
            buf[i*w+j]=1;

}

QImage QKernelConv::inverseColor(QImage *src) {
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            r=qRed(color);
            g=qBlue(color);
            b=qGreen(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return *ret;
}

QImage QKernelConv::produitConv(QImage *src) {
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            r=qRed(color);
            g=qBlue(color);
            b=qGreen(color);
            alpha=qAlpha(color);
            if ((i < 100) || (i>110))
                alpha=0;

            color2=qRgba(255,255,255,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return *ret;
}

QImage QKernelConv::calque(QImage *src) {
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            r=qRed(color);
            g=qBlue(color);
            b=qGreen(color);
            alpha=qAlpha(color);
            if ((j < 3) || (j>60))
                color2=qRgba(0,0,0,0);
            else
                color2=qRgba(r,g,b,alpha);

            //color2=qRgba(0,0,0,0);
            //color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return *ret;
}
