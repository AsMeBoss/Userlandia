/*
 * Copyright © 2009 Intel Corporation
 * Copyright © 1988-2004 Keith Packard and Bart Massey.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except as contained in this notice, the names of the authors
 * or their institutions shall not be used in advertising or
 * otherwise to promote the sale, use or other dealings in this
 * Software without prior written authorization from the
 * authors.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *    Keith Packard <keithp@keithp.com>
 * Integration in r2 core api and hackit up
 *    pancake <nopcode.org>
 */

#include "udos/int.h"
#include "udos/ht.h"
#include "udos/system.h"
#include "udos/memory.h"
#include "udos/log.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

/*
 * From Knuth -- a good choice for hash/rehash values is p, p-2 where
 * p and p-2 are both prime.  These tables are sized to have an extra 10%
 * free to avoid exponential performance degradation as the hash table fills
 */
static const struct {
	int_size max_entries, size, rehash;
} hash_sizes[] = {
	{ 2,		5,		3	  }, // [0]
	{ 4,		7,		5	  },
	{ 8,		13,		11	  },
	{ 16,		19,		17	  },
	{ 32,		43,		41        },
	{ 64,		73,		71        },
	{ 128,		151,		149       }, // [6]
	{ 256,		283,		281       },
	{ 512,		571,		569       },
	{ 1024,		1153,		1151      },
	{ 2048,		2269,		2267      },
	{ 4096,		4519,		4517      },
	{ 8192,		9013,		9011      },
	{ 16384,	18043,		18041     },
	{ 32768,	36109,		36107     },
	{ 65536,	72091,		72089     }, // [15]
	{ 131072,	144409,		144407    },
	{ 262144,	288361,		288359    }, // [17]
	{ 524288,	576883,		576881    },
	{ 1048576,	1153459,	1153457   }, // [19]
	{ 2097152,	2307163,	2307161   },
	{ 4194304,	4613893,	4613891   },
	{ 8388608,	9227641,	9227639   },
	{ 16777216,	18455029,	18455027  }, // [23]
	{ 33554432,	36911011,	36911009  },
	{ 67108864,	73819861,	73819859  },
	{ 134217728,	147639589,	147639587 }, // [26] 1GB
	{ 268435456,	295279081,	295279079 }, // 2GB
	{ 536870912,	590559793,	590559791 }, // [28]
	{ 1073741824,	1181116273,	1181116271}, // 10GB
	{ 2147483648ul,	2362232233ul,	2362232231ul} /*FIXME: 2147 millones de registros (2GB max size) */ // [30]
};

#define entry_is_free(ht,x) (x < ht->max_entries && !ht->table[x])
//#define entry_is_deleted(ht,x) (bit_test(ht->free_bitmap,x) && ht->table[x] == (int_64)&deleted_data)
#define entry_is_present(ht,x) (x < ht->max_entries && ht->table[x])

/**
 * Finds a hash table entry with the given key and hash of that key.
 *
 * Returns NULL if no entry is found.  Note that the data pointer may be
 * modified by the user.
 */
int_64 ht_search (struct hashtable *ht, int_32 hash)
{
	int_32 double_hash, hash_address;
	if (ht && ht->entries) {
		hash_address = (int_32)(hash % ht->size);
		do {
			if (entry_is_free (ht, hash_address))
				return (int_64)0;
			if (/*entry_is_present (ht, hash_address) &&*/hash_address < ht->max_entries && (ht->table[hash_address] >> 32) == hash)
				return ht->table[hash_address];

			double_hash = (int_32)(hash % ht->rehash);
			if (double_hash == (int_32)0)
				double_hash = (int_32)1;
			hash_address = (int_32)((hash_address + double_hash) % ht->size);
		} while (hash_address != hash % ht->size);
	}
	return (int_64)0;
}

int_32 ht_search_address (struct hashtable *ht, int_32 hash)
{
	int_32 double_hash, hash_address;
	if (ht && ht->entries) {
		hash_address = (int_32)(hash % ht->size);
		do {
			if (entry_is_free (ht, hash_address))
				return (int_32)0;
			if (/*entry_is_present (ht, hash_address) &&*/hash_address < ht->max_entries && (ht->table[hash_address] >> 32) == hash)
				return hash_address;

			double_hash = (int_32)(hash % ht->rehash);
			if (double_hash == (int_32)0)
				double_hash = (int_32)1;
			hash_address = (int_32)((hash_address + double_hash) % ht->size);
		} while (hash_address != hash % ht->size);
	}
	return (int_32)0;
}

/**
 * Inserts the data with the given hash into the table.
 *
 * Note that insertion may rearrange the table on a resize or rehash,
 * so previously found hash_entries are no longer valid after this function.
 */
