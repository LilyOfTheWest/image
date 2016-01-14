#include "imageanalyse.h"
#include "transfocouleur.h"
#include "qglobal.h"
#include "kernelconv.h"

ImageAnalyse::ImageAnalyse(QImage *qimageRgbSrc,QObject *parent) : QObject(parent)//,dataRGB(qimageRgbSrc)
{
    QRgb color,color2;
    dataRGB = new QImage(qimageRgbSrc->width(),qimageRgbSrc->height(),qimageRgbSrc->format());
    for (int i=0; i< qimageRgbSrc->height() ; i++) {
        for (int j=0; j<qimageRgbSrc->width() ; j++) {
            color=qimageRgbSrc->pixel(j,i);
            color2=qRgba(qRed(color),qGreen(color),qBlue(color),qAlpha(color));
            dataRGB->setPixel(j,i,color2);
        }
    }
    tc = new TransfoCouleur;
//    dataYUV=NULL;
//    d_x=NULL;
//    d_y=NULL;
}

ImageAnalyse::~ImageAnalyse()
{

}

void ImageAnalyse::fromYuvToRgb(){
    dataRGB = tc->convertYuvToRgb(dataYUV);
}

void ImageAnalyse::initYuvImagris()
{
    QRgb color;
    int r;
    int g,b,r2,g2,b2,y,u,v;
    double point;
    QRgb color1,color2;


    dataYUV = tc->convertRgbToYuv(dataRGB);
    color1 = dataYUV->pixel(216,156);
    r=qRed(color1);
    g=qGreen(color1);
    b=qBlue(color1);
    imagris = new double*[dataYUV->height()];
    for (int i=0; i< dataYUV->height() ; i++) {
        imagris[i] = new double[dataYUV->width()];
        for (int j=0; j<dataYUV->width() ; j++) {
            color=dataYUV->pixel(j,i);
            r=qRed(color);
            imagris[i][j] = r;
            point = imagris[i][j];
            r = qRed(color);
        }
    }

    color2 = dataYUV->pixel(216,156);
    r2=qRed(color2);
    g2=qGreen(color2);
    b2=qBlue(color2);

}

void ImageAnalyse::calculHisto()
{

}

void ImageAnalyse::calculgradient(){
    int ordre;
    KernelConv *SobelX = new KernelConv(ordre);
    KernelConv *SobelY = new KernelConv(ordre);

    SobelX->genereSobelHori();
    SobelY->genereSobelVert();

    d_x = new double *[dataRGB->height()];
    d_y = new double *[dataRGB->height()];

    for(int i=0;i<dataRGB->height();i++){
        d_x[i] = new double[dataRGB->width()];
        d_y[i] = new double[dataRGB->width()];
    }

    d_x = SobelX->produitConv(imagris, dataRGB->width(), dataRGB->height());
    d_y = SobelY->produitConv(imagris, dataRGB->width(), dataRGB->height());
}

QImage * ImageAnalyse::getDataRGB(){
    return dataRGB;
}

void ImageAnalyse::setDataRGB(QImage *i){
    dataRGB = i;
}

QImage * ImageAnalyse::getDataYUV(){
    return dataYUV;
}

void ImageAnalyse::setDataYUV(QImage *i){
    dataYUV = i;
}

double ** ImageAnalyse::getImagris(){
    return imagris;
}

void ImageAnalyse::setImagris(double ** img){

    double pt1, pt2;
    imagris = new double*[dataYUV->height()];
    for (int i=0; i< dataYUV->height() ; i++) {
        imagris[i] = new double[dataYUV->width()];
        for (int j=0; j<dataYUV->width() ; j++) {
            pt2=img[i][j];
            imagris[i][j]=img[i][j];
            pt1 = imagris[i][j];
            pt1=pt2;
        }
    }

    QRgb color,color2;

    int r;
    int g,b,r2,g2,b2;
    double point;
    QRgb color1;
    color1 = dataYUV->pixel(216,156);
    r=qRed(color1);
    g=qGreen(color1);
    b=qBlue(color1);


    int y, u, v,alpha;
    for (int i=0; i< dataYUV->height() ; i++) {
        for (int j=0; j<dataYUV->width() ; j++) {
            color=dataYUV->pixel(j,i);
            point = imagris[i][j];
            y=tc->normalizeColorValue(point);
            u=qGreen(color);
            v=qBlue(color);
            //alpha=qAlpha(color);
            color2=qRgb(y,u,v);
            dataYUV->setPixel(j,i,color2);
        }
    }

    color2 = dataYUV->pixel(216,156);
    r2=qRed(color2);
    g2=qGreen(color2);
    b2=qBlue(color2);
}

double ** ImageAnalyse::getD_x(){
    return d_x;
}

void ImageAnalyse::setD_x(double ** dx){
    d_x = dx;
}

double ** ImageAnalyse::getD_y(){
    return d_y;
}

void ImageAnalyse::setD_y(double ** dy){
    d_y = dy;
}

double ImageAnalyse::getDxIndex(int x, int y){
    return d_x[x][y];
}

double ImageAnalyse::getDyIndex(int x, int y){
    return d_y[x][y];
}

void ImageAnalyse::setDxIndex(double n, int x, int y){
    d_x[x][y] = n;
}

void ImageAnalyse::setDyIndex(double n, int x, int y){
    d_y[x][y] = n;
}
