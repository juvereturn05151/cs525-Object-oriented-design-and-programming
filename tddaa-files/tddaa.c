/*
2x3x4
+----------------------------------------+
|+------------------++------------------+|
||+----++----++----+||+----++----++----+||
|||1234||1234||1234||||1234||1234||1234|||
||+----++----++----+||+----++----++----+||
|+------------------++------------------+|
+----------------------------------------+

+------+
|abcdef| 6 pointers to 1's ( array of row pointers )
+------+

+--+
|mn| 2 pointers to a and d above ( array of pointers to slices )
+--+

a[i][j][k]
i chooses which slice
j chooses which row within the slice
k chooses within element with the row
*/

#include "tddaa.h"
#include <stdlib.h>

int dimension1;
int dimension2;

int *** allocate( int d1, int d2, int d3 ) 
{
    int i, j;
    int ***three_d_array  = (int ***) calloc(d1, sizeof(int**));
    if(three_d_array == NULL)
    {
        return NULL;
    }

    for (i = 0; i < d1; i++) {
        three_d_array[i] = (int **) calloc(d2, sizeof(int *));
        if (three_d_array[i] == NULL)
        {
            return NULL;  
        }

        
        for (j = 0; j < d2; j++) {
            three_d_array[i][j] = (int *) calloc(d3, sizeof(int));
            if (three_d_array[i][j] == NULL)
            {
                return NULL; 
            }
        }
    }

    dimension1 = d1;
    dimension2 = d2;

    return three_d_array;
}

void deallocate( int *** ppp ) 
{
    int i, j;
    for (i = 0; i < dimension1; i++)
    {
        for (j = 0; j < dimension2; j++)
        {
            free(ppp[i][j]);
        }
        free(ppp[i]);
    }
    free(ppp);
}


