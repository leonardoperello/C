#include <stdio.h>
void main(void){
int m[900][500];
int i, j;

for (i=0; i<300; i++)
for (j=0; j<500; j++)
m[i][j]=0;

for(i=300; i<699; i++)
for(j=0; j<500; j++)
m[i][j]=1;

for(i=600; i<900; i++)
for(j=0; j<500; j++)
m[i][j]=2;

for(i = 0; i < 900; i++) {
for(j = 0; j < 500; j++)
printf(" %d ", m[i][j]);
printf("\n");


}
}
