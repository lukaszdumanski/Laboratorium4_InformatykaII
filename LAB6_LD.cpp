
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"

void HilbertMatrix(int N, double** H); //funkcja wypelniajaca macierz Hilberta
void DisplayMatrix(int N, double** H); //funkcja. ktora wyswietla macierz Hilberta
void ComputeVec(int N, double** H, double* b); // funkcja wypelniajaca wektor prawych stron
void plotVec(int N, double* v);//funkcja wypisujaca wektor na ekran


void main()
{
	//wczytujemy N czyli nasza liczbe rowan z klawiatury
	int N, iter;
	printf("Podaj N: ");
	scanf("%d",&N);
	//deklaracja tablic
	double* b, *x;
	double** H;
	b = (double*)malloc(N * sizeof(double));
	x = (double*)malloc(N * sizeof(double));
	H = (double**)malloc(N * sizeof(double*));
	for (iter = 0; iter < N; iter++)
	{
		H[iter] = (double*)malloc(N* sizeof(double));
	}
	HilbertMatrix(N, H);
	DisplayMatrix(N,H);
	ComputeVec(N, H, b);
	plotVec(N,b);
	gauss(N,H,x,b);
	plotVec(N,x);
}


void HilbertMatrix(int N,double** H)
{
	int iter, jter;
	for ( iter = 0; iter<N; iter++)
	{
		for (jter = 0; jter < N; jter++)
		{
			H[iter][jter] = 1.0 / (1.0 + iter + jter);
		}
	}
}

void DisplayMatrix(int N, double** H)
{
	int iter, jter;
	printf("\n Macierz H: \n\n");
	for(iter = 0; iter < N; iter++)
	{
		for (jter = 0; jter < N; jter++)
		{
			printf("%lf", H[iter][jter]);
		}
		printf("\n");
	}
}

void ComputeVec(int N, double** H, double* b)
{
int iter, jter;
double sum;
	for ( iter = 0; iter<N; iter++)
	{
		sum = 0.0;
		for (jter = 0; jter < N; jter++)
		{
			sum += H[iter][jter];
		}
		b[iter] = sum;
    }
}

void plotVec(int N, double* v)
{
	int iter;
	printf(" \n\n Podany wektor: \n\n");
	for(iter=0; iter<N; iter++)
	{
		printf("%lf \n", v[iter]);
	}
}







