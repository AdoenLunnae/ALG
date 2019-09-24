#include <string>
#include <iostream>
#include "productoMatrices.hpp"
#include "qsort.hpp"

using namespace std;

void menu(int &opt){
    opt = 0;
    cout << "Select which algorithm you want to test:\n\t1.Quicksort\n\t2.Matrix Product\n";
    cout << "\tOption:\t";
    cin >> opt;
    while((opt != 1) && (opt != 2)){
        cout << "Invalid option. Press any key to restart\n";
        cin.ignore();
        cin.get();

    }
}


int main(){
    return 0;
}