#include <omp.h>
#include <stdio.h>

double f(int x){
return x; 
}

void main(){
int a = 1, b = 4, n = 4;
int h = (b-a) / n;

int j = 5;
double aprox = (f(a) +f(b)) / 2.0;

int x_1;

	#pragma omp for reduction (+:aprox) { 

	for(int i = 1; i <= n-1; i++){
	x_1 = a + i *h;
	aprox += f(x_1);
	}

aprox = h * aprox;
return aprox;
}
printf("%f", aprox);

}
