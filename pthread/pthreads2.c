#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define VECLEN 100

pthread_mutex_t mutexham;

void initialize_string(char *str,  int l) ;
double gettime(void) ;
void *hammingDistance(void *t);

//////////////////////////////////////////////////////

typedef struct 
{
	char **A;
	char **B;
	int **hamming_array;
	int sum_hamming;
    int m;
    int n;
    int l;
    int nThreads;

} HDATA;

HDATA hstr;

int main()
{
	
	int m,n,l,i;
	char **A,**B;
  
    //printf("Number of strings for total A : ");
    scanf("%d",&m);
    //printf("\nNumber of strings for total B : ");
    scanf("%d",&n);
    //printf("\nSize of strings : ");
    scanf("%d",&l);

    hstr.m=m;
	hstr.n=n;
	hstr.l=l;
   
    A = malloc(sizeof(char*)*hstr.m);
    B = malloc(sizeof(char*)*hstr.n);

    //Create and initialize A with strings  
    for ( i=0; i<hstr.m;i++ )
    {
	    A[i]= malloc((hstr.l+1)*sizeof(char));
	    initialize_string(A[i],hstr.l);
	}

  	//Create and initialize B with strings
	for ( i=0; i<hstr.n;i++ )
	{
	    B[i]= malloc((hstr.l+1)*sizeof(char));
	    initialize_string(B[i],hstr.l);
	}
	
	
	hstr.A=A;
	hstr.B=B;


	int num;
	//printf("Set number of threads u want to use : ");
	scanf("%d",&num);
	while(num<0 || num>10000)
	{
		printf("Plese give a number of threads within bounds : ");
		scanf("%d",&num);
	}
	
	hstr.nThreads=num;

	//Calculate Hamming Distance
	int **hamming_array=malloc(m*sizeof(int*));
    for(i = 0; i < m; i++)
    {
      hamming_array[i] = malloc(n * sizeof(int));
    }

    hstr.hamming_array=hamming_array;


	/* Create threads to perform the dotproduct  */
	pthread_t threads[hstr.nThreads];
	pthread_attr_t attr;



 	// Initialize mutex & attribute
	pthread_mutex_init(&mutexham, NULL);
	pthread_attr_init(&attr);



    double time0 = gettime();

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(i=0; i<hstr.nThreads; i++)
    {
     
    	//Each thread works on a different set of data. The offset is specified 
   		//by 'i'. The size of the data for each thread is indicated by VECLEN.
    	pthread_create(&threads[i], &attr, hammingDistance, (void *)i);

    }

 	void *status;
    /* Wait on the other threads */
    for(i=0; i<hstr.nThreads; i++)
    {
       	pthread_join(threads[i], &status);
    }

	/*
	----------------CROPPED HERE-----------------------
	*/

    double time1 = gettime();

	printf("---------------------------- \n");
	printf("Sum of Hamming Distance = %d \n",hstr.sum_hamming);
	printf("---------------------------- \n"); 

	double elapsed_time = time1-time0;

	//printf("t0 = %lf and t1 = %lf \n",time0,time1);
	printf("Program time execution = %lf \n",elapsed_time);

	printf("-**************************- \n\n");

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutexham);
    pthread_exit(NULL);
    return 0;

}




void *hammingDistance(void *t)
{

	long my_id = (long)t;

	int len = (hstr.n)/(hstr.nThreads);
	int start = my_id*len;
    int end   = start + len;

	//printf("thread num = %ld \n",my_id);
	//printf("start = %d \n",start);
	//printf("end = %d \n",end);

	//Calculate Hamming Distance
	int hamming_counter=0;  
    int i,j,r;

	for(i=0; i<hstr.m; i++) 
	{	
	    for(j=start; j<end; j++) 
	    {
			for(r=0; r<(hstr.l); r++) 
			{
				  
				if((hstr.A[i][r])!=(hstr.B[j][r]))
				{
					hamming_counter++;
				}
				
		    }

		    pthread_mutex_lock (&mutexham);
			hstr.hamming_array[i][j]=hamming_counter;
			hstr.sum_hamming+=hamming_counter;
			hamming_counter=0;
			pthread_mutex_unlock (&mutexham);

		} 
	}

	pthread_exit((void*) 0);
}



void initialize_string(char *str,  int l) 
{
	
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    for (int j = 0; j < l; ++j) 
    {
        str[j] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    str[l] =0;

}

double gettime(void)
{

	struct timeval ttime;
	gettimeofday(&ttime , NULL);
	return ttime.tv_sec + ttime.tv_usec * 0.000001;

}
   


