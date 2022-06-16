/*
 * Botella.h
 *
 *  Created on: 16 jun. 2022
 *      Author: valentin
 */

#ifndef BOTELLA_H_
#define BOTELLA_H_


class Botella {
private:
	bool llenado;
	bool tapado;
	typedef struct entradas{
		bool X = 0;
		bool Y = 0;
	}entradas;

public:
	Botella():llenado(false),tapado(false){}
	virtual ~Botella();
	bool getTapado(int); //Responde si una botella esta tapada o no
	bool getllenado(int); //REsponde si una botella esta llena o no
	void logica();

};

#endif /* BOTELLA_H_ */
