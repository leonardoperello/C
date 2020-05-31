#include <omp.h>
#include <stdio.h>
int main() {

int i, max = 0;
int v[10000];

for (i = 0; i < 10000; i++)
 v[i] = i;

#pragma omp parallel for reduction (max : max)

	for (i = 0; i < 10000; i++)
 	max = v[i];
	printf("Resultado: %d \n", max);

}
