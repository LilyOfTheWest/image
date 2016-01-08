#ifndef KERNELCONV_H
#define KERNELCONV_H

class KernelConv : public QObject
{

public:
    explicit KernelConv();
    double **produitConv(double **src);

signals:

public slots:

private:
    int w;  // convolution kernel width
    int h;  // convolution kernel heigth
    int sum;  // convolution kernel sum
    double **buf;  // convolution kernel data
};

#endif // KERNELCONV_H
