/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   HEAP_H
#define   HEAP_H

#ifndef   HEAPPORT_H
#include "heapport.h"
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup heap_c Functional Layer Heap Manager
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Heap statistics structures used by heap_stats. */
typedef struct
{
	/** total size of the heap                 */
	BlockSize size;
	/** free (useable) space in the heap       */
	BlockSize free;
	/** number of free blocks                  */
	BlockSize num_free;
	/** number of allocated blocks             */
	BlockSize num_alloced;
}
   HeapStats;

/* Initialization routines. */

void *heap_initialize( char *start, BlockSize size );

/* Runtime API routines. */

void *heap_alloc  ( void *heap, BlockSize size );
void *heap_calloc ( void *heap, BlockSize nmemb, BlockSize size );
void *heap_realloc( void *heap, void *buf, BlockSize size );
void  heap_free   ( void *heap, void *buf );
void  heap_reset  ( void *heap );

/* Runtime Internal routines. */

BlockSize heap_free_space        ( void *heap );
BlockSize heap_biggest_free_block( void *heap );

/* Debug Routines */

long  heap_check( void *heap );
void  heap_dump ( void *heap );
void  heap_stats( void *heap, HeapStats * stats );

/* Error values returned by heap_check() */

#define HEAP_OK              (0x00000000)
#define HERR_BAD_HEAP_STRUCT (0x00000001)
#define HERR_FIRST_BLOCK_BAD (0x00000002)
#define HERR_BLOCK_BAD       (0x00000004)
#define HERR_TOTAL_SIZE_BAD  (0x00000008)
#define HERR_FREE_SIZE_BAD   (0x00000010)
#define HERR_NUM_FREE_BAD    (0x00000020)
#define HERR_NUM_ALLOCED_BAD (0x00000040)
#define HERR_PSIZE_BAD       (0x00000080)
#define HERR_BLOCK_TOO_SMALL (0x00000100)
#define HERR_BLOCK_SIZE_MOD  (0x00000200)
#define HERR_FREE_ADJACENT   (0x00000400)
#define HERR_BAD_FREELPTR    (0x00000800)
/** free list pointer not null */
#define HERR_FREELPTR_NN     (0x00001000)
/** bad free list previous ptr */
#define HERR_BAD_FL_PREV     (0x00002000)
/** bad free list previous ptr */
#define HERR_BAD_FL_NEXT     (0x00004000)
/** too many items in the free list */
#define HERR_BAD_FL_TOO_MANY (0x00008000)
/** not enough items in the free list */
#define HERR_BAD_FL_NOT_NUFF (0x00010000)
/** bad previous link */
#define HERR_BAD_PREV_LINK   (0x00020000)
/** a block in the free list is bad */
#define HERR_FL_BLOCK_BAD    (0x00040000)

#ifdef __cplusplus
   }
#endif
#endif /* HEAP_H */
/** @} */
/** @} */
