/*
 * EnviarTrama.h
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef ENVIARTRAMA_H_
#define ENVIARTRAMA_H_
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "PuertoSerie.h"
#include "TramaDatos.h"
#include "TramaControl.h"
#include "Constantes.h"
#include "MetodosAuxiliares.h"

using namespace std;

void enviarTramaDatos(HANDLE &PuertoCOM, char cadCuerpoFichero[], bool &ficheroLog, ofstream &flujo_log, bool &esF1);
void definirTramaControl(HANDLE &PuertoCOM,unsigned char caracterControl);
void enviarTrama(TramaDatos trama, HANDLE &PuertoCOM);
void enviarTramaControl(HANDLE &PuertoCOM,HANDLE &Pantalla, bool &ficheroLog, ofstream &flujo_log);
void enviarTramaProtocolo(HANDLE &PuertoCOM, char cadCuerpoFichero[],TramaDatos &TDatos,bool &error);
void recibimientoCaracter(char ch, int &salir,HANDLE &PuertoCOM,HANDLE &Pantalla,char buffer[], int &pi, TramaDatos &TDatos, int &campo, ofstream &flujo_sal,bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[], bool &ficheroLog, ofstream &flujo_log, bool &esF1,ofstream &fSalMaestro,ofstream &fSalEscalvo);


#endif /* ENVIARTRAMA_H_ */
