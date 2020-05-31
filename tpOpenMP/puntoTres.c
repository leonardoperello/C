#include <omp.h>
#include <stdio.h>

void main(){

int x, y;
x = 1;
y = 1;

#pragma omp parallel private (y) num_threads(1)
{
	x = 2;
 	y = 2;

#pragma omp parallel private (x) num_threads(1)
{
	int z = 1;
 	x = 3;
	y = 3;

}
 printf("x=%d y=%d\n", x, y);
}

printf("x=%d y=%d\n", x, y);
}
