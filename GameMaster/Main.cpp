#include <stdio.h>
#include "stdlib.h"
#include <ostream>
#include "cLista.h"
#include<time.h>
#include "cJuego.h"


int main(void) {
		
	cJuego * GameMaster = new cJuego;
	int rondas = 0;

	GameMaster->Inicio();
	do
	{
		GameMaster->FaseDeAsignacion();

		GameMaster->FaseDeAtaque();
		
		rondas = GameMaster->FaseDeMovimiento();

	} while (rondas > 0);	

	GameMaster->Resultados();
	
	delete GameMaster;
	return 0;
}


