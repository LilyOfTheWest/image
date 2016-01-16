#ifndef KERNELCONV_H
#define KERNELCONV_H

class KernelConv
{

public:
    explicit KernelConv(int ordre);
    ~KernelConv();
    double **produitConv(double **src, int n, int m);
    double * convLinear(double * M, double * K, int n, int k);
    void retournement();
    void sommeCoef();
    void genereImp();
    void genereSobelVert();
    void genereSobelHori();
    int reflect(int M, int x);
    /* Getters & Setters */
    int getW();
    int getCoef();
    double ** getBuf();
    double getIndex(int x, int y);
    void setW(int n);
    void setCoef(int c);
    void setBuf(double ** b);
    void setIndex(double n, int x, int y);

protected:
    int w;  // convolution kernel size
    int coef;  // convolution kernel sum
    double **buf;  // convolution kernel data
};

#endif // KERNELCONV_H
