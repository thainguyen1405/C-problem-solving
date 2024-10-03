//Programming Assignment 1
//Thai Nguyen
//th313791
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define SIZE 100002

int frequency(char *first, char *second); //Checking the same letters

int main()
{
	
	//allocate memory for both strings
	char *first = malloc(SIZE * sizeof(char));   
    char *second = malloc(SIZE * sizeof(char));  

    printf("Enter the first sign: ");
    fgets(first, SIZE, stdin);   //fgets to read

    if (first[strlen(first) - 1] == '\n')  
        first[strlen(first) - 1] = '\0';

    printf("Enter the second sign: ");
    fgets(second, SIZE, stdin);  //fgets to read

    if (second[strlen(second) - 1] == '\n')
        second[strlen(second) - 1] = '\0';


    int letter = 0; 

    for (int i = 0; second[i] != '\0'; i++)  //Count letters in 2nd sign
    {
        if (second[i] != ' ')
        {
            letter += 1;
        }
    }

    int count = 0;

    int output = frequency(first, second); //Recall the function
    
	count = letter - output;  //Determine letters left to buy
    
	printf("The output is: %d\n", count);
	
	//Free the memory
    free(first);
    free(second);

    return 0;
}

int frequency(char *first, char *second)
{
    int frequency1[ALPHABET_SIZE] = {0};  //Frequency array sign 1 

    for (int i = 0; first[i] != '\0'; i++)
    {
        char x = first[i];
        if (x >= 'A' && x <= 'Z')
        {
            frequency1[x - 'A']++;
        }
    }

    int frequency2[ALPHABET_SIZE] = {0};  //Frequency array sign 2

    for (int i = 0; second[i] != '\0'; i++)
    {
        char y = second[i];
        if (y >= 'A' && y <= 'Z')
        {
            frequency2[y - 'A']++;
        }
    }

    int same = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) //Calculate common letters of two strings
    {
        if (frequency1[i] != 0 && frequency2[i] != 0)
        {
            if (frequency1[i] == frequency2[i])
            {
                same += 1;
            }
            if (frequency1[i] > frequency2[i])
            {
                same += frequency2[i];
            }
            if (frequency1[i] < frequency2[i])
            {
                same += frequency1[i];
            }
        }
    }
    return same;
}