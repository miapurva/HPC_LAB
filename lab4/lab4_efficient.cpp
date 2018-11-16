#include<iostream>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

int MAX=0;

int main()
{
	srand(time(NULL));
	int num_matrix=10;
	/*int no_threads[]={1,2,4,6,8,10,12,16,20,24,28,32};
    int th;*/
	//int private_max_array[num_matrix];
	int n= 100;
	int array0[n][n],array1[n][n], array2[n][n], array3[n][n], array4[n][n], array5[n][n], array6[n][n], array7[n][n], array8[n][n], array9[n][n];

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
    	{
    		array0[i][j]=rand()%100;
    		array1[i][j]=rand()%100;
    		array2[i][j]=rand()%100;
    		array3[i][j]=rand()%100;
    		array4[i][j]=rand()%100;
    		array5[i][j]=rand()%100;
    		array6[i][j]=rand()%100;
    		array7[i][j]=rand()%100;
    		array8[i][j]=rand()%100;
    		array9[i][j]=rand()%100;
    	}
	}   

    double start = omp_get_wtime();
    #pragma omp parallel shared(MAX)
    {
    	int private_max = MAX;
    	#pragma for
    	{
    		for (int i = 0; i < num_matrix; ++i)
    		{
    			for (int j = 0; j < num_matrix; ++j)
	    		{
	    			if(array0[i][j]>private_max)
	    				private_max=array0[i][j];
                    if(array1[i][j]>private_max)
                        private_max=array1[i][j];
                    if(array2[i][j]>private_max)
                        private_max=array2[i][j];
                    if(array3[i][j]>private_max)
                        private_max=array3[i][j];
                    if(array4[i][j]>private_max)
                        private_max=array4[i][j];
                    if(array5[i][j]>private_max)
                        private_max=array5[i][j];
                    if(array6[i][j]>private_max)
                        private_max=array6[i][j];
                    if(array7[i][j]>private_max)
                        private_max=array7[i][j];
                    if(array8[i][j]>private_max)
                        private_max=array8[i][j];
                    if(array9[i][j]>private_max)
                        private_max=array9[i][j];
	    		}
    		}
    	}
    	#pragma omp flush(MAX)
    	{
            if(private_max>MAX)
        	{
                #pragma omp critical
        		if(private_max>MAX)
        			MAX=private_max;
            }
    	}	 
    }
    double stop = omp_get_wtime();
    double time_elapsed = stop - start;
    cout<<"\t"<<time_elapsed<<endl;
    return 0;
}