#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
int a  = 12; 
int random = rand();
int x = 1;
#pragma omp parallel
	printf("holi \n");
	omp_set_num_threads(2);
#pragma omp parallel
	{
	x = x + 1;
	}
#pragma omp parallel num_threads (random%4+2) if (a>10)
	printf("%d \n", x);

return 0;
}
