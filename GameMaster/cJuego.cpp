#include "cJuego.h"


cJuego::cJuego()
{	
	Jugador1 = new cJugador("Jugador 1");
	Jugador2 = new cJugador("Jugador 2");
	America = new cContinente(16,"America");
	TropasJugador1[10] = {0};
	TropasJugador2[10] = {0};
	NrTropa = 0;
	Tcaballeros1 = 0;
	Tmagos1 = 0;
	Tarqueros1 = 0;
	Tcaballeros2 = 0;
	Tmagos2 = 0;
	Tarqueros2 = 0;
	Rondas = 0;
	srand(time(NULL));
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

}

void cJuego::CrearContinenteConPaises()
{
	string NomPaises[16] = { "Argentina", "Chile", "Uruguay" , "Brasil", "Peru", "Colombia", "Mexico", "California", "Oregon" , "Alaska", "Yukon", "Canada", "Nueva York", "Terranova", "Labrador", "Groenlandia" };

	America->AgregarPaises(&NomPaises[0]);
}

void cJuego::AsignarVecinos()
{
	string Vargentina[4] = { "Chile", "Uruguay", "Brasil", "Peru" };
	string Vchile[3] = { "Peru", "Argentina", "Groenlandia" };
	string Vuruguay[2] = { "Argentina", "Brasil" };
	string Vbrasil[4] = { "Argentina", "Uruguay", "Colombia", "Peru" };
	string Vperu[4] = { "Chile", "Argentina", "Brasil", "Colombia" };
	string Vcolombia[3] = { "Mexico", "Brasil", "Peru" };
	string Vmexico[2] = { "California", "Colombia" };
	string Vcalifornia[3] = { "Nueva York", "Oregon", "Mexico" };
	string Voregon[5] = { "Yukon", "Alaska", "Canada", "Nueva York", "California" };
	string Valaska[2] = { "Yukon", "Oregon" };
	string Vyukon[3] = { "Alaska", "Canada", "Oregon" };
	string Vcanada[4] = { "Terranova", "Nueva York", "Oregon", "Yukon" };
	string Vnuevayork[4] = { "Terranova", "Canada", "Oregon", "California" };
	string Vterranova[3] = { "Labrador", "Canada", "Nueva York" };
	string Vlabrador[2] = { "Groenlandia", "Terranova" };
	string Vgroenlandia[3] = { "Labrador", "Nueva York", "Chile" };

	America->AsignarVecinos("Argentina", &Vargentina[0], 4);
	America->AsignarVecinos("Chile", &Vchile[0], 3);
	America->AsignarVecinos("Uruguay", &Vuruguay[0], 2);
	America->AsignarVecinos("Brasil", &Vbrasil[0], 4);
	America->AsignarVecinos("Peru", &Vperu[0], 4);
	America->AsignarVecinos("Colombia", &Vcolombia[0], 3);
	America->AsignarVecinos("Mexico", &Vmexico[0], 2);
	America->AsignarVecinos("California", &Vcalifornia[0], 3);
	America->AsignarVecinos("Oregon", &Voregon[0], 5);
	America->AsignarVecinos("Alaska", &Valaska[0], 2);
	America->AsignarVecinos("Yukon", &Vyukon[0], 3);
	America->AsignarVecinos("Canada", &Vcanada[0], 4);
	America->AsignarVecinos("Nueva York", &Vnuevayork[0], 4);
	America->AsignarVecinos("Terranova", &Vterranova[0], 3);
	America->AsignarVecinos("Labrador", &Vlabrador[0], 2);
	America->AsignarVecinos("Groenlandia", &Vgroenlandia[0], 3);

}

void cJuego::AsignarPaisesAJugadores()
{
	int num, check = 0, paisesDeJugador1[8];

	for (int i = 0; i < 8; i++)
	{
		num = rand() % 16;

		check = Jugador1->AgregarPais(America->BuscarPais(num));

		if (check == 1)
		{
			i--;
		}
		else
		{
			paisesDeJugador1[i] = num;
		}

	}

	check = 0;

	for (int i = 0; i < America->getCaLista(); i++)
	{
		for (int k = 0; k < (America->getCaLista()) / 2; k++)
		{
			if (i == paisesDeJugador1[k])
			{
				check++;
			}
		}

		if (check == 0)
		{
			Jugador2->AgregarPais(America->BuscarPais(i));
		}
		else
		{
			check = 0;
		}

	}

}


