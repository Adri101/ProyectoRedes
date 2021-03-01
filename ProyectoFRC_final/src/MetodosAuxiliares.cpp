/*
 * MetodosAuxiliares.cpp
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "MetodosAuxiliares.h"

/*
 * Incrementa en 1 el valor del indice del buffer
 */
void decrementarPI(int &pi) {
	if (pi > 0) {
		pi--;
	}
}

/*
 * Decrementa en 1 el valor del indice del buffer
 */
void incrementarPI(int &pi) {
	if (pi >= 0 && pi < 802) {
		pi++;
	}
}

/*
 * Calcula el numero de tramas que son necesarias para enviar los caracteres de una cadena
 */
int numeroTramas(int &pi) {
	int tramas = pi / 254;
	if (pi % 254 == 0) {
		return tramas;
	} else {
		tramas++;
		return tramas;
	}
}

/*
 * Calcula el BCE a partir de una cadena dada
 */
void calcularBCE(TramaDatos &TDatos,unsigned char &BCE) {
	char cadenaAux[strlen(TDatos.getDatos())];
	strcpy(cadenaAux, TDatos.getDatos());
	BCE = cadenaAux[0];
	for (int i = 1; i < strlen(cadenaAux); i++) {
		BCE = BCE ^ cadenaAux[i];
	}
	if (BCE == 0 || BCE == 255) {
		BCE = 1;
	}
}

/*
 * Segmentar la cadena en tramas
 */
void segmentarCadena(TramaDatos &TDatos,int nTramas, int &contadorDatos, int &pi, char buffer[], char cadenaTrama[]) {
	int j;
	for (j = 0; j < 254 && contadorDatos < pi; j++) {
		cadenaTrama[j] = buffer[contadorDatos];
		contadorDatos++;
	}
	cadenaTrama[j] = '\0';
}

/*
 * Elimina el contenido del buffer
 */
void vaciarBuffer(char buffer[], int &pi) {
	for (int i = 0; i < pi; i++) {
		buffer[i] = ' ';
	}
	pi = 0;
}

/*
 * Almacena en el buffer un caracter "normal", es decir diferente a las teclas de funcion y a la tecla escape
 */
void escribirCaracter(char ch, int &pi, char buffer[], HANDLE &Pantalla) {
	if (pi < 800) {
		buffer[pi] = ch;
		incrementarPI(pi);
		SetConsoleTextAttribute(Pantalla, 11);	//Fondo negro, texto cian
		printf("%c", ch);
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
	}

}

/*
 * Metodo para diferenciar las distintas teclas de funcion
 */
void teclaFuncion(HANDLE &PuertoCOM,HANDLE &Pantalla,int &salir, char buffer[], int &pi, TramaDatos &TDatos, int &campo, ofstream &flujo_sal, bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[], bool &ficheroLog, ofstream &flujo_log, bool &esF1,ofstream &fSalMaestro,ofstream &fSalEsclavo) {
	int contadorDatos = 0;
	char ch = 0;
	int nTramas;
	ch = getch();
	char cadenaTrama[255];
	switch (ch) {
	case F1:
		esF1=true;
		buffer[pi] = '\n';
		incrementarPI(pi);
		nTramas = numeroTramas(pi);
		while (nTramas != 0) {
			segmentarCadena(TDatos,nTramas, contadorDatos,pi,buffer,cadenaTrama);
			enviarTramaDatos(PuertoCOM,cadenaTrama,ficheroLog,flujo_log,esF1);
			recibirTramas(PuertoCOM,Pantalla,campo,TDatos,flujo_sal, esFichero, finFichero, esAutor,esColor,esNombreFichero,cadAutores,cadColor,cadNombreFichero,ficheroLog,flujo_log,fSalMaestro,fSalEsclavo);
			nTramas--;
		}
		printf("\n");
		contadorDatos = 0;
		vaciarBuffer(buffer,pi);
		esF1=false;
		break;
	case F2:
		enviarTramaControl(PuertoCOM,Pantalla,ficheroLog,flujo_log);
		break;
	case F3:
		enviarFicheroDatos(PuertoCOM,Pantalla,campo,flujo_sal, esFichero, finFichero, esAutor,esColor,esNombreFichero,cadAutores,cadColor,cadNombreFichero,ficheroLog,flujo_log,esF1);
		break;
	case F5:
		ficheroLog=true;
		flujo_log.open("log.txt");
		if(ficheroLog){
			if(flujo_log.is_open()){
				flujo_log.write("A partir de este momento todo lo que salga por pantalla se almacenara en el fichero log.txt ... \n",strlen("A partir de este momento todo lo que salga por pantalla se almacenara en el fichero log.txt ... \n"));
			}
		}
		printf("A partir de este momento todo lo que salga por pantalla se almacenara en el fichero log.txt ... \n");
		break;
	case F6:
		if(ficheroLog){
			flujo_log.close();
			ficheroLog=false;
		}
		elegirRole(PuertoCOM,Pantalla,campo,TDatos,flujo_sal,esFichero,finFichero,esAutor,esColor,esNombreFichero,cadAutores,cadColor,cadNombreFichero,fSalMaestro,fSalEsclavo);
		break;
	default:
		break;
	}
}

