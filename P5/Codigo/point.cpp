#include "point.hpp"
#include <math.h>
/* Interface functions for TAD Point */


long double Point::distancePoints(const Point &p)const
{
 	long double dx,dy;

 	dx = getX() - p.getX();
 	dy = getY() - p.getY();

 	return (pow (dx * dx + dy * dy, 0.5));
}


int Point::getChainCodePoint(const Point &nextPoint)const
{	
 	long double angle; //Angle between two consecutive points
 	int chainCode; //chain code to obtain
 	long double dx,dy; //increments between actual and next points

 	// Obtencion de los incrementos
 	dx = nextPoint.getX() - getX();
 	dy = nextPoint.getY() - getY();

 	//We Calculate the angle
 	angle = atan2(dy,dx);
 
 	// If angle < 0, 2PI are added
 	if (angle < 0.0) 
  	angle = angle + 2.0 * M_PI;

 	// Angle is converted to grades
 	angle = (180.0 / M_PI) * angle;

 	// Chain code is obtained. Value 0 for 90 grades and 1 for 0 grades.
 	if (angle > 337.5)
  	chainCode = 2;
 	else if (angle > 292.5)
  	chainCode = 3;
 	else if (angle > 247.5)
  	chainCode = 4;
 	else if (angle > 202.5)
  	chainCode = 5;
 	else if (angle > 157.5)
  	chainCode = 6;
 	else if (angle > 112.5)
  	chainCode = 7;
 	else if (angle > 67.5)
  	chainCode = 0;
 	else if (angle > 22.5)
  	chainCode = 1;
 	else
  	chainCode = 2;

 	return chainCode;
}
