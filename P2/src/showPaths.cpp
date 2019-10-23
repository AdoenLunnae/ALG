#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Square.hpp"
#include "Board.hpp"

using std::find;
using std::string;
using std::cout;
using std:: find;

void showPath(const std::vector<Square> &path, const Board &b){
    string division = "|";
    
    for(int i = 0; i < b.size(); ++i){
        division += "---|";
    }
    
    cout << division << '\n';
    
    for(int i = b.size()-1; i >= 0; --i){
        for(int j = 0; j < b.size(); ++j){
            bool isInPath = find(path.begin(), path.end(), Square(i, j)) != path.end();
            string c = isInPath?"K":" ";
            cout << "| " << c << ' ';
        }
        cout << "|\n" << division << '\n';
    }
}

void showPaths(const std::vector<std::vector<Square>> &paths, const Board &b){
    for(int i = 0; i < paths.size(); ++i){
        if(system("clear")) system("CLS");
        showPath(paths[i], b);
        std::cin.get();
    }
}