/* sobredet.c
resolució d'un sistema lineal sobredeterminat m x n (m >= n)
Mètode:
equacions normals + factoritzacio LDLt + resolució 3 sistemes fàcils
Al final, es calcula el vector residu i la seva norma-2
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 100        /* dimensió màxima permesa */
#define tol 1.e-12   /* tolerància límit per a la factorització */

/*
Matriu: a (mxn)
Vector termes independents: b (mx1)
Matriu normal: mat (nxn)
Vector termes independents normalitzat vec (nx1)
 */
void equnor(int m, int n, double **a, double *b, double **mat, double *vec);
int ldlt(int n, double** mat);

int main(void)
{
    int i,j,index,m,n;
    
    double **a, *b, **mat, *vec, aux, res;
    printf("Digues les dimensions de la matriu A (mxn): ");
    scanf("%d %d",&m,&n);
    while(m<n){
        printf("Dimensions incorrectes, cal m mes gran o igual a n: ");
        printf("Digues les dimensions de la matriu A (mxn): ");
        scanf("%d %d",&m,&n); 
    }
    /*Inicialitzem punters*/
    a = (double **)malloc(m*sizeof(double *));
    mat = (double **)malloc(n*sizeof(double *));
    b = (double *)malloc(m*sizeof(double));
    vec = (double *)malloc(n*sizeof(double));
    /*Inicialitzem vectors matriu a i donem valors als elements*/
    for(i = 0; i<m; i++){
        a[i] = (double *)malloc(n*sizeof(double));
        for(j=0;j<n;j++){
        printf("Escriu a%d%d:\n",i,j);
        scanf("%le", &a[i][j]);
        }
    }
    /*Donem valors a elements de b:*/
    for(i=0;i<m;i++){
        printf("Digues b%d: ", i);
        scanf("%le", &b[i]);
    }
    /*Inicialitzem matriu normal*/
    for(i = 0; i<n;i++){
        mat[i] = (double *)malloc(n*sizeof(double));
    }
    
    /*Equacions normals (omplirem mat i vec)*/
    equnor(m,n,a,b,mat,vec);
    
    /*Fem LDLt de mat*/
    index = ldlt(n,mat);
    if(index != 0) return -1;
    /*Sistema LDLtx=vec*/
    /*Primer sistema Ly=vec -> y*/
    for(i=1;i<n;i++){
        for(j=0;j<i;j++) vec[i] -= vec[j]*mat[i][j];
    }
    /*Segon sistema Da=y -> a*/
    for(i=0;i<n;i++){
        vec[i] /= mat[i][i];
    }
    /*Darrer sistema Ltx=a -> x*/
    for(i=n-1;i>=0;i--){
        for(j=i+1;j<n;j++) vec[i] -= vec[j]*mat[i][j]; 
    }
    
    /*Solucio*/
    printf("Solucio per minims quadrats: \n");
    for (i=0; i<n; i++) printf(" i = %d xi = %+.12e \n", i, vec[i]);
    printf("\n");
    
    /*Residu*/
    printf("Vector residu: \n");
    res = 0;
    for(i=0;i<m;i++){
        aux = b[i];
        for(j=0;j<n;j++) aux = aux-a[i][j]*vec[j];
        printf("i = %2d ri = %+e \n",i, aux);
        res = res + aux * aux;
    }
    res = sqrt(res);
    printf("norma 2 del residu = %e \n", res);
    return 0;
    
}

/* equacions normals */
void equnor(int m, int n, double **a, double *b, double **mat, double *vec){
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mat[i][j] = 0;
            for(k=0;k<m;k++) mat[i][j] += a[k][i]*a[k][j];
        }
    }
    for(i=0;i<n;i++){
        vec[i] = 0;
        for(k=0;k<m;k++) vec[i] += a[k][i]*b[k];
    }
    
    /* escriptura equacions normals (opcional) */
   printf("equacions normals \n");
   for (i=0; i<n; i++) {
      for (j=0; j<n; j++) printf(" %+e ", mat[i][j]);
      printf(" | %+e \n", vec[i]);
   }
   printf("\n");
   /* */
   return;
    
}



/* factorització LDLt */
int ldlt(int n, double ** mat)
{
    int i, j, k;

    for(i=1;i<n;i++){
    mat[i][0] /= mat[0][0];
    }
    
    for(j=1;j<n-1;j++){
        for(k=0;k<j;k++) mat[j][j] -= mat[j][k]*mat[j][k]*mat[k][k];
        for(i=j+1;i<n;i++){
            for(k=0;k<j;k++) mat[i][j] -= mat[i][k]*mat[k][k]*mat[j][k];
            if(mat[i][j]<tol) return -1;
            mat[i][j] /= mat[j][j];
        }
    }
    for(k=0;k<n-1;k++) mat[n-1][n-1] -= mat[n-1][k]*mat[n-1][k]*mat[k][k];

    /* elements de sobre de la diagonal: simetria */
   for (i=0; i<n-1; i++) {
      for (k=i+1; k<n; k++) mat[i][k] = mat[k][i];
   }

   /* escriptura factorització (opcional) */
   printf("factoritzacio \n");
   for (i=0; i<n; i++) {
      for (j=0; j<n; j++) printf(" %+e ", mat[i][j]);
      printf(" \n");
   }
   printf("\n");
   /* */
   return 0;
}
