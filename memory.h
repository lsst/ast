#if !defined( MEMORY_INCLUDED )  /* Include this file only once */
#define MEMORY_INCLUDED
/*
*+
*  Name:
*     memory.h

*  Purpose:
*     Define the interface to the Memory module.

*  Description:
*     This module defines functions which wrap up and extend the
*     standard C functions for performing memory allocation. They
*     provide better security against memory leaks, etc., and should
*     not be inter-mixed with the standard C functions.
*
*     Note that this module is not a class implementation, although it
*     resembles one.

*  Functions Defined:
*     Public:
*        None.
*
*     Protected:
*        astAppendString
*           Append a string to another string which grows dynamically.
*        astChrMatch
*           Case-insensitive string comparison.
*        astChrMatchN
*           Case-insensitive string comparison of an most N characters.
*        astFree
*           Free previously allocated memory.
*        astGrow
*           Allocate memory for an adjustable array.
*        astMalloc
*           Allocate memory.
*        astRealloc
*           Change the size of a dynamically allocated region of memory.
*        astSizeOf
*           Determine the size of a dynamically allocated region of memory.
*        astStore
*           Store data in dynamically allocated memory.
*        astString
*           Create a C string from an array of characters.
*        astStringArray
*           Create an array of C strings from an array of characters.
*        astChrLen
*           Returns length of a string without trailing white space, etc.
*        astSscanf
*           Like sscanf, but fixes certain platform-specific bugs in the
*           native sscanf implementation.
*        astTSizeOf
*           Determine the total size of a dynamically allocated region of memory.

*  Copyright:
*     Copyright (C) 1997-2006 Council for the Central Laboratory of the
*     Research Councils

*  Licence:
*     This program is free software; you can redistribute it and/or
*     modify it under the terms of the GNU General Public Licence as
*     published by the Free Software Foundation; either version 2 of
*     the Licence, or (at your option) any later version.
*     
*     This program is distributed in the hope that it will be
*     useful,but WITHOUT ANY WARRANTY; without even the implied
*     warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
*     PURPOSE. See the GNU General Public Licence for more details.
*     
*     You should have received a copy of the GNU General Public Licence
*     along with this program; if not, write to the Free Software
*     Foundation, Inc., 59 Temple Place,Suite 330, Boston, MA
*     02111-1307, USA

*  Authors:
*     RFWS: R.F. Warren-Smith (Starlink)
*     DSB: D.S. Berry (Starlink)

*  History:
*     8-JAN-1996 (RFWS):
*        Original version.
*     26-JAN-1996 (RFWS)
*        Added function interfaces.
*     20-JUN-1996 (RFWS):
*        Added astString.
*     15-JUL-1996 (RFWS):
*        Use improved prologue style, etc. and make all functions protected.
*     11-SEP-1996 (RFWS):
*        Added astStringArray (original written by DSB).
*     18-MAR-1998 (RFWS):
*        Make interface available for writing foreign language and
*        graphics interfaces, etc.
*     18-MAR-1998 (RFWS):
*        Added explicit arguments to function macros.
*     29-JAN-2002 (DSB):
*        Added astChrLen and astSscanf.
*     15-NOV-2002 (DSB):
*        Added astChrMatch astChrMatchN.
*     23-FEB-2006 (DSB):
*        Added astMemCaching and AST__TUNULL.
*     2-MAR-2006 (DSB):
*        Only use astSscanf if the system on which AST was configured
*        showed the non-ANSI behaviour reported by Bill Joye.
*     27-JUN-2007 (DSB):
*        Added astIsDynamic.
*     25-OCT-2007 (DSB):
*        Added astRemoveLeadingBlanks.
*     22-FEB-2008 (DSB):
*        Added astChrSub.

*-
*/

/* Include files. */
/* ============== */
/* Configuration results. */
/* ---------------------- */
#include <config.h>

/* C header files. */
/* --------------- */
#include <stddef.h>
#include "error.h"    

