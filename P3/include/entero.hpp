#ifndef ENTERO_HPP
#define ENTERO_HPP
#include <iostream>
#include <string>
class Entero {
private:
    std::string value_;
    const static int digitsForDirectMult_ = 4;

public:
    Entero(const std::string& value)
        : value_(value){};

    inline std::string value() const { return value_; }
    inline int digitsForDirectMult() const { return digitsForDirectMult_; }

    inline int numberDigits() const { return value_.length(); }
    inline void value(const std::string& value) { value_ = value; }
};

std::ostream& operator<<(std::ostream& out, const Entero& e);
std::istream& operator>>(std::istream& in, Entero& e);

Entero operator+(const Entero& e1, const Entero& e2);
Entero operator*(const Entero& e1, const Entero& e2);
#endif