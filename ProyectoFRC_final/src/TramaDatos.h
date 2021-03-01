/*
 * TramaDatos.h
 *
 *  Created on: 24 feb. 2020
 *  Autores: Adrian Fernandez Ramos y Daniel Mateos Serrano
 * 	Grupo: 1
 */

#ifndef TRAMADATOS_H_
#define TRAMADATOS_H_

class TramaDatos {
	unsigned char S; //Sincronismo = SYN =22;
	unsigned char D; //Direccion=’T’;
	unsigned char C; //Control = STX = 02;
	unsigned char N; //NumTrama = (En principio fijo a ‘0’);
	unsigned char L; //Long (Longitud del campo de datos);
	char Datos[255]; // Datos[255];
	unsigned char BCE; // (Siempre debe tomar siempre valores entre 1 y 254);
public:

	/*
	 * Constructor por defecto. Aquí le damos un valor a todos los atributos de la trama de control exceptuando al control
	 */
	TramaDatos();
	void inicializarTramaDatos();

	/*
	 * Getters y setters
	 */
	unsigned char getBce();
	void setBce(unsigned char bce);
	unsigned char getControl();
	void setControl(unsigned char c);
	unsigned char getDireccion();
	void setDireccion(unsigned char d);
	char* getDatos();
	void setDatos(char cadena[]);
	unsigned char getLong();
	void setLong(unsigned char l);
	unsigned char getNTrama();
	void setNTrama(unsigned char n);
	unsigned char getSincronismo();
	void setSincronismo(unsigned char s);

	/*
	 * Destructor
	 */
	virtual ~TramaDatos();
};

#endif /* TRAMADATOS_H_ */
