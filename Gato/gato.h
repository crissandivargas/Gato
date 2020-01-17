#ifndef GATO_H
#define GATO_H

#include "jugador.h"
#include "tablero.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
/*incluye:
  -funcion max(): retorna el valor mayor entre dos elementos
  -funcion min(): retorna el menor valor entre dos elementos
*/


#define	X		'X'
#define O		'O'
#define FACIL	1
//#define INTERMEDIO 2
#define DIFICIL	2

class Gato {
public:
	Gato();
	~Gato();
	void jugar();

private:
	Jugador* humano;
	Jugador* cpu;
	Tablero areaJuego;
	char turnoActual;
	int dificultad;

	void instrucciones();
	void menuSimbolo();
	int menuDificultad();
	void determinaTurno();
	void cambiarTurno();
	void realizarMovimiento();
	bool hayGanador();
	void dibujar();
	void muestraResultado();
	void movimientoFacilCpu();
	void mejorMovimientoCpu();
};

#endif // !GATO_H



