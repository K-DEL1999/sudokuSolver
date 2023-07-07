#include "sudokuHeaderFile.h"

void board::setBoardStartingValues(){
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

bool board::checkIfValueIsValid(vector<int> RowCol, size_t potentialBoardStartingValue){
    return (checkRow(RowCol[0],potentialBoardStartingValue) && checkCol(RowCol[1],potentialBoardStartingValue) && checkSquare(RowCol,potentialBoardStartingValue)) ? true : false;
}

bool board::checkRow(int row, int potentialBoardStartingValue){
    for (int c = 0; c < this->COLS; c++){
        if (potentialBoardStartingValue == this->values[row][c]){
            return false;
        }
    }
    return true;
}
bool board::checkCol(int col, int potentialBoardStartingValue){
    for (int r = 0; r < this->ROWS; r++){
        if (potentialBoardStartingValue == this->values[r][col]){
            return false;
        }
    } 
    return true;
}
bool board::checkSquare(vector<int> RowCol, int potentialBoardStartingValue){
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
size_t board::getRowForSquare(int row){
    size_t sqrtOfRow  = sqrt(this->ROWS);
    size_t squareStartingRow = sqrtOfRow;
    
    while (row >= squareStartingRow){
        squareStartingRow += sqrtOfRow;
    }
    
    return squareStartingRow-sqrtOfRow;
}
size_t board::getColForSquare(int col){
    size_t sqrtOfCol  = sqrt(this->COLS);
    size_t squareStartingCol = sqrtOfCol;
    
    while (col >= squareStartingCol){
        squareStartingCol += sqrtOfCol;
    }
    
    return squareStartingCol-sqrtOfCol;
}

void board::solveBoard(){ 
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

void board::getPossibleCellValues(unordered_map<int,vector<int>> &cellPossibleValues, int cellNumber){
    vector<int> possibleValues;
    
    for (int i = 1; i <= this->ROWS; i++){
        if (checkIfValueIsValid({cellNumber/this->ROWS,cellNumber%this->ROWS},i)){
            possibleValues.push_back(i);
        }
    }

    cellPossibleValues.insert({cellNumber,possibleValues});
}

void board::printBoard(){
   for (int r = 0; r < this->ROWS; r++){
       for (int c = 0; c < this->COLS; c++){
           printf("%d ",values[r][c]);
       }
       printf("\n");
   }
   printf("\n");
}


void board::displayBoard(){
    int screenWidth = 900;
    int screenHeight = 900;
    bool done = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

    TTF_Init();
    if (TTF_Init() < 0){
        printf("We got a big problem\n");
    }
    TTF_Font* Sans = TTF_OpenFont("DejaVuSans.ttf",36);
    if (Sans == NULL){
        printf("WE got a PROBLEM, \n%s\n",TTF_GetError());
    }
    SDL_Surface* surfaceCellValue;
    SDL_Texture* textureCellValue;
    
    SDL_Event event;
    bool isRunning = true;
   
    /* 
    vector<vector<int>> values = {{5,3,9,0,0,0,4,1,0},
                                  {7,0,8,3,0,4,0,0,0},
                                  {6,4,1,0,0,0,7,3,0},
                                  {4,0,2,0,0,0,0,7,0},
                                  {3,8,0,7,0,1,6,4,0},
                                  {1,0,7,4,6,8,2,5,3},
                                  {0,0,0,0,0,0,0,0,0},
                                  {9,0,0,0,4,0,5,8,0},
                                  {8,0,4,0,5,0,0,0,6}};
    */
    int cellWidth = (screenWidth/2) / values.size(); 
    int cellHeight = (screenHeight/2) / values.size();   

    while(isRunning){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN && done){
                if (event.key.keysym.sym == SDLK_SPACE){
                    printf("Hello\n");
                    this->solveBoard();
                    printf("boardSolved\n");
                    done = 0;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_Rect rect;
       
        for (int row = 0; row < values.size(); row++){
            for (int column = 0; column < values[row].size(); column++){
                rect.x = screenWidth/4 + column*cellWidth;
                rect.y = screenHeight/4 + row*cellHeight;
                rect.w = cellWidth;
                rect.h = cellHeight;
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderDrawRect(renderer, &rect);
                if (!values[row][column]){
                    surfaceCellValue = TTF_RenderText_Solid(Sans," ",{0,0,0,255});
                }
                else {
                    surfaceCellValue = TTF_RenderText_Solid(Sans,(to_string(values[row][column])).c_str(),{0,0,0,255});
                }
                textureCellValue = SDL_CreateTextureFromSurface(renderer, surfaceCellValue);
                SDL_RenderCopy(renderer, textureCellValue, NULL, &rect);
            }
        } 
               
        SDL_SetRenderDrawColor(renderer,255,200,200,255);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(surfaceCellValue);
    SDL_DestroyTexture(textureCellValue);
    TTF_Quit();   
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();  
}

