#include "Controlador.h"
#include <iostream>
#include <time.h>
#include <vector>

#define ANCHO_TEXTO -5
#define CONVERTIR(a) ( (a) ? "SI" : "NO" )

using std::cout;
using std::endl;
using std::vector;

vector<string>Acciones = {"Llenando",
						  "Tapando",
						  "Llenando y tapando",
						  "Cinta en movimiento",
						  "No se puede llenar",
						  "No se puede tapar"};

vector<string>Eventos = {"Imposible",
		    			 "Relevante",
						 "No modifica"};

Controlador::Controlador(int cant_simulaciones){
	int i;
	X_llenado = new bool[cant_simulaciones];
	Y_tapado = new bool[cant_simulaciones];
	SAL_A = new bool[cant_simulaciones];
	SAL_B = new bool[cant_simulaciones];
	SAL_C = new bool[cant_simulaciones];
	accion = new string[cant_simulaciones];
	evento = new string[cant_simulaciones];
	srand(time(NULL));

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

Controlador::~Controlador(){
	delete []X_llenado;
	delete []Y_tapado;
	delete []SAL_A;
	delete []SAL_B;
	delete []SAL_C;
	delete []accion;
	delete []evento;
	cout<<"Limpiando memoria..."<<endl;
}
void Controlador::logica(int n_eventos){
	int i;
	int flag = 0;
	for(i=0;i<n_eventos;i++){
		if(!i){
			if(!Y_tapado[i]){
				if(X_llenado[i]){
					//Se esta llenando.
					SAL_A[i] = true;
					SAL_B[i] = false;
					SAL_C[i] = false;
					accion[i].assign(Acciones[0]);
					evento[i].assign(Eventos[1]);
				}
				else{
					//Se esta moviendo la cinta
					SAL_A[i] = false;
					SAL_B[i] = false;
					SAL_C[i] = true;
					accion[i].assign(Acciones[3]);
					evento[i].assign(Eventos[1]);
				}
			}
			else{
				//No se puede tapar (Suceso imposible)
				SAL_A[i] = false;
				SAL_B[i] = false;
				SAL_C[i] = false;
				accion[i].assign(Acciones[5]);
				evento[i].assign(Eventos[0]);
			}
		}

		else{
			if(!Y_tapado[i] && !X_llenado[i]){
				//Se mueve la cinta
				SAL_A[i] = false;
				SAL_B[i] = false;
				SAL_C[i] = true;
				accion[i].assign(Acciones[3]);
				evento[i].assign(Eventos[1]);
				if(SAL_A[i-1]){
					flag = 1;
				}
			}

			else{
				if(!Y_tapado[i] && X_llenado[i]){
					if(!SAL_B[i-1] || (SAL_B[i-1] && SAL_A[i-1])){
						//Se esta llenando (se sigue llenando)
						//Se termino de tapar (2da condicion)
						SAL_A[i] = true;
						SAL_B[i] = false;
						SAL_C[i] = false;
						accion[i].assign(Acciones[0]);
						evento[i].assign(Eventos[1]);
					}

					else{
						if(SAL_B[i-1] && !SAL_A[i-1]){
							//No se puede llenar(suceso imposible)
							SAL_A[i] = SAL_A[i-1];
							SAL_B[i] = SAL_B[i-1];
							SAL_C[i] = false;
							accion[i].assign(Acciones[4]);
							evento[i].assign(Eventos[0]);
						}
					}
				}

				else{
					if(Y_tapado[i] && !X_llenado[i]){
						if(SAL_B[i-1]){
							//se esta tapando (o se sigue tapando)
							SAL_A[i] = false;
							SAL_B[i] = true;
							SAL_C[i] = false;
							accion[i].assign(Acciones[1]);
							evento[i].assign(Eventos[1]);
						}

						else{
							//No se puede tapar(suceso imposible)
							SAL_A[i] = SAL_A[i-1];
							SAL_B[i] = SAL_B[i-1];
							SAL_C[i] = false;
							accion[i].assign(Acciones[5]);
							evento[i].assign(Eventos[0]);
							if(!SAL_A[i-1] && flag){
								SAL_B[i] = true;
								flag = false;
								accion[i].assign(Acciones[1]);
								evento[i].assign(Eventos[1]);
							}
						}
					}

					else{
						if(Y_tapado[i] && X_llenado[i]){
							if(SAL_B[i-1] && SAL_A[i-1]){
								//Se esta tapando y llenando
								SAL_A[i] = true;
								SAL_B[i] = true;
								SAL_C[i] = false;
								accion[i].assign(Acciones[2]);
								evento[i].assign(Eventos[1]);
							}

							else{
								if(!SAL_A[i] && SAL_B[i]){
									//No se puede llenar
									SAL_A[i] = SAL_A[i-1];
									SAL_B[i] = SAL_B[i-1];
									SAL_C[i] = false;
									accion[i].assign(Acciones[4]);
									evento[i].assign(Eventos[0]);
								}

								else{
									//No se puede tapar
									SAL_A[i] = SAL_A[i-1];
									SAL_B[i] = SAL_B[i-1];
									SAL_C[i] = false;
									accion[i].assign(Acciones[5]);
									evento[i].assign(Eventos[0]);
									if(!SAL_A[i-1] && flag){
										SAL_B[i] = true;
										flag = false;
										accion[i].assign(Acciones[1]);
										evento[i].assign(Eventos[1]);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Controlador::mostrar(int n_eventos){
	int i;
	cout<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	printf("   BOTELLA X\t BOTELLA Y\t LLENADO(A)\t TAPADO(B)\t CINTA(C)\t Para el estado actual el evento \t    Accion\n");
	cout<<"----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	for(i=0;i<n_eventos;i++){
		//cout<<"        "<<X_llenado[i]<<"        "<<Y_tapado[i]<<"        "<<SAL_A[i]<<"        "<<SAL_B[i]<<"        "<<SAL_C[i]<<"        "<<evento[i]<<"        "<<accion[i]<<endl;
		printf("       %*s  |",ANCHO_TEXTO,CONVERTIR(X_llenado[i]));
		printf("       %*s  |",ANCHO_TEXTO,CONVERTIR(Y_tapado[i]));
		printf("       %*s   |",ANCHO_TEXTO,CONVERTIR(SAL_A[i]));
		printf("       %*s   |",ANCHO_TEXTO,CONVERTIR(SAL_B[i]));
		printf("       %*s   |",ANCHO_TEXTO,CONVERTIR(SAL_C[i]));
		cout<<"		    "<<evento[i];
		cout<<"		    |  "<<accion[i];
		printf("\n");
	}
	cout<<"//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
	cout<<endl;
}
