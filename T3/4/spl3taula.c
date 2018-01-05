/* spl3taula.c
Càlcul del spline cúbic interpolador natural 
d'una taula de valors
*/

#include <stdio.h>
#include <math.h>

#define N 20      /* nombre màxim de subintervals */
#define M 200     /* s'avaluarà el spline en M+1 punts */

int main(void)
{
   int n, j, i;
   double x[N+1], y[N+1], h[N], m[N+1];
   double a[N], b[N];
   double d[N], l[N], u[N];
   double pas, z, s;
   
   /* nombre de subintervals */
   scanf("%d", &n);
   /* comprovació que tenim prou memòria reservada */
   if ( n<=0 || n>N ) return 1;
   /* abscisses i ordenades que cal interpolar */
   for (j=0; j<=n; j++) scanf("%le %le", &x[j], &y[j]);
   /* comprovació que les abscisses estiguin en ordre creixent */
   for (j=0; j<n; j++) {
      if ( x[j]>=x[j+1] ) return 2;
   }
   /* longituds dels subintervals */
   for (j=0; j<n; j++) h[j+1] = x[j+1]-x[j];
   /* coeficients del sistema tridiagonal (n-1)x(n-1),
      components de 1 a n-1 */
   /* matriu */
   for (j=1; j<n; j++) d[j] = (h[j]+h[j+1])/3.;
   for (j=1; j<n-1; j++) u[j] = h[j+1]/6.;
   for (j=2; j<n; j++) l[j] = h[j]/6.;
   /* terme independent */
   for (j=1; j<n; j++) 
      m[j] = ((y[j+1]-y[j])/h[j+1]-((y[j]-y[j-1])/h[j]));
   /* components auxiliars corresponents a spline natural*/
   m[0] = 0.;
   m[n] = 0.;
   /* factorització LU */
   for (j=2; j<n; j++) {
      l[j] = l[j]/d[j-1];
      d[j] = d[j]-l[j]*u[j-1];
   }
   /* resolució sistema triangular inferior */
   for (j=2; j<n; j++) m[j] = m[j]-l[j]*m[j-1];
   /* resolució sistema triangular superior */
   m[n-1] = m[n-1]/d[n-1];
   for (j=n-2; j>=1; j--) m[j] = (m[j]-u[j]*m[j+1])/d[j];
   /* constants d'integració */
   for (j=0; j<n; j++) {
      b[j] = y[j]-m[j]*h[j+1]*h[j+1]/6;
      a[j] = (y[j+1]-y[j])/h[j+1]-(m[j+1]-m[j])*h[j+1]/6;
   }
   /* avaluació del spline en M+1 punts equidistants */
   pas = (x[n]-x[0])/M;
   for (i=0; i<=M; i++) {
      z = x[0]+i*pas;
      /* a quin subinterval j pertany el punt z? */
      j = 0;
      while ( j<n-1 && z>x[j+1]) j = j+1;
      /* avaluació de S(z) */
      s = b[j];
      s = s+a[j]*(z-x[j]);
      s = s+(m[j+1]/(6*h[j+1]))*pow((z-x[j]),3);
      s = s+(m[j]/(6*h[j+1]))*pow((x[j+1]-z),3);
      printf ("%+le  %+le\n", z, s);
   }
   
   return 0;
}
