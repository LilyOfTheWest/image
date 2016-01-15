#ifndef IMAGEBUF_H
#define IMAGEBUF_H

#include <QObject>

class ImageBuf : public QImage
{
    Q_OBJECT

public:
    explicit ImageBuf(QObject *parent = 0);
    void inverseColor();

signals:

public slots:
};

#endif // IMAGEBUF_H
