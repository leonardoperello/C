#include <omp.h>
#include <stdio.h>

int main(){
int x = 1;
#pragma omp parallel num_threads(5)
{
	x = x + 1;
	x = x*2;
	printf("%d \n", x);
}
printf("%d \n", x);

return 0;
}
