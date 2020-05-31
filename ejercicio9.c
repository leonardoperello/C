#include <stdio.h>

int main(){
int N=100;
float arreglo[N];
float suma=0;
int cantElemReg = 16/sizeof(float);
for (int i = 0; i<N; i++){
arreglo[i] = i*2.125;
}

for(int i=0; i<N; i++){
suma=suma+arreglo[i];
}
printf("cantElemReg: %d \n", cantElemReg);
printf(" resultado: %f \n", suma);
return 0;
}
