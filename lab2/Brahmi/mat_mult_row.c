    #include <stdio.h>   
    #include<time.h>
    #include<omp.h>  
    #include<stdlib.h>

    int main()
    {
      int m, n, p, q, c, d, k, sum = 0,th;
      int first[100][100], second[100][100], multiply[100][100];
	int no_threads[]={1,2,4,6,8,10,12,14,18,22,26,30,34,38,42,46,50,54,58,62};   
      float start,end, time;
      m=100;
      n=100;
      p=100;
      q=100;
      printf("Enter the elements of first matrix\n");    
      for (  c = 0 ; c < n ; c++ )
        for ( d = 0 ; d < n ; d++ )
        {
	  first[c][d]=1;
	  second[c][d]=2;    
	}     
	
	 
	for( th=0; th<20;th++)
{
 	start = omp_get_wtime();   
	#pragma omp parallel for num_threads(no_threads[th])   
	for ( c = 0 ; c < n ; c++ )
        {
	  #pragma omp parallel for num_threads(no_threads[th])
          for ( d = 0 ; d < n ; d++ )
          {
            for ( k = 0 ; k < n ; k++ )
            {
              sum = sum + first[c][k]*second[k][d];
            }  
            multiply[c][d] = sum;
            sum = 0;
          }
        }
   
	end = omp_get_wtime();
	time = end-start;
	printf("%d %f\n",no_threads[th],time);       
}
	/*printf("Product of entered matrices:-\n");     
        for ( c = 0 ; c < n ; c++ )
        {
          for ( d = 0 ; d < n ; d++ )
         {   printf("%d\t", multiply[c][d]);
             printf("\n");
         } 
	}
      */
      return 0;
    }
