// gato.cpp
// Implementación de la clase Gato

#include "gato.h"

Gato::Gato() { 

	Celda *c0 = new Celda(0,0);
	Celda *c1 = new Celda(0,1);
	Celda *c2 = new Celda(0,2);
	Celda *c3 = new Celda(1,0);
	Celda *c4 = new Celda(1,1);
	Celda *c5 = new Celda(1,2);
	Celda *c6 = new Celda(2,0);
	Celda *c7 = new Celda(2,1);
	Celda *c8 = new Celda(2,2);

	areaJuego.insertar(0,0,c0);
	areaJuego.insertar(0,1,c1);
	areaJuego.insertar(0,2,c2);

	areaJuego.insertar(1,0,c3);
	areaJuego.insertar(1,1,c4);
	areaJuego.insertar(1,2,c5);

	areaJuego.insertar(2,0,c6);
	areaJuego.insertar(2,1,c7);
	areaJuego.insertar(2,2,c8);

	
}

Gato::~Gato() { }

void Gato::jugar() {
	srand(static_cast<unsigned int>(time(nullptr)));

	humano = new Jugador();
	cpu = new Jugador("CPU", ' ', false);

	// Inicializamos el número de posibles casillas del tablero
	int casillas = 9;

	// Muestra la pantalla de inicio del juego con las instrucciones
	instrucciones();

	// Obtiene el símbolo del jugador 
	menuSimbolo();

	// Determina la dificultad del juego
	dificultad = menuDificultad();

	// Utiliza un algoritmo para obtener el jugador que inicia
	determinaTurno();

	system("cls");

	// Imprimimos el tablero en pantalla
	dibujar();

	// Ciclo que controla la secuencia de jugadas. El ciclo se ejecuta mientras no haya un ganador
	// y todavía existan casillas para jugar. Ambas condiciones se deben cumplir para continuar.
	while (!cpu->getEstado() && !humano->getEstado() && casillas > 0) {

		std::cout << "Turno de la " << turnoActual;
		std::cout << std::endl;

		// Verificamos si es el turno del jugador o el CPU. En cualquier caso, se anota el símbolo correspondiente
		// en el tablero en la posición dada
		realizarMovimiento();

		// Disminuimos la cantidad de posiciones del tablero disponibles
		--casillas;

		// Si todavía no hay un ganador, entonces cambiamos el turno para el siguiente juego
		if (!hayGanador())
			cambiarTurno();

		system("cls");

		// Imprimimos el tablero en pantalla
		dibujar();

	} // Fin del while

	muestraResultado();
}

void Gato::instrucciones() {
	std::cout << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "BIENVENIDO AL JUEGO DEL GATO" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCCIONES: Debe seleccionar una posicion (1 - 9) para jugar." << std::endl;
	std::cout << std::endl;
	std::cout << " " << "1" << " " << "|" << " " << "2" << " " << "|" << " " << "3" << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << " " << "4" << " " << "|" << " " << "5" << " " << "|" << " " << "6" << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << " " << "7" << " " << "|" << " " << "8" << " " << "|" << " " << "9" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Gana el que logre formar tres simbolos en linea, de manera vertical, horizontal o diagonal." << std::endl;
	std::cout << std::endl;
	std::cout << "            ***  QUE COMIENCE EL JUEGO  ***" << std::endl << std::endl << std::endl;
	system("pause");
}

