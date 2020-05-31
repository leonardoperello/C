#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

#define N 10000000
int main(){
    // float ocupan 32 bits
    int i,  cantElem= 32/sizeof(float);
    float *vec, *res;
    float iteraciones,sumaTotal=0;
    __m256 reg1 , reg2;
 // usamos memoria
    if(posix_memalign((void**)&vec, 32, N*sizeof(float)) != 0)
      return 1;

    if(posix_memalign((void**)&res, 32, 8*sizeof(float)) != 0)//
      return 1;

  //inicio vector
  for (i = 0; i < N; i++) {
      vector[i] = i;

  	}
     // en un registro de 256 entran 8 floats
      iteraciones=N/cantElem;
       
      reg1 = _mm256_load_ps((float const*)vec); 
       //reg 1 = reg1 + reg2
      for(i=1;i<iteraciones;i++){
		reg2= _mm256_load_ps((float const*)vec+(i*cantElem));
		reg1= _mm256_add_ps(reg1,reg2);				
	}

    _mm256_store_ps ((float*)res, reg1);//guardamos en memoria lo del reg1 en res


 for (i = 0; i < cantElem; i++) {
      sumaTotal += res[i];
   	}

     printf("Suma total= %.2f\n",sumaTotal);
   	
	return 0;
}