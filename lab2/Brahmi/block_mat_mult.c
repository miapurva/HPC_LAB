    #include <stdio.h>   
    #include<time.h>
    #include<omp.h>  
    #include<stdlib.h>

    int main()
    {
      int m, n, p, q, d, k, sum = 0,th;
      int a[100][100], b[100][100], c[100][100];
      int temp, no_threads[]={1,2,4,6,8,10,12,14,18,22,26,30,34,38,42,46,50,54,58,62};   
      float start,end, time;
      int s=4;
      int N=100;
      p=100;
      q=100;
      printf("Enter the elements of first matrix\n");    
      for ( int e = 0 ; e < N ; e++ )
        for ( d = 0 ; d < N ; d++ )
        {
	  a[e][d]=1;
	  b[e][d]=2;    
	}     
	for( th=0; th<20;th++)
{
 	start = omp_get_wtime();   
	#pragma omp parallel for num_threads(no_threads[th])   
	for(int jj=0;jj<N;jj+= s)
	{
		#pragma omp parallel for num_threads(no_threads[th]) 
        for(int kk=0;kk<N;kk+= s)
	{
		#pragma omp parallel for num_threads(no_threads[th]) 
                for(int i=0;i<N;i++)
		{
			#pragma omp parallel for num_threads(no_threads[th]) 
                        for(int j = jj; j<((jj+s)>N?N:(jj+s)); j++)
			{
                                temp = 0;
                                for(int k = kk; k<((kk+s)>N?N:(kk+s)); k++)
				{
                                        temp += a[i][k]*b[k][j];
                                }
                                c[i][j] += temp;
                        }
                }
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




