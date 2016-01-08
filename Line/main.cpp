#include <iostream>
#include <stdlib.h>

using namespace std;

double ** retournement(double ** M, int k);
void afficheMatrice(double ** M, int k);
double ** conv2(double ** M, double ** K, int n, int m, int k);
double * conv1(double * M, double * K, int n, int k);
double ** genere_gauss(int k);
double ** genere_moy(int k);

int main(int argc, char *argv[])
{
    int k = 4, n=1;
    //int ** M = (int **)malloc(k*sizeof(int *));
    double ** M = new double*[k];
    for(int i = 0;i<k;i++){
        M[i] = new double[k];
    }

    M[0][0]=4;
    M[0][1]=5;
    M[0][2]=6;
    M[0][3]=7;
    M[1][0]=7;
    M[1][1]=6;
    M[1][2]=5;
    M[1][3]=4;
    M[2][0]=1;
    M[2][1]=2;
    M[2][2]=3;
    M[2][3]=1;
    M[3][0]=5;
    M[3][1]=1;
    M[3][2]=6;
    M[3][3]=1;

    double **K=new double*[3];
    for(int i =0;i<3;i++){
        K[i]=new double[3];
    }

    K[0][0]=1;
    K[1][0]=2;
    K[2][0]=1;
    K[0][1]=2;
    K[1][1]=4;
    K[2][1]=2;
    K[0][2]=1;
    K[1][2]=2;
    K[2][2]=1;

    afficheMatrice(M,k);
    afficheMatrice(K,3);
    double ** S = conv2(M,K,k,k,3);

    afficheMatrice(S,k);
    double **N=new double*[5];
    for(int i =0;i<5;i++){
        N[i]=new double[5];
    }
    N = genere_gauss(5);
    afficheMatrice(N,5);

    return 0;
}

double ** retournement(double ** M, int k){
    double ** S = new double*[k];
    for(int i = 0;i<k;i++){
        S[i] = new double[k];
    }
    for(int i = 0;i<k;i++){
        for(int j = 0 ;j<k;j++){
            S[k -(i+1)][k -(j+1)] = M[i][j];
        }
    }

    return S;
}



void afficheMatrice(double ** M, int k){
    cout << "[";
    for(int i=0;i<k;i++){
        for(int j = 0;j<k;j++){
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "]";
    cout << "\n";
}

double ** conv2(double ** M, double ** K, int n, int m, int k){
    double ** S = new double*[n];
    for(int i = 0;i<n;i++){
        S[i] = new double[m];
    }
    K = retournement(K,k);
    int coef = 0;
    for(int i =0;i<k;i++){
        for(int j =0;j<k;j++){
            coef+=K[i][j];
        }
    }

    int lk = (k-1)/2;
    int ck = (k-1)/2;
    int sum;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // Pour ne pas prendre en compte les bords
            if(i==0 || i== n-1 || j== 0 || j== m-1){
                S[i][j] = M[i][j];

            }
            // Les bords restent les mêmes
            else{
                sum = 0;
                for(int l=-lk;l<=lk;l++){
                    for(int c = -ck;c<=ck;c++){
                        sum+=K[l+lk][c+ck]*M[i+l][j+c];
                    }
                }
                S[i][j] = sum/coef;
            }
        }
    }
    return S;
}

double * conv1(double * M, double * K, int n, int k){
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

double ** genere_gauss(int k){
    double **S=new double*[k];
    for(int i=0;i<k;i++){
        S[i]=new double[k];
    }

    double K[2]={1,1};
    double *K2=new double[k];
    int n = 2;
    for(int i=0;i<k-2;i++){
        if(i==0){
            K2=conv1(K,K,n,2);
        }
        else{
            K2=conv1(K2,K,n,2);
        }
        n++;
    }
    int coef = 0;
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            S[i][j]=K2[i]*K2[j];
            coef+=S[i][j];
        }
    }

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            S[i][j]/=coef;
        }
    }
    return S;
}

double ** genere_moy(int k){
    double **S=new double*[k];
    for(int i=0;i<k;i++){
        S[i]=new double[k];
    }

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            S[i][j]=1;
        }
    }

    return S;
}
