#include <stdlib.h>
#include <stdio.h>
int main(){

int * array = malloc(10 * sizeof(int));

if(NULL==array){
printf("error");
}

array[0]= 123123;
printf("valor 0 de array %d \n",array[0]);
printf("se cargo el arreglo dinamicamente y ahora lo liberamos \n");

free(array);

array=NULL;

return 0;
}
