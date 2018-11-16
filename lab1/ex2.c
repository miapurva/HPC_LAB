#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <omp.h>

int main(void)
{
	long double a[100000],b[100000];
	srand(time(NULL));
	int n=100000;
	double start=omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < n; ++i)
		{
			a[i] =(i+1)*1.0; 
			//b[i] = (i+1)*2.0;
		}
		
	}
	double end=omp_get_wtime();

	double time_elapsed=end-start;
	printf("Time elapsed=%lf\n", time_elapsed );
	return(0);
}
