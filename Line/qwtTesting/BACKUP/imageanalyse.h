#ifndef IMAGEANALYSE_H
#define IMAGEANALYSE_H

#include <QObject>
#include <QImage>
#include "TransfoCouleur.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"

class ImageAnalyse : public QObject
{
    Q_OBJECT

public:
    explicit ImageAnalyse(QImage *qimageRgbSrc,QObject *parent = 0);
    ~ImageAnalyse();
    void initYuvImagris();
    void fromYuvToRgb();
    void calculHisto();
    void calculgradient(int mode);
    int min();
    int max();
    int * cumsum(int h[]);
    void histoToPoints(int mode);
    void afficheHisto(int mode);
    int maxHisto(int num, int mode);

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
    int ** getHistoRgb();
    void setHistoRgb(int ** h);
    int ** getHistoYuv();
    void setHistoYuv(int ** h);
signals:

public slots:

private:
QImage *dataRGB;
QImage *dataYUV; //On stocke du YUV dans la structure QRgb - 3 int [0-255] pour décrire
double **imagris; //en entrée pour les convolutions de Line ;
int **histo_rgb;
int **histo_yuv;
double **d_x;
double **d_y;
TransfoCouleur *tc;
QwtPlot *histo1;
QwtPlot *histo2;
QwtPlot *histo3;
QPolygonF serie1;
QPolygonF serie2;
QPolygonF serie3;
};

#endif // IMAGEANALYSE_H
