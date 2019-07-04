#include "cPais.h"

cLista<cPais> *cPais::listaPaises = new cLista<cPais>(16);
HANDLE cPais::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

typedef enum MyEnum {PLimitrofes=0, EPaisParaAtacar, EdeMiTropas, ETropaEnemiga, MagoContraArquero, MagoContraCaballero, MagoContraMago, ConquistasteElPais};

cPais::cPais()
{
	jugador = 0;
}

cPais::cPais(string nomb) : nombre(nomb)
{
	vecinos = new cLista<cPais>();
	TropasEnPais = new cLista<cTropa>;
	jugador = 0;
	if (nombre != "PasarRonda")
	{
		listaPaises->AgregarItem(this);
	}	
	srand(time(NULL));//inicializo los numeros random
}

void cPais::AgregarTropaPais(cTropa * ptr)
{
	TropasEnPais->AgregarItem(ptr);
}

void cPais::AgregarVecinos(cPais * ptr)
{
	vecinos->AgregarItem(ptr);
}

void cPais::setJugador(string jug)
{
	if (jug == "Jugador 1" )
	{
		jugador = 1;
	}	
	else
	{
		jugador = 2;
	}
}

void cPais::MoverTropa(string jugador)
{
	int cVecinos = 0;//cantidad de vecinos
	int paisT = 0, TropaApasar=0;
	cPais * pais = NULL;

	system("cls");

	ImprimirMapa();

	cout << "Paises limitrofes suyos: " << endl << endl;
	cVecinos = vecinos->ListarVecinosTuyos(jugador);
	
	if (cVecinos == 0)
	{
		SetConsoleTextAttribute(consoleHandle, FSCTL_GET_INTEGRITY_INFORMATION);
		cout << "***No tiene paises vecinos enemigos***" << endl << endl;
		SetConsoleTextAttribute(consoleHandle, 7);

		system("Pause");
	}
	else
	{
		cout << endl << "-Elija el pais el cual quiere pasarle alguna tropa, de contrario ponga 0-" << endl;
		cout << "Pais: ";
		cin >> paisT;

		if (paisT > 0 && paisT <= cVecinos)
		{
			pais = vecinos->getVecinoTuyo(jugador, paisT - 1);

			PrintTropas();

			cout << endl << "Cual tropa desea pasar a " << pais->getCodigo() << endl;
			cout << "Tropa: ";
			cin >> TropaApasar;

			if (TropaApasar > 0 && TropaApasar <= TropasEnPais->getCA())
			{
				pais->AgregarTropaPais(TropasEnPais->QuitarenPos(TropaApasar - 1));
			}
			else
			{
				SetConsoleTextAttribute(consoleHandle, FSCTL_GET_INTEGRITY_INFORMATION);
				cout << "***No existe la tropa***" << endl << endl;
				SetConsoleTextAttribute(consoleHandle, 7);

				system("Pause");
			}


		}
	}
	
}

