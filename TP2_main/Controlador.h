/*
 * Controlador.h
 *
 *  Created on: 17 jun. 2022
 *      Author: gusty
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#define MAX 50																	 //
#define MIN 1
#define p 0.55

#include <string>
using namespace std;

class Controlador{
private:
	bool *X_llenado;
	bool *Y_tapado;
	bool *SAL_A;
	bool *SAL_B;
	bool *SAL_C;

public:
	Controlador(int);
	void logica();
	void mostrar(int);
	virtual ~Controlador();
};

#endif /* CONTROLADOR_H_ */
