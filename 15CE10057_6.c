/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 6
    PC Number: 58
    Date: 23-08-2018
*/

#include<stdio.h>
#include<stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

void combine(int A[], int left, int middle, int right);
void superbSorting(int A[], int sizeOfA);
void printArray(int A[], int size);
int compare1(int X[], int sizeOfX, int x, int y);
void combine1(int A[], int left, int middle, int right, int B[], int sizeOfB);
void superbSorting1(int A[], int sizeOfA, int B[], int sizeOfB);

void combine(int A[], int left, int middle, int right)
{
    int i = 0, j = 0, k = 0;
    int *arr1, *arr2;
    int leftSize, rightSize;
    leftSize = middle-left+1;
    rightSize = right-middle;
    arr1 = (int *)malloc(leftSize * sizeof(int));
    arr2 = (int *)malloc(rightSize * sizeof(int));
    
    for(i=left; i<middle+1; i++)
    {
        arr1[j] = A[i];
        j++;
    }
    j=0;
    for(i=middle+1; i<=right; i++)
    {
        arr2[j] = A[i];
        j++;
    }
    i = 0;
    j = 0; 
    k = 0;
    
    // Traverse both array
    while (i<leftSize && j <rightSize)
    {
        if (arr1[i] < arr2[j])
            A[k++] = arr1[i++];
        else
            A[k++] = arr2[j++];
    }
 
    // Store remaining elements of first array
    while (i < leftSize)
        A[k++] = arr1[i++];
 
    // Store remaining elements of second array
    while (j < rightSize)
        A[k++] = arr2[j++];
    
    free(arr1);
    free(arr2);
}

void superbSorting(int A[], int sizeOfA)
{
   int curr_size;  
   int left_start; 

   for (curr_size=1; curr_size<=sizeOfA-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<sizeOfA-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = left_start + curr_size - 1;
 
           int right_end = min(left_start + 2*curr_size - 1, sizeOfA-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           combine(A, left_start, mid, right_end);
       }
   }
}

int compare1(int X[], int sizeOfX, int x, int y)
{
    int i, j;
    
    for(i=0;i<sizeOfX-1; i++)
    {
        for(j=i;j<sizeOfX; j++)
        {
            if(X[i] == x && X[j] == y)
            {
                return 1;
            }
            else if(X[i] == y && X[j] == x)
            {
                return -1;
            }
        }
    }
    return 0;
}
void combine1(int A[], int left, int middle, int right, int B[], int sizeOfB)
{
    int i = 0, j = 0, k = 0;
    int *arr1, *arr2;
    int leftSize, rightSize;
    leftSize = middle-left+1;
    rightSize = right-middle+1;
    arr1 = (int *)malloc(leftSize * sizeof(int));
    arr2 = (int *)malloc(rightSize * sizeof(int));
    
    for(i=left; i<middle+1; i++)
    {
        arr1[j] = A[i];
        j++;
    }
    j=0;
    for(i=middle+1; i<=right; i++)
    {
        arr2[j] = A[i];
        j++;
    }
    i = 0;
    j = 0; 
    k = 0;
    
    // Traverse both array
    while (i<leftSize && j <rightSize)
    {
        if (compare1(B, sizeOfB, arr1[i], arr2[j]) == 1)
            A[k++] = arr1[i++];
        else if(compare1(B, sizeOfB, arr1[i], arr2[j]) == -1)
            A[k++] = arr2[j++];
    }
 
    // Store remaining elements of first array
    while (i < leftSize)
        A[k++] = arr1[i++];
 
    // Store remaining elements of second array
    while (j < rightSize)
        A[k++] = arr2[j++];
    
    free(arr1);
    free(arr2);
}
void superbSorting1(int A[], int sizeOfA, int B[], int sizeOfB)
{
    int curr_size;  
   int left_start; 

   for (curr_size=1; curr_size<=sizeOfA-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<sizeOfA-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = left_start + curr_size - 1;
 
           int right_end = min(left_start + 2*curr_size - 1, sizeOfA-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           combine1(A, left_start, mid, right_end, B, sizeOfB);
       }
   }
}

