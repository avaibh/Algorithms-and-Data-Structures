/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 9
    PC Number: 58
    Date: 13-09-2018
*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int findMinimumDays(int N, int T);
int findMinimumDaysFaster(int N, int T);
int max(int a, int b);

int main()
{
    int N,T,minD;
    printf("\nWrite n: ");
    scanf("%d",&N);
    printf("\nWrite t: ");
    scanf("%d",&T);
    minD = findMinimumDays(N,T);
    printf("\ng(%d, %d) = %d\n",N,T,minD);
    printf("\nWrite n: ");
    scanf("%d",&N);
    printf("\nWrite t: ");
    scanf("%d",&T);
    minD = findMinimumDaysFaster(N,T);
    printf("\ng(%d, %d) = %d\n",N,T,minD);
    return 0;
}

int max(int a, int b)
{
    if(a > b) {return a;}
    else 
    {return b;}
}
int findMinimumDays(int N, int T)
{
    int **arr;
    int i, j, minimumD , min, temp[T], temp_n, temp_t, k;
    min = 99999;
    arr = (int**)malloc(sizeof(int*)*(N+1));
    for(i=0; i<T;i++)
    {
        arr[i]= (int*)malloc(sizeof(int)*(T+1));
    }
    for(i=0; i<N+1;i++)
    {
        for(j=0; j<T+1;j++)
        {
            if(j==0){arr[i][0] = 0;}
            else if(i==1){arr[1][j] = j;}
            else {arr[i][j] = -1;}
        }
    }

    for(i=1; i<T+1;i++)
    {
        for(j=2; j<N+1;j++)
        {
            for(k=1; k<i+1; k++)
            {
                
                temp_n = arr[j-1][k-1];
                temp_t = arr[j][i-k];
                temp[k] = max(temp_n,temp_t);          
                if(temp[k] < min)  min = temp[k];
            }
            arr[i][j] = min+1;
        }
    }
    
    minimumD = arr[N][T];
    free(arr);
    return minimumD;
}

int findMinimumDaysFaster(int N, int T)
{
    int **arr;
    int i, j, minimumD , min, temp[T], temp_n, temp_t, k;
    min = 99999;
    arr = (int**)malloc(sizeof(int*)*(N+1));
    for(i=0; i<T;i++)
    {
        arr[i]= (int*)malloc(sizeof(int)*(T+1));
    }
    
    for(i=0; i<N+1;i++)
    {
        for(j=0; j<T+1;j++)
        {
            if(j==0){arr[i][0] = 0;}
            else if(i==1){arr[1][j] = j;}
            else {arr[i][j] = -1;}
        }
    }

    for(i=2; i<N+1;i++)
    {
        for(j=1; j<T+1;j++)
        {
            if(a[i][j] < a[i][j+1])
            {
                for(k=1; k<j/2+1; k++)
                {
                    temp[k] = max(arr[j-1][k-1],arr[j][i-k]);          
                    if(temp[k] < min)  min = temp[k];
                }
            }
            else if(a[i][j] > a[i][j+1])
            {
                for(k=j/2+1; k<j+1; k++)
                {
                    temp[k] = max(arr[j-1][k-1],arr[j][i-k]);            
                    if(temp[k] < min)  min = temp[k];
                }
            }
            arr[i][j] = min+1;
        }
    }
    minimumD = arr[N][T];
    free(arr);
    return minimumD;
}
