#include<stdio.h>
#include<omp.h>

double f(double x) {
	return x;
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

	printf("%f \n", aproximarArea(1, 4, 23));

}
