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
	bool *ENA1;
	bool *ENA2;
}entradas_salidas;

Datos* Menu_inicio();
bool bit_random(double p);
entradas_salidas *evento_random_entrada(entradas_salidas *E1, int cant_eventos);
//void Mostrar_salida();


int main(){
	Datos *datos_ingreso;
	int num_simulacion = 0,i;
	bool fin = true,reposo = false;
	entradas_salidas *E1 = (entradas_salidas*) malloc(sizeof(entradas_salidas));
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

		//Logica
//		for(i = 0;i<datos_ingreso->n_eventos;i++){
//
//			if(E1->reset[i]){
//				E1->ENA1[i] = false;
//				E1->ENA2[i] = false;
//			}
//			else{
//				if(!E1->boton[i] && !E1->ENA1[i-1] && !E1->ENA2[i-1]){
//						E1->ENA1[i] = true;
//						E1->ENA2[i] = false;
//				}
//				else{
//					if(!E1->boton[i] && E1->ENA1[i-1]){
//						E1->ENA2[i] = true;
//						E1->ENA1[i] = false;
//					}
//					else{
//						if(!E1->boton[i] && E1->ENA2[i-1]){
//							E1->ENA1[i] = true;
//							E1->ENA2[i] = false;
//						}
//						else{
//							E1->ENA1[i] = E1->ENA1[i-1];
//							E1->ENA2[i] = E1->ENA2[i-1];
//							fin = false;
//							reposo = false;
//						}
//					}
//				}
//			}
//		}
		int restart_required = 0;
		for(i = 0;i<datos_ingreso->n_eventos;i++){

			if(E1->reset[i] || E1->t_end[i] ){
				E1->ENA1[i] = false;
				E1->ENA2[i] = false;
				fin = true;
				if(E1->t_end[i]){
					restart_required = 1;
				}
				if(E1->reset[i]){
					restart_required = 0;
				}
			}
			else{
				if(!E1->boton[i] && !E1->ENA1[i-1] && !E1->ENA2[i-1] && restart_required == 0){
					E1->ENA1[i] = true;
					E1->ENA2[i] = false;
				}
				else{
					if(!E1->boton[i] && E1->ENA1[i-1] && restart_required == 0){
						E1->ENA2[i] = true;
						E1->ENA1[i] = false;
					}
					else{
						if(!E1->boton[i] && E1->ENA2[i-1]){
							E1->ENA1[i] = true;
							E1->ENA2[i] = false;
						}
						else{
							E1->ENA1[i] = E1->ENA1[i-1];
							E1->ENA2[i] = E1->ENA2[i-1];
							fin = false;
							reposo = false;
						}
					}
				}
			}
		}
		//
		printf("\n ///////////////////////////////////////////////////////////// \n");

		//Tendriamos que armar todo en una funcio Mostrar_salida();
		printf("Resultados de simulacion %d:\n",num_simulacion);
		printf("---------------------------------------\n");
		printf("RESET\t BOTON\ T_END \t ENA1\t ENA2\t Para el estado actual el evento es\t Accion\n");
		for(i = 0;i<datos_ingreso->n_eventos;i++){
			printf("%d\t",E1->reset[i]);
			printf("%d\t",E1->boton[i]);
			printf("%d\t",E1->t_end[i]);
			printf(" %d\t",E1->ENA1[i]);
			printf(" %d\t",E1->ENA2[i]);

			printf("\n");
		}

		datos_ingreso = Menu_inicio();
	}

	printf("Salio del programa.\n");


	return 0;
}

Datos* Menu_inicio(){
	Datos *datos_ingreso = (Datos*) malloc(sizeof(Datos));
	if(datos_ingreso == NULL){
		printf("Error!! No se pudo reservar memoria para la variable 'datos_ingreso'");
		return NULL;
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

bool bit_random (double p){
	int valor_random = rand() % MAX + MIN;
	bool bit;
	printf("Valor aleatorio: %d  ",valor_random);
	if(valor_random > 20/p){
		bit = true;
		printf("TRUE\n");
	}
	else{
		bit = false;
		printf("FALSE\n");
	}

	return bit;
}

entradas_salidas *evento_random_entrada(entradas_salidas *E1, int cant_eventos){
	// Generar un vector dinámico de valores booleanos
	// para cada una de las variables de entrada.
	E1->boton = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->reset = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->t_end = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->ENA1 = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->ENA2 = (bool*) calloc(cant_eventos,sizeof(bool*));

	for (int i = 0; i < cant_eventos; i++){
		E1->boton[i] = bit_random(0.9);
		E1->reset[i] = bit_random(0.5);
		E1->t_end[i] = bit_random(0.5);
	}
	return E1;
}
