// gato.cpp
// Implementación de la clase Gato

#include "gato.h"

Gato::Gato() {

	humano = nullptr;
	oponente = nullptr;
	cpu = nullptr;
	//areaJuego = NULL;
	turnoActual = ' ';
	dificultad = 0;
	tipoJugador = 0;


	Celda* c0 = new Celda(0, 0);
	Celda* c1 = new Celda(0, 1);
	Celda* c2 = new Celda(0, 2);
	Celda* c3 = new Celda(1, 0);
	Celda* c4 = new Celda(1, 1);
	Celda* c5 = new Celda(1, 2);
	Celda* c6 = new Celda(2, 0);
	Celda* c7 = new Celda(2, 1);
	Celda* c8 = new Celda(2, 2);

	areaJuego.insertar(0, 0, c0);
	areaJuego.insertar(0, 1, c1);
	areaJuego.insertar(0, 2, c2);

	areaJuego.insertar(1, 0, c3);
	areaJuego.insertar(1, 1, c4);
	areaJuego.insertar(1, 2, c5);

	areaJuego.insertar(2, 0, c6);
	areaJuego.insertar(2, 1, c7);
	areaJuego.insertar(2, 2, c8);


}
Gato::~Gato() {
	delete humano;
	delete oponente;
	delete cpu;
}
void Gato::cargarJuego(bool mostrarIntroducciones) {
	srand(static_cast<unsigned int>(time(nullptr)));

	// Muestra la pantalla de inicio del juego con las instrucciones
	if (mostrarIntroducciones) {
		instrucciones();
	}

	// Determina si se juega contra la PC o contra el jugador
	tipoJugador = menuTipoJugador();
	if (tipoJugador == 2) {
		cargarPartidaVsCPU(true);
		jugarVsCPU();
	}
	else {
		cargarPartidaVsContrincante();
		jugarVsContrincante();
	}
}
void Gato::cargarPartidaVsCPU(bool cambiarDificultad) {
	humano = new Jugador();
	cpu = new Jugador("CPU", ' ', false);

	// Obtiene el símbolo del jugador 
	menuSimbolo();// AQUI SE PIDE EL NOMBRE DEL HUMANO ADEMAS
	if (cambiarDificultad) {
		// Determina la dificultad del juego, si se juega contra CPU
		dificultad = menuDificultad();
	}

	determinaTurno();
	// Utiliza un algoritmo para obtener el jugador que inicia

	system("cls");

	// Imprimimos el tablero en pantalla
	dibujar();
}
void Gato::cargarPartidaVsContrincante() {
	humano = new Jugador();
	oponente = new Jugador(); //jugador humano vs.

	menuSimboloHumano();
	determinaTurnoHumano();
	// Utiliza un algoritmo para obtener el jugador que inicia

	system("cls");

	// Imprimimos el tablero en pantalla
	dibujar();
}
void Gato::jugarVsCPU() {
	/* inicializamos el número de posibles casillas del tablero*/
	int casillas = 9;

	// Ciclo para Jugador vs PC
	while (!cpu->getEstado() && !humano->getEstado() && casillas > 0 && tipoJugador == 2) {

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

	muestraResultado(); //AQUI Cuando sale del while muestro resultado

	//Liberar espacio en memoria de los jugadores
	delete humano;
	delete cpu;

	menuFinal(); // Lo muestra al salir de while de juego
}
void Gato::jugarVsContrincante() {

	/* inicializamos el número de posibles casillas del tablero*/
	int casillas = 9;

	while (!oponente->getEstado() && !humano->getEstado() && casillas > 0 && tipoJugador == 1) {

		std::cout << "Turno de la " << turnoActual;
		std::cout << std::endl;

		// Verificamos si es el turno del jugador o el CPU. En cualquier caso, se anota el símbolo correspondiente
		// en el tablero en la posición dada
		realizarMovimientoHumano();

		// Disminuimos la cantidad de posiciones del tablero disponibles
		--casillas;

		// Si todavía no hay un ganador, entonces cambiamos el turno para el siguiente juego
		if (!hayGanadorHumano())
			cambiarTurno();

		system("cls");

		// Imprimimos el tablero en pantalla
		dibujar();

	} // Fin del while

	muestraResultadoHumano(); //AQUI Cuando sale del while muestro resultado

	//Liberar espacio en memoria de los jugadores
	humano = nullptr;
	delete humano;
	oponente = nullptr;
	delete oponente;

	menuFinal(); // Lo muestra al salir de while de juego
}
void Gato::setHumano(Jugador* j)
{
	humano = j;
}
void Gato::setCPU(Jugador* j)
{
	cpu = j;
}
void Gato::setTablero(Tablero t)
{
	areaJuego = t;
}
void Gato::instrucciones() {
	std::cout << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "BIENVENIDO AL JUEGO DEL GATO" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCCIONES: Debe seleccionar una posicion de fila (0 - 2) y columna (0 -2) para jugar." << std::endl;
	std::cout << std::endl;
	std::cout << " " << "0,0" << " " << "|" << " " << "0,1" << " " << "|" << " " << "0,2" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << " " << "1,0" << " " << "|" << " " << "1,1" << " " << "|" << " " << "1,2" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << " " << "2,0" << " " << "|" << " " << "2,1" << " " << "|" << " " << "2,2" << std::endl;
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
void Gato::menuSimboloHumano() {
	system("cls");
	std::cout << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "SELECCION DE SIMBOLO" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << std::endl << std::endl;

	char opcion;
	std::string nombreJugador, nombreJugador2;

	std::cout << "Digite su nombre, Jugador 1: ";
	std::getline(std::cin, nombreJugador);

	humano->setNombre(nombreJugador);

	std::cout << "Digite su nombre, Jugador 2: ";
	std::getline(std::cin, nombreJugador2);

	oponente->setNombre(nombreJugador2);

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
		oponente->setSimbolo(O);
	}
	else {
		humano->setSimbolo(O);
		oponente->setSimbolo(X);
	}

}
int Gato::menuTipoJugador() {
	system("cls");
	std::cout << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "SELECCION DE TIPO DE JUGADOR" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << std::endl << std::endl;

	char opcion;

	do {
		std::cout << "Seleccione el tipo de jugador " << std::endl;
		std::cout << "1. P v P" << std::endl;
		std::cout << "2. P v CPU" << std::endl;
		std::cout << "        Opcion: ";
		std::cin >> opcion;
		std::cout << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (opcion != '1' && opcion != '2');


	if (opcion == '1') return 1;
	else if (opcion == '2') return 2;
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
		std::cout << "3. IA" << std::endl;
		std::cout << "        Opcion: ";
		std::cin >> opcion;
		std::cout << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (opcion != '1' && opcion != '2' && opcion != '3');

	//return opcion == '1' ? FACIL : DIFICIL;
	if (opcion == '1')
		return FACIL;
	if (opcion == '2')
		return DIFICIL;
	else
		return IA;
}
void Gato::menuFinal() {

	//Creamos un nuevo tablero.
	system("cls");
	Tablero nuevoTablero;
	setTablero(nuevoTablero);

	char opcion;

	do {
		std::cout << "Seleccione que desea realizar " << std::endl;
		std::cout << "1. Volver al menu de seleccion de tipo de Jugador " << std::endl;
		std::cout << "2. Cambiar nivel para jugar, vs la CPU" << std::endl;
		std::cout << "3. Jugar de nuevo mismo nivel" << std::endl;
		std::cout << "4. Salir" << std::endl;
		std::cout << "        Opcion: ";
		std::cin >> opcion;
		std::cout << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4');

	if (opcion == '1') {
		cargarJuego(false);
	}
	if (opcion == '2') {
		tipoJugador = 2;
		cargarPartidaVsCPU(true);
		jugarVsCPU();
	}
	if (opcion == '3') {
		if (tipoJugador == 2) {
			cargarPartidaVsCPU(false);
			jugarVsCPU();
		}
		else {
			cargarPartidaVsContrincante();
			jugarVsContrincante();
		}
	}

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
void Gato::determinaTurnoHumano() {
	// Genera un número aleatorio que determina el jugador que comienza primero
	// Si el número es PAR, inicia el jugador, en caso contrario inicia el CPU
	int turnoAleatorio = rand() % 100 + 1;
	if (turnoAleatorio % 2 == 0)
		turnoActual = humano->getSimbolo();     // Inicia el jugador
	else
		turnoActual = oponente->getSimbolo();   // Inicia el CPU

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
void Gato::realizarMovimientoHumano() {
	short int i, j;
	bool valida;
	if (turnoActual == humano->getSimbolo()) {
		do {
			std::cout << std::endl << std::endl << "   POSICION: ";
			std::cin >> i;
			std::cin >> j;
			if (!(valida = areaJuego.validarPosicion(i, j)))
				std::cout << std::endl << std::endl << "    MOVIMIENTO INVALIDO. INTENTE NUEVAMENTE";
		} while (!valida);

		areaJuego.actualizar(i, j, humano->getSimbolo());

		if (areaJuego.encuentraGanador(humano->getSimbolo()))
			humano->setEstado(true);
	}
	else
		if (turnoActual == oponente->getSimbolo()) {
			do {
				std::cout << std::endl << std::endl << "   POSICION: ";
				std::cin >> i;
				std::cin >> j;
				if (!(valida = areaJuego.validarPosicion(i, j)))
					std::cout << std::endl << std::endl << "    MOVIMIENTO INVALIDO. INTENTE NUEVAMENTE";
			} while (!valida);

			areaJuego.actualizar(i, j, oponente->getSimbolo());

			if (areaJuego.encuentraGanador(oponente->getSimbolo()))
				oponente->setEstado(true);
		}

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
			if (!(valida = areaJuego.validarPosicion(i, j)))
				std::cout << std::endl << std::endl << "    MOVIMIENTO INVALIDO. INTENTE NUEVAMENTE";
		} while (!valida);

		areaJuego.actualizar(i, j, humano->getSimbolo());

		if (areaJuego.encuentraGanador(humano->getSimbolo()))
			humano->setEstado(true);
	}
	else {
		if (dificultad == FACIL)
			movimientoFacilCpu();
		else if (dificultad == DIFICIL)
			mejorMovimientoCpu();
		else if (dificultad == IA)
			realizaMovimientoIA();

		if (areaJuego.encuentraGanador(cpu->getSimbolo()))
			cpu->setEstado(true);
	}
}
bool Gato::hayGanador() {
	if (cpu->getEstado() || humano->getEstado())
		return true;
	return false;
}
bool Gato::hayGanadorHumano()
{
	if (oponente->getEstado() || humano->getEstado())
		return true;
	return false;
}
void Gato::dibujar() {
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
void Gato::muestraResultadoHumano() {
	// Muestra el ganador del juego, si lo hay. En caso contrario, declara empate.
	if (oponente->getEstado())
		std::cout << "El GANADOR ES EL " << oponente->getNombre();
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
	} while (!areaJuego.validarPosicion(i, j));

	areaJuego.actualizar(i, j, cpu->getSimbolo());
}
void Gato::realizaMovimientoIA() {
	short int i;
	short int j;
	Celda aux = mejorMovimientoMini();

	do {
		i = aux.getPosX();
		j = aux.getPosY();
	} while (!areaJuego.validarPosicion(i, j));

	areaJuego.actualizar(i, j, cpu->getSimbolo());

}
void Gato::mejorMovimientoCpu() {
	short int i = 0;
	short int j = 0;
	bool encontro = false;

	// Definimos los mejores movimientos en un vector. Se utiliza en caso de que no exista un ganador
	//const short int MEJORES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 }; //{1,1},{0,0},{0,2}

	Celda mejores[] = { Celda(1,1), Celda(0,0), Celda(0,2), Celda(2,0), Celda(2,2), Celda(0,1), Celda(1,0), Celda(1,2), Celda(2,1) };

	//00 01 02
	// 0  1  2
	//10 11 12
	// 3  4  5
	//20 21 22
	// 6  7  8

	// Verificamos si la CPU es ganadora en el siguiente movimiento. El algoritmo prueba todos los movimientos
	// posibles hasta que encuentre una posición ganadora o pruebe todas las posibilidades.
	while (!encontro && i < CASILLAS) { //NO SIRVE CAMBIAR
		while (!encontro && j < CASILLAS) {
			if (areaJuego.validarPosicion(i, j)) {
				areaJuego.actualizar(i, j, cpu->getSimbolo());
				encontro = areaJuego.encuentraGanador(cpu->getSimbolo());
				areaJuego.actualizar(i, j, '_');
			}
			if (!encontro)
				++j;
		}
		if (!encontro)
			++i;
	}

	// Ahora verificamos si el jugador gana en el próximo movimiento. En ese caso el CPU realiza el
	// movimiento para evitarlo
	if (!encontro) {
		i = 0;
		j = 0;
		while (!encontro && i < CASILLAS && j < CASILLAS) {
			while (!encontro && i < CASILLAS && j < CASILLAS) {
				if (areaJuego.validarPosicion(i, j)) {
					areaJuego.actualizar(i, j, humano->getSimbolo());
					encontro = areaJuego.encuentraGanador(humano->getSimbolo());
					areaJuego.actualizar(i, j, '_');
				}
				if (!encontro)
					++j;
			}
			if (!encontro)
				++i;
		}
	}

	// Si el CPU ni el jugador ganan en el siguiente movimiento, la CPU hace la jugada en la mejor casilla disponible
	// en el siguiente orden: centro, esquinas, lateral
	if (!encontro) {
		i = 0;
		j = 0;

		while (!encontro && i < 9) {
			if (areaJuego.validarPosicion(mejores[i].getPosX(), mejores[j].getPosY())) {
				encontro = true;
				i = mejores[i].getPosX();
				j = mejores[j].getPosY();
			}
			else {
				++i;
				++j;
			}
		}
	}

	areaJuego.actualizar(i, j, cpu->getSimbolo());
}
Celda Gato::mejorMovimientoMini()
{
	int mejorValor = -1;
	Celda mejorMov = Celda(0, 0);
	std::vector<std::vector<Celda*>> aux = areaJuego.getTablero();

	for (int i = 0; i < CASILLAS; i++) {
		for (int j = 0; j < CASILLAS; j++) {
			/*revisa si la posicion esta disponible*/
			if (aux[i][j]->getSimbolo() == '_') {

				/*hace movimiento con ficha de cpu*/
				aux[i][j]->setSimbolo(cpu->getSimbolo());

				/*evalua el mejor movimiento en esa posicion*/
				int valorMov = minimax(areaJuego, 0, false);

				/*deshace el movimiento con ficha de cpu*/
				aux[i][j]->setSimbolo('_');

				/*Si el movimiento actual es mayor a el mejor caso
				 asigna a bestMove las coordenadas del movimiento y
				 cambia el valor de bestVal a el valor actual
			   */
				if (valorMov > mejorValor) {
					mejorMov.setPosX(i);
					mejorMov.setPosY(j);
				}
			}
		}
	}
	return mejorMov;
}
int Gato::evaluaTablero(Tablero t)
{
	/*funcion heuristica/evaluacion para Tic-Tac-Toe
	  consiste en asignar un valor positivo al tablero si Max gana
	  un valor negativo si Min gana, y un valor neutro si hay empate.

	  condiciones de gane:
	  -3 en fila
	  -3 en columna
	  -3 en diagonal
  */
	std::vector<std::vector<Celda*>> aux = t.getTablero();

	for (int i = 0; i < 3; i++) {
		/*recorrido de fila para revisar victoria*/

		if (aux[i][0]->getSimbolo() == aux[i][1]->getSimbolo() && aux[i][1]->getSimbolo() == aux[i][2]->getSimbolo()) {

			/*valor positivo si es X*/
			if (aux[i][0]->getSimbolo() == humano->getSimbolo()) return -1;

			/*valor negativo si es O*/
			else if (aux[i][0]->getSimbolo() == cpu->getSimbolo()) return 1;

		}
	}

	for (int j = 0; j < 3; j++) {

		/*recorrido de columna para revisar victoria*/
		if (aux[0][j]->getSimbolo() == aux[1][j]->getSimbolo() && aux[1][j]->getSimbolo() == aux[2][j]->getSimbolo()) {

			/*valor positivo si es X*/
			if (aux[0][j]->getSimbolo() == humano->getSimbolo()) return -1;

			/*valor negativo si es O*/
			else if (aux[0][j]->getSimbolo() == cpu->getSimbolo()) return 1;

		}
	}

	if (aux[0][0]->getSimbolo() == aux[1][1]->getSimbolo() && aux[1][1]->getSimbolo() == aux[2][2]->getSimbolo()) {
		/*Revisa si hay victoria en diagonal izq der*/
		/*valor positivo si es X*/
		if (aux[0][0]->getSimbolo() == humano->getSimbolo()) return -1;

		/*valor negativo si es O*/
		else if (aux[0][0]->getSimbolo() == cpu->getSimbolo()) return 1;
	}

	if (aux[0][2]->getSimbolo() == aux[1][1]->getSimbolo() && aux[1][1]->getSimbolo() == aux[2][0]->getSimbolo()) {
		/*Revisa si hay victoria en diagnoal der izq*/

		/*valor positivo si es X*/
		if (aux[0][2]->getSimbolo() == humano->getSimbolo()) return -1;

		/*valor negativo si es O*/
		else if (aux[0][2]->getSimbolo() == cpu->getSimbolo()) return 1;
	}

	/*si hay empate o no gana nadie aun retorna 0*/
	return 0;
}
int Gato::minimax(Tablero tablero, int depth, bool esMax)
{
	/*Considera todos los casos posibles del juego y
	retorna el valor de la tabla. Usa la funcion evaluate para
	evaluar el valor de la tabla.

	casos
	1-gana Max
	2-gana Min
	3-no quedan mas movimientos
	4-turno de max
	5-turno de min
	*/

	int puntuacion = evaluaTablero(tablero);
	/*caso 1*/
	if (puntuacion == 1) return puntuacion;

	/*caso 2*/
	if (puntuacion == -1) return puntuacion;

	/*caso 3*/
	if (tablero.movimientosDisponibles() == false) return 0;

	/*caso 4*/
	std::vector<std::vector<Celda*>> aux = tablero.getTablero();
	if (esMax) {
		int mejor = -100;
		/*ciclos para recorrer el tablero*/
		for (int i = 0; i < CASILLAS; i++) {
			for (int j = 0; j < CASILLAS; j++) {

				/*revisa si la posicion esta disponible*/
				if (aux[i][j]->getSimbolo() == '_') {

					/*hace movimiento con ficha de humano*/
					aux[i][j]->setSimbolo(cpu->getSimbolo());

					/*llama a minimax recursivamente y escoge el valor maximo*/
					mejor = std::max(mejor, minimax(tablero, depth + 1, false));

					/*deshace el movimiento con ficha de humano*/
					aux[i][j]->setSimbolo('_');
				}
			}
		}
		return mejor;
	}

	/*caso 5*/
	else {
		int mejor = 100;
		/*ciclos para recorrer el tablero*/
		for (int i = 0; i < CASILLAS; i++) {
			for (int j = 0; j < CASILLAS; j++) {

				/*revisa si la posicion esta disponible*/
				if (aux[i][j]->getSimbolo() == '_') {

					/*hace movimiento con ficha de cpu*/
					aux[i][j]->setSimbolo(humano->getSimbolo());

					/*llama a minimax recursivamente y escoge el valor maximo*/
					mejor = std::min(mejor, minimax(tablero, depth + 1, true));

					/*deshace el movimiento con ficha de cpu*/
					aux[i][j]->setSimbolo('_');
				}
			}
		}
		return mejor;
	}

}