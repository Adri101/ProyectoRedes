/*
 * Protocolo.cpp
 *
 *  Created on: 15 abr. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "Protocolo.h"

/*
 * Metodo para elegir el rol, o esclavo o maestro
 */
void elegirRole(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalMaestro, ofstream &fSalEsclavo) {
	char opt = -1;
	bool fin = false;

	while (!fin) {
		SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
		printf("Seleccione maestro o esclavo: \n"
				"    1. Maestro \n"
				"    2. Esclavo \n");
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original

		opt = getch();
		if (opt != ESCAPE) {
			printf("%c\n", opt);
		}
		switch (opt) {
		case UNO:
			fSalMaestro.open("Prolog-m.txt");
			if (fSalMaestro.is_open()) {
				fSalMaestro.write("Seleccione maestro o esclavo: \n",
						strlen("Seleccione maestro o esclavo: \n"));
				fSalMaestro.write("    1. Maestro \n",
						strlen("    1. Maestro \n"));
				fSalMaestro.write("    2. Esclavo \n",
						strlen("    2. Esclavo \n"));
				fSalMaestro.put(opt);
				fSalMaestro.write("\n", strlen("\n"));
			}
			EnviarCaracter(PuertoCOM, 'E');
			maestro(PuertoCOM, Pantalla, campo, TDatos, flujo_salida, esFichero,
					finFichero, esAutor, esColor, esNombreFichero, cadAutores,
					cadColor, cadNombreFichero, fSalMaestro);
			fin = true;
			fSalMaestro.close();
			break;
		case DOS:
			fSalEsclavo.open("Prolog-e.txt");
			if (fSalEsclavo.is_open()) {
				fSalEsclavo.write("Seleccione maestro o esclavo: \n",
						strlen("Seleccione maestro o esclavo: \n"));
				fSalEsclavo.write("    1. Maestro \n",
						strlen("    1. Maestro \n"));
				fSalEsclavo.write("    2. Esclavo \n",
						strlen("    2. Esclavo \n"));
				fSalEsclavo.put(opt);
				fSalEsclavo.write("\n", strlen("\n"));
			}
			EnviarCaracter(PuertoCOM, 'M');
			esclavo(PuertoCOM, Pantalla, campo, TDatos, flujo_salida, esFichero,
					finFichero, esAutor, esColor, esNombreFichero, cadAutores,
					cadColor, cadNombreFichero, fSalEsclavo);
			fin = true;
			fSalEsclavo.close();
			break;
		default:
			SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
			printf("Por favor seleccione una de las dos opciones. \n\n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			break;
		}
	}
}

/*
 * Metodo del maestro donde se elige entre Seleccion o Sondeo
 */
void maestro(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalMaestro) {
	char opt = -1;
	bool fin = false;

	while (!fin) {
		SetConsoleTextAttribute(Pantalla, 2);
		printf("Ha seleccionado MAESTRO, seleccione la operacion a realizar: \n"
				"    1. Seleccion \n"
				"    2. Sondeo \n");
		SetConsoleTextAttribute(Pantalla, 7);
		opt = getch();
		if (opt != ESCAPE) {
			printf("%c\n", opt);
		}
		if (fSalMaestro.is_open()) {
			fSalMaestro.write(
					"Ha seleccionado MAESTRO, seleccione la operacion a realizar: \n",
					strlen(
							"Ha seleccionado MAESTRO, seleccione la operacion a realizar: \n"));
			fSalMaestro.write("    1. Seleccion \n",
					strlen("    1. Seleccion \n"));
			fSalMaestro.write("    2. Sondeo \n", strlen("    2. Sondeo \n"));
			fSalMaestro.put(opt);
			fSalMaestro.write("\n", strlen("\n"));
		}
		switch (opt) {
		case UNO:
			SetConsoleTextAttribute(Pantalla, 2);
			printf("Ha seleccionado seleccion. \n");
			SetConsoleTextAttribute(Pantalla, 7);
			if (fSalMaestro.is_open()) {
				fSalMaestro.write("Ha seleccionado seleccion. \n",
						strlen("Ha seleccionado seleccion. \n"));
			}
			maestroSeleccion(PuertoCOM, Pantalla, campo, TDatos, flujo_salida,
					esFichero, finFichero, esAutor, esColor, esNombreFichero,
					cadAutores, cadColor, cadNombreFichero, fSalMaestro);
			fin = true;
			break;
		case DOS:
			SetConsoleTextAttribute(Pantalla, 2);
			printf("Ha seleccionado sondeo. \n");
			SetConsoleTextAttribute(Pantalla, 7);
			if (fSalMaestro.is_open()) {
				fSalMaestro.write("Ha seleccionado sondeo. \n",
						strlen("Ha seleccionado sondeo. \n"));
			}
			maestroSondeo(PuertoCOM, Pantalla, campo, TDatos, flujo_salida,
					esFichero, finFichero, esAutor, esColor, esNombreFichero,
					cadAutores, cadColor, cadNombreFichero, fSalMaestro);
			fin = true;
			break;
		default:
			SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
			printf("Por favor seleccione una de las dos opciones. \n\n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			break;
		}
	}

	printf("Proceso finalizado \n");
	if (fSalMaestro.is_open()) {
		fSalMaestro.write("Proceso finalizado \n",
				strlen("Proceso finalizado \n"));
	}
}

/*
 * Metodo del maestro durante la operacion de Seleccion
 */
void maestroSeleccion(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalMaestro) {

	TramaDatos tDatosAux;
	bool esSeleccion = true;
	bool esSondeo = false;

	//FASE ESTABLECIMIENTO. LOS OTROS PARAMETROS SE ESTABLECEN POR DEFECTO AL CREAR LA TRAMA. EL NUMERO DE TRAMA AL CREARSE POR DEFECTO ES 0, YA QUE EMPIEZA UNA FASE
	tDatosAux.inicializarTramaDatos();
	tDatosAux.setControl(05);
	tDatosAux.setDireccion('R');
	enviarTrama(tDatosAux, PuertoCOM);
	mostrarTrama(tDatosAux, true, false, 1, Pantalla, fSalMaestro);
	//ESPERAR HASTA QUE SE RECIBA UNA ACK
	esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalMaestro);
	mostrarTrama(tDatosAux, false, true, 1, Pantalla, fSalMaestro);

	//FASE TRANSFERENCIA
	enviarFicheroProtocolo(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, esSeleccion, esSondeo,
			fSalMaestro);

	//FASE LIBERACION
	tDatosAux.inicializarTramaDatos();
	tDatosAux.setControl(04);
	tDatosAux.setDireccion('R');
	enviarTrama(tDatosAux, PuertoCOM);
	mostrarTrama(tDatosAux, true, false, 11, Pantalla, fSalMaestro);
	esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalMaestro);
	mostrarTrama(tDatosAux, false, true, 11, Pantalla, fSalMaestro);

	esSeleccion = false;

}

