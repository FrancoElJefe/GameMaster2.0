#include "cUnidadMago.h"



cUnidadMago::cUnidadMago() :cClases(60, 20)
{
}

cUnidadMago::cUnidadMago(int hp, int at)
{
	HP = hp;
	AT = at;
}

int cUnidadMago::Ataque()
{
	return AT;
}

int cUnidadMago::RecibirAtaque(int Dano)
{
	setHp(HP - Dano);

	return (HP);
}


cUnidadMago::~cUnidadMago()
{
}