void cJuego::EleccionDeUnidades(cJugador * jugadorX)
{
	int MaxUnidades = 0, caballeros = 0, magos = 0, arqueros = 0, opcion = 0, aux = 0, sobrecarga = 0, suma = 0;
	
	NrTropa = 0;

	do
	{
		cout << "---------" << endl;
		cout << jugadorX->getNombre() << endl;
		cout << "---------" << endl << endl;
		cout << "Eleccion de Unidades: (MaxUnidades 50) // Unidades ACTUALES: " << MaxUnidades << endl << endl;
		cout << "1) 10-20 unidades si son caballeros" << endl << "2) 15 - 30 si son arqueros" << endl << "3) 20 - 40 si son magos" << endl << endl;
		cout << "Caballeros : " << caballeros << endl;
		cout << "Arqueros : " << arqueros << endl;
		cout << "Magos : " << magos << endl << endl;

		cout << "Opcion: ";

		cin >> opcion;

		if (opcion == 1)
		{
			if (caballeros != 20)
			{
				aux = caballeros;

				do
				{
					suma = 0;
					cout << "Cantidad de Caballeros: ";
					cin >> suma;
					suma = suma + aux;
					sobrecarga = MaxUnidades + suma - aux;
					if (sobrecarga > 50)suma = 30;
				} while (suma > 20);
				MaxUnidades = MaxUnidades + suma - aux;
				caballeros = caballeros + suma - aux;
			}
			else
			{
				cout << "Maxima unidades de Caballeros" << endl;
			}

		}
		else if (opcion == 2)
		{
			if (arqueros != 30)
			{
				aux = arqueros;
				do
				{
					suma = 0;
					cout << "Cantidad de Arqueros: ";
					cin >> suma;
					suma = suma + aux;
					sobrecarga = MaxUnidades + suma - aux;
					if (sobrecarga > 50)suma = 40;
				} while (suma > 30);

				MaxUnidades = MaxUnidades + suma - aux;
				arqueros = arqueros + suma - aux;
			}
			else
			{
				cout << "Maxima unidades de Arqueros" << endl;
			}

		}
		else if (opcion == 3 && magos != 40)
		{
			aux = magos;
			do
			{
				suma = 0;
				cout << "Cantidad de Magos: ";
				cin >> suma;
				suma = suma + aux;
				sobrecarga = MaxUnidades + suma - aux;
				if (sobrecarga > 50)suma = 70;

			} while (suma > 40);
			MaxUnidades = MaxUnidades + suma - aux;
			magos = magos + suma - aux;
		}

		system("cls");

		if (MaxUnidades == 50)
		{
			if (magos == 0 || arqueros == 0 || caballeros == 0)
			{
				system("cls");
				cout << "Se debe tener 10 tropas, reingrese" << endl << endl;
				NrTropa = 0;
				caballeros = 0;
				arqueros = 0;
				magos = 0;
				MaxUnidades = 0;
				system("pause");
				system("cls");
			}
		}


	} while (MaxUnidades != 50);

	system("cls");

	if (jugadorX->getNombre() == "Jugador 1")
	{
		AgruparUnidadesEnTropas(jugadorX, Tcaballeros1, Tarqueros1, Tmagos1, caballeros, arqueros, magos);
		GeneradorDeTropasParaJugador(jugadorX, Tcaballeros1, Tarqueros1, Tmagos1);
	}
	else
	{
		AgruparUnidadesEnTropas(jugadorX, Tcaballeros2, Tarqueros2, Tmagos2, caballeros, arqueros, magos);
		GeneradorDeTropasParaJugador(jugadorX, Tcaballeros2, Tarqueros2, Tmagos2);
	}

	

}


