#include <stdio.h>
#include <stdlib.h>

struct sensor {
        double* input;
        double* result;
        double min;
        double max;
        char* name;
        int size;
};

typedef struct sensor Sensor;

Sensor* newSensor(int size, char* name, double min, double max) {
        //min and max are both inclusive

        Sensor* sensor = malloc(sizeof *sensor);
        if (posix_memalign((void**)&sensor->input, 16, 20 * sizeof(double)) != 0)
                return 1;

        if (posix_memalign((void**)&sensor->result, 16, 20 * sizeof(double)) != 0)
                return 1;

        sensor->min = min;
        sensor->max = max;
        sensor->size = size;
        sensor->name= name;
        return sensor;
}

int main(){

	Sensor* temperaturaAire = newSensor(5,"Temperatura del aire", 20.0, 30.0);
        Sensor* humedadAire = newSensor(5,"Humedad del aire", -1, 75);
	operar(temperaturaAire);
	operar(humedadAire);
return 0;
}

void operar(Sensor* sensor) {
   double a;
   srand(1u);

   /* Se debe respetar el orden siguiente de inicializacion:
   (1) sensor de temperatura aire, (2) sensor de humedad aire, (3) sensores de humedad suelo. */

   //Numeros para sensor de temperatura del aire [-40 ... 50]
   a = 90.0;
	if(sensor->name == "Temperatura del aire"){
	printf("estoy en sensor del aire"); 
  	for (int i=0;i<25;i++)
        printf("% f ", ((double)rand()/(double)(RAND_MAX)) * a - 40);
        printf("\n\n");
}
   //Numeros para sensor de humedad del aire [0 ... 100]
  /* a = 100.0;
   for (int i=0;i<20;i++)
      printf("% f ", ((double)rand()/(double)(RAND_MAX)) * a);
   printf("\n\n");

   //Numeros para sensor de humedad del suelo [0 ... 100]
   a = 100.0;
   for (int i=0;i<20;i++)
      printf("% f ", ((double)rand()/(double)(RAND_MAX)) * a);
   printf("\n\n");
*/
   }
