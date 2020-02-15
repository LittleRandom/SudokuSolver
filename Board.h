//
// Created by Quoc Chuong Vu on 2/13/2020.
//

#ifndef SUDOKUSOLVER_BOARD_H
#define SUDOKUSOLVER_BOARD_H

#include "nineBox.h"

namespace sudoku {

    class Board {
    private:
        int numVal[9][3][3];  // multidimensional array just for fun
        bool checkNine[10]; // array of bool to check for duplicate numbers
        short line; // index for 3rd dimension
        short section; // index for 2nd dimension
        short num; // index for 1st dimension
        int table[9][9]; // when i gave up on writing an algorithm for multidimensional arrays. :(
        nineBox box[9]; // each subsection of the puzzle in a box structure.


        /*TESTING FUNCTIONS */

        // Debugging functions

        /* FUNCIONALS*/

        // Used for solving
        void initBoxes(); // initiallizes the individual boxes for testing.
        void resetCheckNine(); // resets the checking function that checks for multiple numbers
        void fillBox(); // fills the multidimensional array with table values.
        void fillTable(); // fills a table with the multidimensional array
        bool canPlaceValue(int row, int col, int intToPlace); // checks if the value can be placed or not.

        /*CHECKING FUNCTIONS*/

        // Used to check for errors.

        bool checkBox(int); // checks each box structure if it works.
        bool checkLine(int); // checks the row if it follows sudoku rules.
        bool checkColumn(int); // checks a collumn.

        bool checkSolve(); // checks if the number fits into the board.
        bool solve(int, int); // recursive function that solves the board.

    public:

        /* Everything the users can use.*/

        bool solveBoard();
        Board();
        void printBoard(); // Prints the board to console.
        void fillBoard(); // fills the Board from the text.

    };

}
#endif //SUDOKUSOLVER_BOARD_H
