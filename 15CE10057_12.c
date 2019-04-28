/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 12
    PC Number: 58
    Date: 11-10-2018
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
    int vno;             /* vertex Id */
    struct _node *next;  /* Pointer to the next node in the adjacency list */
} node;

typedef struct _vertex {
    int V;
    node *adjlist;
} vertex;

struct Graph
{
    int numVertices;
    struct node** adjLists;
}Graph; 

typedef vertex* graph;   /* (Dynamic) array of list headers */

node* createNode(int v);
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);\
int DFSComp (graph G, int rem);
int DFSVisit(G,x,v);
void findCritical (graph G);
void findCriticalFast (graph G);

int DFSVisit(G,x,v){
    visited[v] = 1;
    int i=0;
    
    while(G->adjLists[v]->next != NULL) {
        if(V.adjLists[y]===0 && y!=x) 
           i = DFSVisit(G,x,y);
            else G->adjLists[v]=G->adjLists[v]->next;
    }
    visited[v] =1;
    for(i=0;i<G->numVertices;i++){
    if(visited[i] = 0) return 0;
    }
    return 1;
} 
int DFSComp (graph G, int rem){

    int V = G->numVertices;
    int *visited = malloc(sizeof(int)*V);
    int counter = 0;
    for(int v = 0; v < V; v++) 
        visited[v] = 0; 
  
    for (int v=0; v<V; v++) 
    {
        visited[v] = DFSVisit(G, v,rem);
        counter++;
        if (visited[v] == 0) 
        { 
            return counter; 
        } 
    } 
    return -1;
}

void findCritical (graph G){
    int i,number_comp = -1;
    printf("Critical junctions using the simple algorithm:");
    for(i=0; i<G->numVertices; i++){
        int rem_id = G->adjLists[v];
        number_comp = DFSComp(G,rem_id);
        if(number_comp > 1){
            printf("Vertex %d: %d components\n", rem_id, number_comp);
        }
    }
    return;
}
void min(int a, int b){
    int temp;
    if(a<b) temp = a;
    else temp = b;
    return temp;
}
void fast_compute_low(graph G, int discovery[], int low[], int visited[],int pred[],int v){
    visited[v] = 1;
    int time =0;
    low[v] = ++time;
    discovery[v] = ++time;
    node* temp = G->adjLists[v];
    while (temp!=NULL)
        {
            if(visited[temp]==0){
                pred[temp] = v;
                fast_compute_low(G,discovery,low,visited,pred,temp);
                low[v] = min(low[v],low[temp])
            }else if(temp != pred[v]){
                low[v] = min(low[v],discovery[temp]);
            }
            temp = temp->next;
        }
}
void findCriticalFast (graph G){
     int i , v;
     v= G->numVertices;
     int *discovery =  malloc(sizeof(int)*v); 
     int *low =  malloc(sizeof(int)*G->numVertices);
     int *visited =  malloc(sizeof(int)*G->numVertices);
     int *pred =  malloc(sizeof(int)*G->numVertices);
     printf("Critical junctions using the fast algorithm:\n");
     for(i=0; i<v; i++){
        discovery[i] =0;
        low[i] =0;
        visited[i] = 0;
        pred[i]=0;
     }

    for (i = 0; i < v; i++)
    {
        node* temp = graph->adjLists[i];
        fast_compute_low(G,discovery,low,visited,pred,temp);
    }
    for (i = 0; i < v; i++)
    {
        if(pred[i]!=NULL)
    }
    
}

int main(){
    int n, e, i, j, nvertex, temp1, temp2;
    printf("Enter the number of vertices and edges:\n");
    scanf("%d %d", &n, &e);
    Graph* graph = createGraph(n);
    printf("Enter the number of neighbors for each of the vertex:\n");
    for(i=0;i<n;i++){
        printf("Degree of Vertex %d:", i);
        scanf("%d", nvertex);
        printf("\nNeighbors of %d:", i);
        for(j=0; j<nvertex; j++){
            scanf("%d %d",%temp1, &temp2);
            addEdge(graph, temp1, temp2);
        }
    }
    printGraph(graph);
    findCritical(graph);
    void findCriticalFast(graph);
    return 0;
}

node* createNode(int v)
{
    node* newNode = malloc(sizeof(node));
    newNode->vno = v;
    newNode->next = NULL;
    return newNode;
}

graph* createGraph(int V) 
{ 
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = V;
 
    graph->adjLists = malloc(vertices * sizeof(node*));
 
    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
 
    return graph; 
} 

void addEdge(Graph* graph, int src, int dest)
{
    node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
void printGraph(Graph* graph)
{
    int v;
    printf("\nAdjacency list of the graph\n");
    for (v = 0; v < graph->numVertices; v++)
    {
        node* temp = graph->adjLists[v];
        printf("Vertex %d: ", v);
        while (temp)
        {
            printf("%d ", temp->vno);
            temp = temp->next;
        }
        printf("\n");
    }
}
