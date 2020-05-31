#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double f(double x){
return x;
}

void main(){
clock_t begin, end;
begin = clock();
double segundos;

double b = 500000000;
double a = 1;
int n = 500000;

double h = (b - a) / n;
double aprox = (f(a) + f(b)) / 2.0;

for(int i = 1; i < n; i++){
	double x_i = a + i * h;
	aprox += f(x_i);
}

aprox = h * aprox;

end = clock();

printf("aprox %f \n", aprox);

segundos = (double)(begin-end)/CLOCKS_PER_SEC;
printf("tiempo: %f \n", segundos);
}
