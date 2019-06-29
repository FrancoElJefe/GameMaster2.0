#include "cJugador.h"

HANDLE cJugador::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

cJugador::cJugador()
{
	srand(time(NULL));
	nombre = "";
	listaPropiaPaises = new cLista<cPais>(16);
	listaDeTropas = new cLista<cTropa>;
}

cJugador::cJugador(string nomb) : cJugador()
{
	nombre = nomb;
}

void cJugador::setTropaEnPais(void)
{
	unsigned int opc = 0, EleccionDePais = 0;
	int opc3=0, Tropas,check=0;
	unsigned int opc2;
	cPais * pais;
	int variabaleControl = 10;

	//agrego de forma random tropas a los paises

	for (int i = 0; i < 8; i++)
	{
		pais = listaPropiaPaises->getItem(i);
		pais->AgregarTropaPais(listaDeTropas->QuitarenPos(rand() % variabaleControl));
		variabaleControl--;
	}
		

	Tropas = listaDeTropas->getCA();
	do
	{
		system("cls");
		cout << "\t\tDISTRIBUYE LAS TROPAS EN TUS PAISES" << endl << endl;
		cout << "---------" << endl;
		cout << nombre << endl;
		cout << "---------" << endl << endl;
		
		cout << "Tropas: "<< endl;
		listaDeTropas->Listar();

		listaPropiaPaises->ListarV();
		cout << endl;
		cout << "Seleccione el Pais que quiera agregar: ";
		cin.clear();
		cin >> EleccionDePais;

		if (EleccionDePais == 0)
		{
			getchar();
			EleccionDePais = 0;
		}
		else
		{
			if (EleccionDePais <= listaPropiaPaises->getCA()) {

				pais = listaPropiaPaises->getItem(EleccionDePais - 1);
				do
				{
					system("cls");
					listaDeTropas->Listar();

					cout << "Elija la tropa que desee: ";
					cin.clear();
					cin >> opc2;

					pais->AgregarTropaPais(listaDeTropas->QuitarenPos(opc2 - 1));
					opc = 1;
			

				} while (opc != 1);

				check = 0;
				opc = 0;

				cout << endl;
				cout << pais->getCodigo();
				cout << endl;
				pais->PrintTropas();
				system("pause");
				Tropas--;
			}
		}

		system("cls");

	} while (Tropas != 0);

}

void cJugador::agregarTropas(cTropa * ptr, int n)
{
	ptr->AgregarUnidades(n);
	listaDeTropas->AgregarItem(ptr);
}

cPais* cJugador::quitarPais(string pais)
{
	return listaPropiaPaises->Quitar(pais);
}

cPais * cJugador::MenuAtacarPais()
{
	int opcion = 0,check = 0;
	string opcion2;
	string resultado;
	cPais * pais = NULL;
		
	cout << "---------" << endl;
	cout << nombre << endl;
	cout << "---------" << endl << endl;
	
	
	listaPropiaPaises->ListarV();

	cout << "Selecciona el pais con el que queres atacar, si quieres pasar presiona un numero mayor a la cantidad de paises que tiene"<< endl;
	cout << "Pais: ";
	cin.clear();
	cin >> opcion;
	if (opcion == 0)
	getchar();

	if (opcion > listaPropiaPaises->getCA())
	{
		return(NULL);

	}else if (opcion-1 < listaPropiaPaises->getCA() && opcion != 0)
	{
		pais = listaPropiaPaises->getItem(opcion - 1);

		check = pais->getCantidadDeTropas();

		if (check < 2)
		{
			SetConsoleTextAttribute(consoleHandle, FSCTL_GET_INTEGRITY_INFORMATION);
			cout << endl << "Reingrese opcion, se debe atacar con un pais que tenga mas de una tropa.";
			SetConsoleTextAttribute(consoleHandle, 7);
			cout << endl;

			system("pause");
			return(NULL);
			system("cls");
		}
		else
		{
			return pais;
		}
	}
	else
	{
		system("cls");
		return (NULL);
	}
	


	   
}

int cJugador::AgregarPais(cPais * ptr)
{
	cPais * pais;

	for (int i = 0; i < listaPropiaPaises->getCA(); i++)
	{
		pais = listaPropiaPaises->getItem(i);

		if (ptr->getCodigo() == pais->getCodigo())
		{
			return 1;
		}

	}

	ptr->setJugador(nombre);

	listaPropiaPaises->AgregarItem(ptr);

	return 0;
}


void cJugador::listarSusPaises()
{
	listaPropiaPaises->Listar();
}

void cJugador::listarTropas()
{
	cout << "Tropas: " << endl;
	listaDeTropas->Listar();
}

void cJugador::setTropasEnPaisesPrueba(int caballeros, int arqueros, int magos)
{
	cPais * pais;
	int cont = 0;

	for (int i = 0; i < 10; i++)
	{

		pais = listaPropiaPaises->getItem(cont);

		pais->AgregarTropaPais(listaDeTropas->QuitarenPos(0));
		cont++;
		if (cont > 7)
		{
			cont = 0;
		}

	}
}


cJugador::~cJugador()
{
	if (listaDeTropas != NULL)
	{
		delete listaDeTropas;
	}

}
	
	
	
