#include "Celda.h"

Celda::Celda(int x, int y, char s): posX(0), posY(0), simbolo(' '){}

Celda::Celda(int x, int y, char s): posX(x), posY(y), simbolo(s) {}

Celda::~Celda() {}

void Celda::setPosX(int x){
    posX = x;
}
void Celda::setPosY(int y){
    posY = y;
}
char Celda::getSimbolo()
{
    return simbolo;
}
void Celda::setSimbolo(char s) {
    simbolo = s;
}
int Celda::getPosX() {
    return posX;
}
int Celda::getPosY() {
    return posY;
}
char Celda::getSimbolo() {
    return simbolo; 
}