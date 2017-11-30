/*Exercici 2 Tema 3*/
/* Interpolacio de Lagrange d'una funcio per diferencies dividides */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1.0)

double func(double x, char op){
    double res = 0;
    switch(op){
        case 'S':
            res = sin(x);
            break;
        case 'C':
            res = cos(x);
            break;
        case 'E':
            res = exp(x);
            break;
        case 'A':
            res = fabs(x);
            break;
    }
    return res;
}

int main(void){
    
    int n, i, j;
    char op;
    double a, b, prod, coef, x, sum;
    double *xT, *xE, *fT, *fE;
    
    printf("Entra la dimensio: ");
    scanf("%d", &n);
    n++;
    
    xT = (double *) malloc(n * sizeof(double));
    xE = (double *) malloc(n * sizeof(double));
    fT = (double *) malloc(n * sizeof(double));
    fE = (double *) malloc(n * sizeof(double));
    
    
    printf("Entra els extrems de l'interval [a, b] (Ex: '0 1'): ");
    scanf("%le", &a);
    scanf("%le", &b);
    
    do{
        printf("Quina funcio es vol avaluar: sin(x), cos(x), exp(x), |x|? (S / C / E / A)\n");
        scanf(" %c", &op);        
    } while(op != 'S' && op != 'C' && op != 'E' && op != 'A');
    
    for(i = 0; i < n; i++){
        xE[i] = a + ((b - a)/ (n-1.)) * i;
        xT[i] = a + ((b - a)/ 2.) * (1 + cos((2.*i+1)/(n) * PI/2));
        fE[i] = func(xE[i], op);
        fT[i] = func(xT[i], op);
    }
    
    for(i = 1; i < n; i++){
        for(j = n-1; j >= i; j--){
            fE[j] = (fE[j] - fE[j-1]) / (xE[j] - xE[j-i]);
            fT[j] = (fT[j] - fT[j-1]) / (xT[j] - xT[j-i]);
        }
    }
    
    printf("Interpolacio en abscisses equidistants. Diferencies dividides:\n");
    for(i = 0; i < n; i++){
        printf("a%d = %e\n", i, fE[i]);
    }
    printf("\n");
    
    printf("Interpolacio en abscisses de Txebishev. Diferencies dividides:\n");
    for(i = 0; i < n; i++){
        printf("a%d = %e\n", i, fT[i]);
    }
    printf("\n");
    
    
    for(x = a; x <= b; x += (b-a)/10.){
        
        printf("x = %+e     ", x);
        
        sum = 0;
        for(j = 0; j < n; j++){
            prod = fE[j];
            for(i = j-1; i >= 0; i--){
                prod *= x - xE[i];
            }
            sum += prod;
        }
        
        printf("fE = %+e     erE = %+e     ", sum, sum - func(x, op));     
        
        sum = 0;
        for(j = 0; j < n; j++){
            prod = fT[j];
            for(i = j-1; i >= 0; i--){
                prod *= x - xT[i];
            }
            sum += prod;
        }
        
        printf("fT = %+e     erT = %+e\n", sum, sum - func(x, op));
    }
    
    return 0;
}
