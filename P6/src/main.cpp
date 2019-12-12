#include "medionivel.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int menu()
{
    int c;
    do {
        if (system("clear"))
            system("CLS");
        cout << "Elija una opción:\n1.Probar método backtracking\
                \n2.Probar método de Las Vegas\n3.Ajuste de tiempos para el backtracking\
                \n0.Salir\nOpcion:  ";
        cin >> c;
    } while (c != 1 && c != 2 && c != 3 && c != 4 && c != 0);
    return c;
}
int main()
{
    int c = -1;
    srand(time(NULL));
    while (c != 0) {
        c = menu();
        switch (c) {
        case 1:
            probarBacktracking();
            break;

        case 2:
            probarLasVegas();
            break;
        case 3:
            ajusteBacktracking();
            break;
        default:
            break;
        }
    }
}
