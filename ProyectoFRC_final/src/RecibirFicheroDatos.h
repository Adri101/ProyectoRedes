/*
 * RecibirFicheroDatos.h
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef RECIBIRFICHERODATOS_H_
#define RECIBIRFICHERODATOS_H_
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "PuertoSerie.h"
#include "TramaDatos.h"
#include "MetodosAuxiliares.h"

using namespace std;

void procesarFichero(char cadAutores[],char cadColor[],char cadNombreFichero[], TramaDatos &TDatos,HANDLE &Pantalla, ofstream &flujo_salida,bool &esAutor,bool &esColor,bool &esNombreFichero,bool &ficheroLog, ofstream &flujo_log);
void leerCabecera(HANDLE &PuertoCOM,ifstream &flujoEnt,bool &ficheroLog, ofstream &flujo_log, bool &esFichero);
void leerCabeceraProtocolo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],unsigned char &NTrama,ifstream &flujoEnt,bool &esSeleccion,bool &esSondeo,ofstream &fSalMaestroEsclavo, bool &error, bool &escape);
#endif /* RECIBIRFICHERODATOS_H_ */
