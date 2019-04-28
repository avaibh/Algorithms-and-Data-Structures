/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 11
    PC Number: 58
    Date: 04-10-2018
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int subpartID;
    int cost_per_day;
    int duration;
} subpart_data;

typedef struct{
    int predecessorID;
    int successorID;
}dependency_info;

void mergeSort(subpart_data *A, int l, int r); 
void merge(subpart_data *A, int l, int m, int r); 
void print_schedule(subpart_data *A, int k);
void print_schedule1(subpart_data *A, int k, dependency_info *B, int l);

void print_schedule(subpart_data *A, int k)
{
    if(k<2)
    {
        printf("Cost = %d\n",A[0].cost_per_day*A[0].duration);
        return;
    }
    mergeSort(A, 0, k-1);
    int i, cost=0;
    /*
    for(i=k-1; i>=0; i--)
    {
       printf("%d ",A[i].subpartID);
       printf("%d ",A[i].cost_per_day);
       printf("%d\n",A[i].duration);       
    }
    */
    int temp_duration = 0;
    printf("Subparts work order:= ");
    for(i=k-1; i>=0; i--)
    {
        if(i!=0) printf("%d -> ",A[i].subpartID);
        if(i==0) printf("%d;   ", A[i].subpartID);
        temp_duration= temp_duration + A[i].duration;
        cost = cost + temp_duration*A[i].cost_per_day;      
    }
    printf("Cost = %d\n",cost);
    return;
}
int isSuccessor(dependency_info *B, int l, int test)
{
    int i;
    for(i=0; i<l; i++)
    {
        if(B[i].successorID == test) return 1;
    }
    return 0;
}
void print_schedule1(subpart_data *A, int k, dependency_info *B, int l)
{
    if(k<2)
    {
        printf("Cost = %d\n",A[0].cost_per_day*A[0].duration);
        return;
    }
    mergeSort(A, 0, k-1);
    int i,j,cost=0,temp_duration=0;
    int a;
    subpart_data temp;
    printf("Subparts work order:= ");
    for(i=k-1; i>=0; i--)
    {
        if(isSuccessor(B,l,A[i].subpartID)==0)
        {
            if(i!=0) printf("%d -> ",A[i].subpartID);
            if(i==0) printf("%d;   ", A[i].subpartID);
            temp_duration= temp_duration + A[i].duration;
            cost = cost + temp_duration*A[i].cost_per_day;      
        }else
        {  
            for(j=0; j<l; j++)
            {
                if(B[j].successorID ==  A[i].subpartID)
                {
                    for(a=0;a<k;a++)
                    {
                        if(A[a].subpartID == B[j].predecessorID)
                        {
                            temp = A[a];
                            A[a] = A[i];
                            A[i] = temp;
                        }
                    } 
                }
            }
        }
        if(i!=0) printf("%d -> ",A[i].subpartID);
        if(i==0) printf("%d;   ", A[i].subpartID);
        temp_duration= temp_duration + A[i].duration;
        cost = cost + temp_duration*A[i].cost_per_day;    
    }
    /*
    int arr[k], max=0, maxInd=0;
    arr[0] = 0;
    char s[] ="$";
    for(i=0;i<l;i++)
    {
        for(j=1;j<k;j++)
        {
            if(B[i].predecessorID == j) arr[j]++;
            if(B[i].successorID == j) arr[j]++;
        }
    }
    for(j=1;j<k;j++)
    {
        if(arr[j] > max) {
            max=arr[j];
            maxInd = j;
        }
    }
    for(j=0;j<l;j++)
    {
        if(B[j].successorID == maxInd)
        {
            s = s +(char)B[j].predecessorID + "$";
        } 
    }
    s = s +(char)maxInd + "$";
    for(j=0;j<l;j++)
    {
        if(B[j].predecessorID == maxInd)
        {
            s = s +(char)B[j].successorID + "$";
        } 
    }
    printf("%s",s);
    */
    printf("Cost = %d\n",cost);
    return;
}


int main()
{
    int k,i,l;
    scanf("%d",&k);
    subpart_data *A = (subpart_data*)malloc(sizeof(subpart_data)*k);
    for(i=0; i<k; i++)
    {
        A[i].subpartID = i+1;
        scanf("%d", &A[i].duration);
    }
    for(i=0; i<k; i++)
    {
        scanf("%d", &A[i].cost_per_day);
    }
    print_schedule(A,k);
    scanf("%d",&l);
    dependency_info *B = (dependency_info*)malloc(sizeof(dependency_info)*l);
    for(i=0; i<l; i++)
    {
        scanf("%d %d", &B[i].predecessorID, &B[i].successorID);
    }
    print_schedule1(A,k,B,l);
    free(A);
    free(B);     
    return 0;
}

void merge(subpart_data *A, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    subpart_data *L, *R;
    L = (subpart_data*)malloc(sizeof(subpart_data)*n1);
    R = (subpart_data*)malloc(sizeof(subpart_data)*n2); 
    for (i = 0; i < n1; i++)
    { 
        L[i].cost_per_day = A[l + i].cost_per_day;
        L[i].subpartID = A[l + i].subpartID; 
        L[i].duration = A[l + i].duration;

    }  
    for (j = 0; j < n2; j++)
    { 
        R[j].cost_per_day = A[m + 1+ j].cost_per_day;
        R[j].subpartID = A[m + 1+ j].subpartID; 
        R[j].duration = A[m + 1+ j].duration;
    } 
    i = 0; 
    j = 0;
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i].cost_per_day/L[i].duration <= R[j].cost_per_day/R[j].duration) 
        { 
            A[k].cost_per_day = L[i].cost_per_day;
            A[k].subpartID = L[i].subpartID;
            A[k].duration = L[i].duration; 
            i++; 
        } 
        else
        { 
            A[k].cost_per_day = R[j].cost_per_day;
            A[k].subpartID = R[j].subpartID;
            A[k].duration = R[j].duration; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        A[k].cost_per_day = L[i].cost_per_day;
        A[k].subpartID = L[i].subpartID;
        A[k].duration = L[i].duration; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        A[k].cost_per_day = R[j].cost_per_day;
        A[k].subpartID = R[j].subpartID;
        A[k].duration = R[j].duration; 
        j++; 
        k++; 
    }
    free(L);
    free(R); 
} 

void mergeSort(subpart_data *A, int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(A, l, m); 
        mergeSort(A, m+1, r); 
        merge(A, l, m, r); 
    } 
} 
