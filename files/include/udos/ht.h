#ifndef UDOS_HT_H
#define UDOS_HT_H

#include "udos/int.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

struct hashtable {
	int_32  size;
	int_32  rehash;
	int_32  max_entries;
	int_32  size_index;
	int_32  entries;
	int_64* table; // low(table[n])==offset high(table[n]==hash
};

struct hashtable* ht_new (int_32 sizeindex);
int ht_rehash (struct hashtable* ht);
void ht_free (struct hashtable *ht);
int_64 ht_search (struct hashtable *ht, int_32 hash);
int_32 ht_search_address (struct hashtable *ht, int_32 hash);
int_32 ht_lookup (struct hashtable *ht, int_32 hash);
void ht_set (struct hashtable *ht, int_32 hash, int_32 data);
void ht_delete (struct hashtable *ht, int_32 hash);

#define HASHSTART 5381
int_32 ht_hash (int_8 *s, int_32 len);
int_32 ht_hash_integer (int_32 i);


/*
Counting bits set by lookup table

static const unsigned char BitsSetTable256[256] = 
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};

unsigned int v; // count the number of bits set in 32-bit value v
unsigned int c; // c is the total bits set in v

// Option 1:
c = BitsSetTable256[v & 0xff] + 
    BitsSetTable256[(v >> 8) & 0xff] + 
    BitsSetTable256[(v >> 16) & 0xff] + 
    BitsSetTable256[v >> 24]; 

// Option 2:
unsigned char * p = (unsigned char *) &v;
c = BitsSetTable256[p[0]] + 
    BitsSetTable256[p[1]] + 
    BitsSetTable256[p[2]] +	
    BitsSetTable256[p[3]];


// To initially generate the table algorithmically:
BitsSetTable256[0] = 0;
for (int i = 0; i < 256; i++)
{
  BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];
}

On July 14, 2009 Hallvard Furuseth suggested the macro compacted table.
*/


#ifdef __cplusplus
}
#endif
#endif
