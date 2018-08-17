#include<stdio.h>
#include<stdlib.h>

typedef struct rm {
int hInd;
int vInd;
} room;

struct node {
room data;
struct node *next;
};
typedef struct node node, *list;

typedef struct {
struct node *front, *rear ;
} QUEUE ;

void printmaze(int H[][20], int V[][21], int n);
void createmaze(list maze[][20], int n, int H[][20], int V[][21]);
void init(QUEUE *qP);//initializes the front and rear pointers
int isempty(QUEUE *qP);//prints 1 if the queue is emptry, else 0
void enqueue(QUEUE *qP, room data);
room dequeue(QUEUE *qP);
int strategy2(list maze[][20], int n, room start, room end);

void printmaze(int H[][20], int V[][21], int n){
    int i,j;
    printf("+---+---+---+---+\n\n");
    for(i=0; i<n; i++)
    {
    if(i >= 1){
        for(j=0; j<n; j++)
        {
            if(H[i][j] == 0){printf("+---");}
            else{printf("+   ");}
        }
        printf("+\n\n");
    }
        for(j=0; j<n+1; j++)
        {
            if(V[i][j] == 0){printf("|   ");}
            else{printf("    ");}
        }
        printf("\n\n");  
    }
    printf("+---+---+---+---+\n\n");
}

void init(QUEUE *qP){    
    qP->front = NULL;
    qP->rear = NULL;
}
int isempty(QUEUE *qP)
{
    return (qP->rear == NULL);
}
void enqueue(QUEUE *qP, room data){
    node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data.hInd = data.hInd;
    temp->data.vInd = data.vInd;
    temp->next = NULL;
    if(!isempty(qP))
    {
        qP->rear->next = temp;
        qP->rear = temp;
    }
    else
    {
        qP->front = temp;
        qP->rear = temp;
    }
}
room dequeue(QUEUE *qP){
    node *temp;
    room r;
    r.hInd = qP->front->data.hInd;
    r.vInd = qP->front->data.vInd;
    temp = qP->front;
    qP->front = qP->front->next;
    free(temp);
    return(r);
}

int strategy2(list maze[][20], int n, room start, room end){
    int flag[4][4],i,j;
    QUEUE *q;
    struct node *tempN;
    room temp;
    int x,y;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            flag[i][j] = 0;
        }     
    }
    q = malloc(sizeof(QUEUE));
    init(q);
    enqueue(q,start);
    while(!isempty(q)){
        temp = dequeue(q);
        x=temp.vInd;
        y=temp.hInd;
        tempN = maze[x][y]->next;
        flag[x][y] = 1;
        if (x == end.vInd && y ==end.hInd)
        {
            return(1);
        }else{
            while(tempN != NULL){
                temp.vInd = tempN->data.vInd;
                temp.hInd = tempN->data.hInd;
                if (flag[temp.vInd][temp.hInd] == 0){
                    if(q->front ==NULL){
                        init(q);
                    }
                    enqueue(q,temp);
                    // temp = dequeue(q);
                    // printf("-------(%d,%d)\n",temp.vInd,temp.hInd);
                }
                tempN = tempN->next;
            }
        }
    }
    return(0);
}