/*
 * Metodo del maestro durante la operacion de Sondeo
 */
void maestroSondeo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalMaestro) {

	unsigned char NTrama = '0';
	TramaDatos tDatosAux;
	int tipo = 0;
	unsigned char BCE;
	int cabecera = 0;
	char color;
	char opt = -1;
	bool fin = false;
	bool errorOpcion = false;

	//FASE ESTABLECIMIENTO. LOS OTROS PARAMETROS SE ESTABLECEN POR DEFECTO AL CREAR LA TRAMA
	tDatosAux.inicializarTramaDatos();
	tDatosAux.setControl(05);
	enviarTrama(tDatosAux, PuertoCOM);
	mostrarTrama(tDatosAux, true, false, 1, Pantalla, fSalMaestro);
	//ESPERAR HASTA QUE SE RECIBA UNA ACK
	esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalMaestro);
	mostrarTrama(tDatosAux, false, true, 1, Pantalla, fSalMaestro);

	while (tipo != 8 && tipo != 2) {
		tipo = recibirTramaProtocolo(PuertoCOM, Pantalla, campo, tDatosAux,
				flujo_salida, esFichero, finFichero, esAutor, esColor,
				esNombreFichero, cadAutores, cadColor, cadNombreFichero,
				fSalMaestro);
	}

	if (tipo != 2) {
		//FASE DE TRANSFERENCIA
		while (tipo != 6) { //CARACTER } : FIN DE FICHERO
			while (tipo != 6 && tipo != 5 && tipo != 7) {
				tipo = recibirTramaProtocolo(PuertoCOM, Pantalla, campo,
						tDatosAux, flujo_salida, esFichero, finFichero, esAutor,
						esColor, esNombreFichero, cadAutores, cadColor,
						cadNombreFichero, fSalMaestro);
			}
			if (tipo != 6) {
				if (cabecera < 3) {
					color = 12;
				} else {
					color = 2;
				}
				mostrarTrama(tDatosAux, false, true, color, Pantalla,
						fSalMaestro);
				NTrama = tDatosAux.getNTrama();
				tDatosAux.inicializarTramaDatos();
				tDatosAux.setControl(06);
				tDatosAux.setNTrama(NTrama);
				calcularBCE(tDatosAux, BCE);
				if (tipo == 7) {
					tDatosAux.setControl(21);
				}
				enviarTrama(tDatosAux, PuertoCOM);
				mostrarTrama(tDatosAux, true, false, color, Pantalla,
						fSalMaestro);
				tipo = 0;
				cabecera++;
			}
		}

		//TAMANHO FICHERO
		esperarTramaDatos(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
				esFichero, finFichero, esAutor, esColor, esNombreFichero,
				cadAutores, cadColor, cadNombreFichero, fSalMaestro);
		mostrarTrama(tDatosAux, false, true, 8, Pantalla, fSalMaestro);

		NTrama = tDatosAux.getNTrama();
		tDatosAux.inicializarTramaDatos();
		tDatosAux.setControl(06);
		tDatosAux.setNTrama(NTrama);
		enviarTrama(tDatosAux, PuertoCOM);
		mostrarTrama(tDatosAux, true, false, 8, Pantalla, fSalMaestro);
	}

	//FASE LIBERACION
	while (!fin) {
		if (tipo != 2) { // Comprobar que no se ha procesado ya la trama de liberacion
			while (tipo != 2) { //EOT
				tipo = recibirTramaProtocolo(PuertoCOM, Pantalla, campo,
						tDatosAux, flujo_salida, esFichero, finFichero, esAutor,
						esColor, esNombreFichero, cadAutores, cadColor,
						cadNombreFichero, fSalMaestro);
			}
		}
		mostrarTrama(tDatosAux, false, true, 11, Pantalla, fSalMaestro);
		while (!errorOpcion) {
			SetConsoleTextAttribute(Pantalla, 2);	//Fondo negro, texto rojo
			printf("Desea el cierre de la comunicacion \n"
					"1. Si \n"
					"2. No \n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			opt = getch();
			if (opt != ESCAPE) {
				printf("%c\n", opt);
			}
			if (fSalMaestro.is_open()) {
				fSalMaestro.write("Desea el cierre de la comunicacion \n",
						strlen("Desea el cierre de la comunicacion \n"));
				fSalMaestro.write("1. Si \n", strlen("1. Si \n"));
				fSalMaestro.write("2. No \n", strlen("2. No \n"));
				fSalMaestro.put(opt);
				fSalMaestro.write("\n", strlen("\n"));
			}
			switch (opt) {
			case UNO:
				NTrama = tDatosAux.getNTrama();
				tDatosAux.inicializarTramaDatos();
				tDatosAux.setControl(06);
				tDatosAux.setNTrama(NTrama);
				enviarTrama(tDatosAux, PuertoCOM);
				mostrarTrama(tDatosAux, true, false, 11, Pantalla, fSalMaestro);
				fin = true;
				errorOpcion = true;
				break;
			case DOS:
				NTrama = tDatosAux.getNTrama();
				tDatosAux.inicializarTramaDatos();
				tDatosAux.setControl(21);
				tDatosAux.setNTrama(NTrama);
				enviarTrama(tDatosAux, PuertoCOM);
				mostrarTrama(tDatosAux, true, false, 11, Pantalla, fSalMaestro);
				errorOpcion = true;
				break;
			default:
				SetConsoleTextAttribute(Pantalla, 12);//Fondo negro, texto rojo
				printf("Por favor seleccione una de las dos opciones. \n\n");
				SetConsoleTextAttribute(Pantalla, 7);//Vuelta al color original

				if (fSalMaestro.is_open()) {
					fSalMaestro.write(
							"Por favor seleccione una de las dos opciones. \n\n",
							strlen(
									"Por favor seleccione una de las dos opciones. \n\n"));
				}
				break;
			}
		}
		errorOpcion = false;
		tipo = 0;
	}

}
/*
 * Metodo del esclavo donde se elige entre Seleccion o Sondeo
 */
