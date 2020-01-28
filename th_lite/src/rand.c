/**
 * @file
 * @brief  Functional Layer Pseudo Random Number Generator
 *
 * $RCSfile: rand.c,v $
 *
 * @author  Lawrence Spracklen, Sun Microsystems
 *
 *  EEMBC : TechTag
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/rand.c,v $
 *          
 * @note    
 *
 *
 * HISTORY :
 *
 * $Log: rand.c,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.13  2005/12/02 23:53:35  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.12  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.11  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.10  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.6  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.5  2004/03/15 21:29:06  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.4  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.3  2003/06/05 19:48:56  rick
 * Integrate rand,srand into thip
 *
 * Revision 1.2  2003/06/03 18:54:56  rick
 * Add th_srand, and initialization
 *
 * Revision 1.1  2003/05/28 23:08:39  rick
 * Move GRAND to th_rand
 *
 *
 * @verbatim
 *------------------------------------------------------------------------------
 * Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
 * Benchmark Consortium (EEMBC), Inc. 
 * 
 * All Rights Reserved. This is licensed program product and 
 * is owned by EEMBC. The Licensee understands and agrees that the 
 * Benchmarks licensed by EEMBC hereunder (including methods or concepts 
 * utilized therein) contain certain information that is confidential 
 * and proprietary which the Licensee expressly agrees to retain in the 
 * strictest confidence and to use only in conjunction with the Benchmarks 
 * pursuant to the terms of this Agreement. The Licensee further agrees 
 * to keep the source code and all related documentation confidential and 
 * not to disclose such source code and/or related documentation to any 
 * third party. The Licensee and any READER of this code is subject to 
 * either the EEMBC Member License Agreement and/or the EEMBC Licensee 
 * Agreement. 
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, EEMBC DISCLAIMS ALL 
 * WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, 
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 * PURPOSE, WITH REGARD TO THE BENCHMARKS AND THE ACCOMPANYING 
 * DOCUMENTATION. LICENSEE ACKNOWLEDGES AND AGREES THAT THERE ARE NO 
 * WARRANTIES, GUARANTIES, CONDITIONS, COVENANTS, OR REPRESENTATIONS BY 
 * EEMBC AS TO MARKETABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR OTHER 
 * ATTRIBUTES, WHETHER EXPRESS OR IMPLIED (IN LAW OR IN FACT), ORAL OR 
 * WRITTEN. 
 * 
 * Licensee hereby agrees by accessing this source code that all benchmark 
 * scores related to this code must be certified by ECL prior to publication 
 * in any media, form, distribution, or other means of conveyance of 
 * information subject to the terms of the EEMBC Member License Agreement 
 * and/or EEMBC Licensee Agreement. 
 * 
 * Other Copyright Notice (if any): 
 * 
 * 
 * Copyright (c) 1998-2001 Luigi Rizzo, Universita` di Pisa
 * Portions Copyright (c) 2000 Akamba Corp.
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE @author AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE @author OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/netinet/ip_dummynet.c,v 1.45 2002/02/27 18:32:16 jhb Exp $
 *
 * For conditions of distribution and use, see the accompanying README file.
 *------------------------------------------------------------------------------
 * @endverbatim
 */

/* 
 * We will do a direct call to avoid linking this into every bmark. No Porting Option.
 */

