//
// Created by Quoc Chuong Vu on 2/13/2020.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Board.h"

using namespace sudoku;
using namespace std;

Board::Board() { // creates a board that is initialized to zero
    for( line = 0; line<9 ; line++){
        for( section = 0; section<3 ; section++){
            for( num = 0; num <3; num++){
                numVal[line][section][num] = 0;
            }
        }
    }
}

void Board::printBoard() { // function to print the board out nicely.
    std::cout<< std::endl;
    std::cout<< char(218);
    for(int i = 0; i<35; i++){
        std::cout<<char(196);
    }
    std::cout << char(191)<<std::endl;
    for ( line = 0; line < 9; line++) {
        for ( section = 0; section < 3; section++) {
            std::cout<< char(179);
            for ( num = 0; num < 3; num++) {
                if(num==0)std::cout<<"  ";
                if(numVal[line][section][num]) {
                    std::cout << numVal[line][section][num];
                } else std::cout << "0";

                if(num<2)std::cout<< "  ";
            } if(!(section==2)) std::cout<< "  ";
        }
        std::cout<< "  "<<char(179);
        if(!((line==2)||(line==5))) std::cout<<std::endl;
        if((line==2)||(line==5)) {
            std::cout << std::endl << char(195);
            for (int i = 0; i < 35; i++){
                std::cout<<char(196);
            }
            std::cout << char(180) << std::endl;
        }
    }
    std::cout<< char(192);
    for(int i = 0; i<35; i++){
        std::cout<<char(196);
    }
    std::cout << char(217);
    std::cout << std::endl;
}

void Board::resetCheckNine() { // resets checker to see if there is a duplicate number
    for(int index = 0; index<10; index++){ // sets every checkNine value to zero.
        checkNine[index]=false;
    }
    line = 0;
    section = 0;
    num = 0;
}


bool Board::checkLine(int lnNum) {  // checks individual lines.
    int numCheck; // temporary number that holds index for checker
    resetCheckNine();
    for(int section1_3 = 0; section1_3 < 3 ; section1_3++){ // loops through section
        for(int num1_3 = 0; num1_3 < 3 ; num1_3++){ // loops through numbers
            numCheck = numVal[lnNum][section1_3][num1_3]; // sets the value in the data structure to temp val
            if(!checkNine[numCheck]) { // if the value is liste in index, then return false.
                if(numCheck) {
                    checkNine[numCheck] = true;
                }
            } else {return false;}
        }
    }
    return true;
}

void Board::initBoxes() {  // initializes a new Box object
    int increment = 0;
    int boxNo = 0;

    int row = 0;
    int col = 0;

    for(int i = 0; i<3 ; i++){ // 3 for loops for each dimension
        for(int j = 0; j<9 ; j++){
            for(int k =0; k<3;k++){
                box[boxNo].boxNum[row][col] = numVal[j][i][k];
                col++;
                if(col>2){
                    col = 0;
                    row++;
                    if(row>2){
                        row = 0;
                        col = 0;
                        boxNo++;
                    }
                }
            }
        }
    }
}



bool Board::checkBox(int boxNum) {  // checks if the box is appropriate with sudoku solves.
  for(int i=0;i<9;i++){
      if(!(box[i].testBox()))return false;
  }
  return true;
}

bool Board::checkColumn(int a) { // function to check if the column is appropriate.
    resetCheckNine(); // reset before going in

    int numCheck; // temp value to check if the number has been written or not.

    num = a%3;  // returns num val
    section =a/3; // returns section value;

    for(int i = 0;i<9;i++){ // for loop for checking the values.
        numCheck = numVal[i][section][num];
        if(!checkNine[numCheck-1]) {
            if(numCheck) {
                checkNine[numCheck - 1] = true;
            }
        } else {return false;}
    }

    return true;
}

void Board::fillBoard(){ // used to fill the board with numbers from a notepad file.
    char number;
    int numbers[81];
    int i=0;
    ifstream myfile;
    myfile.open("C:/Users/LittleRandom/Workspace/C++/SudokuSolver/sudoku_puzzle.txt");  // location of the puzzle in txt form
    if (myfile.is_open()) {
        while (!myfile.eof()) {
            myfile >> number; // grabs a number
            numbers[i]=int(number) - '0';
            i++;
        }
        myfile.close(); // closes the file
    }
    i = 0;
    for( line = 0; line<9 ; line++){  // writes the numbers into the multidimensional array
        for( section = 0; section<3 ; section++){
            for( num = 0; num <3; num++){
                numVal[line][section][num] = numbers[i];
                i++;
            }
        }
    }
    initBoxes(); // writes the multidimensional arrays to 9 boxes
    fillTable(); // fills a table with the same values
}

bool Board::checkSolve() { // checks if the number is appropriate for solve.
    for(int i=0;i<9;i++){
        if (!this->checkLine(i)) { // checking line by line
            return false;
        }
        if (!checkColumn(i)) {  // checking column by column
            return false;
        }
        if (!checkBox(i)) { // checking each sub box
            return false;
        }
    }
    return true;
}

bool Board::solveBoard(){ // initializer because the solve() function has to be recursive, therefor needs to have arguments.
    if(solve(0,0)) return true;
    else return false;
}

bool Board::solve(int row, int col){  // Algorithm to solve the board.
    if (col == 9) { // column can't be longer than 9 columns
        col = 0;
        row++; // everytime it passes the last column, resets and goes down 1 row.

        if (row == 9) {
            return true; // if has reached index 9 which is row 10, then it is finished!
        }
    }

    // Skip entries already filled out. They already have a value in them.
    if (table[row][col] != 0) { // skips any values that aren't 0
        return solve(row, col + 1); // recursion to the next column value
    }

    for (int value = 1; value <= 9; value++) { // once it finds an empty slot, then it cycles through the numbers to try
        if (canPlaceValue(row, col, value)) { // checks if the value works.
            table[row][col] = value; // temporarily sets the value
            cout<< "Trying value: "<< value<< endl; // for users to debug
            cout<< "Row: "<< row<< " Col: "<< col<< endl; // for users to debug and effect
            if (solve(row, col + 1)) { // if the  next value works, then keep going, otherwise end recursion.
                return true;
            }
            table[row][col] = 0; //sets the value back to empty and value before it.
        }

    }

    return false; // if the value doesn't work then return false.
}

void Board::fillTable(){ // to fill the table from the multi dimensional array.

    int row=0;
    int col=0;
    for(int i= 0; i<9;i++){ // 3 for loops for 3 dimensions
        for(int j=0; j<3; j++){
            for(int k=0;k<3;k++){
                if(col>8) {
                    col =0;
                    row++;
                }
                table[row][col]= numVal[i][j][k]; // sets the values of table to multidimensional array
                col++;
            }
        }
    }
}

bool Board::canPlaceValue(int row, int col, int intToPlace){ // checks if the value can be placed.
    fillBox();
    if(!checkSolve()){ // checks if the values can be placed, also updates the multidimensional array as well.
        return false;
    }
    return true;
}

void Board::fillBox(){ // to fill the multidimensional array from table.

    int row=0;
    int col=0;
    for(int i= 0; i<9;i++){
        for(int j=0; j<3; j++){
            for(int k=0;k<3;k++){
                if(col>8) {
                    col =0;
                    row++;
                }
                numVal[i][j][k]=table[row][col]; // replaces the values of multidimensional array with table
                col++;
            }
        }
    }
}