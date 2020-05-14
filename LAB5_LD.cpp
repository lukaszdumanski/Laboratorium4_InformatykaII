 
#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"
void rhs(double t, double* X, double* F);
void veuler( double t, double* X, double h, int n, void (*fun)(double, double*, double*), double* X1);

void main()
{
	
    FILE*plik;
    plik = fopen ("dane.txt", "w");

    int n = 2;
    double t, tk, h, a0, w0;
    double* Xe, * Xle, * Xr, * Xlr;
    a0 = 0.2;
    w0 = 0.0;
    h = 1e-3;
    tk = 10.0;
    Xe = (double*)malloc(n * sizeof(double));
    Xle = (double*)malloc(n * sizeof(double));
    Xr = (double*)malloc(n * sizeof(double));
    Xlr = (double*)malloc(n * sizeof(double));
    Xe[0] = w0;
    Xr[0] = w0;
    Xe[1] = a0;
    Xr[1] = a0;
    for(t = 0; t <= tk; t=t+h ){
        veuler(t, Xe, h, n, rhs, Xle);
        vrk4(t, Xr, h, n, rhs, Xlr);
        printf("%lf\t%lf\t%lf\t%lf\t%lf\n", t, Xe[0], Xr[0], Xe[1], Xr[1]); 
        fprintf(plik, "%lf\t%lf\t%lf\t%lf\t%lf\n", t, Xe[0], Xr[0], Xe[1], Xr[1]); 
        Xe[0] = Xle[0];
        Xe[1] = Xle[1];
        Xr[0] = Xlr[0];
        Xr[1] = Xlr[1];
        }
    free(Xe);
    free(Xle);
    free(Xr);
    free(Xlr);
    fclose(plik);
}
void rhs(double t, double* X, double* F)
{
    double g, l;
    g = 9.81;
    l = 1.0;
    F[0] = (-1.0) * g / l * sin(X[1]);
    F[1] = X[0];
}
void veuler( double t, double* X, double h, int n, void(*fun)(double, double*, double*), double* X1)
{
    double* F;
    F = (double*)malloc(n * sizeof(double));
    fun(t, X, F);
    X1[0] = X[0] + (h * F[0]);
    X1[1] = X[1] + (h * F[1]);
    free(F);
}
