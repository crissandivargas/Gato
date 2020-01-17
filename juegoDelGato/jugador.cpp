// jugador.cpp
// Implementación de la clase Jugador

#include "jugador.h"

Jugador::Jugador() : simbolo(' '), estado(false) { }

Jugador::Jugador(std::string n, char s, bool b) : nombre(n), simbolo(s), estado(b) {}

Jugador::~Jugador() {}

void Jugador::setNombre(std::string n) {
	nombre = n;
}

void Jugador::setSimbolo(char s) {
	simbolo = s;
}

void Jugador::setEstado(bool b) {
	estado = b;
}

std::string Jugador::getNombre() {
	return nombre;
}

char Jugador::getSimbolo() {
	return simbolo;
}

bool Jugador::getEstado() {
	return estado;
}