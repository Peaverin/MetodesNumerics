/* rangenters.c
Experimentació amb operacions elementals per trobar el rang de valors que pot prendre
una variable int.
Sumem/restem 1 cada cop a dues variables fins que ja no es realitza el càlcul per trobar màxim/mínim.

Després calculem una llista de factorials amb int fins que trobem un valor que no correspongui al valor real per extreure conclusions.
*/

#include <stdio.h> 
#include <math.h> 
#include <limits.h>

int main(void)
{
    /*Trobem valors màxim i mínim*/
    int max = 0,min = 0;
    int i, I, j, factorial;
    while(min>min-1){
        min = min - 1;
    }
    while(max<max+1){
        max = max + 1;
    }

    printf("min=%d max=%d INT_MIN=%d INT_MAX=%d\n",min, max, INT_MIN, INT_MAX);
    
    /*Calculem factorials:*/
    I=34;
    for(i=1; i <= I; i++){
        factorial = 1;
        for(j=i; j>1; j--){
            factorial *= j;
        }
        printf("%d! = %d\n",i, factorial);
    }
    printf("Observem 34! es un multiple de 2^32, i el seu factorial dona 0, per tant els factorials es calculen modul 2^32.", INT_MAX);
   return 0;
   
}
