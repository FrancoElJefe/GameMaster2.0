#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include <ostream>
#include <windows.h>
#include "cUnidadMago.h"
#include "cLista.h"
#include "cTropa.h"

using namespace std;

class cTropaMago : public cTropa
{
	int ATtropa;
	cLista<cUnidadMago> * listaUnidades;
	static string nombre;
	static HANDLE consoleHandle;

public:
	cTropaMago();

	void AgregarUnidades(int n);
	int Ataque();
	int RecibirAtaqueTropa(int dano, string clase);

	string getNombre() { return getNombreC(); }//funcion del padre
	static string getNombreC() { return nombre; }
	int getCUnidades() { return listaUnidades->getCA(); }

	void PrintA();//funcion de prueba

	~cTropaMago();
};

