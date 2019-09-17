#include <vector>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>
#include "sistemaEcuaciones.hpp"
#include "ClaseTiempo.hpp"

using std::ofstream;
using std::vector;
using std::cout;
using std::cin;

void rellenarVector(vector<int> &v){
    for(int i = 0; i < v.size(); ++i){
        v[i] = rand() % 10000;
    }
}

void estaOrdenado(const vector<int> &v){
    for(int i = 0; i < v.size()-1; ++i){
        assert(v[i] <= v[i+1]);
    }
}

int partition(vector<int> &v, int begin, int end){
    int left;
    int right;
    int pivot;
    int aux;

    pivot = v[begin];
    left = begin;
    right = end;

    while (left < right){
        while (v[right] > pivot){
          right--;
        }

        while ((left < right) && (v[left] <= pivot)){
          left++;
        }

    // Si todavia no se cruzan los indices seguimos intercambiando
        if(left < right){
            aux= v[left];
            v[left] = v[right];
            v[right] = aux;
        }
    }

    //Los indices ya se han cruzado, ponemos el pivote en el lugar que le corresponde
    aux = v[right];
    v[right] = v[begin];
    v[begin] = aux;

    //La nueva posición del pivote
    return right;
}

//						Funcion Quicksort
//======================================================================
//funcion recursiva para hacer el ordenamiento
void quicksort(vector<int> &v, int begin, int end){
  int pivot;
  if(begin < end){
    pivot = partition(v, begin, end );
    quicksort( v, begin, pivot - 1 );//ordeno la lista de los menores
    quicksort( v, pivot + 1, end );//ordeno la lista de los mayores
  }
}

double sumatorio(vector<double> x, vector<double> y, int expX, int expY){
    double result = 0.0;
    for(int i = 0; i < x.size(); ++i){
        result += pow(x[i], expX)*pow(y[i], expY);
    }
    return result;

}

void ajusteNlogN(const vector<double> &n, const vector<double> &tiemposReales, double &a0, double &a1){
    vector<double> z(n.size(), 0);
    vector<vector<double>> A(2, vector<double>(2, 0));
    vector<vector<double>> B(2, vector<double>(1, 0));
    vector<vector<double>> X(2, vector<double>(1, 0));
    for(int i = 0; i < n.size(); ++i){
        z[i]=(n[i]*log10(n[i]));
    }
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            if(i==0 && j==0){
                A[0][0]=tiemposReales.size();
            }
            else{
                A[i][j]=sumatorio(z, tiemposReales, i+j, 0);
            }
        }
        B[i][0] = sumatorio(z, tiemposReales, i, 1);
    }
    
    resolverSistemaEcuaciones(A, B, 2, X);
    a0 = X[0][0];
    a1 = X[1][0];
    cout << "Ajuste:   " << a0 << " + " << a1 << "*nlog(n)" << "\n";
}

int main(){
    srand(time(NULL));
    Clock clock;
    vector<int> v;
    double avg, a0, a1;
    vector<double> times, sizes;
    int n, min = 0, max = 0, increment = 0, repetitions = 0;
    while(min <= 0){
        cout << "Introduce the minimum number of elements in the vector (>0)" << '\n';
        cin >> min;
    }
    while(max <= 0){
        cout << "Introduce the maximum number of elements in the vector (>0)" << '\n';
        cin >> max;
    }
    while(increment <= 0){
        cout << "Introduce the increment in the number of elements in the vector (>0)" << '\n';
        cin >> increment;
    }
    while(repetitions <= 0){
        cout << "Introduce the repetitions per number of elements in the vector (>0)" << '\n';
        cin >> repetitions;
    }

    ofstream f("Datos.txt");
    ofstream f2("Medias.txt");
    for(n = min; n<=max; n+=increment){
        v.resize(n);
        avg = 0;
        for(int i = 0; i < repetitions; ++i){
            rellenarVector(v);
            clock.restart();
            quicksort(v, 0, v.size()-1);
            clock.stop();
            estaOrdenado(v);
            f << n << " " << clock.elapsed() <<'\n';
            avg += clock.elapsed();
        }
        avg /= repetitions;
        sizes.push_back(n);
        times.push_back(avg);
        cout << "Media para N=" << n << " " << avg << '\n';
        f2 << n << " " << avg <<'\n';
    }
    f.close();
    ajusteNlogN(sizes, times, a0, a1);
    cout << "Ajuste:   " << a0 << "+" << a1 << "*nlog(n)" << "\n";
    f.open("Estimacion.txt");
    for(int i = 0; i < sizes.size(); ++i){
        f << sizes[i] << " " << a0+a1*sizes[i]*log10(sizes[i]) << "\n";
    }
    f.close();

}
