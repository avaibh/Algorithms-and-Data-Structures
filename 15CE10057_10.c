/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 10
    PC Number: 58
    Date: 27-09-2018
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct _rwd {
    int start_time;
    int service_time;
}reqWD;

typedef struct _rsd {
    int service_time;
    int target_time;
}reqSD;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(reqWD *req, int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
   
       for (j = 0; j < n-i-1; j++) 
           if (req[j].start_time > req[j+1].start_time)
           {
              swap(&req[j].start_time, &req[j+1].start_time);
              swap(&req[j].service_time, &req[j+1].service_time);
          }
}

void bubbleSort2(reqSD *req, int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
   
       for (j = 0; j < n-i-1; j++) 
           if ((req[j].service_time)*(req[j].target_time-req[j].service_time) > (req[j+1].service_time)*(req[j+1].target_time-req[j+1].service_time))
           {
              swap(&req[j].target_time, &req[j+1].target_time);
              swap(&req[j].service_time, &req[j+1].service_time);
          }
}

int findIndex(int arr[], int r, int n)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        if(arr[i] == r)
        {
            return i;
        }
    }
}
int schedule1(reqWD *req, int n)
{
    if(n<2)
    {
        printf("\nCounter 0");
        printf("\n0 %d %d", req[0].start_time, req[0].start_time+req[0].service_time);
        return 1;
    }
    int i,j,counter[n],numberofC;
    int arr[n];
    for(i=0; i<n; i++)
    {
        arr[i] = req[i].start_time;
    }
    bubbleSort(req, n);
    
    for(i=0;i<n;i++)
    {
        counter[i] = 0;
    }
    i = 0;
    numberofC = 0;
    printf("\nCounter %d\n%d %d %d", counter[i],findIndex(arr,req[i].start_time,n),req[i].start_time, req[i].start_time+req[i].service_time);
    counter[i] = req[i].start_time+req[i].service_time;
    for(i=1;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //printf("\n--------------------%d %d %d\n", j, counter[j], req[i].start_time);
            if(counter[j]<=req[i].start_time)
            {
                printf("\nCounter %d\n%d %d %d", j,findIndex(arr,req[i].start_time,n),req[i].start_time, req[i].start_time+req[i].service_time);
                counter[j] = req[i].start_time+req[i].service_time;
                break;
            }
        }     
    }
    for(i=0;i<n;i++)
    {
        if(counter[i] != 0)
        {
            numberofC++;
        }
    }
    return numberofC;
}
/*
** Saturday scheduling criteria
** Following two conditions are preferred
** The activities which will take least amount of time to finish(Length, L), must be scheduled first 
** The activities with least (Deadline-Length) i.e. D - L
** Criteria = "1/[(L)(D-L)]"
** L = req[i].service_time
** D = req[i].target_time
** Criteria = "1/[(req[i].service_time)*(req[i].target_time-req[i].service_time)]"
** Implemented the above criteria in the bubleSort2() function
*/

void schedule2(reqSD *req, int n)
{
    if(n<2)
    {
        printf("\n0 0 %d", req[0].service_time);
        return;
    }
    int i,j,counter[n],numberofC, start_time, finish_time;
    int arr[n];
    for(i=0; i<n; i++)
    {
        arr[i] = req[i].service_time+req[i].target_time;
    }
    bubbleSort2(req, n);
    start_time = 0;
    for(i=0;i<n;i++)
    {
        printf("\n%d %d %d", findIndex(arr,req[i].service_time+req[i].target_time,n),start_time, start_time+req[i].service_time);
        start_time = start_time+req[i].service_time;
    }
    printf("\n");
    return ;
}

int main()
{
    int n,i,numberofC, m;
    
    printf("\nEnter the number of requests over weekday: ");
    scanf("%d", &n);
    printf("\nEnter the start time and length for each of the requests ");
    
    reqWD *rwd;
    rwd = (reqWD*)malloc(sizeof(struct _rwd)*n);
    
    for(i=0; i<n; i++)
    {
        printf("\nrequest %d:: ", i);
        scanf("%d %d", &rwd[i].start_time, &rwd[i].service_time);
    }
    printf("\nPrint the schedule as per various counters in the following format:\ncounter Id\nrequest Id, start time, finish time\n");
    numberofC = schedule1(rwd,n);
    printf("\nNumber of counter = %d",numberofC);
    
    printf("\n\nEnter the number of requests over Saturday: ");
    scanf("%d", &m);
    printf("\nEnter the length and deadline for each of the requests ");
    
    reqSD *rsd;
    rsd = (reqSD*)malloc(sizeof(struct _rsd)*m);
    
    for(i=0; i<m; i++)
    {
        printf("\nrequest %d:: ", i);
        scanf("%d %d", &rsd[i].service_time, &rsd[i].target_time);
    }
    printf("\nPrint the schedule in the following format:\nrequest Id, start time, finish time\n");
    schedule2(rsd,m);
    
    return 0;
}