void Gato::menuSimbolo() {
	system("cls");
	std::cout << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "SELECCION DE SIMBOLO" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << std::endl << std::endl;

	char opcion;
	std::string nombreJugador;

	std::cout << "Digite su nombre, humano: ";
	std::getline(std::cin, nombreJugador);

	humano->setNombre(nombreJugador);

	do {
		std::cout << "Seleccione el simbolo que desee utilizar " << humano->getNombre() << std::endl;
		std::cout << "1. X" << std::endl;
		std::cout << "2. O" << std::endl;
		std::cout << "        Opcion: ";
		std::cin >> opcion;
		std::cout << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (opcion != '1' && opcion != '2');

	if (opcion == '1') {
		humano->setSimbolo(X);
		cpu->setSimbolo(O);
	}
	else {
		humano->setSimbolo(O);
		cpu->setSimbolo(X);
	}
}

int Gato::menuDificultad() {
	system("cls");
	std::cout << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "SELECCION DE NIVEL" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << std::endl << std::endl;

	char opcion;

	do {
		std::cout << "Seleccione la dificultad " << humano->getNombre() << std::endl;
		std::cout << "1. FACIL" << std::endl;
		std::cout << "2. DIFICIL" << std::endl;
		std::cout << "        Opcion: ";
		std::cin >> opcion;
		std::cout << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (opcion != '1' && opcion != '2');

	return opcion == '1' ? FACIL : DIFICIL;
	//if (opcion == '1')
	//	return FACIL;
	//if (opcion == '2')
	//	return INTERMEDIO;
	//else
	//	return DIFICIL;
}

void Gato::determinaTurno() {
	// Genera un número aleatorio que determina el jugador que comienza primero
	// Si el número es PAR, inicia el jugador, en caso contrario inicia el CPU
	int turnoAleatorio = rand() % 100 + 1;
	if (turnoAleatorio % 2 == 0)
		turnoActual = humano->getSimbolo();     // Inicia el jugador
	else
		turnoActual = cpu->getSimbolo();   // Inicia el CPU

	std::cout << std::endl << std::endl;
	std::cout << "INICIA EL JUGADOR CON LA " << turnoActual;
	std::cout << std::endl << std::endl;
	system("pause");
}

void Gato::cambiarTurno() {
	if (turnoActual == X)
		turnoActual = O;
	else
		turnoActual = X;
}

void Gato::realizarMovimiento() {
	short int i, j;
	bool valida;

	// Si es el turno del jugador
	if (turnoActual == humano->getSimbolo()) {
		do {
			std::cout << std::endl << std::endl << "   POSICION: ";
			std::cin >> i;
			std::cin >> j;
			if (!(valida = areaJuego.validarPosicion(i,j)))
				std::cout << std::endl << std::endl << "    MOVIMIENTO INVALIDO. INTENTE NUEVAMENTE";
		} while (!valida);

		areaJuego.actualizar(i,j, humano->getSimbolo());

		if (areaJuego.encuentraGanador(humano->getSimbolo())) 
			humano->setEstado(true);
	}
	else {
		if (dificultad == FACIL)
			movimientoFacilCpu();
		else if (dificultad == DIFICIL)
			mejorMovimientoCpu();

		if (areaJuego.encuentraGanador(cpu->getSimbolo()))
			cpu->setEstado(true);
	}
}

bool Gato::hayGanador() {
	if (cpu->getEstado() || humano->getEstado())
		return true;
	return false;
}

void Gato::dibujar() {
//	char* copiaTablero = areaJuego.getTablero();
//
//	std::cout << std::endl;
//	std::cout << " " << copiaTablero[0] << " " << "|" << " " << copiaTablero[1] << " " << "|" << " " << copiaTablero[2] << std::endl;
//	std::cout << "----------" << std::endl;
//	std::cout << " " << copiaTablero[3] << " " << "|" << " " << copiaTablero[4] << " " << "|" << " " << copiaTablero[5] << std::endl;
//	std::cout << "----------" << std::endl;
//	std::cout << " " << copiaTablero[6] << " " << "|" << " " << copiaTablero[7] << " " << "|" << " " << copiaTablero[8] << std::endl;
//	std::cout << std::endl << std::endl;
	std::cout << areaJuego.toString();
}

void Gato::muestraResultado() {
	// Muestra el ganador del juego, si lo hay. En caso contrario, declara empate.
	if (cpu->getEstado())
		std::cout << "El GANADOR ES EL " << cpu->getNombre() << ". INTENTALO NUEVAMENTE";
	else if (humano->getEstado())
		std::cout << humano->getNombre() << " HA GANADO. BIEN HECHO";
	else
		std::cout << "EL JUEGO RESULTO EN EMPATE. MEJOR SUERTE LA PROXIMA VEZ";

	std::cout << std::endl << std::endl;
	system("pause");
}

void Gato::movimientoFacilCpu() {
	short int i;
	short int j;

	do {
		i = rand() % 3;
		j = rand() % 3;
	} while (!areaJuego.validarPosicion(i,j));

	areaJuego.actualizar(i,j, cpu->getSimbolo());
}

void Gato::mejorMovimientoCpu() {
	short int i = 0;
	short int j = 0;
	bool encontro = false;

	// Definimos los mejores movimientos en un vector. Se utiliza en caso de que no exista un ganador
	const short int MEJORES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 }; //{1,1},{0,0},{0,2}

	// Verificamos si la CPU es ganadora en el siguiente movimiento. El algoritmo prueba todos los movimientos
	// posibles hasta que encuentre una posición ganadora o pruebe todas las posibilidades.
	while (!encontro && (i,j) < CASILLAS) {
		if (areaJuego.validarPosicion(i,j)) {
			areaJuego.actualizar(i,j, cpu->getSimbolo());
			encontro = areaJuego.encuentraGanador(cpu->getSimbolo());
			areaJuego.actualizar(i,j, ' ');
		}
		if (!encontro)
			++i,j;
	}

	// Ahora verificamos si el jugador gana en el próximo movimiento. En ese caso el CPU realiza el
	// movimiento para evitarlo
	if (!encontro) {
		i = 0;
		j = 0;
		while (!encontro && (i,j) < CASILLAS) {
			if (areaJuego.validarPosicion(i,j)) {
				areaJuego.actualizar(i,j, humano->getSimbolo());
				encontro = areaJuego.encuentraGanador(humano->getSimbolo());
				areaJuego.actualizar(i,j, ' ');
			}
			if (!encontro)
				++i,j;
		}
	}

	// Si el CPU ni el jugador ganan en el siguiente movimiento, la CPU hace la jugada en la mejor casilla disponible
	// en el siguiente orden: centro, esquinas, lateral
	if (!encontro) {
		i,j = 0;

		while (!encontro && i,j < CASILLAS) {
			if (areaJuego.validarPosicion(MEJORES[i],MEJORES[j]))
				encontro = true;
			else
				++i,j;
		}
		i,j = MEJORES[i];
	}

	areaJuego.actualizar(i,j, cpu->getSimbolo());
}
