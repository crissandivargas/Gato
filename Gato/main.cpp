#include "gato.h"
#include "tablero.h"

int main(int argc, char** argv[]) {

	Gato* juegoDelGato = new Gato();
    juegoDelGato->cargarJuego(true);
	juegoDelGato = nullptr;
	delete juegoDelGato;
	return 0;
}