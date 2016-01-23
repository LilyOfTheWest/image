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

    histo1 = new QwtPlot();
    histo2 = new QwtPlot();
    histo3 = new QwtPlot();
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

void ImageAnalyse::calculgradient(int mode){
    int ordre = 3;

    KernelConv *noyauX = new KernelConv(ordre);
    KernelConv *noyauY = new KernelConv(ordre);
    switch(mode){
    case 0:
        noyauX->generePrewittHori();
        noyauY->generePrewittVert();
        break;
    case 2:
        noyauX->genereScharrHori();
        noyauY->genereScharrVert();
        break;
    default:
        noyauX->genereSobelHori();
        noyauY->genereSobelVert();
        break;
    }

    d_x = new double *[dataRGB->height()];
    d_y = new double *[dataRGB->height()];

    for(int i=0;i<dataRGB->height();i++){
        d_x[i] = new double[dataRGB->width()];
        d_y[i] = new double[dataRGB->width()];
    }

    d_x = noyauX->produitConv(imagris, dataRGB->width(), dataRGB->height());
    d_y = noyauY->produitConv(imagris, dataRGB->width(), dataRGB->height());
}

int ImageAnalyse::min(){
    int min = 255;
    QRgb color;
    int r;
    for(int i=0;i<dataYUV->height();i++){
        for(int j=0;j<dataYUV->width();j++){
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
        for(int j=0;j<dataYUV->width();j++){
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

void ImageAnalyse::histoToPoints(int mode){
    int valeur;
    for(int i=0;i<3;i++){
        for(int j=0;j<256;j++){
            if(mode == 1){
                valeur = histo_yuv[i][j];
            }
            else{
                valeur = histo_rgb[i][j];
            }
            if(i==0){
                serie1.append(QPoint(j,0));
                serie1.append(QPoint(j,valeur));
            }
            else if(i == 1){
                serie2.append(QPoint(j,0));
                serie2.append(QPoint(j,valeur));
            }
            else{
                serie3.append(QPoint(j,0));
                serie3.append(QPoint(j,valeur));
            }
        }
    }
}

void ImageAnalyse::afficheHisto(int mode){
    histo1->setCanvasBackground(Qt::gray);
    if(mode == 1){
        histo1->setTitle("Composante Y");
    }
    else{
        histo1->setTitle("Répartition des pixels en rouge");
    }
    histo1->setFixedHeight(300);
    histo1->setFixedWidth(600);
    histo1->setAxisScale( QwtPlot::yLeft, 0, maxHisto(0,mode)); //Scale the y-axis
    histo1->setAxisScale(QwtPlot::xBottom,0,256); //Scale the x-axis

    QwtPlotCurve *courbe1 = new QwtPlotCurve("Rouge");
    QColor c = Qt::red;
    c.setAlpha(150);
    courbe1->setPen(c, 2);
    courbe1->setBrush(c);
    courbe1->setSamples(serie1);
    courbe1->attach(histo1);
    histo1->show();

    histo2->setCanvasBackground(Qt::gray);
    if(mode == 1)
        histo2->setTitle("Composante U");
    else
        histo2->setTitle("Répartition des pixels en vert");
    histo2->setFixedHeight(300);
    histo2->setFixedWidth(600);
    histo2->setAxisScale( QwtPlot::yLeft, 0, maxHisto(1,mode)); //Scale the y-axis
    histo2->setAxisScale(QwtPlot::xBottom,0,256); //Scale the x-axis

    QwtPlotCurve *courbe2 = new QwtPlotCurve("Vert");
    QColor c2 = Qt::green;
    c2.setAlpha(150);
    courbe2->setPen(c2, 2);
    courbe2->setBrush(c2);
    courbe2->setSamples(serie2);
    courbe2->attach(histo2);
    histo2->show();

    histo3->setCanvasBackground(Qt::gray);
    if(mode == 1)
        histo3->setTitle("Composante V");
    else
        histo3->setTitle("Répartition des pixels en bleu");
    histo3->setFixedHeight(300);
    histo3->setFixedWidth(600);
    histo3->setAxisScale( QwtPlot::yLeft, 0, maxHisto(2,mode)); //Scale the y-axis
    histo3->setAxisScale(QwtPlot::xBottom,0,256); //Scale the x-axis

    QwtPlotCurve *courbe3 = new QwtPlotCurve("Bleu");
    QColor c3 = Qt::blue;
    c3.setAlpha(150);
    courbe3->setPen(c3, 2);
    courbe3->setBrush(c3);
    courbe3->setSamples(serie3);
    courbe3->attach(histo3);
    histo3->show();


}

int ImageAnalyse::maxHisto(int num, int mode){
    int max = 0;
    if(mode == 1){
        for(int i=0;i<256;i++){
            if(histo_yuv[num][i] >= max){
                max = histo_yuv[num][i];
            }
        }
    }
    else{
        for(int i=0;i<256;i++){
            if(histo_rgb[num][i] >= max){
                max = histo_rgb[num][i];
            }
        }
    }
    return max;
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
