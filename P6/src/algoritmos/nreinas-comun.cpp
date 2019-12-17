#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;

/*
Algoritmo  Lugar(k, x; ; )
inicio
    para  i  de 1  a  k− 1  hacer
        si (x(i) = x(k)  o |x(i)− x(k)| =|i− k|  entonces
            devolver  falso
        finsi
    finpara
    devolver  cierto
fin
*/
bool posicionValida(const int& k, const vector<int>& x)
{
    for (int i = 0; i < k; ++i) {
        //Comprueba fila   y   diagonal
        if ((x[k] == x[i]) || (abs(x[k] - x[i]) == abs(k - i)))
            return false;
    }
    return true;
}

void drawSolution(const vector<int>& solution)
{
    char square;
    int n = solution.size();
    string division = "|";

    for (int i = 0; i < n; ++i) {
        division += "---|";
    }

    cout << division << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            square = (j == solution[i]) ? 'Q' : ' ';
            cout << "| " << square << ' ';
        }
        cout << "|\n"
             << division << '\n';
    }
}

void drawSolutions(const vector<vector<int>>& solutions)
{

    int c;
    cin.ignore();
    for (auto solution : solutions) {
        if (system("clear"))
            system("cls");
        drawSolution(solution);
        cout << "\nIntroduce Q para salir o cualquier otra tecla para continuar\n";
        c = getchar();
        if (c == 'q' || c == 'Q')
            return;
    }
}