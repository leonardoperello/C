#include <omp.h>
#include <stdio.h>

void main(){
int x = 1;
#pragma omp parallel num_threads(2)
{
	#pragma omp critical
	x++;
	#pragma omp atomic
	x++;
}
printf("%d \n", x);
}
