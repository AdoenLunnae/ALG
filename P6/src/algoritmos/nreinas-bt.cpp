#include "nreinas-comun.hpp"
#include <vector>
using std::vector;
/*
Algoritmo  n−reinas(n)
inicio
    x(1)← 0
    k← 1
    mientras  k > 0  hacer
        x(k)← x(k) + 1
        
        mientras  x(k)≤ n  y  Lugar(k, x) = falso hacer
            x(k)← x(k) + 1
        finmientras
        si  x(k)≤ n  entonces
            si  k = n  entonces
                escribir  x(1), x(2), . . . , x(k)
            sino
                k← k + 1
                x(k)← 0
            finsi
        sino
            k← k− 1
        finsi
    finmientras
fin
*/

vector<vector<int>> nReinasBacktracking(const int& n)
{
    vector<int> x(n, -1); //Todas las filas empiezan con la columna -1
    vector<vector<int>> soluciones;
    int k = 0;

    //Mientras no hayamos agotado todas las posibilidades
    while (k >= 0) {
        //Probar la siguiente columna para la fila k
        x[k]++;

        //Encontrar la primera posición válida
        while ((x[k] < n) && (!posicionValida(k, x)))
            x[k]++;

        //Si la columna está en el tablero
        if (x[k] < n) {
            if (k == n - 1) //Si estamos en la última fila hemos encontrado una solución
                soluciones.push_back(x);
            else { //Si no, vamos a la siguiente fila y la inicializamos a -1
                k++;
                x[k] = -1;
            }
        } else
            k--; //Si la columna no está en el tablero (no hay más posiciones válidas) volvemos a la fila anterior
    }
    return soluciones;
}
