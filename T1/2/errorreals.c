#include <stdio.h>
#include <math.h>

int main(void){
    double inicial, finall,a,b,h;
    int n,i;
    printf("Introdueix un valor inicial i un final tal que l'inicial sigui major que el final\n");
    scanf("%le %le", &inicial, &finall);
    printf("Introdueix un nombre ""n"" per n>10000\n");
    scanf("%d", &n);
    h=(finall-inicial)/(double)n;
    for(i=0, a=inicial; i<n; i++){
        a=a+h;
        b=(float)a;
        printf("%d     %le     %e      %le    %le\n",i,a,(float)b, fabs(a-b), fabs((a-b)/a));
    }
    return(0);
}
