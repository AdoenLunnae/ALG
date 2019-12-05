#include <math.h>
#include <cassert>
#include "line.hpp"
#include "point.hpp"

/* La Line se va a representar en forma general ax + by + c = 0 */

Line::Line(const Point &p1, const Point &p2)
{
	//assert(p1 != p2);
 	setA(p1.getY() - p2.getY());
 	setB(p2.getX() - p1.getX());
	setC(p1.getX() * (-(p1.getY() - p2.getY())) + p1.getY() * (-(p2.getX() - p1.getX())));
}

Line::Line(const Line &r) //Constructor de copia
{
	setA(r.getA());
	setB(r.getB());
	setC(r.getC());
}


long double Line::distancePointLine(const Point &Point)const
{
 	long double distance;

 	distance = fabs( getA() * Point.getX() + getB() * Point.getY() + getC()) / pow( getA() * getA() + getB() * getB(), 0.5);

 	return distance;
}

int Line::signPointLine(const Point &Point)const
{  
  long double value;
  value = getA() * Point.getX() + getB() * Point.getY() + getC();
  //printf("Valor = %lf\n", valor);

  if (value > 0.0)
    return 1;
  else if (value < 0.0)
    return -1;
  else
    return 0;
}
