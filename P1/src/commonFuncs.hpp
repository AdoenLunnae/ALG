#ifndef _COMMON_FUNCS_HPP_
#define _COMMON_FUNCS_HPP_
    #include<vector>

    void rellenarMatriz(vector<vector<double>> &m);
    double sumatorio(std::vector<double> x, std::vector<double> y, float expX, int expY);
    double mean(const std::vector<double> &n);
    double variance(const std::vector<double> &n);
    double calcularCoeficienteDeterminacion(const std::vector<double> &tiemposReales, const std::vector<double> &tiemposEstimados);
#endif