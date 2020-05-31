#include <omp.h>
#include <stdio.h>
int main() {

int i, max = 0;
int v[10000];

for (i = 0; i < 10000; i++)
 v[i] = i;

#pragma omp parallel num_threads(5)
{
#pragma omp critical
        for (i = 0; i < 10000; i++){ 
        if(v[i] > v[i+1])
	max = v[i];
	}
}
        printf("Resultado: %d \n", max);
}

