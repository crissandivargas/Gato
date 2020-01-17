// tablero.cpp
// Implementación de la clase Tablero

#include "tablero.h"

Tablero::Tablero(){
	for (int i = 0; i < CASILLAS; ++i) {
		for (int j = 0; j < CASILLAS; j++) {

		}
	}
		
}

Tablero::~Tablero() {}

char* Tablero::getTablero() {
	return tab;
}

void Tablero::limpiar() {
	for (int i = 0; i < CASILLAS; ++i)
		tab[i] = VACIO;
}

void Tablero::actualizar(short int pos, char s) {
		tab[pos] = s;
}

bool Tablero::encuentraGanador(char s) {
	// Verificamos las filas
	if ((tab[0] == s && tab[1] == s && tab[2] == s) ||
		(tab[3] == s && tab[4] == s && tab[5] == s) ||
		(tab[6] == s && tab[7] == s && tab[8] == s))
		return true;

	// Verificamos las columnas
	if ((tab[0] == s && tab[3] == s && tab[6] == s) ||
		(tab[1] == s && tab[4] == s && tab[7] == s) ||
		(tab[2] == s && tab[5] == s && tab[8] == s))
		return true;

	// Verificamos las diagonales
	if ((tab[0] == s && tab[4] == s && tab[8] == s) ||
		(tab[2] == s && tab[4] == s && tab[6] == s))
		return true;

	// Si ninguna coincide, retornamos FALSO
	return false;
}

bool Tablero::validarPosicion(int pos) {
	if (pos < 0 || pos > 8) {
		return false;
	}

	if (tab[pos] != VACIO) {
		return false;
	}
	return true;
}