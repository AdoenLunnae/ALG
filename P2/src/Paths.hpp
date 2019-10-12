#ifndef _PATHS_HPP_
#define _PATHS_HPP_
#include "Square.hpp"
#include "Board.hpp"
    int pathFromRow(const int rowOrigin, const Square &goal, const Board &b);
    int path(const Square &origin, const Square &position, const Square &goal, const Board &board);
#endif