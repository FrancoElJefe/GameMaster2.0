#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <ostream>
#include "cUnidadArquero.h"
#include "cLista.h"
#include "cTropa.h"

using namespace std;

class cTropaArquero : public cTropa
{
	int ATtropa;
	cLista<cUnidadArquero> * listaUnidades;
	static string nombre;
	static HANDLE consoleHandle;

public:
	cTropaArquero();

	void AgregarUnidades(int n);

	int Ataque();
	int RecibirAtaqueTropa(int dano, string clase);

	string getNombre() { return getNombreC(); }	
	static string getNombreC() { return nombre; }

	void PrintA();//funcion de prueba

	~cTropaArquero();
};

