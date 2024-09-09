#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG

int fuse( char const ** filenames, int num_files, char const * output)
{
  int BUFFER_SIZE = 1<<16; /* 65 Kb */

}

int unfuse( char const * filename )
{
}
