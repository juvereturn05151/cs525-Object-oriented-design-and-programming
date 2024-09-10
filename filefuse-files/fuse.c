#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG

int fuse( char const ** filenames, int num_files, char const * output)
{
    int BUFFER_SIZE = 1<<16; /* 65 Kb */
    
    FILE *out_file = fopen(output, "wb");  

    if (out_file == NULL) {
        perror("Unable to open output file");
        return -1;
    }
    
    for (int i = 0; i < num_files; i++) {
        FILE *read_file = fopen(filenames[i], "rb");  

        if (read_file == NULL) {
            perror("Unable to open the read file");
            fclose(out_file);
            return -1;
        }

        fwrite(filenames[i], sizeof (char), strlen(filenames[i]) + 1, out_file);

        fseek(read_file, 0L, SEEK_END );
        int file_size = ftell( read_file );
        fseek(read_file, 0L, SEEK_SET );

        fwrite(&file_size, sizeof(int), 1, out_file);

        char * buffer = (char*)malloc(BUFFER_SIZE*sizeof(char));

        if(buffer == NULL)
        {
            perror("Unable to read the buffer");
            fclose(out_file);
            fclose(read_file);
            return -1;
        }

        fread(buffer, sizeof(char), file_size, read_file);
        fwrite(buffer, sizeof(char), file_size, out_file);
    }

    fclose(out_file);
    return 0;
}

int unfuse( char const * filename )
{
}
