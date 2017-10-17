/* Ax+y.c 
Calcul de l'actualitzacio y <- y+Ax
A mxn, x nx1, y mx1
Dos algorismes: orientat per files / orientat per columnes
Generacio aleatoria de dades
Temps d'execucio
*/

#include<stdio.h>    
#include<stdlib.h>  
#include <time.h>  

int main(void)
{
   double **A, *x, *y, t;
   int m, n, i, j;
   clock_t init, fint;

   srand( time(NULL) );
   
   scanf("%d %d", &m, &n);
  
   while (m>0 && n>0) {

   A = (double **)malloc( m*sizeof(double *) );
   if ( A==NULL ) return 2;
   for (i=0; i<m; i++) {
      A[i] = (double *)malloc( n*sizeof(double) );
      if ( A[i]==NULL ) return 3; 
   }
   x = (double *)malloc( n*sizeof(double) );
   y = (double *)malloc( m*sizeof(double) );
   if ( x==NULL || y==NULL ) return 4;

   /* algorisme orientat per files */
   for (i=0; i<m; i++) {
      for (j=0; j<n; j++) A[i][j] = ( (double)rand() )/RAND_MAX;
   }
   for (j=0; j<n; j++) x[j] = ( (double)rand() )/RAND_MAX;
   for (i=0; i<m; i++) y[i] = ( (double)rand() )/RAND_MAX;

   init = clock();
   for (i=0; i<m; i++) { 
      for (j=0; j<n; j++) {
         y[i] = y[i]+A[i][j]*x[j];
      }
   }
   fint = clock();
   t = (double)(fint-init)/CLOCKS_PER_SEC;
   printf("m=%8d, n=%8d, fil, t=%+8.2f, t/mn= %+.2e\n", m, n, t, t/(m*n));

   /* algorisme orientat per columnes */
   for (i=0; i<m; i++) {
      for (j=0; j<n; j++) A[i][j] = ( (double)rand() )/RAND_MAX;
   }
   for (j=0; j<n; j++) x[j] = ( (double)rand() )/RAND_MAX;
   for (i=0; i<m; i++) y[i] = ( (double)rand() )/RAND_MAX;

   init = clock();
   for (j=0; j<n; j++) { 
      for (i=0; i<m; i++) {
         y[i] = y[i]+A[i][j]*x[j];
      }
   }
   fint = clock();
   t = (double)(fint-init)/CLOCKS_PER_SEC;
   printf("m=%8d, n=%8d, col, t=%+8.2f, t/mn= %+.2e\n", m, n, t, t/(m*n));
   printf("\n");
   
   for (i=0; i<m; i++) free(A[i]);
   free(A);
   free(x);
   free(y);

   scanf("%d %d", &m, &n);
   }

   return 0;
}
