/*
    Name: Vaibhav Agrawal
    Roll Number: 15CE10057
    Assignment 8
    PC Number: 58
    Date: 06-09-2018
*/

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

typedef struct score
{
    int mscore;
    int escore;
}score, *scorelist;

int NearestProfiles(scorelist T, int n, score *score1, score *score2);
int distance(score s1, score s2);
void merge_M(scorelist T, int l, int m, int r);
void mergeSort_M(scorelist T, int l, int r);
void merge_E(scorelist T, int l, int m, int r);
void mergeSort_E(scorelist T, int l, int r);
int ClusterDist(scorelist section1, int n, scorelist section2, int m, score *score1, score *score2);
int min(int x, int y) 
{
    int d;
    if(x<y)
    {
        d = x;
    }else{
        d = y;
    }
    return d; 
} 
int distance(score s1, score s2)
{
    return(abs(s1.mscore - s2.mscore)+abs(s1.escore - s2.escore));   
}

int closest_point(scorelist P, int n, int *x1, int *x2, int *y1, int *y2) 
{
    int dl,dr,d;  
    if (n <= 3)
    {
        int i,j;
        int min = 201; // Maximum distance possible is 200
        for (i = 0; i < n; ++i) 
            for (j = i+1; j < n; ++j) 
                if (distance(P[i], P[j]) < min) 
                    min = distance(P[i], P[j]); 
        return(min);
    }
   
    int mid = n/2; 
    score midPoint_score = P[mid]; 

    dl = closest_point(P, mid, x1, x2, y1, y2); 
    dr = closest_point(P + mid, n-mid, x1, x2, y1, y2);
    if(dl<dr)
    {
        d = dl;
    }else{
        d = dr;
    }   
   
    scorelist strip;
    int i,j;
    int strip_size = 0; 
    for (i = 0; i < n; i++)
    { 
        if (abs(P[i].mscore - midPoint_score.mscore) < d)
        { 
            strip[strip_size] = P[i]; 
            strip_size+=1; 
        }
    }
    mergeSort_E(strip, 0, strip_size-1);
    int min_distance;
    score s1,s2;
    for (i = 0; i < n; ++i)
    { 
        for (j = i+1; j < n && (strip[j].escore - strip[i].escore) < d; ++j)
        { 
            s1 = strip[i];
            s2 = strip[j];
            if (distance(strip[i],strip[j]) < d)
            { 
                min_distance = distance(strip[i], strip[j]);
                *x1 = strip[i].mscore;
                *y1 = strip[i].escore;
                *x2 = strip[j].mscore;
                *y2 = strip[j].escore; 
            }
        }
    } 
    return min(d, min_distance); 
} 
int NearestProfiles(scorelist T, int n, score *score1, score *score2)
{
    int x1, x2, y1, y2;
    mergeSort_M(T, 0, n-1);
    int minimum_dist; 
    minimum_dist = closest_point(T, n, &x1, &x2, &y1, &y2);
    score1->mscore = x1;
    score1->escore = y1;
    score2->mscore = x2;
    score2->escore = y2;
    return minimum_dist; 
}

int closest_point_part2(score s, scorelist P, int n, int *x1, int *y1) 
{
    int dl,dr,d;  
    if (n <= 2)
    {
        int i;
        int min = 201; // Maximum distance possible is 200
        for (i = 0; i < n; ++i) 
                if (distance(P[i], s) < min) 
                    min = distance(P[i], s); 
        return(min);
    }
   
    int mid = n/2; 
    score midPoint_score = P[mid]; 

    dl = closest_point_part2(s,P, mid, x1,y1); 
    dr = closest_point_part2(s,P + mid, n-mid, x1,y1);
    if(dl<dr)
    {
        d = dl;
    }else{
        d = dr;
    }   
   
    scorelist strip;
    int i;
    int strip_size = 0; 
    for (i = 0; i < n; i++)
    { 
        if (abs(P[i].mscore - midPoint_score.mscore) < d)
        { 
            strip[strip_size] = P[i]; 
            strip_size+=1; 
        }
    }
    mergeSort_E(strip, 0, strip_size-1);
    int min_distance;
    score s1, s2;
    for (i = 0; i < n; ++i)
    { 
        if((s.escore - strip[i].escore) < d){ 
            s1 = strip[i];
            s2 = s;
            if (distance(strip[i],s) < d)
            { 
                min_distance = distance(strip[i], s);
                *x1 = strip[i].mscore;
                *y1 = strip[i].escore; 
            }
        }
    } 
    return min(d, min_distance);  
}

