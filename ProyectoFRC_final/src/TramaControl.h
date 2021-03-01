/*
 * TramaControl.h
 *
 *  Created on: 17 feb. 2020
 *  Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef TRAMACONTROL_H_
#define TRAMACONTROL_H_

class TramaControl {
	unsigned char S; //sincronismo, por defecto 22
	unsigned char D; //direccion, por defecto 'T'
	unsigned char C; //Control = (05 (ENQ), 04 (EOT), 06 (ACK), 21 (NACK))
	unsigned char NT; //Numero de trama, en un principio '0'
public:
	/*
	 * Constructor por defecto. Aquí le damos un valor a todos los atributos de la trama de control exceptuando al control
	 */
	TramaControl();

	/*
	 * Getters y setters
	 */
	unsigned char getControl();
	void setControl(unsigned char c);
	unsigned char getDireccion();
	void setDireccion(unsigned char d);
	unsigned char getNumeroTrama();
	void setNumeroTrama(unsigned char nt);
	unsigned char getSincronismo();
	void setSincronismo(unsigned char s);

	/*
	 * Destructor
	 */
	virtual ~TramaControl();

};

#endif /* TRAMACONTROL_H_ */
