#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
int current[5][5], maximum_claim[5][5], available[5], need[5][5],need1[5][5], request[5][5];
int allocation[5] = {0, 0, 0, 0, 0};
int maxres[5],running[5], available[5],avail1[5],safe = 0;
int counter = 0, i, j, exec, resources, processes, k = 1,p,counter2=0;


    
void *process1()
{

	printf("\nThe total instances is: ");
    	for (i = 0; i < resources; i++)
	{
	        printf("\t%d", maxres[i]);
	}

    	printf("\n ------------Allocated---------- :\n");
    	for (i = 0; i < processes; i++)
	{
	        for (j = 0; j < resources; j++)
		{
            		printf("\t%d", current[i][j]);
        	}
		printf("\n");
    	}

    	printf("\n-------------Maximum-----------\n");
    	for (i = 0; i < processes; i++)
	{
        	for (j = 0; j < resources; j++)
		{
		        printf("\t%d", maximum_claim[i][j]);
		
        	}
        	printf("\n");
    	}
    	
    	for (i = 0; i < processes; i++)
	    {
        	for (j = 0; j < resources; j++)
		    {
		    need[i][j]=maximum_claim[i][j]-current[i][j];
		    }
		}
		
	printf("\n----------Need Matrix---------\n");
	
	for (i = 0; i < processes; i++)
	{
        	for (j = 0; j < resources; j++)
		{
		    printf("\t%d",need[i][j]);
		  
		}
		printf("\n");
	}
	
    	for (i = 0; i < processes; i++)
	{
        	for (j = 0; j < resources; j++)
		{
            		allocation[j] += current[i][j];
        	}
    	}

    	printf("\nAllocated resources:");
    	for (i = 0; i < resources; i++)
	{
        	printf("\t%d", allocation[i]);
    	}

    	for (i = 0; i < resources; i++)
	{
	        available[i] = maxres[i] - allocation[i];
	        }
	        
    	for (i = 0; i < resources; i++)
	{
		avail1[i]=maxres[i] - allocation[i];
	}

    	printf("\nAvailable resources:");
    	for (i = 0; i < resources; i++)
	{
        	printf("\t%d", available[i]);
    	}
	
    	printf("\nAvail1 resources:");
    	for (i = 0; i < resources; i++)
	{
        	printf("\t%d", avail1[i]);
    	}
	for (i = 0; i < processes; i++)
	{
        	running[i] = 1;
        	counter++;
    	}


  	while (counter != 0)
	{
	
        	safe = 0;
        	for (i = 0; i < processes; i++)
		{
            		if (running[i])
			{
                		exec = 1;
                		for (j = 0; j < resources; j++)
				{
                    			if (need[i][j] > available[j])
					{
                        			exec = 0;
                        			break;
                    			}
                		}
                		if (exec)
				{
                    			printf("\nProcess[%d] executing \n", i+1 );
                    			running[i] = 0;
                    			counter--;
                    			safe = 1;

                    			for (j = 0; j < resources; j++)
					{
                        			available[j] += current[i][j];
                    			}
					
			                break;
                		}
            		}
				
        	}
		
		
        	if (!safe)
		{
            		printf("\nThe processes are in unsafe state.\n");
            		break;
        	}
		else
		{
            		printf("\nThe process is in safe state");
            		printf("\nAvailable vector:");

            		for (i = 0; i < resources; i++)
			{
                		printf("\t%d", available[i]);
            		}

		        printf("\n");
        	}
    	}
    	
   } 
