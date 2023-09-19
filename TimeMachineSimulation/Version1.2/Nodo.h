#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    Nodo* PtrPasado;
    std::string evento;
    std::string cientifico;
    int datos;
    Nodo* PtrFuturo;

    Nodo(std::string evento, std::string cientifico, int datos);
};

#endif
