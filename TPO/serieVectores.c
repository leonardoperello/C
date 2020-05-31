#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sensor {
	double* input;
	double* result;
	double min;
	double max;
	char* name;
	int size;
};

typedef struct sensor Sensor;


void operar(Sensor* sensor);
void cargarElementos(Sensor* sensor);
void verificarValores(Sensor* sensor);
void contarMediciones(Sensor* sensor);

void contarMedicionesSensorSuelo(Sensor** sensores, int sizeSuelo);

void liberarSensor(Sensor* sensor);
void liberarSensores(Sensor** sensores, int size);
char* concat(const char* s1, const char* s2);

Sensor* newSensor(int size, char* name, double min, double max) {

	Sensor* sensor = malloc(sizeof *sensor);

	sensor->input=malloc(size*sizeof(double));
	sensor->result=malloc(size*sizeof(double));

	sensor->min = min;
	sensor->max = max;
	sensor->size = size;
	sensor->name= name;
	return sensor;
}


int main(){
	srand(1u);
	Sensor* temperaturaAire = newSensor(86400,"Temperatura del aire", 20.0, 30.0);
	Sensor* humedadAire = newSensor(86400,"Humedad del aire", -1, 75);

	const int sizeHumedadSueloArray = 2000;
	Sensor** sensoresHumedadSuelo = malloc(sizeof(Sensor) * sizeHumedadSueloArray);

	operar(temperaturaAire);
	operar(humedadAire);

		int i;
		for (i = 0; i < sizeHumedadSueloArray; i++) {
			sensoresHumedadSuelo[i] = newSensor(86400, "Humedad del suelo", -1, 30);
		}

		for (i = 0; i <  sizeHumedadSueloArray; i++) {
			char aux[4];
			sprintf(aux, "%d",  i+1);

			char* name = concat("Humedad del suelo - sensor", aux);
			//cambio de nombre para que aparezca con su numero
			sensoresHumedadSuelo[i]->name=name;

			operar(sensoresHumedadSuelo[i]);
		}
			contarMediciones(temperaturaAire);
       			contarMediciones(humedadAire);
			contarMedicionesSensorSuelo(sensoresHumedadSuelo, sizeHumedadSueloArray);


return 0;
}

void operar(Sensor* sensor) {
	cargarElementos(sensor);
	verificarValores(sensor);
}


void verificarValores(Sensor* sensor) {

	int i;
	for (i = 0; i < sensor->size; i++) {

		if (sensor->min == -1) {
			if(sensor->input[i] > sensor->max){
			sensor->result[i]=1.0;

		}else{
			sensor->result[i]=0.0;
		}

		} else {

                  if(sensor->input[i] > sensor->min && sensor->input[i] < sensor->max){
			sensor->result[i]= 1.0;
		}else{
		sensor->result[i]=0.0;
		}
		}

	}
}


void cargarElementos(Sensor* sensor){
	float a;
	int i;

	if(sensor->name=="Temperatura del aire"){
   	a = 90.0;
//Numeros para sensor de temperatura del aire [-40 ... 50]
   	for (i = 0; i < sensor->size ; i++)
      	sensor->input[i] = ((double)rand()/(double)(RAND_MAX)) * a - 40;

	}else{

	if(sensor->name=="Humedad del aire"){
//Numeros para sensor de humedad del aire [0 ... 100]
   	a = 100.0;
   	for (i = 0; i < sensor->size ; i++)
      	sensor->input[i] = ((double)rand()/(double)(RAND_MAX)) * a;

	}else{

//Numeros para sensor de humedad del suelo [0 ... 100]
   	a = 100.0;
      	for (i = 0; i < sensor->size; i++)
      	sensor->input[i] = ((double)rand()/(double)(RAND_MAX)) * a;

	}
	}

}


void contarMediciones(Sensor* sensor){
	int correctas=0, incorrectas=0, i;
	
	for(i=0; i < sensor->size; i++){
	if(sensor->result[i]==1){
		correctas++;
	}else{
	incorrectas++;
	}
	}
	printf("sensor %s:  %d correctas - %d incorrectas \n", sensor->name, correctas, incorrectas);
	printf("\n");
}
	
void contarMedicionesSensorSuelo(Sensor** sensores, int sizeSuelo){
	int i, j, correctas=0, incorrectas=0;
	Sensor* sensor;

	for(i=0; i< sizeSuelo; i++){
	sensor= sensores[i];
	
	for(j=0; j< sensor->size; j++){
	
	if(sensor->result[j] == 1){
	correctas++;
	}else{
	incorrectas++;
	}
}
}
	printf("Sensores de humedad del suelo: correctas: %d - incorretas: %d \n", correctas, incorrectas);
}


char* concat(const char* s1, const char* s2)
{
	const size_t len1 = strlen(s1);
	const size_t len2 = strlen(s2);
	char* result = malloc(len1 + len2 + 1); // +1 for the null-terminator

	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
	return result;
}

