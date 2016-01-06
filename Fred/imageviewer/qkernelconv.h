#ifndef QKERNELCONV_H
#define QKERNELCONV_H

#include <QObject>

class QKernelConv : public QObject
{
    Q_OBJECT
public:
    explicit QKernelConv(QObject *parent = 0);
    QImage inverseColor(QImage *src);
    QImage produitConv(QImage *src);
    QImage calque(QImage *src);

signals:

public slots:

private:
    int w;  // convolution kernel width
    int h;  // convolution kernel heigth
    int sum;  // convolution kernel sum
    int *buf;  // convolution kernel data
};

#endif // QKERNELCONV_H
