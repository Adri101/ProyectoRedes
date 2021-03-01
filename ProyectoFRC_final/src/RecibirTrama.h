/*
 * RecibirTrama.h
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef RECIBIRTRAMA_H_
#define RECIBIRTRAMA_H_
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
#include "RecibirFicheroDatos.h"
#include "Protocolo.h"

using namespace std;

void recibirTramas(HANDLE &PuertoCOM,HANDLE &Pantalla,int &campo, TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero, char cadAutores[], char cadColor[], char cadNombreFichero[], bool &ficheroLog, ofstream &flujo_log,ofstream &fSalMaestro,ofstream &fSalEsclavo);
void procesarTramaControl(HANDLE &Pantalla,TramaControl &TControl,bool &ficheroLog, ofstream &flujo_log);

#endif /* RECIBIRTRAMA_H_ */
