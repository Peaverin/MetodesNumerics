#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double *pol;
int n;

double evaluar(double x,  double *polinomi, int m){
    double res = 0;
    int i;
    /*x: Array m: grau del polinomi*/
    for(i=0;i<=m;i++){
        res += polinomi[i]*pow(x,i);
    }
    return res;
}

double derievaluar(double x, double *polinomi, int m){
    double *polinomiderivat;
    int i;
    /*x: Array n: grau del polinomi*/
    
    /*Fem la derivada del polinomi:*/
    polinomiderivat = (double*)malloc(m*sizeof(double));
    for(i = 0;i<=m-1;i++){
        polinomiderivat[i] = polinomi[i+1]*(i+1);
    }
    /*Evaluem la derivada*/
    return evaluar(x, polinomiderivat, m-1);
    free(polinomiderivat);
}

int newton (double *x, double prec, int imax){
    double xant;
    int i;
    for(i=0;i<imax;i++){
        xant = *x;
        *x -= (evaluar(*x,pol,n) / derievaluar(*x,pol,n) );
        if( fabs(evaluar(*x,pol,n)) < prec || fabs(*x-xant)<prec){
            return 0;
        }
    }
    /*Si hem arribat aquí, vol dir que hem fet imax passos sense trobar convergència.*/
    return -1;
}

int secant(double *x0, double *x1, double prec, int imax){
    double xant;
    int i;
    for(i=0;i<imax;i++){
        xant = *x1; /*Guardem x1 ja que l'actualitzarem*/
        *x1 -= evaluar(*x1,pol,n)*( (*x1-*x0) / ( evaluar(*x1,pol,n) - evaluar(*x0,pol,n)));
        /*x1 anterior passa a ser x0*/
        *x0 = xant;
        if( fabs(evaluar(*x1,pol,n)) < prec || fabs(*x1-*x0) < prec){
            return 0;
        }
    }
    /*Si hem arribat aquí, vol dir que hem fet imax passos sense trobar convergència.*/
    return -1;    
}

int main (void){
    int i,k, imax, solnewton, solsecant;
    double x, xant, polx, polxant, prec, h, C, *a, *b, *c;
    
    /*Dades arbitràries:*/
    prec = 1.e-10; /*Precisio desitjada*/
    imax = 15;
    k = 37; /*Nombre d'intents per fer l'interval [-C,C] més petit.*/
    
    /*Demanem grau i coeficients polinomi:*/
    printf("Digues el grau: ");
    scanf("%d",&n);
    printf("Escriu els coeficients del polinomi (de grau menor a major): ");
    /*Reservem la memòri pel polinomi*/
    pol = (double*)malloc((n+1)*sizeof(double));
    C =0;/*Anem calculant C a mesura que ens donen els graus*/
    for(i=0;i<=n;i++){
        scanf("%le",&pol[i]);
        C += fabs(pol[i]);
    }
    
    /*Tenim interval [-C,C]. Volem trobar un interval més petit*/
    polxant = evaluar(-C,pol,n);
    xant = -C;
    /*Reservem memòria per les variables auxiliars a,b,c: */
    a = (double*)malloc(sizeof(double));
    b = (double*)malloc(sizeof(double));
    c = (double*)malloc(sizeof(double));
    for(i=1;i<k;i++){
        /*intervals [xant, x], amb evaluació respectiva p(xant)=polxant, p(x) = polx*/
        h = 2*C/k;
        x = -C + i*h;
        polx = evaluar(x,pol,n);
        printf("%le\n",polx); /*Mostrem les avaluacions del polinomi que fem.*/
        if(polx*polxant <= 0){
            /*Variables auxiliars per cridar newton i secant. a,b per l'interval [a,b], i c pel punt mig de a i b*/
            *a = xant;
            *b = x;
            *c = (x+xant)/2;
            printf("Canvia de signe a: [%le,%le]\n",*a,*b);
            solnewton = newton(c,prec,imax);
            solsecant = secant(a,b,prec,imax);
            if(solnewton==0){
                printf("Newton: %le\n",*c);
            }else{
                printf("No convergencia amb Newton.\n");
            }
            if(solsecant==0){
                printf("Secant: %le\n",*b);
            }else{
                printf("No convergencia amb Secant.\n");
            }
        }
        polxant = polx;
        xant = x;
    }
    
    return 0;
}
