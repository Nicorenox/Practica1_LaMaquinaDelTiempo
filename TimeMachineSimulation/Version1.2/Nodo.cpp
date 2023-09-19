#include "Nodo.h"

Nodo::Nodo(std::string evento, std::string cientifico, int datos) {
    this->evento = evento;
    this->cientifico = cientifico;
    this->datos = datos;
    PtrPasado = nullptr;
    PtrFuturo = nullptr;
}
