/*
 * TramaDatos.cpp
 *
 *  Created on: 24 feb. 2020
 *  Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "TramaDatos.h"
#include <string.h>

TramaDatos::TramaDatos() {
	setSincronismo(22);
	setDireccion('T');
	setNTrama('0');
	setControl(02);
}

void TramaDatos::inicializarTramaDatos(){
	setSincronismo(22);
	setDireccion('T');
	setNTrama('0');
	setControl(02);
}
unsigned char TramaDatos::getBce() {
	return BCE;
}

void TramaDatos::setBce(unsigned char bce) {
	BCE = bce;
}

unsigned char TramaDatos::getControl() {
	return C;
}

void TramaDatos::setControl(unsigned char c) {
	C = c;
}

unsigned char TramaDatos::getDireccion(){
	return D;
}

void TramaDatos::setDireccion(unsigned char d) {
	D = d;
}

char* TramaDatos::getDatos() {
	return Datos;
}
void TramaDatos::setDatos(char cadena[]){
	strcpy(Datos,cadena);
}

unsigned char TramaDatos::getLong(){
	return L;
}

void TramaDatos::setLong(unsigned char l) {
	L = l;
}

unsigned char TramaDatos::getNTrama(){
	return N;
}

void TramaDatos::setNTrama(unsigned char n) {
	N = n;
}

unsigned char TramaDatos::getSincronismo(){
	return S;
}

void TramaDatos::setSincronismo(unsigned char s) {
	S = s;
}

TramaDatos::~TramaDatos() {
	// TODO Auto-generated destructor stub
}

