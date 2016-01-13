

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */


/*****************************************************************************/
/* stdarg.h   v7.3.4                                                         */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/



   typedef char *va_list;


/*****************************************************************************/
/* VA_END - Reclaim resources used by varargs handling.                      */
/*                                                                           */
/* No action needed                                                          */
/*****************************************************************************/


/*****************************************************************************/
/* VA_START - Set up the va_list pointer.				     */
/*****************************************************************************/



/*---------------------------------------------------------------------------*/
/* ELF ABI convention:							     */
/* - va_list pointer points one byte beyond the last argument.		     */
/*---------------------------------------------------------------------------*/



/*****************************************************************************/
/* VA_ARG - Return the next argument, adjust va_list pointer		     */
/*                                                                           */
/* Some arguments passed by value are turned into pass-by-reference by	     */
/* making a temporary object and passing a pointer to this temporary.  For   */
/* such an argument (indicated by __va_argref(_type)) the actual argument    */
/* passed is a pointer, so it must be dealt with specially.		     */
/*                                                                           */
/* When an argument is larger than the maximum alignment (8 bytes for double */
/* or long long), we only align to 8 bytes.				     */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* What happens on every va_arg(_ap, _type) call is:			     */
/* 1) Align the value of _ap (the va_list pointer) appropriately for _type   */
/*    (the requested type).						     */
/* 2) Increment _ap appropriately for _type.				     */
/* 3) Return the value desired by dereferencing _ap.			     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* 1) Align _ap to satisfy alignment of _type.				     */
/* 2) Increment _ap by sizeof(_type)                                         */
/* 3) return *(ap-sizeof(_type))                                             */
/*---------------------------------------------------------------------------*/







/*---------------------------------------------------------------------------*/
/* The big- and little-endian variants are different only because we are     */
/* trying to support the case of the user asking for "char" or "short",	     */
/* which is actually undefined behavior (See ISO/IEC 9899:1999 7.15.1.1),    */
/* but we are trying to be friendly.					     */
/*---------------------------------------------------------------------------*/







/*****************************************************************************/
/* stddef.h   v7.3.4                                                         */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/




typedef int ptrdiff_t;

typedef unsigned size_t;


typedef unsigned short wchar_t;






/*-----------------------------------------------------------------------*/
/* Define _win_t, for compiling GCC libraries with the TI compiler.      */
/* GCC's library (newlib) expects wint_t to be defined here, in stddef.h,*/
/* which is arguably incorrect, but we go along for compatibility.       */
/* This is outside the _STDDEF guard in case this file has already       */
/* been included without __need_wint_t.                                  */
/*-----------------------------------------------------------------------*/

/* macros to simplify "stringification" and computed includes */

/* TitleCase standard types */


typedef char            xdc_Char;
typedef unsigned char   xdc_UChar;
typedef short           xdc_Short;
typedef unsigned short  xdc_UShort;
typedef int             xdc_Int;
typedef unsigned int    xdc_UInt;
typedef long            xdc_Long;
typedef unsigned long   xdc_ULong;
typedef float           xdc_Float;
typedef double          xdc_Double;
typedef long double     xdc_LDouble;
typedef size_t          xdc_SizeT;
typedef va_list         xdc_VaList;

/* Generic Extended Types */

typedef unsigned short  xdc_Bool;       /* boolean flag */
typedef void            *xdc_Ptr;       /* data pointer */
typedef char            *xdc_String;    /* null terminated string */

/* we intentionally omit arguments from Fxn to indicate that it can have
 * any (or none).  Unfortunately this causes gcc to emit warnings when
 * -Wstrict-prototypes is used.  Newer gcc's (4.6 or later) support a pragma
 * that works around this:
 *
 *    #pragma GCC diagnostic ignored "-Wstrict-prototypes"
 */
    typedef int             (*xdc_Fxn)();   /* function pointer */

/*
 * Import the target-specific std.h
 */
/* if the user did not supply the required xdc_target* definitions, ask well
 * known compiler tool chains to select based on their pre-defined macros
 */
/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== select.h ========
 *  This header selects an appropriate target name based on TI compiler
 *  predefined macros and includes the appropriate target-specific std.h.
 *
 *  This header is entirely optional: the user can directly select any
 *  existing target by adding definition of the following two symbols to
 *  the compile line:
 *    xdc_target_name__     the short name of the target; e.g., C64P
 *    xdc_target_types__    a package path relative path to the types header
 *                          for the target; e.g., ti/targets/std.h
 *
 *  For more information about these symbols see:
 *  http://rtsc.eclipse.org/docs-tip/Integrating_RTSC_Modules
 */

/*
 *  ======== MSP430 ========
 */
     /* set to 1 if compiling for EABI (ELF) and is set to 0 otherwise. */

/*
 *  ======== ARP32 ========
 *  ARP32 (EVE) devices
 */

/*
 *  ======== include the selected type header ========
 */
/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
/*
 *  ======== ti/targets/elf/std.h ========
 *  Standard types for supported TI compilers for ELF
 */


/*  Define target-specific "portable" macros
 *
 *  The build command-line define xdc_target_name__ to be the value
 *  of the target's name config parameter.  We use this to include the
 *  target-specific definitions for the required target-independent
 *  xdc_target* macros.
 */
