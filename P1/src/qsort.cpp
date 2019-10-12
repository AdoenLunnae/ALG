#include <vector>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cmath>
#include "qsort.hpp"
#include "sistemaEcuaciones.hpp"
#include "ClaseTiempo.hpp"
#include "commonFuncs.hpp"

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
        if(left < right){
            aux= v[left];
            v[left] = v[right];
            v[right] = aux;
        }
    }

    aux = v[right];
    v[right] = v[begin];
    v[begin] = aux;

    return right;
}

void quicksort(vector<int> &v, int begin, int end){
  int pivot;
  if(begin < end){
    pivot = partition(v, begin, end );
    quicksort( v, begin, pivot - 1 );
    quicksort( v, pivot + 1, end );
  }
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

void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, const double &a0, const double &a1, vector<double> &tiemposEstimados){
    tiemposEstimados.clear();
    for(int i = 0; i < n.size(); ++i){
        tiemposEstimados.push_back(a0+a1*n[i]*log10(n[i]));
    }
}

void options(int &n, int &min, int &max, int &increment, int &repetitions){
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
}

double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1){
	return (a0 + a1*n*log(n));
}

void getTimeDataQuickSort(std::string filename){
    srand(time(NULL));
    Clock clock;
    vector<int> v;
    double avg, a0, a1;
    vector<double> tiemposReales, sizes, tiemposEstimados;
    int n, min = 0, max = 0, increment = 0, repetitions = 0;
    std::ofstream f;

    options(n, min, max, increment, repetitions);

    for(n = min; n<=max; n+=increment){
        v.resize(n);
        avg = 0;
        for(int i = 0; i < repetitions; ++i){
            rellenarVector(v);
            clock.restart();
            quicksort(v, 0, v.size()-1);
            clock.stop();
            estaOrdenado(v);
            avg += clock.elapsed();
        }
        avg /= repetitions;
        cout << "Mean for N=" << n << ":  " << avg << "\n";
        sizes.push_back(n);
        tiemposReales.push_back(avg);
    }

    ajusteNlogN(sizes, tiemposReales, a0, a1);
    calcularTiemposEstimadosNlogN(sizes, tiemposReales, a0, a1, tiemposEstimados);
    double r2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    cout << "Ajuste:   " << a0 << "+" << a1 << "*nlog(n)" << "\n";
    cout << "Coeficiente de determinación R2:   " << r2 << "\n";

    f.open(filename, ios::out);
    for(int i = 0; i < sizes.size(); ++i){
        f << sizes[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << "\n";
    }
    f.close();

	double estimate;
    double calculated;
	do{
		do{
			cout << "Estimate for N = ";
			cin >> estimate;
		}while(estimate < 0);
        calculated = calcularTiempoEstimadoNlogN(estimate, a0, a1)/1000000; 
		cout << "The time value is " << calculated/(3600*24) << " days. ("<< calculated << " seconds).\n";
	}while(estimate != 0);
}
