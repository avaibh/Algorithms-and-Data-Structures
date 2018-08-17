/*
Name: Vaibhav Agrawal
Roll Number: 15CE10057
Assignment 4
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
}NODE, *NODEPTR;

NODEPTR makeRoot(NODEPTR root, NODEPTR N);
NODEPTR sameOrientation(NODEPTR root, NODEPTR N);
NODEPTR oppositeOrientation(NODEPTR root, NODEPTR N);
NODEPTR insert(NODEPTR root, int key);
NODEPTR delete(NODEPTR root, int key);

void inOrder(NODEPTR node)
{
    if (node == NULL)
        return;
    inOrder(node->left);
    printf("%d, ",node->value);
    inOrder(node->right);
}

void preOrder(NODEPTR node)
{
    if (node == NULL)
        return;
    printf("%d, ",node->value);
    preOrder(node->left);
    preOrder(node->right);
}

NODEPTR FindMin(NODEPTR root)
{
	while(root->left != NULL) root = root->left;
	return root;
}

NODEPTR makeRoot(NODEPTR root, NODEPTR N)
{
    if(root == NULL || N==NULL || N->parent != root)
    {
        return NULL;
    }
    else if(N == root->left || N == root->right)
    {
        if(root->left == N)
        {
            root->left = N->right;
            N->right->parent = root;
            N->right = root;
            root->parent = N; 
            N->parent =NULL;
        }
        else if(root->right == N)
        {
            root->right = N->left;
            N->left->parent = root;
            N->left = root;
            root->parent = N;
            N->parent =NULL;
        }
    }
    return N;
}

NODEPTR sameOrientation(NODEPTR root, NODEPTR N)
{
    if(root == NULL || N==NULL || N->parent->parent != root)
    {
        return NULL;
    }
    else if(root->left->left == N)
    {
        root->left = root->left->right;
        root->left->parent = root;
        N->parent->right = root;
        root->parent = N->parent;
        N->parent->left = N->right;
        N->right->parent = N->parent;
        N->right=N->parent; 
        N->parent =NULL;
    }
    else if(root->right->right == N)
    {
        root->right = root->right->left;
        root->right->parent = root;
        N->parent->left = root;
        root->parent = N->parent;
        N->parent->right = N->left;
        N->left->parent = N->parent;
        N->left=N->parent; 
        N->parent =NULL;
    }
    return N;
}

NODEPTR oppositeOrientation(NODEPTR root, NODEPTR N)
{
    if(root == NULL || N==NULL || N->parent->parent != root)
    {
        return NULL;
    }
    else if(root->left->right == N)
    {
        root->left = N->right;
        N->right->parent = root;
        root->parent = N;
        N->right = root;
        N->parent->right = N->left;
        N->left->parent = N->parent;
        N->left = N->parent;
        N->parent->parent = N;
        N->parent =NULL;
    }
    else if(root->right->left == N)
    {
        root->right = N->left;
        N->left->parent = root;
        root->parent = N;
        N->left = root;
        N->parent->left = N->right;
        N->right->parent = N->parent;
        N->right = N->parent;
        N->parent->parent = N;
        N->parent =NULL;
    }
    return N;
}
int isElementInBinaryTree(NODEPTR root, int search_item)
{
    if(root) {
        if (search_item == root -> value) return 1;
        if (isElementInBinaryTree(root -> left, search_item)) return 1;
        if (isElementInBinaryTree(root -> right, search_item)) return 1;
    }

    return 0;
}
NODEPTR GetNewNode(int data)
{
    NODEPTR newNode;
    newNode = malloc(sizeof(NODE));
    newNode->value = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}
NODEPTR insert(NODEPTR root, int key)
{
    if(root == NULL) 
    { // empty tree
		root = GetNewNode(key);
	}
	// if data to be inserted is lesser, insert in left subtree. 
	    if(key <= root->value) 
	    {
		    root->left = insert(root->left,key);
		    if(root->left->left->value == key)
		    {
		        root = sameOrientation(root, root->left->left);
		    }
		    else if(root->left->right->value == key)
		    {
		        root = oppositeOrientation(root, root->left->right);
		    }
		    else if(root->left->value == key)
		    {
		        root = makeRoot(root, root->left);
		    }
	    }
	    // else, insert in right subtree. 
	    else 
	    {
		    root->right = insert(root->right,key);
		    if(root->right->right->value == key)
		    {
		        root = sameOrientation(root, root->right->right);
		    }
		    else if(root->right->left->value == key)
		    {
		        root = oppositeOrientation(root, root->right->left);
		    }
		    else if(root->right->value == key)
		    {
		        root = makeRoot(root, root->right);
		    }
	    }
    return root;
}

NODEPTR delete(NODEPTR root, int key)
{ 
    NODEPTR nodeParent;
    if(isElementInBinaryTree(root, key)==1)
    {
        if(root == NULL) return root; 
	    else if(key < root->value) 
	    {
	        root->left = delete(root->left,key);
	        root->left->parent =root;
        }
	    else if(key > root->value) 
	    {
	        root->right = delete(root->right,key);
	        root->right->parent =root;
	    }	
	    else {
		    // Case 1:  No child
		    if(root->left == NULL && root->right == NULL) 
		    { 
			    free(root);
			    root = NULL;
		    }
		    //Case 2: One child 
		    else if(root->left == NULL) 
		    {
			    NODEPTR temp = root;
			    root = root->right;
			    free(temp);
		    }
		    else if(root->right == NULL) 
		    {
			    NODEPTR temp = root;
			    root = root->left;
			    free(temp);
		    }
		    // case 3: 2 children
		    else 
		    { 
			    NODEPTR temp = FindMin(root->right);
			    root->value = temp->value;
			    root->right = delete(root->right,temp->value);
            }
	    }
	    if(root->left->left->value == key || root->right->right->value == key)
        {
            root = sameOrientation(root, root->left->left);
        }
        else if(root->left->right->value == key || root->right->left->value == key)
        {
            root = oppositeOrientation(root, root->left->right);
        }
        else if(root->left->value == key || root->right->value == key)
        {
            root = makeRoot(root, root->left);
        }
	}
	else
	{
	    printf("The value does not exist\n");
	}
	return root; 
}
int main()
{
    NODEPTR root = NULL;
    int n,i;
    printf("\n\nEnter number of numbers to insert:");
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        int temp;
        printf("\nEnter numbers to insert:");
        scanf("%d", &temp);
        root = insert(root, temp);
    }
    printf("\n\npreorder traversal:");
    preOrder(root);
    printf("\ninorder traversal:");
    inOrder(root);
    
    printf("\n\nEnter number of numbers to delete:");
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        int temp;
        printf("\n\nEnter key to delete:");
        scanf("%d", &temp);
        root = delete(root, temp);
        printf("\n\npreorder traversal:");
        preOrder(root);
        printf("\ninorder traversal:");
        inOrder(root);
    }
    return 0;
}
