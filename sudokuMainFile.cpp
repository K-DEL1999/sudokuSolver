#include "sudokuHeaderFile.h"

int main(){
    board b;
    printf("Unsolved sudoku\n");
    b.initializeBoard();
    b.showBoard();
    b.solve();
    printf("\nSolved sudoku\n");
    b.showBoard();
    b.displayBoard();
}

/*  run program
/   compile source files to object files first
/       
/       g++ -c sudokuSourceFile.cpp -o objectFile1
/       g++ -c sudokuMainFile.cpp -o objectFile2
/
/   then link objects into final executable
/
/       g++ objectFile1 objectFile2 -o sudoku `sdl2-config --cflags --libs` -lSDL2_ttf
/
/   finally run executable
/
/       ./sudoku
/ */ 
