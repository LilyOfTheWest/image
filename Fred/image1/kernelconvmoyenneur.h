#ifndef KERNELCONVMOYENNEUR_H
#define KERNELCONVMOYENNEUR_H
#include "kernelconv.h"

class KernelConvMoyenneur : public KernelConv
{

public:
    explicit KernelConvMoyenneur(int ordre);
    ~KernelConvMoyenneur();

};

#endif // KERNELCONVMOYENNEUR_H
