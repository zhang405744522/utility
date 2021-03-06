/* ***** BEGIN LICENSE BLOCK ***** 
 * Version: RCSL 1.0/RPSL 1.0 
 *  
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc. All Rights Reserved. 
 *      
 * The contents of this file, and the files included with this file, are 
 * subject to the current version of the RealNetworks Public Source License 
 * Version 1.0 (the "RPSL") available at 
 * http://www.helixcommunity.org/content/rpsl unless you have licensed 
 * the file under the RealNetworks Community Source License Version 1.0 
 * (the "RCSL") available at http://www.helixcommunity.org/content/rcsl, 
 * in which case the RCSL will apply. You may also obtain the license terms 
 * directly from RealNetworks.  You may not use this file except in 
 * compliance with the RPSL or, if you have a valid RCSL with RealNetworks 
 * applicable to this file, the RCSL.  Please see the applicable RPSL or 
 * RCSL for the rights, obligations and limitations governing use of the 
 * contents of the file.  
 *  
 * This file is part of the Helix DNA Technology. RealNetworks is the 
 * developer of the Original Code and owns the copyrights in the portions 
 * it created. 
 *  
 * This file, and the files included with this file, is distributed and made 
 * available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL SUCH WARRANTIES, 
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. 
 * 
 * Technology Compatibility Kit Test Suite(s) Location: 
 *    http://www.helixcommunity.org/content/tck 
 * 
 * Contributor(s): 
 *  
 * ***** END LICENSE BLOCK ***** */ 

/**************************************************************************************
 * Fixed-point MP3 decoder
 * Jon Recker (jrecker@real.com), Ken Cooke (kenc@real.com)
 * June 2003
 *
 * assembly.h - assembly language functions and prototypes for supported platforms
 *
 * - inline rountines with access to 64-bit multiply results 
 * - x86 (_WIN32) and ARM (ARM_ADS, _WIN32_WCE) versions included
 * - some inline functions are mix of asm and C for speed
 * - some functions are in native asm files, so only the prototype is given here
 *
 * MULSHIFT32(x, y)    signed multiply of two 32-bit integers (x and y), returns top 32 bits of 64-bit result
 * FASTABS(x)          branchless absolute value of signed integer x
 * CLZ(x)              count leading zeros in x
 * MADD64(sum, x, y)   (Windows only) sum [64-bit] += x [32-bit] * y [32-bit]
 * SHL64(sum, x, y)    (Windows only) 64-bit left shift using __int64
 * SAR64(sum, x, y)    (Windows only) 64-bit right shift using __int64
 */

#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H

#include <stdint.h> 

#define RDA5991H

#if defined(RDA5991H)

#if defined(__ICCARM__)
#define __inline __INLINE
#endif

#if 1
static __inline int FASTABS(int x)
{
  return((x > 0) ? x : -(x));
}
#endif

#if 0
static __inline int CLZ(int x)
{
  return __CLZ(x);
}
#endif

#if 0
static __inline int CLZ(int x)
{
	int numZeros;

	if (!x)
		return (sizeof(int) * 8);

	numZeros = 0;
	while (!(x & 0x80000000)) {
		numZeros++;
		x <<= 1;
	} 

	return numZeros;
}
#endif

#if 1
static __inline int CLZ(int x)
{
	int numZeros;
		
	if (!x)
		return (sizeof(int) * 8);
	
	__asm{
		CLZ numZeros, x
	}

	return numZeros;
}
#endif

#if 1
static __inline int64_t SAR64(int64_t x, int n)
{
  return (x >> n);
}
#endif

#if 1
static __inline int MULSHIFT32(int x, int y)
{
  int64_t tmp;

  tmp = ((int64_t)x * (int64_t)y);
  return (tmp>>32);
}
#endif

#if 0
static int __inline MULSHIFT32(int x, int y)
{
	int tmp;
	
	__asm{
		SMULL tmp, y, x, y
	}

	return y;
}
#endif

#if 1
static __inline int64_t MADD64(int64_t sum64, int x, int y)
{
  return (sum64 + (int64_t)x * (int64_t)y);
}
#endif

#if 0
static __inline int64_t MADD64(int64_t sum64, int x, int y)
{
	unsigned int sum64Lo = ((unsigned int *)&sum64)[0];
	int sum64Hi = ((int *)&sum64)[1];
	
	__asm{
		SMLAL sum64Lo, sum64Hi, x, y
	}

	sum64 = (((int64_t) sum64Hi) << 32) | sum64Lo;
	
	return sum64;
}
#endif

#else
#error No assembly defined. See valid options in assembly.h
#endif /** RDA5991H */

#endif /* _ASSEMBLY_H */
