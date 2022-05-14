// 11/05/22 23:47 - 0 errores 0 warnings

// Tengo que chequearlo bien pero en principio la idea es:
// entradas: estructura con 3 punteros a booleano
// bit_random: genera un booleano random a partir de rand(), valor_random se
//				encuentra entre 1 y 50, por lo tanto el bit es equiprobable
// En void se almacena espacion con malloc para una variable de tipo estructura
// La cantidad de eventos (cant_eventos) lo puse en main pero eso lo ingresaria el user
// evento_random_entrada: Cada campo de la estrcutura "entradas" seria un vector de bool
//  						En esta funcion se reserva el espacio en memoria para ellos
//							y se llama a la funcion bit_random() para generar entradas aleatorias


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


typedef struct entradas_t {
	bool *boton;
	bool *reset;
	bool *t_end;
}entradas;

typedef struct salidas_t {
	unsigned int ENA1 : 1;
	unsigned int ENA2 : 1;
	unsigned int fin : 1;
}salidas;

bool bit_random (double p){
	int valor_random = rand() %50;
	bool bit;
	(valor_random > 20/p) ? (bit = true) : (bit = false);
	return bit;
}

void delay(int s){
	double timeDelay = (double) s + clock()/CLOCKS_PER_SEC;
	while(timeDelay > clock()/CLOCKS_PER_SEC){}
}

void evento_random_entrada(entradas *E1, int cant_eventos){
	// Generar un vector dinámico de valores booleanos
	// para cada una de las variables de entrada.
	E1->boton = (bool*) malloc(cant_eventos*sizeof(bool*));
	E1->reset = (bool*) malloc(cant_eventos*sizeof(bool*));
	E1->t_end = (bool*) malloc(cant_eventos*sizeof(bool*));
	if(E1->boton == NULL || E1->reset == NULL || E1->t_end == NULL){
		printf("No se ha podido reservar memoria para alguna de las entradas\n");
	}
	for (int i = 0; i < cant_eventos; i++){
		E1->boton[i] = bit_random(1);
		E1->reset[i] = bit_random(0.7);
		E1->t_end[i] = bit_random(0.5);
	}
}

void imprimir_entradas_aleatorias (entradas *E1,int cant_eventos){
	printf("Boton = [ ");
		for(int i = 0; i < cant_eventos; i++){
			printf("%d ",E1->boton[i]);
		}
		printf("]\n");

		printf("Reset = [ ");
		for(int i = 0; i < cant_eventos; i++){
			printf("%d ",E1->reset[i]);
		}
		printf("]\n");

		printf("t_end = [ ");
		for(int i = 0; i < cant_eventos; i++){
			printf("%d ",E1->t_end[i]);
		}
		printf("]\n");
}

void liberar_memoria_entradas(entradas *E1, int cant_eventos){
	free(E1->boton);
	free(E1->reset);
	free(E1->t_end);
	free(E1);
}


int main(void) {
	srand(time(NULL));
	int cant_eventos = 0;
	printf("Ingrese cantidad de eventos a generar: ");
	scanf("%d",&cant_eventos);
	entradas *E1 = (entradas*) malloc(sizeof(entradas));
	evento_random_entrada(E1,cant_eventos);
	imprimir_entradas_aleatorias(E1,cant_eventos);
	liberar_memoria_entradas(E1,cant_eventos);

	return EXIT_SUCCESS;
}