string cPais::AtacarOtroPais(string nomb)
{
	int opcion = 0, OpcionTropaTuya = 0, fin = 0, sinTROPA = 0, sinTROPAmia = 0, Otropas = 0, estado = 0, i = 1, cVecinos = 0, eliminar = 0;
	string salir; 
	unsigned int clase_tuya = 0, clase_slc = 0;
	char atras;
	cPais * PaisParaAtacar = NULL;
	
	cTropa *TropaTuya = NULL;

	system("cls");
	getchar();

	do
	{
		
		
		switch (estado)
		{
		case PLimitrofes:

			titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

			cout << "Paises limitrofes para atacar: " << endl << endl;
			cVecinos = vecinos->ListarParaAtacar(nomb);
			if (cVecinos == 0)
			{
				SetConsoleTextAttribute(consoleHandle, FSCTL_GET_INTEGRITY_INFORMATION);
				cout << "***No tiene paises vecinos enemigos***" << endl << endl;
				SetConsoleTextAttribute(consoleHandle, 7);

				system("Pause");
				return("atras");
			}
			
			cout << endl << "si quiere ir para atras presione retroceso <-, de lo contrario pulse cualquier tecla";
			atras = _getch();
			if (atras == '\0')
			atras = _getch();

			if (atras == '\b')
			{
				return("atras");

			}else
			{
				cout << endl << "Pais a Atacar: ";
				cin.clear();
				cin >> opcion;
				if (opcion == 0)getchar();				

				if (opcion - 1 <= vecinos->getCA() && opcion != 0) 
				estado = EPaisParaAtacar;
				
			}
			
					
			system("cls");
			break;

		case EPaisParaAtacar:

			titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

			PaisParaAtacar = vecinos->AtacarVecino(nomb, opcion);

			cout << "Usted eligio atacar al pais: " << PaisParaAtacar->getCodigo() << endl << endl;

			PaisParaAtacar->PrintTropas(); 

			cout << "si desea continuar presione enter, de lo contrario pulse cualquier tecla";
			atras = _getch();
			if (atras == '\0')
			atras = _getch();

			
			if (atras != 13)
			{
				estado = PLimitrofes;
			}
			else
			{
				estado = EdeMiTropas;
			}
			
			system("cls");

			break;

		case EdeMiTropas:

			titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

			cout << "Tropas Disponibles en "<< nombre<<" para Realizar el ataque:" << endl << endl; //mostras las tropas disponibles en el pais con el que atacas
			PrintTropas();

			cout << "Elija la tropa: "; //seleccionar clase con la que atacas
			cin.clear();
			cin >> clase_tuya;

			if (clase_tuya == 0)getchar();

			if (clase_tuya != 0 && clase_tuya <= TropasEnPais->getCA())
			{
				cTropaCaballero * caballero = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(clase_tuya - 1));
				if (caballero != NULL)
				{
					TropaTuya = caballero;
					estado = ETropaEnemiga;
				}
				else
				{
					cTropaArquero * arquero = dynamic_cast<cTropaArquero*>(TropasEnPais->getItem(clase_tuya - 1));
					if (arquero != NULL)
					{
						TropaTuya = arquero;
						estado = ETropaEnemiga;
					}
					else
					{
						cTropaMago * mago = dynamic_cast<cTropaMago*>(TropasEnPais->getItem(clase_tuya - 1));
						if (mago != NULL)
						{
							TropaTuya = mago;//se atacan a todas las tropas falta informar
							estado = MagoContraArquero;
						}
					}
				}
			}
					
			
			system("cls");

			break;
			
		case ETropaEnemiga:

			    titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

				PaisParaAtacar->PrintTropas();

				cout << endl << "Elija la tropa la cual quiere atacar:";
				cin.clear();
				cin >> clase_slc;

				if (clase_slc == 0)getchar();

				if (clase_slc != 0 && clase_slc <= PaisParaAtacar->getCantidadDeTropas())
				{					
					fin = PaisParaAtacar->Atacado(clase_slc - 1, TropaTuya->Ataque(), TropaTuya->getNombre());

					if (TropaTuya->getNombre() == "ARQUERO" && fin == 0)
					{
						if (rand()%5 == 2) //los arqueros realizan un segundo ataque con un aumento del 50%
						{
							SetConsoleTextAttribute(consoleHandle, EVENT_SYSTEM_FOREGROUND);
							cout << endl << "*****Los Arqueros efectuan un segundo ataque potenciado al 50%!!!*****" << endl;
							SetConsoleTextAttribute(consoleHandle, 7);
							fin = PaisParaAtacar->Atacado(clase_slc - 1, 3 * TropaTuya->Ataque()*0.50, TropaTuya->getNombre());
						}
					}

					PaisParaAtacar->ContrataqueDeCaballeros(TropaTuya, clase_slc-1);

					system("pause");
					
					estado = ConquistasteElPais;
				}
				else
				{
					system("cls");
				}

			
						
			break;

			case MagoContraArquero:
				
				if (PaisParaAtacar->getCantTarquro() != 0)
				{
					titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

					fin = PaisParaAtacar->AtacadoPorMagos("ARQUERO", TropaTuya->Ataque());
					
					system("Pause");
					
				}
				else
				{
					system("cls");
				}
						
				estado = MagoContraMago;

				break;

			case MagoContraMago:

				if (PaisParaAtacar->getCantTMago() != 0)
				{
					//titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);
					fin = PaisParaAtacar->AtacadoPorMagos("MAGO", TropaTuya->Ataque());

					system("pause");
				}
				else
				{
					system("cls");
				}		
				

				estado = MagoContraCaballero;

				break;

			case MagoContraCaballero:

				if (PaisParaAtacar->getCantTcaballero() != 0)
				{
					//titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

					fin = PaisParaAtacar->AtacadoPorMagos("CABALLERO", TropaTuya->Ataque());
					
					if (fin == 0)
					{
						for (int i = 0; i < PaisParaAtacar->getCantTcaballero(); i++)
						{
							eliminar = PaisParaAtacar->ContrataqueDeCaballeros(TropaTuya,i); // contraataque de los caballeros
							if (eliminar == 1)
							{
								TropasEnPais->Eliminar(clase_tuya - 1);
								break;
							}
						}

					}

					system("Pause");
				}
				else
				{
					system("cls");
				}				

				estado = ConquistasteElPais;

				break;

			case ConquistasteElPais:
				
				system("cls");
		

				if (fin == 2)// ganaste el pais
				{
					ImprimirMapa();

					//titulo(PaisParaAtacar, estado, nombre, jugador, consoleHandle);

					SetConsoleTextAttribute(consoleHandle, EVENT_SYSTEM_FOREGROUND);
					cout << endl << "******************************************";
					cout << endl << "Enhorabuena, ganaste el pais " << PaisParaAtacar->getCodigo() << endl;
					cout << "******************************************" << endl << endl;
					SetConsoleTextAttribute(consoleHandle, 7);

					cout << "Debes pasarle una tropa:" << endl << endl;
					TropasEnPais->Listar();

					cout << endl << "seleccione la Tropa: ";
					cin.clear();
					cin >> OpcionTropaTuya;
					
					if (OpcionTropaTuya == 0)getchar();

					if (OpcionTropaTuya <= TropasEnPais->getCA())
					{
						PaisParaAtacar->AgregarTropaPais(TropasEnPais->getItem(OpcionTropaTuya - 1));
						TropasEnPais->QuitarenPos(OpcionTropaTuya - 1);

						system("pause");

						return(PaisParaAtacar->getCodigo());
					}
										
				}
				else
				{
					return("0");
				}



			break;

		default:
			break;
		}//termina el switch
		

	} while (i != 0);


	
	

}

