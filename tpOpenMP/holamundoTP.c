#include <stdio.h>
#include <omp.h>

void main(){

int n = 5;

#pragma omp parallel num_threads (n) 
{
	int i = omp_get_thread_num();
	printf("Hola mundo, soy el thread número %d de un total de %d \n", i, n);

}

printf("chau \n");


}

