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
#define IA 3

class Gato {
public:
	Gato();
	~Gato();
	//Funciones para segmentar la carga de la partida jugador vs jugador, o vs CPU

	void cargarJuego(bool);
	void cargarPartidaVsCPU(bool);
	void cargarPartidaVsContrincante();
	void jugarVsCPU();
	void jugarVsContrincante();

	/*funciones para probar metodos nuevos*/
	void setHumano(Jugador* j);
	void setCPU(Jugador* j);
	void setTablero(Tablero t);
	Celda mejorMovimientoMini();
	void dibujar();
private:
	Jugador* humano;
	Jugador* oponente;
	Jugador* cpu;
	Tablero areaJuego;
	char turnoActual;
	int dificultad;
	int tipoJugador;

	void instrucciones();
	void menuSimbolo();
	void menuSimboloHumano();
	int menuDificultad();
	int menuTipoJugador();
	void menuFinal();
	void determinaTurno();
	void determinaTurnoHumano();
	void cambiarTurno();
	void realizarMovimiento();
	void realizarMovimientoHumano();
	void realizaMovimientoIA();
	bool hayGanador();
	bool hayGanadorHumano();

	void muestraResultado();
	void muestraResultadoHumano();
	void movimientoFacilCpu();
	void mejorMovimientoCpu();


	int evaluaTablero(Tablero t); //evaluate
	int minimax(Tablero t, int d, bool m); //
};

#endif // !GATO_H