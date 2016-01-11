#include "kernelconvbinomial.h"

KernelConvBinomial::KernelConvBinomial(int ordre) : KernelConv(ordre)
{
    double K[2]={1,1};
    double *K2=new double[ordre];
    int n = 2;
    for(int i=0;i<ordre-2;i++){
        if(i==0){
            K2=convLinear(K,K,n,2);
        }
        else{
            K2=convLinear(K2,K,n,2);
        }
        n++;
    }
    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            buf[i][j]=K2[i]*K2[j];
        }
    }

    sommeCoef();

    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            buf[i][j]=buf[i][j]/coef;
        }
    }
}

KernelConvBinomial::~KernelConvBinomial()
{

}
