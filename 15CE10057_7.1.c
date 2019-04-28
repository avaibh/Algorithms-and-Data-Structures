/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 7(Part 1 and Part 2)
    PC Number: 58
    Date: 30-08-2018
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100 
typedef struct _job { 
    int jobId; 
    int startTime; 
    int jobLength;
    int remLength; 
} job;

typedef struct _heap { 
    job list[MAX_SIZE]; 
    int numJobs; 
} heap;

void initHeap(heap *H);
void insertJob(heap *H, job j);
int extractMinJob(heap *H, job *j);
void printheap(heap *H);
void swap(heap *H, int p, int i);
int minIndex(heap *H, int l, int r);
void scheduler(job jobList[], int n);

void initHeap(heap *H)
{
    if(H==NULL)
    {
        return;
    }
    H->numJobs = 0;
}

void swap(heap *H, int p, int i)
{
    job temp;
    temp = H->list[i];
    H->list[i] = H->list[p];
    H->list[p] = temp;
}

void merge(job joblist[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = joblist[l + i].jobId; 
    for (j = 0; j < n2; j++) 
        R[j] = joblist[m + 1+ j].jobId; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            joblist[k].jobId = L[i]; 
            i++; 
        } 
        else
        { 
            joblist[k].jobId = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        joblist[k].jobId = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        joblist[k].jobId = R[j]; 
        j++; 
        k++; 
    } 
} 

void sort(job joblist[], int l, int r)
{
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        sort(joblist, l, m); 
        sort(joblist, m+1, r); 
  
        merge(joblist, l, m, r); 
    } 
}
void printheap(heap *H)
{
    if(H==NULL)
    {
        return;
    }
    int i;
    for(i = 0; i<H->numJobs; i++)
    {
        printf("%d ", H->list[i].jobId);
    }
    printf("\n");
}

int minIndex(heap *H, int l, int r)
{
    int n;
    if(H->list[l].remLength < H->list[r].remLength)
    {
        n = l;
    }else if(H->list[l].remLength > H->list[r].remLength)
    {
        n = r;
    }else if(H->list[l].remLength == H->list[r].remLength && H->list[l].jobId < H->list[r].jobId)
    {
        n = l;
    }else if(H->list[l].remLength == H->list[r].remLength && H->list[l].jobId > H->list[r].jobId)
    {
        n = r;
    }
    return n;
}

void insertJob(heap *H, job j)
{
    int i, p;
    if(H==NULL)
    {
        return;
    }
    i= H->numJobs+1;
    H->list[i] = j;
    while(1)
    {
        if(i==1) {return;}
        p = i/2;
        if(H->list[p].remLength < H->list[i].remLength) {return;}
        else
        {
            swap(H, p, i);
            i = p;
        }
    }
    
}

int extractMinJob(heap *H, job *j)
{
    if(H==NULL)
    {
        return -1;
    }
    int i=1, l, r, minInd;
    H->list[i] = H->list[H->numJobs];
    H->numJobs--;
    while(1)
    {
        l = 2*i;
        r = 2*i + 1;
        if(l>H->numJobs) {break;}
        minInd = minIndex(H, l, r);
        if(H->list[i].remLength > H->list[minInd].remLength){break;}
        else if(H->list[i].remLength == H->list[minInd].remLength && H->list[i].jobId < H->list[minInd].jobId){break;}
        i = minInd;
    }
    j = H->list[minInd];
    return 0;
}

void scheduler(job jobList[], int n)
{
    int timeStep = 0;
    int lastJob = 0;
    heap H;
    initHeap(&H);
    sort(jobList, 0, n-1);
    job crrJob;
    while(1)
    {      
        while(timeStep == jobList[lastJob].startTime && lastJob < n) 
        {
            insertJob(&H, jobList[lastJob]);
            lastJob++;
        }
        if(crrJob.remLength == 0)
        {
            extractMinJob(&H, &crrJob);
        }
        crrJob.remLength--;
        timeStep++;
        printf("%d ", crrJob.jobId);
        
        if(H.numJobs == 0){break;}
    }
}

int main()
{
    int n,i;
    job J;
    heap *H;
    initHeap(H);
    scanf("%d", &n);
    if(n<=MAX_SIZE)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d %d %d", &j.jobId, &j.startTime, &j.jobLength);
            j.remLength = j.jobLength;
        }
        printf("\nJobs scheduled at each timestep are:");
        scheduler(j,n);
    }
    else
    {
        printf("Number of Jobs is more than the maximum number of jobs!!");    
    }
    return 0;
}
