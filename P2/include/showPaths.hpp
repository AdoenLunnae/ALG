#ifndef _SHOW_PATHS_HPP_
#define _SHOW_PATHS_HPP_
#include <vector>
#include "Board.hpp"
#include "Square.hpp"
    void showPath(const std::vector<Square> &path, const Board &b);
    void showPaths(const std::vector<std::vector<Square>> &paths, const Board &b);
#endif