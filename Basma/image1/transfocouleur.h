#ifndef TRANSFOCOULEUR_H
#define TRANSFOCOULEUR_H

#include <QObject>
#include <QImage>

class TransfoCouleur : public QObject
{
    Q_OBJECT

public:
    explicit TransfoCouleur(QObject *parent = 0);
    QImage *inverseColor(QImage *src);
    QImage *flou(QImage *src);
    QImage *rehaussement(QImage *src);
    QImage *contour(QImage *src);
    QImage *gris(QImage *src);
    QImage *etalement(QImage *src);
    QImage *egalisation(QImage *src);
    /* A mettre dans imageanalyse !!
     * double *rgb_YUV_image(QImage *src);
    double **get_YBuf_image(QImage *src);
    double *rgb_YUV_pixel(QRgb *pixel_src);*/
    QImage *resize(QImage *src, int pct_V, int pct_H);

    int get_YVal_Pixel_FromRgb(QRgb pixel_src);
    int get_UVal_Pixel_FromRgb(QRgb pixel_src);
    int get_VVal_Pixel_FromRgb(QRgb pixel_src);
    int get_RVal_Pixel_FromYuv(QRgb pixel_src);
    int get_GVal_Pixel_FromYuv(QRgb pixel_src);
    int get_BVal_Pixel_FromYuv(QRgb pixel_src);
    QImage *convertRgbToYuv(QImage *src);
    QImage *convertYuvToRgb(QImage *src);
    QImage *extractSubImage(QImage *src,QPoint *origin_select,QPoint *end_select);
    int normalizeColorValue(double val);
signals:

public slots:

};

#endif // TRANSFOCOULEUR_H
