#include "transfocouleur.h"

TransfoCouleur::TransfoCouleur(QObject *parent) : QObject(parent)
{


}

QImage *TransfoCouleur::inverseColor(QImage *src) {
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            r=255-qRed(color);
            g=255-qBlue(color);
            b=255-qGreen(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }

    return ret;
}



double TransfoCouleur::get_YVal_Pixel(QRgb *pixel_src)
{
    double ret = 0;
    ret = qRed(*pixel_src);
    return ret;
}

double TransfoCouleur::get_UVal_Pixel(QRgb *pixel_src)
{

}

double TransfoCouleur::get_VVal_Pixel(QRgb *pixel_src)
{

}

double ** TransfoCouleur::get_YBuf_image(QImage *src) {
    double ** M = new double*[src->height()];
    for(int i = 0 ; i<src->height() ; i++){
        M[i] = new double[src->width()];
    }
    return M;
}
