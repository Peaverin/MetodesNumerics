/*
Exercici 2 [Interpolacio de Lagrange d’una funcio per diferencies dividides]
Feu una funci´o que resolgui el problema (1)-(3) mitjan¸cant el m`etode de les difer`encies
dividides de Newton.
Tamb´e cal fer una funci´o on s’avalu¨ı la f(x) que es vol interpolar. Useu qualsevol funci´o
senzilla, per exemple, sin(x), exp(x), |x|, etc.
En el programa principal, es llegir`a n i els extrems de l’interval [a, b] on es vol fer la
interpolaci´o. Aquesta es far`a de dues maneres, en abscisses equidistant i en abscisses de
Txebishev.
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double fun(double x){
    double y;
    y = sin(x);/*/exp(x)/fabs(x);*/
    return y;
    
}
int main(void){
    int n;
    double a,b;
    printf("Digues n:\n");
    scanf("%d",&n);
    printf("Digues a,b de l'interval [a,b]:\n");
    scanf("%le", &a);
    scanf("%le", &b);
    return 0;
}
