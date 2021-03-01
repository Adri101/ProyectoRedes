/*
 * RecibirTrama.cpp
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "RecibirTrama.h"

/*
 * Se distinguen las diferentes partes de la trama
 */
void recibirTramas(HANDLE &PuertoCOM,HANDLE &Pantalla,int &campo, TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero, char cadAutores[], char cadColor[], char cadNombreFichero[], bool &ficheroLog, ofstream &flujo_log,ofstream &fSalMaestro,ofstream &fSalEsclavo) {
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
				} else {
					if (car == '}') {
						if(ficheroLog){
							if(flujo_log.is_open()){
								flujo_log.write("Fichero recibido \n",strlen("Fichero recibido \n"));
							}
						}
						SetConsoleTextAttribute(Pantalla, atoi(cadColor));
						printf("Fichero recibido \n");
						SetConsoleTextAttribute(Pantalla, 7);
						esFichero = false;
						finFichero = true;
						flujo_salida.close();
					}
					if (car == 'E'){
						if(ficheroLog){
							flujo_log.close();
							ficheroLog = false;
						}
						fSalEsclavo.open("Prolog-e.txt");
						esclavo(PuertoCOM,Pantalla,campo,TDatos,flujo_salida,esFichero,finFichero,esAutor,esColor,esNombreFichero,cadAutores,cadColor,cadNombreFichero,fSalEsclavo);
						fSalEsclavo.close();
					}else{
						if(car == 'M'){
							if(ficheroLog){
								flujo_log.close();
								ficheroLog = false;
							}
							fSalMaestro.open("Prolog-m.txt");
							maestro(PuertoCOM,Pantalla,campo,TDatos,flujo_salida,esFichero,finFichero,esAutor,esColor,esNombreFichero,cadAutores,cadColor,cadNombreFichero,fSalMaestro);
							fSalMaestro.close();
						}
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
				procesarTramaControl(Pantalla,TControl,ficheroLog,flujo_log);
				//Reiniciar el campo control de la trama de datos
				TDatos.setControl(02);
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
			calcularBCE(TDatos,BCE);
			if (BCE == TDatos.getBce()) {
				if (esFichero) {
					procesarFichero(cadAutores,cadColor,cadNombreFichero,TDatos,Pantalla,flujo_salida,esAutor,esColor,esNombreFichero,ficheroLog,flujo_log);
				} else {
					if (finFichero) {
						if(ficheroLog){
							if(flujo_log.is_open()){
								flujo_log.write("El fichero recibido tiene un tamanho de ",strlen("El fichero recibido tiene un tamanho de "));
								flujo_log.write(TDatos.getDatos(),strlen(TDatos.getDatos()));
								flujo_log.write(" bytes.\n",strlen(" bytes.\n"));
							}
						}
						SetConsoleTextAttribute(Pantalla, atoi(cadColor));
						printf("El fichero recibido tiene un tamanho de %s bytes.\n",TDatos.getDatos());
						SetConsoleTextAttribute(Pantalla, 7);
						finFichero = false;
					} else {
						if(ficheroLog){
							if(flujo_log.is_open()){
								flujo_log.write(TDatos.getDatos(),strlen(TDatos.getDatos()));
							}
						}
						SetConsoleTextAttribute(Pantalla, 2); //Fondo negro, texto verde
						printf("%s", TDatos.getDatos());
						SetConsoleTextAttribute(Pantalla, 7); //Vuelta al color original
					}
				}

			} else {
				if (esFichero) {
					if(ficheroLog){
						if(flujo_log.is_open()){
							flujo_log.write("Error en la recepción de la trama del fichero.\n",strlen("Error en la recepción de la trama del fichero.\n"));
						}
					}
					SetConsoleTextAttribute(Pantalla, 12); //Fondo negro, texto rojo
					printf("Error en la recepción de la trama del fichero.\n");
					SetConsoleTextAttribute(Pantalla, 7); //Vuelta al color original
				} else {
					if(ficheroLog){
						if(flujo_log.is_open()){
							flujo_log.write("Error al recibir la trama \n",strlen("Error al recibir la trama \n"));
						}
					}
					SetConsoleTextAttribute(Pantalla, 12); //Fondo negro, texto rojo
					printf("Error al recibir la trama \n");
					SetConsoleTextAttribute(Pantalla, 7); //Vuelta al color original
				}
			}
			campo = 1;
			break;
		}
	}
}

/*
 * Se muestra por pantalla el nombre de la trama de control que se haya recibido
 */
void procesarTramaControl(HANDLE &Pantalla,TramaControl &TControl,bool &ficheroLog, ofstream &flujo_log) {
	switch (TControl.getControl()) {
	case ENQ:
		if(ficheroLog){
			if(flujo_log.is_open()){
				flujo_log.write("Se ha recibido una trama ENQ\n",strlen("Se ha recibido una trama ENQ\n"));
			}
		}
		SetConsoleTextAttribute(Pantalla, 5);	//Fondo negro, texto morado
		printf("Se ha recibido una trama ENQ\n");
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
		break;
	case EOT:
		if(ficheroLog){
			if(flujo_log.is_open()){
				flujo_log.write("Se ha recibido una trama ENQ\n",strlen("Se ha recibido una trama EOT\n"));
			}
		}
		SetConsoleTextAttribute(Pantalla, 5);	//Fondo negro, texto morado
		printf("Se ha recibido una trama EOT\n");
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
		break;
	case ACK:
		if(ficheroLog){
			if(flujo_log.is_open()){
				flujo_log.write("Se ha recibido una trama ACK\n",strlen("Se ha recibido una trama ACK\n"));
			}
		}
		SetConsoleTextAttribute(Pantalla, 5);	//Fondo negro, texto morado
		printf("Se ha recibido una trama ACK\n");
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
		break;
	case NACK:
		if(ficheroLog){
			if(flujo_log.is_open()){
				flujo_log.write("Se ha recibido una trama NACK\n",strlen("Se ha recibido una trama NACK\n"));
			}
		}
		SetConsoleTextAttribute(Pantalla, 5);	//Fondo negro, texto morado
		printf("Se ha recibido una trama NACK\n");
		SetConsoleTextAttribute(Pantalla, 7);	//Vuelta al color original
		break;
	}
}








