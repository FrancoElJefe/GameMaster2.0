#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include <ostream>
#include "cClases.h"

using namespace std;

class cUnidadCaballero : cClases
{
public:
	cUnidadCaballero();
	cUnidadCaballero(int hp, int at);

	int Ataque();
	int RecibirAtaque(int Dano);

	int getHP() { return HP; }

	~cUnidadCaballero();
};

