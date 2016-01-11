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
}

ImageAnalyse::~ImageAnalyse()
{

}

void ImageAnalyse::convertRgbToYuv()
{
    /*QRgb color,color2;
    int r,g,b,alpha;
    TransfoCouleur *tc = new TransfoCouleur;
    dataYUV = new QImage(qimageRgbSrc->width(),qimageRgbSrc->height(),qimageRgbSrc->format());
    imagris = new double*[dataRGB->height()];
    for (int i=0; i< dataRGB->height() ; i++) {
        imagris[i] = new double[dataRGB->width()];
        for (int j=0; j<dataRGB->width() ; j++) {
            color=dataRGB->pixel(j,i);
            r=tc->get_YVal_Pixel(color);
            g=tc->get_UVal_Pixel(color);
            b=tc->get_VVal_Pixel(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            dataYUV->setPixel(j,i,color2);
            imagris[i][j] = r;
        }
    }*/
}

void ImageAnalyse::convertYuvToRgb()
{
    QRgb color,color2;
    int r,g,b,alpha;
    TransfoCouleur *tc = new TransfoCouleur;
    for (int i=0; i< dataRGB->height() ; i++) {
        for (int j=0; j<dataRGB->width() ; j++) {
            color=dataRGB->pixel(j,i);
            /*r=tc->get_RVal_Pixel(color);
            g=tc->get_GVal_Pixel(color);
            b=tc->get_BVal_Pixel(color);*/
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            dataYUV->setPixel(j,i,color2);
        }
    }
}

void ImageAnalyse::calculHisto()
{

}

QImage * getDataRGB(){
    return this.dataRGB;
}

void setDataRGB(QImage i){
    this.dataRGB = i;
}

QImage * getDataYUV(){
    return this.dataYUV;
}

void setDataYUV(QImage i){
    this.dataYUV = i;
}

double ** getImagris(){
    return this.imagris;
}

void setImagris(double ** i){
    this.imagris = i;
}

int ** getHisto_rgb(){
    return this.histo_rgb;
}

void setHisto_rgb(int ** h){
    this.histo_rgb = h;
}

int ** getHisto_yuv(){
    return this.histo_yuv;
}

void setHisto_yuv(int ** h){
    this.histo_yuv = h;
}

double ** getD_x(){
    return this.d_x;
}

void setD_x(double ** dx){
    this.d_x = dx;
}

double ** getD_y(){
    return this.d_y;
}

void setD_y(double ** dy){
    this.d_y = dy;
}
