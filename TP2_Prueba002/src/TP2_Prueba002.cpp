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
#include <array>
#include "Botella.h"

#define EVENT_MAX 100
#define MAX 50																	 //
#define MIN 1

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

typedef struct{
	bool X_llenado;
	bool Y_tapado;
	bool cinta;
}Proceso;

Datos_inicio *Menu_inicio();
void logica(Botella b);
bool bit_random(double p);

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::array;

int main(){
	//int num_simulacion = 0;
	srand(time(NULL));
	Datos_inicio *datos_ingreso;
	int i;

	cout<<"----------------------- Bienvenido!! -----------------------"<<endl;
	datos_ingreso = Menu_inicio();
	int cant_eventos = datos_ingreso->n_eventos;
	Botella botellas[cant_eventos];
	for(i = 0; i < cant_eventos; i++){
		botellas[i].setLlena(bit_random(0.55));
		botellas[i].setTapada(bit_random(0.55));
		cout<<"Valor de X:"<<botellas[i].getLlena()<<" Valor de Y:"<<botellas[i].getTapada()<<endl;
	}

	for(i = 0;i<cant_eventos;i++){
		logica(botellas[i]);
		cout<<"Evento : "<<i<<" "<<botellas[i].getEstado()<<" "<<botellas[i].getEvento()<<endl;
	}


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

bool bit_random (double p){
	int valor_random = rand() % MAX + MIN;
	bool bit;

	if(valor_random > 20/p) bit = true;
	else bit = false;

	return bit;
}

void logica(Botella b){
	bool control = false;

	if(b.getLlena() && b.getTapada() && !control){
		b.setEstado(Acciones[2]);
		b.setEvento(Eventos[1]);
		control = true;
	}
	else{
		if(b.getLlena() && !b.getTapada() && !control){
			b.setEstado(Acciones[0]);
			b.setEvento(Eventos[1]);
		}
		else{
			if(!b.getLlena() && !b.getTapada()){
				b.setEstado(Acciones[3]);
				b.setEvento(Eventos[1]);
				control = false;
			}
		}
	}
}
