#ifndef GreedyMethod_HPP
#define GreedyMethod_HPP

#include "algorithm.hpp"

//This class implements a method for obtaining a polygonal approximation
class GreedyMethod:public Algorithm
{
	private:
		
	public:
		GreedyMethod(char * fileName, int numberPointsPolygonalApproximation);
		~GreedyMethod();
		//Inherited method from algorithm class. It must be implemented in all inherited classes
		//This method calculates the polygonal approximation
		void apply();
		
};
		

#endif