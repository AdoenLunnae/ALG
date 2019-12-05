#include <vector>    // necesario para el contenedor Vector2D
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <cassert>
#include "digitalcurve.hpp"
#include "point.hpp"
#include "line.hpp"



using namespace std;

// TAD  DigitalCurve 
//
DigitalCurve::DigitalCurve()	
{
}


//Constructor. Crea un DigitalCurve a partir de un fichero
DigitalCurve::DigitalCurve(char *fileName)	
{
	long double x, y;
  Point point;
  
  ifstream pf(fileName);
  if (!pf)
  {
    cout << "\n File does not exist";
    exit(0);
  }
  
  //read from file
  while ( pf >> x >> y)
  {
    point.setX(x);
    point.setY(y);
    point.setRadio(0.0);
    point.setAngle(0.0);
    _point.push_back(point);
  }
  pf.close();
}

//Destructor
DigitalCurve::~DigitalCurve() 
{
}

//Copy Constructor

DigitalCurve::DigitalCurve(const DigitalCurve &digitalCurve)
{
  if (this != &digitalCurve)
    *this = digitalCurve;
}


long double DigitalCurve::longDigitalCurve()const
{
 	long double longitud = 0.0;
 	Point p1, p2;
 	

 	for(int i = 0; i < getNumberPointsDigitalCurve() - 1; i++)
 	{
  	p1 = getPointDigitalCurve(i);
  	p2 = getPointDigitalCurve(i + 1);
  	longitud += p1.distancePoints(p2);
 	}
 	return longitud;
}


void DigitalCurve::saveDigitalCurve(char *fileName)const
{
	Point point;
 	ofstream pf(fileName);

 	if (!pf) 
  {
    cout << "Error opening file \n";
    exit(0);
  }
 
 	// The points of the digital curve are saved in a file 
 	for(int i = 0 ;i < getNumberPointsDigitalCurve() ; i++)
	{
		point = getPointDigitalCurve(i);
   	pf << point.getX() << " " << point.getY() << "\n";
	}

  pf.close();
}


void DigitalCurve::calculateChainCodeDigitalCurve()
{
 	int chainCode; 
 	Point current, next;

  //The chain code of the n-1 first points are calculated

 	for(int i = 0; i <  getNumberPointsDigitalCurve() - 1; i++)
 	{
		current = getPointDigitalCurve(i);
    next = getPointDigitalCurve(i + 1);
  	chainCode = current.getChainCodePoint(next);
  	_chainCode.push_back(chainCode);
 	}
  //The chain code of the last point is similar to the first point
  if (isClosed()) //Closed curve
  {
    //cout << "Es cerrada \n";
    _chainCode.push_back(getChainCodePoint(0)); //The value of chain code of first and last are equal
  }
  else
  {
    //cout << "No Es cerrada \n";
    _chainCode.push_back(10000); //So, it never will be eliminated as collinear point
  }
  //for(int i = 0; i <  getNumberPointsDigitalCurve(); i++)
  //{
    //cout << "Chain code of point " << i << " = " << _chainCode[i] << endl;
  //}
}

