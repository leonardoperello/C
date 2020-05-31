#include <stdio.h>
#include <immintrin.h>
#include <stdlib.h>

#define N 10000000
int main(){
//double ocupan 64 bits

int i, cantElem = 64/sizeof(double);
double *vector, *resultado;
double iteraciones, sumaTotal=0;

__m512 registro1, registro2;

//

if(posix_memalign((void**)&vector, 64, N*sizeof(double)) != 0)
      return 1;

    if(posix_memalign((void**)&resultado, 64, 8*sizeof(double)) != 0)//
      return 1;

//inicializacion

for(i=0; i<N; i++){
vector[i];
}

// en un registro de 512 entran 8 doubles (son de 64)
iteraciones = N/cantElem;

registro1= _mm512_load_ps((double const*)vector+(i*cantElem));

for(i=1; i<iteraciones; i++){
registro2= _mm512_load_ps((double const*)vector+(i*cantElem));
registro1= _mm512_add_epi32(registro1, registro2);
}

_mm512_store_ps((double*)resultado, registro1); 

for(i=0; i<cantElem; i++){
sumaTotal+=resultado[i];
}

printf("suma total = %lf \n", sumaTotal);

return 0;
}
