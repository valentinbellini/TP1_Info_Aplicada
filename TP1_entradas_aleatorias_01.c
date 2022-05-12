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


typedef struct po {
	bool *boton;
	bool *reset;
	bool *t_end;
}entradas;

bool bit_random (){
	int valor_random = rand() %50;
	bool bit;
	(valor_random > 25) ? (bit = true) : (bit = false);
	return bit;
}

void evento_random_entrada(entradas *E1, int cant_eventos){
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
}

int main(void) {
	srand(time(NULL));
	int cant_eventos = 5;
	entradas *E1 = (entradas*) malloc(sizeof(entradas));
	evento_random_entrada(E1,cant_eventos);



	return EXIT_SUCCESS;
}