/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== C66.h ========
 *  DO NOT MODIFY: This header is generated from stddef.xdt
 *
 *  This header contains target-specific definitions of target-independent
 *  macros required by the ITarget interface.  These definitions allow C/C++
 *  sources to portably compile for multiple targets (using #ifdef ...).
 */

/*
 *  ======== ti_targets_elf_C66 ========
 *  This macro identifies the specific target being used.  This macro should
 *  probably be avoided in portable sources.
 */

/*
 *  ======== xdc_target__isaCompatible_* macros ========
 *  The following definitions enable clients to conditionally compile for any
 *  compatible subset of the actual target ISA.
 */

/*
 *  ======== xdc_target__isa_66 ========
 *  This macro identifies the specific target ISA for which we are being
 *  compiled.
 */

/*
 *  ======== xdc_target__{big|little}Endian ========
 *  The following macro enables clients to portably compile for big or little
 *  endian targets.
 */

/*
 *  ======== xdc_target__os_undefined ========
 *  The following macro enables clients to portably compile for target specific
 *  OS; e.g., Linux, Solaris, Windows, undefined.
 */

/*
 *  ======== xdc_target__sizeof_ ========
 *  The following macros enable clients to portably determine type sizes
 *  within #ifdef blocks; sizeof() can't be used and the definitions in
 *  stdint.h are not available to C++ clients (unless the special macro
 *  __STDC_LIMIT_MACROS is defined).
 */

/*
 *  ======== xdc_target__alignof_ ========
 *  The following macros enable clients to portably determine type alignment
 *  within #ifdef blocks; even if provided by the compiler, alignof() can't
 *  be used in pre-processor statements.
 */

/*
 *  ======== xdc_target__bitsPerChar ========
 *  The number of bits in a char.  This macro allow one to determine the
 *  precise number of bits in any of the standard types (whose sizes are
 *  expressed as a number of chars).
 */

/*
 *  @(#) ti.targets.elf; 1, 0, 0,298; 4-27-2012 17:07:43; /db/ztree/library/trees/xdctargets/xdctargets-f21x/src/ xlibrary

 */


/* "inherit" (i.e., include) all ti.targets standard types */
/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
/*
 *  ======== ti/targets/std.h ========
 *  Standard types for supported TI compilers
 *
 */


/* include target-specific "portable" macros */

/*****************************************************************************/
/* STDINT.H v7.3.4                                                           */
/*                                                                           */
/* Copyright (c) 2002-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/* 7.18.1.1 Exact-width integer types */

    typedef   signed char   int8_t;
    typedef unsigned char  uint8_t;
    typedef          short  int16_t;
    typedef unsigned short uint16_t;
    typedef          int    int32_t;
    typedef unsigned int   uint32_t;

    typedef          __int40_t  int40_t;
    typedef unsigned __int40_t uint40_t;

    typedef          long long  int64_t;
    typedef unsigned long long uint64_t;

/* 7.18.1.2 Minimum-width integer types */

    typedef  int8_t   int_least8_t;
    typedef uint8_t  uint_least8_t;

    typedef  int16_t  int_least16_t;
    typedef uint16_t uint_least16_t;
    typedef  int32_t  int_least32_t;
    typedef uint32_t uint_least32_t;

    typedef  int40_t  int_least40_t;
    typedef uint40_t uint_least40_t;

    typedef  int64_t  int_least64_t;
    typedef uint64_t uint_least64_t;

/* 7.18.1.3 Fastest minimum-width integer types */

    typedef  int32_t  int_fast8_t;
    typedef uint32_t uint_fast8_t;
    typedef  int32_t  int_fast16_t;
    typedef uint32_t uint_fast16_t;

    typedef  int32_t  int_fast32_t;
    typedef uint32_t uint_fast32_t;

    typedef  int40_t  int_fast40_t;
    typedef uint40_t uint_fast40_t;

    typedef  int64_t  int_fast64_t;
    typedef uint64_t uint_fast64_t;

/* 7.18.1.4 Integer types capable of holding object pointers */
    typedef          int intptr_t;
    typedef unsigned int uintptr_t;

/* 7.18.1.5 Greatest-width integer types */
    typedef          long long intmax_t;
    typedef unsigned long long uintmax_t;

/* 
   According to footnotes in the 1999 C standard, "C++ implementations
   should define these macros only when __STDC_LIMIT_MACROS is defined
   before <stdint.h> is included." 
*/

/* 7.18.2 Limits of specified width integer types */
















/* 7.18.3 Limits of other integer types */







/* 7.18.4.1 Macros for minimum-width integer constants */

/*
   There is a defect report filed against the C99 standard concerning how 
   the (U)INTN_C macros should be implemented.  Please refer to --
   http://wwwold.dkuug.dk/JTC1/SC22/WG14/www/docs/dr_209.htm 
   for more information.  These macros are implemented according to the
   suggestion given at this web site.
*/




/* 7.18.4.2 Macros for greatest-width integer constants */




        typedef int xdc_Arg;    /* deprecated, but compatible with BIOS 5.x */

/*
 * xdc__LONGLONG__ indicates if compiler supports 'long long' type
 * xdc__BITS<n> __ indicates if compiler supports 'uint<n>_t' type
 */



/*
 *  ======== [U]Int<n> ========
 */
typedef int_least8_t    xdc_Int8;
typedef uint_least8_t   xdc_UInt8;
typedef int_least16_t   xdc_Int16;
typedef uint_least16_t  xdc_UInt16;
typedef int_least32_t   xdc_Int32;
typedef uint_least32_t  xdc_UInt32;

    typedef int_least64_t   xdc_Int64;
    typedef uint_least64_t   xdc_UInt64;

    typedef int_least40_t   xdc_Int40;
    typedef uint_least40_t  xdc_UInt40;

  /*  the following unqualified names are here because 40-bit types are not
   *  supported by xdc/std.h
   */
    typedef xdc_Int40       Int40;
    typedef xdc_UInt40      UInt40;

/*
 *  ======== Bits<n> ========
 */
    typedef uint8_t     xdc_Bits8;
    typedef uint16_t    xdc_Bits16;
    typedef uint32_t    xdc_Bits32;
    typedef uint64_t    xdc_Bits64;

/*
 *  ======== [UI]Arg ========
 */
typedef intptr_t        xdc_IArg;
typedef uintptr_t       xdc_UArg;

/*
 *  ======== restrict ========
 */


/*
 *  ======== ti_targets_mkPragma ========
 */

/*
 *  ======== xdc__META ========
 */

/*
 *  ======== __ti__ ========
 *  These symbols are used by RTSC tools to indicate presence/absence of
 *  assorted #pragma options in TI compiler.
 */


/*
 *  @(#) ti.targets; 1, 0, 3,531; 4-27-2012 17:07:38; /db/ztree/library/trees/xdctargets/xdctargets-f21x/src/ xlibrary

 */


/*
 *  @(#) ti.targets.elf; 1, 0, 0,298; 4-27-2012 17:07:43; /db/ztree/library/trees/xdctargets/xdctargets-f21x/src/ xlibrary

 */


/*
 *  @(#) ti.targets; 1, 0, 3,531; 4-27-2012 17:07:38; /db/ztree/library/trees/xdctargets/xdctargets-f21x/src/ xlibrary

 */


/* Each modules' internal header file defines 'module' as 
 * xdc__MODOBJADDR__(Module__state__V), where Module__state__V is the actual
 * object where the module state is kept. For most targets, the default macro
 * given here results in the construct '(&Module__state__V)->field', when the
 * expression 'module->field' is used. Compilers then generate the code that
 * doesn't dereference a pointer, but puts the address of the field in the
 * code.
 * The targets that need to do something different can define
 * xdc__MODOBJADDR__ in std.h for their target package.
 */

/* Long Long Types */

typedef long long               xdc_LLong;
typedef unsigned long long      xdc_ULLong;


/* Arg to Ptr and Fxn conversion operators
 *
 * Individual targets may override these definitions in the event
 * that compilers issue warnings about shortening of an Arg to a pointer,
 * for example.
 */
static inline xdc_Ptr xdc_iargToPtr(xdc_IArg a) { return ((xdc_Ptr)a); }
static inline xdc_Ptr xdc_uargToPtr(xdc_UArg a) { return ((xdc_Ptr)a); }

static inline xdc_Fxn xdc_iargToFxn(xdc_IArg a) { return ((xdc_Fxn)a); }
static inline xdc_Fxn xdc_uargToFxn(xdc_UArg a) { return ((xdc_Fxn)a); }

/*
 * functions to convert a single precision float to an arg
 * Here assumption is that sizeof(Float) <= sizeof(IArg);
 */
typedef union xdc_FloatData {
    xdc_Float f;
    xdc_IArg  a;
} xdc_FloatData;

static inline xdc_IArg xdc_floatToArg(xdc_Float f)
{
     xdc_FloatData u;
     u.f = f;

     return (u.a);
}

static inline xdc_Float xdc_argToFloat(xdc_IArg a)
{
     xdc_FloatData u;
     u.a = a;

     return (u.f);
}

/* restrict keyword */

/* Unprefixed Aliases */




typedef xdc_Char        Char;
typedef xdc_UChar       UChar;
typedef xdc_Short       Short;
typedef xdc_UShort      UShort;
typedef xdc_Int         Int;
typedef xdc_UInt        UInt;
typedef xdc_Long        Long;
typedef xdc_ULong       ULong;
typedef xdc_LLong       LLong;
typedef xdc_ULLong      ULLong;
typedef xdc_Float       Float;
typedef xdc_Double      Double;
typedef xdc_LDouble     LDouble;
typedef xdc_SizeT       SizeT;
typedef xdc_VaList      VaList;

typedef xdc_IArg        IArg;
typedef xdc_UArg        UArg;
typedef xdc_Bool        Bool;
typedef xdc_Int8        Int8;
typedef xdc_Int16       Int16;
typedef xdc_Int32       Int32;
typedef xdc_Fxn         Fxn;
typedef xdc_Ptr         Ptr;
typedef xdc_String      String;

typedef xdc_UInt8       UInt8;
typedef xdc_UInt16      UInt16;
typedef xdc_UInt32      UInt32;

/* DEPRECATED Aliases */

/* xdc_Arg is defined only in ti/targets/std.h; use IArg and UArg instead */
typedef xdc_Arg         Arg;

typedef xdc_UInt8       Uint8;
typedef xdc_UInt16      Uint16;
typedef xdc_UInt32      Uint32;
typedef xdc_UInt        Uns;

/*
 *  ======== optional types ========
 *  The following types are not always defined for all targets
 */
typedef xdc_Int64       Int64;
typedef xdc_UInt64      UInt64;

/* The following exact size types are not required by C99 and may not be
 * supported by some compiler/processor environments.  For greater
 * portability, use the IntN or UIntN types above.
 */
typedef xdc_Bits8       Bits8;

typedef xdc_Bits16      Bits16;

typedef xdc_Bits32      Bits32;

typedef xdc_Bits64      Bits64;


/* Standard Constants */

/* NULL must be 0 for C++ and is set to 0 in C to allow legacy code to
 * compile without warnings.
 *
 * If xdc_strict is defined, NULL is defined to be a pointer to allow
 * maximal type checking in "modern" C sources
 */



/* Declaration Qualifiers */


/*
 *  ======== xdc__CODESECT ========
 *  Code-Section Directive
 *
 *  Targets can optionally #define xdc__CODESECT in their specific
 *  std.h files.  This directive is placed in front of all
 *  "extern" function declarations, and specifies a section-name in
 *  which to place this function.  This approach
 *  provides more control on combining/organizing groups of
 *  related functions into a single named sub-section (e.g.,
 *  "init-code")  If this macro is not defined by the target, an
 *  empty definition is used instead.
 */ 

/*
 *  ======== xdc__META ========
 *  Embed unreferenced string in the current file
 *
 *  Strings emebdded via xdc__META can be placed in a section that is
 *  _not_ loaded on the target but are, nevertheless, part of the
 *  executable and available to loaders.
 *
 *  Different targets may define this macro in a way that places these
 *  strings in an output section that is not loaded (and therefore does
 *  not takeup space on the target).  Unless the target provides a
 *  definition of xdc__META, the definition below simply defines
 *  as string constant in the current file.
 */

/*
 *  @(#) xdc; 1, 1, 1,380; 4-27-2012 14:30:08; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*****************************************************************************/
/* STDIO.H v7.3.4                                                            */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* linkage.h   v7.3.4                                                        */
/*                                                                           */
/* Copyright (c) 1998-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Define _CODE_ACCESS ==> how to call RTS functions                        */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Define _DATA_ACCESS ==> how to access RTS global or static data          */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Define _DATA_ACCESS_NEAR ==> some C6000 RTS data must always be near     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Define _IDECL ==> how inline functions are declared                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* If compiling with non-TI compiler (e.g. GCC), nullify any TI-specific    */
/* language extensions.                                                     */
/*--------------------------------------------------------------------------*/

/*****************************************************************************/
/* stdarg.h   v7.3.4                                                         */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/




/*---------------------------------------------------------------------------*/
/* Attributes are only available in relaxed ANSI mode.                       */
/*---------------------------------------------------------------------------*/



/****************************************************************************/
/* TYPES THAT ANSI REQUIRES TO BE DEFINED                                   */
/****************************************************************************/

typedef struct {
      int fd;                    /* File descriptor */
      unsigned char* buf;        /* Pointer to start of buffer */
      unsigned char* pos;        /* Position in buffer */
      unsigned char* bufend;     /* Pointer to end of buffer */
      unsigned char* buff_stop;  /* Pointer to last read char in buffer */
      unsigned int   flags;      /* File status flags (see below) */
} FILE;

typedef int fpos_t; 

/****************************************************************************/
/* DEVICE AND STREAM RELATED MACROS                                         */
/****************************************************************************/
/****************************************************************************/
/* MACROS THAT DEFINE AND USE FILE STATUS FLAGS                             */
/****************************************************************************/



/****************************************************************************/
/* MACROS THAT ANSI REQUIRES TO BE DEFINED                                  */
/****************************************************************************/









/******** END OF ANSI MACROS ************************************************/


/****************************************************************************/
/* DEVICE AND STREAM RELATED DATA STRUCTURES AND MACROS                     */
/****************************************************************************/

extern far FILE _ftable[20];
extern far char _tmpnams[20][16];

/****************************************************************************/
/*   FUNCTION DEFINITIONS  - ANSI                                           */
/****************************************************************************/
/****************************************************************************/
/* OPERATIONS ON FILES                                                      */
/****************************************************************************/
extern  int     remove(const char *_file);
extern  int     rename(const char *_old, const char *_new);
extern  FILE   *tmpfile(void);
extern  char   *tmpnam(char *_s);

/****************************************************************************/
/* FILE ACCESS FUNCTIONS                                                    */
/****************************************************************************/
extern  int     fclose(FILE *_fp); 
extern  FILE   *fopen(const char *_fname, const char *_mode);
extern  FILE   *freopen(const char *_fname, const char *_mode,
			            register FILE *_fp);
extern  void    setbuf(register FILE *_fp, char *_buf);
extern  int     setvbuf(register FILE *_fp, register char *_buf, 
			            register int _type, register size_t _size);
extern  int     fflush(register FILE *_fp); 

/****************************************************************************/
/* FORMATTED INPUT/OUTPUT FUNCTIONS                                         */
/****************************************************************************/
extern  int fprintf(FILE *_fp, const char *_format, ...)
               __attribute__((__format__ (__printf__, 2, 3)));
extern  int fscanf(FILE *_fp, const char *_fmt, ...)
               __attribute__((__format__ (__scanf__, 2, 3)));
extern  int printf(const char *_format, ...)
               __attribute__((__format__ (__printf__, 1, 2)));
extern  int scanf(const char *_fmt, ...)
               __attribute__((__format__ (__scanf__, 1, 2)));
extern  int sprintf(char *_string, const char *_format, ...)
               __attribute__((__format__ (__printf__, 2, 3)));
extern  int snprintf(char *_string, size_t _n, 
				 const char *_format, ...)
               __attribute__((__format__ (__printf__, 3, 4)));
extern  int sscanf(const char *_str, const char *_fmt, ...)
               __attribute__((__format__ (__scanf__, 2, 3)));
extern  int vfprintf(FILE *_fp, const char *_format, va_list _ap)
               __attribute__((__format__ (__printf__, 2, 0)));
extern  int vprintf(const char *_format, va_list _ap)
               __attribute__((__format__ (__printf__, 1, 0)));
extern  int vsprintf(char *_string, const char *_format,
				 va_list _ap)
               __attribute__((__format__ (__printf__, 2, 0)));
extern  int vsnprintf(char *_string, size_t _n, 
				  const char *_format, va_list _ap)
               __attribute__((__format__ (__printf__, 3, 0)));

/****************************************************************************/
/* CHARACTER INPUT/OUTPUT FUNCTIONS                                         */
/****************************************************************************/
extern  int     fgetc(register FILE *_fp);
extern  char   *fgets(char *_ptr, register int _size,
				  register FILE *_fp);
extern  int     fputc(int _c, register FILE *_fp);
extern  int     fputs(const char *_ptr, register FILE *_fp);
extern  int     getc(FILE *_p);
extern  int     getchar(void);
extern  char   *gets(char *_ptr); 
extern  int     putc(int _x, FILE *_fp);
extern  int     putchar(int _x);
extern  int     puts(const char *_ptr); 
extern  int     ungetc(int _c, register FILE *_fp);

/****************************************************************************/
/* DIRECT INPUT/OUTPUT FUNCTIONS                                            */
/****************************************************************************/
extern  size_t  fread(void *_ptr, size_t _size, size_t _count,
				  FILE *_fp);
extern  size_t  fwrite(const void *_ptr, size_t _size,
				   size_t _count, register FILE *_fp); 

/****************************************************************************/
/* FILE POSITIONING FUNCTIONS                                               */
/****************************************************************************/
extern  int     fgetpos(FILE *_fp, fpos_t *_pos);
extern  int     fseek(register FILE *_fp, long _offset,
				  int _ptrname);
extern  int     fsetpos(FILE *_fp, const fpos_t *_pos);
extern  long    ftell(FILE *_fp);
extern  void    rewind(register FILE *_fp); 

/****************************************************************************/
/* ERROR-HANDLING FUNCTIONS                                                 */
/****************************************************************************/
extern  void    clearerr(FILE *_fp);
extern  int     feof(FILE *_fp);
extern  int     ferror(FILE *_fp);
extern  void    perror(const char *_s);








/************************************************************************
 * File:
 *      $RCSfile: dcs_types.h,v $
 *      $Revision: 1.5 $
 *      $Date: 2010/04/04 02:35:35 $
 *
 *      (c) 2006 DelCom Systems, Inc.
 *      The Source Code contained herein is DelCom
 *      Systems, Inc. Confidential material and subject to Non-Disclosure.
 *
 *      The Source Code is and shall remain owned by DelCom
 *      Systems, Inc. and/or its suppliers and is protected by United
 *      States copyright laws and international treaty provisions.  As an
 *      express condition of the executed Source License Agreement, title
 *      to, ownership of, and all rights in patents, copyrights, trade
 *      secrets and any other intellectual property rights in this Source
 *      Code and/or any copy or part thereof is and shall remain in DelCom
 *      Systems, Inc. and/or its suppliers.  It is understood
 *      by the user of the Source Code that valuable, confidential
 *      information and trade secrets are contained within and that
 *      unauthorized use and/or copying shall be harmful to DelCom
 *      Systems, Inc.
 *
 *      THE SOURCE CODE MAY NOT BE MODIFIED, ADAPTED, TRANSLATED, RENTED,
 *      LEASED, LOANED, RESOLD FOR PROFIT, DISTRIBUTED OR OTHERWISE ASSIGNED
 *      OR TRANSFERRED NOR MAY DERIVITATIVE WORKS BASED UPON THIS SOFTWARE
 *      OR ANY PART THEREOF BE DEVELOPED WITHOUT WRITTEN AGREEMENT BY DELCOM
 *      SYSTEMS, INC. 
 *
 *
 *
 ************************************************************************/
/************************************************************************
 * File:
 *      $RCSfile: dcs_types.h,v $
 *      $Revision: 1.5 $
 *      $Date: 2010/04/04 02:35:35 $
 *
 * Purpose:
 *      This file contains the type definitions for the global types
 *      used to specify types that require certain bit widths, such
 *      as INT16, UINT16, etc...
 *
 * Operation:
 *      
 * Notes/Issues:
 *      hye: add types used for receiver performance simulation
 *       
 ************************************************************************/

typedef unsigned short UINT16;
typedef unsigned int   UINT32;
typedef short INT16;
typedef short Flag;
typedef short FLAG;
typedef int INT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef long INT40;
typedef unsigned long UINT40;
typedef          char  INT8;    /* 8 bit wide signed quantities */ 
typedef unsigned char  UINT8;   /* 8 bit wide unsigned quantities */
typedef unsigned char  BIT_TYPE;/* 1 bit per element 0 or 1 only */
typedef unsigned char  OCTET;   /* 8 bits per element */
typedef unsigned char  SCRATCH; /* Scratch buffer pointer type */






typedef struct complex16 {      /* 16 bit precision complex quantities */
  INT16 r; 
  INT16 i;
} COMPLEX16;


#pragma STRUCT_ALIGN (complex16, 4);

typedef struct complex32 {      /* 32 bit precision complex quantities */
  INT32 r;
  INT32 i;
} COMPLEX32;
#pragma STRUCT_ALIGN (complex32, 8);

/* Define complex floating point data structure */
typedef struct 
{
  float re;
  float im;
} complex_flt;

/*  Define complex double precision floating point data structure */
typedef struct
{
  double re;
  double im;
} complex_double;








//typedef	signed char		INT8;
//typedef	signed short	INT16;
//typedef signed int		INT32;
//typedef signed long long int	INT64;

//typedef	unsigned char	UINT8;
//typedef	unsigned short	UINT16;
//typedef unsigned int	UINT32;
//typedef unsigned long long int	UINT64;
//### typedef modification for 6678(previously these defined in dcs_types.h, now we are excluding that file)
//typedef Int16 INT16;
//typedef Int8 INT8;
//typedef UInt16 UINT16;
//typedef UInt8 UINT8;

//#########################
typedef INT8	BOOL;
//typedef Int8	BOOL;  // remesh

typedef signed char CHAR;
//typedef Char CHAR;

typedef enum DSP_CORE
{
	CORE_0 = 0,
	CORE_1,
	CORE_2,
	CORE_3,
	CORE_4,
	CORE_5,
	CORE_6,
	CORE_7,
	MAX_CORE,
	INVALID_CORE = 0xFF

}DSP_CORE;




//#define	TRUE	(BOOL)1
//#define FALSE	(BOOL)0




/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 * ======== xdc.h ========
 *  All generated public module headers include this file
 */


/*
 *  ======== __CONC__ ========
 *  Concatenate the specified tokens to create a new single token
 */

/*
 *  ======== __STR__ ========
 *  Stringify the specified arguement
 */

/*
 *  ======== xdc_FILE__ ========
 *  Alternative to __FILE__ which defaults to NULL
 *
 *  We define our own symbol in lieu of the standard __FILE__
 *  so we can avoid embedding lots of static strings in applications
 *  that use Error and Assert.
 *
 *  Both Error and Assert use xdc_FILE__ and ALL module internal headers
 *  redefine xdc_FILE__ to be NULL, unless xdc_FILE is defined.  If xdc_FILE
 *  is defined, xdc-FILE__ has the same value assigned to xdc_FILE.  So, by
 *  default, Error and Asserts in modules do *not* provide a file name.
 *
 *  Since this header in included in all module public headers, "non-module"
 *  clients of Error and Assert *will*, by default, provide a file name
 *  string.  To eliminate these embedded strings, add the following line
 *  before all module headers:
 *      #define xdc_FILE    NULL
 *
 *  Module creators may opt to define xdc_FILE as the string to use in
 *  Error and Assert messages.  For example, adding the following line
 *  to a module's implementation (before the inclusion of the module's
 *  internal header) will cause the standard __FILE__ to be
 *  used in lieu of NULL in Error and Assert calls:
 *      #define xdc_FILE    __FILE__
 *
 */

/*
 *  ======== xdc_LINE ========
 *  Standard file-line-number string for identifying a call site
 */







/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== Types__prologue.h ========
 *  Hand crafted definitions for Types.xdc
 */
/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */



/*
 * ======== interface xdc.runtime.IModule ========
 */

typedef struct xdc_runtime_IModule_Fxns__ xdc_runtime_IModule_Fxns__;
typedef const xdc_runtime_IModule_Fxns__* xdc_runtime_IModule_Module;

/*
 * ======== module xdc.runtime.Assert ========
 */


/*
 * ======== module xdc.runtime.Core ========
 */

typedef struct xdc_runtime_Core_ObjDesc xdc_runtime_Core_ObjDesc;

/*
 * ======== module xdc.runtime.Defaults ========
 */


/*
 * ======== module xdc.runtime.Diags ========
 */

typedef struct xdc_runtime_Diags_DictElem xdc_runtime_Diags_DictElem;

/*
 * ======== module xdc.runtime.Error ========
 */

typedef struct xdc_runtime_Error_Data xdc_runtime_Error_Data;
typedef struct xdc_runtime_Error_Block xdc_runtime_Error_Block;
typedef struct xdc_runtime_Error_Module_State xdc_runtime_Error_Module_State;

/*
 * ======== module xdc.runtime.Gate ========
 */


/*
 * ======== interface xdc.runtime.IGateProvider ========
 */

typedef struct xdc_runtime_IGateProvider_Fxns__ xdc_runtime_IGateProvider_Fxns__;
typedef const xdc_runtime_IGateProvider_Fxns__* xdc_runtime_IGateProvider_Module;
typedef struct xdc_runtime_IGateProvider_Params xdc_runtime_IGateProvider_Params;
typedef struct xdc_runtime_IGateProvider___Object { xdc_runtime_IGateProvider_Fxns__* __fxns; xdc_Bits32 __label; } *xdc_runtime_IGateProvider_Handle;

/*
 * ======== module xdc.runtime.GateNull ========
 */

typedef struct xdc_runtime_GateNull_Fxns__ xdc_runtime_GateNull_Fxns__;
typedef const xdc_runtime_GateNull_Fxns__* xdc_runtime_GateNull_Module;
typedef struct xdc_runtime_GateNull_Params xdc_runtime_GateNull_Params;
typedef struct xdc_runtime_GateNull_Object xdc_runtime_GateNull_Object;
typedef struct xdc_runtime_GateNull_Struct xdc_runtime_GateNull_Struct;
typedef xdc_runtime_GateNull_Object* xdc_runtime_GateNull_Handle;
typedef struct xdc_runtime_GateNull_Object__ xdc_runtime_GateNull_Instance_State;
typedef xdc_runtime_GateNull_Object* xdc_runtime_GateNull_Instance;

/*
 * ======== module xdc.runtime.Log ========
 */

typedef struct xdc_runtime_Log_EventRec xdc_runtime_Log_EventRec;

/*
 * ======== interface xdc.runtime.ILogger ========
 */

typedef struct xdc_runtime_ILogger_Fxns__ xdc_runtime_ILogger_Fxns__;
typedef const xdc_runtime_ILogger_Fxns__* xdc_runtime_ILogger_Module;
typedef struct xdc_runtime_ILogger_Params xdc_runtime_ILogger_Params;
typedef struct xdc_runtime_ILogger___Object { xdc_runtime_ILogger_Fxns__* __fxns; xdc_Bits32 __label; } *xdc_runtime_ILogger_Handle;

/*
 * ======== interface xdc.runtime.IFilterLogger ========
 */

typedef struct xdc_runtime_IFilterLogger_Fxns__ xdc_runtime_IFilterLogger_Fxns__;
typedef const xdc_runtime_IFilterLogger_Fxns__* xdc_runtime_IFilterLogger_Module;
typedef struct xdc_runtime_IFilterLogger_Params xdc_runtime_IFilterLogger_Params;
typedef struct xdc_runtime_IFilterLogger___Object { xdc_runtime_IFilterLogger_Fxns__* __fxns; xdc_Bits32 __label; } *xdc_runtime_IFilterLogger_Handle;

/*
 * ======== module xdc.runtime.LoggerBuf ========
 */

typedef struct xdc_runtime_LoggerBuf_Entry xdc_runtime_LoggerBuf_Entry;
typedef struct xdc_runtime_LoggerBuf_Module_State xdc_runtime_LoggerBuf_Module_State;
typedef struct xdc_runtime_LoggerBuf_Fxns__ xdc_runtime_LoggerBuf_Fxns__;
typedef const xdc_runtime_LoggerBuf_Fxns__* xdc_runtime_LoggerBuf_Module;
typedef struct xdc_runtime_LoggerBuf_Params xdc_runtime_LoggerBuf_Params;
typedef struct xdc_runtime_LoggerBuf_Object xdc_runtime_LoggerBuf_Object;
typedef struct xdc_runtime_LoggerBuf_Struct xdc_runtime_LoggerBuf_Struct;
typedef xdc_runtime_LoggerBuf_Object* xdc_runtime_LoggerBuf_Handle;
typedef struct xdc_runtime_LoggerBuf_Object__ xdc_runtime_LoggerBuf_Instance_State;
typedef xdc_runtime_LoggerBuf_Object* xdc_runtime_LoggerBuf_Instance;

/*
 * ======== module xdc.runtime.LoggerSys ========
 */

typedef struct xdc_runtime_LoggerSys_Fxns__ xdc_runtime_LoggerSys_Fxns__;
typedef const xdc_runtime_LoggerSys_Fxns__* xdc_runtime_LoggerSys_Module;
typedef struct xdc_runtime_LoggerSys_Params xdc_runtime_LoggerSys_Params;
typedef struct xdc_runtime_LoggerSys_Object xdc_runtime_LoggerSys_Object;
typedef struct xdc_runtime_LoggerSys_Struct xdc_runtime_LoggerSys_Struct;
typedef xdc_runtime_LoggerSys_Object* xdc_runtime_LoggerSys_Handle;
typedef struct xdc_runtime_LoggerSys_Object__ xdc_runtime_LoggerSys_Instance_State;
typedef xdc_runtime_LoggerSys_Object* xdc_runtime_LoggerSys_Instance;

/*
 * ======== module xdc.runtime.Main ========
 */


/*
 * ======== module xdc.runtime.Memory ========
 */

typedef struct xdc_runtime_Memory_Stats xdc_runtime_Memory_Stats;
typedef struct xdc_runtime_Memory_Module_State xdc_runtime_Memory_Module_State;

/*
 * ======== interface xdc.runtime.IHeap ========
 */

typedef struct xdc_runtime_IHeap_Fxns__ xdc_runtime_IHeap_Fxns__;
typedef const xdc_runtime_IHeap_Fxns__* xdc_runtime_IHeap_Module;
typedef struct xdc_runtime_IHeap_Params xdc_runtime_IHeap_Params;
typedef struct xdc_runtime_IHeap___Object { xdc_runtime_IHeap_Fxns__* __fxns; xdc_Bits32 __label; } *xdc_runtime_IHeap_Handle;

/*
 * ======== module xdc.runtime.HeapMin ========
 */

typedef struct xdc_runtime_HeapMin_Fxns__ xdc_runtime_HeapMin_Fxns__;
typedef const xdc_runtime_HeapMin_Fxns__* xdc_runtime_HeapMin_Module;
typedef struct xdc_runtime_HeapMin_Params xdc_runtime_HeapMin_Params;
typedef struct xdc_runtime_HeapMin_Object xdc_runtime_HeapMin_Object;
typedef struct xdc_runtime_HeapMin_Struct xdc_runtime_HeapMin_Struct;
typedef xdc_runtime_HeapMin_Object* xdc_runtime_HeapMin_Handle;
typedef struct xdc_runtime_HeapMin_Object__ xdc_runtime_HeapMin_Instance_State;
typedef xdc_runtime_HeapMin_Object* xdc_runtime_HeapMin_Instance;

/*
 * ======== module xdc.runtime.HeapStd ========
 */

typedef struct xdc_runtime_HeapStd_Module_State xdc_runtime_HeapStd_Module_State;
typedef struct xdc_runtime_HeapStd_Fxns__ xdc_runtime_HeapStd_Fxns__;
typedef const xdc_runtime_HeapStd_Fxns__* xdc_runtime_HeapStd_Module;
typedef struct xdc_runtime_HeapStd_Params xdc_runtime_HeapStd_Params;
typedef struct xdc_runtime_HeapStd_Object xdc_runtime_HeapStd_Object;
typedef struct xdc_runtime_HeapStd_Struct xdc_runtime_HeapStd_Struct;
typedef xdc_runtime_HeapStd_Object* xdc_runtime_HeapStd_Handle;
typedef struct xdc_runtime_HeapStd_Object__ xdc_runtime_HeapStd_Instance_State;
typedef xdc_runtime_HeapStd_Object* xdc_runtime_HeapStd_Instance;

/*
 * ======== module xdc.runtime.Registry ========
 */

typedef struct xdc_runtime_Registry_Module_State xdc_runtime_Registry_Module_State;

/*
 * ======== module xdc.runtime.Rta ========
 */

typedef struct xdc_runtime_Rta_CommandPacket xdc_runtime_Rta_CommandPacket;
typedef struct xdc_runtime_Rta_ResponsePacket xdc_runtime_Rta_ResponsePacket;

/*
 * ======== module xdc.runtime.Startup ========
 */

typedef struct xdc_runtime_Startup_Module_State xdc_runtime_Startup_Module_State;

/*
 * ======== module xdc.runtime.System ========
 */

typedef struct xdc_runtime_System_ParseData xdc_runtime_System_ParseData;
typedef struct xdc_runtime_System_Module_State xdc_runtime_System_Module_State;

/*
 * ======== interface xdc.runtime.ISystemSupport ========
 */

typedef struct xdc_runtime_ISystemSupport_Fxns__ xdc_runtime_ISystemSupport_Fxns__;
typedef const xdc_runtime_ISystemSupport_Fxns__* xdc_runtime_ISystemSupport_Module;

/*
 * ======== module xdc.runtime.SysStd ========
 */

typedef struct xdc_runtime_SysStd_Fxns__ xdc_runtime_SysStd_Fxns__;
typedef const xdc_runtime_SysStd_Fxns__* xdc_runtime_SysStd_Module;

/*
 * ======== module xdc.runtime.SysMin ========
 */

typedef struct xdc_runtime_SysMin_Module_State xdc_runtime_SysMin_Module_State;
typedef struct xdc_runtime_SysMin_Fxns__ xdc_runtime_SysMin_Fxns__;
typedef const xdc_runtime_SysMin_Fxns__* xdc_runtime_SysMin_Module;

/*
 * ======== module xdc.runtime.Text ========
 */

typedef struct xdc_runtime_Text_Node xdc_runtime_Text_Node;
typedef struct xdc_runtime_Text_MatchVisState xdc_runtime_Text_MatchVisState;
typedef struct xdc_runtime_Text_PrintVisState xdc_runtime_Text_PrintVisState;
typedef struct xdc_runtime_Text_Module_State xdc_runtime_Text_Module_State;

/*
 * ======== interface xdc.runtime.ITimestampClient ========
 */

typedef struct xdc_runtime_ITimestampClient_Fxns__ xdc_runtime_ITimestampClient_Fxns__;
typedef const xdc_runtime_ITimestampClient_Fxns__* xdc_runtime_ITimestampClient_Module;

/*
 * ======== module xdc.runtime.Timestamp ========
 */

typedef struct xdc_runtime_Timestamp_Fxns__ xdc_runtime_Timestamp_Fxns__;
typedef const xdc_runtime_Timestamp_Fxns__* xdc_runtime_Timestamp_Module;

/*
 * ======== interface xdc.runtime.ITimestampProvider ========
 */

typedef struct xdc_runtime_ITimestampProvider_Fxns__ xdc_runtime_ITimestampProvider_Fxns__;
typedef const xdc_runtime_ITimestampProvider_Fxns__* xdc_runtime_ITimestampProvider_Module;

/*
 * ======== module xdc.runtime.TimestampNull ========
 */

typedef struct xdc_runtime_TimestampNull_Fxns__ xdc_runtime_TimestampNull_Fxns__;
typedef const xdc_runtime_TimestampNull_Fxns__* xdc_runtime_TimestampNull_Module;

/*
 * ======== module xdc.runtime.TimestampStd ========
 */

typedef struct xdc_runtime_TimestampStd_Fxns__ xdc_runtime_TimestampStd_Fxns__;
typedef const xdc_runtime_TimestampStd_Fxns__* xdc_runtime_TimestampStd_Module;

/*
 * ======== module xdc.runtime.Types ========
 */

typedef struct xdc_runtime_Types_CordAddr__ xdc_runtime_Types_CordAddr__;
typedef struct xdc_runtime_Types_GateRef__ xdc_runtime_Types_GateRef__;
typedef struct xdc_runtime_Types_Label xdc_runtime_Types_Label;
typedef struct xdc_runtime_Types_Site xdc_runtime_Types_Site;
typedef struct xdc_runtime_Types_Timestamp64 xdc_runtime_Types_Timestamp64;
typedef struct xdc_runtime_Types_FreqHz xdc_runtime_Types_FreqHz;
typedef struct xdc_runtime_Types_RegDesc xdc_runtime_Types_RegDesc;
typedef struct xdc_runtime_Types_Vec xdc_runtime_Types_Vec;
typedef struct xdc_runtime_Types_Link xdc_runtime_Types_Link;
typedef struct xdc_runtime_Types_InstHdr xdc_runtime_Types_InstHdr;
typedef struct xdc_runtime_Types_PrmsHdr xdc_runtime_Types_PrmsHdr;
typedef struct xdc_runtime_Types_Base xdc_runtime_Types_Base;
typedef struct xdc_runtime_Types_SysFxns xdc_runtime_Types_SysFxns;
typedef struct xdc_runtime_Types_SysFxns2 xdc_runtime_Types_SysFxns2;

/*
 * ======== interface xdc.runtime.IInstance ========
 */

typedef struct xdc_runtime_IInstance_Fxns__ xdc_runtime_IInstance_Fxns__;
typedef const xdc_runtime_IInstance_Fxns__* xdc_runtime_IInstance_Module;
typedef struct xdc_runtime_IInstance_Params xdc_runtime_IInstance_Params;
typedef struct xdc_runtime_IInstance___Object { xdc_runtime_IInstance_Fxns__* __fxns; xdc_Bits32 __label; } *xdc_runtime_IInstance_Handle;

/*
 * ======== module xdc.runtime.LoggerBuf_TimestampProxy ========
 */

typedef struct xdc_runtime_LoggerBuf_TimestampProxy_Fxns__ xdc_runtime_LoggerBuf_TimestampProxy_Fxns__;
typedef const xdc_runtime_LoggerBuf_TimestampProxy_Fxns__* xdc_runtime_LoggerBuf_TimestampProxy_Module;

/*
 * ======== module xdc.runtime.LoggerBuf_Module_GateProxy ========
 */

typedef struct xdc_runtime_LoggerBuf_Module_GateProxy_Fxns__ xdc_runtime_LoggerBuf_Module_GateProxy_Fxns__;
typedef const xdc_runtime_LoggerBuf_Module_GateProxy_Fxns__* xdc_runtime_LoggerBuf_Module_GateProxy_Module;
typedef struct xdc_runtime_LoggerBuf_Module_GateProxy_Params xdc_runtime_LoggerBuf_Module_GateProxy_Params;
typedef struct xdc_runtime_IGateProvider___Object *xdc_runtime_LoggerBuf_Module_GateProxy_Handle;

/*
 * ======== module xdc.runtime.LoggerSys_TimestampProxy ========
 */

typedef struct xdc_runtime_LoggerSys_TimestampProxy_Fxns__ xdc_runtime_LoggerSys_TimestampProxy_Fxns__;
typedef const xdc_runtime_LoggerSys_TimestampProxy_Fxns__* xdc_runtime_LoggerSys_TimestampProxy_Module;

/*
 * ======== module xdc.runtime.Main_Module_GateProxy ========
 */

typedef struct xdc_runtime_Main_Module_GateProxy_Fxns__ xdc_runtime_Main_Module_GateProxy_Fxns__;
typedef const xdc_runtime_Main_Module_GateProxy_Fxns__* xdc_runtime_Main_Module_GateProxy_Module;
typedef struct xdc_runtime_Main_Module_GateProxy_Params xdc_runtime_Main_Module_GateProxy_Params;
typedef struct xdc_runtime_IGateProvider___Object *xdc_runtime_Main_Module_GateProxy_Handle;

/*
 * ======== module xdc.runtime.Memory_HeapProxy ========
 */

typedef struct xdc_runtime_Memory_HeapProxy_Fxns__ xdc_runtime_Memory_HeapProxy_Fxns__;
typedef const xdc_runtime_Memory_HeapProxy_Fxns__* xdc_runtime_Memory_HeapProxy_Module;
typedef struct xdc_runtime_Memory_HeapProxy_Params xdc_runtime_Memory_HeapProxy_Params;
typedef struct xdc_runtime_IHeap___Object *xdc_runtime_Memory_HeapProxy_Handle;

/*
 * ======== module xdc.runtime.System_SupportProxy ========
 */

typedef struct xdc_runtime_System_SupportProxy_Fxns__ xdc_runtime_System_SupportProxy_Fxns__;
typedef const xdc_runtime_System_SupportProxy_Fxns__* xdc_runtime_System_SupportProxy_Module;

/*
 * ======== module xdc.runtime.System_Module_GateProxy ========
 */

typedef struct xdc_runtime_System_Module_GateProxy_Fxns__ xdc_runtime_System_Module_GateProxy_Fxns__;
typedef const xdc_runtime_System_Module_GateProxy_Fxns__* xdc_runtime_System_Module_GateProxy_Module;
typedef struct xdc_runtime_System_Module_GateProxy_Params xdc_runtime_System_Module_GateProxy_Params;
typedef struct xdc_runtime_IGateProvider___Object *xdc_runtime_System_Module_GateProxy_Handle;

/*
 * ======== module xdc.runtime.Timestamp_SupportProxy ========
 */

typedef struct xdc_runtime_Timestamp_SupportProxy_Fxns__ xdc_runtime_Timestamp_SupportProxy_Fxns__;
typedef const xdc_runtime_Timestamp_SupportProxy_Fxns__* xdc_runtime_Timestamp_SupportProxy_Module;




/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ModuleId */
typedef xdc_Bits16 xdc_runtime_Types_ModuleId;

/* DiagsMask */
typedef xdc_Bits16 xdc_runtime_Types_DiagsMask;

/* Event */
typedef xdc_Bits32 xdc_runtime_Types_Event;

/* EventId */
typedef xdc_runtime_Types_Event xdc_runtime_Types_EventId;

/* CordAddr__ */
struct xdc_runtime_Types_CordAddr__;

/* CordAddr */
typedef xdc_runtime_Types_CordAddr__* xdc_runtime_Types_CordAddr;

/* GateRef__ */
struct xdc_runtime_Types_GateRef__;

/* GateRef */
typedef xdc_runtime_Types_GateRef__* xdc_runtime_Types_GateRef;

/* RopeId */
typedef xdc_Bits16 xdc_runtime_Types_RopeId;

/* CreatePolicy */
enum xdc_runtime_Types_CreatePolicy {
    xdc_runtime_Types_STATIC_POLICY,
    xdc_runtime_Types_CREATE_POLICY,
    xdc_runtime_Types_DELETE_POLICY
};
typedef enum xdc_runtime_Types_CreatePolicy xdc_runtime_Types_CreatePolicy;

/* Label */
struct xdc_runtime_Types_Label {
    xdc_Ptr handle;
    xdc_runtime_Types_ModuleId modId;
    xdc_String iname;
    xdc_Bool named;
};

/* Site */
struct xdc_runtime_Types_Site {
    xdc_runtime_Types_ModuleId mod;
    xdc_String file;
    xdc_Int line;
};

/* Timestamp64 */
struct xdc_runtime_Types_Timestamp64 {
    xdc_Bits32 hi;
    xdc_Bits32 lo;
};

/* FreqHz */
struct xdc_runtime_Types_FreqHz {
    xdc_Bits32 hi;
    xdc_Bits32 lo;
};

/* RegDesc */
struct xdc_runtime_Types_RegDesc {
    xdc_runtime_Types_RegDesc* next;
    xdc_String modName;
    xdc_runtime_Types_ModuleId id;
    xdc_runtime_Types_DiagsMask mask;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* LogEvent */
typedef xdc_Bits32 xdc_runtime_Types_LogEvent;

/* LoggerFxn0 */
typedef void (*xdc_runtime_Types_LoggerFxn0)(xdc_Ptr, xdc_runtime_Types_LogEvent, xdc_runtime_Types_ModuleId);

/* LoggerFxn1 */
typedef void (*xdc_runtime_Types_LoggerFxn1)(xdc_Ptr, xdc_runtime_Types_LogEvent, xdc_runtime_Types_ModuleId, xdc_IArg);

/* LoggerFxn2 */
typedef void (*xdc_runtime_Types_LoggerFxn2)(xdc_Ptr, xdc_runtime_Types_LogEvent, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg);

/* LoggerFxn4 */
typedef void (*xdc_runtime_Types_LoggerFxn4)(xdc_Ptr, xdc_runtime_Types_LogEvent, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);

/* LoggerFxn8 */
typedef void (*xdc_runtime_Types_LoggerFxn8)(xdc_Ptr, xdc_runtime_Types_LogEvent, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);

/* Vec */
struct xdc_runtime_Types_Vec {
    xdc_Int len;
    xdc_Ptr arr;
};

/* Link */
struct xdc_runtime_Types_Link {
    xdc_runtime_Types_Link* next;
    xdc_runtime_Types_Link* prev;
};

/* InstHdr */
struct xdc_runtime_Types_InstHdr {
    xdc_runtime_Types_Link link;
};

/* PrmsHdr */
struct xdc_runtime_Types_PrmsHdr {
    xdc_SizeT size;
    xdc_Ptr self;
    xdc_Ptr modFxns;
    xdc_Ptr instPrms;
};

/* Base */
struct xdc_runtime_Types_Base {
    xdc_runtime_Types_Base* base;
};

/* SysFxns */
struct xdc_runtime_Types_SysFxns {
    xdc_Ptr (*__create)(xdc_Ptr, xdc_SizeT, const xdc_Ptr, const xdc_Ptr, xdc_SizeT, xdc_runtime_Error_Block*);
    void (*__delete)(xdc_Ptr);
    xdc_runtime_Types_Label* (*__label)(xdc_Ptr, xdc_runtime_Types_Label*);
    xdc_runtime_Types_ModuleId __mid;
};

/* SysFxns2 */
struct xdc_runtime_Types_SysFxns2 {
    xdc_Ptr (*__create)(xdc_Ptr, xdc_SizeT, const xdc_Ptr, const xdc_UChar*, xdc_SizeT, xdc_runtime_Error_Block*);
    void (*__delete)(xdc_Ptr);
    xdc_runtime_Types_Label* (*__label)(xdc_Ptr, xdc_runtime_Types_Label*);
    xdc_runtime_Types_ModuleId __mid;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Types_Module__diagsEnabled;
extern far const CT__xdc_runtime_Types_Module__diagsEnabled xdc_runtime_Types_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Types_Module__diagsIncluded;
extern far const CT__xdc_runtime_Types_Module__diagsIncluded xdc_runtime_Types_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Types_Module__diagsMask;
extern far const CT__xdc_runtime_Types_Module__diagsMask xdc_runtime_Types_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Types_Module__gateObj;
extern far const CT__xdc_runtime_Types_Module__gateObj xdc_runtime_Types_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Types_Module__gatePrms;
extern far const CT__xdc_runtime_Types_Module__gatePrms xdc_runtime_Types_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Types_Module__id;
extern far const CT__xdc_runtime_Types_Module__id xdc_runtime_Types_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Types_Module__loggerDefined;
extern far const CT__xdc_runtime_Types_Module__loggerDefined xdc_runtime_Types_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Types_Module__loggerObj;
extern far const CT__xdc_runtime_Types_Module__loggerObj xdc_runtime_Types_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Types_Module__loggerFxn0;
extern far const CT__xdc_runtime_Types_Module__loggerFxn0 xdc_runtime_Types_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Types_Module__loggerFxn1;
extern far const CT__xdc_runtime_Types_Module__loggerFxn1 xdc_runtime_Types_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Types_Module__loggerFxn2;
extern far const CT__xdc_runtime_Types_Module__loggerFxn2 xdc_runtime_Types_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Types_Module__loggerFxn4;
extern far const CT__xdc_runtime_Types_Module__loggerFxn4 xdc_runtime_Types_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Types_Module__loggerFxn8;
extern far const CT__xdc_runtime_Types_Module__loggerFxn8 xdc_runtime_Types_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Types_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Types_Module__startupDoneFxn xdc_runtime_Types_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Types_Object__count;
extern far const CT__xdc_runtime_Types_Object__count xdc_runtime_Types_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Types_Object__heap;
extern far const CT__xdc_runtime_Types_Object__heap xdc_runtime_Types_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Types_Object__sizeof;
extern far const CT__xdc_runtime_Types_Object__sizeof xdc_runtime_Types_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Types_Object__table;
extern far const CT__xdc_runtime_Types_Object__table xdc_runtime_Types_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Types_Module__startupDone__S( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Types_Module__id xdc_runtime_Types_Module_id( void ) 
{
    return xdc_runtime_Types_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Types_Module_hasMask( void ) 
{
    return xdc_runtime_Types_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Types_Module_getMask( void ) 
{
    return xdc_runtime_Types_Module__diagsMask__C != 0 ? *xdc_runtime_Types_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Types_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Types_Module__diagsMask__C != 0) *xdc_runtime_Types_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== Types__epilogue.h ========
 *  Hand crafted macros for Types.xdc
 */

/*
 *  ======== xdc_runtime_Types_getEventId ========
 */

/*
 *  ======== xdc_runtime_Types_makeEvent ========
 */

/*
 *  ======== xdc_runtime_Types_getModuleId ========
 */
/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */





/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_IInstance_Params {
    size_t __size;
    xdc_String name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_IInstance_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base xdc_runtime_IInstance_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* delete */
static inline void xdc_runtime_IInstance_delete( xdc_runtime_IInstance_Handle* instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}

/* Handle_to_Module */
static inline xdc_runtime_IInstance_Module xdc_runtime_IInstance_Handle_to_Module( xdc_runtime_IInstance_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label* xdc_runtime_IInstance_Handle_label( xdc_runtime_IInstance_Handle inst, xdc_runtime_Types_Label* lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_IInstance_Module_id( xdc_runtime_IInstance_Module mod )
{
    return mod->__sysp->__mid;
}


/*
 * ======== FUNCTION SELECTORS ========
 */


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Memory_HeapProxy_Module__diagsEnabled;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__diagsEnabled xdc_runtime_Memory_HeapProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Memory_HeapProxy_Module__diagsIncluded;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__diagsIncluded xdc_runtime_Memory_HeapProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Memory_HeapProxy_Module__diagsMask;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__diagsMask xdc_runtime_Memory_HeapProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Memory_HeapProxy_Module__gateObj;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__gateObj xdc_runtime_Memory_HeapProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Memory_HeapProxy_Module__gatePrms;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__gatePrms xdc_runtime_Memory_HeapProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Memory_HeapProxy_Module__id;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__id xdc_runtime_Memory_HeapProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Memory_HeapProxy_Module__loggerDefined;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerDefined xdc_runtime_Memory_HeapProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Memory_HeapProxy_Module__loggerObj;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerObj xdc_runtime_Memory_HeapProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn0;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn0 xdc_runtime_Memory_HeapProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn1;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn1 xdc_runtime_Memory_HeapProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn2;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn2 xdc_runtime_Memory_HeapProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn4;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn4 xdc_runtime_Memory_HeapProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn8;
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__loggerFxn8 xdc_runtime_Memory_HeapProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Memory_HeapProxy_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Memory_HeapProxy_Module__startupDoneFxn xdc_runtime_Memory_HeapProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Memory_HeapProxy_Object__count;
extern far const CT__xdc_runtime_Memory_HeapProxy_Object__count xdc_runtime_Memory_HeapProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Memory_HeapProxy_Object__heap;
extern far const CT__xdc_runtime_Memory_HeapProxy_Object__heap xdc_runtime_Memory_HeapProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Memory_HeapProxy_Object__sizeof;
extern far const CT__xdc_runtime_Memory_HeapProxy_Object__sizeof xdc_runtime_Memory_HeapProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Memory_HeapProxy_Object__table;
extern far const CT__xdc_runtime_Memory_HeapProxy_Object__table xdc_runtime_Memory_HeapProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_Memory_HeapProxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_Memory_HeapProxy_Struct {
    const xdc_runtime_Memory_HeapProxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_Memory_HeapProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*alloc)(xdc_runtime_Memory_HeapProxy_Handle, xdc_SizeT, xdc_SizeT, xdc_runtime_Error_Block*);
    void (*free)(xdc_runtime_Memory_HeapProxy_Handle, xdc_Ptr, xdc_SizeT);
    xdc_Bool (*isBlocking)(xdc_runtime_Memory_HeapProxy_Handle);
    void (*getStats)(xdc_runtime_Memory_HeapProxy_Handle, xdc_runtime_Memory_Stats*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const xdc_runtime_Memory_HeapProxy_Fxns__ xdc_runtime_Memory_HeapProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* xdc_runtime_Memory_HeapProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Memory_HeapProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void xdc_runtime_Memory_HeapProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void xdc_runtime_Memory_HeapProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void xdc_runtime_Memory_HeapProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool xdc_runtime_Memory_HeapProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_Proxy__delegate__S( void );

/* alloc__E */

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_alloc__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );

extern xdc_Ptr xdc_runtime_Memory_HeapProxy_alloc__R( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );

/* free__E */

extern void xdc_runtime_Memory_HeapProxy_free__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_Ptr block, xdc_SizeT size );

extern void xdc_runtime_Memory_HeapProxy_free__R( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_Ptr block, xdc_SizeT size );

/* isBlocking__E */

extern xdc_Bool xdc_runtime_Memory_HeapProxy_isBlocking__E( xdc_runtime_Memory_HeapProxy_Handle __inst );

extern xdc_Bool xdc_runtime_Memory_HeapProxy_isBlocking__R( xdc_runtime_Memory_HeapProxy_Handle __inst );

/* getStats__E */

extern void xdc_runtime_Memory_HeapProxy_getStats__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_runtime_Memory_Stats* stats );

extern void xdc_runtime_Memory_HeapProxy_getStats__R( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_runtime_Memory_Stats* stats );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* alloc_{FxnT,fxnP} */
typedef xdc_Ptr (*xdc_runtime_Memory_HeapProxy_alloc_FxnT)(void*, xdc_SizeT, xdc_SizeT, xdc_runtime_Error_Block*);
static inline xdc_runtime_Memory_HeapProxy_alloc_FxnT xdc_runtime_Memory_HeapProxy_alloc_fxnP( void )
{
    return (xdc_runtime_Memory_HeapProxy_alloc_FxnT)xdc_runtime_Memory_HeapProxy_alloc__E; 
}

/* free_{FxnT,fxnP} */
typedef void (*xdc_runtime_Memory_HeapProxy_free_FxnT)(void*, xdc_Ptr, xdc_SizeT);
static inline xdc_runtime_Memory_HeapProxy_free_FxnT xdc_runtime_Memory_HeapProxy_free_fxnP( void )
{
    return (xdc_runtime_Memory_HeapProxy_free_FxnT)xdc_runtime_Memory_HeapProxy_free__E; 
}

/* isBlocking_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_Memory_HeapProxy_isBlocking_FxnT)(void*);
static inline xdc_runtime_Memory_HeapProxy_isBlocking_FxnT xdc_runtime_Memory_HeapProxy_isBlocking_fxnP( void )
{
    return (xdc_runtime_Memory_HeapProxy_isBlocking_FxnT)xdc_runtime_Memory_HeapProxy_isBlocking__E; 
}

/* getStats_{FxnT,fxnP} */
typedef void (*xdc_runtime_Memory_HeapProxy_getStats_FxnT)(void*, xdc_runtime_Memory_Stats*);
static inline xdc_runtime_Memory_HeapProxy_getStats_FxnT xdc_runtime_Memory_HeapProxy_getStats_fxnP( void )
{
    return (xdc_runtime_Memory_HeapProxy_getStats_FxnT)xdc_runtime_Memory_HeapProxy_getStats__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IHeap_Module xdc_runtime_Memory_HeapProxy_Module_upCast( void )
{
    return (xdc_runtime_IHeap_Module)xdc_runtime_Memory_HeapProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IHeap */

/* Handle_upCast */
static inline xdc_runtime_IHeap_Handle xdc_runtime_Memory_HeapProxy_Handle_upCast( xdc_runtime_Memory_HeapProxy_Handle i )
{
    return (xdc_runtime_IHeap_Handle)i;
}

/* Handle_to_xdc_runtime_IHeap */

/* Handle_downCast */
static inline xdc_runtime_Memory_HeapProxy_Handle xdc_runtime_Memory_HeapProxy_Handle_downCast( xdc_runtime_IHeap_Handle i )
{
    xdc_runtime_IHeap_Handle i2 = (xdc_runtime_IHeap_Handle)i;
if (xdc_runtime_Memory_HeapProxy_Proxy__abstract__S()) return (xdc_runtime_Memory_HeapProxy_Handle)i;
    return (void*)i2->__fxns == (void*)xdc_runtime_Memory_HeapProxy_Proxy__delegate__S() ? (xdc_runtime_Memory_HeapProxy_Handle)i : 0;
}

/* Handle_from_xdc_runtime_IHeap */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Memory_HeapProxy_Module__id xdc_runtime_Memory_HeapProxy_Module_id( void ) 
{
    return xdc_runtime_Memory_HeapProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */

/* Params_init */
static inline void xdc_runtime_Memory_HeapProxy_Params_init( xdc_runtime_Memory_HeapProxy_Params* prms ) 
{
    if (prms) {
        xdc_runtime_Memory_HeapProxy_Params__init__S(prms, 0, sizeof(xdc_runtime_Memory_HeapProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_Memory_HeapProxy_Params_copy( xdc_runtime_Memory_HeapProxy_Params* dst, const xdc_runtime_Memory_HeapProxy_Params* src ) 
{
    if (dst) {
        xdc_runtime_Memory_HeapProxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(xdc_runtime_Memory_HeapProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline xdc_runtime_Memory_HeapProxy_Handle xdc_runtime_Memory_HeapProxy_create( const xdc_runtime_Memory_HeapProxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_Memory_HeapProxy_Handle)xdc_runtime_Memory_HeapProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_Memory_HeapProxy_Params), __eb);
}

/* delete */
static inline void xdc_runtime_Memory_HeapProxy_delete( xdc_runtime_Memory_HeapProxy_Handle* instp )
{
    xdc_runtime_Memory_HeapProxy_Object__delete__S(instp);
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */

/* Size */
typedef xdc_UArg xdc_runtime_Memory_Size;

/* Stats */
struct xdc_runtime_Memory_Stats {
    xdc_runtime_Memory_Size totalSize;
    xdc_runtime_Memory_Size totalFreeSize;
    xdc_runtime_Memory_Size largestFreeSize;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Memory_Module__diagsEnabled;
extern far const CT__xdc_runtime_Memory_Module__diagsEnabled xdc_runtime_Memory_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Memory_Module__diagsIncluded;
extern far const CT__xdc_runtime_Memory_Module__diagsIncluded xdc_runtime_Memory_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Memory_Module__diagsMask;
extern far const CT__xdc_runtime_Memory_Module__diagsMask xdc_runtime_Memory_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Memory_Module__gateObj;
extern far const CT__xdc_runtime_Memory_Module__gateObj xdc_runtime_Memory_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Memory_Module__gatePrms;
extern far const CT__xdc_runtime_Memory_Module__gatePrms xdc_runtime_Memory_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Memory_Module__id;
extern far const CT__xdc_runtime_Memory_Module__id xdc_runtime_Memory_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Memory_Module__loggerDefined;
extern far const CT__xdc_runtime_Memory_Module__loggerDefined xdc_runtime_Memory_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Memory_Module__loggerObj;
extern far const CT__xdc_runtime_Memory_Module__loggerObj xdc_runtime_Memory_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Memory_Module__loggerFxn0;
extern far const CT__xdc_runtime_Memory_Module__loggerFxn0 xdc_runtime_Memory_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Memory_Module__loggerFxn1;
extern far const CT__xdc_runtime_Memory_Module__loggerFxn1 xdc_runtime_Memory_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Memory_Module__loggerFxn2;
extern far const CT__xdc_runtime_Memory_Module__loggerFxn2 xdc_runtime_Memory_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Memory_Module__loggerFxn4;
extern far const CT__xdc_runtime_Memory_Module__loggerFxn4 xdc_runtime_Memory_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Memory_Module__loggerFxn8;
extern far const CT__xdc_runtime_Memory_Module__loggerFxn8 xdc_runtime_Memory_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Memory_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Memory_Module__startupDoneFxn xdc_runtime_Memory_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Memory_Object__count;
extern far const CT__xdc_runtime_Memory_Object__count xdc_runtime_Memory_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Memory_Object__heap;
extern far const CT__xdc_runtime_Memory_Object__heap xdc_runtime_Memory_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Memory_Object__sizeof;
extern far const CT__xdc_runtime_Memory_Object__sizeof xdc_runtime_Memory_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Memory_Object__table;
extern far const CT__xdc_runtime_Memory_Object__table xdc_runtime_Memory_Object__table__C;

/* defaultHeapInstance */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Memory_defaultHeapInstance;
extern far const CT__xdc_runtime_Memory_defaultHeapInstance xdc_runtime_Memory_defaultHeapInstance__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Memory_Module__startupDone__S( void );

/* alloc__E */

extern xdc_Ptr xdc_runtime_Memory_alloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );

extern xdc_Ptr xdc_runtime_Memory_alloc__F( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );
extern xdc_Ptr xdc_runtime_Memory_alloc__R( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );

/* calloc__E */

extern xdc_Ptr xdc_runtime_Memory_calloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );

extern xdc_Ptr xdc_runtime_Memory_calloc__F( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );
extern xdc_Ptr xdc_runtime_Memory_calloc__R( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb );

/* free__E */

extern void xdc_runtime_Memory_free__E( xdc_runtime_IHeap_Handle heap, xdc_Ptr block, xdc_SizeT size );

extern void xdc_runtime_Memory_free__F( xdc_runtime_IHeap_Handle heap, xdc_Ptr block, xdc_SizeT size );
extern void xdc_runtime_Memory_free__R( xdc_runtime_IHeap_Handle heap, xdc_Ptr block, xdc_SizeT size );

/* getStats__E */

extern void xdc_runtime_Memory_getStats__E( xdc_runtime_IHeap_Handle heap, xdc_runtime_Memory_Stats* stats );

extern void xdc_runtime_Memory_getStats__F( xdc_runtime_IHeap_Handle heap, xdc_runtime_Memory_Stats* stats );
extern void xdc_runtime_Memory_getStats__R( xdc_runtime_IHeap_Handle heap, xdc_runtime_Memory_Stats* stats );

/* query__E */

extern xdc_Bool xdc_runtime_Memory_query__E( xdc_runtime_IHeap_Handle heap, xdc_Int qual );

extern xdc_Bool xdc_runtime_Memory_query__F( xdc_runtime_IHeap_Handle heap, xdc_Int qual );
extern xdc_Bool xdc_runtime_Memory_query__R( xdc_runtime_IHeap_Handle heap, xdc_Int qual );

/* getMaxDefaultTypeAlign__E */

extern xdc_SizeT xdc_runtime_Memory_getMaxDefaultTypeAlign__E( void );

extern xdc_SizeT xdc_runtime_Memory_getMaxDefaultTypeAlign__F( void );
extern xdc_SizeT xdc_runtime_Memory_getMaxDefaultTypeAlign__R( void );

/* valloc__E */

extern xdc_Ptr xdc_runtime_Memory_valloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_Char value, xdc_runtime_Error_Block* eb );

extern xdc_Ptr xdc_runtime_Memory_valloc__F( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_Char value, xdc_runtime_Error_Block* eb );
extern xdc_Ptr xdc_runtime_Memory_valloc__R( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_Char value, xdc_runtime_Error_Block* eb );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Memory_Module__id xdc_runtime_Memory_Module_id( void ) 
{
    return xdc_runtime_Memory_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Memory_Module_hasMask( void ) 
{
    return xdc_runtime_Memory_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Memory_Module_getMask( void ) 
{
    return xdc_runtime_Memory_Module__diagsMask__C != 0 ? *xdc_runtime_Memory_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Memory_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Memory_Module__diagsMask__C != 0) *xdc_runtime_Memory_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:34; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_IHeap_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_IHeap_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*alloc)(void*, xdc_SizeT, xdc_SizeT, xdc_runtime_Error_Block*);
    void (*free)(void*, xdc_Ptr, xdc_SizeT);
    xdc_Bool (*isBlocking)(void*);
    void (*getStats)(void*, xdc_runtime_Memory_Stats*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base xdc_runtime_IHeap_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
static inline xdc_runtime_IHeap_Handle xdc_runtime_IHeap_create( xdc_runtime_IHeap_Module __mod, const xdc_runtime_IHeap_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_IHeap_Handle) __mod->__sysp->__create(0, 0, 0, (const xdc_UChar*)__prms, sizeof (xdc_runtime_IHeap_Params), __eb);
}

/* delete */
static inline void xdc_runtime_IHeap_delete( xdc_runtime_IHeap_Handle* instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}

/* Handle_to_Module */
static inline xdc_runtime_IHeap_Module xdc_runtime_IHeap_Handle_to_Module( xdc_runtime_IHeap_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label* xdc_runtime_IHeap_Handle_label( xdc_runtime_IHeap_Handle inst, xdc_runtime_Types_Label* lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_IHeap_Module_id( xdc_runtime_IHeap_Module mod )
{
    return mod->__sysp->__mid;
}

/* alloc */
static inline xdc_Ptr xdc_runtime_IHeap_alloc( xdc_runtime_IHeap_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb )
{
    return __inst->__fxns->alloc((void*)__inst, size, align, eb);
}

/* free */
static inline void xdc_runtime_IHeap_free( xdc_runtime_IHeap_Handle __inst, xdc_Ptr block, xdc_SizeT size )
{
    __inst->__fxns->free((void*)__inst, block, size);
}

/* isBlocking */
static inline xdc_Bool xdc_runtime_IHeap_isBlocking( xdc_runtime_IHeap_Handle __inst )
{
    return __inst->__fxns->isBlocking((void*)__inst);
}

/* getStats */
static inline void xdc_runtime_IHeap_getStats( xdc_runtime_IHeap_Handle __inst, xdc_runtime_Memory_Stats* stats )
{
    __inst->__fxns->getStats((void*)__inst, stats);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* alloc_{FxnT,fxnP} */
typedef xdc_Ptr (*xdc_runtime_IHeap_alloc_FxnT)(void*, xdc_SizeT, xdc_SizeT, xdc_runtime_Error_Block*);
static inline xdc_runtime_IHeap_alloc_FxnT xdc_runtime_IHeap_alloc_fxnP( xdc_runtime_IHeap_Handle __inst )
{
    return (xdc_runtime_IHeap_alloc_FxnT)__inst->__fxns->alloc;
}

/* free_{FxnT,fxnP} */
typedef void (*xdc_runtime_IHeap_free_FxnT)(void*, xdc_Ptr, xdc_SizeT);
static inline xdc_runtime_IHeap_free_FxnT xdc_runtime_IHeap_free_fxnP( xdc_runtime_IHeap_Handle __inst )
{
    return (xdc_runtime_IHeap_free_FxnT)__inst->__fxns->free;
}

/* isBlocking_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_IHeap_isBlocking_FxnT)(void*);
static inline xdc_runtime_IHeap_isBlocking_FxnT xdc_runtime_IHeap_isBlocking_fxnP( xdc_runtime_IHeap_Handle __inst )
{
    return (xdc_runtime_IHeap_isBlocking_FxnT)__inst->__fxns->isBlocking;
}

/* getStats_{FxnT,fxnP} */
typedef void (*xdc_runtime_IHeap_getStats_FxnT)(void*, xdc_runtime_Memory_Stats*);
static inline xdc_runtime_IHeap_getStats_FxnT xdc_runtime_IHeap_getStats_fxnP( xdc_runtime_IHeap_Handle __inst )
{
    return (xdc_runtime_IHeap_getStats_FxnT)__inst->__fxns->getStats;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_IModule_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base xdc_runtime_IModule_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_IModule_Module_id( xdc_runtime_IModule_Module mod )
{
    return mod->__sysp->__mid;
}


/*
 * ======== FUNCTION SELECTORS ========
 */


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */

/* Q_PREEMPTING */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_IGateProvider_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_IGateProvider_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(void*);
    void (*leave)(void*, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base xdc_runtime_IGateProvider_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
static inline xdc_runtime_IGateProvider_Handle xdc_runtime_IGateProvider_create( xdc_runtime_IGateProvider_Module __mod, const xdc_runtime_IGateProvider_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_IGateProvider_Handle) __mod->__sysp->__create(0, 0, 0, (const xdc_UChar*)__prms, sizeof (xdc_runtime_IGateProvider_Params), __eb);
}

/* delete */
static inline void xdc_runtime_IGateProvider_delete( xdc_runtime_IGateProvider_Handle* instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}

/* Handle_to_Module */
static inline xdc_runtime_IGateProvider_Module xdc_runtime_IGateProvider_Handle_to_Module( xdc_runtime_IGateProvider_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label* xdc_runtime_IGateProvider_Handle_label( xdc_runtime_IGateProvider_Handle inst, xdc_runtime_Types_Label* lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_IGateProvider_Module_id( xdc_runtime_IGateProvider_Module mod )
{
    return mod->__sysp->__mid;
}

/* query */
static inline xdc_Bool xdc_runtime_IGateProvider_query( xdc_runtime_IGateProvider_Module __inst, xdc_Int qual )
{
    return __inst->query(qual);
}

/* enter */
static inline xdc_IArg xdc_runtime_IGateProvider_enter( xdc_runtime_IGateProvider_Handle __inst )
{
    return __inst->__fxns->enter((void*)__inst);
}

/* leave */
static inline void xdc_runtime_IGateProvider_leave( xdc_runtime_IGateProvider_Handle __inst, xdc_IArg key )
{
    __inst->__fxns->leave((void*)__inst, key);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* query_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_IGateProvider_query_FxnT)(xdc_Int);
static inline xdc_runtime_IGateProvider_query_FxnT xdc_runtime_IGateProvider_query_fxnP( xdc_runtime_IGateProvider_Module __inst )
{
    return (xdc_runtime_IGateProvider_query_FxnT)__inst->query;
}

/* enter_{FxnT,fxnP} */
typedef xdc_IArg (*xdc_runtime_IGateProvider_enter_FxnT)(void*);
static inline xdc_runtime_IGateProvider_enter_FxnT xdc_runtime_IGateProvider_enter_fxnP( xdc_runtime_IGateProvider_Handle __inst )
{
    return (xdc_runtime_IGateProvider_enter_FxnT)__inst->__fxns->enter;
}

/* leave_{FxnT,fxnP} */
typedef void (*xdc_runtime_IGateProvider_leave_FxnT)(void*, xdc_IArg);
static inline xdc_runtime_IGateProvider_leave_FxnT xdc_runtime_IGateProvider_leave_fxnP( xdc_runtime_IGateProvider_Handle __inst )
{
    return (xdc_runtime_IGateProvider_leave_FxnT)__inst->__fxns->leave;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */

/* Q_PREEMPTING */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Main_Module_GateProxy_Module__diagsEnabled;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__diagsEnabled xdc_runtime_Main_Module_GateProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Main_Module_GateProxy_Module__diagsIncluded;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__diagsIncluded xdc_runtime_Main_Module_GateProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Main_Module_GateProxy_Module__diagsMask;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__diagsMask xdc_runtime_Main_Module_GateProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Main_Module_GateProxy_Module__gateObj;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__gateObj xdc_runtime_Main_Module_GateProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Main_Module_GateProxy_Module__gatePrms;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__gatePrms xdc_runtime_Main_Module_GateProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Main_Module_GateProxy_Module__id;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__id xdc_runtime_Main_Module_GateProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Main_Module_GateProxy_Module__loggerDefined;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerDefined xdc_runtime_Main_Module_GateProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Main_Module_GateProxy_Module__loggerObj;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerObj xdc_runtime_Main_Module_GateProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn0;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn0 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn1;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn1 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn2;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn2 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn4;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn4 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn8;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__loggerFxn8 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Main_Module_GateProxy_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Main_Module_GateProxy_Module__startupDoneFxn xdc_runtime_Main_Module_GateProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Main_Module_GateProxy_Object__count;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Object__count xdc_runtime_Main_Module_GateProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Main_Module_GateProxy_Object__heap;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Object__heap xdc_runtime_Main_Module_GateProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Main_Module_GateProxy_Object__sizeof;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Object__sizeof xdc_runtime_Main_Module_GateProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Main_Module_GateProxy_Object__table;
extern far const CT__xdc_runtime_Main_Module_GateProxy_Object__table xdc_runtime_Main_Module_GateProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_Main_Module_GateProxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_Main_Module_GateProxy_Struct {
    const xdc_runtime_Main_Module_GateProxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_Main_Module_GateProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(xdc_runtime_Main_Module_GateProxy_Handle);
    void (*leave)(xdc_runtime_Main_Module_GateProxy_Handle, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const xdc_runtime_Main_Module_GateProxy_Fxns__ xdc_runtime_Main_Module_GateProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* xdc_runtime_Main_Module_GateProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Main_Module_GateProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr xdc_runtime_Main_Module_GateProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void xdc_runtime_Main_Module_GateProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void xdc_runtime_Main_Module_GateProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr xdc_runtime_Main_Module_GateProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr xdc_runtime_Main_Module_GateProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr xdc_runtime_Main_Module_GateProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void xdc_runtime_Main_Module_GateProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool xdc_runtime_Main_Module_GateProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr xdc_runtime_Main_Module_GateProxy_Proxy__delegate__S( void );

/* query__E */

extern xdc_Bool xdc_runtime_Main_Module_GateProxy_query__E( xdc_Int qual );

extern xdc_Bool xdc_runtime_Main_Module_GateProxy_query__R( xdc_Int qual );

/* enter__E */

extern xdc_IArg xdc_runtime_Main_Module_GateProxy_enter__E( xdc_runtime_Main_Module_GateProxy_Handle __inst );

extern xdc_IArg xdc_runtime_Main_Module_GateProxy_enter__R( xdc_runtime_Main_Module_GateProxy_Handle __inst );

/* leave__E */

extern void xdc_runtime_Main_Module_GateProxy_leave__E( xdc_runtime_Main_Module_GateProxy_Handle __inst, xdc_IArg key );

extern void xdc_runtime_Main_Module_GateProxy_leave__R( xdc_runtime_Main_Module_GateProxy_Handle __inst, xdc_IArg key );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* enter_{FxnT,fxnP} */
typedef xdc_IArg (*xdc_runtime_Main_Module_GateProxy_enter_FxnT)(void*);
static inline xdc_runtime_Main_Module_GateProxy_enter_FxnT xdc_runtime_Main_Module_GateProxy_enter_fxnP( void )
{
    return (xdc_runtime_Main_Module_GateProxy_enter_FxnT)xdc_runtime_Main_Module_GateProxy_enter__E; 
}

/* leave_{FxnT,fxnP} */
typedef void (*xdc_runtime_Main_Module_GateProxy_leave_FxnT)(void*, xdc_IArg);
static inline xdc_runtime_Main_Module_GateProxy_leave_FxnT xdc_runtime_Main_Module_GateProxy_leave_fxnP( void )
{
    return (xdc_runtime_Main_Module_GateProxy_leave_FxnT)xdc_runtime_Main_Module_GateProxy_leave__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IGateProvider_Module xdc_runtime_Main_Module_GateProxy_Module_upCast( void )
{
    return (xdc_runtime_IGateProvider_Module)xdc_runtime_Main_Module_GateProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */

/* Handle_upCast */
static inline xdc_runtime_IGateProvider_Handle xdc_runtime_Main_Module_GateProxy_Handle_upCast( xdc_runtime_Main_Module_GateProxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */

/* Handle_downCast */
static inline xdc_runtime_Main_Module_GateProxy_Handle xdc_runtime_Main_Module_GateProxy_Handle_downCast( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
if (xdc_runtime_Main_Module_GateProxy_Proxy__abstract__S()) return (xdc_runtime_Main_Module_GateProxy_Handle)i;
    return (void*)i2->__fxns == (void*)xdc_runtime_Main_Module_GateProxy_Proxy__delegate__S() ? (xdc_runtime_Main_Module_GateProxy_Handle)i : 0;
}

/* Handle_from_xdc_runtime_IGateProvider */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Main_Module_GateProxy_Module__id xdc_runtime_Main_Module_GateProxy_Module_id( void ) 
{
    return xdc_runtime_Main_Module_GateProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */

/* Params_init */
static inline void xdc_runtime_Main_Module_GateProxy_Params_init( xdc_runtime_Main_Module_GateProxy_Params* prms ) 
{
    if (prms) {
        xdc_runtime_Main_Module_GateProxy_Params__init__S(prms, 0, sizeof(xdc_runtime_Main_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_Main_Module_GateProxy_Params_copy( xdc_runtime_Main_Module_GateProxy_Params* dst, const xdc_runtime_Main_Module_GateProxy_Params* src ) 
{
    if (dst) {
        xdc_runtime_Main_Module_GateProxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(xdc_runtime_Main_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline xdc_runtime_Main_Module_GateProxy_Handle xdc_runtime_Main_Module_GateProxy_create( const xdc_runtime_Main_Module_GateProxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_Main_Module_GateProxy_Handle)xdc_runtime_Main_Module_GateProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_Main_Module_GateProxy_Params), __eb);
}

/* delete */
static inline void xdc_runtime_Main_Module_GateProxy_delete( xdc_runtime_Main_Module_GateProxy_Handle* instp )
{
    xdc_runtime_Main_Module_GateProxy_Object__delete__S(instp);
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Main_Module__diagsEnabled;
extern far const CT__xdc_runtime_Main_Module__diagsEnabled xdc_runtime_Main_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Main_Module__diagsIncluded;
extern far const CT__xdc_runtime_Main_Module__diagsIncluded xdc_runtime_Main_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Main_Module__diagsMask;
extern far const CT__xdc_runtime_Main_Module__diagsMask xdc_runtime_Main_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Main_Module__gateObj;
extern far const CT__xdc_runtime_Main_Module__gateObj xdc_runtime_Main_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Main_Module__gatePrms;
extern far const CT__xdc_runtime_Main_Module__gatePrms xdc_runtime_Main_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Main_Module__id;
extern far const CT__xdc_runtime_Main_Module__id xdc_runtime_Main_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Main_Module__loggerDefined;
extern far const CT__xdc_runtime_Main_Module__loggerDefined xdc_runtime_Main_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Main_Module__loggerObj;
extern far const CT__xdc_runtime_Main_Module__loggerObj xdc_runtime_Main_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Main_Module__loggerFxn0;
extern far const CT__xdc_runtime_Main_Module__loggerFxn0 xdc_runtime_Main_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Main_Module__loggerFxn1;
extern far const CT__xdc_runtime_Main_Module__loggerFxn1 xdc_runtime_Main_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Main_Module__loggerFxn2;
extern far const CT__xdc_runtime_Main_Module__loggerFxn2 xdc_runtime_Main_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Main_Module__loggerFxn4;
extern far const CT__xdc_runtime_Main_Module__loggerFxn4 xdc_runtime_Main_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Main_Module__loggerFxn8;
extern far const CT__xdc_runtime_Main_Module__loggerFxn8 xdc_runtime_Main_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Main_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Main_Module__startupDoneFxn xdc_runtime_Main_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Main_Object__count;
extern far const CT__xdc_runtime_Main_Object__count xdc_runtime_Main_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Main_Object__heap;
extern far const CT__xdc_runtime_Main_Object__heap xdc_runtime_Main_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Main_Object__sizeof;
extern far const CT__xdc_runtime_Main_Object__sizeof xdc_runtime_Main_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Main_Object__table;
extern far const CT__xdc_runtime_Main_Object__table xdc_runtime_Main_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Main_Module__startupDone__S( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Main_Module__id xdc_runtime_Main_Module_id( void ) 
{
    return xdc_runtime_Main_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Main_Module_hasMask( void ) 
{
    return xdc_runtime_Main_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Main_Module_getMask( void ) 
{
    return xdc_runtime_Main_Module__diagsMask__C != 0 ? *xdc_runtime_Main_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Main_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Main_Module__diagsMask__C != 0) *xdc_runtime_Main_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:34; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  ======== xdc_runtime_Error_Id ========
 */
typedef xdc_Bits32 xdc_runtime_Error_Id;



/*
 *  ======== Module__MID ========
 *  This definition allows non-module code to
 *  use the Error module.  This symbol is normally defined in each
 *  module internal header (i.e., package/internal/<mod>.xdc.h).
 *
 *  Only do this if this file is not one that will be included in the Registry.
 *  This check ensures that Registry.h (which similarly defines these Module__*
 *  symbols) can be included in any order relative to other xdc.runtime 
 *  headers.
 */


/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Policy */
enum xdc_runtime_Error_Policy {
    xdc_runtime_Error_TERMINATE,
    xdc_runtime_Error_UNWIND
};
typedef enum xdc_runtime_Error_Policy xdc_runtime_Error_Policy;

/* Id */

/* HookFxn */
typedef void (*xdc_runtime_Error_HookFxn)(xdc_runtime_Error_Block*);

/* NUMARGS */

/* Data */
typedef xdc_IArg __T1_xdc_runtime_Error_Data__arg;
typedef xdc_IArg __ARRAY1_xdc_runtime_Error_Data__arg[2];
typedef __ARRAY1_xdc_runtime_Error_Data__arg __TA_xdc_runtime_Error_Data__arg;
struct xdc_runtime_Error_Data {
    __TA_xdc_runtime_Error_Data__arg arg;
};

/* Block */
typedef xdc_IArg __T1_xdc_runtime_Error_Block__xtra;
typedef xdc_IArg __ARRAY1_xdc_runtime_Error_Block__xtra[4];
typedef __ARRAY1_xdc_runtime_Error_Block__xtra __TA_xdc_runtime_Error_Block__xtra;
struct xdc_runtime_Error_Block {
    xdc_UInt16 unused;
    xdc_runtime_Error_Data data;
    xdc_runtime_Error_Id id;
    xdc_String msg;
    xdc_runtime_Types_Site site;
    __TA_xdc_runtime_Error_Block__xtra xtra;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Error_Module__diagsEnabled;
extern far const CT__xdc_runtime_Error_Module__diagsEnabled xdc_runtime_Error_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Error_Module__diagsIncluded;
extern far const CT__xdc_runtime_Error_Module__diagsIncluded xdc_runtime_Error_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Error_Module__diagsMask;
extern far const CT__xdc_runtime_Error_Module__diagsMask xdc_runtime_Error_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Error_Module__gateObj;
extern far const CT__xdc_runtime_Error_Module__gateObj xdc_runtime_Error_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Error_Module__gatePrms;
extern far const CT__xdc_runtime_Error_Module__gatePrms xdc_runtime_Error_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Error_Module__id;
extern far const CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Error_Module__loggerDefined;
extern far const CT__xdc_runtime_Error_Module__loggerDefined xdc_runtime_Error_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Error_Module__loggerObj;
extern far const CT__xdc_runtime_Error_Module__loggerObj xdc_runtime_Error_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Error_Module__loggerFxn0;
extern far const CT__xdc_runtime_Error_Module__loggerFxn0 xdc_runtime_Error_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Error_Module__loggerFxn1;
extern far const CT__xdc_runtime_Error_Module__loggerFxn1 xdc_runtime_Error_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Error_Module__loggerFxn2;
extern far const CT__xdc_runtime_Error_Module__loggerFxn2 xdc_runtime_Error_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Error_Module__loggerFxn4;
extern far const CT__xdc_runtime_Error_Module__loggerFxn4 xdc_runtime_Error_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Error_Module__loggerFxn8;
extern far const CT__xdc_runtime_Error_Module__loggerFxn8 xdc_runtime_Error_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Error_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Error_Module__startupDoneFxn xdc_runtime_Error_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Error_Object__count;
extern far const CT__xdc_runtime_Error_Object__count xdc_runtime_Error_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Error_Object__heap;
extern far const CT__xdc_runtime_Error_Object__heap xdc_runtime_Error_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Error_Object__sizeof;
extern far const CT__xdc_runtime_Error_Object__sizeof xdc_runtime_Error_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Error_Object__table;
extern far const CT__xdc_runtime_Error_Object__table xdc_runtime_Error_Object__table__C;

/* E_generic */
typedef xdc_runtime_Error_Id CT__xdc_runtime_Error_E_generic;
extern far const CT__xdc_runtime_Error_E_generic xdc_runtime_Error_E_generic__C;

/* E_memory */
typedef xdc_runtime_Error_Id CT__xdc_runtime_Error_E_memory;
extern far const CT__xdc_runtime_Error_E_memory xdc_runtime_Error_E_memory__C;

/* E_msgCode */
typedef xdc_runtime_Error_Id CT__xdc_runtime_Error_E_msgCode;
extern far const CT__xdc_runtime_Error_E_msgCode xdc_runtime_Error_E_msgCode__C;

/* policy */
typedef xdc_runtime_Error_Policy CT__xdc_runtime_Error_policy;
extern far const CT__xdc_runtime_Error_policy xdc_runtime_Error_policy__C;

/* raiseHook */
typedef xdc_runtime_Error_HookFxn CT__xdc_runtime_Error_raiseHook;
extern far const CT__xdc_runtime_Error_raiseHook xdc_runtime_Error_raiseHook__C;

/* maxDepth */
typedef xdc_UInt16 CT__xdc_runtime_Error_maxDepth;
extern far const CT__xdc_runtime_Error_maxDepth xdc_runtime_Error_maxDepth__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Error_Module__startupDone__S( void );

/* check__E */

extern xdc_Bool xdc_runtime_Error_check__E( xdc_runtime_Error_Block* eb );

extern xdc_Bool xdc_runtime_Error_check__F( xdc_runtime_Error_Block* eb );
extern xdc_Bool xdc_runtime_Error_check__R( xdc_runtime_Error_Block* eb );

/* getData__E */

extern xdc_runtime_Error_Data* xdc_runtime_Error_getData__E( xdc_runtime_Error_Block* eb );

extern xdc_runtime_Error_Data* xdc_runtime_Error_getData__F( xdc_runtime_Error_Block* eb );
extern xdc_runtime_Error_Data* xdc_runtime_Error_getData__R( xdc_runtime_Error_Block* eb );

/* getCode__E */

extern xdc_UInt16 xdc_runtime_Error_getCode__E( xdc_runtime_Error_Block* eb );

extern xdc_UInt16 xdc_runtime_Error_getCode__F( xdc_runtime_Error_Block* eb );
extern xdc_UInt16 xdc_runtime_Error_getCode__R( xdc_runtime_Error_Block* eb );

/* getId__E */

extern xdc_runtime_Error_Id xdc_runtime_Error_getId__E( xdc_runtime_Error_Block* eb );

extern xdc_runtime_Error_Id xdc_runtime_Error_getId__F( xdc_runtime_Error_Block* eb );
extern xdc_runtime_Error_Id xdc_runtime_Error_getId__R( xdc_runtime_Error_Block* eb );

/* getMsg__E */

extern xdc_String xdc_runtime_Error_getMsg__E( xdc_runtime_Error_Block* eb );

extern xdc_String xdc_runtime_Error_getMsg__F( xdc_runtime_Error_Block* eb );
extern xdc_String xdc_runtime_Error_getMsg__R( xdc_runtime_Error_Block* eb );

/* getSite__E */

extern xdc_runtime_Types_Site* xdc_runtime_Error_getSite__E( xdc_runtime_Error_Block* eb );

extern xdc_runtime_Types_Site* xdc_runtime_Error_getSite__F( xdc_runtime_Error_Block* eb );
extern xdc_runtime_Types_Site* xdc_runtime_Error_getSite__R( xdc_runtime_Error_Block* eb );

/* init__E */

extern void xdc_runtime_Error_init__E( xdc_runtime_Error_Block* eb );

extern void xdc_runtime_Error_init__F( xdc_runtime_Error_Block* eb );
extern void xdc_runtime_Error_init__R( xdc_runtime_Error_Block* eb );

/* print__E */

extern void xdc_runtime_Error_print__E( xdc_runtime_Error_Block* eb );

extern void xdc_runtime_Error_print__F( xdc_runtime_Error_Block* eb );
extern void xdc_runtime_Error_print__R( xdc_runtime_Error_Block* eb );

/* raiseX__E */

extern void xdc_runtime_Error_raiseX__E( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 );

extern void xdc_runtime_Error_raiseX__F( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 );
extern void xdc_runtime_Error_raiseX__R( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module_id( void ) 
{
    return xdc_runtime_Error_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Error_Module_hasMask( void ) 
{
    return xdc_runtime_Error_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Error_Module_getMask( void ) 
{
    return xdc_runtime_Error_Module__diagsMask__C != 0 ? *xdc_runtime_Error_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Error_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Error_Module__diagsMask__C != 0) *xdc_runtime_Error_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== xdc_runtime_Error_raise ========
 *  Call underlying error handler with current module ID, file name, and
 *  line number.
 *
 *  Note use of xdc_FILE__ in lieu of __FILE__; this is done
 *  to prevent accumulation of file name strings in the application.  See
 *  xdc.h for details.
 */

/*
 *  ======== xdc_runtime_Error_idToCode ========
 */

/*
 *  ======== xdc_runtime_Error_idToUid ========
 */
/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */





/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:34; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */

/*
 *  ======== Diags__prologue.h ========
 *
 *  This header defines Module__* symbols for every Module__* value used
 *  by the Diags module's headers.  This allows non-module code to
 *  use the Diags module.  These symbols are normally defined in
 *  module internal headers (i.e., package/internal/<mod>.xdc.h) and they
 *  define a "current module context".
 */
/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:34; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/* 
 * Only define these symbols for xdc.runtime.Main if this file is not one that
 * will be included in the Registry. This check ensures that Registry.h (which
 * similarly defines these Module__* symbols) can be included in any order
 * relative to other xdc.runtime headers.
 */

/*
 *  ======== Module__DGSINCL ========
 *  The set of diags categories that are runtime controllable _or_ always on
 *
 *  This costant is computed at config time and enables us to eliminate
 *  expensive runtime time checks and unnecessary data (the module's diags 
 *  mask) when whole program optimization is used.
 */

/*
 *  ======== Module__DGSENAB ========
 *  The set of diags categories that are _always_ enabled
 *
 *  This costant is computed at config time and enables us to eliminate
 *  expensive runtime time checks and unnecessary data (the module's diags 
 *  mask) when whole program optimization is used.
 */

/*
 *  ======== Module__DGSMASK ========
 *  Pointer to the set of diags categories that are runtime controllable 
 */

/*
 *  ======== Module__MID ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Mask */
typedef xdc_runtime_Types_DiagsMask xdc_runtime_Diags_Mask;

/* ENTRY */

/* EXIT */

/* LIFECYCLE */

/* INTERNAL */

/* ASSERT */

/* STATUS */

/* LEVEL */

/* USER1 */

/* USER2 */

/* USER3 */

/* USER4 */

/* USER5 */

/* USER6 */

/* USER7 */

/* INFO */

/* USER8 */

/* ANALYSIS */

/* ALL */

/* ALL_LOGGING */

/* EventLevel */
enum xdc_runtime_Diags_EventLevel {
    xdc_runtime_Diags_LEVEL1 = 0x0,
    xdc_runtime_Diags_LEVEL2 = 0x20,
    xdc_runtime_Diags_LEVEL3 = 0x40,
    xdc_runtime_Diags_LEVEL4 = 0x60
};
typedef enum xdc_runtime_Diags_EventLevel xdc_runtime_Diags_EventLevel;

/* EMERGENCY */

/* CRITICAL */

/* ERROR */

/* WARNING */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* DictElem */
struct xdc_runtime_Diags_DictElem {
    xdc_runtime_Types_ModuleId modId;
    xdc_runtime_Diags_Mask* maskAddr;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Diags_Module__diagsEnabled;
extern far const CT__xdc_runtime_Diags_Module__diagsEnabled xdc_runtime_Diags_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Diags_Module__diagsIncluded;
extern far const CT__xdc_runtime_Diags_Module__diagsIncluded xdc_runtime_Diags_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Diags_Module__diagsMask;
extern far const CT__xdc_runtime_Diags_Module__diagsMask xdc_runtime_Diags_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Diags_Module__gateObj;
extern far const CT__xdc_runtime_Diags_Module__gateObj xdc_runtime_Diags_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Diags_Module__gatePrms;
extern far const CT__xdc_runtime_Diags_Module__gatePrms xdc_runtime_Diags_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Diags_Module__id;
extern far const CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Diags_Module__loggerDefined;
extern far const CT__xdc_runtime_Diags_Module__loggerDefined xdc_runtime_Diags_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Diags_Module__loggerObj;
extern far const CT__xdc_runtime_Diags_Module__loggerObj xdc_runtime_Diags_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Diags_Module__loggerFxn0;
extern far const CT__xdc_runtime_Diags_Module__loggerFxn0 xdc_runtime_Diags_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Diags_Module__loggerFxn1;
extern far const CT__xdc_runtime_Diags_Module__loggerFxn1 xdc_runtime_Diags_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Diags_Module__loggerFxn2;
extern far const CT__xdc_runtime_Diags_Module__loggerFxn2 xdc_runtime_Diags_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Diags_Module__loggerFxn4;
extern far const CT__xdc_runtime_Diags_Module__loggerFxn4 xdc_runtime_Diags_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Diags_Module__loggerFxn8;
extern far const CT__xdc_runtime_Diags_Module__loggerFxn8 xdc_runtime_Diags_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Diags_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Diags_Module__startupDoneFxn xdc_runtime_Diags_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Diags_Object__count;
extern far const CT__xdc_runtime_Diags_Object__count xdc_runtime_Diags_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Diags_Object__heap;
extern far const CT__xdc_runtime_Diags_Object__heap xdc_runtime_Diags_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Diags_Object__sizeof;
extern far const CT__xdc_runtime_Diags_Object__sizeof xdc_runtime_Diags_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Diags_Object__table;
extern far const CT__xdc_runtime_Diags_Object__table xdc_runtime_Diags_Object__table__C;

/* setMaskEnabled */
typedef xdc_Bool CT__xdc_runtime_Diags_setMaskEnabled;
extern far const CT__xdc_runtime_Diags_setMaskEnabled xdc_runtime_Diags_setMaskEnabled__C;

/* dictBase */
typedef xdc_runtime_Diags_DictElem* CT__xdc_runtime_Diags_dictBase;
extern far const CT__xdc_runtime_Diags_dictBase xdc_runtime_Diags_dictBase__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Diags_Module__startupDone__S( void );

/* setMask__E */

extern void xdc_runtime_Diags_setMask__E( xdc_String control );

extern void xdc_runtime_Diags_setMask__F( xdc_String control );
extern void xdc_runtime_Diags_setMask__R( xdc_String control );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module_id( void ) 
{
    return xdc_runtime_Diags_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Diags_Module_hasMask( void ) 
{
    return xdc_runtime_Diags_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Diags_Module_getMask( void ) 
{
    return xdc_runtime_Diags_Module__diagsMask__C != 0 ? *xdc_runtime_Diags_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Diags_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Diags_Module__diagsMask__C != 0) *xdc_runtime_Diags_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== xdc_runtime_Diags_query ========
 *  Returns true iff: 
 *      1. the current module's included diags intersect evt's mask, and
 *      2. either the permanently enabled diags intersect evt's mask or
 *         the runtime controllable diags intersect evt's mask.
 *
 *  This macro relies on three "internal" macros which are defined in each
 *  module's internal header (e.g., package/internal/System.xdc.h):
 *      Module__DGSINCL - a const bit mask of bits that are _not_ ALWAYS_OFF
 *      Module__DGSENAB - a const bit mask of bits that are ALWAYS_ON
 *      Module__DGSMASK - a const pointer to a bit mask of currently enabled
 *                        diagnostics
 *  These macros reference module-specific variables generated at config
 *  time, when we know the value of these constants.
 *
 */

/*
 *  ======== xdc_runtime_Diags_getLevel ========
 *  Returns the event level set in the given diags mask. The level is a value
 *  stored using two bits of the diags mask.
 */

/*
 *  ======== xdc_runtime_Diags_compareLevels ========
 *  The definition of the diags levels assigns the value '0' to the highest
 *  priority events and '3' to the lowest, so the comparison is done backwards.
 *  For example, for (LEVEL4 (0), LEVEL1 (3)) this must return false.
 */
/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */





/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  ======== xdc_runtime_Log_Event ========
 *  Log_Event is an encoded type.  Log Events are encoded on the target as
 *  a 32-bit value:
 *
 *      | format rope | module ID or mask |
 *      | 31 ----- 16 | 15 ------------ 0 |
 *
 *  The lower 16-bits contain either a mask or a module ID; when the event
 *  is statically declared this field has a mask, when the event is passed
 *  to an ILogger this field is the module ID of the module that generated
 *  the event.
 *
 *  The upper 16-bits are an ID (rope) that that identifies the format
 *  string to use to render the event (and its arguments).
 */
typedef xdc_Bits32 xdc_runtime_Log_Event;

/*
 *  The following macros establish xdc.runtime.Main as the "default"
 *  module for all sources files not part of a module.
 *
 *      Module__MID     - the module's ID (see Text.xs)
 *      Module__LOGOBJ  - the module's logger object
 *      Module__LOGFXN0 - the module's logger's write0 function
 *      Module__LOGFXN1 - the module's logger's write1 function
 *      Module__LOGFXN2 - the module's logger's write2 function
 *      Module__LOGFXN4 - the module's logger's write4 function
 *      Module__LOGFXN8 - the module's logger's write8 function
 *      Module__LOGDEF  - 0 if the module has a logger, non-zero otherwise
 *
 *  Only define these symbols for xdc.runtime.Main if this file is not one that
 *  will be included in the Registry. This check ensures that Registry.h (which
 *  similarly defines these Module__* symbols) can be included in any order
 *  relative to other xdc.runtime headers.
 */
 


/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */






/*
 * ======== INCLUDES ========
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* CordAddr */
typedef xdc_runtime_Types_CordAddr xdc_runtime_Text_CordAddr;

/* Label */
typedef xdc_runtime_Types_Label xdc_runtime_Text_Label;

/* RopeId */
typedef xdc_runtime_Types_RopeId xdc_runtime_Text_RopeId;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Node */
struct xdc_runtime_Text_Node {
    xdc_runtime_Types_RopeId left;
    xdc_runtime_Types_RopeId right;
};

/* RopeVisitor */
typedef xdc_Bool (*xdc_runtime_Text_RopeVisitor)(xdc_Ptr, xdc_String);

/* MatchVisState */
struct xdc_runtime_Text_MatchVisState {
    xdc_String pat;
    xdc_Int* lenp;
    xdc_Int res;
};

/* PrintVisState */
struct xdc_runtime_Text_PrintVisState {
    xdc_Char** bufp;
    xdc_Int len;
    xdc_Int res;
};

/* VisitRopeFxn */
typedef void (*xdc_runtime_Text_VisitRopeFxn)(xdc_runtime_Text_RopeId, xdc_Fxn, xdc_Ptr);

/* VisitRopeFxn2 */
typedef void (*xdc_runtime_Text_VisitRopeFxn2)(xdc_runtime_Text_RopeId, xdc_Fxn, xdc_Ptr, xdc_String[]);


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Text_Module__diagsEnabled;
extern far const CT__xdc_runtime_Text_Module__diagsEnabled xdc_runtime_Text_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Text_Module__diagsIncluded;
extern far const CT__xdc_runtime_Text_Module__diagsIncluded xdc_runtime_Text_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Text_Module__diagsMask;
extern far const CT__xdc_runtime_Text_Module__diagsMask xdc_runtime_Text_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Text_Module__gateObj;
extern far const CT__xdc_runtime_Text_Module__gateObj xdc_runtime_Text_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Text_Module__gatePrms;
extern far const CT__xdc_runtime_Text_Module__gatePrms xdc_runtime_Text_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Text_Module__id;
extern far const CT__xdc_runtime_Text_Module__id xdc_runtime_Text_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Text_Module__loggerDefined;
extern far const CT__xdc_runtime_Text_Module__loggerDefined xdc_runtime_Text_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Text_Module__loggerObj;
extern far const CT__xdc_runtime_Text_Module__loggerObj xdc_runtime_Text_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Text_Module__loggerFxn0;
extern far const CT__xdc_runtime_Text_Module__loggerFxn0 xdc_runtime_Text_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Text_Module__loggerFxn1;
extern far const CT__xdc_runtime_Text_Module__loggerFxn1 xdc_runtime_Text_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Text_Module__loggerFxn2;
extern far const CT__xdc_runtime_Text_Module__loggerFxn2 xdc_runtime_Text_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Text_Module__loggerFxn4;
extern far const CT__xdc_runtime_Text_Module__loggerFxn4 xdc_runtime_Text_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Text_Module__loggerFxn8;
extern far const CT__xdc_runtime_Text_Module__loggerFxn8 xdc_runtime_Text_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Text_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Text_Module__startupDoneFxn xdc_runtime_Text_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Text_Object__count;
extern far const CT__xdc_runtime_Text_Object__count xdc_runtime_Text_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Text_Object__heap;
extern far const CT__xdc_runtime_Text_Object__heap xdc_runtime_Text_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Text_Object__sizeof;
extern far const CT__xdc_runtime_Text_Object__sizeof xdc_runtime_Text_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Text_Object__table;
extern far const CT__xdc_runtime_Text_Object__table xdc_runtime_Text_Object__table__C;

/* nameUnknown */
typedef xdc_String CT__xdc_runtime_Text_nameUnknown;
extern far const CT__xdc_runtime_Text_nameUnknown xdc_runtime_Text_nameUnknown__C;

/* nameEmpty */
typedef xdc_String CT__xdc_runtime_Text_nameEmpty;
extern far const CT__xdc_runtime_Text_nameEmpty xdc_runtime_Text_nameEmpty__C;

/* nameStatic */
typedef xdc_String CT__xdc_runtime_Text_nameStatic;
extern far const CT__xdc_runtime_Text_nameStatic xdc_runtime_Text_nameStatic__C;

/* isLoaded */
typedef xdc_Bool CT__xdc_runtime_Text_isLoaded;
extern far const CT__xdc_runtime_Text_isLoaded xdc_runtime_Text_isLoaded__C;

/* charTab */
typedef xdc_Char __T1_xdc_runtime_Text_charTab;
typedef xdc_Char *__ARRAY1_xdc_runtime_Text_charTab;
typedef __ARRAY1_xdc_runtime_Text_charTab __TA_xdc_runtime_Text_charTab;
typedef __TA_xdc_runtime_Text_charTab CT__xdc_runtime_Text_charTab;
extern far const CT__xdc_runtime_Text_charTab xdc_runtime_Text_charTab__C;

/* nodeTab */
typedef xdc_runtime_Text_Node __T1_xdc_runtime_Text_nodeTab;
typedef xdc_runtime_Text_Node *__ARRAY1_xdc_runtime_Text_nodeTab;
typedef __ARRAY1_xdc_runtime_Text_nodeTab __TA_xdc_runtime_Text_nodeTab;
typedef __TA_xdc_runtime_Text_nodeTab CT__xdc_runtime_Text_nodeTab;
extern far const CT__xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__C;

/* charCnt */
typedef xdc_Int16 CT__xdc_runtime_Text_charCnt;
extern far const CT__xdc_runtime_Text_charCnt xdc_runtime_Text_charCnt__C;

/* nodeCnt */
typedef xdc_Int16 CT__xdc_runtime_Text_nodeCnt;
extern far const CT__xdc_runtime_Text_nodeCnt xdc_runtime_Text_nodeCnt__C;

/* unnamedModsLastId */
typedef xdc_UInt16 CT__xdc_runtime_Text_unnamedModsLastId;
extern far const CT__xdc_runtime_Text_unnamedModsLastId xdc_runtime_Text_unnamedModsLastId__C;

/* registryModsLastId */
typedef xdc_UInt16 CT__xdc_runtime_Text_registryModsLastId;
extern far const CT__xdc_runtime_Text_registryModsLastId xdc_runtime_Text_registryModsLastId__C;

/* visitRopeFxn */
typedef xdc_runtime_Text_VisitRopeFxn CT__xdc_runtime_Text_visitRopeFxn;
extern far const CT__xdc_runtime_Text_visitRopeFxn xdc_runtime_Text_visitRopeFxn__C;

/* visitRopeFxn2 */
typedef xdc_runtime_Text_VisitRopeFxn2 CT__xdc_runtime_Text_visitRopeFxn2;
extern far const CT__xdc_runtime_Text_visitRopeFxn2 xdc_runtime_Text_visitRopeFxn2__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Text_Module__startupDone__S( void );

/* cordText__E */

extern xdc_String xdc_runtime_Text_cordText__E( xdc_runtime_Text_CordAddr cord );

extern xdc_String xdc_runtime_Text_cordText__F( xdc_runtime_Text_CordAddr cord );
extern xdc_String xdc_runtime_Text_cordText__R( xdc_runtime_Text_CordAddr cord );

/* ropeText__E */

extern xdc_String xdc_runtime_Text_ropeText__E( xdc_runtime_Text_RopeId rope );

extern xdc_String xdc_runtime_Text_ropeText__F( xdc_runtime_Text_RopeId rope );
extern xdc_String xdc_runtime_Text_ropeText__R( xdc_runtime_Text_RopeId rope );

/* matchRope__E */

extern xdc_Int xdc_runtime_Text_matchRope__E( xdc_runtime_Text_RopeId rope, xdc_String pat, xdc_Int* lenp );

extern xdc_Int xdc_runtime_Text_matchRope__F( xdc_runtime_Text_RopeId rope, xdc_String pat, xdc_Int* lenp );
extern xdc_Int xdc_runtime_Text_matchRope__R( xdc_runtime_Text_RopeId rope, xdc_String pat, xdc_Int* lenp );

/* putLab__E */

extern xdc_Int xdc_runtime_Text_putLab__E( xdc_runtime_Types_Label* lab, xdc_Char** bufp, xdc_Int len );

extern xdc_Int xdc_runtime_Text_putLab__F( xdc_runtime_Types_Label* lab, xdc_Char** bufp, xdc_Int len );
extern xdc_Int xdc_runtime_Text_putLab__R( xdc_runtime_Types_Label* lab, xdc_Char** bufp, xdc_Int len );

/* putMod__E */

extern xdc_Int xdc_runtime_Text_putMod__E( xdc_runtime_Types_ModuleId mid, xdc_Char** bufp, xdc_Int len );

extern xdc_Int xdc_runtime_Text_putMod__F( xdc_runtime_Types_ModuleId mid, xdc_Char** bufp, xdc_Int len );
extern xdc_Int xdc_runtime_Text_putMod__R( xdc_runtime_Types_ModuleId mid, xdc_Char** bufp, xdc_Int len );

/* putSite__E */

extern xdc_Int xdc_runtime_Text_putSite__E( xdc_runtime_Types_Site* site, xdc_Char** bufp, xdc_Int len );

extern xdc_Int xdc_runtime_Text_putSite__F( xdc_runtime_Types_Site* site, xdc_Char** bufp, xdc_Int len );
extern xdc_Int xdc_runtime_Text_putSite__R( xdc_runtime_Types_Site* site, xdc_Char** bufp, xdc_Int len );

/* matchVisFxn__I */

extern xdc_Bool xdc_runtime_Text_matchVisFxn__I( xdc_Ptr p, xdc_String s );

/* printVisFxn__I */

extern xdc_Bool xdc_runtime_Text_printVisFxn__I( xdc_Ptr p, xdc_String s );

/* visitRope__I */

extern void xdc_runtime_Text_visitRope__I( xdc_runtime_Text_RopeId rope, xdc_Fxn visFxn, xdc_Ptr visState );

/* visitRope2__I */

extern void xdc_runtime_Text_visitRope2__I( xdc_runtime_Text_RopeId rope, xdc_Fxn visFxn, xdc_Ptr visState, xdc_String stack[] );

/* xprintf__I */

extern xdc_Int xdc_runtime_Text_xprintf__I( xdc_Char** bufp, xdc_String fmt, ... );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Text_Module__id xdc_runtime_Text_Module_id( void ) 
{
    return xdc_runtime_Text_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Text_Module_hasMask( void ) 
{
    return xdc_runtime_Text_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Text_Module_getMask( void ) 
{
    return xdc_runtime_Text_Module__diagsMask__C != 0 ? *xdc_runtime_Text_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Text_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Text_Module__diagsMask__C != 0) *xdc_runtime_Text_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:34; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:35; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* NUMARGS */

/* PRINTFID */

/* EventRec */
typedef xdc_IArg __T1_xdc_runtime_Log_EventRec__arg;
typedef xdc_IArg __ARRAY1_xdc_runtime_Log_EventRec__arg[8];
typedef __ARRAY1_xdc_runtime_Log_EventRec__arg __TA_xdc_runtime_Log_EventRec__arg;
struct xdc_runtime_Log_EventRec {
    xdc_runtime_Types_Timestamp64 tstamp;
    xdc_Bits32 serial;
    xdc_runtime_Types_Event evt;
    __TA_xdc_runtime_Log_EventRec__arg arg;
};

/* Event */

/* EventId */
typedef xdc_runtime_Types_RopeId xdc_runtime_Log_EventId;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Log_Module__diagsEnabled;
extern far const CT__xdc_runtime_Log_Module__diagsEnabled xdc_runtime_Log_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Log_Module__diagsIncluded;
extern far const CT__xdc_runtime_Log_Module__diagsIncluded xdc_runtime_Log_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Log_Module__diagsMask;
extern far const CT__xdc_runtime_Log_Module__diagsMask xdc_runtime_Log_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Log_Module__gateObj;
extern far const CT__xdc_runtime_Log_Module__gateObj xdc_runtime_Log_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Log_Module__gatePrms;
extern far const CT__xdc_runtime_Log_Module__gatePrms xdc_runtime_Log_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Log_Module__id;
extern far const CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Log_Module__loggerDefined;
extern far const CT__xdc_runtime_Log_Module__loggerDefined xdc_runtime_Log_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Log_Module__loggerObj;
extern far const CT__xdc_runtime_Log_Module__loggerObj xdc_runtime_Log_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Log_Module__loggerFxn0;
extern far const CT__xdc_runtime_Log_Module__loggerFxn0 xdc_runtime_Log_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Log_Module__loggerFxn1;
extern far const CT__xdc_runtime_Log_Module__loggerFxn1 xdc_runtime_Log_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Log_Module__loggerFxn2;
extern far const CT__xdc_runtime_Log_Module__loggerFxn2 xdc_runtime_Log_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Log_Module__loggerFxn4;
extern far const CT__xdc_runtime_Log_Module__loggerFxn4 xdc_runtime_Log_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Log_Module__loggerFxn8;
extern far const CT__xdc_runtime_Log_Module__loggerFxn8 xdc_runtime_Log_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Log_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Log_Module__startupDoneFxn xdc_runtime_Log_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Log_Object__count;
extern far const CT__xdc_runtime_Log_Object__count xdc_runtime_Log_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Log_Object__heap;
extern far const CT__xdc_runtime_Log_Object__heap xdc_runtime_Log_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Log_Object__sizeof;
extern far const CT__xdc_runtime_Log_Object__sizeof xdc_runtime_Log_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Log_Object__table;
extern far const CT__xdc_runtime_Log_Object__table xdc_runtime_Log_Object__table__C;

/* L_construct */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_construct;
extern far const CT__xdc_runtime_Log_L_construct xdc_runtime_Log_L_construct__C;

/* L_create */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_create;
extern far const CT__xdc_runtime_Log_L_create xdc_runtime_Log_L_create__C;

/* L_destruct */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_destruct;
extern far const CT__xdc_runtime_Log_L_destruct xdc_runtime_Log_L_destruct__C;

/* L_delete */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_delete;
extern far const CT__xdc_runtime_Log_L_delete xdc_runtime_Log_L_delete__C;

/* L_error */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_error;
extern far const CT__xdc_runtime_Log_L_error xdc_runtime_Log_L_error__C;

/* L_warning */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_warning;
extern far const CT__xdc_runtime_Log_L_warning xdc_runtime_Log_L_warning__C;

/* L_info */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_info;
extern far const CT__xdc_runtime_Log_L_info xdc_runtime_Log_L_info__C;

/* L_start */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_start;
extern far const CT__xdc_runtime_Log_L_start xdc_runtime_Log_L_start__C;

/* L_stop */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_stop;
extern far const CT__xdc_runtime_Log_L_stop xdc_runtime_Log_L_stop__C;

/* L_startInstance */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_startInstance;
extern far const CT__xdc_runtime_Log_L_startInstance xdc_runtime_Log_L_startInstance__C;

/* L_stopInstance */
typedef xdc_runtime_Log_Event CT__xdc_runtime_Log_L_stopInstance;
extern far const CT__xdc_runtime_Log_L_stopInstance xdc_runtime_Log_L_stopInstance__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Log_Module__startupDone__S( void );

/* doPrint__E */

extern void xdc_runtime_Log_doPrint__E( xdc_runtime_Log_EventRec* evRec );

extern void xdc_runtime_Log_doPrint__F( xdc_runtime_Log_EventRec* evRec );
extern void xdc_runtime_Log_doPrint__R( xdc_runtime_Log_EventRec* evRec );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module_id( void ) 
{
    return xdc_runtime_Log_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Log_Module_hasMask( void ) 
{
    return xdc_runtime_Log_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Log_Module_getMask( void ) 
{
    return xdc_runtime_Log_Module__diagsMask__C != 0 ? *xdc_runtime_Log_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Log_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Log_Module__diagsMask__C != 0) *xdc_runtime_Log_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */

/*
 *  ======== Log__epilogue.h ========
 *  Implementation of the Log_* macros
 *
 *  The implementation below relies on eight symbols defined by every module
 *  header.  Each of these symbols is a reference to a constant defined in a
 *  separate compilation unit.  The values of these constants are as follows:
 *
 *      Module__MID     - the module's ID (see Text.xs)
 *      Module__LOGOBJ  - the module's logger object
 *      Module__LOGFXN0 - the module's logger's write0 function
 *      Module__LOGFXN1 - the module's logger's write1 function 
 *      Module__LOGFXN2 - the module's logger's write2 function
 *      Module__LOGFXN4 - the module's logger's write4 function
 *      Module__LOGFXN8 - the module's logger's write8 function
 *      Module__LOGDEF  - 0 if the module has a logger, non-zero otherwise
 */

/*
 *  Define flags for compiling out all Log calls
 *
 *  The intent of these flags is to allow users to completely optimize logging
 *  out of their code even when not using whole program optimization. This is
 *  implemented by controlling the definitions of the Log macros. This will
 *  only affect code compiled with the flag(s) set, so it will not disable 
 *  logging in any precompiled libraries.
 *
 *  The DISABLE_ALL flag will have the effect of disabling all Log put, write, 
 *  print, error, warning, and info log calls. The flag just has to be defined,
 *  we give it a value of zero or one to use in the macros.
 *
 *  There are additional flags which can be used to disable all log calls
 *  "except for". We use the presence of the DISABLE_ALL flag and the presence
 *  of any ENABLE_ERROR, ENABLE_INFO, or ENABLE_WARNING flags to compute the
 *  value of ENABLE_ERROR, etc., as zero or one.
 *
 *  We ensure that all of the flags are ultimately defined and given a zero or
 *  one value. Then the macro definitions are conditional on the value of the
 *  appropriate flag.
 */

/* 
 * If DISABLE_ALL is defined, give it the value 1, and assign values to all
 * of the ENABLE flags based on whether they've been defined or not.
 */

/*
 *  ======== xdc_runtime_Log_getMask ========
 */

/*
 *  ======== xdc_runtime_Log_getRope ========
 */

/*
 *  ======== xdc_runtime_Log_getEventId ========
 */

/*
 *  ======== xdc_runtime_Log_doPut* ========
 *  The 'doPut' macros are the real implementation of the Log_put* APIs.
 *  The Log_put* macros are just stubs which point to these definitions. We do
 *  this so that we can disable the Log_put APIs but still leave their
 *  functionality available for any other Log macros which use them. 
 *  For example, if the flags DISABLE_ALL and ENABLE_ERROR were set, we'd want
 *  to disable the Log_put* macros, but not the Log_error* macros which are
 *  built on top of Log_put.
 */




   
/*
 *  ======== xdc_runtime_Log_put* ========
 *  See Log_doPut*
 */







/*
 *  ======== xdc_runtime_Log_doWrite* ========
 *  The real implementations of the Log_write* APIs. See Log_doPut* for an
 *  explanation of why we stub-out the Log_put* and Log_write* APIs.
 */

    
     
    




/*
 *  ======== xdc_runtime_Log_write* ========
 *  See Log_doWrite*
 */

 
    
    
    


    
    

    
  
/*
 *  ======== xdc_runtime_Log_print* ========
 *  Since "print" events do not have a rope, we use 0 (an invalid rope value)
 *  as the event Id and construct a Log_Event to pass to Log_put. This has the 
 *  benefit that the Log_Event is equal to just the mask: (0 | mask). For this 
 *  reason, we simply pass the 'mask' as the first argument to 'put'.
 *
 *  Each print function is mapped to a call to appropriate 'put' function.
 *  print0 -> put1
 *  print1 -> put2
 *  print2 -> print3 -> put4
 *  print3 -> put4
 *  print4 -> print6 -> put8
 *  print5 -> print6 -> put8
 *  print6 -> put8
 */

 
    
    





/*
 *  ======== xdc_runtime_Log_error* ========
 *  Log an error event
 */
 
 
        
    
    

    
/*
 *  ======== xdc_runtime_Log_warning* ========
 *  Log a warning event
 */

 
    
    
    

    
/*
 *  ======== xdc_runtime_Log_info* ========
 *  Log an informational event
 */

    
    
    

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */





/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */



/* module prefix */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */



/* module prefix */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/********************************************************************
* Copyright (C) 2003-2008 Texas Instruments Incorporated.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/* CSL Modification:
 *  The file has been modified from the AUTOGEN file for the following
 *  reasons:-
 *      a) Modified the header file includes to be RTSC compliant
 */

/*  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2006, 2008
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/** ============================================================================
 *   @file  cslr.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the macro definations for Register layer
 *
 */

/* Register layer central -- contains field-manipulation macro definitions */


/* the "expression" macros */

/* the Field MaKe macro */

/* the Field EXTract macro */

/* the Field INSert macro */


/* the "token" macros */

/* the Field MaKe (Token) macro */

/* the Field INSert (Token) macro */


/* the "raw" macros */

/* the Field MaKe (Raw) macro */

/* the Field EXTract (Raw) macro */

/* the Field INSert (Raw) macro */


/*********************************************************************
 * Copyright (C) 2005 Texas Instruments Incorporated. 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/*
 *  ======== tistdtypes.h ========
 */

/*
 * These types are also defined by other TI components.  They are bracketed
 * with _TI_STD_TYPES to avoid warnings for duplicate definition.
 *
 * You may get warnings about duplicate type definitions when using this
 * header file with earlier versions of DSP/BIOS and CSL.
 *
 * You can use the '-pds303' compiler option to suppress these warnings.
 */


/* Minimum unit = 1 byte */

/*************************************************************************** Register Overlay Structure for Bank_Registers
\**************************************************************************/
typedef struct  {
    volatile Uint32 DIR;
    volatile Uint32 OUT_DATA;
    volatile Uint32 SET_DATA;
    volatile Uint32 CLR_DATA;
    volatile Uint32 IN_DATA;
    volatile Uint32 SET_RIS_TRIG;
    volatile Uint32 CLR_RIS_TRIG;
    volatile Uint32 SET_FAL_TRIG;
    volatile Uint32 CLR_FAL_TRIG;
    volatile Uint32 INTSTAT;
} CSL_GpioBank_registersRegs;

/*************************************************************************** Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 PID;
    volatile Uint32 PCR;
    volatile Uint32 BINTEN;
    volatile Uint8 RSVD0[4];
    CSL_GpioBank_registersRegs BANK_REGISTERS[4];
} CSL_GpioRegs;

/*************************************************************************** Field Definition Macros
\**************************************************************************/

/* DIR */




/* OUT_DATA */




/* SET_DATA */




/* CLR_DATA */




/* IN_DATA */




/* SET_RIS_TRIG */




/* CLR_RIS_TRIG */




/* SET_FAL_TRIG */




/* CLR_FAL_TRIG */




/* INTSTAT */




/* PID */









/* PCR */





/* BINTEN */









//#define EVM_BOARD

/* Need to change the Pin no as per Schematics */


//SPI ports
//GPIO pins


									//GPIO pinno for BOOT_RED LED


//Common GPIO pins


/*****************************************************************************/
/* stdarg.h   v7.3.4                                                         */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/



/**
 *   @file  csl_cacheAux.h
 *
 *   @brief   
 *      This is the CACHE Auxilary Header File which exposes the various
 *      CSL Functional Layer API's to configure the CACHE Module.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2002, 2003, 2004, 2005, 2008, 2009, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/



/**
 *   @file  csl_cache.h
 *
 *   @brief   
 *      This is the CACHE Auxilary Header File which exposes the various
 *      CSL Functional Layer API's to configure the CACHE Module.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2002, 2003, 2004, 2005, 2008, 2009, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/** @defgroup CSL_CACHE_API CACHE
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 * This page describes the Functions, Data Structures, Enumerations and Macros
 * within CACHE module.
 *
 * This module uses three cache architectures, Level 1 Program (L1P), Level 1
 * Data (L1D) and Level 2 CACHE architectures, The L1P and L1D can be
 * configured as 0K, 4K, 8K, 16K, or 32K CACHE size. The L2 can be configured
 * as 32KB, 64KB, 128KB, or 256KB CACHE size. This CACHE module supports the
 * Block and Global Coherence Operations.
 *
 * @subsection References
 *    -# TMS320TCI6484 Data Sheet SPRS438 (Dec 2007) 
 *
 */
 


/*  ===========================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2006, 2008
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/** ============================================================================
 *   @file  csl.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for CSL
 *
 */



/*  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2006, 2008
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/** ============================================================================
 *   @file  csl_types.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for CSL types
 *
 */
 




typedef Int16           CSL_Uid;
typedef Int16           CSL_ModuleId;
typedef Uint32          CSL_Xio;

typedef Uint8           CSL_BitMask8;
typedef Uint16          CSL_BitMask16;
typedef Uint32          CSL_BitMask32;

typedef volatile Uint8  CSL_Reg8;
typedef volatile Uint16 CSL_Reg16;
typedef volatile Uint32 CSL_Reg32;

typedef Int16           CSL_Status;
typedef Int16           CSL_InstNum;
typedef Int16           CSL_ChaNum;

typedef unsigned long long int  CSL_Uint64;

typedef enum {
  CSL_EXCLUSIVE = 0,
  CSL_SHARED    = 1
} CSL_OpenMode;

typedef enum {
  CSL_FAIL      = 0,
  CSL_PASS      = 1
} CSL_Test;



/*  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2006, 2008
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/** ============================================================================
 *   @file  csl_error.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for ERRORs
 *
 */

/* ---- File: <csl_error.h> ---- */

/* Below Error codes are Global across all CSL Modules. */

/* Peripheral IDs */

/* Error codes individual to various modules. */

/* Error code for DMA, individual error would be assigned as
 * eg: #define CSL_E<Peripheral name>_<error code>  CSL_EDMA_FIRST - 1
 */



















void
    CSL_sysInit (
        void
);



/********************************************************************
* Copyright (C) 2003-2010 Texas Instruments Incorporated.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/* CSL Modification:
 *  The file has been modified from the AUTOGEN file for the following
 *  reasons:-
 *      a) Modified the header file includes to be RTSC compliant
 *      b) The MAR0-MAR255 have been made into an array of MAR[256]
 */


/* Minimum unit = 1 byte */

/*************************************************************************** Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 EVTFLAG[4];
    volatile Uint8 RSVD0[16];
    volatile Uint32 EVTSET[4];
    volatile Uint8 RSVD1[16];
    volatile Uint32 EVTCLR[4];
    volatile Uint8 RSVD2[48];
    volatile Uint32 EVTMASK[4];
    volatile Uint8 RSVD3[16];
    volatile Uint32 MEVTFLAG[4];
    volatile Uint8 RSVD4[16];
    volatile Uint32 EXPMASK[4];
    volatile Uint8 RSVD5[16];
    volatile Uint32 MEXPFLAG[4];
    volatile Uint8 RSVD6[20];
    volatile Uint32 INTMUX1;
    volatile Uint32 INTMUX2;
    volatile Uint32 INTMUX3;
    volatile Uint8 RSVD7[48];
    volatile Uint32 AEGMUX0;
    volatile Uint32 AEGMUX1;
    volatile Uint8 RSVD8[56];
    volatile Uint32 INTXSTAT;
    volatile Uint32 INTXCLR;
    volatile Uint32 INTDMASK;
    volatile Uint8 RSVD9[52];
    volatile Uint32 EVTASRT;
    volatile Uint8 RSVD10[65084];
    volatile Uint32 PDCCMD;
    volatile Uint8 RSVD11[8188];
    volatile Uint32 MM_REVID;
    volatile Uint8 RSVD12[57340];
    volatile Uint32 IDMA0_STAT;
    volatile Uint32 IDMA0_MASK;
    volatile Uint32 IDMA0_SOURCE;
    volatile Uint32 IDMA0_DEST;
    volatile Uint32 IDMA0_COUNT;
    volatile Uint8 RSVD13[236];
    volatile Uint32 IDMA1_STAT;
    volatile Uint8 RSVD14[4];
    volatile Uint32 IDMA1_SOURCE;
    volatile Uint32 IDMA1_DEST;
    volatile Uint32 IDMA1_COUNT;
    volatile Uint8 RSVD15[236];
    volatile Uint32 CPUARBE;
    volatile Uint32 IDMAARBE;
    volatile Uint32 SDMAARBE;
    volatile Uint8 RSVD16[4];
    volatile Uint32 ECFGARBE;
    volatile Uint8 RSVD17[236];
    volatile Uint32 ICFGMPFAR;
    volatile Uint32 ICFGMPFSR;
    volatile Uint32 ICFGMPFCR;
    volatile Uint8 RSVD18[252];
    volatile Uint32 ECFGERR;
    volatile Uint32 ECFGERRCLR;
    volatile Uint8 RSVD19[240];
    volatile Uint32 PAMAP0;
    volatile Uint32 PAMAP1;
    volatile Uint32 PAMAP2;
    volatile Uint32 PAMAP3;
    volatile Uint32 PAMAP4;
    volatile Uint32 PAMAP5;
    volatile Uint32 PAMAP6;
    volatile Uint32 PAMAP7;
    volatile Uint32 PAMAP8;
    volatile Uint32 PAMAP9;
    volatile Uint32 PAMAP10;
    volatile Uint32 PAMAP11;
    volatile Uint32 PAMAP12;
    volatile Uint32 PAMAP13;
    volatile Uint32 PAMAP14;
    volatile Uint32 PAMAP15;
    volatile Uint8 RSVD20[129728];
    volatile Uint32 L2CFG;
    volatile Uint8 RSVD21[28];
    volatile Uint32 L1PCFG;
    volatile Uint32 L1PCC;
    volatile Uint8 RSVD22[24];
    volatile Uint32 L1DCFG;
    volatile Uint32 L1DCC;
    volatile Uint8 RSVD23[4024];
    volatile Uint32 CPUARBU;
    volatile Uint32 IDMAARBU;
    volatile Uint32 SDMAARBU;
    volatile Uint32 UCARBU;
    volatile Uint32 MDMAARBU;
    volatile Uint8 RSVD24[44];
    volatile Uint32 CPUARBD;
    volatile Uint32 IDMAARBD;
    volatile Uint32 SDMAARBD;
    volatile Uint32 UCARBD;
    volatile Uint8 RSVD25[12208];
    volatile Uint32 L2WBAR;
    volatile Uint32 L2WWC;
    volatile Uint8 RSVD26[8];
    volatile Uint32 L2WIBAR;
    volatile Uint32 L2WIWC;
    volatile Uint32 L2IBAR;
    volatile Uint32 L2IWC;
    volatile Uint32 L1PIBAR;
    volatile Uint32 L1PIWC;
    volatile Uint8 RSVD27[8];
    volatile Uint32 L1DWIBAR;
    volatile Uint32 L1DWIWC;
    volatile Uint8 RSVD28[8];
    volatile Uint32 L1DWBAR;
    volatile Uint32 L1DWWC;
    volatile Uint32 L1DIBAR;
    volatile Uint32 L1DIWC;
    volatile Uint8 RSVD29[4016];
    volatile Uint32 L2WB;
    volatile Uint32 L2WBINV;
    volatile Uint32 L2INV;
    volatile Uint8 RSVD30[28];
    volatile Uint32 L1PINV;
    volatile Uint8 RSVD31[20];
    volatile Uint32 L1DWB;
    volatile Uint32 L1DWBINV;
    volatile Uint32 L1DINV;
    volatile Uint8 RSVD32[4024];
    volatile Uint32 L2EDSTAT;
    volatile Uint32 L2EDCMD;
    volatile Uint32 L2EDADDR;
    volatile Uint8 RSVD33[8];
    volatile Uint32 L2EDCPEC;
    volatile Uint32 L2EDCNEC;
    volatile Uint32 MDMAERR;
    volatile Uint32 MDMAERRCLR;
    volatile Uint8 RSVD34[8];
    volatile Uint32 L2EDCEN;
    volatile Uint8 RSVD35[976];
    volatile Uint32 L1PEDSTAT;
    volatile Uint32 L1PEDCMD;
    volatile Uint32 L1PEDADDR;
    volatile Uint8 RSVD36[7152];
    volatile Uint32 MAR[256];
    volatile Uint8 RSVD37[7168];
    volatile Uint32 L2MPFAR;
    volatile Uint32 L2MPFSR;
    volatile Uint32 L2MPFCR;
    volatile Uint8 RSVD38[500];
    volatile Uint32 L2MPPA[32];
    volatile Uint8 RSVD39[384];
    volatile Uint32 L1PMPFAR;
    volatile Uint32 L1PMPFSR;
    volatile Uint32 L1PMPFCR;
    volatile Uint8 RSVD40[564];
    volatile Uint32 L1PMPPA[16];
    volatile Uint8 RSVD41[1408];
    volatile Uint32 L1DMPFAR;
    volatile Uint32 L1DMPFSR;
    volatile Uint32 L1DMPFCR;
    volatile Uint8 RSVD42[244];
    volatile Uint32 MPLK[4];
    volatile Uint32 MPLKCMD;
    volatile Uint32 MPLKSTAT;
    volatile Uint8 RSVD43[296];
    volatile Uint32 L1DMPPA[16];
} CSL_CgemRegs;

/*************************************************************************** Field Definition Macros
\**************************************************************************/

/* EVTFLAG */



/* EVTSET */



/* EVTCLR */



/* EVTMASK */



/* MEVTFLAG */



/* EXPMASK */



/* MEXPFLAG */



/* INTMUX1 */










/* INTMUX2 */










/* INTMUX3 */










/* AEGMUX0 */






/* AEGMUX1 */






/* INTXSTAT */






/* INTXCLR */




/* INTDMASK */





/* EVTASRT */








/* PDCCMD */












/* MM_REVID */



/* IDMA0_STAT */





/* IDMA0_MASK */



/* IDMA0_SOURCE */




/* IDMA0_DEST */




/* IDMA0_COUNT */






/* IDMA1_STAT */





/* IDMA1_SOURCE */




/* IDMA1_DEST */




/* IDMA1_COUNT */








/* CPUARBE */






/* IDMAARBE */




/* SDMAARBE */




/* ECFGARBE */





/* ICFGMPFAR */



/* ICFGMPFSR */












/* ICFGMPFCR */




/* ECFGERR */







/* ECFGERRCLR */




/* PAMAP0 */




/* PAMAP1 */




/* PAMAP2 */




/* PAMAP3 */




/* PAMAP4 */




/* PAMAP5 */




/* PAMAP6 */




/* PAMAP7 */




/* PAMAP8 */




/* PAMAP9 */




/* PAMAP10 */




/* PAMAP11 */




/* PAMAP12 */




/* PAMAP13 */




/* PAMAP14 */




/* PAMAP15 */




/* L2CFG */








/* L1PCFG */




/* L1PCC */






/* L1DCFG */




/* L1DCC */






/* CPUARBU */






/* IDMAARBU */




/* SDMAARBU */




/* UCARBU */




/* MDMAARBU */







/* CPUARBD */






/* IDMAARBD */




/* SDMAARBD */




/* UCARBD */




/* L2WBAR */



/* L2WWC */




/* L2WIBAR */



/* L2WIWC */




/* L2IBAR */



/* L2IWC */




/* L1PIBAR */



/* L1PIWC */




/* L1DWIBAR */



/* L1DWIWC */




/* L1DWBAR */



/* L1DWWC */




/* L1DIBAR */



/* L1DIWC */




/* L2WB */




/* L2WBINV */




/* L2INV */




/* L1PINV */




/* L1DWB */




/* L1DWBINV */




/* L1DINV */




/* L2EDSTAT */














/* L2EDCMD */











/* L2EDADDR */






/* L2EDCPEC */




/* L2EDCNEC */




/* MDMAERR */







/* MDMAERRCLR */




/* L2EDCEN */








/* L1PEDSTAT */










/* L1PEDCMD */










/* L1PEDADDR */





/* MAR0 */







/* MAR1 */







/* MAR2 */







/* MAR3 */







/* MAR4 */







/* MAR5 */







/* MAR6 */







/* MAR7 */







/* MAR8 */







/* MAR9 */







/* MAR10 */







/* MAR11 */







/* MAR12 */







/* MAR13 */







/* MAR14 */







/* MAR15 */







/* MAR16 */







/* MAR17 */







/* MAR18 */







/* MAR19 */







/* MAR20 */







/* MAR21 */







/* MAR22 */







/* MAR23 */







/* MAR24 */







/* MAR25 */







/* MAR26 */







/* MAR27 */







/* MAR28 */







/* MAR29 */







/* MAR30 */







/* MAR31 */







/* MAR32 */







/* MAR33 */







/* MAR34 */







/* MAR35 */







/* MAR36 */







/* MAR37 */







/* MAR38 */







/* MAR39 */







/* MAR40 */







/* MAR41 */







/* MAR42 */







/* MAR43 */







/* MAR44 */







/* MAR45 */







/* MAR46 */







/* MAR47 */







/* MAR48 */







/* MAR49 */







/* MAR50 */







/* MAR51 */







/* MAR52 */







/* MAR53 */







/* MAR54 */







/* MAR55 */







/* MAR56 */







/* MAR57 */







/* MAR58 */







/* MAR59 */







/* MAR60 */







/* MAR61 */







/* MAR62 */







/* MAR63 */







/* MAR64 */







/* MAR65 */







/* MAR66 */







/* MAR67 */







/* MAR68 */







/* MAR69 */







/* MAR70 */







/* MAR71 */







/* MAR72 */







/* MAR73 */







/* MAR74 */







/* MAR75 */







/* MAR76 */







/* MAR77 */







/* MAR78 */







/* MAR79 */







/* MAR80 */







/* MAR81 */







/* MAR82 */







/* MAR83 */







/* MAR84 */







/* MAR85 */







/* MAR86 */







/* MAR87 */







/* MAR88 */







/* MAR89 */







/* MAR90 */







/* MAR91 */







/* MAR92 */







/* MAR93 */







/* MAR94 */







/* MAR95 */







/* MAR96 */







/* MAR97 */







/* MAR98 */







/* MAR99 */







/* MAR100 */







/* MAR101 */







/* MAR102 */







/* MAR103 */







/* MAR104 */







/* MAR105 */







/* MAR106 */







/* MAR107 */







/* MAR108 */







/* MAR109 */







/* MAR110 */







/* MAR111 */







/* MAR112 */







/* MAR113 */







/* MAR114 */







/* MAR115 */







/* MAR116 */







/* MAR117 */







/* MAR118 */







/* MAR119 */







/* MAR120 */







/* MAR121 */







/* MAR122 */







/* MAR123 */







/* MAR124 */







/* MAR125 */







/* MAR126 */







/* MAR127 */







/* MAR128 */







/* MAR129 */







/* MAR130 */







/* MAR131 */







/* MAR132 */







/* MAR133 */







/* MAR134 */







/* MAR135 */







/* MAR136 */







/* MAR137 */







/* MAR138 */







/* MAR139 */







/* MAR140 */







/* MAR141 */







/* MAR142 */







/* MAR143 */







/* MAR144 */







/* MAR145 */







/* MAR146 */







/* MAR147 */







/* MAR148 */







/* MAR149 */







/* MAR150 */







/* MAR151 */







/* MAR152 */







/* MAR153 */







/* MAR154 */







/* MAR155 */







/* MAR156 */







/* MAR157 */







/* MAR158 */







/* MAR159 */







/* MAR160 */







/* MAR161 */







/* MAR162 */







/* MAR163 */







/* MAR164 */







/* MAR165 */







/* MAR166 */







/* MAR167 */







/* MAR168 */







/* MAR169 */







/* MAR170 */







/* MAR171 */







/* MAR172 */







/* MAR173 */







/* MAR174 */







/* MAR175 */







/* MAR176 */







/* MAR177 */







/* MAR178 */







/* MAR179 */







/* MAR180 */







/* MAR181 */







/* MAR182 */







/* MAR183 */







/* MAR184 */







/* MAR185 */







/* MAR186 */







/* MAR187 */







/* MAR188 */







/* MAR189 */







/* MAR190 */







/* MAR191 */







/* MAR192 */







/* MAR193 */







/* MAR194 */







/* MAR195 */







/* MAR196 */







/* MAR197 */







/* MAR198 */







/* MAR199 */







/* MAR200 */







/* MAR201 */







/* MAR202 */







/* MAR203 */







/* MAR204 */







/* MAR205 */







/* MAR206 */







/* MAR207 */







/* MAR208 */







/* MAR209 */







/* MAR210 */







/* MAR211 */







/* MAR212 */







/* MAR213 */







/* MAR214 */







/* MAR215 */







/* MAR216 */







/* MAR217 */







/* MAR218 */







/* MAR219 */







/* MAR220 */







/* MAR221 */







/* MAR222 */







/* MAR223 */







/* MAR224 */







/* MAR225 */







/* MAR226 */







/* MAR227 */







/* MAR228 */







/* MAR229 */







/* MAR230 */







/* MAR231 */







/* MAR232 */







/* MAR233 */







/* MAR234 */







/* MAR235 */







/* MAR236 */







/* MAR237 */







/* MAR238 */







/* MAR239 */







/* MAR240 */







/* MAR241 */







/* MAR242 */







/* MAR243 */







/* MAR244 */







/* MAR245 */







/* MAR246 */







/* MAR247 */







/* MAR248 */







/* MAR249 */







/* MAR250 */







/* MAR251 */







/* MAR252 */







/* MAR253 */







/* MAR254 */







/* MAR255 */







/* L2MPFAR */



/* L2MPFSR */













/* L2MPFCR */




/* L2MPPA */



















/* L1PMPFAR */



/* L1PMPFSR */













/* L1PMPFCR */




/* L1PMPPA */



















/* L1DMPFAR */



/* L1DMPFSR */













/* L1DMPFCR */




/* MPLK */



/* MPLKCMD */






/* MPLKSTAT */





/* L1DMPPA */



















/**
 *   @file  soc.h
 *
 *   @brief
 *      This file contains SOC specific defintions.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2009, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


/*  ============================================================================
 *  Copyright (c) Texas Instruments Incorporated 2002-2012
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


/* CSL Modification:
 *  The file has been modified from the AUTOGEN file for the following
 *  reasons:-
 *      a) Header files are included as per RTSC guidelines
 */


/**************************************************************************
* Memory Region Descriptions for the device
**************************************************************************/
/**************************************************************************
* Peripheral Instance counts
**************************************************************************/


/*************************************************************************** Peripheral Instance definitions.
\**************************************************************************/

/** @brief Instance number of internal RAM */

/** @brief Instance number of CGEM_0_5_LOCAL_REGISTERS */

/** @brief Peripheral Instance numbers of CP_TRACER */

/** @brief Peripheral Instance for AIF */

/** @brief Peripheral Instance for PA_SS */

/** @brief Peripheral Instance of Timer 64p */
/** @brief Instance number of PLL controller*/

/** @brief Peripheral Instance for GPIO */

/** @brief Peripheral Instance for SMARTREFLEX */

/** @brief Instance number of PSC controller */

/** @brief Instance number of MPU */

/** @brief Instance number of DEBUG_SS */

/** @brief Instance number of GEM_DEBUG */

/** @brief Instance number of SEC_CTL */

/** @brief Instance number of SEC_KEY_MGR */

/** @brief Peripheral Instance for I2C */

/** @brief Peripheral Instance of UART */

/** @brief Peripheral Instance numbers of CP_INTC */

/** @brief Peripheral Instance of BOOT_CFG */

/** @brief Peripheral Instance of SEMAPHORE */

/** @brief Peripheral Instance of TPCC instances */
/* Same as above - name changed to match data manuals */

/** @brief Peripheral Instance of TPTC instances */
/* Same as above - name changed to match data manuals */

/** @brief Peripheral Instance of SRIO */

/** @brief Peripheral Instance of QM_SS */

/** @brief Peripheral Instance of MSMC */

/** @brief Peripheral Instance of DSP0_GLOBAL */

/** @brief Peripheral Instance of DSP1_GLOBAL */

/** @brief Peripheral Instance of DSP2_GLOBAL */

/** @brief Peripheral Instance of DSP3_GLOBAL */

/** @brief Peripheral Instance of DSP4_GLOBAL */

/** @brief Peripheral Instance of DSP5_GLOBAL */

/** @brief Peripheral Instance of DSP6_GLOBAL */

/** @brief Peripheral Instance of DSP7_GLOBAL */

/** @brief Peripheral Instance of BOOT */

/** @brief Peripheral Instance of SPI */

/** @brief Peripheral Instance of TSIP */

/** @brief Peripheral Instance for DDR3 */

/** @brief Instance number of MCM */

/** @brief Peripheral Instance for PCIE_SS */

/** @brief Instance number of device configuration module */

/* PSC Definitions */
/* PSC Power Domain Assignment Definitions */

/* PSC LPSC Module Assignment Definitions */


/** @TPCC0 Configuration*/

/* Same as above - name changed to match data manuals */

/** @TPCC1 Configuration*/

/* Same as above - name changed to match data manuals */

/** @TPCC2 Configuration*/

/* Same as above - name changed to match data manuals */
/**************************************************************************
* Peripheral Base Address-0.1.6
**************************************************************************/

/**************************************************************************
* CHIP LEVEL INTC0 EVENT INPUT-0.1.10
**************************************************************************/



/**************************************************************************
* CHIP LEVEL INTC0 EVENT DEFINITION
**************************************************************************/
/* Same as above - name changed to match data manuals */
/* Same as above - name changed to match data manuals */
/* Same as above - name changed to match data manuals */
/**************************************************************************
* CHIP LEVEL INTC1 EVENT INPUT-0.1.10
**************************************************************************/



/**************************************************************************
* CHIP LEVEL INTC1 EVENT DEFINITION
**************************************************************************/


/**************************************************************************
* CHIP LEVEL INTC2 EVENT INPUT
**************************************************************************/



/**************************************************************************
* CHIP LEVEL INTC2 EVENT DEFINITION
**************************************************************************/

/**************************************************************************
* CHIP LEVEL INTC3 EVENT INPUT
**************************************************************************/



/**************************************************************************
* CHIP LEVEL INTC3 EVENT DEFINITION
**************************************************************************/

/**************************************************************************
* TPCC0 (CPU_2) EVENT INPUT
**************************************************************************/


/**************************************************************************
* EDMA3CC0 (CPU/2) EVENT INPUT
**************************************************************************/


/**************************************************************************
* TPCC0 (CPU_2) EVENT DEFINITION
**************************************************************************/

/**************************************************************************
* EDMA3CC0 (CPU_2) EVENT DEFINITION
**************************************************************************/

/**************************************************************************
* TPCC1 (CPU_3) EVENT INPUT
**************************************************************************/



/**************************************************************************
* TPCC1 (CPU_3) EVENT DEFINITION
**************************************************************************/

/* Same as above - name changed to match data manuals */
/**************************************************************************
* EDMA3CC1 (CPU/3) EVENT INPUT
**************************************************************************/


/**************************************************************************
* EDMA3CC1 (CPU_3) EVENT DEFINITION
**************************************************************************/


/**************************************************************************
* TPCC2 (CPU_3) EVENT INPUT
**************************************************************************/



/**************************************************************************
* TPCC2 (CPU_3) EVENT DEFINITION
**************************************************************************/

/* Same as above - name changed to match data manuals */
/**************************************************************************
* EDMA3CC2 (CPU/3) EVENT INPUT
**************************************************************************/


/**************************************************************************
* EDMA3CC2 (CPU_3) EVENT DEFINITION
**************************************************************************/


/**************************************************************************
* MCM EVENT INPUT
**************************************************************************/



/**************************************************************************
* MCM EVENT DEFINITION
**************************************************************************/


/**************************************************************************
* GEM EVENT INPUT
**************************************************************************/



/**************************************************************************
* GEM EVENT DEFINITION
**************************************************************************/
/* Same as above - name changed to match data manuals */
/* Same as above - name changed to match data manuals */
/* Same as above - name changed to match data manuals */
/* Same as above - name changed to match data manuals */

/**************************************************************************
* EOI Values
**************************************************************************/


/****************************************************************************** Static inline definition
\*****************************************************************************/




/**
@defgroup CSL_CACHE_SYMBOL  CACHE Symbols Defined
@ingroup CSL_CACHE_API
*/
/**
@defgroup CSL_CACHE_ENUM  CACHE Enumerated Data Types
@ingroup CSL_CACHE_API
*/
/**
@defgroup CSL_CACHE_FUNCTION  CACHE Functions
@ingroup CSL_CACHE_API
*/


/**
@addtogroup CSL_CACHE_SYMBOL
@{
*/
/** L2 Line Size */
/** L1D Line Size */
/** L1P Line Size */

/** Handle to the CGEM Register Layer */

/** Cache Round to Line size */        
/**
@}
*/

/******************************************************************************* global macro declarations
\******************************************************************************/

/** @addtogroup CSL_CACHE_ENUM
 @{ */
/** @brief Enumeration for Cache wait flags
 *
 *  This is used for specifying whether the cache operations should block till
 *  the desired operation is complete.
 */
typedef enum 
{
    /** No blocking, the call exits after programmation of the 
     *  control registers 
     */
    CACHE_NOWAIT = 0,
                         
    /** Blocking Call, the call exits after the relevant cache 
     *  status registers indicate completion. For block coherence
     *  this waits on the Word count register to be come 0.
     */
    CACHE_WAIT   = 1,

    /** Blocking Call, For block coherence this uses the MFENCE to 
     * wait for completion
     */
    CACHE_FENCE_WAIT  = 2    
}CACHE_Wait;

/** @brief Enumeration for L1 (P or D) Sizes */

typedef enum { 
    /** No Cache    */                 
    CACHE_L1_0KCACHE  = 0,
    /** 4KB Cache   */                               
    CACHE_L1_4KCACHE  = 1,
    /** 8KB Cache   */                 
    CACHE_L1_8KCACHE  = 2,
    /** 16KB Cache  */                                 
    CACHE_L1_16KCACHE = 3,
    /** 32KB Cache  */                
    CACHE_L1_32KCACHE = 4,
    /** MAX Cache Size */                
    CACHE_L1_MAXIM1   = 5,
    /** MAX Cache Size */                
    CACHE_L1_MAXIM2   = 6,      
    /** MAX Cache Size */                
    CACHE_L1_MAXIM3   = 7          
} CACHE_L1Size;

/** @brief Enumeration for L2 Sizes */

    /** For devices that have maximum caches less 
     * than the defined values, setting a higher value 
     * will map to maximum cache 
     */
typedef enum { 
    /** No Cache     */
    CACHE_0KCACHE   = 0,  
    /** 32KB Cache   */
    CACHE_32KCACHE  = 1, 
    /** 64KB Cache   */
    CACHE_64KCACHE  = 2, 
    /** 128KB Cache  */
    CACHE_128KCACHE = 3,
    /** 256KB Cache  */
    CACHE_256KCACHE = 4,
    /** 512KB Cache  */
    CACHE_512KCACHE = 5,
    /* 1024KB Cache  */
    CACHE_1024KCACHE = 6 
} CACHE_L2Size; 

/**
@}
*/



/** @addtogroup CSL_CACHE_FUNCTION
 @{ */

/** ============================================================================
 *   @n@b CACHE_enableCaching
 *
 *   @b Description
 *   @n This function enables caching for a specific memory region. 
 *
 *   @b Arguments
     @verbatim
          mar      Memory region for which cache is to be enabled.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n Memory region is now cacheable.
 *
 *   @b Writes
 *   @n CGEM_MAR0_PC=1
 *
 *   @b Example
 *   @verbatim
        CACHE_enableCaching (20);

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_enableCaching  (Uint8 mar)
{
    ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) = ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) & ~(0x00000001u)) | (((1) << (0x00000000u)) & (0x00000001u)));
}

/** ============================================================================
 *   @n@b CACHE_disableCaching
 *
 *   @b Description
 *   @n This function disables caching for a specific memory region. 
 *
 *   @b Arguments
     @verbatim
          mar      Memory region for which cache is to be disabled.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n Memory region is now *not* cacheable.
 *
 *   @b Writes
 *   @n CGEM_MAR0_PC=0
 *
 *   @b Example
 *   @verbatim
        CACHE_disableCaching (20);

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_disableCaching (Uint8 mar)
{
    ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) = ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) & ~(0x00000001u)) | (((0) << (0x00000000u)) & (0x00000001u)));
}

/** ============================================================================
 *   @n@b CACHE_getMemRegionInfo
 *
 *   @b Description
 *   @n This function is used to get memory region information.
 *
 *   @b Arguments
     @verbatim
          mar      Memory region for which the information is required.
          pcx      Is address cacheable in external cache (MSMC)
          pfx      Is address prefetchable 
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Reads
 *   @n CGEM_MAR0_PCX, CGEM_MAR0_PFX
 *
 *   @b Example
 *   @verbatim
        
        Uint8 pcx;
        Uint8 pfx;

        // Get the memory region information for 20
        CACHE_getMemRegionInfo (20, &pcx, &pfx);

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_getMemRegionInfo (Uint8 mar, Uint8* pcx, Uint8* pfx)
{
    Uint32 value = ((CSL_CgemRegs *)(0x01800000))->MAR[mar];

    *pcx = (((value) & (0x00000004u)) >> (0x00000002u));
    *pfx = (((value) & (0x00000008u)) >> (0x00000003u));
}

/** ============================================================================
 *   @n@b CACHE_setMemRegionInfo
 *
 *   @b Description
 *   @n This function is used to set memory region information.
 *
 *   @b Arguments
     @verbatim
          mar      Memory region for which the information is required.
          pcx      Is address cacheable in external cache (MSMC)
          pfx      Is address prefetchable 
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Writes
 *   @n CGEM_MAR0_PCX, CGEM_MAR0_PFX
 *
 *   @b Example
 *   @verbatim
        
        Uint8 pcx;
        Uint8 pfx;

        // Get the memory region information for 20
        CACHE_getMemRegionInfo (20, &pcx, &pfx);
        ...
        // Ensure Memory Region 20 is not prefetchable.
        CACHE_setMemRegionInfo(20, pcx, 0);
     @endverbatim
 * =============================================================================
 */
static inline void CACHE_setMemRegionInfo (Uint8 mar, Uint8 pcx, Uint8 pfx)
{
    ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) = ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) & ~(0x00000004u)) | (((pcx) << (0x00000002u)) & (0x00000004u)));
    ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) = ((((CSL_CgemRegs *)(0x01800000))->MAR[mar]) & ~(0x00000008u)) | (((pfx) << (0x00000003u)) & (0x00000008u)));
}

/** ============================================================================
 *   @n@b CACHE_setL1DSize
 *
 *   @b Description
 *   @n This function is used to set the L1 Data Cache Size.  
 *
 *   @b Arguments
      @verbatim
          newSize      Cache Size to be configured.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CGEM_L1DCFG_L1DMODE
 *
 *   @b Example
 *   @verbatim
        
        CACHE_setL1DSize(1); // Configure 4K Cache Size

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_setL1DSize (CACHE_L1Size newSize)
{
    ((((CSL_CgemRegs *)(0x01800000))->L1DCFG) = ((((CSL_CgemRegs *)(0x01800000))->L1DCFG) & ~(0x00000007u)) | (((newSize) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_getL1DSize
 *
 *   @b Description
 *   @n This function is used to get the L1 Data Cache Size.  
 *
 *   @b Arguments
 *   @n None
 * 
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CGEM_L1DCFG_L1DMODE
 *
 *   @b Example
 *   @verbatim
        CACHE_L1Size cacheSize;
        
        cacheSize = CACHE_getL1DSize();

     @endverbatim
 * =============================================================================
 */
static inline CACHE_L1Size CACHE_getL1DSize (void)
{
    return (CACHE_L1Size)(((((CSL_CgemRegs *)(0x01800000))->L1DCFG) & (0x00000007u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CACHE_freezeL1D
 *
 *   @b Description
 *   @n This function is used to freeze the L1D cache.  
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CGEM_L1DCC_OPER=1
 *
 *   @b Example
 *   @verbatim
        
        CACHE_freezeL1D();

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_freezeL1D(void)
{
    /* Set the Freeze Mode Enabled bit. */
    ((((CSL_CgemRegs *)(0x01800000))->L1DCC) = ((((CSL_CgemRegs *)(0x01800000))->L1DCC) & ~(0x00000007u)) | (((1) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_unfreezeL1D
 *
 *   @b Description
 *   @n This function is used to unfreeze the L1D cache.  
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CGEM_L1DCC_OPER=0
 *
 *   @b Example
 *   @verbatim
        
        CACHE_unfreezeL1D();

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_unfreezeL1D(void)
{
    /* Reset the Freeze Mode Enabled bit. */
    ((((CSL_CgemRegs *)(0x01800000))->L1DCC) = ((((CSL_CgemRegs *)(0x01800000))->L1DCC) & ~(0x00000007u)) | (((0) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_getPrevL1DMode
 *
 *   @b Description
 *   @n This function is used get the previous operating state of the L1D cache 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CGEM_L1DCC_POPER
 *
 *   @b Example
 *   @verbatim
        Uint32 prev;
        
        prev = CACHE_getPrevL1DMode();

     @endverbatim
 * =============================================================================
 */
static inline Uint32 CACHE_getPrevL1DMode(void)
{
    return (((((CSL_CgemRegs *)(0x01800000))->L1DCC) & (0x00070000u)) >> (0x00000010u));    
}

/** ============================================================================
 *   @n@b CACHE_invAllL1dWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D global invalidate operation
 *      to complete. This API should be used only if the CACHE_invAllL1d was called
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_invAllL1d(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CGEM_L1DINV_I=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_invAllL1d(CACHE_NOWAIT); // Invalidate the L1D cache
        ...        
        CACHE_invAllL1dWait();        // Wait for the invalidate operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invAllL1dWait (void)
{
    /* Wait for the Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1DINV) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);
}

/** ============================================================================
 *   @n@b CACHE_invAllL1d
 *
 *   @b Description
 *   @n This function is used to globally invalidate the L1D cache.  
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The L1D Cache is being invalidated. 
 *
 *   @b Writes
 *   @n CGEM_L1DINV_I=1
 *
 *   @b Example
 *   @verbatim
        
        CACHE_invAllL1d(CACHE_WAIT); // Invalidate the L1D cache 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invAllL1d (CACHE_Wait wait)
{
    /* Invalidate the Cache Line. */
    ((((CSL_CgemRegs *)(0x01800000))->L1DINV) = ((((CSL_CgemRegs *)(0x01800000))->L1DINV) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu))); 
    
    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_invAllL1dWait();
}

/** ============================================================================
 *   @n@b CACHE_wbAllL1dWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D writeback operation
 *      to complete. This API should be used only if the CACHE_wbAllL1d was called
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbAllL1d(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The L1D Dirty lines are written back
 *
 *   @b Reads
 *   @n CGEM_L1DWB_C=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_wbAllL1d(CACHE_NOWAIT); // Writeback the L1D cache
        ...        
        CACHE_wbAllL1dWait();        // Wait for the writeback operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbAllL1dWait (void)
{
    /* Wait for the Writeback operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1DWB) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);
}

/** ============================================================================
 *   @n@b CACHE_wbAllL1d
 *
 *   @b Description
 *   @n This function is used to writeback the dirty lines of the L1D Cache  
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The dirty lines of the L1D Cache are being written back 
 *
 *   @b Writes
 *   @n CGEM_L1DWB_C=1
 *
 *   @b Example
 *   @verbatim
        
        CACHE_wbAllL1d(CACHE_WAIT); // Writeback the Dirty Lines of the L1D cache 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbAllL1d (CACHE_Wait wait)
{
    /* Writeback the Cache Line. */
    ((((CSL_CgemRegs *)(0x01800000))->L1DWB) = ((((CSL_CgemRegs *)(0x01800000))->L1DWB) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu))); 
    
    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_wbAllL1dWait();
}

/** ============================================================================
 *   @n@b CACHE_wbInvAllL1dWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D writeback invalidate operation
 *      to complete. This API should be used only if the CACHE_wbInvAllL1d was called
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbInvAllL1d(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The L1D Dirty lines are written back
 *
 *   @b Reads
 *   @n CGEM_L1DWBINV_C=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_wbInvAllL1d(CACHE_NOWAIT); // Invalidate/Writeback the L1D cache
        ...        
        CACHE_wbInvAllL1dWait();        // Wait for the Invalidate/Writeback operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvAllL1dWait (void)
{
    /* Wait for the Invalidate Writeback operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1DWBINV) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);
}

/** ============================================================================
 *   @n@b CACHE_wbInvAllL1d
 *
 *   @b Description
 *   @n This function is used to invalidate and writeback the dirty lines of the 
 *      L1D Cache  
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Invalidates and Writebacks the dirty lines of the L1D Cache 
 *
 *   @b Writes
 *   @n CGEM_L1DWBINV_C=1
 *
 *   @b Example
 *   @verbatim
        
        CACHE_wbInvAllL1d(CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void  CACHE_wbInvAllL1d (CACHE_Wait wait)
{
    /* Invalidate and writeback the cache line. */
    ((((CSL_CgemRegs *)(0x01800000))->L1DWBINV) = ((((CSL_CgemRegs *)(0x01800000))->L1DWBINV) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu))); 
    
    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_wbInvAllL1dWait();     
}

/** ============================================================================
 *   @n@b CACHE_invL1dWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D invalidate block operation to 
 *      complete. This API should be used only if the CACHE_invL1d was called 
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_invL1d(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The L1D Block Cache is invalidated. 
 *
 *   @b Reads
 *   @n CGEM_L1DIWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_invL1d((void *)ptr_buffer, 128, CACHE_NOWAIT);
        ...        
        CACHE_invL1dWait();        // Wait for the Invalidate/Writeback operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invL1dWait (void)
{
    /* Wait for the Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1DIWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);
}

/** ============================================================================
 *   @n@b CACHE_invL1d
 *
 *   @b Description
 *   @n This function is used to invalidate a block in the L1D Cache. Although
 *      the block size can be specified in the number of bytes, the cache
 *      controller operates on whole cache lines. To prevent unintended behavior
 *      "blockPtr" should be aligned on the cache line size and "byteCnt" should
 *      be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be invalidated
          byteCnt       Size of the block to be invalidated.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the blockPtr are being invalidated  
 *
 *   @b Writes
 *   @n CGEM_L1DIBAR_ADDR,CGEM_L1DIWC_WC
 *
 *   @b Example
 *   @verbatim
        
        Uint8* ptr_buffer;
                
        // Invalidate 128 bytes of the buffer.
        CACHE_invL1d((void *)ptr_buffer, 128, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invL1d 
(
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length */
    ((CSL_CgemRegs *)(0x01800000))->L1DIBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));
    ((CSL_CgemRegs *)(0x01800000))->L1DIWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));

    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_invL1dWait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_wbL1dWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D writeback block operation to 
 *      complete. This API should be used only if the CACHE_wbL1d was called 
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbL1d(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The dirty lines of the L1D Block Cache have been written back. 
 *
 *   @b Reads
 *   @n CGEM_L1DWWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_wbL1d((void *)ptr_buffer, 128, CACHE_NOWAIT);
        ...        
        CACHE_wbL1dWait();        // Wait for the writeback operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbL1dWait (void)
{
    /* Wait for the Writeback operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1DWWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);    
}

/** ============================================================================
 *   @n@b CACHE_wbL1d
 *
 *   @b Description
 *   @n This function is used to writeback the dirty lines of the block address.
 *      Although the block size can be specified in the number of bytes, the cache
 *      controller operates on whole cache lines. To prevent unintended behavior
 *      "blockPtr" should be aligned on the cache line size and "byteCnt" should
 *      be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be written back
          byteCnt       Size of the block to be written back.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the blockPtr are being written back  
 *
 *   @b Writes
 *   @n CGEM_L1DWBAR_ADDR,CGEM_L1DWWC_WC
 *
 *   @b Example
 *   @verbatim
        
        Uint8* ptr_buffer;
                
        // Writeback 128 bytes of the buffer.
        CACHE_wbL1d((void *)ptr_buffer, 128, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbL1d 
(
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length */
    ((CSL_CgemRegs *)(0x01800000))->L1DWBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));
    ((CSL_CgemRegs *)(0x01800000))->L1DWWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));

    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_wbL1dWait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_wbInvL1dWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D invalidate/writeback block 
 *      operation to complete. This API should be used only if the CACHE_wbInvL1d 
 *      was called with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbInvL1d(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The dirty lines of the L1D Block Cache have been written back and the cache
 *       contents pointed to by the block address are also invalidated.
 *
 *   @b Reads
 *   @n CGEM_L1DWIWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_wbInvL1d((void *)ptr_buffer, 128, CACHE_NOWAIT);
        ...        
        CACHE_wbInvL1dWait();        // Wait for the operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvL1dWait (void)
{
    /* Wait for the Block Writeback/Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1DWIWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);
}

/** ============================================================================
 *   @n@b CACHE_wbInvL1d
 *
 *   @b Description
 *   @n This function is used to invalidate and writeback the dirty lines 
 *      of the block address.  Although the block size can be specified in 
 *      the number of bytes, the cache controller operates on whole cache lines. 
 *      To prevent unintended behavior "blockPtr" should be aligned on the 
 *      cache line size and "byteCnt" should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be invalidated/written back
          byteCnt       Size of the block to be invalidated/written back.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the blockPtr are being invalidated and the dirty lines are
 *       written back  
 *
 *   @b Writes
 *   @n CGEM_L1DWIBAR_ADDR,CGEM_L1DWIWC_WC
 *
 *   @b Example
 *   @verbatim
        
        Uint8* ptr_buffer;
                
        // Writeback/Invalidate 128 bytes of the buffer.
        CACHE_wbInvL1d((void *)ptr_buffer, 128, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvL1d 
(
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length */
    ((CSL_CgemRegs *)(0x01800000))->L1DWIBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));
    ((CSL_CgemRegs *)(0x01800000))->L1DWIWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));
 
    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_wbInvL1dWait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_setL1PSize
 *
 *   @b Description
 *   @n This function is used to set the L1P Cache Size.  
 *
 *   @b Arguments
      @verbatim
          newSize      Cache Size to be configured.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CGEM_L1PCFG_L1PMODE
 *
 *   @b Example
 *   @verbatim
        
        CACHE_setL1PSize(1); // Configure 4K Cache Size

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_setL1PSize (CACHE_L1Size newSize)
{
    ((((CSL_CgemRegs *)(0x01800000))->L1PCFG) = ((((CSL_CgemRegs *)(0x01800000))->L1PCFG) & ~(0x00000007u)) | (((newSize) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_getL1PSize
 *
 *   @b Description
 *   @n This function is used to get the L1P Cache Size.  
 *
 *   @b Arguments
 *   @n None
 * 
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CGEM_L1PCFG_L1PMODE
 *
 *   @b Example
 *   @verbatim
        CACHE_L1Size cacheSize;
        
        cacheSize = CACHE_getL1PSize();

     @endverbatim
 * =============================================================================
 */
static inline CACHE_L1Size CACHE_getL1PSize (void)
{
    return (CACHE_L1Size)(((((CSL_CgemRegs *)(0x01800000))->L1PCFG) & (0x00000007u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CACHE_freezeL1P
 *
 *   @b Description
 *   @n This function is used to freeze the L1P cache.  
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CGEM_L1PCC_OPER=1
 *
 *   @b Example
 *   @verbatim
        
        CACHE_freezeL1P();

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_freezeL1P(void)
{
    /* Set the Freeze Mode Enabled bit. */
    ((((CSL_CgemRegs *)(0x01800000))->L1PCC) = ((((CSL_CgemRegs *)(0x01800000))->L1PCC) & ~(0x00000007u)) | (((1) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_unfreezeL1P
 *
 *   @b Description
 *   @n This function is used to unfreeze the L1D cache.  
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n CGEM_L1PCC_OPER=0
 *
 *   @b Example
 *   @verbatim
        
        CACHE_unfreezeL1D();

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_unfreezeL1P(void)
{
    /* Reset the Freeze Mode Enabled bit. */
    ((((CSL_CgemRegs *)(0x01800000))->L1PCC) = ((((CSL_CgemRegs *)(0x01800000))->L1PCC) & ~(0x00000007u)) | (((0) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_getPrevL1PMode
 *
 *   @b Description
 *   @n This function is used get the previous operating state of the L1P cache 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n CGEM_L1PCC_POPER
 *
 *   @b Example
 *   @verbatim
        Uint32  prev;
        
        prev = CACHE_getPrevL1PMode();

     @endverbatim
 * =============================================================================
 */
static inline Uint32 CACHE_getPrevL1PMode(void)
{
    return (((((CSL_CgemRegs *)(0x01800000))->L1PCC) & (0x00070000u)) >> (0x00000010u));    
}

/** ============================================================================
 *   @n@b CACHE_invL1pWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1D invalidate block operation to 
 *      complete. This API should be used only if the CACHE_invL1p was called 
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_invL1p(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The L1D Block Cache is invalidated. 
 *
 *   @b Reads
 *   @n CGEM_L1PIWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_invL1p((void *)&foo, 128, CACHE_NOWAIT);
        ...        
        CACHE_invL1pWait();        // Wait for the Invalidate operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invL1pWait (void)
{
    /* Wait for the Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1PIWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);    
}

/** ============================================================================
 *   @n@b CACHE_invL1p
 *
 *   @b Description
 *   @n This function is used to invalidate the L1P Cache pointed by the block 
 *      address. Although the block size can be specified in the number of bytes, 
 *      the cache controller operates on whole cache lines. To prevent unintended 
 *      behavior "blockPtr" should be aligned on the cache line size and "byteCnt" 
 *      should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be invalidated
          byteCnt       Size of the block to be invalidated.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the blockPtr are being invalidated
 *
 *   @b Writes
 *   @n CGEM_L1PIBAR_ADDR,CGEM_L1PIWC_WC
 *
 *   @b Example
 *   @verbatim
 
        // Invalidate the 128 bytes of the function 'foo'
        CACHE_invL1p((void *)&foo, 128, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invL1p 
(
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length which is to be invalidated */
    ((CSL_CgemRegs *)(0x01800000))->L1PIBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));
    ((CSL_CgemRegs *)(0x01800000))->L1PIWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));

    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_invL1pWait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_invAllL1pWait
 *
 *   @b Description
 *   @n This function is used to wait for the L1P invalidate operation to complete. 
 *      This API should be used only if the CACHE_invAllL1p was called with the 
 *      CACHE_NOWAIT argument.  
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_invAllL1p(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The L1P Cache is invalidated. 
 *
 *   @b Reads
 *   @n CGEM_L1PINV_I=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_invAllL1p(CACHE_NOWAIT);
        ...        
        CACHE_invAllL1pWait();        // Wait for the Invalidate operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invAllL1pWait (void)
{
    /* Wait for the Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L1PINV) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);    
}

/** ============================================================================
 *   @n@b CACHE_invAllL1p
 *
 *   @b Description
 *   @n This function is used to invalidate the entire L1P Cache 
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The entire L1P cache is being invalidated.  
 *
 *   @b Writes
 *   @n CGEM_L1PINV_I=1
 *
 *   @b Example
 *   @verbatim
         
        CACHE_invAllL1p(CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invAllL1p (CACHE_Wait wait)
{
    /* Invalidate the L1P Cache. */
    ((((CSL_CgemRegs *)(0x01800000))->L1PINV) = ((((CSL_CgemRegs *)(0x01800000))->L1PINV) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu)));    

    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_invAllL1pWait();
}

/** ============================================================================
 *   @n@b CACHE_setL2Size
 *
 *   @b Description
 *   @n This function is used to set the new size of the L2 Cache.  
 *
 *   @b Arguments
      @verbatim
          newSize   New Size of the L2 Cache to be set.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The L2 Cache is configured to use the new size.  
 *
 *   @b Writes
 *   @n CGEM_L2CFG_L2MODE
 *
 *   @b Example
 *   @verbatim
         
        CACHE_setL2Size(CACHE_32KCACHE); // Use 32K L2 Cache. 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_setL2Size (CACHE_L2Size newSize)
{
    /* Set the new L2 cache size. */
    ((((CSL_CgemRegs *)(0x01800000))->L2CFG) = ((((CSL_CgemRegs *)(0x01800000))->L2CFG) & ~(0x00000007u)) | (((newSize) << (0x00000000u)) & (0x00000007u)));
}

/** ============================================================================
 *   @n@b CACHE_getL2Size
 *
 *   @b Description
 *   @n This function is used to get the L2 cache size.  
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  CACHE_L2Size
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None  
 *
 *   @b Reads
 *   @n CGEM_L2CFG_L2MODE
 *
 *   @b Example
 *   @verbatim
        CACHE_L2Size size;
        
        size = CACHE_getL2Size(); 

     @endverbatim
 * =============================================================================
 */
static inline CACHE_L2Size CACHE_getL2Size (void)
{    
    return (CACHE_L2Size) (((((CSL_CgemRegs *)(0x01800000))->L2CFG) & (0x00000007u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CACHE_freezeL2
 *
 *   @b Description
 *   @n This function is used to freeze the L2 Cache  
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The L2 Cache is frozen.  
 *
 *   @b Example
 *   @verbatim
         
        CACHE_freezeL2(); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_freezeL2 (void)
{
    /* The RL File does not define the L2CC bit so we used the RAW macro to 
     * configure the corresponding bit. */
    ((((CSL_CgemRegs *)(0x01800000))->L2CFG) = ((((CSL_CgemRegs *)(0x01800000))->L2CFG) &~ (((1 << ((3) - (3) + 1)) - 1) << (3))) | (((1) & ((1 << ((3) - (3) + 1)) - 1)) << (3)));
}

/** ============================================================================
 *   @n@b CACHE_unfreezeL2
 *
 *   @b Description
 *   @n This function is used to unfreeze the L2 Cache  
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The L2 Cache is unfrozen  
 *
 *   @b Example
 *   @verbatim
         
        CACHE_unfreezeL2(); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_unfreezeL2 (void)
{
    /* The RL File does not define the L2CC bit so we used the RAW macro to 
     * configure the corresponding bit. */
    ((((CSL_CgemRegs *)(0x01800000))->L2CFG) = ((((CSL_CgemRegs *)(0x01800000))->L2CFG) &~ (((1 << ((3) - (3) + 1)) - 1) << (3))) | (((0) & ((1 << ((3) - (3) + 1)) - 1)) << (3)));
}

/** ============================================================================
 *   @n@b CACHE_wbL2Wait
 *
 *   @b Description
 *   @n This function is used to wait for the L2 writeback block operation to 
 *      complete. This API should be used only if the CACHE_wbL2 was called 
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbL2(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The dirty lines of the L1D Block Cache have been written back. 
 *
 *   @b Reads
 *   @n CGEM_L2WWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_wbL2((void *)ptr_buffer, 128, CACHE_NOWAIT);
        ...        
        CACHE_wbL2Wait();        // Wait for the writeback operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbL2Wait (void)
{
    /* Wait for the Writeback operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L2WWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);        
}

/** ============================================================================
 *   @n@b CACHE_wbL2
 *
 *   @b Description
 *   @n This function is used to writeback the contents of the L2 Cache. Although 
 *      the block size can be specified in the number of bytes, the cache 
 *      controller operates on whole cache lines. To prevent unintended behavior 
 *      "blockPtr" should be aligned on the  cache line size and "byteCnt" 
 *      should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be written back
          byteCnt       Size of the block to be written block.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The dirty lines of the L2 Cache are being written back.   
 *
 *   @b Writes
 *   @n CGEM_L2WBAR_ADDR,CGEM_L2WWC_WC
 *
 *   @b Example
 *   @verbatim
        Uint8* ptr_buffer;
        
        // Writeback the contents of the buffer. 
        CACHE_wbL2(ptr_buffer, 100, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbL2 
(
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length */
    ((CSL_CgemRegs *)(0x01800000))->L2WBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));    
    ((CSL_CgemRegs *)(0x01800000))->L2WWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));

    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_wbL2Wait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_invL2Wait
 *
 *   @b Description
 *   @n This function is used to wait for the L2 invalidate block operation to 
 *      complete. This API should be used only if the CACHE_invL2 was called 
 *      with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_invL2(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  Invalidate the contents of the L2 Cache. 
 *
 *   @b Reads
 *   @n CGEM_L2IWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_invL2((void *)ptr_buffer, 128, CACHE_NOWAIT);
        ...        
        CACHE_invL2Wait();        // Wait for the Invalidate operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invL2Wait (void)
{
    /* Wait for the Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L2IWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);        
}

/** ============================================================================
 *   @n@b CACHE_invL2
 *
 *   @b Description
 *   @n This function is used to invalidate the contents of the L2 Cache. 
 *      Although the block size can be specified in  the number of bytes, 
 *      the cache controller operates on whole cache lines. To prevent unintended 
 *      behavior "blockPtr" should be aligned on the cache line size and "byteCnt" 
 *      should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be invalidated
          byteCnt       Size of the block to be invalidated.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache are being invalidated.   
 *
 *   @b Writes
 *   @n CGEM_L2IBAR_ADDR,CGEM_L2IWC_WC
 *
 *   @b Example
 *   @verbatim
        Uint8* ptr_buffer;
        
        // Invalidate the contents of the buffer. 
        CACHE_invL2(ptr_buffer, 100, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invL2 
(
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length */
    ((CSL_CgemRegs *)(0x01800000))->L2IBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));    
    ((CSL_CgemRegs *)(0x01800000))->L2IWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));

    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_invL2Wait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_wbInvL2Wait
 *
 *   @b Description
 *   @n This function is used to wait for the L2 Writeback & invalidate block 
 *      operation to complete. This API should be used only if the CACHE_wbInvL2 
 *      was called with the CACHE_NOWAIT argument. 
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbInvL2(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  Invalidate the contents of the L2 Cache. 
 *
 *   @b Reads
 *   @n CGEM_L2WIWC_WC=0
 *
 *   @b Example
 *   @verbatim
                
        CACHE_wbInvL2((void *)ptr_buffer, 128, CACHE_NOWAIT);
        ...        
        CACHE_wbInvL2Wait();  // Wait for the Writeback-Invalidate operation to complete.

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvL2Wait (void)
{
    /* Wait for the Writeback & Invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L2WIWC) & (0x0000FFFFu)) >> (0x00000000u)) != 0);        
}

/** ============================================================================
 *   @n@b CACHE_wbInvL2
 *
 *   @b Description
 *   @n This function is used to write back and invalidate the contents of the L2 Cache.
 *      Although the block size can be specified in the number of bytes, 
 *      the cache controller operates on whole cache lines. To prevent unintended 
 *      behavior "blockPtr" should be aligned on the cache line size and "byteCnt" 
 *      should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be written back & invalidated
          byteCnt       Size of the block to be written back & invalidated.
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache are being written back & invalidated.   
 *
 *   @b Writes
 *   @n CGEM_L2WIBAR_ADDR,CGEM_L2WIWC_WC
 *
 *   @b Example
 *   @verbatim
        Uint8* ptr_buffer;
        
        // Invalidate the contents of the buffer. 
        CACHE_wbInvL2(ptr_buffer, 100, CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvL2 (
    void*       blockPtr,
    Uint32      byteCnt,
    CACHE_Wait  wait
)
{
    /* Setup the block address and length */
    ((CSL_CgemRegs *)(0x01800000))->L2WIBAR = ((((Uint32)blockPtr) << (0x00000000u)) & (0xFFFFFFFFu));
    ((CSL_CgemRegs *)(0x01800000))->L2WIWC  = ((((Uint32)((byteCnt+3)>>2)) << (0x00000000u)) & (0x0000FFFFu));
 
    /* Determine if we need to wait for the operation to complete. */
    if (wait == CACHE_WAIT)
        CACHE_wbInvL2Wait();
    else if (wait == CACHE_FENCE_WAIT)
        _mfence();
}

/** ============================================================================
 *   @n@b CACHE_wbAllL2Wait
 *
 *   @b Description
 *   @n This function is used to wait for the L2 Writeback & invalidate operation 
 *      to complete. This API should be used only if the CACHE_wbAllL2 was called 
 *      with the CACHE_NOWAIT argument.   
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbAllL2(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache have been written back
 *
 *   @b Reads
 *   @n CGEM_L2WB_C=0
 *
 *   @b Example
 *   @verbatim
        
        // Writeback the contents of the L2 Cache.
        CACHE_wbAllL2(CACHE_NOWAIT);
        
        // Wait for the operation to complete. 
        CACHE_wbAllL2Wait(); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbAllL2Wait (void)
{
    /* Wait for the writeback operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L2WB) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);    
}

/** ============================================================================
 *   @n@b CACHE_wbAllL2
 *
 *   @b Description
 *   @n This function is used to write back all the contents of the L2 Cache.  
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache are being written back.   
 *
 *   @b Writes
 *   @n CGEM_L2WB_C=1
 *
 *   @b Example
 *   @verbatim
        
        // Writeback the contents of the L2 Cache. 
        CACHE_wbAllL2(CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbAllL2 (CACHE_Wait wait)
{
    ((((CSL_CgemRegs *)(0x01800000))->L2WB) = ((((CSL_CgemRegs *)(0x01800000))->L2WB) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu)));
    
    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_wbAllL2Wait();
}

/** ============================================================================
 *   @n@b CACHE_invAllL2Wait
 *
 *   @b Description
 *   @n This function is used to wait for the L2 Invalidate operation to complete. 
 *      This API should be used only if the CACHE_invAllL2 was called with the 
 *      CACHE_NOWAIT argument.   
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_invAllL2(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache have been invalidated   
 *
 *   @b Reads
 *   @n CGEM_L2INV_I=0
 *
 *   @b Example
 *   @verbatim
        
        // Invalidate the contents of the L2 Cache.
        CACHE_invAllL2(CACHE_NOWAIT);
        
        // Wait for the operation to complete. 
        CACHE_invAllL2Wait(); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invAllL2Wait (void)
{
    /* Wait for the invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L2INV) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);    
}

/** ============================================================================
 *   @n@b CACHE_invAllL2
 *
 *   @b Description
 *   @n This function is used to invalidate all the contents of the L2 Cache.  
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache are being invalidated.   
 *
 *   @b Writes
 *   @n CGEM_L2INV_I=1 
 *
 *   @b Example
 *   @verbatim
        
        // Invalidate the contents of the L2 Cache. 
        CACHE_invAllL2(CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_invAllL2 (CACHE_Wait wait)
{
    ((((CSL_CgemRegs *)(0x01800000))->L2INV) = ((((CSL_CgemRegs *)(0x01800000))->L2INV) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu)));
    
    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_invAllL2Wait();    
}

/** ============================================================================
 *   @n@b CACHE_wbInvAllL2Wait
 *
 *   @b Description
 *   @n This function is used to wait for the L2 Writeback and Invalidate 
 *      operation to complete. This API should be used only if the CACHE_wbInvAllL2 was 
 *      called with the CACHE_NOWAIT argument.   
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CACHE_wbInvAllL2(wait=CACHE_NOWAIT) must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache have been invalidated and written back
 *
 *   @b Reads
 *   @n CGEM_L2WBINV_C=0
 *
 *   @b Example
 *   @verbatim
        
        // Writeback & Invalidate the contents of the L2 Cache.
        CACHE_wbInvAllL2(CACHE_NOWAIT);
        
        // Wait for the operation to complete. 
        CACHE_wbInvAllL2Wait(); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvAllL2Wait (void)
{
    /* Wait for the writeback-invalidate operation to complete. */
    while ((((((CSL_CgemRegs *)(0x01800000))->L2WBINV) & (0xFFFFFFFFu)) >> (0x00000000u)) == 1);    
}

/** ============================================================================
 *   @n@b CACHE_wbInvAllL2
 *
 *   @b Description
 *   @n This function is used to writeback and invalidate all the contents of the L2 Cache.  
 *
 *   @b Arguments
      @verbatim
          wait          Indicates if the call should block or not.
     @endverbatim 
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The contents of the L2 Cache are being written back & invalidated.   
 *
 *   @b Writes
 *   @n CGEM_L2WBINV_C=1
 *
 *   @b Example
 *   @verbatim
        
        // Invalidate the contents of the L2 Cache. 
        CACHE_wbInvAllL2(CACHE_WAIT); 

     @endverbatim
 * =============================================================================
 */
static inline void CACHE_wbInvAllL2 (CACHE_Wait wait)
{
    ((((CSL_CgemRegs *)(0x01800000))->L2WBINV) = ((((CSL_CgemRegs *)(0x01800000))->L2WBINV) & ~(0xFFFFFFFFu)) | (((1) << (0x00000000u)) & (0xFFFFFFFFu)));
    
    /* Determine if we need to wait for the operation to complete. */
    if (wait)
        CACHE_wbInvAllL2Wait();    
}

/**
@}
*/




extern void CACHE_wbAllL1dWait(void);
extern void CACHE_wbL2Wait(void);

extern void CACHE_invAllL1dWait(void);
extern void CACHE_invL2Wait(void);








//#define OLD_IIPC
//#define USE_MESSAGEQ
/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////// final configuration //////////////////////////////

//#define _CONFIG_TARGET_WITH_RELEASE_

//#define _CONFIG_POC_WITH_RELEASE_


////////////////////////////////////////////////////////////////////////////////////////////



// to put logs in all functions to find the exception error
//#define ToFindExcpError

extern void Eth_Debug2(const char *msg,CHAR *format, ...);
extern void uart_write(const char *fmt, ... );

//@@@@@@@@@@@@@@@@@@@@@@ Build Related definitions @@@@@@@@@@@@@@@@@@@@@@
//#define _STE_BOOT		//Build for Bootloader


extern volatile void *pEthObj;

//@@@@@@@@@@@@@@@@@@@@@@ Log related definitions @@@@@@@@@@@@@@@@@@@@@@
// #define LOG_MSG_BOX
//#define LOG_MSG_DEBUG
//#define LOG_MSG_DUMP
//#define LOG_MSG_EVENT
//#define LOG_MSG_FATAL
//#define LOG_MSG_TRACE
//#define LOG_MSG_WARN
//#define JTAG_TRACE
//#define JTAG_DUMP
//#define JTAG_EVENT
//#define	LOG_EVENT_CB(format,...) LOG_printf(&event, format, ##__VA_ARGS__)
//#define	LOG_TRACE_CB(format,...) LOG_printf(&trace, format, ##__VA_ARGS__)
//#define	LOG_FATAL_CB(format,...) LOG_printf(&fatal, format, ##__VA_ARGS__)
//#define LOG_EVENT_CB  





//#define	LOG_FATAL(format,...) LOG_printf(&fatal, format, ##__VA_ARGS__)





// USER CONFIGURATION FOR RX MANAGER

/* DO NOT CHANGE BELOW SETTINGS UNLESS REGRESSION TEST IS DONE */
/*******************************************************************/

/*******************************************************************/

//switch for Assembly Functions

//@@@@@@@@@@@@@@@@@@@@@@ Operation mode related definition @@@@@@@@@@@@@@@@@@@@@@
/* below two definition should be disabled for final configuration*/
//#define	SINGLE_CORE_OPERATION	//for enabling single core operation (PC simulation mode)
//#define 	SIMULATE_PAYLOAD		

//@@@@@@@@@@@@@@@@@@@@@@ Commmand related definitions @@@@@@@@@@@@@@@@@@@@@@
/* below three definition should be disabled for final configuration*/
//#define	SIMULATE_CMD_97_SUCCESS  //for generating command success for Rx tune(command 97)
//#define 	TESTING_CIPHER_WITH_IPU  //for enabling cipher when testing with IPU stub
//#define 	TESTING_HOPPING_WITH_IPU  //for enabling hopping when testing with IPU stub

//@@@@@@@@@@@@@@@@@@@@@@ SRIO related definitions @@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@ Ethernet related definitions @@@@@@@@@@@@@@@@@@@@@@
//#define	ENABLE_EMAC				//for enabling the NDK library
//#define	ETHBUFF_SIMULATE      	//for testing the ethernet dump
//#define     _USE_ETHERNET_INTERFACE  // to spawan ethernet related tasks/module




//@@@@@@@@@@@@@@@@@@@@@@ TX Manager related definitions @@@@@@@@@@@@@@@@@@@

//#define VBTS_SEND_ONLY_FCCH_ALL_FN	//for sending FCCH only
//#define VBTS_SEND_ONLY_SCH_WITH_FIXED_FN_ALL_FN	//for sending SCH only
//#define VBTS_SEND_ONLY_C0TO			//for sending on Timeslot 0 only
//#define VBTS_SEND_ONLY_DUMMY_C0TX  	//for sending Dummy burst on all Timeslot
//#define VBTS_SEND_ONLY_SCH_C0TX		//for sending SCH in all Timeslot
//#define VBTS_SEND_ONLY_FCCH_C0TX		//for sending FCCH in all Timeslot
//#define VBTS_FPGA_BYTE_SWAP			//Workaround for FPGA Byte swap
//#define VBTS_FPGA_NIBBLE_SWAP			//Workaround for FPGA Nibble swap
//#define AREA_JAMMING_TESTING

//@@@@@@@@@@@@@@@@@@@@@@ Rx Manager related definitions @@@@@@@@@@@@@@@@@@@@@@
//#define FIXED_BAND  			//for enabling PGSM band only
//#define FIXED_ARFCN   		//for testing in Simulate mode
//#define _FEED_TEST_VECTOR_    // feeding test vector in SCH burst against real
//#define SEARCH_ONLY_40			// search only arfcn 40

//#define ENABLE_RESET_TRX		// upon getting reset, all the associated rx and tx including beacon channels
								// gets dropped off


/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////// final configuration //////////////////////////////


//#define _CONFIG_POC_WITH_RELEASE_


////////////////////////////////////////////////////////////////////////////////////////////

extern void StatMgr_Fatal(void);





/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */



/*
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */


/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


void LOG_DumpMsg(void *pMsg, UINT16 nBytes, BOOL bIsByteFormat);





#pragma CODE_SECTION(LOG_DumpMsg,".textDDR")

void LOG_DumpMsg(void *pMsg, UINT16 nNumBytes, BOOL bIsByteFormat)
{
	UINT8	*pPtr8;
	UINT16 *pPtr16;
	UINT16	nBytes;

	pPtr8	=	(UINT8*)pMsg;
	pPtr16	=	(UINT16*)pMsg;

//	LOG_DUMP("Dumping the memory 0x%x upto %d bytes", pMsg, nNumBytes);
//	LOG_DUMP2("Dumping the memory 0x%x upto %d bytes", pMsg, nNumBytes);

	for(nBytes = 0; nBytes < nNumBytes; nBytes++)
	{
		if(bIsByteFormat)
		{
		//	LOG_DUMP( "0x%x", *pPtr8);
	//		LOG_DUMP1( "0x%x", *pPtr8);
		}
		else
		{
			//LOG_DUMP( "0x%x", *pPtr16);
	//		LOG_DUMP1( "0x%x", *pPtr16);
			nBytes++;
		}
		pPtr8++;
		pPtr16++;
	}
}

