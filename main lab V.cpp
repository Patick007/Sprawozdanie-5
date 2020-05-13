#include <math.h>
#include <stdio.h>
#include "winbgi2.h"
#include <stdlib.h>
#include "rk4.h"
#define g 9.81
#define pi 4*atan(1.0)
#define alfa 0.
#define omega 0.7
#define l 0.9
#define m 10

void rhs_fun (double t,double *X, double *F);
void veuler (double t,double *X, double h, int n ,double *F, void (*fun)(double,double*,double*), double *X1);
void e (double *X, double *E);
void main(){
	int n;
	double* X;
	double* F;
	double* X1;
	double E;
	double h = 0.004;
	printf("Liczba rownan = \n");
	scanf("%d", &n);
	X = (double*)malloc(n*sizeof(*X));
	F = (double*)malloc(n*sizeof(*F));
	X1 = (double*)malloc(n*sizeof(*X1));
	graphics(800,600);
	scale(-11, -4, 9, 3);
	X[0] = alfa;
	X[1] = omega;
	X1[0] = X[0];
	X1[1] = X[1];
	for(double t = 0; t<=10; t+=h)
	{
		setcolor(1.);
		point(X1[0]*180./pi, X1[1]);
		//vrk4(t,X,h,n,rhs_fun,X1);
		veuler(t,X,h,n,F,rhs_fun,X1);
		X[0] = X1[0];
		X[1] = X1[1];
	}
	printf("Wprowadz dowolna liczbe aby pojawil sie wykres rozk³adu energii w czasie\n");
	scanf("%lf", &X[1]);
	X[0] = alfa;
	X[1] = omega;
	setgray(1.);
	scale(0, -10, 10, 15);
	for(double t = 0; t<=10; t+=h)
	{
		
		//vrk4(t,X,h,n,rhs_fun,X1);
		veuler(t,X,h,n,F,rhs_fun,X1);
		e(X,&E);
		setcolor(0.);
		point(t,E);
		X[0] = X1[0];
		X[1] = X1[1];
	}
	
	free(X);
	free(F);
	free(X1);
	wait();
}



void rhs_fun(double t, double *X, double *F)
{
	F[0] = X[1];
	F[1] = -g/l*sin(X[0]);
}
void veuler (double t,double *X, double h, int n,double *F, void (*fun)(double,double*,double*), double *X1)
{
	fun(t,X,F);
	for(int i=0;i<n;i++){
	X1[i]=X[i]+h*F[i];
	}
}
void e (double *X, double *E)
{
	*E = m*pow(l,2.)/2*pow(X[1],2.) + m*g*l*(1-cos(X[0]));
}
