/*
 * main.cpp
 *
 *  Created on: 16 jun. 2022
 *      Author: gusty
 */

#include <iostream>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>																 //
#include <stdbool.h>
#include <vector>
#include "Controlador.h"

#define EVENT_MAX 100

string Acciones[] = {"Llenando",
 	 	 	 	     "Tapando",
 	 	 	 	     "Llenando y tapando",
 	 	 	 	     "Cinta en movimiento"};

string Eventos[] = {"Imposible",
				    "Relevante",
				    "No modifica"};

typedef struct{																	 //
	char opcion;																 //
	int n_eventos;																 //
}Datos_inicio;

Datos_inicio *Menu_inicio();

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::array;

int main(){
	int num_simulacion = 0;
	srand(time(NULL));
	Datos_inicio *datos_ingreso;

	cout<<"----------------------- Bienvenido!! -----------------------"<<endl;
	datos_ingreso = Menu_inicio();
	int cant_eventos = datos_ingreso->n_eventos;
	Controlador driver(cant_eventos);
//	for(i = 0; i < cant_eventos; i++){
//		cout<<"Valor de X:"<<driver.getLlena(i)<<" Valor de Y:"<<driver.getTapada(i)<<endl;
//	}
	driver.logica();
	driver.mostrar(num_simulacion);
//	for(i = 0;i<cant_eventos;i++){
//		cout<<"Evento : "<<i<<" "<<driver.getEstado()<<" "<<driver.getEvento()<<endl;
//	}

	return 0;
}

Datos_inicio* Menu_inicio(){
	Datos_inicio *datos_ingreso;
	datos_ingreso = new Datos_inicio;
	if(datos_ingreso == NULL){
		cout<<"Error!! No se pudo reservar memoria para la variable 'datos_ingreso'"<<endl;
		return NULL;
	}

	char opcion;
	datos_ingreso->n_eventos = 0;

	cout<<"Elige una de las siguientes opciones:"<<endl;
	cout<<"1 - Simular una nueva partida"<<endl;
	cout<<"2 - Salir del programa"<<endl;
	cout<<"Pulsa S para simular nuevamente o F para salir del programa."<<endl;
	cin>>opcion;

	while((opcion != 'S') && (opcion != 's') && (opcion != 'F') && (opcion != 'f')){
		cout<<"Debes ingresar el numero de alguna de las opciones del menu."<<endl;
		cin>>opcion;
	}

	datos_ingreso->opcion = opcion;
	cout<<"La opcion elegida es:"<<opcion<<endl;

	if((opcion == 'S') || (opcion == 's')){
		cout<<"Ingresa la cantidad de eventos que deseas generar: ";
		cin>>datos_ingreso->n_eventos;

		while((datos_ingreso->n_eventos <= 0) || (datos_ingreso->n_eventos > EVENT_MAX)){
			if(datos_ingreso->n_eventos <= 0){
				cout<<"Opcion invalida. La cantidad de eventos a simular debe ser un numero positivo."<<endl;
				cin>>datos_ingreso->n_eventos;
			}

			else{
				if(datos_ingreso->n_eventos > EVENT_MAX){
					cout<<"La cantidad de eventos ingresada es demasiado grande, por favor ingresa un valor menor a"<<EVENT_MAX<<endl;
					cin>>datos_ingreso->n_eventos;
				}
			}
		}
		cout<<"Cantidad de eventos de la simulacion: "<<datos_ingreso->n_eventos<<endl;
	}

	return datos_ingreso;
}