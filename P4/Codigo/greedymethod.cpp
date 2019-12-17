
#include "greedymethod.hpp"
#include "algorithm.hpp"
#include "digitalcurve.hpp"
#include <limits>
#include <vector> // necesario para el contenedor vector
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"

using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

GreedyMethod::GreedyMethod(char* fileName, int numberPointsPolygonalApproximation)
{
    //A digital curve is created to load the digital curve in file
    DigitalCurve dc(fileName);

    //Digital curve as saved as original curve
    setOriginalCurve(dc);

    //Set the number of points of the polygonal approximation
    setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);
    calculateSummations();
}

//Destructor
GreedyMethod::~GreedyMethod()
{
}

void GreedyMethod::apply()
{
    collinearPointsElimination();

    int jump = (getDominantPointsPosition().size() / (getNumberPointsPolygonalApproximation() - 1));

    vector<int> newDominants;

    //Escogemos N puntos
    for (auto i = 0; i < getDominantPointsPosition().size(); i += jump)
        newDominants.push_back(getDominantPointsPosition()[i]);

    if (newDominants.back() != getDominantPointsPosition().back())
        newDominants.back() = getDominantPointsPosition().back();

    int inserted = 0;
    long double err, minErr;

    for (int i = 1; i < getNumberPointsPolygonalApproximation(); ++i) {
        minErr = std::numeric_limits<long double>::infinity();
        for (int j = newDominants[i - 1] + 1; j <= newDominants[i + 1]; ++j) {
            err = calculateISEValue(newDominants[i - 1], j) + calculateISEValue(j, newDominants[i + 1]);

            if (err < minErr) {
                minErr = err;
                inserted = j;
            }
        }
        newDominants[i] = inserted;
    }
    //    if (getOriginalCurve().isClosed() && (newDominants.front() != newDominants.back()))
    //        newDominants.push_back(newDominants.front());

    getDominantPointsPosition() = newDominants;
    calculatePolygonalApproximation();
}
