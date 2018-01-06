#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*Funció d'exemple: e^x*/
double fun(double x){
    double y;
    y = 1/(1.+x);
    return y;
}
/*Fòrmula trapezis:*/
double trap(int n,double a, double h){
    double y = 0.;
    double x = 0;
    int i;
    for (i=1;i<n;i++){
        x = a + i*h;
        y += h*fun(x);
    }
    y += h*(fun(a)+fun(x+h))/2;
    return y;
}
/*diferenciació:*/

int diferenciacio(double** M,double a,double h,double q,int k,double prec, int n){
    int i,j,o,p;
    
    M[0][0] = trap(n,a,h);
    for(i=1;i<k;i++){
        M[i][0] = trap(n*pow(q,i),a,h/pow(q,i));
        for(j=1;j<=i;j++){/*Següents columnes de fila i*/
            M[i][j] = (pow(q,2*j)*M[i][j-1]-M[i-1][j-1])/(pow(q,2*j)-1);
            if (fabs(M[i][j]-M[i][j-1])<prec){ /*Si la diferència és menor a la precisió, ja hem acabat.*/
                printf("Resultat: %.10e\n", M[i][j]);
                /*Opcional: fem print de la matriu sencera: */
                for(o=0;o<=i;o++){/* o<=i ja que imprimirem fins on haguem realitzat etapes*/
                    for(p=0;p<=o;p++){
                        printf("%.10e   ", M[o][p]);
                    }
                    printf("\n");
                }
                /**/
                return 0;
            }
        }
    }
    printf("No s'ha pogut trobar");
    return -1;
}

int main (void){
    int i,k; /**/
    double a,b,q, prec, **M, n,h;
    
    a = 0.;
    b = 1.;
    q = 2.; /*Factor d'escala. Farem trap(h), trap(h/q)...*/
    prec = 1.e-10; /*Precisió mínima requerida*/
    /*Demanem la quantitat d'etapes d'extrapolació que farem així com el valor de n*/
    printf("Digues n: \n");
    scanf("%le",&n);
    /*Llavors h=(b-a)/n i cada xi=a+i*h*/
    h=(b-a)/n;
    printf("Digues la quantitat d'etapes que farem (k): ");
    scanf("%d", &k);/*Si tenim k etapes d'extrapolació, la matriu tindrà mida k+1.*/
    k = k+1;
    /*Omplim la matriu: contindrà els valors trap en els diferents punts h, h/q, h/q^2... (files) en els diferents passos(columnes):*/
    M = (double**)malloc(k*sizeof(double));
    /*Realment no és una matriu sino que cada fila és un vector amb i elements (per estalviar memòria)*/
    for(i = 0;i<k;i++){
        M[i] = (double*)malloc((i+1)*sizeof(double));
    }
    diferenciacio(M,a,h,q,k,prec,n);
    /**/
    return 0;
}
