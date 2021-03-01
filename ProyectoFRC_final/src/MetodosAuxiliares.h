/*
 * MetodosAuxiliares.h
 *
 *  Created on: 26 mar. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef METODOSAUXILIARES_H_
#define METODOSAUXILIARES_H_
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "TramaDatos.h"
#include "Constantes.h"
#include "EnviarTrama.h"
#include "RecibirTrama.h"
#include "EnviarFicheroDatos.h"
#include "Protocolo.h"

using namespace std;

void decrementarPI(int &pi);
void incrementarPI(int &pi);
int numeroTramas(int &pi);
void calcularBCE(TramaDatos &TDatos,unsigned char &BCE);
void segmentarCadena(TramaDatos &TDatos,int nTramas, int &contadorDatos, int &pi, char buffer[], char cadenaTrama[]);
void vaciarBuffer(char buffer[], int &pi);
void escribirCaracter(char ch, int &pi, char buffer[], HANDLE &Pantalla);
void teclaFuncion(HANDLE &PuertoCOM,HANDLE &Pantalla,int &salir, char buffer[], int &pi, TramaDatos &TDatos, int &campo, ofstream &flujo_sal, bool &esFichero, bool &finFichero, bool &esAutor, bool &esColor, bool &esNombreFichero,char cadAutores[], char cadColor[], char cadNombreFichero[], bool &ficheroLog, ofstream &flujo_log, bool &esF1,ofstream &fSalMaestro,ofstream &fSalEsclavo);
void mostrarTrama(TramaDatos tDatos, bool emisorFichero, bool receptor, char color, HANDLE &Pantalla, ofstream &fSalMaestroEscalvo);

#endif /* METODOSAUXILIARES_H_ */
