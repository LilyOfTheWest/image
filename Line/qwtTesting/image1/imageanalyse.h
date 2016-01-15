#ifndef IMAGEANALYSE_H
#define IMAGEANALYSE_H

#include <QObject>
#include <QImage>
#include "TransfoCouleur.h"

class ImageAnalyse : public QObject
{
    Q_OBJECT

public:
    explicit ImageAnalyse(QImage *qimageRgbSrc,QObject *parent = 0);
    ~ImageAnalyse();
    void initYuvImagris();
    void fromYuvToRgb();
    void calculHisto();
    void calculgradient();

    /* Getters & Setters */
    QImage * getDataRGB();
    void setDataRGB(QImage *i);
    QImage * getDataYUV();
    void setDataYUV(QImage *i);
    double ** getImagris();
    void setImagris(double ** img);
    double ** getD_x();
    void setD_x(double ** dx);
    double ** getD_y();
    void setD_y(double ** dy);
    double getDxIndex(int x, int y);
    double getDyIndex(int x, int y);
    void setDxIndex(double n, int x, int y);
    void setDyIndex(double n, int x, int y);
signals:

public slots:

private:
QImage *dataRGB;
QImage *dataYUV; //On stocke du YUV dans la structure QRgb - 3 int [0-255] pour décrire
double **imagris; //en entrée pour les convolutions de Line ;
int histo_rgb[255][3];
int histo_yuv[255][3];
double **d_x;
double **d_y;
TransfoCouleur *tc;
};

#endif // IMAGEANALYSE_H
