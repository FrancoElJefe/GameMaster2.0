#include "cUnidadArquero.h"



cUnidadArquero::cUnidadArquero():cClases(80,30)
{
}

cUnidadArquero::cUnidadArquero(int hp, int at)
{
	HP = hp;
	AT = at;
}

int cUnidadArquero::Ataque()
{
	return AT;
}

int cUnidadArquero::RecibirAtaque(int Dano)
{
	setHp(HP - Dano);

	return (HP);
	
}


cUnidadArquero::~cUnidadArquero()
{
}
