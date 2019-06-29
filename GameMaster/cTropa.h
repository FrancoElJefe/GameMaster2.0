#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <conio.h>
#include <iostream>
#include <ostream>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;
class cTropa
{

public:

	cTropa();

	virtual void AgregarUnidades(int n) = 0;

	virtual int Ataque() = 0;
	virtual int RecibirAtaqueTropa(int dano, string clase) = 0;

	virtual void PrintA() = 0;

	virtual string getNombre() = 0;

	~cTropa();
};