int cPais::Atacado(int ntropa, int dano, string claseTAtacante)
{
	int eliminar=1;
	cTropa * tropa = NULL;


		cTropaCaballero *tropaAtacada = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(ntropa));

		if (tropaAtacada != NULL)
		{
			tropa = tropaAtacada;
		}
		else
		{
			cTropaArquero *tropaAtacada = dynamic_cast<cTropaArquero*>(TropasEnPais->getItem(ntropa));

			if (tropaAtacada != NULL)
			{
				tropa = tropaAtacada;
			}
			else
			{
				cTropaMago *tropaAtacada = dynamic_cast<cTropaMago*>(TropasEnPais->getItem(ntropa));

				if (tropaAtacada != NULL)
				{
					tropa = tropaAtacada;
				}
			}

		}


		SetConsoleTextAttribute(consoleHandle, 14);
		cout << endl << "\t--------------------------------------" << endl;
		cout << "\tTropa " << ntropa + 1 << ": ";
		eliminar = tropa->RecibirAtaqueTropa(dano, claseTAtacante);

		if (eliminar == 0)
		{
			TropasEnPais->Eliminar(ntropa);

			if (TropasEnPais->getCA() == 0)
			{
				return (2);
			}

		}
		else
		{
			//se viene el contrataque
			return (0);
		}

		
	
}

