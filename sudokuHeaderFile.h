#ifndef SUDOKU_HEADER_FILE
#define SUDOKU_HEADER_FILE
#include <time.h>
#include <cmath>
using std::sqrt;
#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;
#include <stack>
using std::stack;
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <string>
using std::to_string;

class board {
    public:
        board(size_t ROWS = 9, size_t COLS = 9){
            this->ROWS = ROWS;
            this->COLS = COLS;
            for (size_t r = 0; r < ROWS; r++){
                this->values.push_back({});
                for (size_t c = 0; c < COLS; c++){
                    this->values[r].push_back(0);
                }
            }
        }
        void initializeBoard(){
            this->setBoardStartingValues();   
        }
        void solve(){
            this->solveBoard();
        }
        void showBoard(){
            this->printBoard();
        }
        void displayBoard();

    private:
        vector<vector<int>> values;
        int ROWS;
        int COLS;

        SDL_Window *window;
        SDL_Renderer *renderer;
        TTF_Font *Sans;
        SDL_Event event;
        bool isRunning;        
        
        void setBoardStartingValues();
        bool checkIfValueIsValid(vector<int> RowCol, size_t potentialBoardStartingValue);
        bool checkRow(int row, int potentialBoardStartingValue);
        bool checkCol(int col, int potentialBoardStartingValue);
        bool checkSquare(vector<int> RowCol, int potentialBoardStartingValue);
        size_t getRowForSquare(int row);
        size_t getColForSquare(int col);
        void solveBoard(); 
        void getPossibleCellValues(unordered_map<int,vector<int>> &cellPossibleValues, int cellNumber);
        void printBoard();
};

#endif

