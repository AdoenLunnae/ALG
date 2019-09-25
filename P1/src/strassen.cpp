#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
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

void sum(const vector<vector<double>> &m1, const vector<vector<double>> &m2, vector<vector<double>> &r, bool substract = false){
    for(int i = 0; i < m1.size(); ++i){
        for(int j = 0; j < m2.size(); ++j){
            r[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void strassen(const vector<vector<double>> &a, const vector<vector<double>> &b, vector<vector<double>> &r){
    int order = a.size();
    int half = order/2;
    vector<vector<double>> a11(half, vector<double>(half,0));
    vector<vector<double>> a12(half, vector<double>(half,0));
    vector<vector<double>> a21(half, vector<double>(half,0));
    vector<vector<double>> a22(half, vector<double>(half,0));

    vector<vector<double>> b11(half, vector<double>(half,0));
    vector<vector<double>> b12(half, vector<double>(half,0));
    vector<vector<double>> b21(half, vector<double>(half,0));
    vector<vector<double>> b22(half, vector<double>(half,0));

    vector<vector<double>> r11(half, vector<double>(half,0));
    vector<vector<double>> r12(half, vector<double>(half,0));
    vector<vector<double>> r21(half, vector<double>(half,0));
    vector<vector<double>> r22(half, vector<double>(half,0));

    vector<vector<double>> m1(half, vector<double>(half,0));
    vector<vector<double>> m2(half, vector<double>(half,0));
    vector<vector<double>> m3(half, vector<double>(half,0));
    vector<vector<double>> m4(half, vector<double>(half,0));
    vector<vector<double>> m5(half, vector<double>(half,0));
    vector<vector<double>> m6(half, vector<double>(half,0));
    vector<vector<double>> m7(half, vector<double>(half,0));

    vector<vector<double>> auxA(half, vector<double>(half,0));
    vector<vector<double>> auxB(half, vector<double>(half,0));
    if(order < 2){
        r[0][0] = a[0][0] * b[0][0];
    }
    else{
        for(int i=0; i<half; i++){
            for(int j=0; j<half; j++){
                a11[i][j] = a[i][j];
                a12[i][j] = a[i][j+half];
                a21[i][j] = a[i+half][j];
                a22[i][j] = a[i+half][j+half];

                b11[i][j] = b[i][j];
                b12[i][j] = b[i][j+half];
                b21[i][j] = b[i+half][j];
                b22[i][j] = b[i+half][j+half];
            }
        }
        sum(a11, a22, auxA);
        sum(b11, b22, auxB);
        strassen(auxA, auxB, m1);


        sum(a21, a22, auxA);
        strassen(auxA, b11, m2);


        sum(b12, b22, auxB, true);
        strassen(a11, auxB, m3);


        sum(b21, b11, auxB, true);
        strassen(a22, auxB, m4);


        sum(a11, a12, auxA);
        strassen(auxA, b22, m5);

        sum(a21, a11, auxA, true);
        sum(b11, b12, auxB);
        strassen(auxA, auxB, m6);


        sum(a12, a22, auxA, true);
        sum(b21, b22, auxB);
        strassen(auxA, auxB, m7);

        //C11 = M1 + M2 - M5 + M7
        sum(m1, m4, auxA);
        sum(m7, m5, auxB);
        sum(auxA, auxB, r11);

        //C12 = M3 + M5
        sum(m3, m5, r12);

        //C21 = M2 + M4
        sum(m2, m4, r21);

        //C22 = M1 - M2 + M3 + M6
        sum(m1, m2, auxA, true);
        sum(m6, m3, auxB);
        sum(auxA, auxB, r22);

        for(int i=0; i<half; i++) {
           for(int j=0; j<half; j++) {
              r[i][j] = r11[i][j];
              r[i][j+half] = r12[i][j];
              r[i+half][j] = r21[i][j];
              r[i+half][j+half] = r22[i][j];
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


void getTimeDataStrassenProduct(string filename){
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
        strassen(m1, m2, result);
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