/*
 * TramaControl.cpp
 *
 *  Created on: 17 feb. 2020
 * 	Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#include "TramaControl.h"

TramaControl::TramaControl() {
	setSincronismo(22);
	setDireccion('T');
	setNumeroTrama('0');

}
unsigned char TramaControl::getControl() {
	return C;
}

void TramaControl::setControl(unsigned char c) {
	C = c;
}

unsigned char TramaControl::getDireccion() {
	return D;
}

void TramaControl::setDireccion(unsigned char d) {
	D = d;
}

unsigned char TramaControl::getNumeroTrama() {
	return NT;
}

void TramaControl::setNumeroTrama(unsigned char nt) {
	NT = nt;
}

unsigned char TramaControl::getSincronismo() {
	return S;
}

void TramaControl::setSincronismo(unsigned char s) {
	S = s;
}

TramaControl::~TramaControl() {
}