void cJuego::GeneradorDeTropasParaJugador(cJugador * jugadorX, int Tcaballeros, int Tarqueros, int Tmagos)
{
	int Tropas[10];
	cout << endl;

	if (jugadorX->getNombre() == "Jugador 1")
	{
		for (int i = 0; i < 10; i++)
		{
			Tropas[i] = TropasJugador1[i];
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			Tropas[i] = TropasJugador2[i];
		}
	}


	cout << "Caballeros: " << endl;
	for (int i = 0; i < Tcaballeros; i++)
	{
		cout << "Tropa Nr " << i + 1 << ": " << Tropas[i] << " Unidades" << endl;
		jugadorX->agregarTropas(new cTropaCaballero, Tropas[i]);
	}
	cout << endl;
	cout << "Arqueros: " << endl;
	for (int i = Tcaballeros; i < Tarqueros + Tcaballeros; i++)
	{

		cout << "Tropa Nr " << i + 1 << ": " << Tropas[i] << " Unidades" << endl;
		jugadorX->agregarTropas(new cTropaArquero, Tropas[i]);
	}
	cout << endl;
	cout << "Magos: " << endl;
	for (int i = Tarqueros + Tcaballeros; i < Tmagos + Tcaballeros + Tarqueros; i++)
	{
		cout << "Tropa Nr " << i + 1 << ": " << Tropas[i] << " Unidades" << endl;
		jugadorX->agregarTropas(new cTropaMago, Tropas[i]);
	}
	system("Pause");
	system("cls");
}

void cJuego::Inicio(void)
{
	CrearContinenteConPaises(); //se le agregan los paises al continente
	AsignarVecinos();//se le agregan los vecinos a cada pais
	AsignarPaisesAJugadores(); // se le agregan los paises a cada jugador

	ModoDeJuego();//se elige jugar por rondas o hasta conquistar el continente

	EleccionDeUnidades(Jugador1);
	EleccionDeUnidades(Jugador2);

	AgregarTropasEnPais();
}

void cJuego::ModoDeJuego(void)
{
	string opcion;
	int check = 0;

	do
	{
		system("cls");
		if (check == 0)
		{
			cout << "Si quiere jugar a cierto numero de rondas escriba RONDAS, de lo contrario, si quiere jugar hasta conquistar el continente escriba COMBATE A MUERTE" << endl << endl;
			cout << ": ";
			cin >> opcion;
		}
		else
		{
			cout << "Si quiere jugar a cierto numero de rondas escriba RONDAS, de lo contrario, si quiere jugar hasta conquistar el continente escriba CONQUISTAR" << endl << endl;
			cout << ": " << opcion << endl;
		}


		if (opcion == "conquistar" || opcion == "CONQUISTAR")
		{
			IteradorDeRondas = 0;
			Rondas = 1;
		}
		else if (opcion == "rondas" || opcion == "RONDAS")
		{
			cout << "ingrese la cantidad de rondas: ";
			cin.clear();
			cin >> Rondas;
			if (Rondas == 0)
			{
				getchar();
				Rondas = 0;
				check = 1;
			}
			else if (Rondas != 0 && Rondas > 0)
			{
				IteradorDeRondas = 1;
			}
		}

	} while (Rondas == 0);

	system("cls");

}

