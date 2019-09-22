
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void initialize_string(char *str,  int l) ;
double gettime(void);



int main()
{


	
	
	int m=0,n=0,r=0,j=0,l=0,i=0,v=0,b=0,hamming_counter=0;
	char**A,**B;
	// hamming_array;
  
   // printf("Number of strings for total A : ");
    scanf("%d",&m);
    //printf("\nNumber of strings for total B : ");
    scanf("%d",&n);
   //printf("\nSize of strings : ");
    scanf("%d",&l);

   
   
    A = (char**)malloc(sizeof(char*)*m);

    B =(char**) malloc(sizeof(char*)*n);


    //Create and initialize A [ #strings]   
    for ( v=0; v<m;v++ )
    {
	    if( (A[v]=(char*) malloc((l+1)*sizeof(char))) ==NULL)
	     printf("\nError Allocatting A[element]");
			
	    initialize_string(A[v],l);
	    // printf(" \n string %d of A : %s ",i,A[v]);
	}

	//Create and initialize B [ #strings]   	
	for ( b=0; b<n;b++ )
	{
	 if((  B[b]= (char*)malloc((l+1)*sizeof(char)))==NULL)
printf("\nError Allocatting B[element]");
	    initialize_string(B[b],l);
	   // printf(" \n string %d of B : %s ",i,B[b]);
	}
	
    //Calculate Hamming Distance
 long long int sum_hamming=0;
   
	char *temp1=NULL,*temp2=NULL;
    int **hamming_array =(int**) malloc((m * sizeof (int*)));

	for (int q=0; q<m; q++)
         hamming_array[q] = (int *)malloc(n * sizeof(int));

double time0 = gettime();
   //clock_t start=clock();

    

	 for(i=0; i<m; i++) {
		
     			 for(j=0;j<n;j++) {
	
					for(r=0; r<l; r++) {
							
								
							  temp1=A[i];
         						  temp2=B[j];
			 				
					      		  if(temp1[r]!=temp2[r]) 
								hamming_counter++;
					                 		 if(r==l-1) 
										{
										hamming_array[i][j]=hamming_counter;
										sum_hamming=sum_hamming+hamming_array[i][j];
										hamming_counter=0;
										}	
						
								
					  
							   }

     					 }
  
			}


   
 
//clock_t end =clock();
double time1 = gettime();
    //double hamm_time=(double)(end-start)/CLOCKS_PER_SEC;
    double elapsed_time = time1-time0;

	printf("---------------------------- \n");
	printf("-**************************- \n");
	printf("Sum of Hamming Distance = %lli \n",sum_hamming);
	printf("---------------------------- \n"); 

	printf("Program time execution = %lf \n",elapsed_time);

	

	//printf("t0 = %lf and t1 = %lf \n",time0,time1);
	//printf("Program time execution = %lf \n",hamm_time);

    return 0;

    

}





void initialize_string(char *str,  int l) 
{
	
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    for (int j = 0; j < l; ++j) 
    {
        str[j] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    //str[l+1] ='0';

}


double gettime(void)
{

	struct timeval ttime;
	gettimeofday(&ttime , NULL);
	return ttime.tv_sec + ttime.tv_usec * 0.000001;

}