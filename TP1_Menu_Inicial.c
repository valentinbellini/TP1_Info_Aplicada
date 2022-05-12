/*
 * TP1.c
 *
 *  Created on: 12 may. 2022
 *      Author: gusty
 */


/*
 *Aca arme el menu que mostaria con las validaciones de datos y los bucles que pide para repetir.
 *Agregue una parte que seria como mostraria la tabla de los resultados pero para probarla necesitamos
 *el generador aleatorio. Despues lo integramos todo.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define EVENT_MAX 100

typedef struct{
	char opcion;
	int n_eventos;
}Datos;

Datos* Menu_inicio();
//void Mostrar_salida();


int main(){
	Datos *datos_ingreso;
	int num_simulacion = 0;

	printf("----------------------- Bienvenido!! -----------------------\n");
	datos_ingreso = Menu_inicio();
//	Prueba de valores
//	printf("La opcion elegida es: %s\n",datos_ingreso->opcion);
//	printf("Cantidad de eventos de la simulacion: %d\n",datos_ingreso->n_eventos);
	while(datos_ingreso->opcion == 'S' || datos_ingreso->opcion == 's'){
		printf("\n ///////////////////////////////////////////////////////////// \n");
		printf("Se realiza una nueva simulacion.\n");
		num_simulacion++;
		printf("\n ///////////////////////////////////////////////////////////// \n");

		//Tendriamos que armar todo en una funcio Mostrar_salida();
		printf("Resultados de simulacion de partida %d:\n",num_simulacion+1);
		printf("---------------------------------------\n");
		printf("Estado RESET\t Estado Boton\t Estado Salida ENA1\t Estado Salida ENA2\t Para el estado actual el evento es\n");


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