void cJuego::AgruparUnidadesEnTropas(cJugador * jugadorX, int Tcaballeros, int Tarqueros, int Tmagos, int caballerox, int arquerox, int magox)
{
	int check = 0, numero = 0, Tropas[10] = {0}, MaxUnidades = 0, aux = 0, opcion= 0;

	MaxUnidades = caballerox;
	aux = arquerox;
	opcion = magox;

	do
	{
		caballerox = MaxUnidades;
		arquerox = aux;
		magox = opcion;

		for (int i = 0; i < 10; i++)
		{

			cout << "Armado de las tropas: " << endl << endl;

			cout << "---------" << endl;
			cout << jugadorX->getNombre() << endl;
			cout << "---------" << endl << endl;

			cout << "Caballeros : " << caballerox << endl;
			cout << "Arqueros : " << arquerox << endl;
			cout << "Magos : " << magox << endl << endl;

			if (caballerox != 0)
			{
				do
				{
					cout << "Caballeros: " << endl;
					cout << "Tropa Nr " << i + 1 << ":";
					cin >> numero;
					if (numero == 0) {
						getchar();
					}
					else
					{
						Tropas[i] = numero;
					}

					if (caballerox - Tropas[i] < 0)Tropas[i] = -1;

				} while (Tropas[i] <= 0);
				NrTropa++;
				caballerox = caballerox - Tropas[i];
				Tcaballeros++;
			}
			else if (arquerox != 0)
			{
				do
				{
					cout << "Arqueros: " << endl;
					cout << "Tropa Nr " << i + 1 << ":";
					cin >> numero;
					if (numero == 0) {
						getchar();
					}
					else
					{
						Tropas[i] = numero;
					}

					if (arquerox - Tropas[i] < 0)Tropas[i] = -1;

				} while (Tropas[i] <= 0);
				NrTropa++;
				Tarqueros++;
				arquerox = arquerox - Tropas[i];
			}
			else if (magox != 0)
			{
				do
				{
					cout << "Magos: " << endl;
					cout << "Tropa Nr " << i + 1 << ":";
					cin >> numero;
					if (numero == 0) {
						getchar();
					}
					else
					{
						Tropas[i] = numero;
					}

					if (magox - Tropas[i] < 0) {
						Tropas[i] = -1;
					}

				} while (Tropas[i] <= 0);
				NrTropa++;
				Tmagos++;
				magox = magox - Tropas[i];
			}

			check = check + Tropas[i];
			system("cls");

		}//FOR


		if (check != 50)
		{
			cout << endl << endl;
			SetConsoleTextAttribute(consoleHandle, FSCTL_GET_INTEGRITY_INFORMATION);
			cout << "Se debe tener 10 tropas, reingrese";
			SetConsoleTextAttribute(consoleHandle, 7);
			cout << endl << endl;
			check = 0;
			Tcaballeros = 0;
			Tarqueros = 0;
			NrTropa = 0;
			Tmagos = 0;
			system("pause");
			system("cls");
		}

	} while (check != 50);

	if (jugadorX->getNombre() == "Jugador 1")
	{
		Tcaballeros1 = Tcaballeros;
		Tarqueros1 = Tarqueros;
		Tmagos1 = Tmagos;

		for (int i = 0; i < 10; i++)
		{
			TropasJugador1[i] = Tropas[i];
		}
	}
	else
	{
		Tcaballeros2 = Tcaballeros;
		Tarqueros2 = Tarqueros;
		Tmagos2 = Tmagos;
		for (int i = 0; i < 10; i++)
		{
			TropasJugador2[i] = Tropas[i];
		}
	}

	system("cls");

}

void cJuego::AgregarTropasEnPais()
{
	Jugador1->setTropaEnPais();
	Jugador2->setTropaEnPais();
}

void cJuego::inicioPrueba(void)
{
	int caballeros = 0, arqueros = 0, magos = 0;
	ModoDeJuego();


	int Tropas[10];
	CrearContinenteConPaises(); //se le agregan los paises al continente
	AsignarVecinos();//se le agregan los vecinos a cada pais
	AsignarPaisesAJugadores(); // se le agregan los paises a cada jugador
	
	TropasJugador1[10] = { 0 };
	TropasJugador2[10] = { 0 };
	NrTropa = 0;
	Tcaballeros1 = 0;
	Tmagos1 = 0;
	Tarqueros1 = 0;
	Tcaballeros2 = 0;
	Tmagos2 = 0;
	NrTropa = 0;

	caballeros = 20;
	arqueros = 10;
	magos = 20;
	int Tcaballeros = 4;
	int Tarqueros = 3;
	int Tmagos = 3;

	Tcaballeros1 = Tcaballeros;
	Tarqueros1 = Tarqueros;
	Tmagos1 = Tmagos;


	for (int i = 0; i < Tcaballeros; i++)
	{
		TropasJugador1[i] = 5;
	}
	for (int i = Tcaballeros; i < Tcaballeros + arqueros; i++)
	{

		TropasJugador1[i] = 5;


	}
	for (int i = Tcaballeros + arqueros; i < Tcaballeros + Tmagos + Tarqueros; i++)
	{

		TropasJugador1[i] = 5;

	}

	GeneradorDeTropasParaJugador(Jugador1, Tcaballeros, Tarqueros, Tmagos);
	Jugador1->setTropasEnPaisesPrueba(Tcaballeros, Tarqueros, Tmagos);

	system("cls");

	caballeros = 10;
	arqueros = 20;
	magos = 20;
	Tcaballeros = 2;
	Tarqueros = 4;
	Tmagos = 4;

	Tcaballeros2 = Tcaballeros;
	Tarqueros2 = Tarqueros;
	Tmagos2 = Tmagos;

	for (int i = 0; i < Tcaballeros; i++)
	{
		TropasJugador2[i] = 10;
	}
	for (int i = Tcaballeros; i < Tcaballeros + Tarqueros; i++)
	{
		TropasJugador2[i] = 5;
	}
	for (int i = Tcaballeros + Tarqueros; i < Tcaballeros + Tarqueros + Tmagos; i++)
	{

		TropasJugador2[i] = 5;

	}

	GeneradorDeTropasParaJugador(Jugador2, Tcaballeros, Tarqueros, Tmagos);
	Jugador2->setTropasEnPaisesPrueba(Tcaballeros, Tarqueros, Tmagos);

	system("cls");
}

