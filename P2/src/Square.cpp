#include "Square.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Square &s){
    out << "(" << s.f() << ", " << s.c() << ")";
}
