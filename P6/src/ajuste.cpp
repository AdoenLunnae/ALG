#include "ajuste.hpp"
#include "ClaseTiempo.hpp"
#include "nreinas-bt.hpp"
#include "sistemaEcuaciones.hpp"
#include <fstream>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
int factorial(const int n)
{
    int result = 1;
    if (n >= 0) {
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
    }
    return result;
}

double sumatorio(vector<double> x, vector<double> y, float expX, int expY)
{
    double result = 0.0;
    for (int i = 0; i < x.size(); ++i) {
        result += pow(x[i], expX) * pow(y[i], expY);
    }
    return result;
}
double mean(const vector<double>& n)
{
    double sum = 0;
    for (int i = 0; i < n.size(); ++i) {
        sum += n[i];
    }
    return (sum / n.size());
}

double variance(const vector<double>& n)
{
    vector<double> sq;
    for (int i = 0; i < n.size(); ++i) {
        sq.push_back(n[i] * n[i]);
    }
    return (mean(sq) - (mean(n) * mean(n)));
}

double calcularCoeficienteDeterminacion(const vector<double>& tiemposReales, const vector<double>& tiemposEstimados)
{
    return (variance(tiemposEstimados) / variance(tiemposReales));
}

void ajuste(const vector<double>& n, const vector<double>& tiemposReales, double& a0, double& a1)
{
    vector<double> z;
    vector<vector<double>> A(2, vector<double>(2, 0));
    vector<vector<double>> B(2, vector<double>(1, 0));
    vector<vector<double>> X(2, vector<double>(1, 0));
    for (int i = 0; i < n.size(); ++i) {
        z.push_back(factorial(n[i]));
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == 0 && j == 0) {
                A[0][0] = tiemposReales.size();
            } else {
                A[i][j] = sumatorio(z, tiemposReales, i + j, 0);
            }
        }
        B[i][0] = sumatorio(z, tiemposReales, i, 1);
    }

    resolverSistemaEcuaciones(A, B, 2, X);
    a0 = X[0][0];
    a1 = X[1][0];
    cout << "Ajuste:   " << a0 << " + " << a1 << " * n!\n";
}

double calcularTiempoEstimado(const double& n, const double& a0, const double& a1)
{
    return (a0 + a1 * factorial(n));
}

void calcularTiemposEstimados(const vector<double>& n, const double& a0, const double& a1, vector<double>& tiemposEstimados)
{
    tiemposEstimados.clear();
    for (int i = 0; i < n.size(); ++i) {
        tiemposEstimados.push_back(calcularTiempoEstimado(n[i], a0, a1));
    }
}

void ajustarYGuardar(const int& tamInicial, const int& tamMaximo, const std::string& filepath)
{
    Clock time;
    vector<double> realTimes, sizes, estimatedTimes;
    double a0, a1;
    for (int i = tamInicial; i <= tamMaximo; ++i) {
        time.start();
        nReinasBacktracking(i);
        time.stop();
        realTimes.push_back(time.elapsed());
        sizes.push_back(i);
    }

    ajuste(sizes, realTimes, a0, a1);
    calcularTiemposEstimados(sizes, a0, a1, estimatedTimes);

    cout << "Guardando datos...\n";
    std::ofstream f(filepath);
    for (int i = 0; i < sizes.size(); ++i) {
        f << sizes[i] << " " << realTimes[i] << " " << estimatedTimes[i] << '\n';
    }

    cout << "El coeficiente de determinación del ajuste es: " << calcularCoeficienteDeterminacion(realTimes, estimatedTimes) << '\n';
    cout << "Pulse cualquier tecla para salir\n";
    cin.ignore();
    cin.get();
}