/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment No.: 13
    PC Number: 58
    Date: 01-11-2018
*/

#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef int **graph;

typedef struct{
    int weight;
    int node1;
    int node2;
}Graph;

int isConnectedUsingBFS(graph G, int numberOfNodes);
void findMST(graph G, int numberOfNodes, int numberOfEdges);
void mergeSort(Graph *A, int l, int r); 
void merge(Graph *A, int l, int m, int r); 

void insert_queue(int vertex, int* front, int* rear, int queue[])
{
    if(*rear == MAX-1)
        printf("Queue Overflow\n");
    else
    {
        if(*front == -1) 
            *front = 0;
        *rear = *rear+1;
        queue[*rear] = vertex ;
    }
}
 
int isEmpty_queue(int* front, int* rear, int queue[])
{
    if(*front == -1 || *front > *rear)
        return 1;
    else
        return 0;
}
 
int delete_queue(int* front, int* rear, int queue[])
{
    
    int delete_item;
    if(*front == -1 || *front > *rear)
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    
    delete_item = queue[*front];
    *front = *front+1;
    return delete_item;
}

void BFS(graph g, int state[], int n)
{
    int i, v=0;
    int queue[MAX];
    int front,rear;
    front = -1;
    rear = -1;
    insert_queue(v, &front, &rear, queue);
    state[v] = 2;
    
    while(!isEmpty_queue(&front, &rear, queue))
    {
        v = delete_queue(&front, &rear, queue);
        //printf("%d ",v);
        state[v] = 3;
        
        for(i=0; i<n; i++)
        {
            if(g[v][i] != 0 && state[i] == 1) 
            {
                insert_queue(i, &front, &rear, queue);
                state[i] = 2;
            }
        }
    }
    printf("\n");
}

int isConnectedUsingBFS(graph G, int numberOfNodes){
    int i, state[MAX];
    for(i=0; i<numberOfNodes; i++){
        state[i] = 1;
    }
    BFS(G, state, numberOfNodes);
    int flag = 0;
    for(i =0; i<numberOfNodes; i++){
        if(state[i] == 3) flag++;
    }
    if(flag == numberOfNodes) return 1;
    else return 0;
}
void findMST(graph G, int numberOfNodes, int numberOfEdges){
    if(isConnectedUsingBFS(G,numberOfNodes == 0)) {
        printf("\nNo MST possible. Graph is not connected\n");
        return;
    }
    int i,j, k=0, a;
    int test[numberOfNodes][numberOfNodes];
    for(i =0; i<numberOfNodes; i++){
        for(j =0; j<numberOfNodes; j++){
            test[i][j] = 0;
    }
    }
    Graph *A = (Graph*)malloc(sizeof(Graph)*numberOfEdges);
    for(i=0; i<numberOfNodes; i++){
     for(j=0; j<numberOfNodes; j++){
        if(G[i][j] != 0 && test[i][j] == 0){
            A[k].weight = G[i][j];
            A[k].node1 = i;
            A[k].node2 = j;
            test[i][j] = 1;
            test[j][i] = 1;
        }
      }   
    }  
    mergeSort(A, 0, numberOfEdges-1);
    int t1, t2, t3, arr[k];
    for(i =0; i<k; i++) arr[i] = 0;
    for(a = k-1; a>=0; a--){
        int bool_val;
        t1 = A[a].weight;
        t2 = A[a].node1;
        t3 = A[a].node2;
        G[t2][t3] = 0;
        G[t3][t2] = 0;
        bool_val = isConnectedUsingBFS(G, numberOfNodes);

        if(bool_val == 0){
            G[t2][t3] = t1;
            G[t3][t2] = t1;
            arr[a] = 1;
        }
        else{
            printf("\nUnknown Error\n");
            return;
        }
    }  
    return;
}
void print(graph g, int n){
    int i, j;
    printf("\nThe neighbors of each node in the input graph and corresponding weights");
    for(i=0; i<n; i++){
    printf("\nVertex %d:", i);
        for(j=0; j<n; j++){
            if(g[i][j] != 0) printf(" %d %d ",j,g[i][j]);
        }
    }
    printf("\n");
    return;
}

int main(){
    int n, m,i,j,k;
    printf("Enter the number of nodes and edges\n");
    scanf("%d", &n);
    scanf("%d", &m);
    graph A;
    A = (int**)malloc(n*(sizeof(int*)));
    for(i=0; i<n;i++){
        A[i] = (int*)malloc(n*(sizeof(int)));
        for(j=0; j<n; j++){
            A[i][j] = 0;
        }
    }
    print(A,n);
    int t1, t2;
     printf("Enter the neighbors of each node and corresponding weights\n");
    for(i=0; i<n;i++){
    printf("\nDegree of vertex %d: ", i);
    scanf("%d", &k);
    printf("\nNeighbors of %d: ", i);
        for(j=0; j<k; j++){
        scanf("%d", &t1);
        scanf("%d", &t2);
        //printf("%d %d \n",t1,t2);
            A[i][t1] = t2;
            A[t1][i] = t2;
        }
    }
    print(A,n);
    findMST(A,n,m);
    print(A,n);
    return 0;
}

void merge(Graph *A, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    Graph *L, *R;
    L = (Graph*)malloc(sizeof(Graph)*n1);
    R = (Graph*)malloc(sizeof(Graph)*n2); 
    for (i = 0; i < n1; i++)
    { 
        L[i].weight = A[l + i].weight;
        L[i].node1 = A[l + i].node1; 
        L[i].node2 = A[l + i].node2;

    }  
    for (j = 0; j < n2; j++)
    { 
        R[j].weight = A[m + 1+ j].weight;
        R[j].node1 = A[m + 1+ j].node1; 
        R[j].node2 = A[m + 1+ j].node2;
    } 
    i = 0; 
    j = 0;
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i].weight <= R[j].weight) 
        { 
            A[k].weight = L[i].weight;
            A[k].node1 = L[i].node1;
            A[k].node2 = L[i].node2; 
            i++; 
        } 
        else
        { 
            A[k].weight = R[j].weight;
            A[k].node1 = R[j].node1;
            A[k].node2 = R[j].node2; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        A[k].weight = L[i].weight;
            A[k].node1 = L[i].node1;
            A[k].node2 = L[i].node2; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        A[k].weight = R[j].weight;
            A[k].node1 = R[j].node1;
            A[k].node2 = R[j].node2; 
        j++; 
        k++; 
    }
    free(L);
    free(R); 
} 

void mergeSort(Graph *A, int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(A, l, m); 
        mergeSort(A, m+1, r); 
        merge(A, l, m, r); 
    } 
} 

