//============================================================================
// ----------- PRÁCTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2019/20 --------------------------------
// ----------------------------- main.CPP ---------------------------------
//============================================================================

/*
 * Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * Grupo: 1
 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "PuertoSerie.h"
#include "TramaControl.h"
#include "TramaDatos.h"
#include "Constantes.h"
#include "RecibirTrama.h"

using namespace std;

//Variables
HANDLE PuertoCOM;
HANDLE Pantalla = GetStdHandle(STD_OUTPUT_HANDLE); //Manejador para controlar el color

/*
 * Selecciona el puerto por donde se quiere realizar la comunicacion
 * Existe un parametro de entrada/salida que hace referencia al puerto
 */
void seleccionarPuerto(char (&PSerie)[5], int &salir) {
	salir = 0; //Entero que indica si el usuario desea salir o no. Si quiere salir esta variable tomara el valor 1
	char opt = -1;		//Char que representa la opcion elegida por el usuario
	boolean fin = false;//Booleano que representa la condicion del bucle. Este finalizará si se ha elegido una de las opciones

	while (!fin) {

		printf("Seleccionar el puerto a utilizar: \n"
				"1. COM1 \n"
				"2. COM2 \n"
				"3. COM3 \n"
				"4. COM4 \n"
				"<ESC> Finalizar\n");

		opt = getch();
		if (opt != ESCAPE) {
			printf("%c\n", opt);
		}
		switch (opt) {
		case UNO:
			strcpy(PSerie, "COM1");
			fin = true;
			break;
		case DOS:
			strcpy(PSerie, "COM2");
			fin = true;
			break;
		case TRES:
			strcpy(PSerie, "COM3");
			fin = true;
			break;
		case CUATRO:
			strcpy(PSerie, "COM4");
			fin = true;
			break;
		case ESCAPE:
			fin = true;
			salir = 1;
			break;
		default:
			SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
			printf("Por favor seleccione una de las cuatro opciones. \n\n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			break;
		}
	}

}

/*
 * Selecciona la velocidad de transmision de la comunicacion
 * Existe un parametro de entrada/salida que hace referencia a la velocidad de transmision
 */
void seleccionarVelocidad(int &velTransmision, int &salir) {
	salir = 0;//Entero que indica si el usuario desea salir o no. Si quiere salir esta variable tomara el valor 1
	char opt = -1;		//Char que representa la opcion elegida por el usuario
	boolean fin = false;//Booleano que representa la condicion del bucle. Este finalizará si se ha elegido una de las opciones

	while (!fin) {

		printf("Seleccionar la velocidad de transmision: \n"
				"1. 1200 \n"
				"2. 2400 \n"
				"3. 4800 \n"
				"4. 9600 \n"
				"5. 19200 \n"
				"<ESC> Finalizar\n");

		opt = getch();
		if (opt != ESCAPE) {
			printf("%c\n", opt);
		}
		switch (opt) {
		case UNO:
			velTransmision = 1200;
			fin = true;
			break;
		case DOS:
			velTransmision = 2400;
			fin = true;
			break;
		case TRES:
			velTransmision = 4800;
			fin = true;
			break;
		case CUATRO:
			velTransmision = 9600;
			fin = true;
			break;
		case CINCO:
			velTransmision = 19200;
			fin = true;
			break;
		case ESCAPE:
			fin = true;
			salir = 1;
			break;
		default:
			SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
			printf("Por favor seleccione una de las cinco opciones. \n\n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			break;
		}
	}
}

/*
 * Programa principal
 */
int main() {
	int salirPuerto = 0; //Variable para controlar la pulsacion del escape en la eleccion del puerto
	int salirVelocidad = 0;	//Variable para controlar la pulsacion del escape en la eleccion de la velocidad
	int salirTrama = 0;	//Variable para controlar la pulsacion del escape en la eleccion de la trama de control
	char c = 0;
	int velTransmision = 0;
	char PSerie[5];
	TramaDatos TDatos;
	ofstream flujo_sal;
	char buffer[802];
	int pi = 0;					//Indice del buffer
	int campoTrama = 1;		//Entero que hace referencia al campo de la trama
	bool esAutor = true;
	bool esColor = true;
	bool esNombreFichero = true;
	bool esFichero = false;
	bool finFichero = false;
	char cadAutores[70];
	char cadColor[5];
	char cadNombreFichero[50];
	bool ficheroLog = false;
	ofstream flujo_log;
	bool esF1 = false;
	ofstream fSalEsclavo;
	ofstream fSalMaestro;

//Encabezado
	printf(
			"============================================================================\n");
	printf(
			"----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES ------------\n");
	printf(
			"---------------------------- CURSO 2019/20 ---------------------------------\n");
	printf(
			"----------------------------- MAIN.CPP ----------------------------------\n");
	printf(
			"============================================================================\n\n");

//Se selecciona el puerto
	seleccionarPuerto(PSerie, salirPuerto);
//Si se pulsa el escape termina el programa
	if (salirPuerto == 1) {
		return (0);
	}
	SetConsoleTextAttribute(Pantalla, 14);	//Fondo negro, texto amarillo
	printf("El puerto elegido es: %s\n\n", PSerie);
	SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original

//Se selecciona la velocidad
	seleccionarVelocidad(velTransmision, salirVelocidad);
//Si se pulsa el escape termina el programa
	if (salirVelocidad == 1) {
		return (0);
	}
	SetConsoleTextAttribute(Pantalla, 14);	//Fondo negro, texto amarillo
	printf("La velocidad de transmision elegida es: %i\n\n", velTransmision);
	SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original

	PuertoCOM = AbrirPuerto(PSerie, velTransmision, 8, 0, 0);

//Se comprueba si ha habido algun error al abrir el puerto
	if (PuertoCOM == NULL) {
		SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
		printf("Error al abrir el puerto %s\n", PSerie);
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
		getch();
		return (1);
	} else {
		SetConsoleTextAttribute(Pantalla, 14);	//Fondo negro, texto amarillo
		printf("Puerto %s abierto correctamente\n", PSerie);
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
	}

// Lectura y escritura simultánea de caracteres
	while (c != ESCAPE && salirTrama == 0) {
		recibirTramas(PuertoCOM, Pantalla, campoTrama, TDatos, flujo_sal,
				esFichero, finFichero, esAutor, esColor, esNombreFichero,
				cadAutores, cadColor, cadNombreFichero, ficheroLog, flujo_log,
				fSalMaestro, fSalEsclavo);      //Recepción
		if (kbhit()) {
			c = getch();
			if (c != ESCAPE) { //Este if comprueba si la tecla que se ha pulsado es o no la tecla de escape
				recibimientoCaracter(c, salirTrama, PuertoCOM, Pantalla, buffer,
						pi, TDatos, campoTrama, flujo_sal, esFichero,
						finFichero, esAutor, esColor, esNombreFichero,
						cadAutores, cadColor, cadNombreFichero, ficheroLog,
						flujo_log, esF1, fSalMaestro, fSalEsclavo);
			}

		}
	}
	if (ficheroLog) {
		flujo_log.close();
	}

// Cerramos el puerto
	CerrarPuerto(PuertoCOM);

	return 0;
}