/*
 * Mostrar trama protocolo. Sirve para escribir en el fichero y para mostrar por pantalla
 */
void mostrarTrama(TramaDatos tDatos, bool emisorFichero, bool receptor, char color, HANDLE &Pantalla, ofstream &fSalMaestroEscalvo){
	SetConsoleTextAttribute(Pantalla, color);
	if(emisorFichero){
		printf("E ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("E ",strlen("E "));
		}
	}else{
		printf("R ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("R ",strlen("R "));
		}
	}

	printf("%c ", tDatos.getDireccion());
	if(fSalMaestroEscalvo.is_open()){
		fSalMaestroEscalvo.put(tDatos.getDireccion());
		fSalMaestroEscalvo.write(" ",strlen(" "));
	}
	switch(tDatos.getControl()){
	case STX:
		printf("STX ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("STX ",strlen("STX "));
		}
	break;
	case ENQ:
		printf("ENQ ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("ENQ ",strlen("ENQ "));
		}
	break;
	case EOT:
		printf("EOT ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("EOT ",strlen("EOT "));
		}
	break;
	case ACK:
		printf("ACK ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("ACK ",strlen("ACK "));
		}
	break;
	case NACK:
		printf("NACK ");
		if(fSalMaestroEscalvo.is_open()){
			fSalMaestroEscalvo.write("NACK ",strlen("NACK "));
		}
	break;
	}

	printf("%c ", tDatos.getNTrama());
	if(fSalMaestroEscalvo.is_open()){
		fSalMaestroEscalvo.put(tDatos.getNTrama());
		fSalMaestroEscalvo.write(" ",strlen(" "));
	}

	if(tDatos.getControl() == 02){
		printf("%d ", tDatos.getBce());
		if(fSalMaestroEscalvo.is_open()){
			int bce1 = static_cast <unsigned char> (tDatos.getBce());
			fSalMaestroEscalvo << bce1;
			fSalMaestroEscalvo.write(" ",strlen(" "));
		}
		if(receptor){
			unsigned char BCE;
			calcularBCE(tDatos,BCE);
			printf("%d ", BCE);
			if(fSalMaestroEscalvo.is_open()){
				int bce2 = static_cast <unsigned char> (BCE);
				fSalMaestroEscalvo << bce2;
				fSalMaestroEscalvo.write(" ",strlen(" "));
			}

		}
	}
	printf("\n");
	if(fSalMaestroEscalvo.is_open()){
		fSalMaestroEscalvo.write("\n",strlen("\n"));
	}
	SetConsoleTextAttribute(Pantalla, 7);
}