int cPais::AtacadoPorMagos(string Natacante, int dano)
{
	int eliminar = 0;
	
		if (Natacante == "ARQUERO")
		{
			for (int i = 0; i < TropasEnPais->getCA(); i++)
			{

				cTropaArquero * tropa = dynamic_cast<cTropaArquero*>(TropasEnPais->getItem(i));
				
				if (tropa != NULL)
				{
					SetConsoleTextAttribute(consoleHandle, 14);
					cout << endl << "\t--------------------------------------" << endl;
					cout << "\tTropa " << 1 + 1 << ": ";

					eliminar = tropa->RecibirAtaqueTropa(dano, "MAGO");

					if (eliminar == 0)
					{
						TropasEnPais->Eliminar(i);

						if (TropasEnPais->getCA() == 0)
						{
							return (2);
						}

					}
					else
					{
						//se viene el contrataque
						return (0);
					}
				}


			}
		}
		else if(Natacante == "MAGO")
		{
			for (int i = 0; i < TropasEnPais->getCA(); i++)
			{
				cTropaMago * tropa = dynamic_cast<cTropaMago*>(TropasEnPais->getItem(i));

				if (tropa != NULL)
				{
					SetConsoleTextAttribute(consoleHandle, 14);
					cout << endl << "\t--------------------------------------" << endl;
					cout << "\tTropa " << i + 1 << ": ";

					eliminar = tropa->RecibirAtaqueTropa(dano, "MAGO");

					if (eliminar == 0)
					{
						TropasEnPais->Eliminar(i);

						if (TropasEnPais->getCA() == 0)
						{
							return (2);
						}

					}
					else
					{
						//se viene el contrataque
						return (0);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < TropasEnPais->getCA(); i++)
			{
				cTropaCaballero * tropa = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(i));

				if (tropa != NULL)
				{
					SetConsoleTextAttribute(consoleHandle, 14);
					cout << endl << "\t--------------------------------------" << endl;
					cout << "\tTropa " << i + 1 << ": ";

					eliminar = tropa->RecibirAtaqueTropa(dano, "MAGO");

					if (eliminar == 0)
					{
						TropasEnPais->Eliminar(i);

						if (TropasEnPais->getCA() == 0)
						{
							return (2);
						}

					}
					else
					{
						//se viene el contrataque
						return (0);
					}
				}
			}
		}	


}

int cPais::ContrataqueDeCaballeros(cTropa * ptr, int Ntropa)
{
	int Eliminar = 0;
	cTropaCaballero * miTropa = NULL;
		 
	 miTropa = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(Ntropa));//busca la tropa de caballeros la cual atacaste
	 if (miTropa != NULL)
	 {
		 SetConsoleTextAttribute(consoleHandle, 14);

		 cout << endl << "\t-----------ContraAtaque---------------" << endl;
		 cout << "\tTu Tropa " << Ntropa + 1 << ": ";
		 Eliminar = ptr->RecibirAtaqueTropa(miTropa->Ataque()+miTropa->Ataque()*0.25, "CABALLERO");

		 if (Eliminar == 0)
		 {
			 return (1); //le mataron las tropas en el contra ataque;
		 }
		 else
		 {
			 return(0);
		 }
	 }
	 else
	 {
		 return(0);
	 }	

}

void cPais::combinarTROPA(cTropa * ptr, int Nt, string clase)
{
	int unidades = 0;
	cTropa * tropaAcombinar = NULL;

	cTropaCaballero * tropaC = dynamic_cast<cTropaCaballero*>(ptr);
	if (tropaC != NULL)
	{
		tropaAcombinar = buscarTROPA(clase, Nt);		
		tropaAcombinar->AgregarUnidades(tropaC->getCUnidades());
	}
	else
	{
		cTropaArquero * tropaA = dynamic_cast<cTropaArquero*>(ptr);
		if (tropaA != NULL)
		{
			tropaAcombinar = buscarTROPA(clase, Nt);
			tropaAcombinar->AgregarUnidades(tropaA->getCUnidades());
		}
		else
		{
			cTropaMago * tropaM = dynamic_cast<cTropaMago*>(ptr);
			if (tropaM != NULL)
			{
				tropaAcombinar = buscarTROPA(clase, Nt);
				tropaAcombinar->AgregarUnidades(tropaM->getCUnidades());				
			}
		}
	}
	delete ptr;
}

int cPais::getCantTcaballero()
{
	int cont = 0, N = 0;

	N = TropasEnPais->getCA();

	for (int i = 0; i < N; i++)
	{
		cTropaCaballero * tropa = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(i));
		if (tropa != NULL)
		{
			cont++;
		}
	}

	return(cont);
}

int cPais::getCantTMago()
{
	int cont = 0, N = 0;

	N = TropasEnPais->getCA();

	for (int i = 0; i < N; i++)
	{
		cTropaMago * tropa = dynamic_cast<cTropaMago*>(TropasEnPais->getItem(i));
		if (tropa != NULL)
		{
			cont++;
		}
	}

	return(cont);
}

int cPais::getCantTarquro()
{
	int cont = 0, N = 0;

	N = TropasEnPais->getCA();

	for (int i = 0; i < N; i++)
	{
		cTropaArquero * tropa = dynamic_cast<cTropaArquero*>(TropasEnPais->getItem(i));
		if (tropa != NULL)
		{
			cont++;
		}
	}

	return(cont);
}

void cPais::PrintA()
{
	cout << nombre<< endl;
	vecinos->ListarV();	
}

void cPais::PrintTropas()
{
	TropasEnPais->Listar();
}

