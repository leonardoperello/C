#include<stdio.h>
void main(void)
{
int m[900][500];
int i, j;
for(i = 0; i < 900; i++)
for(j = 0; j < 500; j++)
switch (i) {
case 0 ... 299: m[i][j]=0; break;
case 300 ... 599: m[i][j]=1; break;
default: m[i][j]=2; break;
}
for(i = 0; i < 900; i++) {
for(j = 0; j < 500; j++)
printf(" %d ", m[i][j]);
printf("\n");
}
}
