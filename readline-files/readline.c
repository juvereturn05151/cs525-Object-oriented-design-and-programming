/*
Code By: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief: Read a string from a file
*/

#include"readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Brief: Read from a file and expand the the stored string size according characters read
buffersize: twice the size everytime the reading is not done
startingPos: starting offset (starts at the last character of the string)
*/

void replace_end_of_line(char * outputString);

char * readline( FILE * file)
{
    char* outputString = NULL;
    int bufferSize = 2;
    int startingPos = 0;

    outputString = (char *)malloc(bufferSize * sizeof(char));

    if (outputString == NULL) 
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    while ( fgets(outputString + startingPos, bufferSize, file ) ) 
    { 
        if (ferror(file)) 
        {
            printf("Error occurs\n");
            free(outputString);
            return NULL;
        }

        startingPos = strlen(outputString);
        bufferSize *= 2;
        
        char* tempString = (char *)realloc(outputString, bufferSize * sizeof(char));

        if (tempString == NULL)
        {
            free(outputString); 
            printf("Memory reallocation failed\n");
            return NULL;
        }

        outputString = tempString;

        if (outputString[startingPos - 1] == '\n' || feof(file)) 
        {
            break;
        }
    }

    replace_end_of_line(outputString);

    return outputString;
}

/*
Brief: Replace end of the line with end of the string
 */
void replace_end_of_line(char * outputString)
{
    int charsRead = strlen(outputString); 

    if(charsRead > 0)
    {
        if (outputString[charsRead - 1] == '\n') 
        {
            outputString[charsRead - 1] = '\0'; 
        }
    }
}