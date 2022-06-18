#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include <string>
using namespace std;

/*#define MAX 50
#define MIN 1
#define p 0.55*/

typedef struct{
	int opcion;
	int n_eventos;
}Datos_inicio;

class Controlador{
private:
	bool *X_llenado;
	bool *Y_tapado;
	bool *SAL_A;
	bool *SAL_B;
	bool *SAL_C;
	string *accion;
	string *evento;
	Datos_inicio inicio;

public:
	Controlador(){};
	void Menu_inicio(int);
	int  Get_opcion() {return inicio.opcion;}
	void Set_valores();
	void logica();
	void mostrar(int);
	virtual ~Controlador();
};

#endif /* CONTROLADOR_H_ */
