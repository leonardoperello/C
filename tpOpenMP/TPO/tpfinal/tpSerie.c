#include <stdio.h>
#include <stdlib.h>

double f(double x){
return x*x*x*x*x*x*x*x*x;
}

void main(){

double b = 900000000;
double a = 1;
int n = 9000000;

double h = (b - a) / n;
double aprox = (f(a) + f(b)) / 2.0;
int i;
for(i = 1; i < n; i++){
	double x_i = a + i * h;
	aprox += f(x_i);
}

aprox = h * aprox;

printf("a: %f b: %f n: %d \n", a, b, n);
printf("aprox %f \n", aprox);

}
