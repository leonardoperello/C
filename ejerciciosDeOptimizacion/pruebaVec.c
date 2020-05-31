#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

int main(){

int i;
char *a, *b, *c;
__m128i reg_a, reg_b;

/*con esto le asigno memoria a los char*/
        if(posix_memalign((void**)&a, 16, 16) != 0)
      return 1;

        if(posix_memalign((void**)&b, 16, 16) != 0)
      return 1;

	if(posix_memalign((void**)&c, 16, 16) != 0)
      return 1;
for(i = 0; i<16; i++){
a[i]=i*12;
b[i]=i*3;
}

reg_a = _mm_load_si128((__m128i*)a);
reg_b = _mm_load_si128((__m128i*)b);

reg_a = _mm_adds_epi8(reg_a, reg_b);
_mm_store_si128((__m128i*)c, reg_a);

for(int j=0; j<16; j++){
printf("%d \n", c[j]);
}


return 0;
}
