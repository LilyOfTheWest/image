#include "transfocouleur.h"
#include "qglobal.h"

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
            g=255-qGreen(color);
            b=255-qBlue(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return ret;
}



int TransfoCouleur::get_YVal_Pixel(QRgb pixel_src)
{
    double tmp = 0;
    tmp = 0.299*qRed(pixel_src)+0.587*qGreen(pixel_src)+0.114*qBlue(pixel_src);
    int ret = qRound(tmp);
    return ret;
}

int TransfoCouleur::get_UVal_Pixel(QRgb pixel_src)
{
    double tmp = 0;
    tmp = -0.168*qRed(pixel_src)-0.331*qGreen(pixel_src)+0.5*qBlue(pixel_src)+128;
    int ret = qRound(tmp);
    return ret;
}

int TransfoCouleur::get_VVal_Pixel(QRgb pixel_src)
{
    double tmp = 0;
    tmp = 0.5*qRed(pixel_src)-0.4187*qGreen(pixel_src)-0.0813*qBlue(pixel_src)+128;
    int ret = qRound(tmp);
    return ret;
}

/*double ** TransfoCouleur::get_YBuf_image(QImage *src) {
    double ** M = new double*[src->height()];
    for(int i = 0 ; i<src->height() ; i++){
        M[i] = new double[src->width()];
    }
    return M;
}*/
