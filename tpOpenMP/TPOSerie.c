#include <stdio.h>
#include <stdlib.h>

double f(int x){
return x*x*x*x*x*x*x*x*x;
}

void main(){
int b = 900000000, a = 1, n = 9000000;

int h = (b - a) / n;

int x_i;

double aprox = ( f(a) + f(b) ) / 2.0;

for(int i = 1; i <= n-1; i++){
	x_i = a + 1 * h;
	aprox += f(x_i);
}

aprox = h * aprox;

printf("aprox %f", aprox);
}
