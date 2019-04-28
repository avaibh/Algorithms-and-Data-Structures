/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 7(Part 1 and Part 2)
    PC Number: 58
    Date: 2-09-2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_SIZE 100 

typedef struct _jobPair {
	int jobid_from;
	int jobid_to;
} jobpair;

typedef struct _job { 
    int jobId; 
    int startTime; 
    int jobLength;
    int remLength; 
} job;

typedef struct _new_heap { 
    job list[MAX_SIZE]; 
    jobpair pairs[MAX_SIZE];
    int numJobs; 
} newheap;


void initHeap(newheap *H);
void insertJob(newheap *H, job j);
int extractMinJob(newheap *H, job *j);
void printheap(newheap *H);
void swap(newheap *H, int p, int i);
int minIndex(newheap *H, int l, int r);
void decreaseKey(newheap *H, int jid); 
void newScheduler(job jobList[], int n, jobpair pairList[], int m);
void assign_pair(newheap *H, jobpair pairList[], int k);

void initHeap(newheap *H)
{
    if(H==NULL)
    {
        return;
    }
    H->numJobs = 0;
}

void swap(newheap *H, int p, int i)
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
void printheap(newheap *H)
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

int minIndex(newheap *H, int l, int r)
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

void insertJob(newheap *H, job j)
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

int extractMinJob(newheap *H, job *j)
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
    j = H->list;
    return 0;
}

void decreaseKey(newheap *H, int jid)
{
	//decreases the value of the remLength field of the job with job id jid in heap H by 50%
	jobpair pair;
	int i,n,j;
	n = (int)sizeof(H->pairs)/sizeof(jobpair);
	for (i = 0; i < n; i++)
	{
		if (jid == H->pairs[i].jobid_to)
		{
			for (j = 0; j < MAX_SIZE; j++)
			{
				if (H->list[j].jobId == jid && H->list[j].jobLength == H->list[j].remLength)
				{
					H->list[j].remLength = (int) H->list[j].remLength * 0.5;
				}else{
					return;
				}
			}
		}
	}
	int p;
    i= H->numJobs+1;
    while(1)
    {
        if(i==1) {break;}
        p = i/2;
        if(H->list[p].remLength < H->list[i].remLength) {break;}
        else
        {
            swap(H, p, i);
            i = p;
        }
    }
}

void assign_pair(newheap *H, jobpair pairList[], int k)
{
	for (int i = 0; i < k; ++i)
	{
		H->pairs[i].jobid_from = pairList[i].jobid_from;
		H->pairs[i].jobid_to = pairList[i].jobid_to;
	}
}

void newScheduler(job jobList[], int n, jobpair pairList[], int m)
{
    int timeStep = 0;
    int lastJob = 0;
    newheap H;
    initHeap(&H);
    sort(jobList, 0, n-1);
    job crrJob;
    crrJob.remLength = 0;
    int k,i;
    k = (int)sizeof(H.pairs)/sizeof(jobpair);
    assign_pair(&H,pairList,k);
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
        if(crrJob.remLength == 0)
        {
        	for (i = 0; i < k; i++)
        	{
	            if (pairList[i].jobid_from == crrJob.jobId)
	            {
	            	decreaseKey(&H, pairList[i].jobid_to);
	            }
            }
        }
        crrJob.remLength--;
        timeStep++;
        printf("%d ", crrJob.jobId);
        if(H.numJobs == 0){break;}
    }
}

int main()
{
    int n,i,m;
    job j[MAX_SIZE];
    newheap *H;
    initHeap(H);
    scanf("%d", &n);
    jobpair p[n];
    if(n<=MAX_SIZE)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d %d %d", &j[i].jobId, &j[i].startTime, &j[i].jobLength);
            j[i].remLength = j[i].jobLength;
        }
        scanf("%d", &m);
        for(i=0;i<m;i++)
        {
            scanf("%d %d", &p[i].jobid_from, &p[i].jobid_to);
        }
        printf("\nJobs scheduled at each timestep are:");
        newScheduler(j,n,p,m);
    }
    else
    {
        printf("Number of Jobs is more than the maximum number of jobs!!");    
    }
    return 0;
}
