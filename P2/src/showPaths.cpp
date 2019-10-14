#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Square.hpp"
#include "Board.hpp"

void showPath(const std::vector<Square> &path, const Board &b){
    std::string division = "|";
    for(int i = 0; i < b.size(); ++i){
        division += "===|";
    }
    std::cout << division << '\n';
    for(int i = 0; i < b.size(); ++i){
        for(int j = 0; j < b.size(); ++j){
            char c = (std::find(path.begin(), path.end(), Square(i, j)) != path.end())?'x':' ';
            std::cout << "| " << c << ' ';
        }
        std::cout << "|\n" << division << '\n';
    }
}

void showPaths(const std::vector<std::vector<Square>> &paths, const Board &b){
    for(int i = 0; i < paths.size(); ++i){
        showPath(paths[i], b);
        std::cin.ignore();
        std::cin.get();
        if(system("clear")) system("CLS");
    }
}