void esclavo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalEsclavo) {

	unsigned char NTrama = '0';
	SetConsoleTextAttribute(Pantalla, 2);
	printf("Ha seleccionado ESCLAVO. \n");
	SetConsoleTextAttribute(Pantalla, 7);
	if (fSalEsclavo.is_open()) {
		fSalEsclavo.write("Ha seleccionado ESCLAVO. \n",
				strlen("Ha seleccionado ESCLAVO. \n"));
	}

	TramaDatos tDatosAux;
	//ESPERAR UNA ENQ DEL ESTABLECIMIENTO
	esperarLLamada(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, fSalEsclavo);
	mostrarTrama(tDatosAux, false, true, 1, Pantalla, fSalEsclavo);
	NTrama = tDatosAux.getNTrama();

	if (tDatosAux.getDireccion() == 'R') {

		//ENVIO DE TRAMA ACK EN EL ESTABLECIMIENTO
		tDatosAux.inicializarTramaDatos();
		tDatosAux.setControl(06);
		tDatosAux.setDireccion('R');
		tDatosAux.setNTrama(NTrama);
		enviarTrama(tDatosAux, PuertoCOM);
		mostrarTrama(tDatosAux, true, false, 1, Pantalla, fSalEsclavo);

		esclavoSeleccion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
				esFichero, finFichero, esAutor, esColor, esNombreFichero,
				cadAutores, cadColor, cadNombreFichero, fSalEsclavo);
	} else {
		if (tDatosAux.getDireccion() == 'T') {

			//ENVIO DE TRAMA ACK EN EL ESTABLECIMIENTO
			tDatosAux.inicializarTramaDatos();
			tDatosAux.setControl(06);
			tDatosAux.setNTrama(NTrama);
			enviarTrama(tDatosAux, PuertoCOM);
			mostrarTrama(tDatosAux, true, false, 1, Pantalla, fSalEsclavo);

			esclavoSondeo(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
					esFichero, finFichero, esAutor, esColor, esNombreFichero,
					cadAutores, cadColor, cadNombreFichero, fSalEsclavo);
		}
	}

	printf("Proceso finalizado \n");
	if (fSalEsclavo.is_open()) {
		fSalEsclavo.write("Proceso finalizado \n",
				strlen("Proceso finalizado \n"));
	}
}

