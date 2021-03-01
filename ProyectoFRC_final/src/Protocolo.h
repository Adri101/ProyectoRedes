/*
 * Protocolo.h
 *
 *  Created on: 15 abr. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "Constantes.h"
#include "PuertoSerie.h"
#include "TramaDatos.h"
#include "TramaControl.h"
#include "RecibirTrama.h"

void elegirRole(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalMaestro,ofstream &fSalEsclavo);
void maestro(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalMaestro);
void maestroSeleccion(HANDLE &PuertoCOM,HANDLE &Pantalla,int &campo, TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero, char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalMaestro);
void maestroSondeo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalMaestro);
void esclavo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalEsclavo);
void esclavoSeleccion(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalEsclavo);
void esclavoSondeo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &fSalEsclavo);
void esperarConfirmacion(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &flujo_log);
void esperarLLamada(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &flujo_log);
void esperarTramaDatos(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &flujo_log);
int recibirTramaProtocolo(HANDLE &PuertoCOM,HANDLE &Pantalla,int &campo, TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero, char cadAutores[], char cadColor[], char cadNombreFichero[],ofstream &flujo_logME);

#endif /* PROTOCOLO_H_ */
