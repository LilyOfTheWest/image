#include "imageanalyse.h"
#include "transfocouleur.h"
#include "qglobal.h"

ImageAnalyse::ImageAnalyse(QImage *qimageRgbSrc,QObject *parent) : QObject(parent)//,dataRGB(qimageRgbSrc)
{
    QRgb color,color2;
    dataRGB = new QImage(qimageRgbSrc->width(),qimageRgbSrc->height(),qimageRgbSrc->format());
    dataYUV = new QImage(qimageRgbSrc->width(),qimageRgbSrc->height(),qimageRgbSrc->format());
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
    QRgb color,color2;
    int r,g,b,alpha;
    TransfoCouleur *tc = new TransfoCouleur;
    for (int i=0; i< dataRGB->height() ; i++) {
        for (int j=0; j<dataRGB->width() ; j++) {
            color=dataRGB->pixel(j,i);
            r=tc->get_YVal_Pixel(color);
            g=tc->get_UVal_Pixel(color);
            b=tc->get_VVal_Pixel(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            dataYUV->setPixel(j,i,color2);
        }
    }
}

void ImageAnalyse::convertYuvToRgb()
{
    QRgb color,color2;
    int r,g,b,alpha;
    TransfoCouleur *tc = new TransfoCouleur;
    for (int i=0; i< dataRGB->height() ; i++) {
        for (int j=0; j<dataRGB->width() ; j++) {
            color=dataRGB->pixel(j,i);
            r=tc->get_YVal_Pixel(color);
            g=tc->get_UVal_Pixel(color);
            b=tc->get_VVal_Pixel(color);
            alpha=qAlpha(color);
            color2=qRgba(r,g,b,alpha);
            dataYUV->setPixel(j,i,color2);
        }
    }
}

void ImageAnalyse::calculHisto()
{

}
