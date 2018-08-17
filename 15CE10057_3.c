/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode
{
    char word[100];
    struct treenode *leftchild;
    struct treenode *rightchild;
    struct treenode *parent;
}NODE, *NODEPTR;

NODEPTR insert(NODEPTR root);
void inorder(NODEPTR node);
void find_extensions(NODEPTR root, char pattern[100]);
NODEPTR delete_prefix(NODEPTR root, char *pattern);
int compare(char a[100], char b[100], int n);
int check_substr(char a[100], char b[100], int n);

NODEPTR insert(NODEPTR head)
{
    NODEPTR temp1, temp2=head;
    //temp = (NODEPTR*)malloc(sizeof(NODE));
    temp1 =(NODEPTR)malloc(sizeof(NODE));
    printf("\nEnter word:");
    scanf("%s",temp1->word);
    temp1->leftchild = NULL;
    temp1->rightchild = NULL;
    while(1)
    {
    while(strcmp(temp1->word,temp2->word)<0)
    {
        if(temp2->leftchild == NULL){
            temp2->leftchild = temp1;
            temp1->parent = temp2;
            return head;
        }else
        {
        temp2 = temp2->leftchild;
        }
    }
    while(strcmp(temp1->word,temp2->word)>0)
    {
        if(temp2->leftchild == NULL){
            temp2->rightchild = temp1;
            temp1->parent = temp2;
            return head;
        }else
        {
        temp2 = temp2->rightchild;
        }
    }
    }  
}

void inorder(NODEPTR node)
{
    if (node == NULL)
        return;
 
    /* first recur on left child */
    inorder(node->leftchild);
 
    /* then print the data of node */
    printf("%s",node->word);
 
    /* now recur on right child */
    inorder(node->rightchild);
}
int check_substr(char a[100], char b[100], int n)
{
    int flag=0, i;
    for(i=0;i<n;i++){
        if(a[i]=b[i]){
        flag = flag + 1;
        }
    }
    if(flag == n){
    return 1;
    }else{
    return 0;
    }
}
int compare(char a[100], char b[100], int n)
{
    int flag=0, i,j;
    if(a[0]<b[0])
    {
        return 1;
    }
    else if(a[0]==b[0] && a[1]<b[1])
    {
        return 1;
    }else if(a[0]==b[0] && a[1]==b[1] && a[2]<b[2])
    {
        return 1;
    }else if(a[0]==b[0] && a[1]==b[1] && a[2]==b[2])
    {
        return 1;  
    }else
    {
        return 0;
    }
}

void find_extensions(NODEPTR root, char pattern[100])
{
    NODEPTR temp=root;
    int i,n, flag=0;
    n = strlen(pattern);
    do
    {
        if(compare(root->word, pattern,n)==1 && check_substr(root->word, pattern,n)!=1)
        {
            root = root->rightchild;
            continue;   
        }
        else if(compare(root->word, pattern,n)==1 && check_substr(root->word, pattern,n)!=1)
        {
            root = root->leftchild;
            continue;   
        }else if(check_substr(root->word, pattern,n)==1)
        {
            if(root->leftchild == NULL)
            {
                printf("%s",root->word);
                if(root->rightchild == NULL)
                {
                    root=root->parent;
                    continue;
                }else
                {
                    root = root->rightchild;
                    continue;
                }
            }else
            {
                root = root->leftchild;
                continue;
            } 
        }
    }while(root != temp);
    printf("\n");
}

int main()
{
    NODEPTR root=NULL;
    int n,i;
    int test;
    char pattern[100];
    printf("\nEnter the number of words:");
    scanf("%d",&n);
    
    root = (NODEPTR)malloc(sizeof(NODE));
     
    root->leftchild = NULL;
    root->rightchild = NULL;
    root->parent = NULL;
    scanf("%s",root->word);

    for(i=1; i<n; i++)
    {
        root = insert(root);
    }
    
    printf("\nInorder traversal: \n");
    inorder(root);
    printf("\nEnter the pattern:");
    scanf("%s",pattern);
    printf("\nAll extensions of ”%s” in lexicographic order:\n", pattern);
    find_extensions(root,pattern);
    return 0;
}
