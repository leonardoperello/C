#include <omp.h>
#include <stdio.h>

void main(){

int x, y;
x = 1;
y = 1;
#pragma omp parallel private (y)
{
	x = 2;
	y = 2;
  #pragma omp parallel private (x)
	{
		int z = 1;
		x = 3;
		y = 3;
        }
	//aca deberia imprimir x = 2 y = 3
   printf("x = %d y = %d \n", x, y);
}

//aca deberia imprimir x = 2 y=1
printf("x = %d y = %d \n", x, y);

}
