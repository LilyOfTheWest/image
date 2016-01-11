#include "kernelconv.h"
#include <malloc.h>

KernelConv::KernelConv(int ordre)
{
    w=ordre;
    buf=(double**) malloc(w*w*sizeof(double*)); 
    coef = 0;
}

KernelConv::~KernelConv() {

}

double ** KernelConv::produitConv(double **src, int n, int m) {
    /* Place pour l'image formée */
    double ** S = new double*[n];
    for(int i = 0;i<n;i++){
        S[i] = new double[m];
    }

    /* Retournement spacial du noyau + calcul de ses coeffs */
    this->retournement();
    this->sommeCoef();

    int lk = (k-1)/2;
    int ck = (k-1)/2;
    int sum;

    /* Régler problème des tailles de noyau sup */
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // Pour ne pas prendre en compte les bords
            if(i==0 || i== n-1 || j== 0 || j== m-1){
                S[i][j] = buf[i][j];

            }
            // Les bords restent les mêmes
            else{
                sum = 0;
                for(int l=-lk;l<=lk;l++){
                    for(int c = -ck;c<=ck;c++){
                        sum+=K[l+lk][c+ck]*buf[i+l][j+c];
                    }
                }
                S[i][j] = sum/coef;
            }
        }
    }
    return S;
}

double * convLinear(double * M, double * K, int n, int k){
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


void ** retournement(){
    for(int i = 0;i<this.w();i++){
        for(int j = 0 ;j<k;j++){
            S[k -(i+1)][k -(j+1)] = M[i][j];
        }
    }
}

void sommeCoef(){
    this.setCoef(0);
    for(int i =0;i<k;i++){
        for(int j =0;j<k;j++){
            this.setCoef(this.coef()+K[i][j]);
        }
    }
}

/* Getters & Setters */
int getW(){
    return this.w;
}

int getCoef(){
    return this.coef;
}

double ** getBuf(){
    return this.buf;
}

void setW(int n){
    this.w = n;
}

void setCoef(int c){
    this.coef = c;
}

void setBuf(double ** b){
    this.buf = b;
}
