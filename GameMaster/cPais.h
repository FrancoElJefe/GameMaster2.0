#pragma once
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <ostream>
#include <time.h>
#include <windows.h>
#include "cLista.h"
#include "cTropaCaballero.h"
#include "cTropaArquero.h"
#include "cTropaMago.h"
#include "cTropa.h"


using namespace std;

class cPais
{
	const string nombre;
	int jugador;
	cLista<cTropa> * TropasEnPais;
	static cLista<cPais> * listaPaises;
	cLista<cPais> * vecinos;
	static HANDLE consoleHandle;

public:
	
	cPais();
	cPais(string nomb);

	void AgregarTropaPais(cTropa * ptr);

	void AgregarVecinos(cPais * ptr);

	void setJugador(string jug);

	void MoverTropa(string jugador);

	string AtacarOtroPais(string nomb); //Yo Ataco
	int Atacado(int ntropa, int dano, string claseTAtacante);  //Recibo Ataque
	int AtacadoPorMagos(string Natacante, int dano);
	int ContrataqueDeCaballeros(cTropa * ptr, int Ntropa);

	int getNjugador() { return jugador; }
	const string getCodigo() { return nombre; }
	int getCantidadDeTropas() { return TropasEnPais->getCA(); }
	int getCantTcaballero();
	int getCantTMago();
	int getCantTarquro();
	
	void PrintA(); // mostrar nombre de paises
	void PrintTropas();//funcion de prueba
	void printTodos();//funcion de prueba
		
	void PrintPaisConTropas(void);
	void ImprimirMapa(void);
	void PrintNombre();
	void titulo(cPais * paisParaATACAR, int estado, string nombre, int jugador, HANDLE consoleHandle);
	~cPais();
};

/*
paises:

-argentina : chile, uruguay, brasil y peru
-brasil : uruguay, argentina, peru y colombia
-peru : colombia, brasil, argintina, chile
-colombia : peru, brasil y mexico 
-chile : peru, argentina y groenlandia
-uruguay : argentina y brasil
-canada : terranova , nueva york, oregon y yukon
- nueva york : terranova, canada , oregon y california
-yukon : alaska, canada y oregon
-alaska : yukon y oregon
-groenlandia : labrador, nueva york y chile
-oregon : yukon, alaska, canada, nueva york y california
-california : nueva york, oregon y mexico
-mexico : california y colombia
-teranova : labrador, canada y nueva york
-labrador : groenlandia y terranova

*/