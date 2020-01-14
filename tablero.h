// tablero.h
// Declaración de la clase Tablero

#ifndef TABLERO_H
#define TABLERO_H

#define CASILLAS	9
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
	char tab[CASILLAS];
};

#endif