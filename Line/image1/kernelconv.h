#ifndef KERNELCONV_H
#define KERNELCONV_H

class KernelConv
{

public:
    explicit KernelConv(int ordre);
    ~KernelConv();
    double **produitConv(double **src, int n, int m);
    double * convLinear(double * M, double * K, int n, int k);
    void ** retournement();
    void sommeCoef();
    /* Getters & Setters */
    int getW();
    int getCoef();
    double ** getBuf();
    void setW(int n);
    void setCoef(int c);
    void setBuf(double ** b);

private:
    int w;  // convolution kernel size
    int coef;  // convolution kernel sum
    double **buf;  // convolution kernel data
};

#endif // KERNELCONV_H