/* Macros. */
/* ======= */

#if defined(astCLASS) || defined(astFORTRAN77)
#define STATUS_PTR status
#else
#define STATUS_PTR astGetStatusPtr
#endif
#define AST__TUNULL -99999

/* Type definitions */
/* ================ */

#if defined(astCLASS) 

/* Header for allocated memory. */
/* ---------------------------- */
/* This stores a "magic" value so that dynamically allocated memory
   can be recognised, together with the allocated size. It also
   ensures correct alignment. */
typedef struct Memory {
   struct Memory *next;
   unsigned long magic;
   size_t size;

#ifdef MEM_DEBUG
   struct Memory *prev; /* Pointer to the previous linked Memory structure */
   int id;      /* A unique identifier for every allocated memory chunk */
   int perm;    /* Is this chunk part of an acceptable once-off "memory leak"? */
#endif

} Memory;

/* Define the largest size of a cached memory block in bytes. This does
   not include the size of the Memory header. This does not need to be
   too big because the vast majority of memory blocks allocated by AST are
   less than a few hundred bytes. */
#define MXCSIZE 300

#endif


#if defined(THREAD_SAFE) && defined(astCLASS) 

/* Define a structure holding all data items that are global within the
   memory.c file. */
typedef struct AstMemoryGlobals {
   size_t Sizeof_Memory;
   int Cache_Init;
   int Use_Cache;
   Memory *Cache[ MXCSIZE + 1 ];

} AstMemoryGlobals;

#endif

/* Function prototypes. */
/* ==================== */

#if defined(THREAD_SAFE) && defined(astCLASS)
void astInitMemoryGlobals_( AstMemoryGlobals * );
#endif

#if defined(astCLASS) || 1       /* Nominally protected, but available for */
                                 /* use in developing (e.g.) foreign */
                                 /* language or graphics interfaces. */
int astMemCaching_( int, int * );
char **astChrSplit_( const char *, int *, int * );
char **astChrSplitRE_( const char *, const char *, int *, const char **, int * );
char **astChrSplitC_( const char *, char, int *, int * );
int astChrMatch_( const char *, const char *, int * );
int astChrMatchN_( const char *, const char *, size_t, int * );
char **astStringArray_( const char *, int, int, int * );
char *astString_( const char *, int, int * );
int astSscanf_( const char *str, const char *format, ...);
size_t astSizeOf_( const void *, int * );
int astIsDynamic_( const void *, int * );
size_t astTSizeOf_( const void *, int * );
void *astFree_( void *, int * );
void *astGrow_( void *, int, size_t, int * );
void *astMalloc_( size_t, int * );
void *astRealloc_( void *, size_t, int * );
void *astStore_( void *, const void *, size_t, int * );
size_t astChrLen_( const char *, int * );
double astChr2Double_( const char *, int * );
void astRemoveLeadingBlanks_( char *, int * );
char *astAppendString_( char *, int *, const char *, int * );
char *astChrSub_( const char *, const char *, const char *[], int, int * );

#ifdef MEM_DEBUG
void astActiveMemory_( const char * );
void astWatchMemory_( int );
void astFlushMemory_( int, int * );
int astMemoryTune_( const char *, int, int * );
void *astMemoryPtr_( int );
void astMemoryAlarm_( const char * );
void astMemoryUse_( const void *, const char *, int * );
int astMemoryId_( const void *, int * );
void astBeginPM_( int * );
void astEndPM_( int * );
#endif

#endif

/* Function interfaces. */
/* ==================== */
/* These wrap up the functions defined by this module. */

