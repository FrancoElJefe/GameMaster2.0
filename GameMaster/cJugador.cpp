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

void cJugador::setTropaEnPais(int Turno)
{
	unsigned int opc = 0, EleccionDePais = 0, combinacion = 0, opc2=0;
	int Tropas=0,check=0;
	cPais * pais  = NULL;
	string CTropa = "";
	int variabaleControl = 10;

	
	if (Turno == 0)
	{
		for (int i = 0; i < 8; i++)//agrego de forma random tropas a los paises
		{
			pais = listaPropiaPaises->getItem(i);
			pais->AgregarTropaPais(listaDeTropas->QuitarenPos(rand() % variabaleControl));
			variabaleControl--;
		}
	}		

	Tropas = listaDeTropas->getCA();
	do
	{
		system("cls");

		ImprimirMapa();

		cout << "\t\t***********************************" << endl;
		cout << "\t\tDISTRIBUYE LAS TROPAS EN TUS PAISES" << endl;
		cout << "\t\t***********************************" << endl << endl;
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
					if (opc2 == 0)getchar();

					if (opc2 > 0 && opc2 <= listaDeTropas->getCA())
					{

						cTropaCaballero * tropaC = dynamic_cast<cTropaCaballero*>(listaDeTropas->getItem(opc2-1));
						if (tropaC != NULL && pais->getCantTcaballero() >= 1)
						{
							cout << "Quiere combinar tropas, escriba si o no:";
							cin >> CTropa;

							if (CTropa == "si")
							{
								pais->PrintTropasCaballero();
								cout << endl << "Tropa a combinar:";
								cin.clear();
								cin >> combinacion;

								if (combinacion == 0)getchar();

								if (opc2 - 1 < pais->getCantTcaballero() && combinacion <= pais->getCantTcaballero() && combinacion != 0) {

									pais->combinarTROPA(listaDeTropas->QuitarenPos(opc2 - 1), combinacion - 1, "CABALLERO");
									cout << endl;
									cout << pais->getCodigo();
									cout << endl;
									pais->PrintTropas();
									opc = 1;
									system("pause");
								}							

							}
							else
							{
								pais->AgregarTropaPais(listaDeTropas->QuitarenPos(opc2 - 1));
								opc = 1;
							}
						}
						else
						{
							cTropaArquero * tropaA = dynamic_cast<cTropaArquero*>(listaDeTropas->getItem(opc2-1));
							if (tropaA != NULL && pais->getCantTarquro() >= 1)
							{
								cout << "Quiere combinar tropas, escriba si o no:";
								cin >> CTropa;

								if (CTropa == "si")
								{
									pais->PrintTropasCaballero();
									cout << "Tropa a combinar:";
									cin.clear();
									cin >> combinacion;

									if (combinacion == 0)getchar();

									if (opc2 - 1 < pais->getCantTcaballero() && combinacion <= pais->getCantTcaballero() && combinacion != 0) {

										pais->combinarTROPA(listaDeTropas->QuitarenPos(opc2 - 1), combinacion - 1, "ARQUERO");
										cout << endl;
										cout << pais->getCodigo();
										cout << endl;
										pais->PrintTropas();
										opc = 1;
										system("pause");
									}

								}
								else
								{
									pais->AgregarTropaPais(listaDeTropas->QuitarenPos(opc2 - 1));
									opc = 1;
								}
							}
							else
							{
								cTropaMago * tropaM = dynamic_cast<cTropaMago*>(listaDeTropas->getItem(opc2-1));
								if (tropaM != NULL && pais->getCantTMago() >= 1)
								{
									cout << "Quiere combinar tropas, escriba si o no:";
									cin >> CTropa;

									if (CTropa == "si")
									{
										pais->PrintTropasCaballero();
										cout << "Tropa a combinar:";
										cin.clear();
										cin >> combinacion;

										if (combinacion == 0)getchar();

										if (opc2 - 1 < pais->getCantTcaballero() && combinacion <= pais->getCantTcaballero() && combinacion != 0) {

											pais->combinarTROPA(listaDeTropas->QuitarenPos(opc2 - 1), combinacion - 1, "MAGO");
											cout << endl;
											cout << pais->getCodigo();
											cout << endl;
											pais->PrintTropas();
											opc = 1;
											system("pause");
										}

									}
									else
									{
										pais->AgregarTropaPais(listaDeTropas->QuitarenPos(opc2 - 1));
										opc = 1;
									}
								}
								else
								{
									pais->AgregarTropaPais(listaDeTropas->QuitarenPos(opc2 - 1));
									opc = 1;
								}
							}
							
						}						
					}			

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

	system("cls");

	ImprimirMapa();
		
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

	if (opcion > listaPropiaPaises->getCA())//pasas de ronda
	{
		pais = new cPais("PasarRonda");
		return(pais);

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


void cJugador::MenuFaseDeMovimiento()
{
	int opcion = 0, Check = 0;
	cPais * pais = NULL;

	do
	{
		system("cls");

		ImprimirMapa();

		cout << "\t\t****************************************************" << endl;
		cout << "\t\tFASE DE MOVIMIENTO: reorganice las tropas a su gusto" << endl;
		cout << "\t\t****************************************************" << endl << endl;
		cout << "---------" << endl;
		cout << nombre << endl;
		cout << "---------" << endl << endl;

		listaPropiaPaises->ListarV();

		cout << "-Selecciona el pais el cual quiere mover alguna tropa-" << endl;
		cout << "Pais: ";
		cin.clear();
		cin >> opcion;
		if (opcion == 0)getchar();

		if (opcion > 0 && opcion <= listaPropiaPaises->getCA())
		{
			pais = listaPropiaPaises->getItem(opcion - 1);

			if (pais->getCantidadDeTropas() >= 2)
			{
				pais->MoverTropa(nombre);
			}
			else
			{
				SetConsoleTextAttribute(consoleHandle, FSCTL_GET_INTEGRITY_INFORMATION);
				cout << "***Para pasar tropas se debe tener por lo menos dos o mas en el territorio***" << endl << endl;
				SetConsoleTextAttribute(consoleHandle, 7);

				system("Pause");
			}			

		}

	} while (opcion != 0);

}

void cJugador::ImprimirMapa()
{
	cPais * pais = NULL;
	string NomPaises[16] = { "Argentina", "Chile", "Uruguay" , "Brasil", "Peru", "Colombia", "Mexico", "California", "Oregon" , "Alaska", "Yukon", "Canada", "Nueva York", "Terranova", "Labrador", "Groenlandia" };
	int Npais[16] = {0}, cantPaises = 0;

	cantPaises = listaPropiaPaises->getCA();

	for (int i = 0; i < cantPaises; i++)
	{
		pais = listaPropiaPaises->getItem(i);
		for (int k = 0; k < 16; k++)
		{
			if (pais->getCodigo() == NomPaises[k] && nombre == "Jugador 1")
			{
				Npais[k] = 1;
			}
			else if (pais->getCodigo() == NomPaises[k] && nombre == "Jugador 2")
			{
				Npais[k] = 2;
			}
		}		
	}
	for (int i = 0; i < 16; i++)
	{
		if (Npais[i] == 0 && nombre == "Jugador 1")
		{
			Npais[i] = 2;
		}
		else if (Npais[i] == 0 && nombre == "Jugador 2")
		{
			Npais[i] = 1;
		}

	}
	SetConsoleTextAttribute(consoleHandle, 7);
	cout << "\t\t	                                                                                _________________" << endl;
	cout << "\t\t	                           ____________                                        |                 |" << endl;
	cout << "\t\t	                      ____/            |                                       |                 |" << endl;
	cout << "\t\t	 ____________________/    |            |                                       |                 |" << endl;
	cout << "\t\t	|            /            | CANADA(" << Npais[11] << ")  |              ___________              |  GROENLANDIA(" << Npais[15] << ") |" << endl;
	cout << "\t\t	| ALASKA(" << Npais[9] << ") /  YUKON(" << Npais[10] << ")   |            |             |           |             |                 |" << endl;
	cout << "\t\t\t|__________/______________|____________|______       |LABRADOR(" << Npais[14] << ")|-------------|                 |" << endl;
	cout << "\t\t	|                         |                   |______|___________|             |_________________|" << endl;
	cout << "\t\t	|                          |                                    |                  /" << endl;
	cout << "\t\t	|                           |__         TERRANOVA(" << Npais[13] << ")            |                 /" << endl;
	cout << "\t\t	 |          OREGON(" << Npais[8] << ")          |________________________________|                /" << endl;
	cout << "\t\t	  |                               |__                           |               /" << endl;
	cout << "\t\t	   |                                 |__    NUEVA YORK(" << Npais[12] << ")       /--------------/" << endl;
	cout << "\t\t	    |___________________________________|______________________/" << endl;
	cout << "\t\t	     |                                                        /" << endl;
	cout << "\t\t	      |                CALIFORNIA(" << Npais[7] << ")                         /" << endl;
	cout << "\t\t	       |____________________________________________________/" << endl;
	cout << "\t\t	                         |_                                /" << endl;
	cout << "\t\t	                           |__                            /" << endl;
	cout << "\t\t	                              |___                       /" << endl;
	cout << "\t\t	                                  |       MEXICO(" << Npais[6] << ")     |" << endl;
	cout << "\t\t	                                   | ___                | " << endl;
	cout << "\t\t	                                        |___            | " << endl;
	cout << "\t\t	                                            |           |" << endl;
	cout << "\t\t	                                             |__        |" << endl;
	cout << "\t\t	                                                |__     | " << endl;
	cout << "\t\t	                                                   |___ |" << endl;
	cout << "\t\t	                                                       ||__________________________________________" << endl;
	cout << "\t\t	                                                       /                 |                         |_" << endl;
	cout << "\t\t	                                                      /                  |                           |_" << endl;
	cout << "\t\t	                                                      |    COLOMBIA(" << Npais[5] << ")   |                             |_" << endl;
	cout << "\t\t	                                                      |__________________|                               |_" << endl;
	cout << "\t\t	                                                      |                   |_                               |_" << endl;
	cout << "\t\t	                                                      |                     |_        BRASIL(" << Npais[3] << ")              |" << endl;
	cout << "\t\t	                                                      |                       |_                            /" << endl;
	cout << "\t\t	                                                      |        PERU(" << Npais[4] << ")          |                          /" << endl;
	cout << "\t\t	                                                      |                         |                         /" << endl;
	cout << "\t\t	                                                      |_________________________|________________________/" << endl;
	cout << "\t\t	                                                      |            |                    |               /" << endl;
	cout << "\t\t	                                                      |            /                    |              /" << endl;
	cout << "\t\t	                                                      |           |                     | URUGUAY(" << Npais[2] << ")  |" << endl;
	cout << "\t\t	                                                      |           |                     |            /" << endl;
	cout << "\t\t	                                                      |   (" << Npais[1] << ")      |                    |           /" << endl;
	cout << "\t\t	                                                      |    C      /                      |_________|" << endl;
	cout << "\t\t	                                                      |    H      |                            |" << endl << endl;
	cout << "------------------------------------------------------------------------------|    I      |                            |" << endl << endl;
	cout << "\t\t	                                                      |    L      |    ARGENTINA(" << Npais[0] << ")          _/" << endl;
	cout << "\t\t	                                                      |    E      /                         /" << endl;
	cout << "\t\t	                                                      |          /                       /" << endl;
	cout << "\t\t	                                                       |        /                      /" << endl;
	cout << "\t\t	                                                        |      /                     /" << endl;
	cout << "\t\t	                                                        |      |                   /" << endl;
	cout << "\t\t	                                                        |      |                 /" << endl;
	cout << "\t\t	                                                        |      |               /" << endl;
	cout << "\t\t	                                                        |      |             /" << endl;
	cout << "\t\t	                                                        |      |           /" << endl;
	cout << "\t\t	                                                         |      |         /" << endl;
	cout << "\t\t	                                                          |     |       /" << endl;
	cout << "\t\t	                                                           |    |     /" << endl;
	cout << "\t\t	                                                            |   |   /" << endl;
	cout << "\t\t	                                                              |_|_/" << endl;

	cout << endl;
	SetConsoleTextAttribute(consoleHandle, 7);


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
	
	
	