/*
 * Metodo del esclavo durante la operacion de Seleccion
 */
void esclavoSeleccion(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalEsclavo) {

	unsigned char NTrama = '0';
	unsigned char direccion = 'T';
	TramaDatos tDatosAux;
	int tipo = 0;
	unsigned char BCE;
	int cabecera = 0;
	char color;

	while (tipo != 8 && tipo != 2) { //tipo 8: caracter {; tipo 2: trama de liberacion, esto indica que no existe el fichero
		tipo = recibirTramaProtocolo(PuertoCOM, Pantalla, campo, tDatosAux,
				flujo_salida, esFichero, finFichero, esAutor, esColor,
				esNombreFichero, cadAutores, cadColor, cadNombreFichero,
				fSalEsclavo);
	}

	if (tipo != 2) {
		//FASE DE TRANSFERENCIA
		while (tipo != 6) { //CARACTER } : FIN DE FICHERO
			while (tipo != 6 && tipo != 5 && tipo != 7) {
				tipo = recibirTramaProtocolo(PuertoCOM, Pantalla, campo,
						tDatosAux, flujo_salida, esFichero, finFichero, esAutor,
						esColor, esNombreFichero, cadAutores, cadColor,
						cadNombreFichero, fSalEsclavo);
			}
			if (tipo != 6) {
				if (cabecera < 3) {
					color = 12;
				} else {
					color = 2;
				}
				mostrarTrama(tDatosAux, false, true, color, Pantalla,
						fSalEsclavo);
				NTrama = tDatosAux.getNTrama();
				direccion = tDatosAux.getDireccion();
				tDatosAux.inicializarTramaDatos();
				tDatosAux.setControl(06);
				tDatosAux.setDireccion(direccion);
				tDatosAux.setNTrama(NTrama);
				calcularBCE(tDatosAux, BCE);
				if (tipo == 7) {
					tDatosAux.setControl(21);
				}
				enviarTrama(tDatosAux, PuertoCOM);
				mostrarTrama(tDatosAux, true, false, color, Pantalla,
						fSalEsclavo);
				tipo = 0;
				cabecera++;
			}
		}

		//TAMANHO FICHERO
		esperarTramaDatos(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
				esFichero, finFichero, esAutor, esColor, esNombreFichero,
				cadAutores, cadColor, cadNombreFichero, fSalEsclavo);
		mostrarTrama(tDatosAux, false, true, 8, Pantalla, fSalEsclavo);

		NTrama = tDatosAux.getNTrama();
		direccion = tDatosAux.getDireccion();
		tDatosAux.inicializarTramaDatos();
		tDatosAux.setControl(06);
		tDatosAux.setDireccion(direccion);
		tDatosAux.setNTrama(NTrama);
		enviarTrama(tDatosAux, PuertoCOM);
		mostrarTrama(tDatosAux, true, false, 8, Pantalla, fSalEsclavo);
	}
	//FASE LIBERACION
	if (tipo != 2) { //Comprobar que no se ha procesado antes la trama de liberacion
		while (tipo != 2) { //EOT
			tipo = recibirTramaProtocolo(PuertoCOM, Pantalla, campo, tDatosAux,
					flujo_salida, esFichero, finFichero, esAutor, esColor,
					esNombreFichero, cadAutores, cadColor, cadNombreFichero,
					fSalEsclavo);
		}
	}
	mostrarTrama(tDatosAux, false, true, 11, Pantalla, fSalEsclavo);
	NTrama = tDatosAux.getNTrama();
	direccion = tDatosAux.getDireccion();
	tDatosAux.inicializarTramaDatos();
	tDatosAux.setControl(06);
	tDatosAux.setDireccion(direccion);
	tDatosAux.setNTrama(NTrama);
	enviarTrama(tDatosAux, PuertoCOM);
	mostrarTrama(tDatosAux, true, false, 11, Pantalla, fSalEsclavo);

}

