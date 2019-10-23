#include "entero.hpp"
#include "funcionesbajonivel.hpp"
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

bool checkCorrect(const std::string value)
{
    for (int i = 0; i < value.length(); ++i) {
        if (!isdigit(value[i]))
            return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const Entero& e)
{
    out << e.value();
    return out;
}
std::istream& operator>>(std::istream& in, Entero& e)
{
    std::string aux;
    in >> aux;
    if (checkCorrect(aux))
        e.value(aux);
    return in;
}

void calculateCarry(char* c)
{
    for (int i = strlen(c) - 1; i >= 0; --i) {
        while (c[i] >= '0' + 10) {
            c[i] -= 10;
            c[i - 1]++;
        }
    }
}

Entero operator+(const Entero& e1, const Entero& e2)
{
    int newDigits;
    if (e1.numberDigits() >= e2.numberDigits())
        newDigits = e1.numberDigits() + 1;
    else
        newDigits = e2.numberDigits() + 1;

    char* aux = reservarCadena(newDigits);
    char* v1 = reservarCadena(e1.numberDigits());
    char* v2 = reservarCadena(e2.numberDigits());
    strcpy(v1, e1.value().c_str());
    strcpy(v2, e2.value().c_str());
    agregarCerosDelante(v1, newDigits - strlen(v1));
    agregarCerosDelante(v2, newDigits - strlen(v2));
    for (int i = 0; i < newDigits; ++i) {
        aux[i] = (v1[i] + v2[i] - '0');
    }
    calculateCarry(aux);
    quitarCerosNoSignificativos(aux);
    return (*new Entero(std::string(aux)));
}

Entero operator*(const Entero& e1, const Entero& e2)
{
    return *new Entero("0");
}