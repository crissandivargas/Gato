// tablero.h
// Declaración de la clase Tablero

#include "Celda.h"

#ifndef TABLERO_H
#define TABLERO_H

#define CASILLAS	3
#define VACIO	    ' '

class Tablero {
public:
	Tablero();
	~Tablero();
	char* getTablero();
	void limpiar();
	void actualizar(short int, char);
	bool encuentraGanador(char);
	bool validarPosicion(int);
private:
	Tablero* tab[CASILLAS][CASILLAS];
	Celda* tab[CASILLAS][CASILLAS]
};

#endif