#include <omp.h>
#include <stdio.h>
int main(){
#pragma omp parallel num_threads (5)
{
	printf("hola \n");
	printf("chau \n");
}
printf("fin \n");
return 0;
}
