#include <vector>
#include<cmath>
using std::vector;

void rellenarMatriz(vector<vector<double>> &m){
    for(int i = 0; i < m.size(); ++i){
        for(int j = 0; j < m[i].size(); ++j){
            m[i][j] = ((rand() % 100) + 950) / 100.0;
        }
    }
}

double sumatorio(vector<double> x, vector<double> y, float expX, int expY){
    double result = 0.0;
    for(int i = 0; i < x.size(); ++i){
        result += pow(x[i], expX)*pow(y[i], expY);
    }
    return result;

}
double mean(const vector<double> &n){
    double sum = 0;
    for(int i = 0; i < n.size(); ++i){
        sum += n[i];
    }
    return(sum / n.size());
}

double variance(const vector<double> &n){
    vector<double> sq;
    for(int i = 0; i < n.size(); ++i){
        sq.push_back(n[i]*n[i]);
    }
    return(mean(sq) - (mean(n)*mean(n)));
}

double calcularCoeficienteDeterminacion(const vector<double> &tiemposReales, const vector<double> &tiemposEstimados){
    return(variance(tiemposEstimados) / variance(tiemposReales));
}