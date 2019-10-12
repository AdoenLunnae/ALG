#ifndef _CASILLA_HPP_
#define _CASILLA_HPP_

#include "Board.hpp"

class Square{
    private:
        int _f;
        int _c;
    
    public:
        inline Square(const int f, const int c):_f(f), _c(c){};

        inline bool in(const Board &b) const{
            return((f() >= 0) && (c() >= 0) && (f() < b.size()) && (c() < b.size()));
        }

        inline int f() const {return _f;}
        inline int c() const {return _c;}

        inline bool operator==(const Square &s) const{
            return((s.f() == f()) && (s.c() == c()));
        }
};

#endif