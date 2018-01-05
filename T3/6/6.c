#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double fun(double x){
    double y;
    y = 1/(1.+x);
    return y;
}
double trap(int n, double a, double h){
    double y = 0.;
    double x;
    for (int i=1;i<n;i++){
        x = a + i*h;
        y += h*fun(x);
    }
    y += h*(fun(a)+fun(x+h))/2;
    return y;
}
int main (void){
    int n, i, j, k, q, end;
    double **M,a,b,h,prec,res;
    q = 2.; /*Pas de disminucio*/
    prec = 1.e-10; /*Precisio desitjada*/
    a = 0.;
    b = 1.;
    end = 0;
    k = 10;
    printf("Digues n: ");
    scanf("%d",&n);
    h = (b-a)/n;
    M = (double**)malloc(k*sizeof(double*));
    for(i=0;i<k;i++){
        M[i] = (double*)malloc(k*sizeof(double));
    }
    
    /*Fem la diferenciacio*/
    M[0][0] = trap(n,a,h);
    printf("%.10e\n",M[0][0]);
    for(i=1;i<k;i++){
        M[i][0] = trap(n*pow(q,i),a,h/pow(q,i));
        for(j=1;j<i+1;j++){
            M[i][j] = (pow(q,2*j)*M[i][j-1]-M[i-1][j-1])/(pow(q,2*j)-1);
            if (fabs(M[i][j]-M[i][j-1])<prec){
                end = 1;
                res = M[i][j];
            }
        }
        for(j=0;j<i+1;j++){
            printf("%.10e ",M[i][j]);
        }
        printf("\n");
        if(end){
            printf("resultat=%.10e\n",res);
            break;
        }
    }
    return 0;
}