void cJuego::FaseDeAtaque()
{

	cPais* pais = NULL;
	string nombrePais;

	for (int i = 0; i < 3; i++)
	{
		pais = Jugador1->MenuAtacarPais();

		if (pais != NULL)
		{
			nombrePais = pais->AtacarOtroPais(Jugador1->getNombre());
			if (nombrePais == "atras")
			{
				i--;
			}
			else if (nombrePais != "0")
			{
				Jugador1->AgregarPais(America->BuscarPais(nombrePais));
			}

		}
		else
		{
			i--;
		}


	}
	   	  
}

void cJuego::cambio_de_ronda()
{

	int NPaises = 0, N = 0;

	NPaises = Jugador1->getNumeroDePaises();

	if (NPaises != 0)
	{

		if (NPaises != 16)
		{
			for (int i = 0; i < NPaises / 2; i++)
			{
				N = rand() % 3;

				if (N == 0) //caballero
				{
					Jugador1->agregarTropas(new cTropaCaballero, TropasJugador1[rand() % Tcaballeros1]);
				}
				else if (N == 1)//arquero
				{
					Jugador1->agregarTropas(new cTropaArquero, TropasJugador1[Tcaballeros1 + rand() % (Tarqueros1)]);
				}
				else if (N == 2)//mago
				{
					Jugador1->agregarTropas(new cTropaMago, TropasJugador1[(Tcaballeros1 + Tarqueros1) + rand() % (Tmagos1)]);
				}

			}

			NPaises = Jugador2->getNumeroDePaises();

			for (int i = 0; i < NPaises / 2; i++)
			{
				N = rand() % 3;

				if (N == 0) //caballero
				{
					Jugador2->agregarTropas(new cTropaCaballero, TropasJugador2[rand() % Tcaballeros2 + 1]);
				}
				else if (N == 1)//arquero
				{
					Jugador2->agregarTropas(new cTropaArquero, TropasJugador2[Tcaballeros2 + rand() % (Tarqueros2 + 1)]);
				}
				else if (N == 2)//mago
				{
					Jugador2->agregarTropas(new cTropaMago, TropasJugador2[(Tcaballeros2 + Tarqueros2) + rand() % (Tmagos2 + 1)]);
				}

			}

			AgregarTropasEnPais();
		}
		else
		{
			Turnos = 1;
		}

	}
	else
	{
		Turnos = 1;
	}



}

void cJuego::Resultados()
{
	system("cls");

	if (IteradorDeRondas == 1)
	{
		if (Jugador1->getNumeroDePaises() > Jugador2->getNumeroDePaises())
		{
			cout << "*********************************" << endl;
			cout << "El Jugador 1 gano, Felicitaciones" << endl;
			cout << "*********************************" << endl;
		}
		else if (Jugador1->getNumeroDePaises() > Jugador2->getNumeroDePaises())
		{
			cout << "*********************************" << endl;
			cout << "El Jugador 2 gano, Felicitaciones" << endl;
			cout << "**********************************" << endl;
		}
		else
		{
			cout << "***************************************************" << endl;
			cout << "Se determino que el jugador 1 y jugador 2 empataron" << endl;
			cout << "***************************************************" << endl;
		}

	}
	else
	{
		if (Jugador1->getNumeroDePaises() == 16)
		{
			cout << "**********************************************" << endl;
			cout << "El Jugador 1 conquisto America, Felicitaciones" << endl;
			cout << "**********************************************" << endl;

		}
		else
		{
			cout << "**********************************************" << endl;
			cout << "El Jugador 2 conquisto America, Felicitaciones" << endl;
			cout << "**********************************************" << endl;
		}

	}


	system("Pause");
}

void cJuego::ImprimirMapa(void)
{
	cPais * pais = NULL;
	int Npais[16];

	for (int i = 0; i < 16; i++)
	{
		pais = America->BuscarPais(i);
		Npais[i] = pais->getNjugador();
	}
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

}

cJuego::~cJuego()
{
	delete Jugador1;
	delete Jugador2;
	delete America;
}