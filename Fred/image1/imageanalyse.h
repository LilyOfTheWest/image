#ifndef IMAGEANALYSE_H
#define IMAGEANALYSE_H

#include <QObject>
#include <QImage>

class ImageAnalyse : public QObject
{
    Q_OBJECT

public:
    explicit ImageAnalyse(QImage *qimageRgbSrc,QObject *parent = 0);
    ~ImageAnalyse();
    void convertRgbToYuv();
    void convertYuvToRgb();
    void calculHisto();
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
};

#endif // IMAGEANALYSE_H
