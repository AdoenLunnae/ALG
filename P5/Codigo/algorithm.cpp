#include <vector>
#include "algorithm.hpp"
#include "digitalcurve.hpp"
#include "matrix.hpp"
#include "line.hpp"

using namespace std;

void Algorithm::calculateSummations()
{
	int n = getOriginalCurve().getNumberPointsDigitalCurve();
  	long double x, y; 

  	//First, the summation of the forst row are calculated.
  	//each j element is obtained from j-1 element, adding the summation corresponding to  j-1 point

  	//It declares and initialses matrixes for summations
  	Matrix sX(n, n), sXX(n, n), sY(n, n), sYY(n, n), sXY(n, n);

  	_sX = sX;
  	_sY = sY;
  	_sXX = sXX;
  	_sYY = sYY;
  	_sXY = sXY;
  
  	for(int j = 2; j < n; j++)
  	{
	    x = getOriginalCurve().getPointDigitalCurve(j - 1).getX(); // x from point j - 1
	    y = getOriginalCurve().getPointDigitalCurve(j - 1).getY(); // y from point j - 1
	    _sX.setElement(0, j, _sX.getElement(0, j - 1) + x);
	    _sY.setElement(0, j, _sY.getElement(0, j - 1) + y);
	    _sXX.setElement(0, j, _sXX.getElement(0, j - 1) + x * x);
	    _sYY.setElement(0, j, _sYY.getElement(0, j - 1) + y * y);
		_sXY.setElement(0, j, _sXY.getElement(0, j - 1) + x * y);
  	}

  	//From the second row, the summations are calculated from the previous row.
  	//The element i,j is obtained  substracting to  element (i-1, j) the summation of point i
	for(int i = 1; i < n - 2; i++)
	{
	    x = getOriginalCurve().getPointDigitalCurve(i).getX(); // x from point i
	    y = getOriginalCurve().getPointDigitalCurve(i).getY(); // y from point i
	    for(int j = i + 2; j < n; j++)
	    {
	    	_sX.setElement(i, j, _sX.getElement(i - 1, j) - x);
	    	_sY.setElement(i, j, _sY.getElement(i - 1, j) - y);
	    	_sXX.setElement(i, j, _sXX.getElement(i - 1, j) - x * x);
	    	_sYY.setElement(i, j, _sYY.getElement(i - 1, j) - y * y);
			_sXY.setElement(i, j, _sXY.getElement(i - 1, j) - x * y);
	    }
	}
}

long double Algorithm::calculateISEValue(const int &initial, const int &final)
{
	//For obtaining the summation of errors between initial amd final, 
	//approximating the segment using a line that joins initial and final
	//For this reason the number of points is (final-initial -1)

	
 	long double ISE = 0.0;
 	long double A, B, C; //Coeficients of the line in format . Ax + By + C = 0
 	long double a, b; //Coeficients of the line in format . y = a + bx

 	if (initial == final)
  		return 0.0;
	if (initial == final - 1)
		return 0.0;
  	//printf("initial = %d, final = %d", initial, final);
	//The points are equal. The errors are calculated from the distances of the intermediate points to this point
	if (getOriginalCurve().getPointDigitalCurve(initial) == getOriginalCurve().getPointDigitalCurve(final))
	{
		return getOriginalCurve().getISE(initial, final); //It is obtained from the formula of the digital curve
	}
		
 	Line line(getOriginalCurve().getPointDigitalCurve(initial), getOriginalCurve().getPointDigitalCurve(final));
	//printf("Punto initial %lf %lf \n", contorno().puntoContorno(initial).x(), contorno().puntoContorno(initial).y());
	//printf("Punto final %lf %lf \n", contorno().puntoContorno(final).x(), contorno().puntoContorno(final).y());
 
	//Como la recta se calcula en forma general, hay que calcular los coeficientes en forma explicita (a y b)
 	A = line.getA();
 	B = line.getB();
 	C = line.getC();

	//printf("A = %lf B = %lf C = %lf \n", A, B, C);

   	if (fabs(B) > 0.0000000001) //line not  parallel to y axis
 	{
   		a = - C / B;
   		b = - A / B;
  		ISE = ( (final - initial - 1.0) * a * a + 2.0 * a * b * _sX.getElement(initial, final) + 
		b * b * _sXX.getElement(initial, final) - 2.0 * a * _sY.getElement(initial, final) -
		2.0 * b * _sXY.getElement(initial, final) + _sYY.getElement(initial, final)) / (b * b + 1.0);
		
 	}
 	else //Line parallel to y axis. In this case b is infinite and the error is calculated in another way 
 	{
   		ISE = _sXX.getElement(initial, final) + (2.0 * (C / A)) * _sX.getElement(initial, final) + 
		(final - initial -1) * (C/A) * (C/A);
 	}
 	
 	if (isnan(ISE))
	{
		cout << "\ninitial = "<< initial << endl;
		cout << "final = " << final << endl;
		cout << " A = " << A << endl;
		cout << "B = " << B << endl;
    	cout << "C = " << C << endl;
	}
 	return ISE;
}

long double Algorithm::getISE()
{
	long double ISE = 0.0;
	for(int i = 0; i < _dominantPointPosition.size() - 1; i++)
	{
		ISE += calculateISEValue(_dominantPointPosition[i], _dominantPointPosition[i+1]);
	}
	return ISE;
}

void Algorithm::collinearPointsElimination()
{
	vector <int> collinearPoints;
	
	//First chain codes of the original curve are calculated
	getOriginalCurve().calculateChainCodeDigitalCurve();
	int n = getOriginalCurve().getNumberPointsDigitalCurve();
	
	for(int i = 0; i < n; i++)
	{
		_dominantPointPosition.push_back(i); //First, all points are dominant
	}

	//The collinear points are obtained
	//If is closed, it tests if the first point is collinear
  	if (getOriginalCurve().isClosed())
  	{
    	if (getOriginalCurve().getChainCodePoint(n-2) == getOriginalCurve().getChainCodePoint(0))
    		//It uses n-2 because the n-1 point is similar to 0 point
    		collinearPoints.push_back(0);
  	}
	for(int i = 0; i < n - 1; i++)
	{
		if (getOriginalCurve().getChainCodePoint(i) == getOriginalCurve().getChainCodePoint(i + 1))
		{
			collinearPoints.push_back(i + 1);
			//cout << i + 1 << " is collinear point " << endl;
		}
	}

	//The collinear points are eliminated as dominant points
	for(int i = collinearPoints.size() - 1; i >= 0; i--)
	{
		_dominantPointPosition.erase(_dominantPointPosition.begin() + collinearPoints[i]);
	}
}

void Algorithm::calculatePolygonalApproximation()
{
	for(int i = 0; i < _dominantPointPosition.size(); i++)
		_polygonalApproximation.insertPointDigitalCurve(getOriginalCurve().getPointDigitalCurve(_dominantPointPosition[i]));

    //If the original digital curve is closed, then the polygonal approximation must be closed
	if (getOriginalCurve().isClosed() and not getPolygonalApproximation().isClosed())
		_polygonalApproximation.insertPointDigitalCurve(getPolygonalApproximation().getPointDigitalCurve(0));

}


