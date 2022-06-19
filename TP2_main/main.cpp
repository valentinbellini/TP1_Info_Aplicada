

/////////////    ARCHIVO DE CABECERA    //////////////
#include "Controlador.h"							//
//////////////////////////////////////////////////////


///////////////   PROGRAMA PRINCIPAL   ///////////////
int main() {										//
	int sim = 0;									//
													//
		while(1) {									//
			sim++;									//
			Controlador driver;						//
			driver.Menu_Inicio(sim);				//
													//
			if(driver.Get_Opcion() == 1) {			//
				driver.Set_Valores();				//
				driver.Logica();					//
				driver.Mostrar(sim);				//
			}										//
			else break;								//
		}											//
													//
	return 0;										//
}													//
//////////////////////////////////////////////////////

