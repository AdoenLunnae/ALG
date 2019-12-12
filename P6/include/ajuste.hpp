#ifndef AJUSTE_HPP
#define AJUSTE_HPP
#include <string>
#include <vector>

void ajuste(const std::vector<double>& n, const std::vector<double>& tiemposReales, double& a0, double& a1);
void calcularTiemposEstimados(const std::vector<double>& n, const double& a0, const double& a1, std::vector<double>& tiemposEstimados);
double calcularCoeficienteDeterminacion(const std::vector<double>& tiemposReales, const std::vector<double>& tiemposEstimados);
void ajustarYGuardar(const int& tamInicial, const int& tamMaximo, const std::string& tamFinal);

#endif