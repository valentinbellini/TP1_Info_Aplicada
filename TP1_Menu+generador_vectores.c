/*
 * TP1.c
 *
 *  Created on: 12 may. 2022
 *      Author: gusty
 */
/*
 *AVANCES: Integre lo que estuvo haciendo Vale y ya podemos generar los vectores aleatorios sin dramas
 *segun la cantidad que diga el usuario. Lo que tendriamos que hacer ahora es empezar a armar el arbol de if
 *para que decida que hacer en cada caso según las entradas que se generaron. Tambien fui armando como quedaría
 *la salida una vez que se procesan los datos.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define EVENT_MAX 100
#define MAX 50
#define MIN 1

typedef struct{
	char opcion;
	int n_eventos;
}Datos;

typedef struct po {
	bool *boton;
	bool *reset;
	bool *t_end;
}entradas;

Datos* Menu_inicio();
bool bit_random();
entradas *evento_random_entrada(entradas *E1, int cant_eventos);
//void Mostrar_salida();


int main(){
	Datos *datos_ingreso;
	int num_simulacion = 0;
	entradas *E1 = (entradas*) malloc(sizeof(entradas));
	if(E1 == NULL){
		printf("Error!! No se pudo reservar memoria para la variable 'E1'");
		return -1;
	}

	srand(time(NULL));
	printf("----------------------- Bienvenido!! -----------------------\n");
	datos_ingreso = Menu_inicio();
//	Prueba de valores
//	printf("La opcion elegida es: %s\n",datos_ingreso->opcion);
//	printf("Cantidad de eventos de la simulacion: %d\n",datos_ingreso->n_eventos);
	while(datos_ingreso->opcion == 'S' || datos_ingreso->opcion == 's'){
		printf("\n ///////////////////////////////////////////////////////////// \n");
		printf("Se realiza una nueva simulacion.\n");
		E1 = evento_random_entrada(E1,datos_ingreso->n_eventos);
		num_simulacion++;
		printf("\n ///////////////////////////////////////////////////////////// \n");

		//Tendriamos que armar todo en una funcio Mostrar_salida();
		printf("Resultados de simulacion de partida %d:\n",num_simulacion);
		printf("---------------------------------------\n");
		printf("Estado RESET\t Estado Boton\t Estado Salida ENA1\t Estado Salida ENA2\t Para el estado actual el evento es\n");
		for(int i = 0;i<datos_ingreso->n_eventos;i++){
			//printf("%06d\t %06d\t 0\t\n",E1->reset,E1->boton);
			if(E1->reset[i])
				printf("\t1\t");
			else
				printf("\t0\t");

			if(E1->boton[i])
				printf("\t1\t");
			else
				printf("\t0\t");
			printf("\n");
		}

		datos_ingreso = Menu_inicio();
	}

	printf("Salio del programa.\n");

	getch();
	return 0;
}

Datos* Menu_inicio(){
	Datos *datos_ingreso = (Datos*) malloc(sizeof(Datos));
	if(datos_ingreso == NULL){
		printf("Error!! No se pudo reservar memoria para la variable 'datos_ingreso'");
		return -1;
	}
	char opcion;
	datos_ingreso->n_eventos = 0;

	printf("Elige una de las siguientes opciones:\n");
	printf("1 - Simular una nueva partida\n");
	printf("2 - Salir del programa\n");
	printf("Pulsa S para simular nuevamente o F para salir del programa.\n");
	scanf("%s",&opcion);

	while((opcion != 'S') && (opcion != 's') && (opcion != 'F') && (opcion != 'f')){
		printf("Debes ingresar el numero de alguna de las opciones del menu.\n");
		scanf("%s",&opcion);
	}

	datos_ingreso->opcion = opcion;
	printf("La opcion elegida es: %c\n",opcion);

	if((opcion == 'S') || (opcion == 's')){
		printf("Ingresa la cantidad de eventos que deseas generar: ");
		scanf("%d",&datos_ingreso->n_eventos);

		while((datos_ingreso->n_eventos <= 0) || (datos_ingreso->n_eventos > EVENT_MAX)){
			if(datos_ingreso->n_eventos <= 0){
				printf("Opcion invalida. La cantidad de eventos a simular debe ser un numero positivo.\n");
				scanf("%d",&datos_ingreso->n_eventos);
			}

			else{
				if(datos_ingreso->n_eventos > EVENT_MAX){
					printf("La cantidad de eventos ingresada es demasiado grande, por favot ingresa un valor menor a %d.\n", EVENT_MAX);
					scanf("%d",&datos_ingreso->n_eventos);
				}
			}
		}
		printf("Cantidad de eventos de la simulacion: %d\n",datos_ingreso->n_eventos);
	}

	return datos_ingreso;
}

//void Mostrar_salida(){}

bool bit_random (){
	int valor_random = rand() % MAX + MIN;
	bool bit;
	printf("Valor aleatorio: %d  ",valor_random);
	if(valor_random > 25){
		bit = true;
		printf("TRUE\n");
	}
	else{
		bit = false;
		printf("FALSE\n");
	}
	return bit;
}

entradas *evento_random_entrada(entradas *E1, int cant_eventos){
	// Generar un vector dinámico de valores booleanos
	// para cada una de las variables de entrada.
	E1->boton = (bool*) malloc(cant_eventos*sizeof(bool*));
	E1->reset = (bool*) malloc(cant_eventos*sizeof(bool*));
	E1->t_end = (bool*) malloc(cant_eventos*sizeof(bool*));
	for (int i = 0; i < cant_eventos; i++){
		E1->boton[i] = bit_random();
		E1->reset[i] = bit_random();
		E1->t_end[i] = bit_random();
	}
	return E1;
}
