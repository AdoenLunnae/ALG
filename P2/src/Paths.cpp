#include "Board.hpp"
#include "Square.hpp"
#include <vector>
#include <cmath>
using std::vector;

int path(const int rowOrigin, const Square &goal, const Board &b, vector<vector<Square>> &paths, vector<Square> currPath){

    if(!goal.in(b) || goal.f() < rowOrigin) return 0;
    currPath.push_back(goal);
    if(rowOrigin == goal.f()){
        paths.push_back(currPath);
        return 1;
    }
    int cVals[4] = {-2, -1, 1, 2};
    int result = 0;
    
    for(int i = 0; i < 4; ++i){
        Square aux(goal.f()-(3-abs(cVals[i])), goal.c()-(cVals[i]));
        result += path(rowOrigin, aux, b, paths, currPath);

    }

    return result;
}   


int path(const Square &origin, const Square &goal, const Board &b, vector<vector<Square>> &paths, vector<Square> currPath){

    if(!goal.in(b) || goal.f() < origin.f()) return 0;
    currPath.push_back(goal);
    if(origin == goal){
        paths.push_back(currPath);
        return 1;
    }
    int cVals[4] = {-2, -1, 1, 2};
    int result = 0;
    
    for(int i = 0; i < 4; ++i){
        Square aux(goal.f()-(3-abs(cVals[i])), goal.c()-(cVals[i]));
        result += path(origin, aux, b, paths, currPath);

    }

    return result;
}