#include	"eembc_dt.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup rand_c Functional Layer Pseudo Random Number Generator
@{ */

/** Internal storage for random seed, and current index into table. */
static unsigned int rnd_ndx = 0;

/* Reed-Solomon uses RAND_MAX, duplicated in thlib.h */
#define TH_RAND_MAX	128
#define NUM_RANDS   (4096)
#define GRAND       (GET_RAND(rnd_ndx++))
#define GET_RAND(i) (ee_rndnums[(i)%NUM_RANDS])

int 	t_rand( void );
void	t_srand(unsigned int seed);

/**
 * Random Number Table : uniform distribution [0,128)  - generated using drand48() 
 * This is also used by Networking QOS to initialize memory to a known random state
 */
const e_u8 ee_rndnums[NUM_RANDS]= {
0x32,0x6b,0x2d,0x39,0x28,0x71,0x01,0x4a,0x14,0x31,0x58,0x07,0x73,0x14,0x14,0x44,0x4d,0x4a,0x22,0x31,
0x25,0x5f,0x26,0x09,0x33,0x6d,0x78,0x54,0x6c,0x00,0x3b,0x44,0x64,0x21,0x7d,0x27,0x4c,0x4d,0x1b,0x71,
0x26,0x13,0x2b,0x31,0x52,0x60,0x4d,0x44,0x3a,0x53,0x29,0x79,0x2f,0x78,0x00,0x42,0x22,0x03,0x4b,0x1a,
0x70,0x07,0x21,0x26,0x72,0x3f,0x5a,0x24,0x6e,0x56,0x3a,0x7a,0x63,0x30,0x1d,0x2d,0x26,0x55,0x5c,0x48,
0x69,0x31,0x68,0x6c,0x17,0x78,0x36,0x42,0x08,0x74,0x70,0x61,0x33,0x58,0x61,0x33,0x10,0x3e,0x1c,0x6f,
0x43,0x00,0x6e,0x02,0x68,0x1f,0x28,0x7b,0x77,0x67,0x3e,0x1c,0x49,0x24,0x29,0x21,0x16,0x00,0x05,0x1e,
0x35,0x59,0x1c,0x40,0x08,0x32,0x3d,0x1b,0x1c,0x75,0x2c,0x18,0x1b,0x51,0x06,0x64,0x03,0x38,0x16,0x77,
0x74,0x3c,0x6f,0x59,0x77,0x3a,0x33,0x72,0x58,0x6b,0x5e,0x53,0x56,0x49,0x22,0x77,0x54,0x06,0x2f,0x4f,
0x13,0x30,0x52,0x03,0x6b,0x09,0x5f,0x20,0x73,0x30,0x28,0x1b,0x53,0x20,0x1d,0x20,0x78,0x11,0x22,0x46,
0x29,0x6e,0x25,0x57,0x6a,0x70,0x53,0x09,0x73,0x20,0x4e,0x6b,0x6a,0x2f,0x60,0x0d,0x6c,0x47,0x6d,0x2b,
0x58,0x2c,0x72,0x7a,0x0f,0x7d,0x07,0x4e,0x04,0x30,0x43,0x24,0x47,0x4d,0x68,0x39,0x03,0x3c,0x24,0x25,
0x19,0x02,0x6a,0x49,0x0d,0x5d,0x0f,0x1c,0x79,0x5e,0x69,0x69,0x20,0x20,0x2b,0x31,0x43,0x22,0x33,0x6f,
0x05,0x25,0x32,0x47,0x27,0x69,0x3c,0x0b,0x21,0x75,0x7d,0x2a,0x73,0x1e,0x2f,0x60,0x3a,0x73,0x36,0x48,
0x7c,0x2d,0x37,0x16,0x1b,0x2b,0x3a,0x05,0x57,0x07,0x46,0x28,0x22,0x40,0x08,0x7b,0x5d,0x67,0x13,0x5a,
0x5d,0x6b,0x4f,0x7a,0x3d,0x43,0x03,0x4d,0x06,0x4b,0x33,0x73,0x2a,0x27,0x6d,0x5d,0x0c,0x2b,0x33,0x7e,
0x50,0x6a,0x37,0x65,0x07,0x11,0x45,0x77,0x71,0x31,0x35,0x6d,0x24,0x0d,0x49,0x63,0x12,0x67,0x5f,0x34,
0x3c,0x2c,0x35,0x03,0x43,0x5b,0x1e,0x58,0x63,0x61,0x0f,0x2f,0x76,0x62,0x25,0x7d,0x36,0x04,0x4c,0x01,
0x60,0x10,0x2f,0x1b,0x49,0x1a,0x64,0x5f,0x3a,0x24,0x6c,0x39,0x6a,0x37,0x2a,0x79,0x1f,0x2d,0x35,0x3f,
0x71,0x48,0x57,0x7b,0x17,0x48,0x03,0x1a,0x14,0x46,0x1a,0x1b,0x08,0x18,0x73,0x64,0x26,0x36,0x7e,0x66,
0x31,0x17,0x1c,0x5e,0x44,0x55,0x19,0x3c,0x48,0x0c,0x23,0x02,0x48,0x71,0x08,0x07,0x20,0x27,0x72,0x11,
0x79,0x36,0x0a,0x64,0x38,0x35,0x59,0x18,0x10,0x1f,0x54,0x11,0x29,0x69,0x01,0x76,0x30,0x4a,0x21,0x34,
0x58,0x60,0x15,0x10,0x14,0x25,0x6d,0x23,0x58,0x6b,0x68,0x06,0x09,0x37,0x5f,0x13,0x34,0x0d,0x61,0x52,
0x5e,0x46,0x0c,0x5d,0x43,0x42,0x24,0x79,0x36,0x3f,0x59,0x21,0x67,0x70,0x00,0x0d,0x22,0x7d,0x2e,0x68,
0x6d,0x25,0x7f,0x01,0x08,0x7b,0x57,0x26,0x5c,0x76,0x53,0x75,0x44,0x7d,0x1d,0x35,0x4a,0x63,0x19,0x73,
0x10,0x76,0x61,0x3d,0x47,0x01,0x31,0x30,0x5d,0x45,0x56,0x4b,0x24,0x0d,0x26,0x43,0x73,0x37,0x79,0x1d,
0x42,0x4e,0x18,0x7d,0x40,0x14,0x45,0x18,0x1f,0x2a,0x13,0x4f,0x1b,0x78,0x4f,0x1b,0x3c,0x6b,0x38,0x0f,
0x75,0x56,0x15,0x63,0x5a,0x17,0x63,0x1b,0x20,0x54,0x7a,0x78,0x67,0x66,0x7e,0x59,0x55,0x0f,0x58,0x13,
0x29,0x39,0x34,0x40,0x6c,0x69,0x48,0x58,0x11,0x6c,0x59,0x1a,0x08,0x38,0x6c,0x26,0x2b,0x44,0x04,0x70,
0x17,0x7b,0x5d,0x38,0x66,0x3f,0x2a,0x13,0x5e,0x39,0x2c,0x4f,0x78,0x11,0x61,0x05,0x4b,0x54,0x01,0x7b,
0x2b,0x6c,0x4e,0x01,0x6d,0x41,0x1e,0x55,0x66,0x07,0x61,0x4f,0x76,0x2e,0x1a,0x29,0x47,0x6f,0x79,0x03,
0x33,0x62,0x54,0x6f,0x65,0x48,0x4b,0x49,0x49,0x23,0x5f,0x35,0x66,0x00,0x15,0x44,0x7b,0x76,0x0c,0x65,
0x29,0x6b,0x05,0x30,0x15,0x33,0x13,0x29,0x3d,0x52,0x0f,0x51,0x5f,0x71,0x72,0x0c,0x70,0x32,0x01,0x63,
0x40,0x0f,0x0a,0x46,0x09,0x63,0x13,0x34,0x03,0x68,0x50,0x14,0x4e,0x47,0x71,0x3d,0x2b,0x0e,0x0a,0x3d,
0x10,0x55,0x58,0x00,0x23,0x24,0x63,0x7c,0x12,0x2c,0x3b,0x2c,0x72,0x32,0x16,0x49,0x76,0x28,0x3f,0x1c,
0x37,0x5b,0x48,0x76,0x75,0x32,0x40,0x50,0x36,0x4e,0x5a,0x1f,0x70,0x20,0x2f,0x48,0x1b,0x22,0x02,0x35,
0x51,0x53,0x22,0x3c,0x07,0x1a,0x23,0x21,0x6b,0x60,0x1e,0x5b,0x46,0x63,0x58,0x3d,0x6b,0x0e,0x66,0x6e,
0x66,0x66,0x42,0x1d,0x70,0x50,0x7f,0x7e,0x23,0x3a,0x3a,0x7c,0x44,0x63,0x5a,0x38,0x37,0x02,0x18,0x4b,
0x10,0x05,0x4b,0x26,0x6d,0x45,0x2c,0x66,0x2a,0x49,0x55,0x06,0x4e,0x5a,0x66,0x75,0x73,0x14,0x09,0x44,
0x5b,0x7b,0x3b,0x32,0x5e,0x7c,0x09,0x00,0x4b,0x7f,0x4b,0x5b,0x09,0x49,0x57,0x3a,0x38,0x60,0x22,0x2b,
0x31,0x38,0x34,0x20,0x0e,0x7d,0x68,0x73,0x3b,0x55,0x1e,0x48,0x7a,0x70,0x76,0x70,0x2e,0x13,0x1e,0x02,
0x4b,0x5c,0x49,0x51,0x5a,0x37,0x28,0x3a,0x33,0x4a,0x34,0x5f,0x7c,0x2f,0x04,0x55,0x49,0x7d,0x3d,0x1b,
0x68,0x42,0x03,0x51,0x2f,0x3b,0x41,0x37,0x50,0x4a,0x13,0x5d,0x07,0x69,0x0f,0x1e,0x4b,0x32,0x33,0x75,
0x54,0x75,0x16,0x01,0x4e,0x23,0x55,0x3a,0x1b,0x03,0x08,0x15,0x21,0x71,0x4a,0x57,0x60,0x4f,0x42,0x77,
0x6e,0x6f,0x72,0x26,0x47,0x78,0x5d,0x08,0x27,0x45,0x40,0x63,0x53,0x15,0x4e,0x47,0x1f,0x1d,0x65,0x0e,
0x4f,0x1c,0x40,0x16,0x23,0x54,0x52,0x65,0x6c,0x10,0x78,0x29,0x64,0x66,0x53,0x0d,0x58,0x4c,0x76,0x36,
0x73,0x58,0x7e,0x7f,0x34,0x03,0x78,0x5a,0x61,0x28,0x54,0x60,0x16,0x3f,0x5d,0x1e,0x00,0x4d,0x3a,0x0c,
0x4e,0x0d,0x1a,0x41,0x6f,0x3c,0x21,0x19,0x45,0x36,0x0c,0x18,0x79,0x29,0x21,0x5c,0x46,0x63,0x10,0x06,
0x59,0x15,0x3e,0x74,0x0a,0x15,0x44,0x26,0x46,0x1a,0x03,0x20,0x49,0x1e,0x0f,0x2b,0x12,0x1c,0x50,0x43,
0x68,0x27,0x05,0x01,0x63,0x3a,0x54,0x23,0x51,0x49,0x61,0x20,0x5f,0x3d,0x6f,0x24,0x28,0x5d,0x46,0x23,
0x52,0x52,0x1e,0x02,0x68,0x23,0x32,0x2a,0x71,0x76,0x65,0x2c,0x24,0x72,0x72,0x18,0x12,0x75,0x38,0x31,
0x3f,0x1d,0x7e,0x60,0x2d,0x11,0x78,0x7c,0x13,0x1d,0x57,0x07,0x08,0x42,0x29,0x37,0x17,0x21,0x3d,0x40,
0x69,0x0a,0x65,0x31,0x01,0x75,0x69,0x79,0x0c,0x50,0x30,0x39,0x6a,0x07,0x5e,0x72,0x0e,0x30,0x60,0x56,
0x58,0x5f,0x57,0x05,0x41,0x63,0x1d,0x08,0x06,0x01,0x78,0x71,0x2a,0x17,0x17,0x1c,0x66,0x01,0x02,0x30,
0x30,0x1f,0x3a,0x79,0x67,0x11,0x7d,0x77,0x29,0x49,0x37,0x2f,0x76,0x45,0x1d,0x5c,0x14,0x20,0x26,0x77,
0x22,0x2e,0x11,0x19,0x7d,0x7c,0x3b,0x31,0x3c,0x29,0x42,0x60,0x74,0x68,0x1f,0x70,0x02,0x51,0x2b,0x3d,
0x21,0x02,0x44,0x7a,0x62,0x2a,0x07,0x65,0x59,0x43,0x6e,0x35,0x63,0x5b,0x3b,0x12,0x11,0x79,0x7e,0x56,
0x2e,0x44,0x22,0x4f,0x6c,0x69,0x23,0x35,0x29,0x51,0x57,0x6c,0x56,0x28,0x13,0x2f,0x59,0x14,0x55,0x2a,
0x0a,0x27,0x14,0x6f,0x28,0x1a,0x6a,0x78,0x7f,0x5d,0x70,0x17,0x4f,0x5e,0x08,0x0e,0x61,0x1b,0x14,0x3e,
0x0c,0x76,0x0f,0x67,0x79,0x69,0x21,0x57,0x2a,0x37,0x04,0x39,0x59,0x17,0x12,0x1f,0x67,0x24,0x6c,0x3a,
0x42,0x5c,0x3a,0x4a,0x62,0x5f,0x60,0x10,0x2c,0x6b,0x59,0x52,0x2c,0x2b,0x71,0x1f,0x42,0x54,0x69,0x55,
0x48,0x48,0x76,0x04,0x24,0x75,0x53,0x31,0x75,0x78,0x09,0x3f,0x75,0x4c,0x4e,0x0f,0x00,0x19,0x19,0x5b,
0x21,0x6a,0x5a,0x6b,0x27,0x0a,0x5d,0x21,0x7d,0x68,0x0b,0x2b,0x5a,0x61,0x1f,0x00,0x23,0x04,0x32,0x30,
0x14,0x1c,0x08,0x64,0x02,0x0c,0x58,0x69,0x6a,0x11,0x50,0x2c,0x40,0x3b,0x70,0x41,0x64,0x46,0x11,0x0f,
0x30,0x60,0x55,0x78,0x15,0x35,0x73,0x4c,0x73,0x05,0x31,0x3d,0x22,0x41,0x44,0x0e,0x0e,0x53,0x2d,0x34,
0x31,0x31,0x5a,0x2d,0x75,0x74,0x27,0x44,0x05,0x14,0x0a,0x57,0x1e,0x12,0x6c,0x7b,0x13,0x54,0x62,0x17,
0x52,0x71,0x15,0x1d,0x0e,0x05,0x17,0x0c,0x64,0x28,0x7b,0x3e,0x0e,0x2d,0x7e,0x1f,0x1e,0x38,0x0c,0x3c,
0x42,0x5a,0x4d,0x59,0x65,0x13,0x4c,0x49,0x69,0x43,0x17,0x15,0x45,0x03,0x37,0x04,0x6c,0x15,0x60,0x15,
0x14,0x3d,0x72,0x31,0x10,0x59,0x08,0x21,0x1c,0x50,0x4d,0x64,0x71,0x58,0x70,0x40,0x73,0x60,0x6e,0x08,
0x4b,0x1d,0x3d,0x2a,0x66,0x69,0x3e,0x7d,0x4d,0x75,0x57,0x0e,0x13,0x01,0x30,0x26,0x78,0x2e,0x0e,0x5d,
0x36,0x71,0x63,0x1f,0x0f,0x12,0x18,0x59,0x17,0x59,0x4b,0x5c,0x64,0x0f,0x0a,0x2a,0x23,0x3c,0x0f,0x0f,
0x35,0x1e,0x01,0x77,0x0b,0x08,0x2b,0x0d,0x6b,0x43,0x18,0x5b,0x79,0x07,0x0e,0x27,0x6d,0x42,0x27,0x0e,
0x72,0x35,0x7b,0x5e,0x40,0x5a,0x57,0x4e,0x1b,0x1d,0x24,0x7c,0x61,0x4a,0x78,0x17,0x33,0x28,0x57,0x30,
0x52,0x70,0x6d,0x34,0x71,0x2e,0x60,0x65,0x5a,0x7f,0x6d,0x6a,0x78,0x4f,0x34,0x44,0x68,0x2a,0x70,0x34,
0x75,0x2a,0x15,0x45,0x1a,0x13,0x42,0x52,0x5a,0x7b,0x50,0x18,0x19,0x69,0x47,0x71,0x61,0x2c,0x10,0x34,
0x79,0x70,0x01,0x3e,0x54,0x74,0x68,0x0a,0x11,0x04,0x7f,0x2c,0x55,0x02,0x10,0x37,0x64,0x3e,0x0a,0x41,
0x6b,0x0a,0x38,0x0f,0x08,0x05,0x30,0x45,0x49,0x1c,0x65,0x4e,0x0e,0x37,0x1d,0x47,0x63,0x73,0x41,0x59,
0x00,0x77,0x29,0x78,0x43,0x2d,0x7d,0x51,0x34,0x5d,0x66,0x6a,0x2d,0x5e,0x21,0x74,0x0e,0x76,0x40,0x75,
0x7e,0x16,0x6b,0x2d,0x78,0x60,0x29,0x07,0x0d,0x45,0x3b,0x68,0x78,0x67,0x3f,0x60,0x38,0x15,0x14,0x2a,
0x02,0x18,0x7a,0x4a,0x05,0x3b,0x2c,0x3b,0x22,0x31,0x09,0x1e,0x01,0x12,0x32,0x13,0x24,0x12,0x3e,0x0b,
0x30,0x6d,0x1d,0x1a,0x68,0x28,0x31,0x41,0x17,0x59,0x1f,0x2a,0x6d,0x56,0x2e,0x6f,0x62,0x4a,0x27,0x3c,
0x0c,0x49,0x62,0x23,0x63,0x3a,0x62,0x7e,0x2f,0x39,0x60,0x6e,0x70,0x6c,0x11,0x18,0x1d,0x28,0x08,0x65,
0x53,0x3b,0x29,0x4e,0x27,0x01,0x3b,0x6d,0x38,0x5b,0x6e,0x28,0x4c,0x7a,0x60,0x7d,0x7e,0x00,0x5f,0x4c,
0x79,0x00,0x31,0x4d,0x1a,0x7b,0x19,0x2b,0x35,0x64,0x24,0x5f,0x7d,0x63,0x61,0x37,0x03,0x32,0x50,0x64,
0x23,0x23,0x4b,0x53,0x6c,0x21,0x2d,0x2e,0x2a,0x22,0x31,0x49,0x6e,0x36,0x56,0x71,0x66,0x49,0x24,0x0e,
0x13,0x7a,0x06,0x2b,0x79,0x41,0x65,0x49,0x47,0x76,0x0a,0x59,0x0e,0x16,0x0b,0x21,0x6d,0x67,0x0e,0x23,
0x46,0x70,0x06,0x6b,0x40,0x0a,0x54,0x69,0x50,0x06,0x03,0x7d,0x1a,0x7e,0x5b,0x51,0x26,0x3a,0x43,0x14,
0x1e,0x7c,0x09,0x2a,0x17,0x2b,0x1f,0x4a,0x16,0x5e,0x47,0x2a,0x47,0x05,0x7f,0x77,0x51,0x32,0x29,0x5d,
0x50,0x75,0x75,0x46,0x69,0x6b,0x10,0x4e,0x2a,0x7f,0x5d,0x48,0x4f,0x5b,0x52,0x4c,0x66,0x4f,0x6e,0x41,
0x6d,0x4f,0x32,0x59,0x13,0x37,0x05,0x58,0x14,0x68,0x4f,0x56,0x24,0x47,0x1d,0x0d,0x54,0x5a,0x2f,0x04,
0x2a,0x30,0x0a,0x7c,0x11,0x3e,0x52,0x27,0x40,0x37,0x34,0x6d,0x0a,0x6f,0x29,0x18,0x6a,0x05,0x76,0x61,
0x21,0x53,0x04,0x37,0x02,0x7d,0x0c,0x16,0x68,0x53,0x39,0x67,0x2c,0x1b,0x18,0x75,0x2b,0x2e,0x30,0x44,
0x1c,0x64,0x10,0x0d,0x13,0x56,0x2c,0x07,0x12,0x39,0x5b,0x34,0x31,0x40,0x7d,0x2d,0x56,0x17,0x33,0x45,
0x2d,0x69,0x57,0x3a,0x68,0x52,0x07,0x4b,0x2e,0x40,0x36,0x0d,0x67,0x05,0x1e,0x6b,0x13,0x55,0x60,0x14,
0x11,0x04,0x6e,0x24,0x5c,0x54,0x56,0x52,0x64,0x42,0x68,0x1e,0x69,0x66,0x7e,0x02,0x3a,0x63,0x2c,0x0a,
0x76,0x5d,0x17,0x61,0x4e,0x0f,0x46,0x32,0x00,0x05,0x37,0x70,0x38,0x54,0x31,0x34,0x40,0x7f,0x79,0x46,
0x01,0x5c,0x54,0x00,0x28,0x4a,0x6b,0x0c,0x0a,0x55,0x06,0x29,0x49,0x71,0x44,0x44,0x39,0x2f,0x10,0x22,
0x15,0x49,0x7f,0x22,0x2a,0x20,0x49,0x0d,0x59,0x72,0x35,0x7c,0x2b,0x75,0x7b,0x5c,0x48,0x5d,0x1a,0x2f,
0x55,0x55,0x7d,0x0a,0x42,0x35,0x19,0x56,0x44,0x71,0x31,0x5a,0x58,0x7a,0x1d,0x0f,0x3e,0x6b,0x79,0x1e,
0x52,0x54,0x50,0x7b,0x2e,0x1a,0x24,0x2c,0x44,0x08,0x06,0x13,0x24,0x28,0x56,0x4a,0x50,0x62,0x26,0x6f,
0x77,0x44,0x1b,0x07,0x7e,0x07,0x21,0x16,0x60,0x47,0x5c,0x25,0x06,0x76,0x53,0x52,0x3a,0x31,0x5a,0x5f,
0x03,0x4b,0x75,0x3c,0x34,0x40,0x11,0x16,0x07,0x78,0x47,0x02,0x70,0x32,0x4b,0x28,0x78,0x46,0x13,0x17,
0x3d,0x0a,0x34,0x6b,0x70,0x4c,0x46,0x04,0x7c,0x17,0x56,0x0c,0x69,0x79,0x02,0x23,0x78,0x26,0x75,0x58,
0x07,0x71,0x56,0x19,0x51,0x77,0x0e,0x33,0x56,0x33,0x14,0x23,0x04,0x78,0x08,0x63,0x51,0x60,0x25,0x28,
0x21,0x40,0x7e,0x18,0x6b,0x0a,0x35,0x03,0x5a,0x7f,0x0f,0x64,0x2e,0x0e,0x36,0x2b,0x1b,0x49,0x15,0x53,
0x5b,0x62,0x33,0x07,0x63,0x34,0x4f,0x01,0x4c,0x0d,0x4a,0x7b,0x6e,0x31,0x44,0x1b,0x69,0x3c,0x5b,0x38,
0x56,0x66,0x5a,0x7b,0x64,0x06,0x70,0x7a,0x57,0x7d,0x73,0x09,0x6b,0x60,0x22,0x07,0x18,0x15,0x69,0x75,
0x2b,0x34,0x13,0x25,0x35,0x70,0x2c,0x48,0x02,0x48,0x6d,0x60,0x46,0x61,0x59,0x54,0x38,0x59,0x27,0x53,
0x24,0x61,0x6a,0x60,0x1a,0x45,0x11,0x6f,0x4e,0x4a,0x2a,0x14,0x1d,0x32,0x7a,0x79,0x5d,0x48,0x21,0x0a,
0x30,0x5e,0x32,0x78,0x1d,0x2d,0x5e,0x79,0x0b,0x7c,0x28,0x5d,0x12,0x78,0x2d,0x06,0x25,0x37,0x76,0x57,
0x78,0x60,0x2e,0x33,0x27,0x60,0x61,0x66,0x52,0x13,0x7c,0x1c,0x6a,0x3c,0x72,0x49,0x42,0x24,0x44,0x27,
0x12,0x2b,0x48,0x34,0x6a,0x5e,0x68,0x7c,0x07,0x1b,0x74,0x44,0x08,0x15,0x3d,0x24,0x08,0x44,0x59,0x59,
0x01,0x4a,0x54,0x67,0x03,0x10,0x69,0x52,0x5f,0x7e,0x4b,0x02,0x69,0x1d,0x60,0x2c,0x38,0x16,0x3a,0x25,
0x74,0x3e,0x2c,0x6b,0x21,0x12,0x03,0x2c,0x45,0x4f,0x22,0x59,0x39,0x1e,0x00,0x55,0x08,0x6e,0x46,0x7b,
0x56,0x1e,0x75,0x54,0x79,0x53,0x1a,0x54,0x4d,0x00,0x01,0x73,0x73,0x20,0x33,0x62,0x1f,0x6d,0x52,0x19,
0x3b,0x56,0x16,0x16,0x21,0x5f,0x6b,0x5f,0x6c,0x0e,0x68,0x49,0x22,0x4c,0x01,0x14,0x6f,0x4c,0x5a,0x19,
0x00,0x3c,0x0f,0x6c,0x5f,0x42,0x72,0x6a,0x1f,0x17,0x2d,0x51,0x4f,0x0c,0x5b,0x29,0x0a,0x64,0x0a,0x1f,
0x2f,0x2a,0x2d,0x57,0x5e,0x76,0x5d,0x7f,0x09,0x56,0x76,0x3e,0x5c,0x2c,0x2d,0x50,0x08,0x12,0x28,0x26,
0x5d,0x07,0x6f,0x03,0x20,0x40,0x79,0x4c,0x5f,0x3d,0x35,0x1b,0x45,0x1a,0x7a,0x54,0x3f,0x4e,0x46,0x7e,
0x70,0x43,0x0e,0x61,0x1b,0x65,0x15,0x18,0x35,0x59,0x55,0x74,0x12,0x63,0x35,0x48,0x61,0x14,0x3b,0x4a,
0x67,0x73,0x13,0x05,0x04,0x10,0x5a,0x4c,0x32,0x08,0x51,0x10,0x69,0x3e,0x32,0x5d,0x10,0x4c,0x30,0x13,
0x4b,0x4b,0x4c,0x2a,0x24,0x57,0x59,0x76,0x2c,0x7c,0x71,0x58,0x29,0x0b,0x75,0x47,0x57,0x1b,0x51,0x64,
0x67,0x68,0x2c,0x0d,0x18,0x7b,0x21,0x39,0x4a,0x11,0x4c,0x63,0x59,0x0f,0x28,0x75,0x5d,0x6f,0x3f,0x56,
0x08,0x3c,0x7b,0x31,0x2b,0x13,0x40,0x7d,0x6b,0x41,0x45,0x73,0x04,0x6a,0x43,0x68,0x15,0x10,0x64,0x70,
0x3a,0x5a,0x14,0x0c,0x3e,0x77,0x6e,0x22,0x69,0x20,0x30,0x0c,0x59,0x20,0x3f,0x18,0x43,0x77,0x3f,0x34,
0x29,0x60,0x23,0x07,0x44,0x45,0x1f,0x4b,0x0f,0x29,0x75,0x51,0x0d,0x5a,0x07,0x70,0x39,0x26,0x0e,0x07,
0x6a,0x50,0x7c,0x6e,0x0d,0x3e,0x5a,0x1e,0x4d,0x61,0x0c,0x21,0x26,0x2d,0x14,0x40,0x45,0x07,0x24,0x35,
0x4b,0x5e,0x48,0x26,0x04,0x02,0x2d,0x55,0x1a,0x6b,0x0f,0x56,0x48,0x17,0x38,0x00,0x35,0x75,0x46,0x4c,
0x75,0x5e,0x65,0x18,0x64,0x79,0x6e,0x2b,0x38,0x04,0x0e,0x6b,0x2d,0x68,0x60,0x02,0x02,0x2c,0x4a,0x57,
0x54,0x06,0x20,0x08,0x17,0x72,0x3b,0x63,0x51,0x67,0x38,0x0f,0x5c,0x0d,0x0b,0x7c,0x09,0x08,0x34,0x58,
0x42,0x64,0x54,0x6e,0x17,0x7a,0x43,0x54,0x19,0x65,0x4f,0x6d,0x33,0x20,0x54,0x40,0x42,0x33,0x39,0x6d,
0x15,0x3b,0x74,0x13,0x5b,0x1a,0x16,0x6f,0x5e,0x3c,0x57,0x05,0x42,0x08,0x37,0x4a,0x5a,0x76,0x00,0x15,
0x52,0x1b,0x4a,0x4e,0x73,0x3a,0x3a,0x3f,0x41,0x6d,0x1d,0x2f,0x55,0x5d,0x54,0x50,0x1b,0x39,0x53,0x7d,
0x52,0x51,0x02,0x01,0x4b,0x01,0x47,0x63,0x7c,0x48,0x0b,0x4c,0x6a,0x02,0x18,0x71,0x78,0x43,0x26,0x49,
0x18,0x0f,0x01,0x2a,0x6e,0x7c,0x4e,0x10,0x50,0x72,0x11,0x02,0x3c,0x62,0x2a,0x15,0x7d,0x6b,0x10,0x19,
0x09,0x1b,0x32,0x24,0x4f,0x53,0x0c,0x6f,0x70,0x21,0x5d,0x2b,0x68,0x03,0x68,0x68,0x5c,0x0c,0x28,0x29,
0x42,0x71,0x01,0x0e,0x22,0x07,0x21,0x3a,0x0f,0x57,0x39,0x76,0x41,0x34,0x67,0x58,0x13,0x3b,0x61,0x77,
0x0e,0x71,0x65,0x23,0x40,0x7a,0x0a,0x4d,0x44,0x09,0x23,0x28,0x7d,0x22,0x7c,0x05,0x40,0x42,0x7b,0x47,
0x44,0x10,0x51,0x22,0x51,0x2b,0x23,0x2d,0x20,0x31,0x22,0x29,0x2e,0x2e,0x3e,0x70,0x7f,0x38,0x77,0x4b,
0x2f,0x35,0x66,0x32,0x57,0x4f,0x62,0x3d,0x14,0x77,0x69,0x6e,0x05,0x7d,0x09,0x71,0x60,0x43,0x19,0x50,
0x60,0x75,0x4f,0x07,0x16,0x0f,0x44,0x45,0x01,0x18,0x38,0x46,0x3d,0x1a,0x51,0x5f,0x08,0x0e,0x5b,0x59,
0x2c,0x39,0x69,0x39,0x70,0x52,0x21,0x2d,0x2f,0x27,0x07,0x33,0x20,0x77,0x0a,0x46,0x21,0x53,0x6e,0x61,
0x52,0x07,0x51,0x68,0x02,0x11,0x14,0x3e,0x30,0x32,0x37,0x19,0x73,0x29,0x75,0x49,0x03,0x66,0x39,0x7b,
0x0c,0x45,0x5c,0x53,0x75,0x65,0x79,0x38,0x06,0x3d,0x41,0x0a,0x2e,0x34,0x3f,0x1b,0x5a,0x02,0x34,0x5c,
0x5f,0x09,0x27,0x71,0x4a,0x20,0x7b,0x21,0x40,0x56,0x5f,0x06,0x58,0x06,0x6e,0x06,0x4f,0x24,0x2e,0x16,
0x04,0x05,0x1d,0x2e,0x0f,0x40,0x57,0x74,0x74,0x26,0x4a,0x70,0x0e,0x1f,0x1d,0x19,0x15,0x71,0x59,0x2a,
0x6e,0x47,0x01,0x32,0x5f,0x2d,0x10,0x20,0x12,0x6f,0x43,0x65,0x2f,0x71,0x3b,0x69,0x7e,0x22,0x24,0x4b,
0x44,0x0f,0x37,0x0a,0x25,0x49,0x02,0x53,0x18,0x72,0x24,0x4c,0x52,0x7d,0x0f,0x26,0x3f,0x11,0x36,0x30,
0x65,0x62,0x01,0x38,0x24,0x67,0x09,0x2f,0x73,0x01,0x1b,0x37,0x36,0x29,0x0f,0x69,0x5e,0x3c,0x13,0x37,
0x4f,0x1e,0x6e,0x39,0x09,0x10,0x11,0x5b,0x28,0x7d,0x77,0x0c,0x78,0x2c,0x40,0x0c,0x58,0x2b,0x30,0x56,
0x04,0x4d,0x5f,0x48,0x45,0x03,0x7a,0x53,0x44,0x6c,0x12,0x38,0x0a,0x05,0x5f,0x49,0x4d,0x72,0x61,0x77,
0x2a,0x6a,0x21,0x77,0x0d,0x24,0x40,0x06,0x52,0x0e,0x03,0x50,0x11,0x4b,0x4e,0x17,0x4f,0x0f,0x51,0x16,
0x10,0x6f,0x22,0x1f,0x0e,0x49,0x44,0x18,0x6b,0x15,0x64,0x3c,0x53,0x60,0x22,0x1a,0x71,0x12,0x4b,0x47,
0x7f,0x4e,0x0f,0x3a,0x4c,0x5d,0x21,0x18,0x58,0x30,0x24,0x05,0x17,0x2d,0x74,0x50,0x75,0x70,0x74,0x27,
0x1d,0x60,0x5d,0x39,0x6c,0x30,0x0c,0x0c,0x3a,0x54,0x4d,0x20,0x71,0x68,0x18,0x1d,0x3c,0x40,0x57,0x48,
0x7d,0x37,0x07,0x25,0x1c,0x19,0x21,0x7f,0x11,0x44,0x33,0x3e,0x10,0x4a,0x42,0x12,0x77,0x58,0x6d,0x37,
0x74,0x36,0x30,0x63,0x39,0x18,0x37,0x0f,0x14,0x02,0x32,0x12,0x5e,0x34,0x4a,0x50,0x37,0x2c,0x55,0x26,
0x15,0x04,0x5a,0x5c,0x57,0x40,0x2f,0x0a,0x4a,0x3f,0x3f,0x4c,0x17,0x2c,0x31,0x11,0x28,0x48,0x5d,0x71,
0x11,0x76,0x02,0x1b,0x39,0x34,0x6c,0x10,0x1a,0x74,0x20,0x7b,0x3c,0x28,0x0c,0x63,0x07,0x29,0x56,0x25,
0x7e,0x15,0x2b,0x0e,0x69,0x35,0x7a,0x1f,0x32,0x36,0x09,0x21,0x23,0x5b,0x79,0x3b,0x73,0x50,0x03,0x67,
0x6d,0x5d,0x26,0x1d,0x37,0x6f,0x2f,0x4a,0x3a,0x49,0x11,0x0c,0x6b,0x16,0x66,0x2e,0x24,0x2a,0x37,0x1f,
0x30,0x04,0x53,0x3e,0x20,0x79,0x56,0x69,0x5c,0x36,0x5c,0x52,0x05,0x12,0x68,0x41,0x15,0x06,0x69,0x19,
0x46,0x2e,0x6a,0x03,0x77,0x66,0x65,0x01,0x12,0x33,0x66,0x02,0x4b,0x7e,0x29,0x64,0x45,0x01,0x18,0x46,
0x5f,0x6b,0x0e,0x3f,0x3a,0x16,0x75,0x19,0x7d,0x79,0x64,0x61,0x51,0x04,0x53,0x2b,0x7c,0x57,0x23,0x46,
0x66,0x25,0x2f,0x33,0x43,0x47,0x70,0x7a,0x38,0x5b,0x05,0x25,0x64,0x1b,0x4c,0x33,0x12,0x76,0x2a,0x38,
0x57,0x36,0x1d,0x7f,0x1d,0x79,0x43,0x4f,0x7c,0x4a,0x43,0x43,0x0e,0x06,0x6f,0x57,0x5c,0x45,0x4d,0x75,
0x63,0x31,0x36,0x30,0x2b,0x22,0x22,0x6f,0x09,0x38,0x63,0x39,0x48,0x63,0x74,0x63,0x34,0x7c,0x0b,0x01,
0x69,0x6f,0x44,0x73,0x40,0x02,0x4a,0x61,0x2d,0x6f,0x4d,0x2f,0x4d,0x73,0x7f,0x08,0x52,0x16,0x6f,0x3b,
0x34,0x56,0x3c,0x54,0x2a,0x43,0x46,0x16,0x46,0x14,0x17,0x3d,0x41,0x29,0x0d,0x0e,0x01,0x79,0x7a,0x48,
0x11,0x56,0x3e,0x32,0x40,0x12,0x5a,0x01,0x54,0x0f,0x59,0x33,0x7c,0x03,0x3a,0x40,0x41,0x6a,0x4c,0x4c,
0x6b,0x0f,0x5a,0x5f,0x38,0x54,0x14,0x20,0x67,0x09,0x19,0x15,0x7b,0x19,0x68,0x20,0x03,0x34,0x26,0x5f,
0x35,0x79,0x6c,0x3f,0x36,0x75,0x0a,0x06,0x7f,0x01,0x7e,0x33,0x15,0x4d,0x2e,0x25,0x3c,0x22,0x53,0x7c,
0x57,0x30,0x2c,0x15,0x6c,0x0a,0x6c,0x7b,0x4e,0x21,0x74,0x29,0x22,0x1b,0x3e,0x07,0x55,0x7c,0x25,0x14,
0x7d,0x5f,0x44,0x4f,0x6c,0x5e,0x5b,0x74,0x03,0x6a,0x58,0x35,0x79,0x5d,0x2c,0x5d,0x4c,0x47,0x10,0x1d,
0x5a,0x26,0x20,0x7b,0x47,0x26,0x3d,0x15,0x78,0x1f,0x13,0x51,0x02,0x32,0x27,0x14,0x4e,0x3e,0x17,0x3a,
0x74,0x00,0x2e,0x7f,0x2c,0x2e,0x4f,0x72,0x63,0x7e,0x28,0x09,0x2b,0x37,0x7c,0x7a,0x15,0x7f,0x7b,0x6d,
0x0c,0x00,0x05,0x62,0x46,0x6f,0x49,0x03,0x42,0x62,0x2a,0x0e,0x19,0x07,0x59,0x15,0x30,0x0c,0x4f,0x4f,
0x3d,0x26,0x6d,0x6a,0x74,0x01,0x48,0x3b,0x36,0x11,0x2c,0x60,0x51,0x4b,0x16,0x7a,0x38,0x5f,0x64,0x15,
0x11,0x68,0x08,0x63,0x6d,0x4e,0x28,0x7a,0x4f,0x7b,0x6a,0x7f,0x21,0x6a,0x7a,0x6e,0x39,0x38,0x37,0x4f,
0x7e,0x5a,0x20,0x49,0x75,0x6c,0x67,0x5c,0x06,0x78,0x14,0x1f,0x4b,0x17,0x12,0x06,0x34,0x18,0x20,0x4f,
0x3b,0x47,0x6b,0x1b,0x7d,0x79,0x2a,0x4c,0x02,0x62,0x45,0x40,0x03,0x75,0x6d,0x06,0x08,0x52,0x57,0x5c,
0x2e,0x43,0x21,0x04,0x73,0x79,0x52,0x2a,0x2f,0x06,0x3e,0x78,0x6b,0x67,0x68,0x62,0x63,0x19,0x21,0x2d,
0x58,0x54,0x18,0x40,0x32,0x71,0x16,0x62,0x10,0x6f,0x1f,0x1f,0x48,0x13,0x13,0x63,0x1b,0x52,0x55,0x40,
0x58,0x5c,0x4a,0x60,0x31,0x39,0x04,0x2d,0x79,0x1a,0x3a,0x37,0x4a,0x2a,0x35,0x36,0x0a,0x18,0x60,0x38,
0x73,0x51,0x05,0x57,0x58,0x56,0x4a,0x14,0x27,0x2a,0x02,0x59,0x77,0x6a,0x08,0x04,0x49,0x73,0x6c,0x01,
0x7c,0x01,0x21,0x7d,0x3f,0x78,0x41,0x08,0x5a,0x07,0x28,0x03,0x7a,0x73,0x78,0x37,0x65,0x2a,0x62,0x1b,
0x7b,0x32,0x18,0x59,0x4c,0x53,0x79,0x1e,0x27,0x77,0x56,0x7b,0x2f,0x26,0x45,0x17,0x53,0x71,0x09,0x45,
0x22,0x39,0x67,0x29,0x36,0x24,0x40,0x67,0x08,0x06,0x17,0x71,0x56,0x41,0x19,0x2f,0x01,0x75,0x79,0x21,
0x38,0x51,0x3c,0x5d,0x6f,0x79,0x05,0x1c,0x79,0x4f,0x29,0x01,0x6d,0x5a,0x31,0x3a,0x75,0x2c,0x11,0x39,
0x4b,0x3b,0x73,0x43,0x10,0x2d,0x6d,0x65,0x3a,0x36,0x6c,0x42,0x67,0x1b,0x17,0x71,0x1b,0x42,0x2e,0x40,
0x2f,0x25,0x71,0x1d,0x62,0x1b,0x68,0x5d,0x1e,0x03,0x41,0x50,0x01,0x7b,0x00,0x79,0x0f,0x34,0x65,0x31,
0x70,0x6b,0x47,0x64,0x13,0x0e,0x53,0x0d,0x34,0x0d,0x33,0x55,0x78,0x75,0x5f,0x3e,0x3d,0x3d,0x68,0x3a,
0x1b,0x47,0x50,0x0e,0x63,0x38,0x48,0x49,0x17,0x47,0x7d,0x5b,0x65,0x23,0x30,0x0b,0x46,0x75,0x50,0x75,
0x48,0x04,0x3b,0x76,0x63,0x3c,0x6e,0x27,0x05,0x2e,0x66,0x14,0x24,0x41,0x20,0x76,0x32,0x0f,0x4d,0x06,
0x57,0x66,0x7e,0x27,0x60,0x10,0x6f,0x2a,0x65,0x52,0x0d,0x55,0x14,0x7c,0x65,0x12,0x57,0x36,0x68,0x4e,
0x2e,0x53,0x4c,0x58,0x26,0x32,0x79,0x51,0x18,0x06,0x58,0x75,0x4a,0x5d,0x56,0x18,0x08,0x58,0x7a,0x09,
0x17,0x61,0x62,0x18,0x7d,0x77,0x61,0x1c,0x72,0x16,0x0c,0x50,0x6e,0x60,0x41,0x61,0x02,0x25,0x3b,0x4b,
0x0d,0x58,0x44,0x6c,0x5c,0x0d,0x60,0x2e,0x0b,0x7a,0x58,0x73,0x2e,0x4a,0x74,0x63,0x2c,0x4a,0x42,0x20,
0x2c,0x7f,0x46,0x1a,0x09,0x6a,0x33,0x2f,0x63,0x0e,0x64,0x50,0x01,0x18,0x0f,0x6c,0x60,0x1b,0x52,0x06,
0x53,0x1e,0x17,0x07,0x42,0x3c,0x21,0x5d,0x11,0x44,0x28,0x7f,0x07,0x6f,0x2d,0x79,0x4a,0x7f,0x0f,0x56,
0x78,0x6d,0x3c,0x63,0x00,0x59,0x7c,0x09,0x47,0x2e,0x25,0x6f,0x1a,0x02,0x1b,0x54,0x4c,0x2b,0x35,0x28,
0x07,0x78,0x18,0x0a,0x06,0x63,0x18,0x5f,0x71,0x78,0x74,0x5d,0x3d,0x3c,0x57,0x32,0x27,0x34,0x6e,0x52,
0x30,0x0a,0x21,0x62,0x03,0x46,0x03,0x0f,0x7a,0x7c,0x14,0x22,0x58,0x7b,0x37,0x44,0x3a,0x7a,0x7d,0x06,
0x55,0x4e,0x1b,0x55,0x28,0x65,0x40,0x26,0x0a,0x51,0x50,0x7a,0x2d,0x43,0x60,0x75,0x0e,0x5b,0x64,0x17,
0x7d,0x57,0x28,0x52,0x65,0x5b,0x31,0x0f,0x06,0x45,0x5f,0x51,0x75,0x33,0x36,0x63,0x6a,0x04,0x79,0x33,
0x6d,0x4e,0x49,0x0e,0x70,0x45,0x77,0x24,0x1e,0x50,0x1b,0x15,0x13,0x62,0x50,0x2a};

/** Get random number. */
int	t_rand( void )
{
	return GRAND;
}
/** Set random seed. */
void	t_srand(unsigned int seed)
{
	rnd_ndx = seed;
}
/** @} */
/** @} */