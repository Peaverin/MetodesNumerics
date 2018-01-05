#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double fun(double x){
    double y;
    y = exp(x);
    return y;
}
double F0(double a, double h){
    double y;
    y = (fun(a+h)-fun(a-h))/(2*h);
    return y;
}
int main (void){
    int n, i, j, q, end;
    double **M,a,h,prec, res;
    q = 2.; /*Pas de disminucio*/
    prec = 1.e-10; /*Precisio desitjada*/
    a = 1.;
    end = 0;
    printf("Digues n: ");
    scanf("%d",&n);
    printf("Digues h: ");
    scanf("%le", &h);
    
    M = (double**)malloc(n*sizeof(double*));

    for(i=0;i<n;i++){
        M[i] = (double*)malloc(n*sizeof(double));
    }
    /*Ara tenim una matriu amb tots els parells (xi,fi) de 0 a n*/
    /*Fem la diferenciacio*/
    M[0][0] = F0(a,h);
    printf("%.10e\n",M[0][0]);
    for(i=1;i<n;i++){
        M[i][0] = F0(a,h/pow(q,i));
        for(j=1;j<i+1;j++){
            M[i][j] = (pow(q,2*j)*M[i][j-1]-M[i-1][j-1])/(pow(q,2*j)-1);
            if (fabs(M[i][j]-M[i][j-1])<prec){
                /*printf("\nFINAL: %.10e %.10e\n", M[i][j],M[i][j-1]);*/
                end = 1;
                res = M[i][j];
            }
        }
        for(j=0;j<i+1;j++){
            printf("%.10e ",i,j,M[i][j]);
        }
        printf("\n");
        if(end){
            printf("resultat=%.10e\n",res);
            break;
        }
    }
    return 0;
}