int main()
{
pthread_t cid,tid[10];
	printf("\nEnter number of processes: ");
    	scanf("%d", &processes);

    	

    	printf("\nEnter number of resources: ");
    	scanf("%d", &resources);

    	printf("\nEnter  total instances::");
    	for (i = 0; i < resources; i++)
	{
	        scanf("%d", &maxres[i]);
    	}

   	printf("\nEnter Allocated Resource :\n");
    	for (i = 0; i < processes; i++)
	{
	        for(j = 0; j < resources; j++)
		{
  			scanf("%d", &current[i][j]);
        	}
    	}

    	printf("\nEnter Maximum Claim :\n");
    	for (i = 0; i < processes; i++)
	{
        	for(j = 0; j < resources; j++)
		{
            		scanf("%d", &maximum_claim[i][j]);
        	}
    	}

    	printf("\n");
	
	pthread_create(&cid,NULL,process1,NULL);
	pthread_join(cid,NULL);

	
	for (i = 0; i < processes; i++)
	{
	printf("enter the request for processes[%d]:",i); 
		for (j = 0; j < resources; j++)
		{
	        scanf("%d", &request[i][j]);
    		}
	}
	printf("request:");
	for (i = 0; i < processes; i++)
	{
		for (j = 0; j < resources; j++)
		{
	        printf("%d  ", request[i][j]);
    		}
		printf("\n");
	}
	for (j = 0; j < resources; j++)
	{
		available[j]=avail1[j];
	}
	for (i = 0; i < processes; i++)
	{
		for (j = 0; j < resources; j++)
		{
		
            	current[i][j] += request[i][j];
        	available[j] =available[j]- request[i][j]; 
        	need[i][j]=need[i][j]-request[i][j];
        	}
	}
	printf("\n----------------//////-------------\n");
    	
	
	printf("\navailable =");
	for (j = 0; j < resources; j++)
	{
		printf("%d  ",available[j]);
	}
	for (j = 0; j < resources; j++)
	{
		allocation[j]=0;
	}	
	printf("\nentering to thread");
	pthread_create(&cid,NULL,process1,NULL);
	pthread_join(cid,NULL);
	
	
	printf("\nthread finished");
return 0;
}
/*
Output:
Enter number of processes: 5

Enter number of resources: 3

Enter  total instances::10 5 7

Enter Allocated Resource :
0 1 0
2 0 0
3  0 2
2 1 1
0 0 2

Enter Maximum Claim :
7 5 3
3 2 2
9 0 2 
2 2 2
4 3 3


The total instances is: 	10	5	7
 ------------Allocated---------- :
	0	1	0
	2	0	0
	3	0	2
	2	1	1
	0	0	2

-------------Maximum-----------
	7	5	3
	3	2	2
	9	0	2
	2	2	2
	4	3	3

----------Need Matrix---------
	7	4	3
	1	2	2
	6	0	0
	0	1	1
	4	3	1

Allocated resources:	7	2	5
Available resources:	3	3	2
Avail1 resources:	3	3	2
Process[2] executing 

The process is in safe state
Available vector:	5	3	2

Process[4] executing 

The process is in safe state
Available vector:	7	4	3

Process[1] executing 

The process is in safe state
Available vector:	7	5	3

Process[3] executing 

The process is in safe state
Available vector:	10	5	5

Process[5] executing 

The process is in safe state
Available vector:	10	5	7
enter the request for processes[0]:0 0 0
enter the request for processes[1]:1 0 2
enter the request for processes[2]:0 0 0
enter the request for processes[3]:0 0 0
enter the request for processes[4]:0 0 0
request:0  0  0  
1  0  2  
0  0  0  
0  0  0  
0  0  0  

----------------//////-------------

available =2  3  0  
entering to thread
The total instances is: 	10	5	7
 ------------Allocated---------- :
	0	1	0
	3	0	2
	3	0	2
	2	1	1
	0	0	2

-------------Maximum-----------
	7	5	3
	3	2	2
	9	0	2
	2	2	2
	4	3	3

----------Need Matrix---------
	7	4	3
	0	2	0
	6	0	0
	0	1	1
	4	3	1

Allocated resources:	8	2	7
Available resources:	2	3	0
Avail1 resources:	2	3	0
Process[2] executing 

The process is in safe state
Available vector:	5	3	2

Process[4] executing 

The process is in safe state
Available vector:	7	4	3

Process[1] executing 

The process is in safe state
Available vector:	7	5	3

Process[3] executing 

The process is in safe state
Available vector:	10	5	5

Process[5] executing 

The process is in safe state
Available vector:	10	5	7

thread finished*/ 


