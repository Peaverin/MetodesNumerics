/*
 
 
 
 */ 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double tolerancia;
int n;
void printmatrix(double** A){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%+1.4f       ", A[i][j]);
        }
        printf("\n");
    }
     printf("\n");
}
/*Eliminació Gaussiana amb pivotatge parcial*/
int elimGauss(double**A, double *b){
    double max, *vauxiliar, m;
    int k,v,i,j;
    /*Vector auxiliar per a l'intercanvi de files: Serà de mida n+1 per guardar també bk.*/
    vauxiliar = (double *)malloc((n+1)*sizeof(double));
    /*Cal fer n-1 etapes: */
    for(k=0;k<n-1;k++){
        /*Busquem v pertanyent a {k+1,....,n} tq avk(n) sigui el màxim: */
        max = A[k][k];
        v = k;
        for(i=k+1;i<n;i++){
            if(fabs(A[i][k]) > fabs(max)){
                max = A[i][k];
                v = i; 
            }
        }
        /*Si el màxim es menor a la tolerància, ja hem acabat:*/
        if(fabs(max) < tolerancia) return 1;
        /*Si v!=k Intercanviem les files k i v (a partir de la columna k, ja que les altres seran 0. */
        if(k!=v){
            /*Guardem fila k a vauxiliar: */
            for(i=k;i<n;i++){
                vauxiliar[i] = A[k][i];
            }
            vauxiliar[n] = b[k];
            /*Passem la fila v a k:*/
            for(i=k;i<n;i++){
                A[k][i] = A[v][i];
            }
            b[k] = b[v];
            /*Passem el vector auxiliar, on guardem la fila k, a v:*/
            for(i=k;i<n;i++){
                A[v][i] = vauxiliar[i];
            }
            b[v] = vauxiliar[n];
        }
        /*Un cop hem realizar el canvi de files, calculem per a cada fila i€{k+1,.....,n} mik  i fem la resta:*/
        for(i=k+1;i<n;i++){
            /*Calculem mik*/
            m = A[i][k] / A[k][k];
            /*Ja sabem que efectuan la resta a i=k obtenim 0:*/
            A[i][k] = 0;
            /*Per a cada j€{k+1,.....,n} fem la resta corresponent, i també per a bi*/
            for(j=k+1;j<n;j++) A[i][j] -= m*A[k][j]; 
            b[i] -= m*b[k];
        }
    }
    return 0;
}
/*Resolució del sistema triangular per substitució endarrera:*/
int resoltriangular(double **A, double *b){
    int i, j;
    double sumatori;
    /*xn:*/
    if(fabs(A[n-1][n-1]) < tolerancia) return 2;
    b[n-1] = b[n-1]/A[n-1][n-1];
    for(i=n-2;i>=0;i--){
        /*Sumatori*/
        sumatori = 0;
        for(j=i+1;j<n;j++) sumatori += A[i][j]*b[j];
        /*Restem b[i] (és a dir, actualment és ci) - sumatori*/
        b[i] = b[i] - sumatori;
        /*Si Aii es major a la tolerancia, dividim per Aii:*/
        if(fabs(A[i][i]) < tolerancia) return 2;
        b[i] = b[i]/A[i][i];
    }
    return 0;
}
/*

 */
int main(void){
    int i,j, index;
    double *x, *f, **A;
    
    tolerancia = 1.e-14;
    printf("Digues n:\n");
    scanf("%d", &n);
    n++;
    A = (double**)malloc((n)*sizeof(double*));
    x = (double*)malloc((n)*sizeof(double));
    f = (double*)malloc((n)*sizeof(double));
    
    for(i=0;i<n;i++){
        printf("Digues x%d: \n", i);
        scanf("%le", &x[i]);
        printf("Digues f(x%d): \n", i);
        scanf("%le", &f[i]);
    }
    /*la matriu es: primera columna tot 1
                    per a cada fila i, cada columna és (xi)^j 
                    els coeficients del sistema són els a0,a1,.....an del polinomi que busquem
                    creem l'equació i resolem el sistema amb eliminació gaussiana i resolució del sistema triangular per substitució endarrera
     */
    for(i=0;i<n;i++){
        A[i] = (double*)malloc(n*sizeof(double));
        A[i][0] = 1;
        for(j=1;j<n;j++) A[i][j] = pow((x[i]),j);
    }
    printmatrix(A);
    index = elimGauss(A, f);
    if(index != 0) return -1;
    index = resoltriangular(A,f);
    if(index != 0) return -1;
    printf("Solucions: \n");
    for(i=0;i<n;i++){
        printf("a%d = %e\n", i, f[i]);
    }
    return 0;
}
