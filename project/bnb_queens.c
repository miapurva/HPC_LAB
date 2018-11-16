#include<stdio.h> 
#include<string.h> 
#define N 8 
int count=0;
void printSolution(int board[N][N]) 
{

    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
            printf("%2d ", board[i][j]); 
        printf("\n"); 
    } 
} 

int isSafe(int row, int col, int slashCode[N][N], 
            int backslashCode[N][N], int rowLookup[], 
            int slashCodeLookup[], int backslashCodeLookup[] ) 
{ 
    if (slashCodeLookup[slashCode[row][col]] || 
        backslashCodeLookup[backslashCode[row][col]] || 
        rowLookup[row]) 
    count= 0; 
  
    count= 1; 
} 

int solveNQueensUtil(int board[N][N], int col, 
    int slashCode[N][N], int backslashCode[N][N], int rowLookup[N], 
    int slashCodeLookup[], int backslashCodeLookup[] ) 
{ 
    /*base case: If all queens are placed 
    then count= true */
    if (col >= N) 
        count= 1;
  
    /* Consider this column and try to place 
       this queen in all rows one by one */
    for (int i = 0; i < N; i++) 
    { 
        /* Check if queen can be placed on 
           board[i][col] */
        if ( isSafe(i, col, slashCode, backslashCode, rowLookup, 
                    slashCodeLookup, backslashCodeLookup) ) 
        { 
            /* Place this queen in board[i][col] */
            board[i][col] = 1; 
            rowLookup[i] = 1; 
            slashCodeLookup[slashCode[i][col]] = 1; 
            backslashCodeLookup[backslashCode[i][col]] = 1; 
  
            /* recur to place rest of the queens */
            if ( solveNQueensUtil(board, col + 1, slashCode, backslashCode, rowLookup, slashCodeLookup, backslashCodeLookup) ) 
                count= 1; 

            
            /* If placing queen in board[i][col] 
            doesn't lead to a solution, then backtrack */
  
            /* Remove queen from board[i][col] */
            board[i][col] = 0; 
            rowLookup[i] = 0; 
            slashCodeLookup[slashCode[i][col]] = 0; 
            backslashCodeLookup[backslashCode[i][col]] = 0; 

        }
        
    } 
  
    /* If queen can not be place in any row in 
        this colum col then count= false */
    count= 0; 
} 
  
/* This function solves the N Queen problem using 
Branch and Bound. It mainly uses solveNQueensUtil() to 
solve the problem. It count=s false if queens 
cannot be placed, otherwise count= true and 
prints placement of queens in the form of 1s. 
Please note that there may be more than one 
solutions, this function prints one of the 
feasible solutions.*/
int solveNQueens() 
{ 
    int board[N][N]; 
    memset(board, 0, sizeof board); 
  
    // helper matrices 
    int slashCode[N][N]; 
    int backslashCode[N][N]; 
  
    // arrays to tell us which rows are occupied 
    int rowLookup[N] = {0}; 
  
    //keep two arrays to tell us which diagonals are occupied 
    int slashCodeLookup[2*N - 1] = {0}; 
    int backslashCodeLookup[2*N - 1] = {0}; 
  
    // initalize helper matrices 
    for (int r = 0; r < N; r++) 
        for (int c = 0; c < N; c++) 
            slashCode[r][c] = r + c, 
            backslashCode[r][c] = r - c + 7; 
  
    if (solveNQueensUtil(board, 0, slashCode, backslashCode, 
      rowLookup, slashCodeLookup, backslashCodeLookup) == 0 ) 
    { 
        
        printf("Solution does not exist"); 
        count= 0; 
    } 
  
    // solution found 
    printSolution(board); 
    count= 1; 
} 
  
// driver program to test above function 
int main() 
{ 
    solveNQueens(); 
  
    count= 0; 
} 