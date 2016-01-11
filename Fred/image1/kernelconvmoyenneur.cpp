#include "kernelconvmoyenneur.h"

KernelConvMoyenneur::KernelConvMoyenneur(int ordre) : KernelConv(ordre)
{
//    KernelConv(ordre);
    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            buf[i][j] = 1;
        }
    }

    this->sommeCoef();
}

KernelConvMoyenneur::~KernelConvMoyenneur()
{

}
