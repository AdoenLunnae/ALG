#ifndef ENTERO_HPP
#define ENTERO_HPP
#include <iostream>
#include <string>
class Entero {
private:
    std::string value_;
    const static int digitsForDirectMult_ = 4;

public:
    Entero()
        : value_("0"){};
    Entero(const std::string& value)
        : value_(value){};
    Entero(const Entero& e)
        : value_(e.value()){};

    inline std::string value() const { return value_; }
    inline static int digitsForDirectMult() { return digitsForDirectMult_; }

    inline int numberDigits() const { return value_.length(); }
    inline void value(const std::string& value) { value_ = value; }
    inline bool isSmall() { return numberDigits() < digitsForDirectMult(); }

    Entero operator+=(const Entero& e);
    Entero operator-=(const Entero& e);

    Entero operator++()
    {
        *this += Entero("1");
        return *this;
    }

    Entero operator++(int)
    {
        Entero retval(*this);
        *this += Entero("1");
        return retval;
    }

    Entero operator--()
    {
        *this -= Entero("1");
        return *this;
    }

    Entero operator--(int)
    {
        Entero retval(*this);
        *this -= Entero("1");
        return retval;
    }

    Entero timesTenToThe(const int power) const;
    Entero modTenToThe(const int power) const;

    Entero factorial() const;
};

std::ostream& operator<<(std::ostream& out, const Entero& e);
std::istream& operator>>(std::istream& in, Entero& e);

Entero operator+(const Entero& e1, const Entero& e2);
Entero operator*(const Entero& e1, const Entero& e2);

bool operator<=(const Entero& e1, const Entero& e2);
#endif