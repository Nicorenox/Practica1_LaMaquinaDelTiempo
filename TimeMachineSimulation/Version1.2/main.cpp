#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Nodo.h"

class ListaEventos {
public:
    Nodo* primerNodo;
    Nodo* ultimoNodo;
    int tamano;

    ListaEventos() {
        primerNodo = nullptr;
        ultimoNodo = nullptr;
        tamano = 0;
    }

    void agregarNodo(Nodo* nuevoNodo) {
        if (tamano == 0) {
            primerNodo = nuevoNodo;
            ultimoNodo = nuevoNodo;
        } else {
            nuevoNodo->PtrPasado = ultimoNodo;
            ultimoNodo->PtrFuturo = nuevoNodo;
            ultimoNodo = nuevoNodo;
        }
        tamano++;
    }

    void mostrarListaSimplificada() {
        Nodo* actual = primerNodo;
        std::cout << "|";
        while (actual != nullptr) {
            if (actual->evento == "A" || actual->evento == "B" || actual->evento == "C") {
                std::cout << actual->datos << "|" << actual->cientifico[0] << "|" << actual->evento << "| -> ";
            }
            actual = actual->PtrFuturo;
        }
        std::cout << "NULL|" << std::endl;
    }

    void mostrarTodosLosNodos() {
        Nodo* actual = primerNodo;
        std::cout << "[";
        while (actual != nullptr) {
            std::string evento = (actual->evento == "A" || actual->evento == "B" || actual->evento == "C") ? actual->evento : "-";
            std::cout << actual->datos << "|" << actual->cientifico[0] << "|" << evento;
            if (actual->PtrFuturo != nullptr) {
                std::cout << "-> ";
            } else {
                std::cout << "|";
            }
            actual = actual->PtrFuturo;
        }
        std::cout << "]" << std::endl;
    }

    int contarEventos(std::string tipoEvento) {
        int contador = 0;
        Nodo* actual = primerNodo;
        while (actual != nullptr) {
            if (actual->evento == tipoEvento) {
                contador++;
            }
            actual = actual->PtrFuturo;
        }
        return contador;
    }
};

bool esPrimo(int numero) {
    if (numero <= 1) return false;
    if (numero <= 3) return true;

    if (numero % 2 == 0 || numero % 3 == 0) return false;

    for (int i = 5; i * i <= numero; i += 6) {
        if (numero % i == 0 || numero % (i + 2) == 0) return false;
    }

    return true;
}

int generarNumeroAleatorio() {
    int numero = rand() % 100 + 1;
    if (esPrimo(numero)) {
        if (rand() % 2 == 0) {
            numero++;
            if (numero > 100) {
                numero -= 2;
            }
        }
    }
    return numero;
}

int generarCientificoAleatorio() {
    return rand() % 2 + 1;
}

int main() {
    srand(time(0));
    ListaEventos lista;
    bool compartidos = false;
    int datosA = -1, datosB = -1;

    while (true) {
        int datos = generarNumeroAleatorio();
        std::string cientifico = (generarCientificoAleatorio() == 1) ? "Einstein" : "Rosen";
        std::string evento = "";

        if (esPrimo(datos)) {
            if (evento.empty()) {
                if (lista.contarEventos("A") == 0) {
                    evento = "A";
                } else if (lista.contarEventos("B") == 0) {
                    evento = "B";
                } else {
                    evento = "C";
                    if (compartidos || lista.contarEventos("C") > 0) {
                        compartidos = (rand() % 2 == 0);
                        if (!compartidos) {
                            datosA = generarNumeroAleatorio();
                            datosB = generarNumeroAleatorio();
                        }
                    }
                }
            }
        }

        Nodo* nuevoNodo = new Nodo(evento, cientifico, datos);
        lista.agregarNodo(nuevoNodo);

        if (evento == "A" || evento == "B" || evento == "C") {
            std::cout << "Se ha producido un evento de Tipo " << evento << ": ";
            lista.mostrarListaSimplificada();
            if (evento == "C") {
                if (compartidos) {
                    std::cout << "Se ha viajado en el timepo y Se han compartido datos" << std::endl;
                } else {
                    std::cout << "Se ha viajado en el timepo y No se han compartido datos" << std::endl;
                    while (true) {
                        if (esPrimo(datosA) && esPrimo(datosB) && datosA != datosB) {
                            Nodo* nuevoNodoA = new Nodo("A", "Einstein", datosA);
                            Nodo* nuevoNodoB = new Nodo("B", "Einstein", datosB);
                            lista.agregarNodo(nuevoNodoA);
                            lista.agregarNodo(nuevoNodoB);
                            std::cout << "Se han encontrado nuevos eventos A y B" << std::endl;
                            break;
                        } else {
                            datosA = generarNumeroAleatorio();
                            datosB = generarNumeroAleatorio();
                        }
                    }
                }
            }
        }

        if (evento == "C" && compartidos) {
            break;
        }
    }

    std::cout << "Total de eventos: " << lista.tamano << std::endl;
    lista.mostrarTodosLosNodos();

    return 0;
}
