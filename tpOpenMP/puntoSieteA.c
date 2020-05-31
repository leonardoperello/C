#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

void main()
{
int i, j;

double t;
t = sampleTime();

#pragma omp parallel for schedule(static) private(j)
for (i = 0; i < 100000000; i++)
for(j = 0; j < 100; j++);

t = sampleTime() - t;
printf("tiempo transcurrido: %f segundos\n", t);

}
