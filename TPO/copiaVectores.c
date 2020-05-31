#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <string.h>

// true == 1
// false == 0


struct sensor {
	double* input;
	double* result;
	double min;
	double max;
	char* name;
	int size;
};

typedef struct sensor Sensor;


void operar(Sensor* sensor, int iteraciones, int doublePorReg);
void cargarElementos(Sensor* sensor);
void verificarValores(Sensor* sensor, int iteraciones, int doublePorReg);
void contarMediciones(Sensor* sensor);
void imprimirElementos(Sensor* sensor, bool isInput);
void contarMedicionesSensorSuelo(Sensor** sensores, int sizeSuelo);

void liberarSensor(Sensor* sensor);
void liberarSensores(Sensor** sensores, int size);
char* concat(const char* s1, const char* s2);


Sensor* newSensor(int size, char* name, double min, double max) {
	//min and max are both inclusive

	Sensor* sensor = malloc(sizeof *sensor);


	if (posix_memalign((void**)&sensor->input, 32, size * sizeof(double)) != 0)
		return (void*)NULL;

	if (posix_memalign((void**)&sensor->result, 32, size * sizeof(double)) != 0)
		return (void*)NULL;

	sensor->min = min;
	sensor->max = max;
	sensor->size = size;
	sensor->name= name;
	return sensor;
}

int main() {
	srand(1u);
	int doublePorReg = 16 / sizeof(double);
	double iteraciones = 86400;

	/*	- tamaño a alocar = mas grande de lo normal para evitar problemas de violación de acceso
		- la temperatura aceptada va a estar entre [rango minimo, rango maximo]
		si rango minmimo es -1 quiere decir que no existe, y se interpreta [rango maximo, infinito+)
    	 newSensor(tamaño a alocar, rango minimo, rango maximo)   -> pseudoconstructor
	*/

	Sensor* temperaturaAire = newSensor(86400,"Temperatura del aire", 20.0, 30.0);
	Sensor* humedadAire = newSensor(86400,"Humedad del aire", -1, 75);

	const int sizeHumedadSueloArray = 2000;
	Sensor** sensoresHumedadSuelo = malloc(sizeof(Sensor) * sizeHumedadSueloArray);

	operar(temperaturaAire, iteraciones, doublePorReg);
	operar(humedadAire, iteraciones, doublePorReg);

		int i;
		for (i = 0; i < sizeHumedadSueloArray; i++) {
			sensoresHumedadSuelo[i] = newSensor(86400,"Humedad del suelo", -1, 30);
		}

		for (i = 0; i < sizeHumedadSueloArray; i++) {
			char aux[4];
			sprintf(aux, "%d", i+1);

			char* name = concat("Humedad del suelo - sensor ", aux);
			//cambio de nombre para que aparezca con su numero
			sensoresHumedadSuelo[i]->name=name;

			operar(sensoresHumedadSuelo[i], iteraciones, doublePorReg);
			free(name);
		}
			contarMediciones(temperaturaAire);
       			contarMediciones(humedadAire);
			contarMedicionesSensorSuelo(sensoresHumedadSuelo, sizeHumedadSueloArray);
			
			liberarSensor(temperaturaAire);
			liberarSensor(humedadAire);
			liberarSensores(sensoresHumedadSuelo, sizeHumedadSueloArray);

return 0;
}

void operar(Sensor* sensor, int iteraciones, int doublePorReg) {
	cargarElementos(sensor);
	verificarValores(sensor, iteraciones, doublePorReg);
/*	imprimirElementos(sensor, true);
	imprimirElementos(sensor, false);*/
}


void cargarElementos(Sensor* sensor){
	float a;
	int i;
	
	if(sensor->name=="Temperatura del aire"){
   	a = 90.0;
//Numeros para sensor de temperatura del aire [-40 ... 50]
   	for (i = 0; i < sensor->size; i++)
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

void verificarValores(Sensor* sensor, int iteraciones, int doublePorReg) {
	__m128d mascaraRangoMaximo, mascaraUnos, mascaraRangoMinimo, reg_actual, aux;
	__m128d max= _mm_set1_pd(sensor->max);
	__m128d uno = _mm_set1_pd(1.0);
	int i;
	for (i = 0; i < iteraciones/doublePorReg; i++) {
		reg_actual = _mm_load_pd((double*)sensor->input + (i * doublePorReg));	 /* Carga desde memoria */

		if (sensor->min == -1) {
			mascaraRangoMaximo = _mm_cmpgt_pd(reg_actual, max); //Mayores a max

			reg_actual = _mm_and_pd(uno, mascaraRangoMaximo);

		} else {
			__m128d min = _mm_set1_pd(sensor->min);
			mascaraRangoMinimo = _mm_cmpgt_pd(reg_actual, min);
			mascaraRangoMaximo = _mm_cmplt_pd(reg_actual, max);
			aux = _mm_and_pd(mascaraRangoMinimo, mascaraRangoMaximo);
			reg_actual = _mm_and_pd(uno, aux);
		}

		_mm_store_pd((double*)(sensor->result + (i * doublePorReg)), reg_actual); /* Guarda los resultados en memoria */
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


void imprimirElementos(Sensor* sensor, bool isInput) {
	printf(sensor->name);
	printf(":  [");
	int i;
	for (i = 0; i < sensor->size; i++) {
		if (i == sensor->size - 1) {
			if (isInput) {
				printf("%.2f]   ENTRADA\n", sensor->input[i]);
			}
			else {
				printf("%.2f]   RESULTADO\n\n", sensor->result[i]);
				continue;
		}
		}
		else {
			if (isInput) {
				printf("%.2f, ", sensor->input[i]);
			}
			else {
				printf(" %.2f, ", sensor->result[i]);
			}
		}
	}
}

void liberarSensor(Sensor* sensor) {
	/*WINDOWS SE USA aligned_free*/

	/*_aligned_free(sensor->input);
	_aligned_free(sensor->result);*/

	/* LINUX SE USA free*/

	free(sensor->input);
	free(sensor->result);
	free(sensor);
}

void liberarSensores(Sensor** sensores, int size) {
	int h;
	for (h = 0; h < size; h++) {
		liberarSensor(sensores[h]);
	}
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
