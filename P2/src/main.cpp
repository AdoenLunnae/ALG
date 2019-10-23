#include "Board.hpp"
#include "Paths.hpp"
#include "Square.hpp"
#include "showPaths.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void printPath(const vector<Square> path)
{
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1)
            cout << "<--";
    }
    cout << '\n';
}

void pathToFile(const vector<Square> path, ofstream& f)
{
    for (int j = 0; j < path.size(); ++j) {
        f << path[j];
        if (j != path.size() - 1)
            f << "<--";
    }
    f << '\n';
}

int main()
{
    Board b(8);
    int opt = -1;
    vector<vector<Square>> allPaths;
    while (opt < 1 || opt > 3) {
        if (system("clear"))
            system("CLS");
        cout << "Introduce option:\n\
        \t1.Paths from row 1 to square (8,c)\n\
        \t2.Paths from (1,2) to row 8\n\
        \t3.Paths from (1,7) to row 8\n\
        \t\tOption:\t";
        cin >> opt;
    }

    switch (opt) {
    case 1: {
        int c = 0;
        while (c < 1 || c > b.size()) {
            if (system("clear"))
                system("CLS");
            cout << "Select goal column :\n";
            cin >> c;
        }
        path(0, Square(7, c - 1), b, allPaths);
    } break;
    case 2: {
        path(Square(0, 1), 7, b, allPaths);
    } break;
    case 3: {
        path(Square(0, 6), 7, b, allPaths);
    } break;
    }

    ofstream f("Paths.txt");
    for (int i = 0; i < allPaths.size(); ++i) {
        printPath(allPaths[i]);
        pathToFile(allPaths[i], f);
    }
    f.close();

    char show;
    cout << "Do you want to show the paths graphically[y/N]\t";
    cin.ignore();
    show = cin.get();
    if (show == 'y')
        showPaths(allPaths, b);
}