/*
 * Metodo del esclavo durante la operacion de Sondeo
 */
void esclavoSondeo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &fSalEsclavo) {

	TramaDatos tDatosAux;
	unsigned char NTrama = '0';
	bool esSeleccion = false;
	bool esSondeo = true;
	bool fin = false;

	//FASE TRANSFERENCIA
	enviarFicheroProtocolo(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
			esFichero, finFichero, esAutor, esColor, esNombreFichero,
			cadAutores, cadColor, cadNombreFichero, esSeleccion, esSondeo,
			fSalEsclavo);

	//FASE LIBERACION
	NTrama = '0';
	while (!fin) {
		tDatosAux.inicializarTramaDatos();
		tDatosAux.setControl(04);
		tDatosAux.setNTrama(NTrama);
		enviarTrama(tDatosAux, PuertoCOM);
		mostrarTrama(tDatosAux, true, false, 11, Pantalla, fSalEsclavo);
		esperarConfirmacion(PuertoCOM, Pantalla, campo, tDatosAux, flujo_salida,
				esFichero, finFichero, esAutor, esColor, esNombreFichero,
				cadAutores, cadColor, cadNombreFichero, fSalEsclavo);
		mostrarTrama(tDatosAux, false, true, 11, Pantalla, fSalEsclavo);
		if (tDatosAux.getControl() == ACK) {
			fin = true;
		}
		if (NTrama == '0') {
			NTrama = '1';
		} else {
			NTrama = '0';
		}
	}
	esSondeo = false;

}
/*
 * Esperar confirmacion con un ACK en el recibir
 */
void esperarConfirmacion(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &flujo_log) {

	int llamada = 0;
	while (llamada != 3 && llamada != 4) { //ACK o NACK
		llamada = recibirTramaProtocolo(PuertoCOM, Pantalla, campo, TDatos,
				flujo_salida, esFichero, finFichero, esAutor, esColor,
				esNombreFichero, cadAutores, cadColor, cadNombreFichero,
				flujo_log);
	}
}

/*
 * Esperar llamada con un ENQ en el recibir
 */
void esperarLLamada(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &flujo_log) {

	int llamada = 0;
	while (llamada != 1) { //ENQ
		llamada = recibirTramaProtocolo(PuertoCOM, Pantalla, campo, TDatos,
				flujo_salida, esFichero, finFichero, esAutor, esColor,
				esNombreFichero, cadAutores, cadColor, cadNombreFichero,
				flujo_log);
	}
}

/*
 * Esperar trama de datos con una STX en el recibir
 */
void esperarTramaDatos(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &flujo_log) {

	int llamada = 0;
	while (llamada != 5) { //STX
		llamada = recibirTramaProtocolo(PuertoCOM, Pantalla, campo, TDatos,
				flujo_salida, esFichero, finFichero, esAutor, esColor,
				esNombreFichero, cadAutores, cadColor, cadNombreFichero,
				flujo_log);
	}

}

