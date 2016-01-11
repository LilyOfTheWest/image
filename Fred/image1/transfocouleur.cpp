#include "transfocouleur.h"
#include "kernelconvmoyenneur.h"
#include "kernelconvbinomial.h"
#include "imageanalyse.h"
#include "qglobal.h"

TransfoCouleur::TransfoCouleur(QObject *parent) : QObject(parent)
{


}

QImage *TransfoCouleur::convertRgbToYuv(QImage *src)
{
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            r=get_YVal_Pixel_FromRgb(color);
            g=get_UVal_Pixel_FromRgb(color);
            b=get_VVal_Pixel_FromRgb(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return ret;
}

QImage *TransfoCouleur::convertYuvToRgb(QImage *src)
{
    QRgb color,color2;
    int r,g,b,alpha;
    QImage *ret = new QImage(src->width(),src->height(),src->format());
    for (int i=0; i< src->height() ; i++) {
        for (int j=0; j<src->width() ; j++) {
            color=src->pixel(j,i);
            r=get_RVal_Pixel_FromYuv(color);
            g=get_GVal_Pixel_FromYuv(color);
            b=get_BVal_Pixel_FromYuv(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return ret;
}

QImage *TransfoCouleur::flou(QImage *src)
{
    /* Test de base
    QImage *tmp = convertRgbToYuv(src);
    QImage *ret = convertYuvToRgb(tmp);

    int r,g,b,r2,g2,b2,r3,g3,b3,y,u,v;
    QRgb color1,color2,color3;
    color1 = src->pixel(206,156);
    r=qRed(color1);
    g=qGreen(color1);
    b=qBlue(color1);
    color2 = tmp->pixel(206,156);
    r2=qRed(color2);
    g2=qGreen(color2);
    b2=qBlue(color2);
    color3 = ret->pixel(206,156);
    r3=qRed(color3);
    g3=qGreen(color3);
    b3=qBlue(color3);*/

    /* Final test */
    // appel dialog pour properties /
    // new KernelConv()
    KernelConv *kMoy = new KernelConvBinomial(3);
    // new imageAnalyse -> imagris Y
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    // double **produitConv(double **src);
    imA->setImagris(kMoy->produitConv(imA->getImagris(), src->width(), src->height()));
    // -> nvle image flouter ; passe pictlabel ; undo + ;

    return imA->getDataRGB();
    // delete de tous les new créés.

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



int TransfoCouleur::get_YVal_Pixel_FromRgb(QRgb pixel_src)
{
    double tmp = 0;
    tmp = 0.299*qRed(pixel_src)+0.587*qGreen(pixel_src)+0.114*qBlue(pixel_src);
    int ret = normalizeColorValue(tmp);
    return ret;
}

int TransfoCouleur::get_UVal_Pixel_FromRgb(QRgb pixel_src)
{
    double tmp = 0;
    tmp = -0.168*qRed(pixel_src)-0.331*qGreen(pixel_src)+0.5*qBlue(pixel_src)+128;
    int ret = normalizeColorValue(tmp);
    return ret;
}

int TransfoCouleur::get_VVal_Pixel_FromRgb(QRgb pixel_src)
{
    double tmp = 0;
    tmp = 0.5*qRed(pixel_src)-0.4187*qGreen(pixel_src)-0.0813*qBlue(pixel_src)+128;
    int ret = normalizeColorValue(tmp);
    return ret;
}

int TransfoCouleur::get_RVal_Pixel_FromYuv(QRgb pixel_src)
{
    double tmp = 0;
    tmp = qRed(pixel_src)+1.402*(qBlue(pixel_src)-128);
    int ret = normalizeColorValue(tmp);
    return ret;
}

int TransfoCouleur::get_GVal_Pixel_FromYuv(QRgb pixel_src)
{
    double tmp = 0;
    tmp = qRed(pixel_src)-0.344136*(qGreen(pixel_src)-128)-0.714136*(qBlue(pixel_src)-128);
    int ret = normalizeColorValue(tmp);
    return ret;
}

int TransfoCouleur::get_BVal_Pixel_FromYuv(QRgb pixel_src)
{
    double tmp = 0;
    tmp = qRed(pixel_src)+1.772*(qGreen(pixel_src)-128);
    int ret = normalizeColorValue(tmp);
    return ret;
}

/*double ** TransfoCouleur::get_YBuf_image(QImage *src) {
    double ** M = new double*[src->height()];
    for(int i = 0 ; i<src->height() ; i++){
        M[i] = new double[src->width()];
    }
    return M;
}*/

int TransfoCouleur::normalizeColorValue(double val)
{
    int ret = qRound(val);
    if (ret < 0)
        ret=0;
    if (ret > 255)
        ret=255;
    return ret;
}