#define astChrMatch(str1,str2) astERROR_INVOKE(astChrMatch_(str1,str2,STATUS_PTR))
#define astChrMatchN(str1,str2,n) astERROR_INVOKE(astChrMatchN_(str1,str2,n,STATUS_PTR))
#define astFree(ptr) astERROR_INVOKE(astFree_(ptr,STATUS_PTR))
#define astGrow(ptr,n,size) astERROR_INVOKE(astGrow_(ptr,n,size,STATUS_PTR))
#define astMalloc(size) astERROR_INVOKE(astMalloc_(size,STATUS_PTR))
#define astMemCaching(flag) astERROR_INVOKE(astMemCaching_(flag,STATUS_PTR))
#define astRealloc(ptr,size) astERROR_INVOKE(astRealloc_(ptr,size,STATUS_PTR))
#define astSizeOf(ptr) astERROR_INVOKE(astSizeOf_(ptr,STATUS_PTR))
#define astIsDynamic(ptr) astERROR_INVOKE(astIsDynamic_(ptr,STATUS_PTR))
#define astTSizeOf(ptr) astERROR_INVOKE(astTSizeOf_(ptr,STATUS_PTR))
#define astStore(ptr,data,size) astERROR_INVOKE(astStore_(ptr,data,size,STATUS_PTR))
#define astAppendString(ptr,len,text) astERROR_INVOKE(astAppendString_(ptr,len,text,STATUS_PTR))
#define astString(chars,nchars) astERROR_INVOKE(astString_(chars,nchars,STATUS_PTR))
#define astStringArray(chars,nel,len) astERROR_INVOKE(astStringArray_(chars,nel,len,STATUS_PTR))
#define astChrLen(string) astERROR_INVOKE(astChrLen_(string,STATUS_PTR))
#define astChr2Double(string) astERROR_INVOKE(astChr2Double_(string,STATUS_PTR))
#define astRemoveLeadingBlanks(string) astERROR_INVOKE(astRemoveLeadingBlanks_(string,STATUS_PTR))
#define astChrSub(test,template,subs,nsub) astERROR_INVOKE(astChrSub_(test,template,subs,nsub,STATUS_PTR))

#ifdef HAVE_NONANSI_SSCANF
#define astSscanf astERROR_INVOKE(astSscanf_)
#else
#define astSscanf astERROR_INVOKE(sscanf)
#endif
#define astChrSplit(str,n) astERROR_INVOKE(astChrSplit_(str,n,STATUS_PTR))
#define astChrSplitC(str,c,n) astERROR_INVOKE(astChrSplitC_(str,c,n,STATUS_PTR))
#define astChrSplitRE(str,c,n,m) astERROR_INVOKE(astChrSplitRE_(str,c,n,m,STATUS_PTR))

/* Functions used for debugging memory leaks, etc */
#ifdef MEM_DEBUG

#define astActiveMemory(label) astERROR_INVOKE(astActiveMemory_(label))
#define astMemoryTune(name,value) astERROR_INVOKE(astMemoryTune_(name,value,STATUS_PTR))
#define astWatchMemory(id) astERROR_INVOKE(astWatchMemory_(id))
#define astFlushMemory(leak) astERROR_INVOKE(astFlushMemory_(leak,STATUS_PTR))
#define astBeginPM astERROR_INVOKE(astBeginPM_(STATUS_PTR))
#define astEndPM astERROR_INVOKE(astEndPM_(STATUS_PTR))
#define astMemoryPtr(id) astERROR_INVOKE(astMemoryPtr_(id))
#define astMemoryAlarm(text) astERROR_INVOKE(astMemoryAlarm_(text))
#define astMemoryUse(ptr,text) astERROR_INVOKE(astMemoryUse_(ptr,text,STATUS_PTR))
#define astMemoryId(ptr) astERROR_INVOKE(astMemoryId_(ptr,STATUS_PTR))
#else

#define astActiveMemory(label) 
#define astMemoryTune(name,value)
#define astWatchMemory(id)
#define astFlushMemory(leak) 
#define astBeginPM 
#define astEndPM
#define astMemoryPtr(id) NULL
#define astMemoryAlarm(text)
#define astMemoryUse(ptr,text) 
#define astMemoryId(ptr)

#endif

#endif



