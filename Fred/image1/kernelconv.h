#ifndef KERNELCONV_H
#define KERNELCONV_H

class KernelConv
{

public:
    explicit KernelConv();
    ~KernelConv();
    double **produitConv(double **src);

private:
    int w;  // convolution kernel size
    int sum;  // convolution kernel sum
    double **buf;  // convolution kernel data
};

#endif // KERNELCONV_H
