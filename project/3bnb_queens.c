#include<stdio.h> 
#include<string.h> 
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#define N 8 
//int count=0;
double startprint,endprint;
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
    if (slashCodeLookup[slashCode[row][col]] || backslashCodeLookup[backslashCode[row][col]] || rowLookup[row]) 
        return 0; 
  
    return 1; 
} 

int solveNQueensUtil(int board[N][N], int col, 
    int slashCode[N][N], int backslashCode[N][N], int rowLookup[N], 
    int slashCodeLookup[], int backslashCodeLookup[] ) 
{
    if (col >= N) 
        return 1;

   #pragma omp parallel shared(board,rowLookup,slashCodeLookup,backslashCodeLookup)
    {
        #pragma for
        for (int i = 0; i < N; i++) 
        { 
            #pragma omp flush(board,rowLookup,slashCodeLookup,backslashCodeLookup)
            if ( isSafe(i, col, slashCode, backslashCode, rowLookup, slashCodeLookup, backslashCodeLookup) ) 
            {
                #pragma omp critical
                if ( isSafe(i, col, slashCode, backslashCode, rowLookup, slashCodeLookup, backslashCodeLookup) )
                {
                    board[i][col] = 1; 
                    rowLookup[i] = 1; 
                    slashCodeLookup[slashCode[i][col]] = 1; 
                    backslashCodeLookup[backslashCode[i][col]] = 1; 
        
                    if(solveNQueensUtil(board, col + 1, slashCode, backslashCode, rowLookup, slashCodeLookup, backslashCodeLookup)) 
                    {
                        return 1; 
                    }
                    else
                    {
                        board[i][col] = 0; 
                        rowLookup[i] = 0; 
                        slashCodeLookup[slashCode[i][col]] = 0; 
                        backslashCodeLookup[backslashCode[i][col]] = 0; 
                    }
                }
            } 
        }
    }  
    
    /* If queen can not be place in any row in 
        this colum col then return false */
    return 0; 
    
}
int solveNQueens() 
{ 
    int board[N][N]; 
    memset(board, 0, sizeof board); 
  
    int slashCode[N][N]; 
    int backslashCode[N][N]; 
  
    int rowLookup[N] = {0}; 
  
    int slashCodeLookup[2*N - 1] = {0}; 
    int backslashCodeLookup[2*N - 1] = {0}; 
  
    // initalize 
    #pragma omp parallel shared(slashCode,backslashCode)
    {
        #pragma for
        for (int r = 0; r < N; r++) 
        {
            for (int c = 0; c < N; c++)
            {
                slashCode[r][c] = r + c, 
                backslashCode[r][c] = r - c + 7;    
            }
                
        }
    }
    if (solveNQueensUtil(board, 0, slashCode, backslashCode, rowLookup, slashCodeLookup, backslashCodeLookup) == 0 ) 
    {
        printf("Solution does not exist"); 
        return (0); 
    }
        
     
    startprint=omp_get_wtime();
    printSolution(board); 
    endprint=omp_get_wtime();
    return 1; 
} 

int main() 
{ 
    double start=omp_get_wtime();
    solveNQueens(); 
    double end=omp_get_wtime();
    double time_elapsed_0 = end - start;
    double time_elapsed_1 =endprint - startprint;
    double time_elapsed_2=time_elapsed_0 - time_elapsed_1;
    return 0; 
} 