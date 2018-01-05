/*
 (2) Problema d’interpolaci´o d’Hermite: donats (xi, fi, gi) , i = 0, 1, 2, . . . n, amb totes
les abscisses xi diferents entre si, cal trobar p(x) ∈ P2n+1[x] tal que p(xi) = fi
, p'(xi) =gi, ∀i = 0 ÷ n.
(3) Els problemes anteriors s´on problemes d’interpolaci´o polinomial d’una taula de valors.
Si els valors fi
i gi s´on, respectivament, f(xi) i f'(xi) per alguna determinada funci´o f(x),
llavors s’anomenen problemes d’interpolaci´o polinomial d’una funci´o.
 */
/*Funció de prova a interpolar*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double fun(double x){
    double y;
    y = sin(x);
    return y;
}
/*Derivada*/
double dfun(double x){
    double y;
    y = cos(x);
    return y;
}
int main (void){
    int i, m, j;
    double **M,a,b,h, *r;
    printf("Digues m:");
    scanf("%d",&m);
    printf("Digues a i b de l'interval [a,b]: \n");
    scanf("%le %le", &a, &b);
    /*Agafem m+1 ternes (xi, fi, gi). Quantitat de condicions: 2(m+1) = 2m + 2*/
    M = (double**)malloc((m+1)*sizeof(double*));
    /*Donem valors a les ternes. Utilitzem abscisses equidistants: h = (b-a) / (m+1)-1 = (b-a) / m*/
    h = (b-a) / (double)m;
    for(i=0;i<(m+1);i++){
        M[i] = (double*)malloc(3*sizeof(double));
        M[i][0] = a + (i*h);
        M[i][1] = fun(M[i][0]);
        M[i][2] = dfun(M[i][0]);
    }
    
    /*Diferències dividides: Cada cop que es divideixi per 0 sustituim per la derivada.*/
    r = (double*)malloc(((2*m)+1)*sizeof(double)); 
    /*Fem el pas k=1*/
    for(i=0;i<(2*m)+1;i++){
        if(i%2==0){
            r[i] = M[i/2][2];
        }else{
            r[i] = (M[i/2 + 1][1] - M[i/2][1]) / (M[i/2+1][0] - M[i/2][0]);
        }
    }
    /*Fem els altres passos: k=2,...,n*/
    for(i=1; i<=2*m; i++){
        /*printf("\n");*/
        for(j=2*m;j>=i;j--){
            /*printf("%f-%f/%f-%f ,", r[j],r[j-1], M[j/2+j%2][0],M[(j-i)/2][0]);*/
            r[j] = (r[j]-r[j-1]) / (M[j/2+j%2][0]-M[(j-i)/2][0]);
        }
    }
    printf("Solucions:\ni=0  r=%e\n",M[0][1]);
    for(i=0;i<(2*m)+1;i++){
        printf("i=%d  r=%e\n",i+1, r[i]);
    }
    
    return 0;
}