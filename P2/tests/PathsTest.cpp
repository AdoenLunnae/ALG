#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Paths.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "doctest.h"
#include "showPaths.hpp"
#include <iostream>
#include <vector>
using std::vector;

TEST_CASE("path from a row to a square")
{
    vector<vector<Square>> v;
    SUBCASE("valid goal returns the number and assigns the vector")
    {
        CHECK_EQ(path(0, Square(7, 7), Board(8), v), 205);
        CHECK_EQ(v.size(), 205);
        v.clear();
        CHECK_EQ(path(0, Square(7, 6), Board(8), v), 269);
        CHECK_EQ(v.size(), 269);
        v.clear();
        CHECK_EQ(path(0, Square(3, 0), Board(8), v), 6);
        CHECK_EQ(v.size(), 6);
        v.clear();
    }
    SUBCASE("invalid goal returns 0")
    {
        CHECK_EQ(path(0, Square(-1, 2), Board(8)), 0);
        CHECK_EQ(path(0, Square(8, 5), Board(5)), 0);
    }
    v.clear();
    SUBCASE("goal behind origin row returns 0")
    {
        CHECK_EQ(path(3, Square(1, 3), Board(8)), 0);
    }
    SUBCASE("goal in origin row returns 1")
    {
        CHECK_EQ(path(0, Square(0, 3), Board(8)), 1);
    }
}

TEST_CASE("path from a square to a row")
{
    CHECK_EQ(path(Square(0, 0), 7, Board(8)), 205);
    CHECK_EQ(path(Square(0, 1), 7, Board(8)), 269);
}
