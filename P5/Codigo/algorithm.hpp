#ifndef Algorithm_HPP
#define Algorithm_HPP

#include <vector>
#include "point.hpp"
#include "digitalcurve.hpp"
#include "matrix.hpp"

class Algorithm
{
	private:
		//original digital contour for obtained polygonal approximation
		DigitalCurve _digitalCurve; 

		//Vector of dominant points positions. Dominant points are the points of the polygonal approximation.
		//The position corresponding to the Digital Curve
		vector <int> _dominantPointPosition; 
		
		//Diginal contour that contains polygonal approximation
		DigitalCurve _polygonalApproximation;

		//Matrix for calculate summations
		Matrix _sX, _sY, _sXX, _sYY, _sXY;

		//Number of points of the polygonal approximation
		int _numberPointsPolygonalApproximation;
	public:
		Algorithm()
		{};
		virtual ~Algorithm()
    	{
   		};

   		//Return the curve used to obtain its polygonal approximation
		inline DigitalCurve & getOriginalCurve()
		{
			return _digitalCurve;
		};

		//Set the curve used to obtain its polygonal approximation
		inline void setOriginalCurve(const DigitalCurve &dC) 
		{
			_digitalCurve = dC;
		};

		//Return the number of points of the polygonal approximation
		inline int getNumberPointsPolygonalApproximation()
		{
			return _numberPointsPolygonalApproximation;
		}

		//Set the number of points of the polygonal approximation
		inline void setNumberPointsPolygonalApproximation(int n)
		{
			_numberPointsPolygonalApproximation = n;
		}
		//Return the polygonal approximation of the digital curve. The polygonal approximation is another digital curve
		inline DigitalCurve & getPolygonalApproximation()
		{
			return _polygonalApproximation;
		};

		//Set the polygonal approximation of the digital curve. 
		inline void setPolygonalApproximation(const DigitalCurve &pA) 
		{
			_polygonalApproximation = pA;
		};

		//Obtain a vector that contains the positions of the points of the polygonal approximations
		vector <int> & getDominantPointsPosition()
		{
			return _dominantPointPosition;
		}
		
		//Set the vector that contains the positions of the points of the polygonal approximations
		void  setDominantPointsPosition(const vector <int>  &v)
		{
			 _dominantPointPosition = v;
		}

		//Virtual pure function. It must be implement in derivated classes
		//This function is used to obtain the polygonal approximation
 		virtual void apply()=0;
    
    	//Functions for obtaining errors.
    	//This function obtains the auxiliar summations to calculate the errors
    	void calculateSummations();

    	//This function quickly calculates the accumulated error between two points using the auxiliar summations 
		long double calculateISEValue(const int &initial, const int &final); //To obtain ISE values between two points
		
		// return the ISE value of the polygonal approximation (all points)
		long double getISE(); 

		//Function for collinear points elimination
		void collinearPointsElimination();

		//Calculate te polygonal approximation from the position of dominant points
		void calculatePolygonalApproximation();
};

#endif
		
