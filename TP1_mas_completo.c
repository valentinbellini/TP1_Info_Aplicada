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
#define ANCHO_TEXTO -10
#define LONG_MAX 15

#define PULSADOR(a) ((a > 0)?"PULSADO":"NO PULSADO")
#define TIEMPO(b) ((b > 0)?"SI":"NO")

typedef struct{
	char opcion;
	int n_eventos;
}Datos;

typedef struct{
	bool *boton;
	bool *reset;
	bool *t_end;
	bool *ENA1;
	bool *ENA2;
}entradas_salidas;

typedef struct{
	unsigned char reposo:1;
	unsigned char fin:1;
}control;

typedef struct{
	char *evento;
	char *accion;
}datos;

char* Acciones[] = {"Reset",
 	 	 	 	    "Turno jugador 1",
 	 	 	 	    "Turno jugador 2",
 	 	 	 	    "Tiempo agotado",
 	 	 	 	    "--------------"};

char* Eventos[] = {"Imposible",
				   "Relevante",
				   "No modifica"};

Datos *Menu_inicio();
bool bit_random(double p);
entradas_salidas *evento_random_entrada(entradas_salidas *E1, int cant_eventos);
//char *def_evento(entradas_salidas *E_datos,int cant_eventos);

int main(){
	Datos *datos_ingreso;
	int num_simulacion = 0,i;
	control var_control;
	var_control.fin = 1;
	var_control.reposo = 0;
	//entradas_salidas E1;
	entradas_salidas datos_E1;
//	entradas_salidas *E1 = (entradas_salidas*) malloc(sizeof(entradas_salidas));
//	if(E1 == NULL){
//		printf("Error!! No se pudo reservar memoria para la variable 'E1'");
//		return -1;
//	}
	//p_E1 = &E1;

	srand(time(NULL));
	printf("----------------------- Bienvenido!! -----------------------\n");
	datos_ingreso = Menu_inicio();

	while(datos_ingreso->opcion == 'S' || datos_ingreso->opcion == 's'){
		datos Nombres[datos_ingreso->n_eventos];
		entradas_salidas *E1 = (entradas_salidas*) malloc(sizeof(entradas_salidas));
		if(E1 == NULL){
			printf("Error!! No se pudo reservar memoria para la variable 'E1'");
			return -1;
		}
		printf("Se realiza una nueva simulacion.\n");
		E1 = evento_random_entrada(&datos_E1,datos_ingreso->n_eventos);
		num_simulacion++;

		//Logica
		for(i = 0;i<datos_ingreso->n_eventos;i++){
			if(E1->reset[i] && !E1->t_end[i]){
				var_control.fin = 0;
				E1->boton[i] = true;
				E1->ENA1[i] = false;
				E1->ENA2[i] = false;
				var_control.reposo = 1;
				Nombres[i].evento = Eventos[1];
				Nombres[i].accion = Acciones[0];
			}

			else{
				if(E1->t_end[i]){//Estado de reposo hasta que se pareta Boton
					var_control.fin = 1;
					E1->ENA1[i] = false;
					E1->ENA2[i] = false;
					var_control.reposo = 0;
					Nombres[i].accion = Acciones[3];
					Nombres[i].evento = Eventos[1];
					if(i == 0){
						Nombres[i].evento = Eventos[0];
						Nombres[i].accion = Acciones[4];
					}
				}

				else{
					if(i && var_control.reposo){
						if(!E1->boton[i] && !E1->ENA1[i-1] && !E1->ENA2[i-1] && !var_control.fin){
							E1->ENA1[i] = true;
							E1->ENA2[i] = false;
							var_control.fin = 0;
							Nombres[i].accion = Acciones[1];
							Nombres[i].evento = Eventos[1];
						}
						else{
							if(!E1->boton[i] && E1->ENA1[i-1]){
								E1->ENA2[i] = true;
								E1->ENA1[i] = false;
								Nombres[i].accion = Acciones[2];
								Nombres[i].evento = Eventos[1];
							}
							else{
								if(!E1->boton[i] && E1->ENA2[i-1]){
									E1->ENA1[i] = true;
									E1->ENA2[i] = false;
									Nombres[i].accion = Acciones[1];
									Nombres[i].evento = Eventos[1];
								}

								else{
									E1->ENA1[i] = E1->ENA1[i-1];
									E1->ENA2[i] = E1->ENA2[i-1];
									Nombres[i].accion = Acciones[4];
									Nombres[i].evento = Eventos[2];
								}
							}
						}
					}

					else{
						if(!E1->boton[i] && (i == 0)){
							E1->ENA1[i] = true;
							E1->ENA2[i] = false;
							Nombres[i].accion = Acciones[1];
							Nombres[i].evento = Eventos[1];
						}
						else{
							E1->ENA1[i] = false;
							E1->ENA2[i] = false;
							Nombres[i].accion = Acciones[4];
							Nombres[i].evento = Eventos[2];
						}
					}
				}
			}
		}

		printf("\n////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		printf("Resultados de simulacion %d:\n",num_simulacion);
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		printf("   RESET\t    BOTON\t Se termino el tiempo?\t ENA1\tENA2\t Para el estado actual el evento \t Accion\n");
		printf("-------------------------------------------------------------------------------------------------------------------------\n");
		for(i = 0;i<datos_ingreso->n_eventos;i++){
			printf("%*s    |\t",ANCHO_TEXTO,PULSADOR(E1->reset[i]));
			printf("%*s    |\t",ANCHO_TEXTO,PULSADOR(!E1->boton[i]));
			printf("%*s\t\t|",-ANCHO_TEXTO+2,TIEMPO(E1->t_end[i]));
			printf("%*d  |",3,E1->ENA1[i]);
			printf("%*d  |",3,E1->ENA2[i]);
			printf("\t%*s \t\t|",-ANCHO_TEXTO*2,Nombres[i].evento);
			printf("\t%*s \t\t",ANCHO_TEXTO*2,Nombres[i].accion);

			printf("\n");
		}
		printf("--------------------------------------------------------------------------------------------------------------------------\n");

		datos_ingreso = Menu_inicio();
		//		free(datos_ingreso->n_eventos);
		//		free(datos_ingreso->opcion);
		//		free(datos_ingreso);
		free(E1->ENA1);
		free(E1->ENA2);
		free(E1->boton);
		free(E1->reset);
		free(E1->t_end);
		free(E1);
		free(Nombres->accion);
		free(Nombres->evento);
		free(Nombres);
	}

	printf("Salio del programa.\n");

	getch();
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

bool bit_random (double p){
	int valor_random = rand() % MAX + MIN;
	bool bit;
	if(valor_random > 20/p)
		bit = true;
	else
		bit = false;

	return bit;
}

entradas_salidas *evento_random_entrada(entradas_salidas *E1, int cant_eventos){
	E1->boton = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->reset = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->t_end = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->ENA1 = (bool*) calloc(cant_eventos,sizeof(bool*));
	E1->ENA2 = (bool*) calloc(cant_eventos,sizeof(bool*));

	for (int i = 0; i < cant_eventos; i++){
		E1->boton[i] = bit_random(1);
		E1->reset[i] = bit_random(0.5);
		E1->t_end[i] = bit_random(0.5);
	}
	return E1;
}
