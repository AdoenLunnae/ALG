#ifndef COLLINEARSUPPRESSION_HPP
#define COLLINEARSUPPRESSION_HPP

#include "algorithm.hpp"

//This class implements a method for obtaining a polygonal approximation
class CollinearSuppressionMethod:public Algorithm
{
	private:
		
	public:
		CollinearSuppressionMethod(char * fileName);
		~CollinearSuppressionMethod();
		//Inherited method from algorithm class. It must be implemented in all inherited classes
		//This method calculates the polygonal approximation
		void apply();
		
};
		

#endif