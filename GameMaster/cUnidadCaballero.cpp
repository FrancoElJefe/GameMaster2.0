#include "cUnidadCaballero.h"



cUnidadCaballero::cUnidadCaballero() :cClases(100, 40)
{
}

cUnidadCaballero::cUnidadCaballero(int hp, int at)
{
	HP = hp;
	AT = at;
}

int cUnidadCaballero::Ataque()
{
	return AT;
}

int cUnidadCaballero::RecibirAtaque(int Dano)
{
	setHp(HP - Dano);

	return (HP);
}


cUnidadCaballero::~cUnidadCaballero()
{
}
