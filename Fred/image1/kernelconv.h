#ifndef KERNELCONV_H
#define KERNELCONV_H

#include <QObject>

class KernelConv : public QObject
{
    Q_OBJECT

public:
    explicit KernelConv(QObject *parent = 0);
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

#endif // KERNELCONV_H
