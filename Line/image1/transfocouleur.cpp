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
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            ret->setPixel(j,i,color2);
        }
    }
    return ret;
}

QImage * TransfoCouleur::rehaussement(QImage *src, double alpha){
    int ordre = 3;
    // Filtre Passe Bas
    KernelConv *kerPB = new KernelConvBinomial(ordre);
    // On génère notre noyau impulsionnel
    KernelConv *kerImp = new KernelConv(ordre);
    kerImp->genereImp();
    // Filtre Passe Haut
    KernelConv *kerPH = new KernelConv(ordre);
    double n, imp;

    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            imp = kerImp->getIndex(i,j);
            n = imp-(kerPB->getIndex(i,j))/(kerPB->getCoef());
            kerPH->setIndex(n,i,j);
        }
    }

    /* Image filtrée passe haut ??? */
//    ImageAnalyse *imA = new ImageAnalyse(src);
//    imA->initYuvImagris();
//    imA->setImagris(kerPH->produitConv(imA->getImagris(), src->width(), src->height()));
//    imA->fromYuvToRgb();

    KernelConv *kerRH = new KernelConv(ordre);

    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            n = (kerImp->getIndex(i,j)) + (alpha * kerPH->getIndex(i,j));
            kerRH->setIndex(n,i,j);
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

QImage *TransfoCouleur::gris(QImage *src){
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    QRgb color, color2;
    int y, alpha;
    QImage *gris = new QImage(src->width(),src->height(),src->format());
    double ** imaGris = imA->getImagris();
    for(int i=0;i<gris->height();i++){
        for(int j=0;j<gris->width();j++){
            color=src->pixel(j,i);
            y = imaGris[i][j];
            alpha=qAlpha(color);
            color2=qRgba(y,y,y,alpha);
            gris->setPixel(j,i,color2);
        }
    }
    return gris;
}

QImage *TransfoCouleur::etalement(QImage *src, double alpha, double beta){
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    int min = imA->min();
    int max = imA->max();
    double pic_min = beta * min;
    double pic_max =(1/alpha)*max;
    double ** pic = imA->getImagris();
    double ** ret = new double *[src->height()];
    for(int i=0;i<src->height();i++){
        ret[i]=new double[src->width()];
    }

    for(int i=0;i<src->height();i++){
        for(int j=0;j<src->width();j++){
            ret[i][j] = normalizeColorValue(255*((pic[i][j]-pic_min)/(pic_max/pic_min)));
        }
    }

    imA->setImagris(ret);
    imA->fromYuvToRgb();

    return imA->getDataRGB();
}

QImage *TransfoCouleur::egalisation(QImage *src){
    int nbr_pixels = src->height()*src->width();
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    imA->calculHisto();
    int **hYUV = imA->getHistoYuv();
    int *hY = hYUV[0];
    int *phi = new int[256];
    int *sum = new int[256];
    int p;
    sum=imA->cumsum(hY);
    for(int i=0;i<256;i++){
        p = qRound(255.0/nbr_pixels*(sum[i]));
        phi[i] = p;
    }
    double ** yuv=imA->getImagris();
    int y;
    for(int i=0;i<src->height();i++){
        for(int j=0;j<src->width();j++){
            y=qRound(yuv[i][j]);
            yuv[i][j]=phi[y];
        }
    }

    imA->setImagris(yuv);
    imA->fromYuvToRgb();

    return imA->getDataRGB();
}

void TransfoCouleur::histogramme(QImage *src,int mode){
    ImageAnalyse *imA = new ImageAnalyse(src);
    imA->initYuvImagris();
    /* TEST HISTOGRAMMES */
    imA->calculHisto();
    imA->histoToPoints(mode);
    imA->afficheHisto(mode);
    /* FIN TEST HISTOGRAMMES */
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

QRgb TransfoCouleur::changeAlphaColor(QRgb color,int alpha)
{
    return color;

}
