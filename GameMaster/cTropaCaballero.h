#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include <ostream>
#include <windows.h>
#include "cUnidadCaballero.h"
#include "cLista.h"
#include "cTropa.h"

using namespace std;

class cTropaCaballero : public cTropa
{
	int ATtropa;
	cLista<cUnidadCaballero> * listaUnidades;
	static string nombre;
	static HANDLE consoleHandle;

public:
	cTropaCaballero();

	void AgregarUnidades(int N);
	int Ataque();
	int RecibirAtaqueTropa(int dano, string clase);

	string getNombre() { return getNombreC(); }
	static string getNombreC() { return nombre; }


	void PrintA();//funcion de prueba

	~cTropaCaballero();
};

