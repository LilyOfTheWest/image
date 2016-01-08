#include "kernelconv.h"
#include <malloc.h>

KernelConv::KernelConv()
{
    w=3;
    buf=(double**) malloc(w*w*sizeof(double*));

}

KernelConv::~KernelConv() {

}

double ** KernelConv::produitConv(double **src) {

    return src;
}
