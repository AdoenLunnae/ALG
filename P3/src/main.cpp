#include "entero.hpp"
#include <iostream>
#include <signal.h>

#define MENU_STR "Elige una opción\n\t1.Calcular el producto de dos enteros\n\t2.Calcular el factorial de un entero.\n\n\tOpcion:\t"

using std::cin;
using std::cout;

int main()
{
    int opt = 0;
    while ((opt < 1) || (opt > 2)) {
        if (system("clear"))
            system("CLS");
        cout << MENU_STR;
        cin >> opt;
    }
    switch (opt) {
    case 1: {
        Entero a, b;
        cout << "Introduzca el primer número:\t";
        cin >> a;
        cout << "Introduzca el segundo número:\t";
        cin >> b;
        cout << a << " * " << b << " = " << a * b << '\n';
    } break;
    case 2: {
        Entero a;
        cout << "Introduzca el número:\t";
        cin >> a;
        cout << a << "! = " << a.factorial() << '\n';
    } break;
    default:
        break;
    }
}
