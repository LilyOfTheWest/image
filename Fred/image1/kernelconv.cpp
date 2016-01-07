#include "kernelconv.h"
#include <malloc.h>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QRgb>

KernelConv::KernelConv(QObject *parent) : QObject(parent)
{
    w=3;
    h=3;
    buf=(int*) malloc(w*h*sizeof(int));
    int i,j;
    for (i=0; i<h ; i++)
        for (j=0; j<w ; j++)
            buf[i*w+j]=1;

}

QImage KernelConv::produitConv(QImage *src) {
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            // A faire
        }
    }
    return *ret;
}
