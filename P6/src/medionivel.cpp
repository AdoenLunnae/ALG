#include "ClaseTiempo.hpp"
#include "ajuste.hpp"
#include "nreinas-bt.hpp"
#include "nreinas-comun.hpp"
#include "nreinas-lv.hpp"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

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
    int tamInicial = -1, tamMaximo = -1;
    std::string filepath;
    while (tamInicial <= 3) {
        cout << "Tamaño mínimo del tablero: ";
        cin >> tamInicial;
    }

    while (tamMaximo <= tamInicial) {
        cout << "Tamaño máximo del tablero: ";
        cin >> tamMaximo;
    }

    cout << "Ruta del fichero para guardar el ajuste: ";
    cin >> filepath;

    ajustarYGuardar(tamInicial, tamMaximo, filepath);
}