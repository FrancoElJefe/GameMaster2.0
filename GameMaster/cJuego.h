#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include <ostream>
#include <windows.h>
#include "cJugador.h"
#include "cContinente.h"
#include "cTropaCaballero.h"
#include "cUnidadCaballero.h"
#include "cTropaMago.h"
#include "cUnidadMago.h"
#include "cTropaArquero.h"
#include "cUnidadArquero.h"
#include <time.h>

using namespace std;

class cJuego
{
	cJugador * Jugador1;
	cJugador * Jugador2;
	cContinente * America;
	HANDLE consoleHandle;
	int TropasJugador1[10];
	int TropasJugador2[10];
	int NrTropa;
	int Tcaballeros1;
	int Tmagos1;
	int Tarqueros1;
	int Tcaballeros2;
	int Tmagos2;
	int Tarqueros2;
	int Turnos;
	int Rondas;
	int IteradorDeRondas;

	void EleccionDeUnidades(cJugador * jugadorX); //el jugador elecciona 50 unidades constituedas por las tres facciones 
	void AgruparUnidadesEnTropas(cJugador * jugadorX, int Tcaballeros, int Tarqueros, int Tmagos, int caballerox, int arquerox, int magox); // el jugador agrupa sus unidades en 10 tropas
	void GeneradorDeTropasParaJugador(cJugador * jugadorX, int Tcaballeros, int Tarqueros, int Tmagos); // se generan las tropas y se las da al jugador
	void CrearContinenteConPaises();
	void AsignarVecinos(); // esta funcion asigna los vecinos a los distintos paises
	void AsignarPaisesAJugadores();
	void ModoDeJuego(void);
	void AgregarTropasEnPais();

public:
	cJuego();
		
	void Inicio(void);
			
	void inicioPrueba(void);

	void FaseDeAtaque();
	void cambio_de_ronda();
	void Resultados();

	void ImprimirMapa(void);

	~cJuego();
};

