#include <stdio.h>
#include "stdlib.h"
#include <ostream>
#include "cLista.h"
#include<time.h>
#include "cJuego.h"


int main(void) {
		
	cJuego * GameMaster = new cJuego;

	GameMaster->inicioPrueba();

	//GameMaster->FaseDeAsignacion();

	//GameMaster->FaseDeAtaque();
	
	GameMaster->FaseDeMovimiento();

	GameMaster->Resultados();
	
	delete GameMaster;
	return 0;
}


