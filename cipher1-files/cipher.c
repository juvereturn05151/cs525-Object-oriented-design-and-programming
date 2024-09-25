/*
Auther: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief: Encoding each alphabet into bit numbers
   0  a <-> 0     Group 0 (00) requires only 1 bit to encode 1 character
   1  b <-> 1     b is encoded as 001 (00 specifies group, 1 is the index inside the group
   ----------
   2  c <-> 00     Group 1 (01) requires only 2 bits to encode 1 character
   3  d <-> 01
   4  e <-> 10     e is encoded as 0110 (01 specifies group, 10 is the index inside the group
   5  f <-> 11
   ----------
   6  g <-> 000     Group 2 (10) requires only 3 bits to encode 1 character
   7  h <-> 001
   8  i <-> 010
   9  j <-> 011     j is encoded as 10011 (10 specifies group, 011 is the index inside the group
   10 k <-> 100
   11 l <-> 101
   12 m <-> 110
   13 n <-> 111
   ----------
   14 o <-> 0000     Group 3 (11) requires only 4 bits to encode 1 character
   15 p <-> 0001
   16 q <-> 0010
   17 r <-> 0011
   18 s <-> 0100
   19 t <-> 0101     t is encoded as 110101 (11 specifies group, 0101 is the index inside the group
   20 u <-> 0110
   21 v <-> 0111
   22 w <-> 1000
   23 x <-> 1001
   24 y <-> 1010
   25 z <-> 1011
*/

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
    int group_number;
    int encoding_position;
    *num_bits_used = 0;

    while(*plaintext != '\0')
    {
        group_number = get_group_number(*plaintext);
        if(group_number == -1)
        {
            perror("invalid character");
            return -1;
        }

        encoding_position = get_encoding_position(*plaintext, group_number);
        if(encoding_position == -1)
        {
            perror("invalid character");
            return -1;
        }

        append_to_buffer(encryptedtext, num_bits_used, group_number, 2); 
        append_to_buffer(encryptedtext, num_bits_used, encoding_position, group_number + 1); 
        plaintext++;
    }
}

/*
Brief: 
turn int value into bitnumber, then write it to buffer
Further Explanation: 
        buffer[*num_bits_used / 8] is the location where bit will be written. 
            Note that: buffer[index] will contain up to 8 bits. eg: buffer[0] = 01001111
        (1 << (*num_bits_used % 8)) is used to write/delete bit
            Note that: modular % will give you the position
*/
void append_to_buffer(char *buffer, int *num_bits_used, int value, int bits) 
{
    int i;
    for (i = 0; i < bits; i++) 
    {
        /*
        value & 1 means that the right most value is 1
        */
        if (value & 1) 
        {
            /* |= => add 1 */
            buffer[*num_bits_used / 8] |= (1 << (*num_bits_used % 8));
        } 
        else 
        {
            /* &= ~ => delete 1 */
            buffer[*num_bits_used / 8] &= ~(1 << (*num_bits_used % 8));
        }
        
        value >>= 1;
        (*num_bits_used)++;
    }
}

/*
Brief:
all return value will be converted to bit number (later on: append_to_buffer)
eg. ('x' - 'o' => |-10|) ->  10 => 1010
*/
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

/*
Brief:
all return value will be converted to bit number  (later on: append_to_buffer)
eg. 3 => 11
*/
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
