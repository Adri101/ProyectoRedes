/*
 * EnviarFicheroDatos.cpp
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "EnviarFicheroDatos.h"
/*
 * Metodo para enviar un fichero de datos
 */
void enviarFicheroDatos(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		ofstream &flujo_sal, bool &esFichero, bool &finFichero, bool &esAutor,
		bool &esColor, bool &esNombreFichero, char cadAutores[],
		char cadColor[], char cadNombreFichero[], bool &ficheroLog,
		ofstream &flujo_log, bool &esF1) {
	TramaDatos TDatos;
	ifstream flujoEnt;
	flujoEnt.open("fichero-e.txt", ios::in);
	ofstream f1, f2;

	char cadCuerpoFichero[255];

	int longitud;
	int contador = 0;
	bool escape = false;
	char car; //Caracter leido

	if (flujoEnt.is_open()) {
		EnviarCaracter(PuertoCOM, '{');
		leerCabecera(PuertoCOM, flujoEnt, ficheroLog, flujo_log, esF1);

		//Leyendo el cuerpo del fichero
		while (!flujoEnt.eof() && !escape) {
			if (kbhit()) {
				car = getch();
				if (car == 27)
					escape = true;
			}
			flujoEnt.read(cadCuerpoFichero, 254);
			if (flujoEnt.gcount() != 0) {
				cadCuerpoFichero[flujoEnt.gcount()] = '\0';
				longitud = strlen(cadCuerpoFichero);
				contador = contador + longitud;
				enviarTramaDatos(PuertoCOM, cadCuerpoFichero, ficheroLog,
						flujo_log, esF1);
				recibirTramas(PuertoCOM, Pantalla, campo, TDatos, flujo_sal,
						esFichero, finFichero, esAutor, esColor,
						esNombreFichero, cadAutores, cadColor, cadNombreFichero,
						ficheroLog, flujo_log, f1, f2);
			}
		}
		flujoEnt.close();
		EnviarCaracter(PuertoCOM, '}');

		//Enviar numero caracteres
		enviarNumCaracteres(contador, PuertoCOM, ficheroLog, flujo_log, esF1);

		if (ficheroLog) {
			if (flujo_log.is_open()) {
				flujo_log.write("Fichero enviado \n",
						strlen("Fichero enviado \n"));
			}
		}
		printf("Fichero enviado \n");

	} else {
		if (ficheroLog) {
			if (flujo_log.is_open()) {
				flujo_log.write("ERROR: El fichero fichero-e.txt no existe \n",
						strlen("ERROR: El fichero fichero-e.txt no existe \n"));
			}
		}
		printf("ERROR: El fichero fichero-e.txt no existe \n");
	}
}

void enviarFicheroProtocolo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		bool &esSeleccion, bool &esSondeo, ofstream &fSalMaestroEsclavo) {

	char car; //Caracter leido
	char primero; //Primer caracter de la trama de datos
	bool escape = false;
	bool error = false;
	int longitud;
	int contador = 0;
	unsigned char NTrama = '0';
	TramaDatos tDatosAux;
	bool esNACK = false;

	ifstream flujoEnt;
	char cadCuerpoFichero[255];
	char cadNCaracteres[10];

	flujoEnt.open("EProtoc.txt", ios::in);

	if (flujoEnt.is_open()) {
		EnviarCaracter(PuertoCOM, '{');
		leerCabeceraProtocolo(PuertoCOM, Pantalla, campo, tDatosAux,
				flujo_salida, esFichero, finFichero, esAutor, esColor,
				esNombreFichero, cadAutores, cadColor, cadNombreFichero, NTrama,
				flujoEnt, esSeleccion, esSondeo, fSalMaestroEsclavo, error,
				escape);
		if (NTrama == '0') {
			NTrama = '1';
		} else {
			NTrama = '0';
		}
		//Leyendo el cuerpo del fichero
		while (!flujoEnt.eof() && !escape) {
			if (!esNACK) {
				if (kbhit()) {
					car = getch();
					if (car == FUNCION) {
						car = getch();
						if (car == F7) {
							error = true;
						}
					}
					if (car == ESCAPE)
						escape = true;
				}
			}
			if (!esNACK) { //Comprobamos que no ha recibido una NACK, debido a algun error en la trama. Si es una NACK no se lee
				flujoEnt.read(cadCuerpoFichero, 254);
			}
			if (flujoEnt.gcount() != 0) {
				if (error) { //Guardamos el primer caracter
					primero = cadCuerpoFichero[0];
				} else {
					if (esNACK) {
						cadCuerpoFichero[0] = primero;
					}
				}
				if (!esNACK) { //Comprobamos que no ha recibido una NACK, debido a algun error en la trama. Si es una NACK no se incrementa el contador de bytes
					cadCuerpoFichero[flujoEnt.gcount()] = '\0';
					longitud = strlen(cadCuerpoFichero);
					contador = contador + longitud;
				}
				tDatosAux.inicializarTramaDatos();
				if (esSeleccion) {
					tDatosAux.setDireccion('R');
				} else {
					if (esSondeo) {
						tDatosAux.setDireccion('T');
					}
				}
				tDatosAux.setNTrama(NTrama);
				enviarTramaProtocolo(PuertoCOM, cadCuerpoFichero, tDatosAux,
						error);
				mostrarTrama(tDatosAux, true, false, 2, Pantalla,
						fSalMaestroEsclavo);
				//Esperar la confirmacion
				esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux,
						flujo_salida, esFichero, finFichero, esAutor, esColor,
						esNombreFichero, cadAutores, cadColor, cadNombreFichero,
						fSalMaestroEsclavo);
				mostrarTrama(tDatosAux, false, false, 2, Pantalla,
						fSalMaestroEsclavo);

				esNACK = false;
				if (tDatosAux.getControl() == NACK) {
					esNACK = true;
				}

				if (!esNACK) {
					if (NTrama == '0') {
						NTrama = '1';
					} else {
						NTrama = '0';
					}
				}

			}

		}
		flujoEnt.close();
		EnviarCaracter(PuertoCOM, '}');
		printf("Fichero enviado\n");
		if (fSalMaestroEsclavo.is_open()) {
			fSalMaestroEsclavo.write("Fichero enviado\n",
					strlen("Fichero enviado\n"));
		}

		//Enviando numero de caracteres
		tDatosAux.inicializarTramaDatos();
		if (esSeleccion) {
			tDatosAux.setDireccion('R');
		} else {
			if (esSondeo) {
				tDatosAux.setDireccion('T');
			}
		}
		tDatosAux.setNTrama(NTrama);
		sprintf(cadNCaracteres, "%d", contador);
		enviarTramaProtocolo(PuertoCOM, cadNCaracteres, tDatosAux, error);
		mostrarTrama(tDatosAux, true, false, 8, Pantalla, fSalMaestroEsclavo);

		//Esperar la confirmacion
		esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
				esFichero, finFichero, esAutor, esColor, esNombreFichero,
				cadAutores, cadColor, cadNombreFichero, fSalMaestroEsclavo);
		mostrarTrama(tDatosAux, false, false, 8, Pantalla, fSalMaestroEsclavo);

	}
}

/*
 * Metodo para enviar el numero de caracteres del cuerpo del fichero
 */
void enviarNumCaracteres(int &contador, HANDLE &PuertoCOM, bool &ficheroLog,
		ofstream &flujo_log, bool &esF1) {

	char cadAux[10];

	//Enviando numero de caracteres
	sprintf(cadAux, "%d", contador);
	enviarTramaDatos(PuertoCOM, cadAux, ficheroLog, flujo_log, esF1);
}