static int ht_insert (struct hashtable *ht, int_32 hash, int_32 data)
{
	int_32 hash_address;
	if (!ht || !data)
		return 0;

	if (ht->entries >= ht->max_entries)
		if (!ht_rehash (ht))
			return 0;

	hash_address = hash % ht->size;
	do {
		int_32 double_hash;

		
		if (entry_is_free (ht, hash_address))
		{
			ht->entries++;
			sysinfo()->ht_entries++;

			ht->table[hash_address] = (int_64)( (int_64)hash << 32 | data );

			return 1;
		}
		else if ((ht->table[hash_address] >> 32) == hash)
		{
			ht->table[hash_address] = (int_64)( (int_64)hash << 32 | data );
			return 1;
		}

		double_hash = (int_32)(hash % ht->rehash);
		if (double_hash == (int_32)0)
			double_hash = (int_32)1;
		hash_address = (hash_address + double_hash) % ht->size;
	} while (hash_address != hash % ht->size);

	/* We could hit here if a required resize failed. An unchecked-malloc
	 * application could ignore this result.
	 */
	return 0;
}

int ht_rehash (struct hashtable * ht)
{
    struct hashtable old_ht = *ht;
    int_32 new_size_index = ht->size_index + 1;

	if (new_size_index >= ARRAY_SIZE (hash_sizes)) {
		LOG ("Error: not valid ht size index %u", new_size_index);
		return 0;
	}

	LOG ("ht rehash from:%u to:%u max:%llu", old_ht.size_index, new_size_index, hash_sizes[new_size_index].max_entries);

	// XXX: This code is redupped! fuck't
	ht->table = aalloc (hash_sizes[new_size_index].size * sizeof (int_64));
	if (!ht->table) {
		LOG ("Error: not available memory");
		return 0;
	}
	//set_mem (ht->table, 0, hash_sizes[new_size_index].size * sizeof (*ht->table));
	ht->size_index = new_size_index;
	ht->size = hash_sizes[ht->size_index].size;
	ht->rehash = hash_sizes[ht->size_index].rehash;
	ht->max_entries = hash_sizes[ht->size_index].max_entries;
	ht->entries = 0;
	for (int_32 hash_address = 0; hash_address < old_ht.size; hash_address++) {
		if (entry_is_present ((&old_ht), hash_address))
			ht_insert (ht, (old_ht.table[hash_address] >> 32), (int_32)(old_ht.table[hash_address]));
	}

    if (old_ht.entries != ht->entries)
        LOG ("Error ht reshash transfer entries");

	sysinfo()->ht_entries -= old_ht.entries;
	afree (old_ht.size * sizeof (int_64), old_ht.table);

	return 1;
}

struct hashtable* ht_new (int_32 sizeindex)
{
	struct hashtable * ht;
	if (sizeindex < 5) sizeindex = 11;
	if (sizeindex > 30) sizeindex = 30;

	ht = (struct hashtable *)aalloc (sizeof(struct hashtable));
	if (!ht)
		return NULL;
	ht->size = hash_sizes[sizeindex/*0*/].size;
	//set_mem (ht->table, 0, (int_size)ht->size * sizeof(*ht->table));
	ht->size_index = sizeindex;
	ht->entries = 0;
	ht->rehash = hash_sizes[ht->size_index].rehash;
	ht->max_entries = hash_sizes[ht->size_index].max_entries;
    ht->table = (int_64*)aalloc (hash_sizes[sizeindex].size * sizeof(int_64));

	return ht;
}

void ht_free (struct hashtable *ht)
{
	if (ht) {
		if (ht->entries)
			sysinfo()->ht_entries -= (ht->entries);

        afree ((ht->size * sizeof(int_64)), ht->table);
		afree (sizeof(struct hashtable), ht);
	}
}

int_32 ht_lookup (struct hashtable *ht, int_32 hash)
{
	if (!ht) return (int_64)0;
	int_64 entry = ht_search (ht, hash);

	if (!entry) return (int_32)0;
	else return (int_32)entry;
}

void ht_set (struct hashtable *ht, int_32 hash, int_32 data)
{
	ht_insert (ht, hash, data);
}

void ht_delete (struct hashtable *ht, int_32 hash)
{
	if (!ht) return;

	int_64 entry = ht_search (ht, hash);
	if (entry)
	{
		hash = (entry >> 32);
		ht->table[hash] = (int_64)0;
		ht->entries--;
		sysinfo()->ht_entries--;
	}
}

int_32 ht_hash (int_8 *s, int_32 len)
{
    int_32 h = HASHSTART;
    if (len > 0)
        for (int_32 i = 0; i < len; i++)
            h = (h + (h << 5)) ^* s++;
    return h;
}

