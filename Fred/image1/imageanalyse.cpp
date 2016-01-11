#include "imageanalyse.h"
#include "transfocouleur.h"
#include "qglobal.h"

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
}

ImageAnalyse::~ImageAnalyse()
{

}

void ImageAnalyse::initYuvImagris()
{
    QRgb color;
    int r;
    dataYUV = tc->convertRgbToYuv(dataRGB);
    imagris = new double*[dataYUV->height()];
    for (int i=0; i< dataYUV->height() ; i++) {
        imagris[i] = new double[dataYUV->width()];
        for (int j=0; j<dataYUV->width() ; j++) {
            color=dataYUV->pixel(j,i);
            r=qRed(color);
            imagris[i][j] = r;
        }
    }
}

void ImageAnalyse::calculHisto()
{

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

void ImageAnalyse::setImagris(double ** i){
    imagris = i;
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
