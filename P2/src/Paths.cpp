#include "Board.hpp"
#include "Square.hpp"
#include <vector>
#include <cmath>
using std::vector;

int path(const Square &origin, const Square &position, const Square &goal, const Board &board){
    if(position == goal){
        return 0;
    }
    int result = 0;
    int cvals[4] = {-2, -1, 1, 2};

    for(int i = 0; i < 4; ++i){
        Square aux(3-abs(cvals[i]), cvals[i]);
        if(aux.in(board)){
            result += path(origin, aux, goal, board);
        }
    }
    return result;
}

int pathFromRow(const int rowOrigin, const Square &goal, const Board &b){
    if(rowOrigin == goal.f()-1){
        return (goal.c() < 2 || goal.c() > b.size() - 3)?1:2;
    }
    if(rowOrigin == goal.f()-2){
        return (goal.c() < 1 || goal.c() > b.size() - 2)?1:2;
    }
    int cvals[4] = {-2, -1, 1, 2};
    int result = 0;
    for(int i = 0; i < 4; ++i){
        Square aux(goal.f()-(3-abs(cvals[i])), goal.c()-(cvals[i]));
        if(aux.in(b)){
            result++;
            result += pathFromRow(rowOrigin, aux, b);
        }
    }
    return result;
}