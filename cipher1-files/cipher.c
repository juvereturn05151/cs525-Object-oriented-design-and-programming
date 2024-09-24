#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

void append_to_buffer(char *buffer, int *index, int value, int bits);
int get_group_number(char character);
int get_encoding_position(char character, int group_pos);

/* may be usefule for debugging */
void print_bit( char v, int pos ) 
{
    char one = 1;
    if ( v & one<<pos ) { printf( "1" ); } else { printf( "0" ); }
}

/* may be usefule for debugging */
void print_bits( char* buffer, int start_pos, int how_many )
{
    int i,j;
    printf( "Bits: " );
    for ( i=0; i<how_many ;  ) 
    { /* for each char */
        char *ch = buffer + (start_pos+i)/8;
        for ( j=0; j<8 && i<how_many; ++j, ++i ) 
        { /* from more significant to less */
            print_bit( *ch, j );
        }
    }
    printf ( "\n" );
}

int read_bit( char const* buffer, int i ) 
{
    char const * ch = buffer + i/8;
    int pos  = i%8;
    return ( *ch & 1<<pos ) ? 1:0;
}

/* decode num_chars characters from ciphertext */
/* function assumes output C-style string is allocated by someone else and big enough */
void decode( char const* ciphertext, int num_chars, char* plaintext ) 
{
    int i,j;
    int pos = 0;
    for( i=0; i<num_chars; ++i ) 
    {
        /* read 2 bits for group (00,01,10,11) */
        int group_index = read_bit( ciphertext , pos ) + 2*read_bit( ciphertext , pos+1 );
        int index = 0; /* index inside group */
        pos +=2;
        for( j=0; j<group_index+1; ++j ) 
        {
            index += ( read_bit( ciphertext, pos ) << j );
            ++pos;
        }
        plaintext[i] = 'a' + ( (1<<(group_index+1)) -2) + index;
    }
    plaintext[num_chars] = 0; /* null terminate final result */
}

/* assume all lower case input a-z (no spaces) */
void encode( char const * plaintext, char* encryptedtext, int *num_bits_used ) 
{
 /*not used,
  but the actual number of bytes needed for encodedtext is num_bits_used/8 + (num_bits_used%8)?1:0*/
    int group_number;
    int encoding_position;
    *num_bits_used = 0;

    while(*plaintext != '\0')
    {
        group_number = get_group_number(*plaintext);
        encoding_position = get_encoding_position(*plaintext, group_number);
        append_to_buffer(encryptedtext, num_bits_used, group_number, 2); 
        append_to_buffer(encryptedtext, num_bits_used, encoding_position, group_number + 1); 
        plaintext++;
    }

    encryptedtext[strlen(encryptedtext)] = '\0';
}

/*Function to append binary representation of an integer to the buffer*/
void append_to_buffer(char *buffer, int *num_bits_used, int value, int bits) 
{
    int i;
    for (i = 0; i < bits; i++) 
    {
        if (value & 1) 
        {
            buffer[*num_bits_used / 8] |= (1 << (*num_bits_used % 8));
        } 
        else 
        {
            buffer[*num_bits_used / 8] &= ~(1 << (*num_bits_used % 8));
        }
        value >>= 1;
        (*num_bits_used)++;
    }
}

int get_encoding_position(char character, int group_pos)
{
    switch (group_pos)
    {
    case 0:
        return abs(character - 'a');
    case 1:
        return abs(character - 'c');
    case 2:
        return abs(character - 'g');
    case 3:
        return abs(character - 'o');
    default:
        break;
    }

    return -1;
}

int get_group_number(char character)
{
    if(character >= 'a' && character <= 'b')
    {
        return 0;
    }
    else if(character >= 'c' && character <= 'f')
    {
        return 1;
    }
    else if(character >= 'g' && character <= 'n')
    {
        return 2;       
    }
    else if(character >= 'o' && character <= 'z')
    {
        return 3;
    }

    return -1;
}
