#include "imagebuf.h"

void ImageBuf::inverseColor()
{
    QRgb color,color2;
    int r,g,b,alpha;
    for (int i=0; i< this->height() ; i++) {
        for (int j=0; j< this->width() ; j++) {
            color=src->pixel(j,i);
            r=255-qRed(color);
            g=255-qBlue(color);
            b=255-qGreen(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            this->setPixel(j,i,color2);
        }
    }
}

