#include "dynamicprogrammingmethod.hpp"
#include "digitalcurve.hpp"
#include <iostream>
#include <vector>
using std::vector;

DynamicProgrammingMethod::DynamicProgrammingMethod(char* filename, int numberPoints)
{
    setOriginalCurve(DigitalCurve(filename));
    setNumberPointsPolygonalApproximation(numberPoints);
}

void DynamicProgrammingMethod::getApproxMN(const int& m, const int& n, vector<vector<int>>& father, vector<vector<long double>>& errors)
{
    long double minErr = std::numeric_limits<long double>::infinity();
    int bestFather = 0;
    long double error;
    for (int j = m - 1; j <= n - 1; ++j) {
        error = errors[j][m - 1] + calculateISEValue(j, n);
        if (error < minErr) {
            minErr = error;
            bestFather = j;
        }
    }
    errors[n][m] = minErr;
    father[n][m] = bestFather;
}

void DynamicProgrammingMethod::apply()
{
    const int m = getNumberPointsPolygonalApproximation();
    const int n = getOriginalCurve().getNumberPointsDigitalCurve();

    vector<vector<int>> father(n, vector<int>(m, 0));
    vector<vector<long double>> errors(n, vector<long double>(m, 0));

    vector<int> solution(m, 0);

    calculateSummations();

    for (int i = 1; i < n; ++i) {
        errors[i][0] = std::numeric_limits<long double>::infinity();
    }

    for (int i = 1; i < m; ++i) {
        for (int j = i; j < n; ++j)
            getApproxMN(i, j, father, errors);
    }

    solution[m - 1] = n - 1;

    for (int i = m - 1; i > 0; --i)
        solution[i - 1] = father[solution[i]][i];

    setDominantPointsPosition(solution);
    calculatePolygonalApproximation();
    setNumberPointsPolygonalApproximation(getPolygonalApproximation().getNumberPointsDigitalCurve());
}