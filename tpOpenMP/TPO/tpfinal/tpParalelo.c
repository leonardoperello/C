#include<stdio.h>
#include<omp.h>

double f(double x) {
	return x*x*x*x*x*x*x*x*x;
}


double aproximarArea(double a, double b, int n) {
double h = (b - a) / n;
double aprox = (f(a) + f(b)) / 2.0;
int i;

#pragma omp parallel for reduction (+:aprox)
	for (i = 1; i < n; i++) {
		double x_i = a + i * h;
		aprox += f(x_i);
		}
aprox = h * aprox;
return aprox;


}

int main() {
double a = 1;
double b = 900000000;
int n = 9000000;

	printf("a: %f b: %f n: %d \n", a, b, n);
	printf("%f \n", aproximarArea(1, b, n));

}