/*
 * Recibir para las tramas del protocolo que devolvera un entero al procesar la trama que se recibe
 * ENQ=1;EOT=2;ACK=3;NACK=4;STX=5;FIN FICHERO=6;ERROR BCE=7;INICIO FICHERO=8
 */
int recibirTramaProtocolo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,
		TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,
		bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,
		char cadAutores[], char cadColor[], char cadNombreFichero[],
		ofstream &flujo_logME) {
	bool fichero = true;
	int tipoTrama = 0; //ENQ=1;EOT=2;ACK=3;NACK=4;STX=5;FIN FICHERO=6;ERROR BCE = 7
	char car;
	car = RecibirCaracter(PuertoCOM);
	if (car != 0) {
		switch (campo) {
		case 1:
			if (car == 22) { //si es 22 querra decir que vamos a recibir una trama
				TDatos.setSincronismo(car);
				campo++;
			} else {
				if (car == '{') {
					esFichero = true;
					esAutor = true;
					esColor = true;
					esNombreFichero = true;
					tipoTrama = 8;
				} else {
					if (car == '}') {
						if (flujo_logME.is_open()) {
							flujo_logME.write("Fichero recibido \n",
									strlen("Fichero recibido \n"));
						}
						SetConsoleTextAttribute(Pantalla, atoi(cadColor));
						printf("Fichero recibido \n");
						SetConsoleTextAttribute(Pantalla, 7);
						esFichero = false;
						finFichero = true;
						flujo_salida.close();
						tipoTrama = 6;
					}
				}
			}
			break;
		case 2:
			TDatos.setDireccion(car);
			campo++;
			break;
		case 3:
			TDatos.setControl(car);
			campo++;
			break;
		case 4:
			TDatos.setNTrama(car);
			if (TDatos.getControl() != STX) {
				TramaControl TControl;
				TControl.setSincronismo(TDatos.getSincronismo());
				TControl.setDireccion(TDatos.getDireccion());
				TControl.setControl(TDatos.getControl());
				TControl.setNumeroTrama(TDatos.getNTrama());
				if (TControl.getControl() == ENQ) {
					tipoTrama = 1;
				} else {
					if (TControl.getControl() == EOT) {
						tipoTrama = 2;
					} else {
						if (TControl.getControl() == ACK) {
							tipoTrama = 3;
						} else {
							if (TControl.getControl() == NACK) {
								tipoTrama = 4;
							}
						}
					}
				}
				//Reiniciar el campo control de la trama de datos
				//TDatos.setControl(02);
				campo = 1;
			} else {
				campo++;
			}
			break;
		case 5:
			TDatos.setLong(car);
			campo++;
		case 6:
			RecibirCadena(PuertoCOM, TDatos.getDatos(), TDatos.getLong());
			TDatos.getDatos()[TDatos.getLong()] = '\0';
			campo++;
			break;
		case 7:
			TDatos.setBce(car);
			unsigned char BCE;
			calcularBCE(TDatos, BCE);
			if (BCE == TDatos.getBce()) {
				if (esFichero) {
					tipoTrama = 5;
					procesarFichero(cadAutores, cadColor, cadNombreFichero,
							TDatos, Pantalla, flujo_salida, esAutor, esColor,
							esNombreFichero, fichero, flujo_logME);
				} else {
					if (finFichero) {
						tipoTrama = 5;
						if (flujo_logME.is_open()) {
							flujo_logME.write(
									"El fichero recibido tiene un tamanho de ",
									strlen(
											"El fichero recibido tiene un tamanho de "));
							flujo_logME.write(TDatos.getDatos(),
									strlen(TDatos.getDatos()));
							flujo_logME.write(" bytes.\n", strlen(" bytes.\n"));
						}
						SetConsoleTextAttribute(Pantalla, atoi(cadColor));
						printf(
								"El fichero recibido tiene un tamanho de %s bytes.\n",
								TDatos.getDatos());
						SetConsoleTextAttribute(Pantalla, 7);
						finFichero = false;
					} else {
						if (flujo_logME.is_open()) {
							flujo_logME.write(TDatos.getDatos(),
									strlen(TDatos.getDatos()));
						}
						SetConsoleTextAttribute(Pantalla, 2); //Fondo negro, texto verde
						printf("%s", TDatos.getDatos());
						SetConsoleTextAttribute(Pantalla, 7); //Vuelta al color original
					}
				}

			} else {
				tipoTrama = 7;
			}
			campo = 1;
			break;
		}
	}
	return tipoTrama;
}
