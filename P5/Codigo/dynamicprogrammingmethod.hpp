#ifndef DYNAMIC_PROGRAMMING_METHOD_HPP
#define DYNAMIC_PROGRAMMING_METHOD_HPP

#include "algorithm.hpp"

class DynamicProgrammingMethod : public Algorithm {

private:
    void getApproxMN(const int& m, const int& n, vector<vector<int>>& father, vector<vector<long double>>& errors);

public:
    DynamicProgrammingMethod(char* filename, int numberPoints);
    ~DynamicProgrammingMethod() {}
    void apply();
};

#endif