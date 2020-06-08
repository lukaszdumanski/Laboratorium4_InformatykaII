#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"
void rhs(double t, double* X, double* F);


void main()
{
	
    FILE*plik;
    plik = fopen ("dane.txt", "w");
    int n = 2;
    double t, tk, h, a0, w0;
    double * Xr, * Xlr;
    scanf("%lf",&a0);
    scanf("%lf",&w0);
    scanf("%lf",&h);
    scanf("%lf",&tk);
    Xr = (double*)malloc(n * sizeof(double));
    Xlr = (double*)malloc(n * sizeof(double));
    Xr[0] = w0;
    Xr[1] = a0;
    for(t = 0; t <= tk; t=t+h ){
        vrk4(t, Xr, h, n, rhs, Xlr);
        printf("%lf\t%lf\t%lf\n", t, Xr[0], Xr[1]); 
        fprintf(plik, "%lf\t%lf\t%lf\n", t, Xr[0], Xr[1]); 
        Xr[0] = Xlr[0];
        Xr[1] = Xlr[1];
        }
    free(Xr);
    free(Xlr);
    fclose(plik);
}
void rhs(double t, double* X, double* F)
{
    double g, l;
    g = 9.81;
    l = 1.0;
    F[0] = ((-1.0) * g  * sin(X[1]))/l;
    F[1] = X[0];
}

