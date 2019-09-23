#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"
#include "commonFuncs.hpp"

using namespace std;


void rellenarMatriz(vector<vector<double>> &m){
    for(int i = 0; i < m.size(); ++i){
        for(int j = 0; j < m[i].size(); ++j){
            m[i][j] = ((rand() % 100) + 950) / 100.0;
        }
    }
}

void multiply(const vector<vector<double>> &m1, const vector<vector<double>> &m2, vector<vector<double>> &r){
    for(int i = 0; i < m1.size(); ++i){
        for(int j = 0; j < m1.size(); ++j){
            r[i][j] = 0;
            for(int k = 0; k < m1.size(); ++k){
                r[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void ajustePolinomico(const vector<double> &n, const vector<double> &tiemposReales, vector<double> &a){
    vector<vector<double>> A(4, vector<double>(4, 0));
    vector<vector<double>> B(4, vector<double>(1, 0));
    vector<vector<double>> X(4, vector<double>(1, 0));
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(i==0 && j==0){
                A[0][0]=tiemposReales.size();
            }
            else{
                A[i][j]=sumatorio(n, tiemposReales, i+j, 0);
            }
        }
        B[i][0] = sumatorio(n, tiemposReales, i, 1);
    }
    resolverSistemaEcuaciones(A, B, 4, X);
    for(int i = 0; i < 4; ++i){
        a[i] = X[i][0];
    }
}

void calcularTiempoEstimadoPolinomico(const vector<double> &n, const vector<double> &tiemposReales, const vector<double> &a, vector<double> &tiemposEstimados){
    tiemposEstimados.clear();
    tiemposEstimados.resize(n.size());
    for(int i = 0; i < n.size(); ++i){
        tiemposEstimados[i] = 0.0;
        for(int j = 0; j < a.size(); ++j){
            tiemposEstimados[i] += a[j]*pow(n[i], j);
        }
    }
}

void options(int &n, int &min, int &max, int &increment){
    while(min <= 0){
        cout << "Introduce the minimum order of the matrices (>0)" << '\n';
        cin >> min;
    }
    while(max <= 0){
        cout << "Introduce the maximum order of the matrices (>0)" << '\n';
        cin >> max;
    }
    while(increment <= 0){
        cout << "Introduce the increment in the order of the matrices (>0)" << '\n';
        cin >> increment;
    }
}

int getTimeData(){
    srand(time(NULL));
    Clock clock;
    vector<vector<double>> m1, m2, result;
    vector<double> tiemposReales, sizes, tiemposEstimados, coeficients(4, 0);
    int n = 0, min = 0, max = 0, increment = 0;
    ofstream f;

    options(n, min, max, increment);

    for(n = min; n<=max; n+=increment){
        m1.resize(n);
        m2.resize(n);
        result.resize(n);
        for(int i = 0; i < n; ++i){
            m1[i].resize(n);
            m2[i].resize(n);
            result[i].resize(n);
        }
        rellenarMatriz(m1);
        rellenarMatriz(m2);
        clock.restart();
        multiply(m1, m2, result);
        clock.stop();

        cout << "Time for N=" << n << ":  " << clock.elapsed() << "\n";
        sizes.push_back(n);
        tiemposReales.push_back(clock.elapsed());
    }

    ajustePolinomico(sizes, tiemposReales, coeficients);
    calcularTiempoEstimadoPolinomico(sizes, tiemposReales, coeficients, tiemposEstimados);
    double r2 = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    cout << "Ajuste:   " << coeficients[3] <<"*x³ + " << coeficients[2] <<"*x² + " << coeficients[1] << "*x + " << coeficients[0] << "\n";
    cout << "Coeficiente de determinación R2:   " << r2 << "\n";

    f.open("Datos.txt", ios::out);
    for(int i = 0; i < sizes.size(); ++i){
        f << sizes[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << "\n";
    }
    f.close();

}
