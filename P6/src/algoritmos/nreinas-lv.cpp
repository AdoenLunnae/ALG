#include "nreinas-comun.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
using std::vector;

/*Algoritmo  n−reinasLasVegas(n; ; X, exito)
inicio
    Inicializamos la solución a 0
    para  i  de 1  a  n  hacer
        x(i)← 0
    finpara
    //Se han colocado k-1 reinas y se buscan todas las posicionespara la k-ésima
    para  k  de 1  a  n  hacer
        contador← 0
        //Almacena todas las posiciones posibles la reina k en elvector ok
        para  j  de 1  a  n  hacer
            X(k)← j  //probamos la reina k en la columna j
            si  Lugar(k, x) = cierto  entonces 
                //Se puede colocar en la columna j
                contador← contador + 1
                ok(contador)← j 
                //guardamos la posicion disponible
            finsi
        finpara
        salir si  contador = 0 //no se ha encontrado posicion para la reina k
        //Se puede colocar la reina k y se selecciona una posición aleatoria
        columna← ok(uniforme(1, contador))
        X(k)← columna
    finpara
    si  contador = 0 entonces
        exito← falso //No hay solución
    sino
        exito← cierto //Hay solución
    finsi
fin
*/
vector<int> nReinasLasVegas(const int& n, bool& exito)
{
    //srand(time(NULL));
    vector<int> solucion(n, -1);
    int count;
    vector<int> posicionesValidas;
    for (int fila = 0; fila < n; ++fila) {
        count = 0;
        posicionesValidas.clear();
        for (int columna = 0; columna < n; ++columna) {
            solucion[fila] = columna;
            if (posicionValida(fila, solucion)) {
                count++;
                posicionesValidas.push_back(columna);
            }
        }
        if (count == 0)
            break;
        solucion[fila] = posicionesValidas[rand() % count];
    }
    exito = (count != 0);
    return solucion;
}

vector<int> nReinasLasVegasRepetir(const int &n, int & numeroIntentos){
    vector<int> intento;
    bool exito = false;
    numeroIntentos = 0;
    do{
        intento = nReinasLasVegas(n, exito);
        numeroIntentos++;
    }while(!exito);
    return intento;
}