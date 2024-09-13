/*
Code By: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief: Fuse and unfuse files
*/

#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG
#define MAXIMUM_FILE_NAME 256
#define BUFFER_SIZE (1 << 16) /*Use For Reading the Data*/

/*
Brief: 
Loop through given filesnames
Open the file, and write the file name
Write the file size by using fseek and ftell to calculate the filesize
Read And Write File into the buffer
*/

int fuse( char const ** filenames, int num_files, char const * output)
{
    FILE *out_file; 
    FILE *read_file;
    int index;
    int file_size;
    char * buffer;

    out_file = fopen(output, "wb");  
    if (out_file == NULL) {
        perror("Unable to open output file");
        return -1;
    }

    for (index = 0; index < num_files; index++) 
    {
        read_file = fopen(filenames[index], "rb");  
        if (read_file == NULL) {
            perror("Unable to open the read file");
            fclose(out_file);
            return -1;
        }

        /* Add +1 to strlen to include the null terminator ('\0') in the file*/
        fwrite(filenames[index], sizeof (char), strlen(filenames[index]) + 1, out_file);

        /*Find filesize*/
        file_size = calculate_and_write_filesize( read_file, out_file);

        /*Create a buffer for read and write data*/
        buffer = (char*)malloc(BUFFER_SIZE*sizeof(char));
        if(buffer == NULL)
        {
            perror("Unable to read the buffer");
            fclose(out_file);
            fclose(read_file);
            return -1;
        }
        read_and_write_data(buffer, file_size,  read_file,  out_file);

        free(buffer);
        fclose(read_file);
    }

    fclose(out_file);
    return 0;
}

int unfuse( char const * filename )
{   
    FILE* read_file;
    FILE* out_file;
    char* out_fileName; 
    int file_size;
    char* buffer;

    read_file = fopen(filename, "rb");  
    if (read_file == NULL) {
        perror("Unable to open read_file");
        return -1;
    }

    while(!feof(read_file))
    {
        out_fileName = (char*)malloc(MAXIMUM_FILE_NAME * sizeof(char));
        get_filename(out_fileName, read_file);

        out_file = fopen(out_fileName, "wb");
        if (out_file == NULL) {
            /*NO more file to read*/
            free(out_fileName);
            return 1;
        }

        /*Read the file size*/
        fread(&file_size, sizeof(int), 1, read_file);

        /*Create a buffer for read and write data*/
        buffer = (char*)malloc(file_size*sizeof(char));
        if(buffer == NULL)
        {
            perror("Unable to read the buffer");
            free(buffer);
            fclose(out_file);
            fclose(read_file);
            return -1;
        }
        read_and_write_data(buffer, file_size,  read_file,  out_file);

        free(buffer);
        free(out_fileName);
        fclose(out_file);
    }

    fclose(read_file);
    return 0;
}

/*Applicable On Both Fuse And Unfuse Functions*/
void read_and_write_data(char * buffer, int file_size, FILE* read_file, FILE* out_file)
{
    fread(buffer, sizeof(char), file_size, read_file);
    fwrite(buffer, sizeof(char), file_size, out_file);
}

/*Fuse Functions*/
int calculate_and_write_filesize(FILE* read_file, FILE* out_file)
{
    int file_size;
    fseek(read_file, 0L, SEEK_END );
    file_size = ftell( read_file );
    fseek(read_file, 0L, SEEK_SET );
    fwrite(&file_size, sizeof(int), 1, out_file);
    return file_size;
}

/*Unfuse Functions*/
void get_filename(char* filename, FILE* read_file)
{
    char ch;
    int i;
    size_t read_size;
    i = 0;

   do
   {
        read_size = fread(&ch, sizeof(char), 1, read_file);

        if (read_size == 0 || ch == '\0') {
            filename[i] = '\0';
            break;
        }

        filename[i] = ch;
        i++;
   }
   while (read_size > 0);
}