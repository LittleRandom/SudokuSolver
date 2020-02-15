cmake_minimum_required(VERSION 3.15)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 14)

add_executable(SudokuSolver main.cpp Board.cpp nineBox.cpp)