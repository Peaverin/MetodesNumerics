/* Ax = b
 * Dimensio n
 * Llegeix n, A i b

*/

#include<stdio.h>    
#include<stdlib.h>  
#include <time.h>  
#include <math.h>

int n;
double tolerancia;
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
int elimGauss(double**A){
    double m;
    int k,i,j;
    /*Cal fer n-1 etapes: */
    for(k=0;k<n-1;k++){
        if(fabs(A[k][k]) < tolerancia) return 1;
        /*Calculem per a cada fila i€{k+1,.....,n} mik  i fem la resta:*/
        for(i=k+1;i<n;i++){
            /*Calculem mik*/
            m = A[i][k] / A[k][k];
            /*Ja sabem que efectuan la resta a i=k obtenim 0:*/
            A[i][k] = m;
            /*Per a cada j€{k+1,.....,n} fem la resta corresponent, i també per a bi*/
            for(j=k+1;j<n;j++) A[i][j] -= m*A[k][j];
        }
    }
    return 0;
}
int main(void)
{
   double **A;
   int i, j, index;
   tolerancia = 1.e-12;
   /*Llegim A*/
   printf("Escriu l'enter n:");
   scanf("%d", &n);
   A = (double **)malloc(n*sizeof(double*));
   for(i=0;i<n;i++){
       A[i] = (double *)malloc(n*sizeof(double));
       for(j=0;j<n;j++){
        printf("Escriu A%d%d:",i,j);
        scanf("%le", &A[i][j]);
        }
   }
   index = elimGauss(A);
    /*Fem eliminació Gaussiana. A esdevindrà A(k) i b esdevindrà c */
    if(index != 0){
        printf("No s'ha pogut realitzar eliminacio gaussiana sense pivotatge.\n");
        return index;
    }
    printf("Matriu triangulada amb m a sota la diagonal inferior:\n");
    printmatrix(A);
    printf("A=LU\nL=\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(j<i) printf("%+1.3e   ", A[i][j]);
            if(i==j) printf("%+1.3e   ",1.);
            if(j>i) printf("%+1.3e   ", 0.);
        }
        printf("\n");
    }
    printf("U=\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(j<i) printf("%+1.3e   ", 0.);
            if(i==j) printf("%+1.3e   ",A[i][j]);
            if(j>i) printf("%+1.3e   ", A[i][j]);
        }
        printf("\n");
    }
    return 0;
}
