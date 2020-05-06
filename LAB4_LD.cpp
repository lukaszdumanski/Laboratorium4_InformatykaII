
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "rk4.h"

//szukamy rozwi�zania r�wnania r�niczkowego (*) dy/dt= f(t,y), gdzie y= y(t) oraz znamy warunek pocz�tkowy y(t0)=y_0

double lambda = -0.5; // zmienna do pierwszego przyk�adu

double funkcja(double y, double t);//funkcja po prawej stronie r-nia (*)
double y_analit(double t);//rozwi�zanie policzone w spos�b analityczny
double euler(double t,double y,double h,double (*fun)(double,double));


void main()
{
double t0=0.2,y_0=0.5;// warunek pocz�tkowy y(0.2)=0.5
double h = 0.01; //krok ca�kowania
double t_max = 20; //g�rna granica przedzia�u
double eps_eulera, eps_rk4; // b��dy odpowiednio w metodzie Eulera i w metodzie RK4

int a = 0; //zmienna pomocnicza
printf("Wykres funkcji (0) lub bledu wzglednego(1)\n");
scanf("%d", &a);

graphics(800, 600);
	if (a == 0)
		scale(0, -5, t_max, 5); 
	else
	{
		scale(0, 0, t_max, 0.2);
		title("Blad Eulera  (bialy) i RK4 (zielony)", "", "");
	}


//metoda Eulera
    double t = t0;
	double y = y_0;
	for (int i = 0; i < t_max/h; i++)
	{
		t += h;  
		y += h*funkcja(t, y); 
		
		
		eps_eulera = fabs(y - y_analit(t)) / y; //wyiczamy b��d 
		
		if (a == 0) //rysuje wykres
			circle(t, y, 1);//funkcji
		else
			circle(t, eps_eulera, 1);//b��du
	}


	//metoda RK4
	t = t0;
	y = y_0;
	for (int i = 0; i < t_max / h; i++)
	{
		t += h; 
		y = rk4(t, y, h, funkcja);
		
		
		eps_rk4 = fabs(y - y_analit(t)) / y;
		setcolor(0.6);
		if (a == 0)
			circle(t, y, 1);
		else
			circle(t, eps_rk4, 1);
	}
	

	

	//rozwi�zanie analitycznie
	if (a == 0)
		for (int i = 0; i < t_max; i++)
		{
			setcolor(1);
			circle(i, y_analit(i), 3);
		}
	wait();
}


double funkcja(double t, double y)
{
	return 100*(sin(t)-y);
}
double y_analit(double t) 
{
	return (sin(t)-0.01*cos(t)+0.01*exp(-100.*t))/1.0001;
}