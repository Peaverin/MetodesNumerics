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
double fun(x){
    double y;
    y = sin(x);
    return y;
}
/*Derivada*/
double dfun(x){
    double y;
    y = cos(x);
    return y;
}
int main (void){
    int i,m;
    double **M,a,b,h, *r;
    printf("Digues m:");
    scanf("%d",&m);
    printf("Digues a i b de l'interval [a,b]: \n");
    scanf("%e %e", &a, &b);
    /*Agafem m+1 ternes (xi, fi, gi). Quantitat de condicions: 2(m+1) = 2m + 2*/
    M = (double**)malloc((m+1)*sizeof(double*));
    /*Donem valors a les ternes. Utilitzem abscisses equidistants: h = (b-a) / (m+1)-1 = (b-a) / m*/
    h = (b-a) / m;
    for(i=0;i++;i<(m+1)){
        M[i] = (double*)malloc(3*sizeof(double));
        M[i][0] = a+i*h;
        M[i][1] = fun(M[i][0]);
        M[i][2] = dfun(M[i][0]);
    }
    
    /*Diferències dividides: Cada cop que es divideixi per 0 sustituim per la derivada.*/
    r = (double*)malloc((2*m)*sizeof(double)); 
    /*Fem el pas k=1*/
    for(i=0;i<2*m;i++){
        if(i%2==0){
            r[i] = M[i/2][2];
        }else{
            r[i] = (M[i/2 + 1][1] - M[i/2][1]) / (M[i/2+1][0] - M[i/2][0]);
        }
    }
    /*Fem els altres passos: k=2,...,n*/
    return 0;
}
