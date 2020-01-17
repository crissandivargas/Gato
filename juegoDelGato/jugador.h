// jugador.h
// Declaraci�n de la clase Jugador

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
public:
	Jugador();
	Jugador(std::string, char, bool);
	~Jugador();
	void setNombre(std::string);
	void setSimbolo(char);
	void setEstado(bool);
	std::string getNombre();
	char getSimbolo();
	bool getEstado();

private:
	std::string nombre;  // Nombre del jugador
	char simbolo;        // S�mbolo - 'X' o 'O'
	bool estado;         // Gan� (True) o perdi� (False)
};

#endif