//It calculates ISE between two points
long double DigitalCurve::getISE(int initial, int final) const
{
	assert(initial >= 0 and initial < getNumberPointsDigitalCurve());
	assert(final >= 0 and final < getNumberPointsDigitalCurve());
	
	long double ise = 0.0;
	long double error = 0.0;
	int begin, end, limite;
	
	if (initial == final)
		return 0.0;
        
  Point p;
  //Auxiliar variables to save initial amd final points
  begin = initial;
  end = final;
	
	Line line(getPointDigitalCurve(initial), getPointDigitalCurve(final));
	
  if (getPointDigitalCurve(initial) != getPointDigitalCurve(final)) //It is not a bucle
  { 
  //Error are obtained from distances from points to a line
    if (initial < final)
    {
      for (int i = begin; i <= end; i++)
      {
              error = line.distancePointLine(getPointDigitalCurve(i));
              ise += error * error;
      }
    }
    else 
    {
      int limit = getNumberPointsDigitalCurve() - 1;
      if (isClosed()) //Closed curve. First point duplicated and its error is not calculated
        limit--;
      
      for (int i = begin; i <= limite; i++)
      {
        error = line.distancePointLine(getPointDigitalCurve(i));
        ise += error * error;
      }
      for (int i = 0; i <= end; i++)
      {
        error = line.distancePointLine(getPointDigitalCurve(i));
        ise += error * error;
      }
    }
  }
  else //It is a bucle 
  { 
    if (initial < final)
    {
      for (int i = begin; i <= end; i++)
      {
        error = getPointDigitalCurve(initial).distancePoints(getPointDigitalCurve(i));
        ise += error * error;
      }
    }
    else 
    {
      int limit = getNumberPointsDigitalCurve() - 1;
      if (isClosed()) //Closed curve. First point duplicated and its error is not calculated
        limit--;
      
      for (int i = begin; i <= limite; i++)
      {
        error = getPointDigitalCurve(initial).distancePoints(getPointDigitalCurve(i));
        ise += error * error;
      }
      for (int i = 0; i <= end; i++)
      {
              error = getPointDigitalCurve(initial).distancePoints(getPointDigitalCurve(i));
              ise += error * error;
      }
    }
  }
	
	return ise;	
}


//It calculates eMax between two points and it position
void DigitalCurve::getEmax(int initial, int final, long double &eMax, int &position) const
{
  //Ifthey are the same point
	if  (initial == final)
  {
    eMax = 0.0;
    position = initial;
    return;
  }
  assert(initial!=final);
	assert(initial >= 0 and initial <= getNumberPointsDigitalCurve() - 1);
	assert(final >= 0 and final <= getNumberPointsDigitalCurve() - 1);
	
	eMax = 0.0;
	position = initial;
	long double error = 0.0;
	int begin, end;

  //Auxiliar variables to save initial amd final points
  begin = initial;
  end = final;
	
	
  if (getPointDigitalCurve(initial) != getPointDigitalCurve(final)) //It is not a bucle
  {
    Line line(getPointDigitalCurve(initial), getPointDigitalCurve(final));
    if (initial < final)
    {
      for (int i = begin; i <= end; i++)
      {
        error = line.distancePointLine(getPointDigitalCurve(i));
        if (error > eMax)
        {
          eMax = error;
          position = i;
        }
      }
    }
    else if (initial > final)
    {
      int limit = getNumberPointsDigitalCurve() - 1;
      if (isClosed()) //Closed curve. First point duplicated and its error is not calculated
        limit--;

      for (int i = begin; i <= limit; i++)
      {
        error = line.distancePointLine(getPointDigitalCurve(i));
        if (error > eMax)
        {
          eMax = error;
          position = i;
        }
      }
      for (int i = 0; i <= end; i++)
      {
        error = line.distancePointLine(getPointDigitalCurve(i));
        if (error > eMax)
        {
          eMax = error;
          position = i;
        }
      }
    }
  }
  else //It is a bucle 
  { 
    if (initial < final)
      {
        for (int i = begin; i <= end; i++)
        {
          error = getPointDigitalCurve(initial).distancePoints(getPointDigitalCurve(i));
          if (error > eMax)
          {
            eMax = error;
            position = i;
          }
        }
      }
      else if (initial > final)
      {
        int limit = getNumberPointsDigitalCurve() - 1;
        if (isClosed()) //Closed curve. First point duplicated and its error is not calculated
          limit--;

        for (int i = begin; i <= limit; i++)
        {
          error = getPointDigitalCurve(initial).distancePoints(getPointDigitalCurve(i));
          if (error > eMax)
          {
            eMax = error;
            position = i;
          }
        }
        for (int i = 0; i <= end; i++)
        {
          error = getPointDigitalCurve(initial).distancePoints(getPointDigitalCurve(i));
          if (error > eMax)
          {
            eMax = error;
            position = i;
          }
        }
      }
      
  }
}






