/*
 * EnviarTrama.cpp
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "EnviarTrama.h"

/*
 * Envia uno a uno todos los caracteres que forman la trama de datos
 */
void enviarTramaDatos(HANDLE &PuertoCOM, char cadCuerpoFichero[],
		bool &ficheroLog, ofstream &flujo_log, bool &esF1) {
	if (esF1) {
		if (ficheroLog) {
			if (flujo_log.is_open()) {
				flujo_log.write(cadCuerpoFichero, strlen(cadCuerpoFichero));
			}
		}
	}
	TramaDatos TDatos;
	TDatos.setLong(strlen(cadCuerpoFichero));
	TDatos.setDatos(cadCuerpoFichero);
	unsigned char BCE;
	calcularBCE(TDatos, BCE);
	TDatos.setBce(BCE);

	EnviarCaracter(PuertoCOM, TDatos.getSincronismo());
	EnviarCaracter(PuertoCOM, TDatos.getDireccion());
	EnviarCaracter(PuertoCOM, TDatos.getControl());
	EnviarCaracter(PuertoCOM, TDatos.getNTrama());
	EnviarCaracter(PuertoCOM, TDatos.getLong());
	EnviarCadena(PuertoCOM, TDatos.getDatos(), TDatos.getLong());
	EnviarCaracter(PuertoCOM, TDatos.getBce());
}

/*
 * Envia uno a uno todos los caracteres que forman la trama de control
 */
void definirTramaControl(HANDLE &PuertoCOM, unsigned char caracterControl) {
	TramaControl TControl;
	TControl.setControl(caracterControl);
	EnviarCaracter(PuertoCOM, TControl.getSincronismo());
	EnviarCaracter(PuertoCOM, TControl.getDireccion());
	EnviarCaracter(PuertoCOM, TControl.getControl());
	EnviarCaracter(PuertoCOM, TControl.getNumeroTrama());

}

/*
 * Metodo para enviar tramas del protocolo
 */
void enviarTramaProtocolo(HANDLE &PuertoCOM, char cadCuerpoFichero[],TramaDatos &TDatos,bool &error) {
	TDatos.setLong(strlen(cadCuerpoFichero));
	TDatos.setDatos(cadCuerpoFichero);
	unsigned char BCE;
	calcularBCE(TDatos, BCE);
	TDatos.setBce(BCE);
	if(error){
		cadCuerpoFichero[0] = 'ç';
		error = false;
		TDatos.setDatos(cadCuerpoFichero);
	}

	EnviarCaracter(PuertoCOM, TDatos.getSincronismo());
	EnviarCaracter(PuertoCOM, TDatos.getDireccion());
	EnviarCaracter(PuertoCOM, TDatos.getControl());
	EnviarCaracter(PuertoCOM, TDatos.getNTrama());
	EnviarCaracter(PuertoCOM, TDatos.getLong());
	EnviarCadena(PuertoCOM, TDatos.getDatos(), TDatos.getLong());
	EnviarCaracter(PuertoCOM, TDatos.getBce());
}

/*
 * Enviar dependiendo del tipo de trama
 */
void enviarTrama(TramaDatos trama, HANDLE &PuertoCOM) {
	EnviarCaracter(PuertoCOM, trama.getSincronismo());
	EnviarCaracter(PuertoCOM, trama.getDireccion());
	EnviarCaracter(PuertoCOM, trama.getControl());
	EnviarCaracter(PuertoCOM, trama.getNTrama());

	if (trama.getControl() == 02) { //Si enviamos una trama de Datos
		EnviarCaracter(PuertoCOM, trama.getLong());
		for (int k = 0; k < trama.getLong(); k++) {
			EnviarCaracter(PuertoCOM, trama.getDatos()[k]);
		}
		EnviarCaracter(PuertoCOM, trama.getBce());
	}
}

/*
 * Se selecciona el tipo de trama de control y se llama al metodo que la envia, definirTramaControl
 */
