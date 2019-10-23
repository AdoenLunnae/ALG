#include "Board.hpp"
#include "Square.hpp"
#include <cmath>
#include <vector>
using std::vector;

int path(const int rowOrigin, const Square& goal, const Board& b, vector<vector<Square>>& paths, vector<Square> currPath)
{

    if (!goal.in(b) || goal.f() < rowOrigin)
        return 0; //base

    currPath.push_back(goal);

    if (rowOrigin == goal.f()) {
        paths.push_back(currPath);
        return 1;
    }

    int result = 0;
    result += path(rowOrigin, Square(goal.f() - 1, goal.c() - 2), b, paths, currPath);
    result += path(rowOrigin, Square(goal.f() - 2, goal.c() - 1), b, paths, currPath);
    result += path(rowOrigin, Square(goal.f() - 2, goal.c() + 1), b, paths, currPath);
    result += path(rowOrigin, Square(goal.f() - 1, goal.c() + 2), b, paths, currPath);

    return result;
}

int path(const Square& origin, int goalRow, const Board& b, vector<vector<Square>>& paths, vector<Square> currPath)
{

    if (!origin.in(b) || goalRow < origin.f())
        return 0;

    currPath.push_back(origin);

    if (origin.f() == goalRow) {
        paths.push_back(currPath);
        return 1;
    }

    int result = 0;
    result += path(Square(origin.f() + 1, origin.c() - 2), goalRow, b, paths, currPath);
    result += path(Square(origin.f() + 2, origin.c() - 1), goalRow, b, paths, currPath);
    result += path(Square(origin.f() + 2, origin.c() + 1), goalRow, b, paths, currPath);
    result += path(Square(origin.f() + 1, origin.c() + 2), goalRow, b, paths, currPath);

    return result;
}