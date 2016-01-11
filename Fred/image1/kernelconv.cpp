#include "kernelconv.h"
#include <malloc.h>

KernelConv::KernelConv(int ordre)
{
    w=ordre;
    buf = new double*[ordre];
    for(int i = 0;i<ordre;i++){
        buf[i] = new double[ordre];
    }
    coef = 0;

}

KernelConv::~KernelConv() {

}

double ** KernelConv::produitConv(double **src, int n, int m) {
    /* Place pour l'image formée */
    double ** S = new double*[m];
    for(int i = 0;i<m;i++){
        S[i] = new double[n];
    }

    /* Retournement spacial du noyau + calcul de ses coeffs */
    retournement();
    sommeCoef();

    int lk = (w-1)/2;
    int ck = (w-1)/2;
    int sum;

    /* Régler problème des tailles de noyau sup */
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            // Pour ne pas prendre en compte les bords
            if(i==0 || i == m-1 || j== 0 || j == n-1){
                S[i][j] = src[i][j];

            }
            // Les bords restent les mêmes
            else{
                sum = 0;
                for(int l=-lk;l<=lk;l++){
                    for(int c = -ck;c<=ck;c++){
                        sum+=buf[l+lk][c+ck]*src[i+l][j+c];
                    }
                }
                S[i][j] = sum/coef;
            }
        }
    }
    return S;
}

double * KernelConv::convLinear(double * M, double * K, int n, int k){
    double * S = new double[n+k-1];
    int kmin,kmax;
    for(int i=0;i<n+k-1;i++){
        S[i]=0;
        kmin=(i>=k-1)?i-(k-1):0;
        kmax=(i<n-1)?i:n-1;
        for(int j=kmin;j<=kmax;j++){
            S[i]+=M[j]*K[i-j];
        }
    }
    return S;
}


void KernelConv::retournement(){
    double ** S = new double*[w];
    for(int i = 0;i<w;i++){
        S[i] = new double[w];
    }

    for(int i = 0;i<w;i++){
        for(int j = 0 ;j<w;j++){
            S[w -(i+1)][w -(j+1)] = buf[i][j];
        }
    }
    buf=S;
}

void KernelConv::sommeCoef(){
    setCoef(0);
    for(int i =0;i<w;i++){
        for(int j =0;j<w;j++){
            setCoef(coef+buf[i][j]);
        }
    }
}

/* Getters & Setters */
int KernelConv::getW(){
    return w;
}

int KernelConv::getCoef(){
    return coef;
}

double ** KernelConv::getBuf(){
    return buf;
}

void KernelConv::setW(int n){
    w = n;
}

void KernelConv::setCoef(int c){
    coef = c;
}

void KernelConv::setBuf(double ** b){
    buf = b;
}