void createmaze(list maze[][20], int n, int H[][20], int V[][21])
{
    int i,j; 
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {   
            node *newNode1, *newNode2, *newNode3, *newNode4;
            maze[i][j] = (struct node *)malloc(sizeof(struct node));
            newNode1 = (struct node *)malloc(sizeof(struct node));
            newNode2 = (struct node *)malloc(sizeof(struct node));
            newNode3 = (struct node *)malloc(sizeof(struct node));
            newNode4 = (struct node *)malloc(sizeof(struct node));
            if(maze[i][j] != NULL)
            {
                maze[i][j]->data.hInd = j;
                maze[i][j]->data.vInd = i;
                maze[i][j]->next = newNode1;
                //H[i-1][j] H[i+1][j] V[i][j-1] V[i][j+1]
                if(i-1>=0 && H[i][j] == 1){
                    //node *newNode1;
                    // newNode1 = (struct node *)malloc(sizeof(struct node));
                    if(newNode1 != NULL)
                    {
                        newNode1->data.hInd = j;
                        newNode1->data.vInd = i-1;
                        newNode1->next = newNode2;
                    } 
                }else{
                    maze[i][j]->next = newNode2;
                    newNode1->next = NULL;
                }
                if(i+1<=3 && H[i+1][j] == 1){
                    //node *newNode2;
                    // newNode2 = (struct node *)malloc(sizeof(struct node));
                    if(newNode2 != NULL)
                    {
                        newNode2->data.hInd = j;
                        newNode2->data.vInd = i+1;
                        newNode2->next = newNode3;
                        // printf("-->(%d,%d)",newNode2->data.vInd,newNode2->data.hInd);
                    } 
                }else{  
                    newNode2->next = NULL;
                    if (newNode1->next == NULL)
                    {
                        maze[i][j]->next = newNode3;
                    }else{
                        newNode1->next = newNode3;
                    }
                }
                if(j-1>=0 && V[i][j] == 1){
                    //node *newNode3;
                    // newNode3 = (struct node *)malloc(sizeof(struct node));
                    if(newNode3 != NULL)
                    {
                        newNode3->data.hInd = j-1;
                        newNode3->data.vInd = i;
                        newNode3->next = newNode4;
                        // printf("-->(%d,%d)",newNode3->data.vInd,newNode3->data.hInd);
                    } 
                }else{        
                    newNode3->next = NULL;
                    if (newNode1->next == NULL && newNode2->next == NULL)
                    {
                        maze[i][j]->next = newNode4;
                    }else if(newNode1->next != NULL && newNode2->next == NULL){
                        newNode1->next = newNode4;
                    }else if(newNode2->next != NULL){
                        newNode2->next = newNode4;
                    }
                }
                if(j+1<=3 && V[i][j+1] == 1){
                    //node *newNode4;
                    // newNode4 = (struct node *)malloc(sizeof(struct node));
                    if(newNode4 != NULL)
                    {
                        newNode4->data.hInd = j+1;
                        newNode4->data.vInd = i;
                        newNode4->next = NULL;
                        // printf("-->(%d,%d)",newNode4->data.vInd,newNode4->data.hInd);
                        newNode4->next = NULL;
                    } 
                }else{
                    if (newNode1->next == NULL && newNode2->next == NULL && newNode3->next == NULL)
                    {
                        maze[i][j]->next = NULL;
                    }else if(newNode1->next != NULL && newNode2->next == NULL && newNode3->next == NULL){
                        newNode1->next = NULL;
                    }else if(newNode2->next != NULL && newNode3->next == NULL){
                        newNode2->next = NULL;
                    }else if(newNode3->next != NULL){
                        newNode3->next = NULL;
                    }
                }
            }
        }
    }
    printf("\nThe linked list representation looks like:: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {   
            struct node *temp;
            printf("(%d,%d)::",maze[i][j]->data.vInd, maze[i][j]->data.hInd);
            temp = maze[i][j]->next;
            while(temp != NULL){
                printf("-->(%d,%d)",temp->data.vInd,temp->data.hInd);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

int main(){
    int n,strategy2_response;
    scanf("%d", &n);
    int H[21][20], V[20][21];
    int i,j,s,t,u,v;
    list maze[20][20];
    room start,end;
    for(i=0; i<n+1; i++){
        for(j=0; j<n; j++){
            scanf("%d", &H[i][j]);
        }
    }

    for(i=0; i<n; i++){
        for(j=0; j<n+1; j++){
            scanf("%d", &V[i][j]);
        }
    }
    scanf("%d", &s);
    scanf("%d", &t);
    start.hInd = t;
    start.vInd = s;
    scanf("%d", &u);
    scanf("%d", &v);
    end.hInd = v;
    end.vInd = u;
    printf("Enter the value of n\n");
    printf("%d\n",n);
    printf("Enter the horizontal doors H\n");
    for(i=0; i<n+1; i++){
        for(j=0; j<n; j++){
            printf("%d",H[i][j]);
        }
        printf("\n");
    }
    printf("Enter the vertical doors V\n");
    for(i=0; i<n; i++){
        for(j=0; j<n+1; j++){
            printf("%d",V[i][j]);
        }
        printf("\n");
    }
    printf("Enter the indices of the start room s,t\n");
    printf("%d %d\n",start.vInd,start.hInd);
    printf("Enter the indices of the end room u,v\n");
    printf("%d %d\n",u,v);

    printmaze(H,V,n);
    createmaze(maze,n,H,V);

    strategy2_response = strategy2(maze,n,start,end);
    if (strategy2_response == 1)
    {
        printf("\nUsing Strategy 2 ...\nA path is found using strategy 2 from (3,0) to (0,2)\n\n");
    }else{
        printf("No path found\n");
    }
    return 0;
}
