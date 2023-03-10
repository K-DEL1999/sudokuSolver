#include <cstdio>
#include <time.h>
#include <cmath>
using std::sqrt;
#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;
#include <stack>
using std::stack;


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

    private:
        vector<vector<int>> values;
        int ROWS;
        int COLS;
        
        void setBoardStartingValues(){
            //if you want to set a custom board uncomment below and adjust
            /*this->values = {{5,3,9,0,0,0,4,1,0},
                            {7,0,8,3,0,4,0,0,0},
                            {6,4,1,0,0,0,7,3,0},
                            {4,0,2,0,0,0,0,7,0},
                            {3,8,0,7,0,1,6,4,0},
                            {1,0,7,4,6,8,2,5,3},
                            {0,0,0,0,0,0,0,0,0},
                            {9,0,0,0,4,0,5,8,0},
                            {8,0,4,0,5,0,0,0,6}};*/
            //remember to comment out everything below this comment in the function to use
            //the above board initializer!!
            int randRow;
            int randCol;
            int randValue;
            int numberOfStartingValues = 9;

            srand(time(NULL));

            while (numberOfStartingValues > 0){
                randValue = rand() % this->ROWS + 1;
                randRow = rand() % this->ROWS;
                randCol = rand() % this->COLS;
                while (this->values[randRow][randCol] != 0 || !checkIfValueIsValid({randRow,randCol},randValue)){
                    randRow = rand() % this->ROWS;
                    randCol = rand() % this->COLS;
                }
                this->values[randRow][randCol] = randValue;
                numberOfStartingValues--;
            }
        }

        bool checkIfValueIsValid(vector<int> RowCol, size_t potentialBoardStartingValue){
            return (checkRow(RowCol[0],potentialBoardStartingValue) && checkCol(RowCol[1],potentialBoardStartingValue) && checkSquare(RowCol,potentialBoardStartingValue)) ? true : false;
        }

        bool checkRow(int row, int potentialBoardStartingValue){
            for (int c = 0; c < this->COLS; c++){
                if (potentialBoardStartingValue == this->values[row][c]){
                    return false;
                }
            }
            return true;
        }
        bool checkCol(int col, int potentialBoardStartingValue){
            for (int r = 0; r < this->ROWS; r++){
                if (potentialBoardStartingValue == this->values[r][col]){
                    return false;
                }
            } 
            return true;
        }
        bool checkSquare(vector<int> RowCol, int potentialBoardStartingValue){
            size_t squareStartingRow = getRowForSquare(RowCol[0]);
            size_t squareStartingCol = getColForSquare(RowCol[1]);

            for (int r = squareStartingRow; r < squareStartingRow+sqrt(this->ROWS); r++){
                for (int c = squareStartingCol; c < squareStartingCol+sqrt(this->COLS); c++){
                    if (potentialBoardStartingValue == this->values[r][c]){
                        return false;
                    }   
                }
            }
            return true;
        }
        size_t getRowForSquare(int row){
            size_t sqrtOfRow  = sqrt(this->ROWS);
            size_t squareStartingRow = sqrtOfRow;
            
            while (row >= squareStartingRow){
                squareStartingRow += sqrtOfRow;
            }
            
            return squareStartingRow-sqrtOfRow;
        }
        size_t getColForSquare(int col){
            size_t sqrtOfCol  = sqrt(this->COLS);
            size_t squareStartingCol = sqrtOfCol;
            
            while (col >= squareStartingCol){
                squareStartingCol += sqrtOfCol;
            }
            
            return squareStartingCol-sqrtOfCol;
        }
        
        void solveBoard(){ 
            stack<int> cellStack;
            unordered_map<int,vector<int>> cellPossibleValues;
            int curRow = 0;
            int curCol = 0;
            int cellNumber;

            while(curRow != this->ROWS){
                if (values[curRow][curCol] == 0){
                    cellNumber = (curRow*this->ROWS)+curCol;
                    cellStack.push(cellNumber);
                    
                    if (cellPossibleValues.count(cellNumber) == 0){
                        this->getPossibleCellValues(cellPossibleValues,cellNumber);
                    }
                    if (cellPossibleValues[cellNumber].empty()){
                        cellStack.pop(); 
                        cellPossibleValues.erase(cellNumber);
                        curRow = cellStack.top() / this->ROWS;
                        curCol = cellStack.top() % this->ROWS;
                        values[curRow][curCol] = 0;
                        cellStack.pop();
                        if (cellStack.empty()){
                            printf("\nunsolvable sudoku----...\n");
                            break;
                        }
                    }
                    else { 
                        values[curRow][curCol] = cellPossibleValues[cellNumber].back();
                        cellPossibleValues[cellNumber].pop_back();
                        curCol++;
                    } 
                }
                else {
                    curCol++;
                }
                if (curCol == this->COLS){
                    curCol = 0;
                    curRow++;
                }
            }
        }
        void getPossibleCellValues(unordered_map<int,vector<int>> &cellPossibleValues, int cellNumber){
            vector<int> possibleValues;
            
            for (int i = 1; i <= this->ROWS; i++){
                if (checkIfValueIsValid({cellNumber/this->ROWS,cellNumber%this->ROWS},i)){
                    possibleValues.push_back(i);
                }
            }

            cellPossibleValues.insert({cellNumber,possibleValues});
        }
        void printBoard(){
           for (int r = 0; r < this->ROWS; r++){
               for (int c = 0; c < this->COLS; c++){
                   printf("%d ",values[r][c]);
               }
               printf("\n");
           }
           printf("\n");
        }
};

int main(){
    board b;
    printf("Unsolved sudoku\n");
    b.initializeBoard();
    b.showBoard();
    b.solve();
    printf("\nSolved sudoku\n");
    b.showBoard();
}
 
