//Programming Assignment 3
//Thai Nguyen
//th313791
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Global variable
int n, p;
char names[10][20];
int pop[10];
int seat[10][10];
int count = 0;

// Function prototypes
int isValid(int check[]);
void countpermute(int check[], int l[], int r);


int main() 
{
    scanf("%d %d", &n, &p);

    for (int i = 0; i < n; i++) 
	{
        scanf("%s %d", names[i], &pop[i]);
    }

    for (int i = 0; i < p; i++) 
	{
        char name1[20], name2[20];
        scanf("%s %s", name1, name2);
		
		
        int pair1, pair2;
        for (int j = 0; j < n; j++) 
		{
            if (strcmp(names[j], name1) == 0) pair1 = j;
            if (strcmp(names[j], name2) == 0) pair2 = j;
        }
        seat[pair1][pair2] = seat[pair2][pair1] = 1; 
    }

    int check[10];
    int l[10] = {0};
	
    countpermute(check, l, 0);
    printf("%d\n", count);

    return 0;
}

// Function to check if a given permutation is valid
int isValid(int check[]) 
{
    for (int i = 0; i < n; i++) 
	{
        if (!pop[check[i]] && (i == 0 || !pop[check[i - 1]]) && (i == n - 1 || !pop[check[i + 1]])) 
		{
            return 0;
        }
        if (i > 0 && seat[check[i]][check[i - 1]]) 
		{
            return 0;
        }
        if (i < n - 1 && seat[check[i]][check[i + 1]]) 
		{
            return 0;
        }
    }
    return 1;
}

// Recursive function to count valid permutations
void countpermute(int check[], int l[], int r) 
{
    if (r == n) 
	{
        if (isValid(check)) 
		{
            count++;
        }
        return;
    }

    for (int i = 0; i < n; i++) 
	{
        if (!l[i]) 
		{
            check[r] = i;
            l[i] = 1; 
            countpermute(check, l, r + 1);
            l[i] = 0; 
        }
    }
}
