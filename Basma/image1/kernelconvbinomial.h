#ifndef KERNELCONVBINOMIAL_H
#define KERNELCONVBINOMIAL_H
#include "kernelconv.h"


class KernelConvBinomial : public KernelConv
{
public:
    explicit KernelConvBinomial(int ordre);
    ~KernelConvBinomial();
};

#endif // KERNELCONVBINOMIAL_H
