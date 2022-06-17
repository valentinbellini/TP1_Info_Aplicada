/*
 * Controlador.cpp
 *
 *  Created on: 17 jun. 2022
 *      Author: gusty
 */

#include "Controlador.h"

Controlador::Controlador(int cant_simulaciones){
	int i;
	X_llenado = new bool[cant_simulaciones];
	Y_tapado = new bool[cant_simulaciones];
	SAL_A = new bool[cant_simulaciones];
	SAL_B = new bool[cant_simulaciones];
	SAL_C = new bool[cant_simulaciones];

	for(i = 0;i<cant_simulaciones;i++){
		int valor_random_1 = rand() % 2;
		int valor_random_2 = rand() % 2;

		if(valor_random_1) X_llenado[i] = true;
		else X_llenado[i] = false;
		if(valor_random_2) Y_tapado[i] = true;
		else Y_tapado[i] = false;

		SAL_A[i] = 0;
		SAL_B[i] = 0;
		SAL_C[i] = 0;
	}
}

Controlador::~Controlador(){}
void Controlador::logica(){
//	bool control = false;
//
//	if(b.getLlena() && b.getTapada() && !control){
//		b.setEstado(Acciones[2]);
//		b.setEvento(Eventos[1]);
//		control = true;
//	}
//	else{
//		if(b.getLlena() && !b.getTapada() && !control){
//			b.setEstado(Acciones[0]);
//			b.setEvento(Eventos[1]);
//		}
//		else{
//			if(!b.getLlena() && !b.getTapada()){
//				b.setEstado(Acciones[3]);
//				b.setEvento(Eventos[1]);
//				control = false;
//			}
//		}
//	}
}

