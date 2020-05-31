#include <stdio.h>
#include <time.h>

int main(){

clock_t tiempo_inicio = clock();
clock_t tiempo_final;

double segundos;

segundos = (double)(tiempo_inicio - tiempo_final) / CLOCKS_PER_SEC;

printf("%f \n",segundos);


return 0;
}