/*  PART III 
**  A Binary Search based function, to return the index at which
**  x is FIRST encountered in arr[].  
**  If x is not present, then it returns -1 
**  Brief Algo description
**  Binary search for all occurrences of B[i] in temp[], 
**  if present then copy all occurrences to A[j] 
**  and increment j. Also mark the copied elements visited[]
*/
int first(int arr[], int low, int high, int x, int n)
{
    if (high >= low)
    {
        int mid = low + (high-low)/2;
        if ((mid == 0 || x > arr[mid-1]) && arr[mid] == x)
            return mid;
        if (x > arr[mid])
            return first(arr, (mid + 1), high, x, n);
        return first(arr, low, (mid -1), x, n);
    }
    return -1;
}
// comparetor for qsort function in stdlib.h
int comparetor (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

// Faster Algorithm to Sort A[0..m-1] according to the order defined by B[0..n-1].
void fasterAlgo(int A[], int B[], int m, int n)
{
    // The temp array is used to store a copy of A[] and 
    // visited[] is used to mark the visited elements in temp[].
    int temp[m], visited[m];
    for(int i=0; i<m; i++)
    {
        temp[i] = A[i];
        visited[i] = 0;
    }
 
    // Sort elements in temp
    qsort (temp, m, sizeof(int), comparetor );
    int ind = 0;  // for index of output which is sorted A[]
 
    // Consider all elements of B[], find them in temp[]
    // and copy to A[] in order.
    for (int i=0; i<n; i++)
    {
        // Find index of the first occurrence of B[i] in temp
        int f = first(temp, 0, m-1, B[i], m);
 
        // If not present, no need to proceed
        if (f == -1) continue;
 
        // Copy all occurrences of B[i] to A[]
        for (int j = f; (j<m && temp[j]==B[i]); j++)
        {
            A[ind++] = temp[j];
            visited[j] = 1;
        }
    }
 
    // Now copy all items of temp[] which are not present in B[]
    for (int i=0; i<m; i++)
        if (visited[i] == 0)
            A[ind++] = temp[i];
}
void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
}
int main()
{   
    int i, n, nB;
    int *A, *B;
    // Part I
    printf("\nEnter number of numbers in the array A:");
    scanf("%d",&n);
    A = (int *)malloc(n * sizeof(int));
    printf("\nEnter numbers in the array A:");
    for(i=0; i<n; i++)
    {
        scanf("%d", &A[i]);
    }
    superbSorting(A,n);
    printf("\nArray A sorted in non-decreasing order:");
    printArray(A, n);
    free(A);
    // Part II
    printf("\nEnter number of numbers in the array A:");
    scanf("%d",&n);
    A = (int *)malloc(n * sizeof(int));
    printf("\nEnter numbers in the array A: ");
    for(i=0; i<n; i++)
    {
        scanf("%d", &A[i]);
    }
    printf("\nEnter number of numbers in the array B:");
    scanf("%d",&nB);
    B = (int *)malloc(nB * sizeof(int));
    printf("\nEnter numbers in the array B: ");
    for(i=0; i<nB; i++)
    {
        scanf("%d", &B[i]);
    }
    superbSorting1(A, n, B, nB);
    printf("\nArray A after re-arranging: ");
    printArray(A,n);
    free(A);
    free(B);
    
    // Faster Algorithm i.e. Part III
    A = (int *)malloc(n * sizeof(int));
    printf("\nEnter numbers in the array A: ");
    for(i=0; i<n; i++)
    {
        scanf("%d", &A[i]);
    }
    printf("\nEnter number of numbers in the array B:");
    scanf("%d",&nB);
    B = (int *)malloc(nB * sizeof(int));
    printf("\nEnter numbers in the array B: ");
    for(i=0; i<nB; i++)
    {
        scanf("%d", &B[i]);
    }
    fasterAlgo(A, B, n, nB);
    printf("\nArray A after re-arranging: ");
    printArray(A,n);
    free(A);
    free(B);
    return 0;
}
