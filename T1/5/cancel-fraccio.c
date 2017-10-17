/* cancel-fraccio.c
Observació de la cancel·lació que hi ha en el càlcul de
(1/x) ( (1-x)/(1+x) - 1/(1+4x) )
quan x ~ 0
Una expressió equivalent és  (2-4x)/(1+5x+4x*x)
*/
#include <stdio.h> 
#include <math.h> 

int main(void)
{
   int i, n = 15;
   double x, y, r;
   
   printf("    x        y amb cancel·lacio      y sense cancel·lacio     err abs \n");
   for (i=1; i<=n; i++) {
      x = pow(10.,-i);
      y = (1-x)/(1+x)-1/(1+4*x);
      y = y/x;
      r = (2-4*x)/(1+5*x+4*x*x);
      printf(" %+.2le %+.16le %+.16e %+.6le\n", x, y, r, r-y);
   }

   return 0;
}
