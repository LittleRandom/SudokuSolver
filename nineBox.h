//
// Created by Quoc Chuong Vu on 2/14/2020.
//

#ifndef SUDOKUSOLVER_NINEBOX_H
#define SUDOKUSOLVER_NINEBOX_H

namespace sudoku {
    class nineBox {
    public:
        int boxNum[3][3];
        bool checkNum[9];

        nineBox();
        void testPrint();
        bool testBox();
        void insertNum();

    };


}

#endif //SUDOKUSOLVER_NINEBOX_H