void cPais::printTodos()
{
	listaPaises->Listar();
}

cTropa * cPais::buscarTROPA(string clase, int Num)
{
	int cant = 0, contador = 0;
	cant = TropasEnPais->getCA();

	if (clase == "CABALLERO")
	{
		for (int i = 0; i < cant; i++)
		{
			cTropaCaballero* tropa = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(i));
			if (tropa != NULL)
			{
				if (Num == contador)
				{
					return(tropa);
				}
				contador++;
			}
		}

	}
	else if (clase == "ARQUERO")
	{
		for (int i = 0; i < cant; i++)
		{
			cTropaArquero* tropa = dynamic_cast<cTropaArquero*>(TropasEnPais->getItem(i));
			if (tropa != NULL)
			{
				if (Num == contador)
				{
					return(tropa);
				}
				contador++;
			}
		}
	}
	else
	{
		for (int i = 0; i < cant; i++)
		{
			cTropaMago* tropa = dynamic_cast<cTropaMago*>(TropasEnPais->getItem(i));
			if (tropa != NULL)
			{
				if (Num == contador)
				{
					return(tropa);
				}
				contador++;
			}
		}
	}
}

void cPais::PrintTropasCaballero()
{
	int contador = 1;
	for (int i = 0; i < TropasEnPais->getCA(); i++)
	{
		cTropaCaballero * tropaC = dynamic_cast<cTropaCaballero*>(TropasEnPais->getItem(i));
		if (tropaC != NULL)
		{
			cout << contador++ << ") ";
			tropaC->PrintA();
		}
	}
}

void cPais::PrintTropasArquero()
{
	int contador = 1;
	for (int i = 0; i < TropasEnPais->getCA(); i++)
	{
		cTropaArquero * tropa = dynamic_cast<cTropaArquero*>(TropasEnPais->getItem(i));
		if (tropa != NULL)
		{
			cout << contador++ << ") ";
			tropa->PrintA();
		}
	}
}

void cPais::PrintTropasMago()
{
	int contador = 1;
	for (int i = 0; i < TropasEnPais->getCA(); i++)
	{
		cTropaMago * tropa = dynamic_cast<cTropaMago*>(TropasEnPais->getItem(i));
		if (tropa != NULL)
		{
			cout << contador++ << ") ";
			tropa->PrintA();
		}
	}
}

void cPais::PrintPaisConTropas(void)
{
	cout << nombre << endl;
	PrintTropas();
}

void cPais::ImprimirMapa(void)
{
	cPais * pais = NULL;
	int Npais[16];

	for (int i = 0; i < 16; i++)
	{
		pais = listaPaises->getItem(i);
		Npais[i] = pais->getNjugador();
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

void cPais::PrintNombre()
{
	cout << nombre << endl;
}


void cPais::titulo(cPais * paisParaATACAR, int estado, string nombre, int jugador, HANDLE consoleHandle) {

	SetConsoleTextAttribute(consoleHandle, 7);
	SetConsoleTextAttribute(consoleHandle, 5);
	if (jugador == 1)
	{
		cout << "----------------------------------------------" << endl;
		cout << "    Jugador 1" << " atacando con " << nombre;
		if (estado > 1)
		{
			cout << " a " << paisParaATACAR->getCodigo() << endl;
		}
		else {
			cout << endl;
		}
		cout << "----------------------------------------------" << endl << endl;
	}
	else
	{
		cout << "----------------------------------------------" << endl;
		cout << "    Jugador 2" << " atacando con " << nombre;
		if (estado > 1)
		{
			cout << " a " << paisParaATACAR->getCodigo() << endl;
		}
		else {
			cout << endl;
		}
		cout << "----------------------------------------------" << endl << endl;
	}
	SetConsoleTextAttribute(consoleHandle, 7);


}


cPais::~cPais()
{
	if (vecinos != NULL)
	{
		int n = vecinos->getCA();
		for (int i = 0; i < n; i++)
		{
			vecinos->QuitarenPos(0);
		}
		delete vecinos;
	}


	if (TropasEnPais != NULL)
	{
		delete TropasEnPais;
	}

	if (listaPaises->getCA() == 1)
	{
		listaPaises->Quitar(nombre);
		delete listaPaises;
	}
	else
	{
		if (nombre != "PasarRonda")
		{
			listaPaises->Quitar(nombre);
		}

	}

}
