#if !defined( NULLREGION_INCLUDED ) /* Include this file only once */
#define NULLREGION_INCLUDED
/*
*+
*  Name:
*     nullregion.h

*  Type:
*     C include file.

*  Purpose:
*     Define the interface to the NullRegion class.

*  Invocation:
*     #include "nullregion.h"

*  Description:
*     This include file defines the interface to the NullRegion class and
*     provides the type definitions, function prototypes and macros,
*     etc.  needed to use this class.
*
*     The NullRegion class implement a Region with no boundaries.

*  Inheritance:
*     The NullRegion class inherits from the Region class.

*  Feature Test Macros:
*     astCLASS
*        If the astCLASS macro is undefined, only public symbols are
*        made available, otherwise protected symbols (for use in other
*        class implementations) are defined. This macro also affects
*        the reporting of error context information, which is only
*        provided for external calls to the AST library.

*  Copyright:
*     <COPYRIGHT_STATEMENT>

*  Authors:
*     DSB: David S. Berry (Starlink)

*  History:
*     11-OCT-2004 (DSB):
*        Original version.
*-
*/

/* Include files. */
/* ============== */
/* Interface definitions. */
/* ---------------------- */
#include "region.h"              /* Coordinate regions (parent class) */

#if defined(astCLASS)            /* Protected */
#include "channel.h"             /* I/O channels */
#endif

/* C header files. */
/* --------------- */
#if defined(astCLASS)            /* Protected */
#include <stddef.h>
#endif

/* Type Definitions. */
/* ================= */
/* NullRegion structure. */
/* ------------------ */
/* This structure contains all information that is unique to each object in
   the class (e.g. its instance variables). */
typedef struct AstNullRegion {

/* Attributes inherited from the parent class. */
   AstRegion region;             /* Parent class structure */

} AstNullRegion;

/* Virtual function table. */
/* ----------------------- */
/* This table contains all information that is the same for all
   objects in the class (e.g. pointers to its virtual functions). */
#if defined(astCLASS)            /* Protected */
typedef struct AstNullRegionVtab {

/* Properties (e.g. methods) inherited from the parent class. */
   AstRegionVtab region_vtab;    /* Parent class virtual function table */

/* Unique flag value to determine class membership. */
   int *check;                   /* Check value */

/* Properties (e.g. methods) specific to this class. */
} AstNullRegionVtab;
#endif

/* Function prototypes. */
/* ==================== */
/* Prototypes for standard class functions. */
/* ---------------------------------------- */
astPROTO_CHECK(NullRegion)          /* Check class membership */
astPROTO_ISA(NullRegion)            /* Test class membership */

/* Constructor. */
#if defined(astCLASS)            /* Protected. */
AstNullRegion *astNullRegion_( void *, const char *, ... );
#else
AstNullRegion *astNullRegionId_( void *, const char *, ... );
#endif

#if defined(astCLASS)            /* Protected */

/* Initialiser. */
AstNullRegion *astInitNullRegion_( void *, size_t, int, AstNullRegionVtab *,
                           const char *, AstFrame * );

/* Vtab initialiser. */
void astInitNullRegionVtab_( AstNullRegionVtab *, const char * );

/* Loader. */
AstNullRegion *astLoadNullRegion_( void *, size_t, AstNullRegionVtab *,
                                   const char *, AstChannel * );

#endif

/* Prototypes for member functions. */
/* -------------------------------- */

/* Function interfaces. */
/* ==================== */
/* These macros are wrap-ups for the functions defined by this class
   to make them easier to invoke (e.g. to avoid type mis-matches when
   passing pointers to objects from derived classes). */

/* Interfaces to standard class functions. */
/* --------------------------------------- */
/* Some of these functions provide validation, so we cannot use them
   to validate their own arguments. We must use a cast when passing
   object pointers (so that they can accept objects from derived
   classes). */

/* Check class membership. */
#define astCheckNullRegion(this) astINVOKE_CHECK(NullRegion,this)

/* Test class membership. */
#define astIsANullRegion(this) astINVOKE_ISA(NullRegion,this)

/* Constructor. */
#if defined(astCLASS)            /* Protected. */
#define astNullRegion astINVOKE(F,astNullRegion_)
#else
#define astNullRegion astINVOKE(F,astNullRegionId_)
#endif

#if defined(astCLASS)            /* Protected */

/* Initialiser. */
#define astInitNullRegion(mem,size,init,vtab,name,frame) \
astINVOKE(O,astInitNullRegion_(mem,size,init,vtab,name,frame))

/* Vtab Initialiser. */
#define astInitNullRegionVtab(vtab,name) astINVOKE(V,astInitNullRegionVtab_(vtab,name))
/* Loader. */
#define astLoadNullRegion(mem,size,vtab,name,channel) \
astINVOKE(O,astLoadNullRegion_(mem,size,vtab,name,astCheckChannel(channel)))
#endif

/* Interfaces to public member functions. */
/* -------------------------------------- */
/* Here we make use of astCheckNullRegion to validate NullRegion pointers
   before use.  This provides a contextual error report if a pointer
   to the wrong sort of Object is supplied. */

#if defined(astCLASS)            /* Protected */
#endif
#endif
