#ifdef __cplusplus
extern "C" { 
#endif

#ifndef FUSE_H
#define FUSE_H

#include <stddef.h> /* size_t definition */
#include <stdio.h>  

enum 
{E_BAD_SOURCE=1, E_BAD_DESTINATION, E_NO_MEMORY };

int unfuse( char const * filename );
int fuse( char const ** filenames, int num_files, char const * output);
/*Applicable On Both Fuse And Unfuse Function*/
void read_and_write_data(char * buffer, int file_size,FILE* read_file, FILE* out_file);
/*Fuse Function*/
int calculate_and_write_filesize(FILE* read_file, FILE* out_file);
/*Unfuse Function*/
void get_filename(char* filename, FILE* read_file);

#endif 

/* 
+-------------+--------+-----------+-------------+--------+-----------+....
|filename1    |filesize|data ......|filename1    |filesize|data ......|....
|\0 terminated| int    |           |\0 terminated| int    |           |....
+-------------+--------+-----------+-------------+--------+-----------+....
*/
#ifdef __cplusplus
}
#endif