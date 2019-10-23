#include "entero.hpp"
#include <iostream>
using namespace std;

int main()
{
    Entero e("0");
    cin >> e;
    cout << e << endl;
    cout << e + Entero("100000") << endl;
}
