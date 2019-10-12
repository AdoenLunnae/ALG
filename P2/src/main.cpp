#include <iostream>
#include "Square.hpp"
#include "Board.hpp"
#include "Paths.hpp"

int main(){
    Square origin(1, 4), goal(7, 6);
    Board b(8);

    std::cout << pathFromRow(0, goal, b) << "\n";
}