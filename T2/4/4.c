#include<stdio.h>    
#include<stdlib.h>  
#include <time.h>  
#include <math.h>

#define tol 1.e-14
#define a 1.e0
#define b 2.e0
#define alfa 1.e0
#define beta 2.e0
double funp(double x) { return -2/x; }
double funq(double x) { return 2/(x*x); }
double funr(double x) {return sin(log(x))/(x*x);}

double funy(double x){
    double c1, c2, y;
    c2 = (8-12*sin(log(2.))-4*cos(log(2.)))/70;
    c1 = 1.1-c2;
    y = c1*x+c2/(x*x)-0.3*sin(log(x))-0.1*cos(log(x));
    return y;
}

int tridiagonal(double *s,double *D,double *S,double *x,int n){
    /*
    s = s
    D = D 
    S = S  
    x = Vector de termes independents - es substituirà per la solució del sistema triD
    n = mida de la matriu
    */
    int i;
    double m;
    for(i=1;i<n;i++){
        if(D[i-1] < tol){
            return 1;
        }
        m = (s[i-1]/  D[i-1]);
        D[i] = D[i] - ( S[i-1] * m );
        x[i] = x[i] - ( x[i-1] * m);
    }
    
    x[n-1] = x[n-1]/D[n-1];
    for(i = n-2; i >=0 ; i--){
        if(D[i] < tol){
            return 2;
        } 
        x[i] = (x[i]-x[i+1]*S[i]) / D[i];
    }
    return 0;

}



int main(void){
    double *s, *D, *S, *x, h;
    int i, n;
    printf("Digues la mida de la matriu triD: \n");
    scanf("%d",&n);
    
    s = (double *)malloc((n-1)*sizeof(double));
    D = (double *)malloc(n*sizeof(double));
    S = (double *)malloc((n-1)*sizeof(double));
    x = (double *)malloc(n*sizeof(double));
    
    h = (b-a)/(n+1);
    
    for(i=0;i<n;i++){
        D[i] = 2+h*h*funq(a + (i+1)*h);
    }
    
    x[0] = -h*h*funr(a+h) + (1+h*funp(a+h)/2)*alfa;
    for(i=1;i<n-1;i++){
        x[i] = -h*h*funr(a + (i+1)*h);
    }
    x[n-1] = -h*h*funr(a+n*h) + (1-h*funp(a+n*h)/2)*beta;
        
    for(i=0;i<n-1;i++){
        s[i] = -1 - (h/2.0)*funp(a+(i+2)*h);
    }
    
    for(i=0;i<n-1;i++){
        S[i] = -1 + (h/2.0)*funp(a+(i+1)*h);
    }
    
    
    tridiagonal(s,D,S,x,n);
    
    printf("Solucio: \n");
    printf("y(1) = 1\n");
    for(i=0;i<n;i++){
        printf("x%d = %.6le,  y(x%d) = %.6le err = +%.6le\n", i, a+(i+1)*h, i, x[i], x[i] - funy(a+(i+1)*h)  );
    }
    printf("y(2) = 2");
    
    return 0;
}
