#ifndef IMAGEANALYSE_H
#define IMAGEANALYSE_H

#include <QObject>

class ImageAnalyse : public QObject
{
    Q_OBJECT

public:
    explicit ImageAnalyse(QObject *parent = 0);


signals:

public slots:

private:
QImage *principal;
double **imagris;
int histo_rgb[255][3];
double histo_yuv[255][3];
double **imaYuv;
double **d_x;
double **d_y;
};

#endif // IMAGEANALYSE_H
