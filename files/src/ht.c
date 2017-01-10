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
 */

#include "udos/int.h"
#include "udos/ht.h"
#include "udos/system.h"
#include "udos/memory.h"
#include "udos/log.h"

/*
 * From Knuth -- a good choice for hash/rehash values is p, p-2 where
 * p and p-2 are both prime.  These tables are sized to have an extra 10%
 * free to avoid exponential performance degradation as the hash table fills
 */
	{ 2,		5,		3	  },
	{ 4,		7,		5	  },
	{ 8,		13,		11	  },
	{ 16,		19,		17	  },
	{ 32,		43,		41        },
	{ 64,		73,		71        },
	{ 128,		151,		149       },
	{ 256,		283,		281       },
	{ 512,		571,		569       },
	{ 1024,		1153,		1151      },
	{ 2048,		2269,		2267      },
	{ 4096,		4519,		4517      },
	{ 8192,		9013,		9011      },
	{ 16384,	18043,		18041     },
	{ 32768,	36109,		36107     },
	{ 65536,	72091,		72089     },
	{ 131072,	144409,		144407    },
	{ 262144,	288361,		288359    },
	{ 524288,	576883,		576881    },
	{ 1048576,	1153459,	1153457   },
	{ 2097152,	2307163,	2307161   },
	{ 4194304,	4613893,	4613891   },
	{ 8388608,	9227641,	9227639   },
	{ 16777216,	18455029,	18455027  },
	{ 33554432,	36911011,	36911009  },
	{ 67108864,	73819861,	73819859  },
	{ 134217728,	147639589,	147639587 },
	{ 268435456,	295279081,	295279079 },
	{ 536870912,	590559793,	590559791 },
	{ 1073741824,	1181116273,	1181116271},
	{ 2147483648ul,	2362232233ul,	2362232231ul} 
};

#define entry_is_free(ht,x) (x < ht->max_entries && !ht->table[x])
int_64 return (int_64)
