// tablero.h
// Declaración de la clase Tablero

#include "Celda.h"
#include <string>
#include <sstream>

#ifndef TABLERO_H
#define TABLERO_H

#define CASILLAS	3

class Tablero {
public:
	Tablero();
	~Tablero();
	Celda*** getTablero();
	void limpiar();
	void actualizar(short int, short int, char);
	void insertar(short int, short int, Celda*);
	bool encuentraGanador(char);
	bool validarPosicion(int, int);
	std::string toString();
private:
	Celda*** tab;
};

#endif