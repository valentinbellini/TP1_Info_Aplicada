#include "Controlador.h"

/*#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

using namespace std;
using std::cout;
using std::cin;
using std::endl;*/

int main() {
	int sim = 0;

		while(1) {
			sim++;
			Controlador driver;
			driver.Menu_inicio(sim);

			if(driver.Get_opcion() == 1) {
				driver.Set_valores();
				driver.logica();
				driver.mostrar(sim);
			}
			else break;
		}

	return 0;
}
