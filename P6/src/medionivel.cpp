#include "nreinas-bt.hpp"
#include "nreinas-comun.hpp"
#include "nreinas-lv.hpp"
#include <iostream>

using std::cin;
using std::cout;

void probarBacktracking()
{
    int tam = -1;
    while (tam <= 3) {
        cout << "Tamaño del tablero: ";
        cin >> tam;
    }
    auto solutions = nReinasBacktracking(tam);
    cout << "Se obtuvieron " << solutions.size() << " soluciones\n";
    cout << "¿Mostrar las soluciones? [s/N]  ";
    cin.ignore();
    char c = getchar();
    if (c == 's' || c == 'S')
        drawSolutions(solutions);
}

void probarLasVegas()
{
    int tam = -1;
    int nIntentos;
    while (tam <= 3) {
        cout << "Tamaño del tablero: ";
        cin >> tam;
    }
    auto sol = nReinasLasVegasRepetir(tam, nIntentos);
    cout << "Se obtuvo una solución en " << nIntentos << " intento(s). Pulse cualquier tecla para mostrarla\n";
    cin.ignore();
    cin.get();
    drawSolution(sol);
    cout << "Pulse cualquier tecla para salir\n";
    cin.get();
}

void ajusteBacktracking()
{
}