/*
Name: Vaibhav Agrawal
Roll Number: 15CE10057
Assignment 5
PC Number: 58
Date: 16-08-2018
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct _wordR {
    char word[100];
    double x, y;
} wordR;

typedef struct _node{
    wordR w;
    struct _node *next;
} node, *nodePointer;

typedef nodePointer **hashTable;

void insertH(hashTable H, int m, wordR w);
void printH(hashTable H, int m, FILE *fp);
void findNN(hashTable H, int m, wordR w);
double search(hashTable H, int m, wordR w, int i, int j, wordR *nearW);


void printH(hashTable H, int m, FILE *fp)
{
    int i, j;
    nodePointer tempP;
    tempP = (nodePointer)malloc(sizeof(nodePointer));
    for (i=0; i<m; i++) 
    {
       for (j=0; j<m; ++j)
       {
            tempP = H[i][j];
            fprintf(fp, "\n[%d, %d::(]", i, j);
            if(tempP == NULL){
                fprintf(fp, ")");
            }
            else
            {
                while(tempP != NULL)
                {
                    tempP = tempP->next;
                    fprintf(fp, "%s ", tempP->w.word);  
                }
                fprintf(fp, ")");
            }
       }
    }
}

void findNN(hashTable H, int m, wordR w)
{
    int i,j;
    double tempDist, temp_minDist, minDist;
    wordR nearW, nearestWord;
    // nearW = (wordR)malloc(sizeof(wordR));
    // nearestWord = (wordR)malloc(sizeof(wordR));
    temp_minDist =100;
    i = floor(m*w.x);
    j = floor(m*w.y);
    if(i>=m || j>=m)
    {
        printf("Error wrong input\n");
    }
    minDist = search(H, m, w, i, j, &nearW);
    int X,Y,d;
    double r;
    d = 1;
    while(minDist < temp_minDist)
    {
        for(X=i-d; X<i+d; X++)
        {
           for(Y=j-d; Y<j+d; Y++)
           {
                r = sqrt((X-w.x)*(X-w.x)+(Y-w.y)*(Y-w.y));
                if(r < minDist)
                {
                    tempDist = search(H, m, w, X, Y, &nearW);
                    if(tempDist < temp_minDist)
                    {
                        temp_minDist = tempDist;
                        memcpy(nearestWord.word, nearW.word, sizeof nearestWord.word);
                        nearestWord.x = nearW.x;
                        nearestWord.y = nearW.y;
                        
                    }
                }
           } 
        }
        d++;
    }
    minDist = temp_minDist;
    printf("The correct result is   (%s,%f,%f)\n\n",nearestWord.word, nearestWord.x, nearestWord.y);
}
double search(hashTable H, int m, wordR w, int i, int j, wordR *nearW)
{
    double dist, minDist=100;
    nodePointer tempP;
    tempP = (nodePointer)malloc(sizeof(nodePointer));
    tempP = H[i][j];
    while(tempP!=NULL)
    {
        if(!strcmp(tempP->w.word,w.word))
        {
            dist = sqrt((tempP->w.x-w.x)*(tempP->w.x-w.x)+(tempP->w.y-w.y)*(tempP->w.y-w.y));
        }
        if(dist < minDist)
        {
            minDist = dist;
            memcpy(nearW->word, tempP->w.word, sizeof nearW->word);
            nearW->x = tempP->w.x;
            nearW->y = tempP->w.y;
        }
        tempP = tempP->next;
    }
    return minDist;
}
int main()
{
    FILE *inpf, *outf; 
    int n, i, m, j, a;    
    char tempW[100]; 
    double tempX, tempY;
    wordR w;
    hashTable H;
    
    inpf = fopen("input.txt", "r"); 
    if (inpf == NULL) { 
        printf("Error opening input file input.txt\n"); 
        return (-1); 
    }
    outf = fopen("output.txt", "w"); 
    if (outf == NULL) { 
        printf("Error creating output file output.txt\n"); 
        return (-1); 
    }
    
    /* Read no. of elements from input file */ 
    fscanf(inpf, "%d"  , &n); 
    /*Write number of elements in out[put file */ 
    fprintf(outf, "%d"  , n);
    
    m = ceil(sqrt(n));
    printf("%d\n", m);
    H = (nodePointer **)malloc(m * sizeof(nodePointer *));
    
    for (i=0; i<m; i++) 
    {
       H[i] = (nodePointer *)malloc(m * sizeof(nodePointer));
       for (j=0; j<m; ++j)
       {
       		//H[i][j] = NULL; 
       		H[i][j]->w.word = NULL;
       		// printf("\n[%f, %f::(]", H[i][j]->w.x, H[i][j]->w.y);
       } 
    }

	// for (i=0; i<m; i++) 
 //    {
 //       for (j=0; j<m; ++j)
 //       {
 //       		printf("done\n");
 //            printf("\n[%f, %f::(]", H[i][j]->w.x, H[i][j]->w.y);
	// 		printf("well done\n");
	// 		printf("%s )", H[i][j]->w.word);  
 //       }
 //    }
    
    /*  
       Read each element from the input file and  
       write it to the output file  
    */ 
    // for (i=0; i<n; i++) 
    // { 
    //     fscanf(inpf, "%s%lf%lf", tempW, &tempX, &tempY);
    //     memcpy(w.word, tempW, sizeof w.word); //w.word = tempW;
    //     w.x = tempX;
    //     w.y = tempX;
    //     insertH(H, m, w);
    //     //fprintf(outf, "%s    %lf  %lf\n", tempW, tempX, tempY); 
    // }
    
    // printH(H, m, outf);
    fclose(inpf); 
    fclose(outf); 
    printf("Enter the number of words to search:\n");
    scanf("%d", &a);
    return 0;
}

void insertH(hashTable H, int m, wordR w)
{
    int i,j;
    nodePointer tempP;
    i = floor(m*w.x);
    j = floor(m*w.y);
    if(H[i][j] == NULL)
    {
    	printf("%s\n", w.word);
        memcpy(H[i][j]->w.word, w.word, sizeof H[i][j]->w.word); //H[i][j]->w.word = w.word;
        H[i][j]->w.x = w.x;
        H[i][j]->w.y = w.y;
        H[i][j]->next =NULL;
    }
    else
    {
        tempP = (nodePointer)malloc(sizeof(nodePointer));
        tempP = H[i][j]->next;
        while(1)
        {
            if(tempP == NULL)
            {
               memcpy(tempP->w.word, w.word, sizeof tempP->w.word); //tempP->w.word = w.word;
               tempP->w.x = w.x;
               tempP->w.y = w.y;
               tempP->next = NULL; 
               break;
            }
            tempP = tempP->next; 
        }
    }
 return;
}