void enviarTramaControl(HANDLE &PuertoCOM, HANDLE &Pantalla,
		bool &ficheroLog, ofstream &flujo_log) {
	int salir = 0; //Entero que indica si el usuario desea salir o no. Si quiere salir esta variable tomara el valor 1
	boolean fin = false; //Booleano que representa la condicion del bucle. Este finalizará si se ha elegido una de las opciones
	char control = -1;	//Char que representa la opcion elegida por el usuario
	unsigned char caracterControl = 0;

	while (!fin) {

		if (ficheroLog) {
			if (flujo_log.is_open()) {
				flujo_log.write("Seleccione el tipo de trama de control :\n",
						strlen("Seleccione el tipo de trama de control :\n"));
				flujo_log.write("1: Trama ENQ\n", strlen("1: Trama ENQ\n"));
				flujo_log.write("2: Trama EOT\n", strlen("2: Trama EOT\n"));
				flujo_log.write("3: Trama ACK\n", strlen("3: Trama ACK\n"));
				flujo_log.write("4: Trama NACK\n", strlen("4: Trama NACK\n"));
				flujo_log.write("<ESC> Finalizar\n",
						strlen("<ESC> Finalizar\n"));
			}
		}

		printf("Seleccione el tipo de trama de control :\n");
		printf("1: Trama ENQ\n");
		printf("2: Trama EOT\n");
		printf("3: Trama ACK\n");
		printf("4: Trama NACK\n");
		printf("<ESC> Finalizar\n");

		control = getch();
		if (control != ESCAPE) {
			if (ficheroLog) {
				if (flujo_log.is_open()) {
					flujo_log.put(control);
					flujo_log.write("\n", strlen("\n"));
				}
			}
			printf("%c\n", control);
		}
		switch (control) {
		case UNO:
			caracterControl = ENQ;
			fin = true;
			break;
		case DOS:
			caracterControl = EOT;
			fin = true;
			break;
		case TRES:
			caracterControl = ACK;
			fin = true;
			break;
		case CUATRO:
			caracterControl = NACK;
			fin = true;
			break;
		case ESCAPE:
			fin = true;
			salir = 1;
			SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
			printf("Cancelado el enviar trama de control\n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			break;
		default:
			if (ficheroLog) {
				if (flujo_log.is_open()) {
					flujo_log.write(
							"Por favor seleccione una de las cuatro opciones. \n\n",
							strlen(
									"Por favor seleccione una de las cuatro opciones. \n\n"));
				}
			}
			SetConsoleTextAttribute(Pantalla, 12);	//Fondo negro, texto rojo
			printf("Por favor seleccione una de las cuatro opciones. \n\n");
			SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
			break;
		}
	}
	if (salir == 0) {
		definirTramaControl(PuertoCOM, caracterControl);
	}
}

/*
 * Metodo donde se contemplan los diferentes casos posibles que se dan cuando se ha pulsado una tecla distinta al escape
 * Tiene un parametro que hace referencia al valor de la tecla pulsada, ch.
 */
void recibimientoCaracter(char ch, int &salir,HANDLE &PuertoCOM,HANDLE &Pantalla,char buffer[], int &pi, TramaDatos &TDatos, int &campo, ofstream &flujo_sal,bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[], bool &ficheroLog, ofstream &flujo_log, bool &esF1,ofstream &fSalMaestro,ofstream &fSalEscalvo) {
	switch (ch) {
	case FUNCION:
		teclaFuncion(PuertoCOM,Pantalla,salir,buffer,pi,TDatos,campo,flujo_sal, esFichero, finFichero, esAutor,esColor,esNombreFichero,cadAutores,cadColor,cadNombreFichero,ficheroLog,flujo_log,esF1,fSalMaestro,fSalEscalvo);
		break;
	case RETROCESO:
		printf("\b");
		printf("%c", ' ');
		decrementarPI(pi);
		printf("%c", ch);
		break;
	case ENTER: // retorno de carro
		escribirCaracter('\n',pi,buffer,Pantalla);
		break;
	default:
		escribirCaracter(ch,pi,buffer,Pantalla);
		break;
	}

}

