#include <omp.h>
#include <stdio.h>
#include <unistd.h>
int main(){
int x = 1;

#pragma omp parallel shared(x) num_threads(2)
{
	if(omp_get_thread_num() == 5)
		x = 2;
	sleep(1);
	printf("%d \n", x);
}

printf("%d \n", x);

return 0;
}
