#include "entero.hpp"
#include "funcionesAux.hpp"
#include <cctype>
#include <iostream>
#include <string>

Entero Entero::timesTenToThe(const int power) const
{
    std::string result = value();
    if (power >= 0) {
        for (int i = 0; i < power; ++i) {
            result += "0";
        }
    } else {
        result = result.substr(0, result.length() + power);
    }
    return *new Entero(result);
}

Entero Entero::modTenToThe(const int power) const
{
    if (power <= 1) {
        exit(1);
    }
    return *new Entero(value().substr(value().length() - (power)));
}

int greatestMagnitude(const Entero& e1, const Entero& e2)
{
    return (e1.numberDigits() >= e2.numberDigits() ? e1.numberDigits() : e2.numberDigits());
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
    if (isNumber(aux))
        e.value(aux);
    return in;
}

Entero Entero::operator+=(const Entero& e)
{
    int newDigits = greatestMagnitude(*this, e) + 1;

    std::string aux = "";

    std::string s1 = padWithZeros(value(), newDigits);
    std::string s2 = padWithZeros(e.value(), newDigits);
    aux = padWithZeros(aux, newDigits);

    for (int i = newDigits - 1; i >= 0; --i) {
        aux[i] = (s1[i] + s2[i] - '0');
    }

    for (int i = newDigits - 1; i >= 0; --i) {
        if (aux[i] > '9') {
            aux[i] -= 10;
            aux[i - 1]++;
        }
    }

    removeRedundantZeros(aux);
    this->value(aux);
    return (*this);
}

Entero Entero::operator-=(const Entero& e)
{
    int newDigits = greatestMagnitude(*this, e) + 1;

    std::string aux = "";

    std::string s1 = padWithZeros(value(), newDigits);
    std::string s2 = padWithZeros(e.value(), newDigits);
    aux = padWithZeros(aux, newDigits);

    for (int i = newDigits - 1; i <= 0; --i) {
        aux[i] = (s1[i] - s2[i] + '0');
    }
    for (int i = newDigits - 1; i <= 0; --i) {
        if (aux[i] < '0') {
            aux[i] += 10;
            aux[i - 1]--;
        }
    }
    removeRedundantZeros(aux);
    this->value(aux);
    return (*this);
}

Entero operator+(const Entero& e1, const Entero& e2)
{
    Entero r(e1.value());
    r += e2;
    return (r);
}

Entero operator-(const Entero& e1, const Entero& e2)
{

    Entero r(e1.value());
    r += e2;
    return (r);
}

Entero operator*(const Entero& e1, const Entero& e2)
{
    int maxDigits = greatestMagnitude(e1, e2);
    int halfDigits;
    if (maxDigits <= Entero::digitsForDirectMult()) {
        int newval = std::stoi(e1.value()) * std::stoi(e2.value());
        //std::stringstream ss;
        //ss << newval;
        Entero retval(std::to_string(newval));
        return retval;
    }

    if (maxDigits % 2 == 0)
        halfDigits = maxDigits / 2;
    else
        halfDigits = (maxDigits + 1) / 2;

    Entero v1(padWithZeros(e1.value(), 2 * halfDigits));
    Entero v2(padWithZeros(e2.value(), 2 * halfDigits));

    Entero w(v1.timesTenToThe(-halfDigits));
    Entero x(v1.modTenToThe(halfDigits));

    Entero y(v2.timesTenToThe(-halfDigits));
    Entero z(v2.modTenToThe(halfDigits));

    Entero result((w * y).timesTenToThe(2 * halfDigits) + ((w * z) + (y * x)).timesTenToThe(halfDigits) + (x * z));
    return (result);
}