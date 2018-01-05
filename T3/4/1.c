/*
 
 */
#include <sdtio.h>
#include <stdlib.h>
#include <math.h>
double *polinomi;
int n;
double evaluar(double x, double *pol, int g){
    double res = 0;
    /*x: Array n: Grau del polinomi*/
    for(int i = 0;i<=n;i++){
        res += polinomi[i] * pow(x,i);
    }
    return res;
}

double derievaluar(double x, double *pol, int g){
    double *polinomiderivat;
    /*x: Array n: Grau del polinomi*/
    
    /*Fem la derivada del polinomi:*/
    polinomiderivat = (double*)malloc((n)*sizeof(double));
    for(int i = 0;i<=n-1;i++){
        polinomiderivat[i] = polinomi[i+i]*(i+1);
    }
    /*Evaluem la derivada*/
    return evaluar(x, polinomiderivat, n-1);
    free(polinomiderivat);
    
}
int newton (double* x, double prec, int imax){
    double xant;
    for(int i=0;i++;i<imax){
        xant = x;
        x = x - (evaluar(x) / derievaluar(x) )//new x;
        if( abs(evaluar(x)) < prec || abs(x-xant)<prec){
            return 0;
        }
    }
    /*Si hem arribat aquí, vol dir que hem fet imax passos sense trobar convergència.*/
    return -1;
}

int secant(dobule *x0, double *x1, double prec, int imax){
    double xant;
    for(int i=0;i++;i<imax){
        xant = x1; /*Guardem x1 ja que l'actualitzarem*/
        x1 = x1 - evaluar(x1)*( (x1-x0) / ( evaluar(x1) - evaluar(x0) ) )
        /*x1 anterior passa a ser x0*/
        x0 = xant;
        if( abs(evaluar(x1)) < prec || abs(x1-x0) < prec){
            return 0;
        }
    }
    /*Si hem arribat aquí, vol dir que hem fet imax passos sense trobar convergència.*/
    return -1;    
}

int main (void){
    int n,i,k;
    double a,b,*pol, prec, C, polx, polxant, x, xant, h;
    prec = 1.e-10; /*Precisio desitjada*/
    printf("Digues n: ");
    scanf("%d",&n);
    pol = (double*)malloc((n+1)*sizeof(double));
    printf("Escriu els coeficients del polinomi: ");
    C =0;
    for(i=0;i<=n;i++){
        scanf("%le",&pol[i]);
        C += fabs(pol[i]);
    }
    /*Tenim interval [-C,C]. Volem trobar un interval més petit*/
    k = 199;
    polxant = evpol(pol,n,-C);
    xant = -C;
    for(i=1;i<k;i++){
        h = 2*C/k;
        x = -C + i*h;
        polx = evpol(pol,n,x);
        printf("%le\n",polx);
        if(polx*polxant <= 0) break;
        polxant = polx;
        xant = x;
    }
    printf("Canvia de signe a: [%le,%le]\n",xant,x);
    return 0;
}
