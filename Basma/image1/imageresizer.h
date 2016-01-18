#ifndef IMAGERESIZER_H
#define IMAGERESIZER_H

#include <QObject>
#include <QImage>
#include "transfocouleur.h"

class ImageResizer : public QObject
{
    Q_OBJECT

public:
    explicit ImageResizer(QObject *parent = 0);
    QImage *extractSubImage(QImage *src,QPoint *origin_select,QPoint *end_select);
    QImage *displaceImage(QImage *principal, QImage *img1,QPoint pos_rel1,QImage *img2,QPoint pos_rel2);
    QImage *rotateImage90(QImage *src,bool horaire);
    QImage *rotateImage180(QImage *src);
    QImage *resizeImage(QImage *src,int newWidth, int newHeight);
    void interpol(QImage *dest, int wDest,int hDest,int nb_interpo_w,QRgb color1,
                                QRgb  color2,bool width_sens);

signals:

public slots:

private:
    QImage *resizeImage_w(QImage *src,int newWidth, int height);
    QImage *resizeImage_h(QImage *src,int width, int newHeight);
};

#endif // IMAGERESIZER_H
