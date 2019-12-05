#ifndef DigitalCurve_HPP
#define DigitalCurve_HPP
   
#include "point.hpp"
#include <vector>    
#include <algorithm>

using namespace std; 

//Tad DigitalCurve
class DigitalCurve
{
	private:
		vector <Point> _point; /* Vector of Points for DigitalCurve */		
		vector<int> _chainCode; /* Chain code for every point of the curve */
		
	public:
		DigitalCurve(); 	
		DigitalCurve(char *fileName); //It creates a digital curve from a file
		DigitalCurve(const DigitalCurve &curve); //Constructor copy
		~DigitalCurve();
		
		inline int getNumberPointsDigitalCurve()const 
    	{
			return _point.size();
		}

		//returns the point in position of the digital vuve
		inline Point getPointDigitalCurve(const int &position)const 
		{
			return _point[position];
		}

		//set the point in position of the digital vuve
		inline void setPointDigitalCurve(const Point &p, const int &position) 
		{
			_point[position] = p; 
		}
        
        //Insert point in digital curve in the last position
        inline void insertPointDigitalCurve(const Point &p)
        {
        	_point.push_back(p);
        }

        //returns the chain code for the point in position
		inline int getChainCodePoint(const int &position)const 
		{
 			return _chainCode[position];
		}

		//set the chain code for the point in position
		inline void setChainCodePoint(const int &position, const int &code)  //Modificador
		{
 			_chainCode[position] = code;
		}

		
		//This function tests if the digital curve is closed
		inline bool isClosed() const
    	{
      		return _point[0] == _point[getNumberPointsDigitalCurve() -1];
    	}
	
		//Return the length of the digital curve
		long double longDigitalCurve()const;
		
		//Save digital curve in a file
		void saveDigitalCurve(char *nombre)const;

		//Load digital curve from a file
		void loadDigitalCurve(char *nombre);

		//Calculate the chain code of all points of the curve
		void calculateChainCodeDigitalCurve();

		//Calculate the acumulated error between two points of the curve
		long double getISE(int initial, int final)const;

		//Calculate the maximum error between two points of the curve and its position
		void  getEmax(int initial, int final, long double &maxError, int &position)const;

};




#endif
