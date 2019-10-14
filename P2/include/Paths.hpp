#ifndef _PATHS_HPP_
#define _PATHS_HPP_
#include "Square.hpp"
#include "Board.hpp"
#include <vector>

    int path(const int rowOrigin,
        const Square &goal, 
        const Board &b, 
        std::vector<std::vector<Square>> &paths = *new std::vector<std::vector < Square > >, 
        std::vector<Square> currPath = *new std::vector<Square>);
    
    int path(const Square &origin,
        const Square &goal, 
        const Board &b, 
        std::vector<std::vector<Square>> &paths = *new std::vector<std::vector < Square > >, 
        std::vector<Square> currPath = *new std::vector<Square>);
#endif