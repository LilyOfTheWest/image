#include "transfocouleur.h"
#include "kernelconvmoyenneur.h"
#include "kernelconvbinomial.h"
#include "imageanalyse.h"
#include "qglobal.h"
#include <math.h>

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
//            alpha=qAlpha(color);
            color2=qRgb(r,g,b);
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
//            alpha=qAlpha(color);
            color2=qRgb(r,g,b);
            ret->setPixel(j,i,color2);
        }
    }
    return ret;
}

QImage *TransfoCouleur::extractSubImage(QImage *src,QPoint *origin_select,QPoint *end_select)
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
    KernelConv *kMoy = new KernelConvBinomial(3);
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();

    imA->setImagris(kMoy->produitConv(imA->getImagris(), src->width(), src->height()));
    // -> nvle image flouter ; passe pictlabel ; undo + ;
    imA->fromYuvToRgb();

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
            //alpha=qAlpha(color);
            color2=qRgb(r,g,b);
            ret->setPixel(j,i,color2);
        }
    }
    return ret;
}

QImage * TransfoCouleur::rehaussement(QImage *src){
    int ordre = 3;
    // Filtre Passe Bas
    KernelConv *kerPB = new KernelConvBinomial(ordre);
    // On génère notre noyau impulsionnel
    KernelConv *kerImp = new KernelConv(ordre);
    kerImp->genereImp();
    // Filtre Passe Haut
    KernelConv *kerPH = new KernelConv(ordre);

    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            kerPH->setIndex((kerImp->getIndex(i,j))-(kerPB->getIndex(i,j)),i,j);
        }
    }

    /* Image filtrée passe haut ??? */
//    ImageAnalyse *imA = new ImageAnalyse(src);
//    imA->initYuvImagris();
//    imA->setImagris(kerPH->produitConv(imA->getImagris(), src->width(), src->height()));
//    imA->fromYuvToRgb();

    double alpha = 0.5;

    KernelConv *kerRH = new KernelConv(ordre);
    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            kerRH->setIndex((kerImp->getIndex(i,j)) + (alpha * kerPH->getIndex(i,j)),i,j);
        }
    }

    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();

    imA->setImagris(kerRH->produitConv(imA->getImagris(), src->width(), src->height()));
    imA->fromYuvToRgb();

    return imA->getDataRGB();
}

QImage * TransfoCouleur::contour(QImage *src){
    double ** norm = new double*[src->height()];
    for(int i=0;i<src->height();i++){
        norm[i] = new double[src->width()];
    }

    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    imA->calculgradient();

    for(int i=0;i<src->height();i++){
        for(int j=0;j<src->width();j++){
            norm[i][j]=sqrt(pow(imA->getDxIndex(i,j), 2)+pow(imA->getDyIndex(i,j), 2));
        }
    }

    imA->setImagris(norm);

    imA->fromYuvToRgb();

    return imA->getDataRGB();
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
