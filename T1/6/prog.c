#include <stdio.h>
#include <math.h>

int m;
/*Funcio normal*/
double f(double x, double c){
    int k;
    double y = 1.;
    for (k=1; k<=m; k++) y=y*(x-k);
    y = y+c*pow(x, m);
    return y;
}
/*Derivada de la funcio*/
double d(double x, double c){
    int k,j;
    double y,p;
    
    y=0.;
    for(k=1; k<=m ;k++){
        p = 1.;
        for(j=1; j<=m;j++){
            if(j!=k) p=p*(x-j);
        }
        y = y + p;
    }
    y = y+m*c*pow(x, m-1);
    return y;
    
}

int main(void){
    int k,i,iter;
    double c,x,xi,fi,eps;
    
    iter = 10;
    eps = 1.e-10;
    
    printf("m=?\n");
    scanf("%d", &m);
    printf("c=?\n");
    scanf("%le",&c);
    
    for(k=1; k<=m;k++){
        x = k;
        xi = 1.;
        i = 0;
        while(i<iter && fabs(xi)>eps){
            i = i+1;
            fi = f(x, c);
            xi = fi/d(x,c);
            x = x-xi;
            printf("i=%2d x=%+.16le fi=%+.4le xi=%+4.le\n",i,x,fi,xi);
        }
        
        if(fabs(xi)<eps){
            printf("\n    k=%2d, x_k=%+.16le   ",k,x);
            printf("     dx_k=%+.4le, dx_k/c=%+.4le\n\n",x-k, (x-k)/c);
        }
    }
    return 0;
}
