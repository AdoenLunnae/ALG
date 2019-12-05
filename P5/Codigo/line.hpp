#ifndef LINE_HPP
#define LINE_HPP
#include "point.hpp"

// Line will be used in implicit format ax + by + c = 0 to simplify many operations
class Line
{
	public:
		Line(const Point &p1, const Point &p2);
		Line(const Line &r); //Constructor de copia
		Line & operator=(const Line &r); //Sobrecarga de la asignacion
		inline long double getA()const //Observador
		{
 			return _a;
		};

		inline long double getB()const //Observador
		{
 			return _b;
		};

		inline long double getC()const //Observador
		{
 			return _c;
		};

		inline void setA(const long double &a) //Modificador
		{
			_a = a;
		};

		inline void setB(const long double &b) //Modificador
		{
			_b = b;
		};

		inline void setC(const long double &c) //Modificador
		{
			_c = c;
		};

		long double distancePointLine(const Point &Point)const;
		int signPointLine(const Point &Point)const;

	private:
 		long double _a;
 		long double _b;
 		long double _c;
};





#endif
