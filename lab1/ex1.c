#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <omp.h>

int main(void)
{
	long double a[200][200],b[200][200],c[200][200];
	int n=200;
	srand(time(NULL));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			a[i][j]=1;
			b[i][j]=2;
		}
	}
	
	double start=omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				c[i][j]=a[i][j]+b[i][j];
			}
		}
	}
	double end=omp_get_wtime();

	double time_elapsed=end-start;
	//long double time1= (long double)time_elapsed/(CLOCKS_PER_SEC*100);
	printf("Time elapsed=%lf\n", time_elapsed );
	return(0);
}
