#include <string>
#include <iostream>
#include <cstdlib>
#include "productoMatrices.hpp"
#include "qsort.hpp"

using namespace std;


#define ALGORITHM_LIST_MESSAGE "Select which algorithm you want to test:\n\t1.Quicksort\n\t2.Matrix Product\n\tOption:\t"

typedef void (*Algorithm) (string str);

void menu(int &opt, string &filename){
    int maxOption = 2;
    opt = 0;
    cout << ALGORITHM_LIST_MESSAGE;
    cin >> opt;
    while((1 >= opt) && (maxOption <= opt)){  //We assume the options are incremental
        cout << "Invalid option. Press any key to continue\n";
        cin.ignore();
        cin.get();

        if (system("CLS")) system("clear");

        cout << ALGORITHM_LIST_MESSAGE;
        cin >> opt;
    }

    cout << "Introduce the name of the output file:\t";
    cin >> filename;
}

int drawGraphic(string filename){
    string script = "#!/bin/bash\ncat << _end_ | gnuplot\nset terminal postscript eps color\n\
        set output \"grafico.eps\"\nset key right bottom\nset xlabel \"N\"\nset ylabel \"t(microseconds)\"\n\
        plot '" + filename + "' using 1:2 t \"Datos\", '" + filename + "' using 1:3 t \"Estimacion\" w l\n_end_";

    return (system(script.c_str()));
}

int main(){
    int opt;
    string filename;
    Algorithm alg[] = {getTimeDataQuickSort, getTimeDataMatrixProduct}; //We must add the algorithms here in the order they're in the menu
    menu(opt, filename);
    alg[opt-1](filename);
    if(drawGraphic(filename)) cerr << "Couldn't generate graphic";
    return 0;
}