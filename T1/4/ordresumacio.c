#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(void){
    float resultat, resultat2;
    int i;
    double resultat3;
    resultat = 0;
    
    for(i=1;i<INT_MAX-10;i++){
        resultat += 1./i;
    }
    printf("Ultims 10 resultats de la primera successio:\n");
    while(i!=INT_MAX){
        resultat += 1./i;
        printf("%f\n",resultat);
        i++;
    }
    resultat2 = 0;
    for(i=INT_MAX;i>10;i--){
        resultat2 += 1./i;
    }
    printf("Ultims 10 resultats de la successio a la inversa:\n");
    while(i>0){
        resultat2 += 1./i;
        printf("%f\n",resultat2);
        i--;
    }
    resultat3 = 0;
    for(i=1;i<100000;i++){
        resultat3 += 1./pow(i,2);
    }
    printf("Resultat segona successio: %f",resultat3);
    /*pi quadrat partit 6*/
    return 0;
}
