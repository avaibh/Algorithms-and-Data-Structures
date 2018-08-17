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
struct node *head ;
} STACK ;

void init(STACK *s);//initializes the head pointer
int isempty(STACK s);//prints 1 if the stack is empty, 0 otherwise
void push(STACK *s, room data);
void pop(STACK *s);
void printmaze(int H[][20], int V[][21], int n);
void createmaze(list maze[][20], int n, int H[][20], int V[][21]);

void pop(STACK *s)
{
   if(isempty(s) == 1)
      printf("\nStack is Empty!!!\n");
   else{
      struct Node *temp = top;
      printf("\nDeleted element: %d", temp->data);
      top = temp->next;
      free(temp);
   }
}

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

void createmaze(list maze[][20], int n, int H[][20], int V[][21])
{
    int i,j;
    /*
    room r[16][16];
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {   
            r[i][j]->hInd = j;
            r[i][j]->vInd = i;
        }
    }*/
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {   
            node *newNode1, *newNode2, *newNode3, *newNode4;
            maze[i][j] = (struct node *)malloc(sizeof(struct node));
            if(maze[i][j] != NULL)
            {
                maze[i][j]->data.hInd = j;
                maze[i][j]->data.vInd = i;
                //H[i-1][j] H[i+1][j] V[i][j-1] V[i][j+1]
                if(H[i-1][j] == 1){
                    //node *newNode1;
                    newNode1 = (struct node *)malloc(sizeof(struct node));
                    if(newNode1 != NULL)
                    {
                        newNode1->data.hInd = j;
                        newNode1->data.vInd = i-1;
                        maze[i][j]->next = newNode1;
                    } 
                }
                if(H[i+1][j] == 1){
                    //node *newNode2;
                    newNode2 = (struct node *)malloc(sizeof(struct node));
                    if(newNode2 != NULL)
                    {
                        newNode2->data.hInd = j;
                        newNode2->data.vInd = i-1;
                        newNode1->next = newNode2;
                    } 
                }
                if(V[i][j-1] == 1){
                    //node *newNode3;
                    newNode3 = (struct node *)malloc(sizeof(struct node));
                    if(newNode3 != NULL)
                    {
                        newNode3->data.hInd = j;
                        newNode3->data.vInd = i-1;
                        newNode2->next = newNode3;
                    } 
                }
                if(V[i][j+1] == 1){
                    //node *newNode4;
                    newNode4 = (struct node *)malloc(sizeof(struct node));
                    if(newNode4 != NULL)
                    {
                        newNode4->data.hInd = j;
                        newNode4->data.vInd = i-1;
                        newNode3->next = newNode4;
                        newNode4->next = NULL;
                    } 
                }
            }
        }
    }
    printf("\nThe linked list representation looks like:: ");   
for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {   
            struct node *temp;
            temp = maze[i][j]->next;
            printf("\n(%d,%d)::",maze[i][j]->data.vInd, maze[i][j]->data.hInd);
            while(temp != NULL){
                printf("-->(%d,%d)",temp->data.vInd,temp->data.hInd);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}
int main(){
int n;
scanf("%d", &n);
int H[21][20], V[20][21];
int i,j,s,t,u,v;
list maze[20][20];
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
scanf("%d", &u);
scanf("%d", &v);
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
printf("%d %d\n",s,t);
printf("Enter the indices of the end room u,v\n");
printf("%d %d\n",u,v);

printmaze(H,V,n);
createmaze(maze,n,H,V);
return 0;
}
