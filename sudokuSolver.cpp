#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <cmath>
using std::sqrt;
#include <vector>
using std::vector;

class board {
    public:
        board(size_t ROWS = 9, size_t COLS = 9){
            this->ROWS = ROWS;
            this->COLS = COLS;
            for (size_t r = 0; r < ROWS; r++){
                values.push_back({});
                for (size_t c = 0; c < COLS; c++){
                    values[r].push_back(0);
                }
            }
        }
        void initializeBoard(){
            setBoardStartingValues();   
        }
        void printBoard(){
           printf("rows = %ld, cols = %ld\n",this->ROWS,this->COLS);
           for (int r = 0; r < this->ROWS; r++){
               for (int c = 0; c < this->COLS; c++){
                   printf("%d ",values[r][c]);
               }
               printf("\n");
           }
        }

    private:
        vector<vector<int>> values;
        size_t ROWS;
        size_t COLS;
        
        void setBoardStartingValues(){
            size_t boardStartingValues = 10;
            size_t potentialBoardStartingValue;
            size_t randomRow;
            size_t randomCol;
            srand(time(NULL));

            while (boardStartingValues > 0){
                potentialBoardStartingValue = (rand() % this->ROWS) + 1;
                randomRow = (rand() % this->ROWS);
                randomCol = (rand() % this->COLS); 

                if (this->values[randomRow][randomCol] == 0 && this->checkIfValueIsValid({randomRow,randomCol},potentialBoardStartingValue)){
                    this->values[randomRow][randomCol] = potentialBoardStartingValue;
                    boardStartingValues--;
                }
            }
        }

        bool checkIfValueIsValid(vector<size_t> RowCol, size_t potentialBoardStartingValue){
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
        bool checkSquare(vector<size_t> RowCol, int potentialBoardStartingValue){
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
            
            while (row > squareStartingRow){
                squareStartingRow += sqrtOfRow;
            }
            
            return squareStartingRow-sqrtOfRow;
        }
        size_t getColForSquare(int col){
            size_t sqrtOfCol  = sqrt(this->COLS);
            size_t squareStartingCol = sqrtOfCol;
            
            while (col > squareStartingCol){
                squareStartingCol += sqrtOfCol;
            }
            
            return squareStartingCol-sqrtOfCol;
        }
};

int main(){
    board b;
    b.initializeBoard();
    b.printBoard();
}
 
