// tablero.cpp
// Implementación de la clase Tablero

#include "tablero.h"

Tablero::Tablero() {
	tab = new Celda * *[CASILLAS]; //crea col inicial
	for (int i = 0; i < CASILLAS; ++i) {
		tab[i] = new Celda * [CASILLAS]; //crea filas 
	}

	/*inicializa la matriz en NULL*/
	for (int i = 0; i < CASILLAS; i++) {
		for (int j = 0; j < CASILLAS; j++) {
			tab[i][j] = nullptr;
		}
	}
}

Tablero::~Tablero() {
	/*destruye los objetos en el tablero*/
	for (int i = 0; i < CASILLAS; i++) {
		for (int j = 0; j < CASILLAS; j++) {
			delete tab[i][j];
		}
	}
	/*destruye los arrays*/
	for (int i = 0; i < CASILLAS; ++i) {
		delete[] tab[i];
	}
	/*destruye tab*/
	delete[] tab;
}

Celda*** Tablero::getTablero() {
	return tab;
}

void Tablero::limpiar() {
	for (int i = 0; i < CASILLAS; i++) {
		for (int j = 0; j < CASILLAS; j++) {
			tab[i][j] = nullptr;
		}
	}
}

void Tablero::actualizar(short int i, short int j, char s) {
	tab[i][j]->setSimbolo(s);
}

//Funcion de prueba
void Tablero::insertar(short int i, short int j, Celda* c) {
	if(c != NULL) tab[i][j] = c; 
}

bool Tablero::encuentraGanador(char c) {

	/*verifica si hay victoria en las filas*/
	for (int i = 0; i < CASILLAS; i++) {
		if (tab[i][0]->getSimbolo() == tab[i][1]->getSimbolo() && tab[i][1]->getSimbolo() == tab[i][2]->getSimbolo()) {
			if(tab[i][0]->getSimbolo() == c) return true;
		}
	}

	/*verifica si hay victora en las columnas*/
	for (int i = 0; i < CASILLAS; i++) {
		if (tab[0][i]->getSimbolo() == tab[1][i]->getSimbolo() && tab[1][i]->getSimbolo() == tab[2][i]->getSimbolo()) {
			if(tab[0][i]->getSimbolo() == c) return true;
		}
	}
	/*verifica si hay victora en las diagonales izq-der, der-izq*/
	if (tab[0][0]->getSimbolo() == tab[1][1]->getSimbolo() && tab[1][1]->getSimbolo() == tab[2][2]->getSimbolo()) {
		if(tab[0][0]->getSimbolo() == c) return true;
	}

	if (tab[0][2]->getSimbolo() == tab[1][1]->getSimbolo() && tab[1][1]->getSimbolo() == tab[2][0]->getSimbolo()) {
		if(tab[0][2]->getSimbolo() == c) return true;
	}

	// Si ninguna coincide, retornamos FALSO
	return false;
}

bool Tablero::validarPosicion(int i, int j) {
	if (i < 0 || i > 3 || j < 0 || j > 3) {
		return false;
	}

	if (tab[i][j]->getSimbolo() != '_') {
		return false;
	}
	return true;
}

std::string Tablero::toString()
{
	std::stringstream s;
	for (int i = 0; i < CASILLAS; i++) {
		for (int j = 0; j < CASILLAS; j++) {
			s << "[" << tab[i][j]->getSimbolo() << "]";
		}
		s << "\n";
	}
	return s.str();
}