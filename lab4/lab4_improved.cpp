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
        #pragma for
        {
            for (int i = 0; i < num_matrix; ++i)
            {
                for (int j = 0; j < num_matrix; ++j)
                {
                    #pragma omp flush(MAX)
                    {
                        if(array0[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array0[i][j]>MAX)
                                    MAX=array0[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array1[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array1[i][j]>MAX)
                                    MAX=array1[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array2[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array2[i][j]>MAX)
                                    MAX=array2[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array3[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array3[i][j]>MAX)
                                MAX=array3[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array4[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array4[i][j]>MAX)
                                    MAX=array4[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array5[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array5[i][j]>MAX)
                                    MAX=array5[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array6[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array6[i][j]>MAX)
                                    MAX=array6[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array7[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array7[i][j]>MAX)
                                    MAX=array7[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array8[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array8[i][j]>MAX)
                                    MAX=array8[i][j];
                        }
                    }
                    #pragma omp flush(MAX)
                    {
                        if(array9[i][j]>MAX)
                        {
                            #pragma omp critical
                                if(array9[i][j]>MAX)
                                    MAX=array9[i][j];
                        }
                    }

                }
            }
        }
    }
    double stop = omp_get_wtime();
    double time_elapsed = stop - start;
    cout<<"\t"<<time_elapsed<<endl;
    return 0;
}