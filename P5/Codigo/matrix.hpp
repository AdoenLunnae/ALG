#ifndef Matrix_H
#define Matrix_H

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

class Matrix
{
	private:
    	vector < vector < long double > > _m;
    	int _r;
    	int _c;
    	void reserveMemory()
		{
			_m = vector< vector< long double > >(getRows(), vector< long double >(getColumns()));
		}

  	public:
  		Matrix()
  		{};
		Matrix(const int &r, const int &c)
		{
			setRows(r);
			setColumns(c);
		
			reserveMemory();

			for(int i = 0; i < getRows(); i++)
			{
				for(int j = 0; j < getColumns(); j++)
				{
				   setElement(i, j, 0.0); //Initialise to 0 all elements
				}
			}  
		}

		//Copy constructor.
		Matrix(const Matrix &m)
		{
			if (this != &m)
				*this = m;
		}

		~Matrix()
		{
		}

		inline int getRows() const
		{
			return _r;
		}

		inline int getColumns() const
		{
			return _c;
		}

		inline void setRows(const int &r)
		{
			_r = r;
		}

		inline void setColumns(const int &c)
		{
			_c = c;
		}

		inline long double getElement(const int &r, const int &c) const
		{
			assert(r >= 0 and r < getRows());
      		assert(c >= 0 and c < getColumns());
			
			return _m[r][c];
		}

		inline void setElement(const int &r, const int &c, const long double &x)
		{
			assert(r >= 0 and r < getRows());
      		assert(c >= 0 and c < getColumns());
			_m[r][c] = x;
		}

		void printMatrix() const
		{
			for(int i = 0; i < getRows(); i++)
			{
				for(int j = 0; j < getColumns(); j++)
				  cout << getElement(i, j) << " ";
				cout << "\n";
			}
		}

		void inputMatrix()
		{
			long double x;
			for(int i = 0; i < getRows(); i++)
			{
				for(int j = 0; j < getColumns(); j++)
				{
				  cout << " element(" << i << "," << j << "): ";
				  cin >> x;
				  setElement(i, j, x);
				}
			}
		}
};


#endif
