#include <stdio.h>
#include <stdlib.h>

#define MAX_TEXT_LENGTH 1000

int isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int main()
{
    char *text = (char *) malloc(sizeof(char) * MAX_TEXT_LENGTH);
    int i = 0;
    int numberOfIntegers = 0;
    int *vector;

    printf("Please enter the line:\n");
    gets(text);

    for(i = 0; text[i]; i++)
    {
        if(isDigit(text[i]) && (i == 0 || text[i - 1] == ' ' || text[i - 1] == '\t' || text[i - 1] == 0))
        {
            int number = 0, j = 0;

            while(text[i] && isDigit(text[i]))
                number = number * 10 + (text[i++] - '0'); // convert the digits into an integer number and then iuncrement i by 1

            if(text[i] != 0 && text[i] != ' ' && text[i] != '\t')
            {
                // means the number's seperator is non of these standard characters: SPACE, NULL, TAB
                // an example of this is word "48years old"
                // actually this doesnt happen but i'd like to make sure
                // kar az mohkam kari eybnemikone ostad :)
                continue;
                //skip this word as its an input error
            }
            // copy previous integers and then allocate a new memory to vector array with all integers that has been read untill this point(i);
            int *previous = vector;
            vector = (int *) malloc(sizeof(int) * (numberOfIntegers + 1)); //new memory allocation for vector array
            // I KNOW USING OF malloc IS NOT RECOMMENDED; BUT IN THIS SIMPLE CASE I DECIDED TO USE IT, CONSIDERING THE DYNAMIC STATE OF THE PROBLEM

            for(j = 0; j < numberOfIntegers; j++)
                vector[j] = previous[j];

            // add new value to vector & increment 'numberOfIntegers' by 1 ( at the same time )
            vector[ numberOfIntegers++ ] = number; // first add new number then ++

        }
    }

    // printing array in vector format: (a1, a2, a3, ...)
    printf("\n-----------------------------------------------------\n");
    printf("Extracted vector is as bellow:\n\t");

    printf("(");
    for(i = 0; i < numberOfIntegers; i++)
    {
        printf("%d", vector[i]);
        if(i < numberOfIntegers - 1)
            printf(", ");
    }
    printf(")\n");

    printf("vector successfully extracted. \nPress any key to end...");
    getchar();

    free(vector);
    return 0;
}
