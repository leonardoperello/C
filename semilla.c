#include <stdlib.h>
#include <stdio.h>
int main() {
   int i;
   srand(1u);
   for (i=0;i<100;i++)
      printf("%d ", rand()%10);
   printf("\n");
}
