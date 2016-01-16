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
    QImage *rotateImage90(QImage *src,bool horaire);
    QImage *rotateImage180(QImage *src);

signals:

public slots:
};

#endif // IMAGERESIZER_H
