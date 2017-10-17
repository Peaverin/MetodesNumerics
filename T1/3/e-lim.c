/* e-lim.c
aproximació de    e     per   (1 + 1/n)**n , n = 10**i, i=1,2,...,15

l'error teòric és el de la variable errteo (a ordre 2 en 1/n)

la diferència entre l'error en l'aproximació i l'error teòric es pot
explicar per propagació de l'error
Fem f(x)=(1+x)**n  per a  x: valor guardat de  1/n
El factor de propagació de l'error de x cap a f(x) és 
n (1+x)**(n-1) ~ en  (quan  n  és gran)
*/

#include <stdio.h> 
#include <math.h> 

int main(void)
{
   int i, N;
   double n, en, e, err, errteo;

   N = 15;
   e = exp(1.);
   
   n = 1.;
   for (i=1; i<=N; i++) {
      n = n*10.;
      en = pow(1.+1./n, n);
      err = en - e;
      errteo = e/(2*n)-11*e/(24*n*n);  
      printf("n=%.2le e_n=%+.20f err_n=%+.6le errteo=%+.6le\n", n, en, err, errteo);
   }

   return 0;
}
