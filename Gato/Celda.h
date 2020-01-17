#ifndef CELDA_H
#define CELDA_H



class Celda
{
private:
    int posX;
    int posY;
    char simbolo;
public:
    Celda();
    Celda(int x, int y);
    Celda(int x, int y, char s);
    ~Celda();

    void setPosX(int x);
    void setPosY(int y);
    void setSimbolo(char s);
    int getPosX();
    int getPosY();
    char getSimbolo();
};

#endif // !CELDA_H