int ClusterDist(scorelist section1, int n, scorelist section2, int m, score *score1, score *score2)
{
    score s1, s2;
    int min_distance,i, dist;
    int x1,x2,y1,y2;
    mergeSort_M(section1, 0, n-1);
    mergeSort_M(section1, 0, m-1);
    min_distance = 201;
    for(i=0;i<n;i++)
    {
        dist = closest_point_part2(section1[i],section2, m, &x1,&y1);
        if(dist<min_distance)
        {
            min_distance = dist;
            score1->mscore =  section1[i].mscore;
            score1->escore =  section1[i].escore; 
            score2->mscore =  x1;
            score2->escore =  y1;
        }
    }
    return min_distance;
}

int main()
{
    score profile1, profile2;
    int n,m,i, distance;
    printf("Hello");
    scanf("%d",&n);
    scorelist section1;
    section1 = (score*)malloc(n*sizeof(score));
    for(i=0; i<n; i++)
    {
        scanf("%d %d", &section1[i].mscore, &section1[i].escore);
    }
    distance = NearestProfiles(section1,n,&profile1,&profile2);
    printf("\nclosest pair:(%d,%d) and (%d, %d) \ndistance=%d", profile1.mscore, profile1.escore, profile2.mscore, profile2.escore, distance);
    
    scanf("%d",&m);
    scorelist section2;
    section2 = malloc(m*sizeof(scorelist));
    for(i=0; i<n; i++)
    {
        scanf("%d %d", &section2[i].mscore, &section2[i].escore);
    }
    distance = ClusterDist(section1,n,section2,m,&profile1,&profile2);
    printf("\nclosest pair:(%d,%d) and (%d, %d) \ndistance=%d", profile1.mscore, profile1.escore, profile2.mscore, profile2.escore, distance);
    return 0;
}
// Sorting is done by merge sort. All the functions are below this comment
void merge_M(scorelist T, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    scorelist L,R;
    L = malloc(n1*sizeof(scorelist));
    R = malloc(n2*sizeof(scorelist)); 

    for (i = 0; i < n1; i++) 
        L[i] = T[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = T[m + 1+ j]; 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (L[i].mscore <= R[j].mscore) 
        { 
            T[k] = L[i]; 
            i++; 
        } 
        else
        { 
            T[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        T[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        T[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
void mergeSort_M(scorelist T, int l, int r) 
{ 
    if (l < r) 
    {  
        int m = l+(r-l)/2; 
  
        mergeSort_M(T, l, m); 
        mergeSort_M(T, m+1, r); 
  
        merge_M(T, l, m, r); 
    } 
} 
void merge_E(scorelist T, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    scorelist L,R;
    L = malloc(n1*sizeof(scorelist));
    R = malloc(n2*sizeof(scorelist)); 

    for (i = 0; i < n1; i++) 
        L[i] = T[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = T[m + 1+ j]; 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (L[i].mscore <= R[j].mscore) 
        { 
            T[k] = L[i]; 
            i++; 
        } 
        else
        { 
            T[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        T[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        T[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
void mergeSort_E(scorelist T, int l, int r) 
{ 
    if (l < r) 
    {  
        int m = l+(r-l)/2; 
  
        mergeSort_E(T, l, m); 
        mergeSort_E(T, m+1, r); 
  
        merge_E(T, l, m, r); 
    } 
} 
