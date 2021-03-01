/*
 * EnviarFicheroDatos.h
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef ENVIARFICHERODATOS_H_
#define ENVIARFICHERODATOS_H_
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "PuertoSerie.h"
#include "TramaDatos.h"
#include "MetodosAuxiliares.h"
#include "EnviarTrama.h"
#include "RecibirTrama.h"
#include "RecibirFicheroDatos.h"

using namespace std;

void enviarFicheroDatos(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,ofstream &flujo_sal, bool &esFichero, bool &finFichero, bool &esAutor,bool &esColor, bool &esNombreFichero, char cadAutores[],char cadColor[], char cadNombreFichero[],bool &ficheroLog,ofstream &flujo_log, bool &esF1);
void enviarNumCaracteres(int &contador, HANDLE &PuertoCOM, bool &ficheroLog,ofstream &flujo_log, bool &esF1);
void enviarFicheroProtocolo(HANDLE &PuertoCOM, HANDLE &Pantalla, int &campo,TramaDatos &TDatos, ofstream &flujo_salida, bool &esFichero,bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[],bool &esSeleccion, bool &esSondeo,ofstream &fSalMaestroEsclavo);
#endif /* ENVIARFICHERODATOS_H_ */
