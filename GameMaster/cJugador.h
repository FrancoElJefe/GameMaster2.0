#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include <ostream>
#include <windows.h>
#include "cLista.h"
#include "cTropa.h"
#include "cPais.h"
#include <time.h>

using namespace std;

class cJugador
{
	string nombre;
	cLista<cTropa> * listaDeTropas;	
	cLista<cPais> * listaPropiaPaises;
	static HANDLE consoleHandle;

public:
	cJugador();
	cJugador(string nomb);

	
	void setTropaEnPais(void);
	void agregarTropas(cTropa * ptr, int n);
	int AgregarPais(cPais *ptr);
	cPais* quitarPais(string pais);
		
	cPais* MenuAtacarPais();
	
	string getNombre() { return nombre; }
	int getNumeroDePaises() { return listaPropiaPaises->getCA(); }
	void MenuFaseDeMovimiento();

	void ImprimirMapa();
	void listarSusPaises(); // funcion de prueba
	void listarTropas(); //funcion de prueba
	void setTropasEnPaisesPrueba(int caballeros, int arqueros, int magos);//funcion de prueba

	~cJugador();
};

