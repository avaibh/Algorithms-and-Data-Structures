#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node * prev;
    struct node * next;
};
void traverse_from_front_to_end(struct node *head);
void traverse_from_end_to_front(struct node *tail);
void reverse(struct node *head, struct node *tail, int);

void traverse_from_front_to_end(struct node *head){
    struct node *temp;
    temp = head;
    printf("\nDoubly linked list data traversed from front to end: ");
    while(temp != NULL){
        printf("%d, ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void traverse_from_end_to_front(struct node *tail){
    struct node *temp;
    char data=NULL;
    temp = tail;
    printf("\nDoubly linked list data traversed from front to end: ");
    while(temp != NULL){
        printf("%d, ",temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void reverse(struct node *head, struct node *tail, int n){
    struct node *revNode_h, *revNode_t, *revNode, *temp;
    temp = tail;
    if(head != NULL)
    {
        revNode_h->data = temp->data;
        revNode_h->prev = NULL;
        revNode_h->next = NULL;
        revNode_t = revNode_h;
        // Create rest of the n-1 node
        int i;
        for(i=1; i<=n; i++)
        {
            revNode = (struct node *)malloc(sizeof(struct node));
            if(revNode != NULL)
            {
                temp = temp->prev;
                revNode->data = temp->data;
                revNode->prev = revNode_t; 
                revNode->next = NULL;

                revNode_t->next = revNode; // Link previous node with the new node
                revNode_t = revNode;          // Make new node as last/previous node
            }
            else
            {
                printf("Unable to allocate memory.");
                break;
            }
        }
    }
     traverse_from_front_to_end(revNode_h); 
}

int main()
{
    int n; //length of the doubly linked lists
    printf("What is the length of the doubly linked list");
    scanf("%d", &n);
    int random_numbers[n];
    int i, data;
    for(i=0; i<n; i++){
        random_numbers[i] = rand();
    }
    struct node *head, *tail, *newNode;
    head = (struct node *)malloc(sizeof(struct node));
    if(head != NULL)
    {
        head->data = random_numbers[0];
        head->prev = NULL;
        head->next = NULL;
        tail = head;
        // Create rest of the n-1 node
        for(i=1; i<=n; i++)
        {
            newNode = (struct node *)malloc(sizeof(struct node));
            if(newNode != NULL)
            {
                newNode->data = random_numbers[i];
                newNode->prev = tail; 
                newNode->next = NULL;

                tail->next = newNode; // Link previous node with the new node
                tail = newNode;          // Make new node as last/previous node
            }
            else
            {
                printf("Unable to allocate memory.");
                break;
            }
        }
    }
    traverse_from_front_to_end(head);
    traverse_from_end_to_front(tail);
    reverse(head,tail,n);
    return 0;
}
