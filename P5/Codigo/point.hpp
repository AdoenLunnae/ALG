#ifndef Point_HPP
#define Point_HPP

#include <math.h>
/* Interface functions for TAD Point */
class Point
{
	private:
		/* Cartesian coordinates */
 		long double _x; 
 		long double _y; 
 		/* Polar coordinates */
 		long double _radio; 
 		long double _angle;

  	public:
		Point()
		{
			_x = 0.0;
			_y = 0.0;
			_radio = 0.0;
			_angle = 0.0;
		};
		Point(long double x, long double y)
    	{ 
			_x = x;
			_y = y;
			_radio = 0.0;
			_angle = 0.0;
		};


    	bool operator==(const Point &p) const
    	{
			if (fabs(getX()- p.getX()) < 0.0000000001 && fabs(getY() - p.getY()) < 0.0000000001)
				return true;
			return false;
		};
		
		bool operator!=(const Point &p) const
		{
			if (fabs(getX()- p.getX()) < 0.0000000001 && fabs(getY() - p.getY()) < 0.0000000001)
				return false;
			return true;
		};
		

		inline long double getX()const 
		{
			return _x;
		};
			
		inline long double getY()const 
		{
			return _y;
		};

		inline long double getRadio()const 
		{
			return _radio;
		};

		inline long double getAngle()const 
		{
			return _angle;
		};

		inline void setX(const long double &x) 
		{
			_x = x;
		};

		inline void setY(const long double &y) 
		{
			_y = y;
		};

		inline void setRadio(const long double &radio) 
		{
			_radio = radio;
		};

		inline void setAngle(const long double &angle) //Modificador
		{
			_angle = angle;
		};

		long double distancePoints(const Point &p)const;
	  	int getChainCodePoint(const Point &p)const;
};


#endif
