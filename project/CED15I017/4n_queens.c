/*
Submission By Yutika Kulwe, CED15I017
compile: g++ -fopenmp -o nqueens 4n_queens.c
run:	 ./nqueens number_of_queens number_of_threads
eg. ./nqueens 8 1
Here, 8 is the number of queens and 1 is the number of thread to execute 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define MAX_N 16
void print_solution(int queen_rows[ ], int n)
{
	#pragma omp critical
    {
	    printf("\n");
	    for (int i = 0; i < n; i++)
	    {
	        int j;
		    for (j = 0; j < n; j++)
		    {
			    if (queen_rows[i] == j)	
			    	printf("|X");
			    else 
			    	printf("| ");
		    }
		    printf("|\n");
	    }
	    printf("\n");
	}			
}

int check_for_clash(int queen_rows[MAX_N], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = i+1; j < n; j++)
		{
			// two queens in the same row or column -> not a solution!
			if (queen_rows[i] == queen_rows[j]) 
				return 0;
			
			// two queens in the same diagonal -> not a solution!
			if (queen_rows[i] - queen_rows[j] == i - j ||
			    queen_rows[i] - queen_rows[j] == j - i)
			    return 0;
		}
	}

	return 1;
}

int main(int argc, char* argv[])
{
	//number_of_queens
	int n;

    int max_iter = 1;
    
    double start_time, end_time;
    int num_sol = 0;
        
	{
	    //number of threads
	    int num_workers;

        int i;
	
        n = (argc > 1) ? atoi(argv[1]) : 8;
        num_workers = (argc > 2) ? atoi(argv[2]) : 30;
        
        omp_set_num_threads(num_workers);
	        
        for (i = 0; i < n; i++)
        {
            max_iter *= n;
        }
    }
  
    start_time = omp_get_wtime();
    
	int iter;
	#pragma omp parallel
	{
		#pragma omp for
		for (iter = 0; iter < max_iter; iter++)
		{
			int code = iter;
			int i;
	    	int queen_rows[MAX_N];
			
			for (i = 0; i < n; i++)
			{
				queen_rows[i] = code % n;
				code /= n;
			}
			if (check_for_clash(queen_rows, n))
			{
				#pragma omp atomic
				    num_sol++;
				//print_solution(queen_rows,n);
			}
		}
	}

    // get end time
    end_time = omp_get_wtime();
    // print results
    printf("The execution time is %g sec\n", end_time - start_time);
    printf("Number of found solutions is %d\n", num_sol);
    
	return 0;
}
