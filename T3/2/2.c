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

#define PI acos(-1.0)

double fun(double x){
    double y;
    y = sin(x);/*/exp(x)/fabs(x);*/
    return y;
    
}
int main(void){
    int i,k,n;
    double a,b,hEqui, *xEqui, *fEqui, *xCheb, *fCheb, x, p; /*Equi: amb abscisses equidistants. Cheb: amb abscisses de Chebyschev*/
    printf("Digues n:\n");
    scanf("%d",&n);
    /*n és el grau del polinomi. per un polinomi de grau n necessitem n+1 punts*/
    n++;
    printf("Digues a,b de l'interval [a,b]:\n");
    scanf("%le", &a);
    scanf("%le", &b);
    /*Definim h per tal de separar l'interval en n elements equidistants: (Les abscisses de txebitxev depenen de cada i al cosinus)*/
    hEqui = (b-a)/(n-1.);
    /*Omplim els vectors xi i fi (pel cas equidistant i de Chebyschev)*/
    xEqui = (double*)malloc(n*sizeof(double));
    fEqui = (double*)malloc(n*sizeof(double));
    xCheb = (double*)malloc(n*sizeof(double));
    fCheb = (double*)malloc(n*sizeof(double));
    /*Omplim les abscisses x i les funcions utilitzant aquestes abscisses:*/
    for(i = 0;i<n;i++){
        xEqui[i] = a + hEqui*i;
        fEqui[i] = fun(xEqui[i]);
        xCheb[i] = a + ((b - a)/ 2.) * (1 + cos((2.*i+1)/(n) * PI/2));
        fCheb[i] = fun(xCheb[i]);
    }
    /*Mètode diferències dividides:*/
    for(k=1;k<n;k++){
        for(i=n-1;i>=k;i--){
            fEqui[i] = (fEqui[i] - fEqui[i-1]) / (xEqui[i] - xEqui[i-k]);
            fCheb[i] = (fCheb[i] - fCheb[i-1]) / (xCheb[i] - xCheb[i-k]);
        }
    }
    /*Mostrem els vectors de les diferències dividides resultants en cada cas: */
        printf("Interpolacio en abscisses equidistants. Diferencies dividides:\n");
    for(i = 0; i < n; i++){
        printf("a%d = %e\n", i, fEqui[i]);
    }
    printf("\n");
    
    printf("Interpolacio en abscisses de Chebyschev. Diferencies dividides:\n");
    for(i = 0; i < n; i++){
        printf("a%d = %e\n", i, fCheb[i]);
    }
    printf("\n");
    /*Avaluem en Horner diversos punts de l'interval i mirem l'error amb la funció original.*/
    printf("Evaluem en 10 punts de [a,b] amb Horner:\n");
    for(x=a; x<=b; x = x +(b-a)/10.){
        /*Hornes amb equidistants*/
        p = fEqui[n-1];
        for(k=n-2;k>=0;k--){
            p = p*(x - xEqui[k]) + fEqui[k];
        }
        printf("x = %e\n",x);
        printf("Equi: f=%+.6e   err=%+.6e   ", p, p-fun(x));
        /*Hornes amb Chebyschev*/
        p = fEqui[n-1];
        for(k=n-2;k>=0;k--){
            p = p*(x - xCheb[k]) + fCheb[k];
        }
        printf("Cheby: f=%+.6e   err=%+.6e\n",p, p-fun(x));
        
    }
    
    return 0;
}
