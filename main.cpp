//
// Created by Quoc Chuong Vu on 2/13/2020.
//

#include <iostream>
#include "Board.h"


using namespace sudoku;
using namespace std;

int main() {
    Board a;
    a.fillBoard();
    if(a.solveBoard()){
        a.printBoard();
        cout<< "SOLVE COMPLETE.";
    } else {
        cout<< "IMPOSSIBLE TO SOLVE.";
    }
    return 0;
}