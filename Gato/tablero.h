#ifndef TABLERO_H
#define TABLERO_H

#define CASILLAS 3

#include "Celda.h"
#include <sstream>
#include <vector>
#include <iterator>

class Tablero
{
public:
	Tablero();
	~Tablero();
	std::vector<std::vector<Celda*> > getTablero();
	void limpiar();
	void actualizar(short int, short int, char);
	void insertar(short int, short int, Celda*);
	bool encuentraGanador(char);
	bool movimientosDisponibles();
	bool validarPosicion(int, int);
	std::string toString();
private:
	std::vector<std::vector<Celda*> > tab;
};

#endif