/* Ax = b
 * Dimensio n
 * Llegeix n, A i b

*/

#include<stdio.h>    
#include<stdlib.h>  
#include <time.h>  
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
            if(A[i][k] > max){
                max = A[i][k];
                v = i; 
            }
        }
        /*Si el màxim es menor a la tolerància, ja hem acabat:*/
        if(max < tolerancia) return 1;
        /*Intercanviem les files k i v (a partir de la columna k, ja que les altres seran 0. */
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
    b[n-1] = b[n-1]/A[n-1][n-1];
    for(i=n-2;i>=0;i--){
        /*Sumatori*/
        sumatori = 0;
        for(j=i+1;j<n;j++) sumatori += A[i][j]*b[j];
        /*Restem b[i] (és a dir, actualment és ci) - sumatori*/
        b[i] = b[i] - sumatori;
        /*Si Aii es major a la tolerancia, dividim per Aii:*/
        if(A[i][i] > tolerancia){
        b[i] = b[i]/A[i][i];
        }else{
            return 2;
        }
    }
    return 0;
}
int main(void)
{
   double **A, *b;
   int i, j;
   tolerancia = 1.e-14;
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
   /*Llegim b*/
   b = (double *)malloc(n*sizeof(double));
   for(i=0;i<n;i++){
    printf("Escriu b%d:",i);
    scanf("%le", &b[i]);
    }
    /*Fem eliminació Gaussiana. A esdevindrà A(k) i b esdevindrà c */
    elimGauss(A,b);
    printf("Matriu triangulada\n");
    printmatrix(A);
    /*Fem sustitució triangular. c esdevindrà x (solucio)*/
    resoltriangular(A,b);
    /*Mostrem els resultats:*/
    printf("Solucions:\n");
    for(i=0;i<n;i++){
        printf("x%d = %+.7le\n", i+1, b[i]);
    }
    return 0;
}
