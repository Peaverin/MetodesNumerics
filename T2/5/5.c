/* sobredet.c
resolució d'un sistema lineal sobredeterminat m x n (m >= n)
Mètode:
equacions normals + factoritzacio LDLt + resolució 3 sistemes fàcils
Al final, es calcula el vector residu i la seva norma-2
*/
#include <stdio.h>
#include <math.h>

#define N 100        /* dimensió màxima permesa */
#define tol 1.e-12   /* tolerància límit per a la factorització */

void equnor(int m, int n, double a[][N], double b[], double mat[][N], double vec[]);
int ldlt(int n, double mat[][N]);

int main(void)
{
   int m, n, i, j, index;
   double a[N][N], b[N], mat[N][N], vec[N], aux, res;
   
   /* dades */
   scanf("%d %d", &m, &n);
   if (m>N || n>N || n>m) {
      printf("dimensions incorrectes\n");
      return 1;
   }
   for (i=0; i<m; i++) {
      for (j=0; j<n; j++) scanf("%le", &a[i][j]);
   }
   for (i=0; i<m; i++) scanf("%le", &b[i]);
   
   /* equacions normals */
   equnor(m, n, a, b, mat, vec);
   
   /* factoritzacio LDLt */
   index = ldlt(n, mat);
   if ( index!=0 ) return -1;
   
   /* resolució sistema L */
   for (i=0; i<n; i++) {
      for (j=0; j<i; j++) 
            vec[i] = vec[i]-mat[i][j]*vec[j];
   }
   /* resolució sistema D */
   for (i=0; i<n; i++) vec[i] = vec[i]/mat[i][i];
   
   /* resolució sistema Lt */
   for (i=n-1; i>=0; i--) {
      for (j=i+1; j<n; j++) 
            vec[i] = vec[i]-mat[i][j]*vec[j];
   }
   
   /* escriptura resultats */ 
   printf("solucio per minim-quadrats \n");
   for (i=0; i<n; i++) printf(" i = %d xi = %+.12le \n", i, vec[i]);
   printf("\n");
   
   /* residu */
   printf("vector residu \n");
   res = 0;
   for (i=0; i<m; i++) {
      aux = b[i];
      for (j=0; j<n; j++) aux = aux-a[i][j]*vec[j];
      printf(" i = %2d ri = %+le \n", i, aux);
      res = res + aux*aux;
   }
   res = sqrt(res);
   printf("norma 2 del residu = %+le \n", res);
   printf("\n");

   return 0;
}

/* equacions normals */
void equnor(int m, int n, double a[][N], double b[], double mat[][N], double vec[])
{
   int i, j, k;
   
   for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
         mat[i][j] = 0;
         for (k=0; k<m; k++) mat[i][j] = mat[i][j]+a[k][i]*a[k][j];
      }
      vec[i] = 0;
      for (k=0; k<m; k++) vec[i] = vec[i]+a[k][i]*b[k];
   }
   /* escriptura equacions normals (opcional) */
   printf("equacions normals \n");
   for (i=0; i<n; i++) {
      for (j=0; j<n; j++) printf(" %+le ", mat[i][j]);
      printf(" | %+le \n", vec[i]);
   }
   printf("\n");
   /* */
   return;
}

/* factorització LDLt */
int ldlt(int n, double mat[][N])
{
   int i, j, k;
   
   /* fórmules recurrents per als elements de la diagonal i els de sota */
   for (j=0; j<n; j++) {
      for (k=0; k<j; k++) {
         mat[j][j] = mat[j][j]-mat[j][k]*mat[j][k]*mat[k][k];
      }
      if (fabs(mat[j][j])<tol) {
         printf("no es pot factoritzar, per j=%d es m_jj = %le\n", j, mat[j][j]);
         return -1;
      }
      for (i=j+1; i<n; i++) {
         for (k=0; k<j; k++) {
            mat[i][j] =  mat[i][j]-mat[i][k]*mat[j][k]*mat[k][k];
         }
         mat[i][j] = mat[i][j]/mat[j][j];
      }
   }
   /* elements de sobre de la diagonal: simetria */
   for (i=0; i<n-1; i++) {
      for (k=i+1; k<n; k++) mat[i][k] = mat[k][i];
   }

   /* escriptura factorització (opcional) */
   printf("factoritzacio \n");
   for (i=0; i<n; i++) {
      for (j=0; j<n; j++) printf(" %+le ", mat[i][j]);
      printf(" \n");
   }
   printf("\n");
   /* */
   return 0;
}
