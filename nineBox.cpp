//
// Created by Quoc Chuong Vu on 2/14/2020.
//

#include "nineBox.h"
#include <iostream>

using namespace sudoku;

void nineBox::insertNum() {
    int i=0;
    for(int row=0; row<3;row++){
        for(int col=0;col<3;col++){
           i++;
            boxNum[row][col] = i;
        }
    }
}

void nineBox::testPrint(){
    for(int row=0; row<3;row++){
        for(int col=0;col<3;col++){
            std::cout << boxNum[row][col];
        }
    }
}

nineBox::nineBox() {
    for(int row=0; row<3;row++){
        for(int col=0;col<3;col++){
            boxNum[row][col]=0;
        }
    }
    for(int i=0;i<9;i++){
        checkNum[i]= false;
    }
}

bool nineBox::testBox(){

    for(int i =0; i<9;i++){
        checkNum[i] = false;
    }

    int checkNumIndex;
    for(int row=0; row<3;row++){
        for(int col=0;col<3;col++){
            checkNumIndex = boxNum[row][col];
            if(!checkNum[checkNumIndex-1]){
                if(checkNumIndex) {
                    checkNum[checkNumIndex-1] = true;
                }
            } else {
                return false;
            }
        }
    }
    return true;
}