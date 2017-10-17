/* Ax+y.c 
Calcul de l'actualitzacio y <- y+Ax
A mxn, x nx1, y mx1
Dos algorismes: orientat per files / orientat per columnes
Generacio aleatoria de dades
Temps d'execucio
*/

#include<stdio.h>    
#include<stdlib.h>  
#include <time.h>  
int m;
void printmatrix(double** A){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            printf("%+1.4f       ", A[i][j]);
        }
        printf("\n");
    }
     printf("\n");
}
int main(void){
    /*Farem el producte C = AxB*/
    double **A, **B, **C, t;
    int i, j, k;
    clock_t init, fint;
    srand ( time(NULL) );
    scanf("%d", &m);
    /*Generem matrius A i B*/
    A = (double **)malloc(m*sizeof(double *));
    B = (double **)malloc(m*sizeof(double *));
    C = (double **)malloc(m*sizeof(double *));
    for(i=0;i<m;i++){
        A[i] = (double *)malloc(m*sizeof(double));
        B[i] = (double *)malloc(m*sizeof(double));
        C[i] = (double *)malloc(m*sizeof(double));
    }
    /*Les generem orientat per files ( triga menys) */
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            A[i][j] = ((double)rand() / RAND_MAX);
            B[i][j] = ((double)rand() / RAND_MAX);
            C[i][j] = (double)0;
        }
    }
    
    
    /*Producte de matrius AxB:*/ 
    /*Columnes de B per files de A*/
    init = clock();
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            /*Sumatori ajk*bki*/
            for(k=0;k<m;k++){
                C[j][i] += (A[j][k] * B[k][i]);
            }
        }
    }    
    fint = clock();
    t = (double)(fint-init)/CLOCKS_PER_SEC;
    /*Prints*/
    printf("%.10e\n", t);
    
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = (double)0;
        }
    }
    /**/
    init = clock();
    for(i=0;i<m;i++){
        for(k=0;k<m;k++){
            /*Sumatori ajk*bki*/
            for(j=0;j<m;j++){
                C[j][i] += (A[j][k] * B[k][i]);
            }
        }
    }    
    fint = clock();
    t = (double)(fint-init)/CLOCKS_PER_SEC;
    /*Prints*/
    printf("%.10e\n", t);
    
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = (double)0;
        }
    }
    
    
    
    /*Recorrem primer files de A i despres columnes de B*/
    init = clock();
    for(j=0;j<m;j++){
        for(i=0;i<m;i++){
            /*Sumatori ajk*bki*/
            for(k=0;k<m;k++){
                C[j][i] += (A[j][k] * B[k][i]);
            }
        }
    }
    fint = clock();
    t = (double)(fint-init)/CLOCKS_PER_SEC;
    /*Prints*/
    printf("%.10e\n", t);
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = (double)0;
        }
    }
    /*4 El que tarda menos*/
    init = clock();
    for(j=0;j<m;j++){
        for(k=0;k<m;k++){
            /*Sumatori ajk*bki*/
            for(i=0;i<m;i++){
                C[j][i] += (A[j][k] * B[k][i]);
            }
        }
    }
    fint = clock();
    t = (double)(fint-init)/CLOCKS_PER_SEC;
    /*Prints*/
    printf("%.10e\n", t);
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = (double)0;
        }
    }
    /*5*/
    init = clock();
    for(k=0;k<m;k++){
        for(i=0;i<m;i++){
            /*Sumatori ajk*bki*/
            for(j=0;j<m;j++){
                C[j][i] += (A[j][k] * B[k][i]);
            }
        }
    }
    fint = clock();
    t = (double)(fint-init)/CLOCKS_PER_SEC;
    /*Prints*/
    printf("%.10e\n", t);
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = (double)0;
        }
    }
    /*6*/
    init = clock();
    for(k=0;k<m;k++){
        for(j=0;j<m;j++){
            /*Sumatori ajk*bki*/
            for(i=0;i<m;i++){
                C[j][i] += (A[j][k] * B[k][i]);
            }
        }
    }
    fint = clock();
    t = (double)(fint-init)/CLOCKS_PER_SEC;
    /*Prints*/
    printf("%.10e\n", t);
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            C[i][j] = (double)0;
        }
    }
    return 0;
}
