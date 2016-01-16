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

    histo_rgb = new int *[3];
    histo_yuv = new int *[3];
    for(int i=0; i < 3; i++) {
        histo_rgb[i] = new int[256];
        histo_yuv[i] = new int[256];
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<256;j++){
            histo_rgb[i][j]=0;
            histo_yuv[i][j]=0;
        }
    }
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
    double point;

    dataYUV = tc->convertRgbToYuv(dataRGB);

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
}

void ImageAnalyse::calculHisto()
{
    QRgb color, color2;
    int r,g,b,y,u,v;
    // Pour initialiser dataYUV
    initYuvImagris();
    for(int i=0;i<dataRGB->height();i++){
        for(int j=0;j<dataRGB->width();j++){
            color=dataRGB->pixel(j,i);
            r=qRed(color);
            b=qBlue(color);
            g=qGreen(color);
            histo_rgb[0][r]++;
            histo_rgb[1][g]++;
            histo_rgb[2][b]++;

            color2=dataYUV->pixel(j,i);
            y=qRed(color2);
            v=qBlue(color2);
            u=qGreen(color2);
            histo_yuv[0][y]++;
            histo_yuv[1][u]++;
            histo_yuv[2][v]++;
        }
    }
}

void ImageAnalyse::calculgradient(){
    int ordre = 3;
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

int ImageAnalyse::min(){
    int min = 255;
    QRgb color;
    int r;
    for(int i=0;i<dataYUV->height();i++){
        for(int j=0;i<dataYUV->width();j++){
            color=dataYUV->pixel(j,i);
            r=qRed(color);
            if(r <= min){
                min = r;
            }
        }
    }
    return min;
}

int ImageAnalyse::max(){
    int max = 0;
    QRgb color;
    int r;
    for(int i=0;i<dataYUV->height();i++){
        for(int j=0;i<dataYUV->width();j++){
            color=dataYUV->pixel(j,i);
            r=qRed(color);
            if(r >= max){
                max = r;
            }
        }
    }
    return max;
}

int * ImageAnalyse::cumsum(int *h){
    int * sum = new int[256];
    sum[0]=h[0];
    for(int i=1;i<256;i++){
        sum[i]=sum[i-1]+h[i];
    }

    return sum;
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
    double point;

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

int ** ImageAnalyse::getHistoRgb(){
//    int ** h = new int *[3];
//    for(int i=0;i<3;i++){
//        h[i] = new int[256];
//    }

//    h=histo_rgb;

    return histo_rgb;
}

void ImageAnalyse::setHistoRgb(int ** h){
    histo_rgb=h;
}

int ** ImageAnalyse::getHistoYuv(){
//    int ** h = new int *[3];
//    for(int i=0;i<3;i++){
//        h[i] = new int[256];
//    }

//    h=histo_yuv;

    return histo_yuv;
}

void ImageAnalyse::setHistoYuv(int ** h){
    histo_yuv=h;
}
