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
    double *rgb_YUV_image(QImage *src);
    double *rgb_YUV_pixel(QRgb *pixel_src);
    QImage *resize(QImage *src, int pct_V, int pct_H);

signals:

public slots:

};

#endif // TRANSFOCOULEUR_H
