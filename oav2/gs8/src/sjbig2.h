/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: sjbig2.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Definitions for jbig2decode filter */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sjbig2_INCLUDED
#  define sjbig2_INCLUDED

#include "stdint_.h"
#include "scommon.h"
#include <jbig2.h>

/* JBIG2Decode internal stream state */
typedef struct stream_jbig2decode_state_s
{
    stream_state_common;	/* a define from scommon.h */
    Jbig2GlobalCtx *global_ctx;
    Jbig2Ctx *decode_ctx;
    Jbig2Image *image;
    long offset; /* offset into the image bitmap of the next byte to be returned */
    int error;
}
stream_jbig2decode_state;

#define private_st_jbig2decode_state()	\
  gs_private_st_simple(st_jbig2decode_state, stream_jbig2decode_state,\
    "jbig2decode filter state")
extern const stream_template s_jbig2decode_template;

/* call ins to process the JBIG2Globals parameter */
public int
s_jbig2decode_make_global_data(byte *data, uint length, void **result);
public int
s_jbig2decode_set_global_data(stream_state *ss, void *data);
public void
s_jbig2decode_free_global_data(void *data);
	
#endif /* sjbig2_INCLUDED */