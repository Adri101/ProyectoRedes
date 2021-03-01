/*
 * RecibirFicheroDatos.cpp
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "RecibirFicheroDatos.h"

/*
 * Metodo para procesar el fichero
 */
void procesarFichero(char cadAutores[], char cadColor[],
		char cadNombreFichero[], TramaDatos &TDatos, HANDLE &Pantalla,
		ofstream &flujo_salida, bool &esAutor, bool &esColor,
		bool &esNombreFichero, bool &ficheroLog, ofstream &flujo_log) {
	if (esAutor) { //PRIMERA LINEA DE LA CABECERA
		strcpy(cadAutores, TDatos.getDatos());
		esAutor = false;
	} else {
		if (esColor) { //SEGUNDA LINEA DE LA CABECERA
			strcpy(cadColor, TDatos.getDatos());
			esColor = false;
		} else {
			if (esNombreFichero) { //TERCERA LINEA DE LA CABECERA
				strcpy(cadNombreFichero, TDatos.getDatos());
				esNombreFichero = false;
			} else {
				if (!esAutor && !esColor && !esNombreFichero
						&& !flujo_salida.is_open()) {
					SetConsoleTextAttribute(Pantalla, atoi(cadColor));
					printf("Recibiendo fichero por %s \n", cadAutores);
					SetConsoleTextAttribute(Pantalla, 7);
					if (ficheroLog) {
						if (flujo_log.is_open()) {
							flujo_log.write("Recibiendo fichero por ",
									strlen("Recibiendo fichero por "));
							flujo_log.write(cadAutores, strlen(cadAutores));
							flujo_log.write("\n", strlen("\n"));
						}
					}
					flujo_salida.open(cadNombreFichero, ios::out);
				} //CUERPO DEL FICHERO
				if (flujo_salida.is_open()) {
					flujo_salida.write(TDatos.getDatos(), TDatos.getLong());
				} else {
					if (ficheroLog) {
						if (flujo_log.is_open()) {
							flujo_log.write("Error al abrir el fichero ",
									strlen("Error al abrir el fichero "));
							flujo_log.write(cadNombreFichero,
									strlen(cadNombreFichero));
							flujo_log.write("\n", strlen("\n"));
						}
					}
					printf("Error al abrir el fichero %s \n", cadNombreFichero);
				}

			}
		}
	}
}

/*
 * Metodo para leer la cabecera del fichero
 */
void leerCabecera(HANDLE &PuertoCOM, ifstream &flujoEnt, bool &ficheroLog,
		ofstream &flujo_log, bool &esFichero) {
	char cadAutores[70];
	char cadColor[5];
	char cadNombreFichero[50];

	//Extreyendo los nombres
	flujoEnt.getline(cadAutores, 70);
	enviarTramaDatos(PuertoCOM, cadAutores, ficheroLog, flujo_log, esFichero);
	if (ficheroLog) {
		if (flujo_log.is_open()) {
			flujo_log.write("Enviando fichero por ",
					strlen("Enviando fichero por "));
			flujo_log.write(cadAutores, strlen(cadAutores));
			flujo_log.write("\n", strlen("\n"));
		}
	}
	printf("Enviando fichero por %s\n", cadAutores);

	//Extreyendo el color
	flujoEnt.getline(cadColor, 5);
	enviarTramaDatos(PuertoCOM, cadColor, ficheroLog, flujo_log, esFichero);

	//Extrayendo el nombre del fichero
	flujoEnt.getline(cadNombreFichero, 50);
	enviarTramaDatos(PuertoCOM, cadNombreFichero, ficheroLog, flujo_log,
			esFichero);

}

void leerCabeceraProtocolo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		unsigned char &NTrama, ifstream &flujoEnt, bool &esSeleccion, bool &esSondeo,
		ofstream &fSalMaestroEsclavo, bool &error, bool &escape) {

	char car;
	TramaDatos tDatosAux;
	NTrama = '0';
	tDatosAux.inicializarTramaDatos();
	if (esSeleccion) {
		tDatosAux.setDireccion('R');
	} else {
		if (esSondeo) {
			tDatosAux.setDireccion('T');
		}
	}
	tDatosAux.setNTrama(NTrama);

	//Comprobar si se ha pulsado el ESCAPE o el F7. Antes de leer la cabecera
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

	//Lee la primera linea de la cabecera
	flujoEnt.getline(cadAutores, 255);
	enviarTramaProtocolo(PuertoCOM, cadAutores, tDatosAux, error);
	mostrarTrama(tDatosAux, true, false, 12, Pantalla, fSalMaestroEsclavo);
	//Espera confirmacion
	esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalMaestroEsclavo);
	mostrarTrama(tDatosAux, false, false, 12, Pantalla, fSalMaestroEsclavo);

	//Comprobar si se ha pulsado el ESCAPE o el F7. Despues de leer la primera linea
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

	//Lee la segunda linea de la cabecera
	NTrama = '1';
	tDatosAux.inicializarTramaDatos();
	if (esSeleccion) {
		tDatosAux.setDireccion('R');
	} else {
		if (esSondeo) {
			tDatosAux.setDireccion('T');
		}
	}
	tDatosAux.setNTrama(NTrama);
	flujoEnt.getline(cadColor, 255);
	enviarTramaProtocolo(PuertoCOM, cadColor, tDatosAux, error);
	mostrarTrama(tDatosAux, true, false, 12, Pantalla, fSalMaestroEsclavo);
	//Espera confirmacion
	esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalMaestroEsclavo);
	mostrarTrama(tDatosAux, false, false, 12, Pantalla, fSalMaestroEsclavo);

	//Comprobar si se ha pulsado el ESCAPE o el F7. Despues de leer la segunda linea
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

	//Lee la tercera linea de la cabecera
	NTrama = '0';
	tDatosAux.inicializarTramaDatos();
	if (esSeleccion) {
		tDatosAux.setDireccion('R');
	} else {
		if (esSondeo) {
			tDatosAux.setDireccion('T');
		}
	}
	tDatosAux.setNTrama(NTrama);
	flujoEnt.getline(cadNombreFichero, 255);
	enviarTramaProtocolo(PuertoCOM, cadNombreFichero, tDatosAux, error);
	mostrarTrama(tDatosAux, true, false, 12, Pantalla, fSalMaestroEsclavo);
	//Espera confirmacion
	esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalMaestroEsclavo);
	mostrarTrama(tDatosAux, false, false, 12, Pantalla, fSalMaestroEsclavo);

	//Comprobar si se ha pulsado el ESCAPE o el F7. Despues de leer la tercera linea
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

	printf("Enviando fichero por %s\n", cadAutores);
	if (fSalMaestroEsclavo.is_open()) {
		fSalMaestroEsclavo.write("Enviando fichero por ",
				strlen("Enviando fichero por "));
		fSalMaestroEsclavo.write(cadAutores, strlen(cadAutores));
		fSalMaestroEsclavo.write("\n", strlen("\n"));
	}
}
