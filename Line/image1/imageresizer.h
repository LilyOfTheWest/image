#ifndef IMAGERESIZER_H
#define IMAGERESIZER_H

#include <QObject>
#include <QImage>


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

signals:

public slots:
};

#endif // IMAGERESIZER_H
