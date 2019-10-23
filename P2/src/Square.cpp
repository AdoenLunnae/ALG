#include "Square.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Square &s){
    out << "(" << s.f() << ", " << s.c() << ")";
}

std::ofstream& operator<<(std::ofstream& f, const Square &s){
    f << "(" << s.f() << ", " << s.c() << ")";    
}