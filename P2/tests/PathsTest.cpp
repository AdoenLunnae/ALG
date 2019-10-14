#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Paths.hpp"
#include "Square.hpp"
#include "Board.hpp"
#include "showPaths.hpp"
#include <vector>
#include <iostream>
using std::vector;

TEST_CASE("path from a row to a square"){
    vector<vector<Square>> v;
    SUBCASE("valid goal returns the number and assigns the vector"){
        CHECK(path(0, Square(7,7), Board(8), v) == 205);
        CHECK(v.size() == 205);
        v.clear();
        CHECK(path(0, Square(7,6), Board(8), v) == 269);
        CHECK(v.size() == 269);
        v.clear();
        CHECK(path(0, Square(3,0), Board(8), v) == 6);
        CHECK(v.size() == 6);
        v.clear();
    }
    SUBCASE("invalid goal returns 0"){
        CHECK(path(0, Square(-1, 2), Board(8)) == 0);
        CHECK(path(0, Square(8, 5), Board(5)) == 0);
    }
    v.clear();
    SUBCASE("goal behind origin row returns 0"){
        CHECK(path(3, Square(1, 3), Board(8)) == 0);
    }
    SUBCASE("goal in origin row returns 1"){
        CHECK(path(0, Square(0, 3), Board(8)) == 1);
    }
}
/*
TEST_CASE("path between two squares"){

}
*/