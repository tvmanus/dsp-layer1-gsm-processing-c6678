

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





/**
 *   @file  csl_gpio.h
 *
 *   @brief
 *      This is the main Header File for the GPIO Module which defines all
 *      the data structures and exported API.
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



/** @defgroup CSL_GPIO_API GPIO
 *
 * @section Introduction
 *
 * @subsection 
 *  None
 *
 * @subsection References
 *  None
 *
 */

/**
@defgroup CSL_GPIO_DATASTRUCT  GPIO Data structures
@ingroup  CSL_GPIO_API
*/

/**
@defgroup CSL_GPIO_FUNCTION  GPIO Functions
@ingroup  CSL_GPIO_API
*/

/**
@addtogroup CSL_GPIO_DATASTRUCT  
@{
*/

/** @brief This is the handle to the GPIO instance */
typedef volatile CSL_GpioRegs*   CSL_GpioHandle;

/**
@}
*/

/* Device specific API which opens the GPIO instance and returns a handle used in all subsequent calls */
extern CSL_GpioHandle CSL_GPIO_open (Int32 instNum);
        




/*  ============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2008
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
 *   @file  csl_intc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer CSL of INTC
 *
 */

/** @defgroup CSL_INTC_API INTC  
 *
 *  @section Introduction 
 *  
 * The CPU has one exception input, one non-maskable interrupt, 12 maskable
 * interrupts, and two dedicated emulation interrupts.The Interrupt Controller
 * supports up to 128 system events. There are 128 system events that act as
 * inputs to the Interrupt Controller. They consist of both internally-generated
 * events (within the megamodule) and chip-level events. In addition to these
 * 128 events, INTC also receives (and routes straight through to the CPU) the
 * non-maskable and reset events.From these event inputs, the Interrupt
 * Controller outputs signals to the CPU:
 *   - One maskable, hardware exception (EXCEP)
 *   - Twelve maskable hardware interrupts (INT4 ... INT15)
 *   - One non-maskable signal which can be used as either an interrupt or
 * exception (NMI)
 *   - One reset signal (RESET)
 * 
 * NOTE: The CSL 3.0 INTC module is delivered as a separate library from the
 * remaining CSL modules. When using an embedded operating system that contains
 * interrupt controller/dispatcher support, do not link in the INTC library.
 * For interrupt controller support, DSP/BIOS users should use the HWI
 * (Hardware Interrupt) and ECM (Event Combiner Manager) modules supported
 * under DSP/BIOS v5.21 or later.
 *  
 *  @subsection References
 *     -# CSL 3.x Technical Requirements Specifications Version 0.5, dated
 *        May 14th, 2003
 *     -# TMS320C64x+ DSP Megamodule SPRU871I.pdf (May 2008)
 *  
 *  @subsection Assumptions
 *     The abbreviations INTC, Intc and intc have been used throughout this
 *     document to refer to Interrupt Controller
 */


/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Jun-2004 Ruchika Kharwar File Created
 *  14-Mar-2005 brn Moved the Event Ids to soc64plus.h
 *  16-Mar-2005 brn modified for doxygen documentation
 *  19-Nov-2008 Updated for Doxygen
 * =============================================================================
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
 *   @file  cslr_intc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for INTC
 *
 */


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
    volatile Uint8 RSVD7[112];
    volatile Uint32 INTXSTAT;
    volatile Uint32 INTXCLR;
    volatile Uint32 INTDMASK;
} CSL_IntcRegs;

typedef volatile CSL_IntcRegs         *CSL_IntcRegsOvly;

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






/* INTXSTAT */


/*----SYSINT Tokens----*/


/*----CPUINT Tokens----*/



/*----DROP Tokens----*/


/* INTXCLR */




/* INTDMASK */















/**
@defgroup CSL_INTC_DATASTRUCT  INTC Data Structures
@ingroup CSL_INTC_API
*/
/**
@defgroup CSL_INTC_SYMBOL  INTC Symbols Defined
@ingroup CSL_INTC_API
*/
/**
@defgroup CSL_INTC_ENUM  INTC Enumerated Data Types
@ingroup CSL_INTC_API
*/

/**
@defgroup CSL_INTC_FUNCTION  INTC Functions
@ingroup CSL_INTC_API
*/

/**
@addtogroup CSL_INTC_SYMBOL
@{
*/
        
/** Number of Events in the System */

/** Indicates there is no associated event-handler */

/** Invalid handle */

/** None mapped */

/**
@}
*/

/** @addtogroup CSL_INTC_ENUM
 @{ */
        
/**
 *  Interrupt Vector IDs
 */
typedef enum {
    /** Should be used only along with CSL_intcHookIsr() */
    CSL_INTC_VECTID_NMI      =   1,   
    /** CPU Vector 4 */
    CSL_INTC_VECTID_4        =   4,
    /** CPU Vector 5 */   
    CSL_INTC_VECTID_5        =   5,   
    /** CPU Vector 6 */
    CSL_INTC_VECTID_6        =   6,   
    /** CPU Vector 7 */
    CSL_INTC_VECTID_7        =   7,   
    /** CPU Vector 8 */
    CSL_INTC_VECTID_8        =   8,
    /** CPU Vector 9 */
    CSL_INTC_VECTID_9        =   9,
    /** CPU Vector 10 */   
    CSL_INTC_VECTID_10       =   10,
    /** CPU Vector 11 */   
    CSL_INTC_VECTID_11       =   11,
    /** CPU Vector 12 */  
    CSL_INTC_VECTID_12       =   12,
    /** CPU Vector 13 */  
    CSL_INTC_VECTID_13       =   13,  
    /** CPU Vector 14 */    
    CSL_INTC_VECTID_14       =   14,
    /** CPU Vector 15 */  
    CSL_INTC_VECTID_15       =   15,  
    /** Should be used at the time of opening an Event handle
     *  to specify that the event needs to go to the combiner
     */
    CSL_INTC_VECTID_COMBINE  =   16,  
    /** Should be used at the time of opening an Event handle
     * to specify that the event needs to go to the exception
     * combiner.
     */
    CSL_INTC_VECTID_EXCEP    =   17   
} CSL_IntcVectId; 

/**
 *  Interrupt Event IDs
 */
typedef Int     CSL_IntcEventId; 


/**
 *  Enumeration of the control commands
 *
 *  These are the control commands that could be used with
 *  CSL_intcHwControl(..). Some of the commands expect an
 *  argument as documented along-side the description of
 *  the command.
 */
typedef enum {
        /**
         * @brief   Enables the event
         * @param   CSL_IntcEnableState
         */
    CSL_INTC_CMD_EVTENABLE      = 0,
        /**
         * @brief   Disables the event
         * @param   CSL_IntcEnableState
         */
    CSL_INTC_CMD_EVTDISABLE     = 1,
        /**
         * @brief   Sets the event manually
         * @param   None
         */   
    CSL_INTC_CMD_EVTSET         =2,
        /**
         * @brief   Clears the event (if pending)
         * @param   None
         */
    CSL_INTC_CMD_EVTCLEAR       =3,
        /**
         * @brief   Enables the Drop Event detection feature for this event
         * @param   None
         */    
    CSL_INTC_CMD_EVTDROPENABLE  =4,
        /**
         * @brief   Disables the Drop Event detection feature for this event
         * @param   None
         */       
    CSL_INTC_CMD_EVTDROPDISABLE =5,
        /**
         * @brief   To be used ONLY to invoke the associated Function handle 
         * with Event when the user is writing an exception handling routine. 
         * @param   None
         */             
    CSL_INTC_CMD_EVTINVOKEFUNCTION = 6
} CSL_IntcHwControlCmd;


/**
 *  Enumeration of the queries
 *
 *  These are the queries that could be used with CSL_intcGetHwStatus(..).
 *  The queries return a value through the object pointed to by the pointer
 *  that it takes as an argument. The argument supported by the query is
 *  documented along-side the description of the query.
 */
typedef enum {
        /**
         * @brief   The Pend Status of the Event is queried 
         * @param   Bool
         */  
    CSL_INTC_QUERY_PENDSTATUS
}CSL_IntcHwStatusQuery;


/**
 *  Enumeration of the exception mask registers
 *
 *  These are the symbols used along with the value to be programmed
 *  into the Exception mask register.
 */
typedef enum {
        /**
         * @brief   Symbol for EXPMASK[0]
         * @param   BitMask for EXPMASK0
         */
    CSL_INTC_EXCEP_0TO31 = 0,
        /**
         * @brief   Symbol for EXPMASK[1]
         * @param   BitMask for EXPMASK1
         */
    CSL_INTC_EXCEP_32TO63 = 1,
        /**
         * @brief   Symbol for EXPMASK[2]
         * @param   BitMask for EXPMASK2
         */   
    CSL_INTC_EXCEP_64TO95 = 2,
        /**
         * @brief   Symbol for EXPMASK[3]
         * @param   BitMask for EXPMASK3
         */
    CSL_INTC_EXCEP_96TO127 = 3
} CSL_IntcExcepEn;

/**
 *  Enumeration of the exception
 * These are the symbols used along with the Exception Clear API
 */
typedef enum {
        /**
         * @brief   Symbol for NMI
         * @param   None
         */ 
    CSL_INTC_EXCEPTION_NMI = 31,
        /**
         * @brief   Symbol for External Exception
         * @param   None
         */ 
    CSL_INTC_EXCEPTION_EXT = 30,
        /**
         * @brief   Symbol for Internal Exception
         * @param   None
         */ 
    CSL_INTC_EXCEPTION_INT = 1,
        /**
         * @brief   Symbol for Software Exception
         * @param   None
         */ 
    CSL_INTC_EXCEPTION_SW = 0
} CSL_IntcExcep;

/**
@}
*/

/** @addtogroup CSL_INTC_DATASTRUCT
 @{ */

/**
 *  Event Handler pointer
 *
 *  Event handlers ought to conform to this type
 */
typedef void (* CSL_IntcEventHandler)(void *);


/**
 *  Event Handler Record
 *
 *  Used to set-up the event-handler using CSL_intcPlugEventHandler(..)
 */
typedef struct  {
    /** pointer to the event handler */
    CSL_IntcEventHandler    handler;
    /** the argument to be passed to the handler when it is invoked */  
    void *                  arg;        
                                          
} CSL_IntcEventHandlerRecord;

/**
 *  INTC Module Context. 
 */
typedef struct {
    /** Pointer to the event handle record */
    CSL_IntcEventHandlerRecord* eventhandlerRecord;

    /** Event allocation mask */
    CSL_BitMask32   eventAllocMask[(128 + 31) / 32];

    /** Number of event entries */
    Uint16          numEvtEntries;

    /** Reserved */
    Int8            offsetResv[128];
} CSL_IntcContext;


/**
 *  Event enable state
 */
typedef Uint32 CSL_IntcEventEnableState;


/**
 *  Global Interrupt enable state
 */
typedef Uint32 CSL_IntcGlobalEnableState;

/**
 *  The interrupt handle object
 *  This object is used by the handle to identify the event.
 */
typedef struct CSL_IntcObj {
    /** The event-id */
    CSL_IntcEventId eventId;
    /** The vector-id */    
    CSL_IntcVectId   vectId;    
} CSL_IntcObj;

/**
 *  The drop status structure
 *
 *  This object is used along with the CSL_intcQueryDropStatus()
 *  API.
 */
typedef struct {
    /** whether dropped/not */
    Bool drop;
    /** The event-id */                  
    CSL_IntcEventId eventId;
    /** The vect-id */    
    CSL_IntcVectId  vectId;     
}CSL_IntcDropStatus;

/**
 *  INTC module parameters for open
 *
 *  This is equivalent to the Vector Id for the event number.
 */
typedef CSL_IntcVectId CSL_IntcParam;

/**
 *  The interrupt handle
 *
 *  This is returned by the CSL_intcOpen(..) API. The handle is used
 *  to identify the event of interest in all INTC calls.
 */
typedef struct CSL_IntcObj*   CSL_IntcHandle;

/**
@}
*/

/** @addtogroup CSL_INTC_FUNCTION
 @{ */

/*  ============================================================================
 *   @n@b CSL_intcInit
 *
 *   @b Description
 *   @n This is the initialization function for the INTC. This function is
 *      idempotent in that calling it many times is same as calling it once.
 *      This function initializes the CSL data structures, and doesn't affect
 *      the H/W.
 *
 *   @b Arguments
 *   @verbatim
              pContext     Pointer to module-context structure
             
    @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  This function should be called before using any of the CSL INTC APIs. 
 *       The context should be initialized such that numEvtEntries is equal to 
 *       the number of records capable of being held in the eventhandlerRecord
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n  None
 *
 *   @b Example
 *   @verbatim
    CSL_IntcContext context; 
    CSL_Status intStat;
    CSL_IntcParam vectId;
    CSL_IntcEventHandlerRecord recordTable[10];
    
    context.numEvtEntries = 10;
    context.eventhandlerRecord = &recordTable;

    // Init Module
    ...
    if (CSL_intcInit(&context) != CSL_SOK) {
       exit;
    }
     @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcInit (
    CSL_IntcContext     *pContext 
);

/*  ============================================================================
 *   @n@b CSL_intcOpen
 *
 *   @b Description
 *   @n The API would reserve an interrupt-event for use. It returns
 *      a valid handle to the event only if the event is not currently
 *      allocated. The user could release the event after use by calling
 *      CSL_intcClose(..). The CSL-object ('intcObj') that the user
 *      passes would be used to store information pertaining handle.
 *
 *   @b Arguments
 *   @verbatim
              pIntcObj     pointer to the CSL-object allocated by the user

              eventId      the event-id of the interrupt

              param        pointer to the Intc specific parameter

              pStatus      (optional) pointer for returning status of the
                           function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_IntcHandle
 *   @n                     Valid INTC handle identifying the event
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    INTC object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid intc handle is returned
 *   @li            CSL_ESYS_FAIL       The open command failed
 *
 *   @b Writes
 *   @n    1. The status variable
 *   @n    2. INTC object structure
 *
 * @b Example:
 * @verbatim

        CSL_IntcObj                 intcObj20;
        CSL_IntcGlobalEnableState   state;
        CSL_IntcContext             context;
        CSL_Status                  intStat;
        CSL_IntcParam               vectId;

        context.numEvtEntries = 0;
        context.eventhandlerRecord = NULL;
        // Init Module
        CSL_intcInit(&context);

        // NMI Enable
        CSL_intcGlobalNmiEnable();

        // Enable Global Interrupts
        intStat = CSL_intcGlobalEnable(&state);

        // Opening a handle for the Event 20 at vector id 4

        vectId = CSL_INTC_VECTID_4;
        hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);

        // Close handle
        CSL_IntcClose(hIntc20);
   @endverbatim
 * =============================================================================
 */
CSL_IntcHandle   CSL_intcOpen (
    CSL_IntcObj        *intcObj,    
    CSL_IntcEventId     eventId,    
    CSL_IntcParam      *params,     
    CSL_Status         *status
);

/* =============================================================================
 *   @n@b CSL_intcClose
 *
 *   @b Description
 *   @n This intc Handle can no longer be used to access the event. The event is 
 *    de-allocated and further access to the event resources are possible only after
 *    opening the event object again.
 *
 *   @b Arguments
 *   @verbatim
            hIntc            Handle identifying the event
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_FAIL       - Close failed
 *
 *   @b Example
 *   @verbatim
        CSL_IntcContext             context; 
        CSL_Status                  intStat;
        CSL_IntcParam               vectId;
        CSL_IntcObj                 intcObj20;
        CSL_IntcHandle              hIntc20;
        CSL_IntcEventHandlerRecord  recordTable[10];

        context.numEvtEntries = 10;
        context.eventhandlerRecord = &recordTable;

        // Init Module
        ...
        if (CSL_intcInit(&context) != CSL_SOK) {
           exit;
        // Opening a handle for the Event 20 at vector id 4

        vectId = CSL_INTC_VECTID_4;
        hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);

        // Close handle
        CSL_IntcClose(hIntc20);    
               
     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_intcClose (
    CSL_IntcHandle      hIntc   
);

/*  ============================================================================
 *  @n@b CSL_intcPlugEventHandler
 *
 *  @b Description
 *  @n Associate an event-handler with an event
 *     CSL_intcPlugEventHandler(..) ties an event-handler to an event; so
 *     that the occurence of the event, would result in the event-handler
 *     being invoked.
 *
 *  @b Arguments
 *  @verbatim
        hIntc                Handle identying the interrupt-event

        eventHandlerRecord   Provides the details of the event-handler
    @endverbatim
 *
 *  <b> Return Value </b>
 *  @n  Returns the address of the previous handler
 *
 *  @b Example:
 *  @verbatim
        CSL_IntcObj                 intcObj20;
        CSL_IntcGlobalEnableState   state;
        CSL_IntcContext             context; 
        CSL_Status                  intStat;
        CSL_IntcParam               vectId;

        context.numEvtEntries = 0;
        context.eventhandlerRecord = NULL;
        // Init Module
        CSL_intcInit(&context);

        // NMI Enable   
        CSL_intcGlobalNmiEnable();

        // Enable Global Interrupts 
        intStat = CSL_intcGlobalEnable(&state);

        // Opening a handle for the Event 20 at vector id 4

        vectId = CSL_INTC_VECTID_4;
        hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);

        EventRecord.handler = &event20Handler;
        EventRecord.arg = hIntc20;
        CSL_intcPlugEventHandler(hIntc20,&EventRecord); 
        // Close handle
        CSL_IntcClose(hIntc20);
        }

        void event20Handler( CSL_IntcHandle hIntc)
        {

        }
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcPlugEventHandler (
    CSL_IntcHandle                  hIntc,
    CSL_IntcEventHandlerRecord      *eventHandlerRecord
);

/*  ============================================================================
 *  @n@b CSL_intcHookIsr
 *
 *  @b Description
 *  @n Hook up an exception handler
 *     This API hooks up the handler to the specified exception.
 *     Note: In this case, it is done by inserting a B(ranch) instruction
 *     to the handler. Because of the restriction in the instruction
 *     th handler must be within 32MB of the exception vector.
 *     Also, the function assumes that the exception vector table is
 *     located at its default ("low") address.
 *
 *  @b Arguments
 *  @verbatim
        vectId       Interrupt Vector identifier

        isrAddr      Pointer to the handler
    @endverbatim
 *
 *  @b Example:
 *  @verbatim
        CSL_IntcContext             context; 
        CSL_Status                  intStat;
        CSL_IntcParam               vectId;
        CSL_IntcObj                 intcObj20;
        CSL_IntcHandle              hIntc20;
        CSL_IntcDropStatus          drop;
        CSL_IntcEventHandlerRecord  recordTable[10];
        CSL_IntcGlobalEnableState   state;
        Uint32 intrStat;

        context.numEvtEntries = 10;
        context.eventhandlerRecord = &recordTable;

        // Init Module
        ...
        if (CSL_intcInit(&context) != CSL_SOK)
           exit;
        // Opening a handle for the Event 20 at vector id 4

        vectId = CSL_INTC_VECTID_4;
        hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);

        CSL_intcNmiEnable();
        // Enable Global Interrupts 
        intStat = CSL_intcGlobalEnable(&state);

        // Hook Isr appropriately
        CSL_intcHookIsr(CSL_INTC_VECTID_4,&isrVect4);
        ...
         }
        interrupt void isrVect4()
        {

        }
        @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcHookIsr (
    CSL_IntcVectId  vectId,
    void            *isrAddr
);

/*  ============================================================================
 *   @n@b CSL_intcHwControl
 *
 *   @b Description
 *   @n Perform a control-operation. This API is used to invoke any of the
 *      supported control-operations supported by the module.
 *
 *   @b Arguments
 *   @verbatim
            hIntc           Handle identifying the event

            command         The command to this API indicates the action to be
                            taken on INTC.

            commandArg      An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - HwControl successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVCMD     - Invalid command
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcOpen() must be invoked before this call.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n The hardware registers of INTC.
 *
 *   @b Example
 *   @verbatim
        CSL_IntcObj                 intcObj20;
        CSL_IntcGlobalEnableState   state;
        CSL_IntcContext             context; 
        CSL_Status                  intStat;
        CSL_IntcParam               vectId;
        
        context.numEvtEntries = 0;
        context.eventhandlerRecord = NULL;
        
        // Init Module
        CSL_intcInit(&context);

        // NMI Enable   
        CSL_intcGlobalNmiEnable();

        // Enable Global Interrupts 
        intStat = CSL_intcGlobalEnable(&state);

        // Opening a handle for the Event 20 at vector id 4

        vectId = CSL_INTC_VECTID_4;
        hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);

        CSL_intcHwControl(hIntc20,CSL_INTC_CMD_EVTENABLE,NULL);
     @endverbatim
 * =============================================================================
 */

CSL_Status CSL_intcHwControl (
    CSL_IntcHandle          hIntc,      
    CSL_IntcHwControlCmd    command,    
    void                   *commandArg  
);

/*  ============================================================================
 *   @n@b CSL_intcGetHwStatus
 *
 *   @b Description
 *   @n Queries the peripheral for status. The CSL_intcGetHwStatus(..) API
 *      could be used to retrieve status or configuration information from
 *      the peripheral. The user must allocate an object that would hold
 *      the retrieved information and pass a pointer to it to the function.
 *      The type of the object is specific to the query-command.
 *
 *   @b Arguments
 *   @verbatim
            hIntc           Handle identifying the event

            query           The query to this API of INTC which indicates the
                            status to be returned.

            answer          Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK               - Status info return successful
 *   @li                   CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li                   CSL_ESYS_INVQUERY     - Invalid query
 *   @li                   CSL_ESYS_NOTSUPPORTED - Action not supported
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n None
 *
 *   @b Example:
 *   @verbatim
        CSL_IntcContext             context; 
        CSL_Status                  intStat;
        CSL_IntcParam               vectId;
        CSL_IntcObj                 intcObj20;
        CSL_IntcHandle              hIntc20;
        CSL_IntcEventHandlerRecord  recordTable[10];
        CSL_IntcGlobalEnableState   state;
        Uint32                      intrStat;

        context.numEvtEntries = 10;
        context.eventhandlerRecord = &recordTable;

        // Init Module
        ...
        if (CSL_intcInit(&context) != CSL_SOK)
           exit;
        // Opening a handle for the Event 20 at vector id 4

        vectId = CSL_INTC_VECTID_4;
        hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);

        // NMI Enable   
        CSL_intcGlobalNmiEnable();

        // Enable Global Interrupts 
        intStat = CSL_intcGlobalEnable(&state);

        do {
           CSL_intcGetHwStatus(hIntc20,CSL_INTC_QUERY_PENDSTATUS,                               (void*)&intrStat);
        } while (!stat);

        // Close handle
        CSL_IntcClose(hIntc20);

    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGetHwStatus (
    CSL_IntcHandle          hIntc,      
    CSL_IntcHwStatusQuery   query,      
    void                    *response    
);

/**  ============================================================================
 *  @n@b CSL_intcGlobalEnable
 *
 *  @b Description
 *  @n Globally enable interrupts.
 *     The API enables the global interrupt by manipulating the processor's
 *     global interrupt enable/disable flag. If the user wishes to restore
 *     the enable-state at a later point, they may store the current state
 *     using the parameter, which could be used with CSL_intcGlobalRestore(..).
 *     CSL_intcGlobalEnable(..) must be called from a privileged mode.
 *
 *  @b Arguments
 *  @verbatim
        prevState   (Optional) Pointer to object that would store current
                    stateObject that contains information about previous state
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        CSL_intcGlobalEnable(NULL);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalEnable (
    CSL_IntcGlobalEnableState * prevState   

);

/** ============================================================================
 *  @n@b CSL_intcGlobalDisable
 *
 *  @b Description
 *  @n Globally disable interrupts.
 *     The API disables the global interrupt by manipulating the processor's
 *     global interrupt enable/disable flag. If the user wishes to restore
 *     the enable-state at a later point, they may store the current state
 *     using the parameter, which could be used with CSL_intcGlobalRestore(..).
 *     CSL_intcGlobalDisable(..) must be called from a privileged mode.
 *
 *  @b Arguments
 *  @verbatim
        prevState   (Optional) Pointer to object that would store current
                    stateObject that contains information about previous state
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        
        CSL_intcGlobalDisable(NULL);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalDisable (
    CSL_IntcGlobalEnableState   *prevState   
);

/** ============================================================================
 *  @n@b CSL_intcGlobalRestore
 *
 *  @b Description
 *  @n Restore global interrupt enable/disable to a previous state.
 *     The API restores the global interrupt enable/disable state to a previous
 *     state as recorded by the global-event-enable state passed as an argument.
 *     CSL_intcGlobalRestore(..) must be called from a privileged mode.
 *
 *  @b Arguments
 *  @verbatim
        prevState   Object containing information about previous state
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        CSL_IntcGlobalEnableState   prevState;
 
        CSL_intcGlobalRestore(prevState);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalRestore (
    CSL_IntcGlobalEnableState   prevState
);

/** ============================================================================
 *  @n@b CSL_intcGlobalNmiEnable
 *
 *  @b Description
 *  @n This API enables global NMI
 *     
 *
 *  @b Arguments
 *  @verbatim
        None
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        
        CSL_intcGlobalNmiEnable();
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalNmiEnable (void);

/** ============================================================================
 *  @n@b CSL_intcGlobalExcepEnable
 *
 *  @b Description
 *  @n This API enables global exception
 *     
 *
 *  @b Arguments
 *  @verbatim
        None
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
       CSL_intcGlobalExcepEnable();
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalExcepEnable (void);  

/** ============================================================================
 *  @n@b CSL_intcGlobalExtExcepEnable
 *
 *  @b Description
 *  @n This API enables external exception
 *     
 *
 *  @b Arguments
 *  @verbatim
        None
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        
        CSL_intcGlobalExtExcepEnable();
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalExtExcepEnable (void);  

/** ============================================================================
 *  @n@b CSL_intcGlobalExcepClear
 *
 *  @b Description
 *  @n This API clears Global Exceptions
 *     
 *
 *  @b Arguments
 *  @verbatim
        exc     Exception to be cleared NMI/SW/EXT/INT 
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        CSL_intcGlobalExcepClear(exc);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcGlobalExcepClear (
    CSL_IntcExcep       exc
);

/*  ============================================================================
 *  @n@b CSL_intcExcepAllEnable
 *
 *  @b Description
 *  @n This API enables all exceptions
 *     
 *
 *  @b Arguments
 *  @verbatim
         excepMask    Exception Mask
         excVal       Event Value
         prevState    Pre state information 
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        CSL_IntcExcepEn   excepMask;                  
        CSL_BitMask32         excVal;            
        CSL_IntcEventEnableState *prevState;
     
        CSL_intcExcepAllEnable(excepMask, excVal, prevState);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcExcepAllEnable (
    CSL_IntcExcepEn     excepMask,
    CSL_BitMask32       excVal,
    CSL_BitMask32       *prevState    
);

/*  ============================================================================
 *  @n@b CSL_intcExcepAllDisable
 *
 *  @b Description
 *  @n This API disables all exceptions
 *     
 *
 *  @b Arguments
 *  @verbatim
         excepMask    Exception Mask
         excVal       Event Value
         prevState    Pre state informationT 
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
    CSL_IntcExcepEn   excepMask;                  
    CSL_BitMask32     excVal;            
    CSL_IntcEventEnableState *prevState;
     
        CSL_intcExcepAllDisable(excepMask, excVal, prevState);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcExcepAllDisable (
    CSL_IntcExcepEn             excepMask,
    CSL_BitMask32               excVal,
    CSL_BitMask32               *prevState
);

/*  ============================================================================
 *  @n@b CSL_intcExcepAllRestore
 *
 *  @b Description
 *  @n This API restores all exceptions 
 *     
 *
 *  @b Arguments
 *  @verbatim
         excepMask    Exception Mask 0/1/2/3
         
         prevState    BitMask to be restored
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
    CSL_IntcExcepEn   excepMask;                  
    CSL_IntcEventEnableState *prevState;
     
        CSL_intcExcepAllRestore(excepMask, prevState);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcExcepAllRestore (
    CSL_IntcExcepEn             excepMask,
    CSL_IntcGlobalEnableState   restoreVal
);

/*  ============================================================================
 *  @n@b CSL_intcExcepAllClear
 *
 *  @b Description
 *  @n This API clears all exceptions
 *     
 *
 *  @b Arguments
 *  @verbatim
         excepMask    Exception Mask
         
         excVal       Holder for the event bitmask to be cleared
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
    CSL_IntcExcepEn   excepMask;                  
    CSL_BitMask32     excVal;
     
        CSL_intcExcepAllClear(excepMask, excVal);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcExcepAllClear (
    CSL_IntcExcepEn excepMask,  
    CSL_BitMask32   excVal      
);

/*  ============================================================================
 *  @n@b CSL_intcExcepAllStatus
 *
 *  @b Description
 *  @n This API is to get the exception status query
 *     
 *
 *  @b Arguments
 *  @verbatim
         excepMask    Exception Mask
         
         status       status of exception
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
    CSL_IntcExcepEn   excepMask;                  
    CSL_BitMask32     *status;
     
        CSL_intcExcepAllStatus(excepMask, status);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcExcepAllStatus (
    CSL_IntcExcepEn     excepMask,
    CSL_BitMask32       *status   
);      

/*  ============================================================================
 *  @n@b CSL_intcQueryDropStatus
 *
 *  @b Description
 *  @n This API is to get the exception drop status query
 *     
 *
 *  @b Arguments
 *  @verbatim
         dropStat     place holder for the drop status
               
    @endverbatim
 *
 *  <b> Return Value </b> CSL_Status
 *  @li                   CSL_SOK on success
 *
 *  @b Example:
 *  @verbatim
        CSL_IntcDropStatus   *dropStat;
     
        CSL_intcQueryDropStatus(dropStat);
    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_intcQueryDropStatus (
    CSL_IntcDropStatus   *dropStat
);

/**
@}
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
/* string.h   v7.3.4                                                         */
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


 




static __inline size_t  strlen(const char *_string);

static __inline char *strcpy(char *_dest, const char *_src);
static __inline char *strncpy(char *_to, const char *_from, size_t _n);
static __inline char *strcat(char *_string1, const char *_string2);
static __inline char *strncat(char *_to, const char *_from, size_t _n);
static __inline char *strchr(const char *_string, int _c);
static __inline char *strrchr(const char *_string, int _c);

static __inline int  strcmp(const char *_string1, const char *_string2);
static __inline int  strncmp(const char *_string1, const char *_string2, size_t _n);

 int     strcoll(const char *_string1, const char *_string2);
 size_t  strxfrm(char *_to, const char *_from, size_t _n);
 char   *strpbrk(const char *_string, const char *_chs);
 size_t  strspn(const char *_string, const char *_chs);
 size_t  strcspn(const char *_string, const char *_chs);
 char   *strstr(const char *_string1, const char *_string2);
 char   *strtok(char *_str1, const char *_str2);
 char   *strerror(int _errno);

 void   *memmove(void *_s1, const void *_s2, size_t _n);
 void   *memcpy(void *_s1, const void *_s2, size_t _n);

static __inline int     memcmp(const void *_cs, const void *_ct, size_t _n);
static __inline void   *memchr(const void *_cs, int _c, size_t _n);

 void   *memset(void *_mem, int _ch, size_t _n);







static __inline size_t strlen(const char *string)
{
   size_t      n = (size_t)-1;
   const char *s = string;

   do n++; while (*s++);
   return n;
}

static __inline char *strcpy(register char *dest, register const char *src)
{
     register char       *d = dest;     
     register const char *s = src;

     while (*d++ = *s++);
     return dest;
}

static __inline char *strncpy(register char *dest,
		     register const char *src,
		     register size_t n)
{
     if (n) 
     {
	 register char       *d = dest;
	 register const char *s = src;
	 while ((*d++ = *s++) && --n);              /* COPY STRING         */
	 if (n-- > 1) do *d++ = '\0'; while (--n);  /* TERMINATION PADDING */
     }
     return dest;
}

static __inline char *strcat(char *string1, const char *string2)
{
   char       *s1 = string1;
   const char *s2 = string2;

   while (*s1) s1++;		     /* FIND END OF STRING   */
   while (*s1++ = *s2++);	     /* APPEND SECOND STRING */
   return string1;
}

static __inline char *strncat(char *dest, const char *src, register size_t n)
{
    if (n)
    {
	char       *d = dest;
	const char *s = src;

	while (*d) d++;                      /* FIND END OF STRING   */

	while (n--)
	  if (!(*d++ = *s++)) return dest; /* APPEND SECOND STRING */
	*d = 0;
    }
    return dest;
}

static __inline char *strchr(const char *string, int c)
{
   char        tch, ch  = c;
   const char *s        = string;

   for (;;)
   {
       if ((tch = *s) == ch) return (char *) s;
       if (!tch)             return (char *) 0;
       s++;
   }
}

static __inline char *strrchr(const char *string, int c)
{
   char        tch, ch = c;
   char       *result  = 0;
   const char *s       = string;

   for (;;)
   {
      if ((tch = *s) == ch) result = (char *) s;
      if (!tch) break;
      s++;
   }

   return result;
}

static __inline int strcmp(register const char *string1,
		  register const char *string2)
{
   register int c1, res;

   for (;;)
   {
       c1  = (unsigned char)*string1++;
       res = c1 - (unsigned char)*string2++;

       if (c1 == 0 || res != 0) break;
   }

   return res;
}

static __inline int strncmp(const char *string1, const char *string2, size_t n)
{
     if (n) 
     {
	 const char *s1 = string1;
	 const char *s2 = string2;
	 unsigned char cp;
	 int         result;

	 do 
	    if (result = (unsigned char)*s1++ - (cp = (unsigned char)*s2++))
                return result;
	 while (cp && --n);
     }
     return 0;
}

static __inline int memcmp(const void *cs, const void *ct, size_t n)
{
   if (n) 
   {
       const unsigned char *mem1 = (unsigned char *)cs;
       const unsigned char *mem2 = (unsigned char *)ct;
       int                 cp1, cp2;

       while ((cp1 = *mem1++) == (cp2 = *mem2++) && --n);
       return cp1 - cp2;
   }
   return 0;
}

static __inline void *memchr(const void *cs, int c, size_t n)
{
   if (n)
   {
      const unsigned char *mem = (unsigned char *)cs;   
      unsigned char        ch  = c;

      do 
         if ( *mem == ch ) return (void *)mem;
         else mem++;
      while (--n);
   }
   return 0;
}







/*  ============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2002, 2003, 2004, 2005, 2008
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
 
/* @file csl_intcAux.h
 *
 * @brief   Header file for functional layer of CSL
 *
 *  PATH  $(CSLPATH)\\inc
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Jun-2004 Ruchika Kharwar File Created
 *  16-Mar-2005 brn modified for doxygen documentation and removed redundant 
                    CSL_intcInterruptEnable, CSL_intcInterruptDisable and 
                    CSL_intcInterruptRestore functions.
    27-Mar-2006 ds  Removed Read access to Write only EVTSET[3] and EVTCLR[3] 
                    registers 
 * =============================================================================
 */
 



/* External definition for _CSL_intcEventOffsetMap */
extern Int8 *_CSL_intcEventOffsetMap;

/* External definition for _CSL_intcAllocMask */
extern CSL_BitMask32*    _CSL_intcAllocMask;

/* External definition for _CSL_intcEventHandlerRecord */
extern CSL_IntcEventHandlerRecord* _CSL_intcEventHandlerRecord;

/* External definition for _CSL_intcNumEvents */
extern Uint16 _CSL_intcNumEvents;

/*  ============================================================================
 *   @n@b CSL_intcMapEventVector
 *
 *   @b Description
 *      This API Maps the event to the given CPU vector
 *      
 *   @b Arguments
 *   @verbatim
        hInts    Handle to the intcs
        vectId   Intc vector identifier 
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Maps the event to the given CPU vector 
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcHandle     hIntc;
        CSL_IntcVectId     vectId;
        ...
        CSL_intcMapEventVector (hIntc, vectId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_intcMapEventVector (
    CSL_IntcEventId    eventId,
    CSL_IntcVectId     vectId
)
{
    
    Int         bitLow;
    
    if (vectId < CSL_INTC_VECTID_8) {
        bitLow = (vectId - 4) * 8;
        ((((CSL_IntcRegsOvly)(0x01800000))->INTMUX1) = ((((CSL_IntcRegsOvly)(0x01800000))->INTMUX1) &~ (((1 << ((bitLow+6) - (bitLow) + 1)) - 1) << (bitLow))) | (((eventId) & ((1 << ((bitLow+6) - (bitLow) + 1)) - 1)) << (bitLow)));
    } 
    else {
        if (vectId < CSL_INTC_VECTID_12) {
            bitLow = (vectId - 8) * 8;
            ((((CSL_IntcRegsOvly)(0x01800000))->INTMUX2) = ((((CSL_IntcRegsOvly)(0x01800000))->INTMUX2) &~ (((1 << ((bitLow+6) - (bitLow) + 1)) - 1) << (bitLow))) | (((eventId) & ((1 << ((bitLow+6) - (bitLow) + 1)) - 1)) << (bitLow)));
        } 
        else {
            bitLow = (vectId - 12) * 8;
            ((((CSL_IntcRegsOvly)(0x01800000))->INTMUX3) = ((((CSL_IntcRegsOvly)(0x01800000))->INTMUX3) &~ (((1 << ((bitLow+6) - (bitLow) + 1)) - 1) << (bitLow))) | (((eventId) & ((1 << ((bitLow+6) - (bitLow) + 1)) - 1)) << (bitLow)));
        }   
    }
}

/*  ============================================================================
 *   @n@b CSL_intcEventEnable
 *
 *   @b Description
 *      This API enables particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_IntcEventEnableState - Previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be enabled
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_IntcEventEnableState   eventStat;
        ...
        eventStat = CSL_intcEventEnable (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_IntcEventEnableState CSL_intcEventEnable (
    CSL_IntcEventId     eventId
)
{
    Int                      _x;
    Int                      _y;
    Int                      _regVal;
    CSL_IntcEventEnableState _oldState;
    
    _y = eventId >> 5;
    _x = eventId & 0x1f;
    _regVal = ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[_y];
    _oldState = (((_regVal) >> (_x)) & ((1 << ((_x) - (_x) + 1)) - 1));
    ((_regVal) = ((_regVal) &~ (((1 << ((_x) - (_x) + 1)) - 1) << (_x))) | (((0) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x)));
    ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[_y] = _regVal;
    
    return _oldState;
}

/*  ============================================================================
 *   @n@b CSL_intcEventDisable
 *
 *   @b Description
 *      This API disables particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_IntcEventEnableState - Previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be disabled
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_IntcEventEnableState   eventStat;
        ...
        eventStat = CSL_intcEventDisable (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_IntcEventEnableState  CSL_intcEventDisable (
    CSL_IntcEventId            eventId
)
{
    Int                       _x;
    Int                       _y;
    Int                      _regVal;
    CSL_IntcEventEnableState oldState;
    
    _y = eventId >> 5;
    _x = eventId & 0x1f;
    _regVal = ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[_y];
    oldState = (((_regVal) >> (_x)) & ((1 << ((_x) - (_x) + 1)) - 1));
    ((_regVal) = ((_regVal) &~ (((1 << ((_x) - (_x) + 1)) - 1) << (_x))) | (((1) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x)));
    ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[_y] = _regVal;
    
    return oldState;
}

/*  ============================================================================
 *   @n@b CSL_intcEventRestore
 *
 *   @b Description
 *      This API restores particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_IntcEventEnableState - Previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be restored
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_IntcEventEnableState   restoreVal;
        CSL_IntcEventEnableState   eventStat;
        ...
        eventStat = CSL_intcEventRestore (eventId, restoreVal);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcEventRestore(
    CSL_IntcEventId               eventId,
    CSL_IntcEventEnableState      restoreVal
)
{
    Int     _x;
    Int     _y;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    ((((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[_y]) = ((((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[_y]) &~ (((1 << ((_x) - (_x) + 1)) - 1) << (_x))) | (((restoreVal) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x)));
}

/*  ============================================================================
 *   @n@b CSL_intcEventSet
 *
 *   @b Description
 *      This API sets Event  (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will set
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        ...
        CSL_intcEventSet (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcEventSet(
    CSL_IntcEventId               eventId
)
{
    Int     _x;
    Int     _y;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    ((CSL_IntcRegsOvly)(0x01800000))->EVTSET[_y] = (((1) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x));
}

/*  ============================================================================
 *   @n@b CSL_intcEventClear
 *
 *   @b Description
 *      This API clears particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be cleared
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        ...
        CSL_intcEventClear (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcEventClear (
    CSL_IntcEventId               eventId
)
{
    Int     _x;
    Int     _y;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    ((CSL_IntcRegsOvly)(0x01800000))->EVTCLR[_y] = (((1) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x));
}

/*  ============================================================================
 *   @n@b CSL_intcCombinedEventClear
 *
 *   @b Description
 *      This API clears particular combined events 
 *      (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
        clearMask   BitMask of events to be cleared
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular combined event will be cleared
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        ...
        CSL_intcCombinedEventClear (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */

static inline void  CSL_intcCombinedEventClear(
    CSL_IntcEventId               eventId,
    CSL_BitMask32                 clearMask
)
{
    ((CSL_IntcRegsOvly)(0x01800000))->EVTCLR[eventId] = clearMask;
}

/*  ============================================================================
 *   @n@b CSL_intcCombinedEventGet
 *
 *   @b Description
 *      This API gets particular combined events 
 *      (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
                
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_BitMask32 - The combined events information 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_BitMask32              combEvntStat;
        ...
        combEvntStat = CSL_intcCombinedEventGet (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_BitMask32  CSL_intcCombinedEventGet(
   CSL_IntcEventId               eventId
)
{
    return (((CSL_IntcRegsOvly)(0x01800000))->MEVTFLAG[eventId]);
}

/*  ============================================================================
 *   @n@b CSL_intcCombinedEventEnable
 *
 *   @b Description
 *      This API enables particular combined events 
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
        enableMask  BitMask of events to be enabled     
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_BitMask32 - previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_BitMask32              enableMask;
        CSL_BitMask32              combEvntStat;
        ...
        combEvntStat = CSL_intcCombinedEventEnable (eventId, enableMask);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_BitMask32  CSL_intcCombinedEventEnable(
    CSL_IntcEventId               eventId,
    CSL_BitMask32                 enableMask
)
{
    CSL_BitMask32 evtMask = 
            ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[eventId];
    ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[eventId] = ~enableMask;
    
    return evtMask;
}

/** ============================================================================
 *   @n@b CSL_intcCombinedEventDisable
 *
 *   @b Description
 *      This API disables particular combined events 
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
        enableMask  BitMask of events to be disabled     
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_BitMask32 - previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_BitMask32              enableMask;
        CSL_BitMask32              combEvntStat;
        
        ...
        combEvntStat = CSL_intcCombinedEventDisable (eventId, enableMask);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_BitMask32  CSL_intcCombinedEventDisable (
    CSL_IntcEventId               eventId,
    CSL_BitMask32                 enableMask
)
{
    CSL_BitMask32 evtMask = 
            ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[eventId];
    ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[eventId] = enableMask;
    
    return evtMask ;    
}

/*  ============================================================================
 *   @n@b CSL_intcCombinedEventRestore
 *
 *   @b Description
 *      This API restores particular combined events 
 *      
 *   @b Arguments
 *   @verbatim
        eventId      event identifier
        restoreMask  BitMask of events to be restored     
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId             eventId;
        CSL_BitMask32              restoreMask
        ...
        CSL_intcCombinedEventRestore (eventId, restoreMask);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcCombinedEventRestore(
    CSL_IntcEventId               eventId,
    CSL_BitMask32                 restoreMask
)
{
    ((CSL_IntcRegsOvly)(0x01800000))->EVTMASK[eventId] = restoreMask;

}

/*  ============================================================================
 *   @n@b CSL_intcIntrDropEnable
 *
 *   @b Description
 *      This API enables interrupts for which drop detection 
 *      
 *   @b Arguments
 *   @verbatim
        dropMask  Vector id mask
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_BitMask32              dropMask
        ...
        CSL_intcIntrDropEnable (dropMask);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcInterruptDropEnable (
    CSL_BitMask32                dropMask        
)
{
    ((CSL_IntcRegsOvly)(0x01800000))->INTDMASK &= ~dropMask;
    
}

/*  ============================================================================
 *   @n@b CSL_intcIntrDropDisable
 *
 *   @b Description
 *      This API disables interrupts for which drop detection 
 *      
 *   @b Arguments
 *   @verbatim
        dropMask  Vector id mask
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_BitMask32              dropMask
        ...
        CSL_intcIntrDropDisable (dropMask);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcInterruptDropDisable (
    CSL_BitMask32                dropMask        
)
{
    ((CSL_IntcRegsOvly)(0x01800000))->INTDMASK  |= dropMask;
    
}

/*  ============================================================================
 *   @n@b CSL_intcInvokeEventHandle
 *
 *   @b Description
 *     This API is for the purpose of excption handler which will need to be
 * written by the user. This API invokes the event handler regisered by 
 *      the user at the time of event Open and event handler registration 
 *      
 *   @b Arguments
 *   @verbatim
        evtId  Event Id of the function to be invoked
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_SOK
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcEventId              evtId;
        CSL_Status                   status;
        ...
        status = CSL_intcInvokeEventHandle (evtId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_Status CSL_intcInvokeEventHandle (
    CSL_IntcEventId     evtId
)
{

    if (_CSL_intcEventOffsetMap[evtId] != (-1)) 
        _CSL_intcEventHandlerRecord[_CSL_intcEventOffsetMap[evtId]].handler (
            _CSL_intcEventHandlerRecord[_CSL_intcEventOffsetMap[evtId]].arg );
          
     return (1);
}

/*  ============================================================================
 *   @n@b CSL_intcQueryEventStatus
 *
 *   @b Description
 *      This API is to check whether a specified event is enabled or not 
 *
 *   @b Arguments
 *   @verbatim
        evtId      Event Id of the query event
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       Bool
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcEventId              evtId;
        Bool                         return;
        ...
        return = CSL_intcQueryEventStatus (evtId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline Bool CSL_intcQueryEventStatus(CSL_IntcEventId eventId)
{
    Int     _x;
    Int     _y;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    return ((Bool)((((((CSL_IntcRegsOvly)(0x01800000))->EVTFLAG[_y]) >> (_x)) & ((1 << ((_x) - (_x) + 1)) - 1))));
}

/* CPU Interrupt Handling routines */

/*  ============================================================================
 *   @n@b CSL_intcInterruptEnable
 *
 *   @b Description
 *      This API is enables Interrupt 
 *      
 *   @b Arguments
 *   @verbatim
        vectId      Vector Id of the query event
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       Uint32     - previous state
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId              vectId;
        Uint32                      return;
        ...
        return = CSL_intcInterruptEnable (vectId);
        ...
     @endverbatim
 * ===========================================================================
 */
Uint32 CSL_intcInterruptEnable (
    CSL_IntcVectId vectId
);

/*  ============================================================================
 *   @n@b CSL_intcInterruptDisable
 *
 *   @b Description
 *      This API is disables Interrupt 
 *      
 *   @b Arguments
 *   @verbatim
        vectId      Vector Id of the query event
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       Uint32     - previous state
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId              vectId;
        Uint32                      return;
        ...
        return = CSL_intcInterruptDisable (vectId);
        ...
     @endverbatim
 * ===========================================================================
 */
Uint32 CSL_intcInterruptDisable (
    CSL_IntcVectId vectId
);

/*  ============================================================================
 *   @n@b CSL_intcInterruptRestore
 *
 *   @b Description
 *      This API is restores Interrupt 
 *      
 *   @b Arguments
 *   @verbatim
        vectId      Vector Id of the query event
        restoreVal  Value to be restored
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None
 *       
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId              vectId;
        Uint32                      restore;
        ...
        CSL_intcInterruptRestore (vectId, restore);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_intcInterruptRestore ( 
    CSL_IntcVectId      vectId,
    Uint32              restoreVal
);

/*  ============================================================================
 *   @n@b CSL_intcInterruptSet
 *
 *   @b Description
 *      This API is sets interrupt(ISR) 
 *
 *   @b Arguments
 *   @verbatim
        vectId       Vector id to set

     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None
 *       
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId              vectId;
        ...
        CSL_intcInterruptSet (vectId);
        ...
     @endverbatim
 * ===========================================================================
 */
void CSL_intcInterruptSet ( 
    CSL_IntcVectId      vectId
);

/*  ============================================================================
 *   @n@b CSL_intcInterruptClear
 *
 *   @b Description
 *      This API is clears specified interrupt  
 *      
 *   @b Arguments
 *   @verbatim
        vectId       Vector id to cleared
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId              vectId;
        ...
        CSL_intcInterruptClear (vectId);
        ...
     @endverbatim
 * ===========================================================================
 */
void CSL_intcInterruptClear ( 
    CSL_IntcVectId      vectId
);

/*  ============================================================================
 *   @n@b CSL_intcQueryInterruptStatus
 *
 *   @b Description
 *      This API is to check whether a specified CPU interrupt is pending or not  
 *
 *   @b Arguments
 *   @verbatim
        vectId       Vector id to cleared

     @endverbatim
 *
 *   <b> Return Value </b> 
 *       Bool
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcVectId              vectId;
        Bool                        return;
        ...
        return = CSL_intcQueryInterruptStatus (vectId);
        ...
     @endverbatim
 * ===========================================================================
 */
Bool  CSL_intcQueryInterruptStatus (
    CSL_IntcVectId      vectId
);


/* Exception handling routines */

/*  ============================================================================
 *   @n@b CSL_intcExcepEnable
 *
 *   @b Description
 *      This API is enables the specific exception event  
 *      
 *   @b Arguments
 *   @verbatim
        eventId       event id to be enabled
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_IntcEventEnableState
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcEventId             eventId;
        CSL_IntcEventEnableState    return;
        ...
        return = CSL_intcExcepEnable (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_IntcEventEnableState  CSL_intcExcepEnable (
    CSL_IntcEventId      eventId
)
{
    Int                         _x;
    Int                         _y;
    Int                         _regVal;
    CSL_IntcEventEnableState    _oldState;
    
    _y = eventId >> 5;
    _x = eventId & 0x1f;
    _regVal = ((CSL_IntcRegsOvly)(0x01800000))->EXPMASK[_y];
    _oldState = (((_regVal) >> (_x)) & ((1 << ((_x) - (_x) + 1)) - 1));
    ((_regVal) = ((_regVal) &~ (((1 << ((_x) - (_x) + 1)) - 1) << (_x))) | (((0) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x)));
    ((CSL_IntcRegsOvly)(0x01800000))->EXPMASK[_y] = _regVal;
    
    return _oldState;
}

/*  ============================================================================
 *   @n@b CSL_intcExcepDisable
 *
 *   @b Description
 *      This API is disables the specific exception event  
 *      
 *   @b Arguments
 *   @verbatim
        eventId       event id to be disabled
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_IntcEventEnableState
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcEventId             eventId;
        CSL_IntcEventEnableState    return;
        ...
        return = CSL_intcExcepDisable (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_IntcEventEnableState  CSL_intcExcepDisable (
    CSL_IntcEventId            eventId
)
{
    Int                         _x;
    Int                         _y;
    Int                         _regVal;
    CSL_IntcEventEnableState    oldState;
    
    _y = eventId >> 5;
    _x = eventId & 0x1f;
    _regVal = ((CSL_IntcRegsOvly)(0x01800000))->EXPMASK[_y];
    oldState = (((_regVal) >> (_x)) & ((1 << ((_x) - (_x) + 1)) - 1));
    ((_regVal) = ((_regVal) &~ (((1 << ((_x) - (_x) + 1)) - 1) << (_x))) | (((1) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x)));
    ((CSL_IntcRegsOvly)(0x01800000))->EXPMASK[_y] = _regVal;
    
    return oldState;
}

/*  ============================================================================
 *   @n@b CSL_intcExcepRestore
 *
 *   @b Description
 *      This API restores the specific exception event 
 *      
 *   @b Arguments
 *   @verbatim
        eventId       event id to be restored 
        restoreVal    restore value
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcEventId             eventId;
        
        ...
        CSL_intcExcepRestore (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcExcepRestore (
    CSL_IntcEventId               eventId,
    Uint32                        restoreVal
)
{
    Int         _x;
    Int         _y;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    ((((CSL_IntcRegsOvly)(0x01800000))->EXPMASK[_y]) = ((((CSL_IntcRegsOvly)(0x01800000))->EXPMASK[_y]) &~ (((1 << ((_x) - (_x) + 1)) - 1) << (_x))) | (((restoreVal) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x)));
}

/*  ============================================================================
 *   @n@b CSL_intcExcepClear
 *
 *   @b Description
 *      This API clears the specific exception event 
 *      
 *   @b Arguments
 *   @verbatim
        eventId       event id to be cleared 
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_IntcEventId             eventId;
        
        ...
        CSL_intcExcepClear (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void  CSL_intcExcepClear (
    CSL_IntcEventId         eventId
)
{
    Int         _x;
    Int         _y;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    ((CSL_IntcRegsOvly)(0x01800000))->EVTCLR[_y] = (((1) & ((1 << ((_x) - (_x) + 1)) - 1)) << (_x));
}

/**
 *   @file  csl_semAux.h
 *
 *   @brief   
 *      This is the SEM Auxilary Header File which exposes the various
 *      CSL Functional Layer API's to configure the SEM Module.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2008, 2009, Texas Instruments, Inc.
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
 *   @file  csl_sem.h
 *
 *   @brief
 *      This is the main Header File for the SEM Module which defines all
 *      the data structures and exported API.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2008, 2009, Texas Instruments, Inc.
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


/* Minimum unit = 1 byte */

/*************************************************************************** Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 SEM_PID;
    volatile Uint32 SEM_SCRATCH;
    volatile Uint32 SEM_RST_RUN;
    volatile Uint32 SEM_EOI;
    volatile Uint8 RSVD0[240];
    volatile Uint32 SEM[32];
    volatile Uint8 RSVD1[128];
    volatile Uint32 ISEM[32];
    volatile Uint8 RSVD2[128];
    volatile Uint32 QSEM[32];
    volatile Uint8 RSVD3[128];
    volatile Uint32 SEMFLAGL_CLEAR[4];
    volatile Uint8 RSVD4[112];
    volatile Uint32 SEMFLAGL_SET[4];
    volatile Uint8 RSVD5[112];
    volatile Uint32 SEMERR;
    volatile Uint32 SEMERR_CLEAR;
    volatile Uint32 SEMERR_SET;
} CSL_SemRegs;

/*************************************************************************** Field Definition Macros
\**************************************************************************/

/* SEM_PID */









/* SEM_SCRATCH */



/* SEM_RST_RUN */




/* SEM_EOI */


/*----SELECT_INTERRUPT_REARM Tokens----*/


/* SEM */






/* ISEM */






/* QSEM */






/* SEMFLAGL */



































/* SEMFLAGL_CLEAR */



































/* SEMFLAGL_SET */

































/*----F Tokens----*/


/* SEMERR */




/*----ERR Tokens----*/


/* SEMERR_CLEAR */


/*----CLRERR Tokens----*/


/* SEMERR_SET */




/*----ERR Tokens----*/



/** @defgroup CSL_SEM_API Semaphore
 *
 * @section Introduction
 *
 * @subsection 
 *  None
 *
 * @subsection References
 *  None
 *
 */

/**
@defgroup CSL_SEM_SYMBOL  SEM Symbols Defined
@ingroup  CSL_SEM_API
*/
/**
@defgroup CSL_SEM_FUNCTION  SEM Functions
@ingroup  CSL_SEM_API
*/
/**
@addtogroup CSL_SEM_SYMBOL
@{
*/

/**
 *  Handle to access SEM registers.
 */

/**
@}
*/






/** @addtogroup CSL_SEM_FUNCTION
 @{ */

/** ============================================================================
 *   @n@b CSL_semSetEoi
 *
 *   @b Description
 *   @n This function sets the SEM Module EOI Register to rearm the interrupt line
 *      after processing an existing interrupt.
 *
 *   @b Arguments
     @verbatim
          eoiVal   Value to be written to the EOI register.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n SEM_SEM_EOI_SELECT_INTERRUPT_REARM
 *
 *   <b> Post Condition </b>
 *   @n Semaphore interrupts to the specific Master are reenabled.
 *
 *   @b Example
 *   @verbatim

        // Reenable Semaphore interrupts for CPU Core 0.
        CSL_semSetEoi (semHandle, CSL_SEM_REARM_SEMINT0);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_semSetEoi (Uint8 eoiVal)
{
    ((CSL_SemRegs*)(0x02640000))->SEM_EOI = (((eoiVal) << (0x00000000u)) & (0x000000FFu));
}         

/** ============================================================================
 *   @n@b CSL_semAcquireDirect
 *
 *   @b Description
 *   @n This function acquires a semaphore for direct access.
 *
 *   @b Arguments
     @verbatim
          semNum      Semaphore which is to be acquired.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  1 - Resource was available and has been allocated to the Master
 *   @n  0 - Resource was NOT available and has NOT been allocated to the Master
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n Semaphore is allocated to the Master on Success.
 *
 *   @b Reads
 *   @n SEM_SEM_FREE
 *
 *   @b Example
 *   @verbatim

        Uint8 status;

        // Acquire the semaphore number 2.
        status = CSL_semAcquireDirect (2);

     @endverbatim
 * =============================================================================
 */
static inline Uint8 CSL_semAcquireDirect (Uint8 semNum)
{
    /* Direct Access Request: Read from the SEMn register */
    return (((((CSL_SemRegs*)(0x02640000))->SEM[semNum]) & (0x00000001u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CSL_semAcquireIndirect
 *
 *   @b Description
 *   @n This function acquires a semaphore for indirect access.
 *
 *   @b Arguments
     @verbatim
          semNum      Semaphore which is to be acquired.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n Semaphore is placed into the request queue to be acquired.
 *
 *   @b Writes
 *   @n SEM_SEM_FREE=0
 *
 *   @b Example
 *   @verbatim

        // Acquire the semaphore number 2.
        CSL_semAcquireIndirect (2);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_semAcquireIndirect (Uint8 semNum)
{
    /* Indirect Access Request: Write a 0 to the SEMn register; to request for the resource. */
    ((CSL_SemRegs*)(0x02640000))->SEM[semNum] = (((0) << (0x00000000u)) & (0x00000001u));
}

/** ============================================================================
 *   @n@b CSL_semAcquireCombined
 *
 *   @b Description
 *   @n This function acquires a semaphore for combined access. 
 *
 *   @b Arguments
     @verbatim
          semNum      Semaphore which is to be acquired.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n Semaphore is acquired immediately if free else it is  placed into the request 
 *      queue to be acquired.
 *
 *   @b Reads
 *   @n SEM_ISEM_FREE
 *
 *   @b Example
 *   @verbatim

        Uint8 status;

        // Acquire the semaphore number 2.
        status = CSL_semAcquireCombined (2);

     @endverbatim
 * =============================================================================
 */
static inline Uint8 CSL_semAcquireCombined(Uint8 semNum)
{
    /* Combined Access Request: Read from the Indirect register */
    return (((((CSL_SemRegs*)(0x02640000))->ISEM[semNum]) & (0x00000001u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CSL_semReleaseSemaphore
 *
 *   @b Description
 *   @n This function is used to release a sempahore which had been acquired
 *      previously.
 *
 *   @b Arguments
     @verbatim
          semNum      Semaphore which is to be released.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n @a CSL_semAcquireDirect() or @a CSL_semAcquireCombined() @a CSL_semAcquireIndirect()
 *      must be called.
 *
 *   <b> Post Condition </b>
 *   @n Semaphore resource is freed up 
 *
 *   @b Writes
 *   @n SEM_SEM_FREE=1
 *
 *   @b Example
 *   @verbatim

        // Acquire the semaphore using the direct method. 
        CSL_semAcquireDirect (2);
        ...
        // Release the semaphore.
        CSL_semReleaseSemaphore (2);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_semReleaseSemaphore (Uint8 semNum)
{
    /* Semaphore is released up by writing a 1 to the SEMn register */
    ((CSL_SemRegs*)(0x02640000))->SEM[semNum] = (((1) << (0x00000000u)) & (0x00000001u));
}

/** ============================================================================
 *   @n@b CSL_semIsFree
 *
 *   @b Description
 *   @n This function checks if the specified semaphore is acquired or not?
 *
 *   @b Arguments
     @verbatim
          semNum      Semaphore which is to be queried.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  TRUE  - Semaphore is Free
 *   @n  FALSE - Semaphore is Available   
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n SEM_QSEM_FREE
 *
 *   @b Example
 *   @verbatim

        Bool isFree;

        // Check if Semaphore is available.
        isFree = CSL_semIsFree (2);

     @endverbatim
 * =============================================================================
 */
static inline Bool CSL_semIsFree(Uint8 semNum)
{
    /* Read the Query Status register to determine the semaphore status. */
    return (Bool)(((((CSL_SemRegs*)(0x02640000))->QSEM[semNum]) & (0x00000001u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CSL_semGetResourceOwner
 *
 *   @b Description
 *   @n This function returns the resource owner for the specific semaphore.
 *
 *   @b Arguments
     @verbatim
          semNum      Semaphore Number whose resource owner is to be retreived.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n Semaphore Resource Owner.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n SEM_QSEM_OWNER
 *
 *   @b Example
 *   @verbatim

        Bool    isFree;
        Uint8   owner;

        // Check if Semaphore is available.
        isFree = CSL_semIsFree (2);
        if (isFree == FALSE)
        {
            // Resource is acquired. Get the owner 
            owner = CSL_semGetResourceOwner(2);
        }

     @endverbatim
 * =============================================================================
 */
static inline Uint8 CSL_semGetResourceOwner(Uint8 semNum)
{
    return (Uint8)(((((CSL_SemRegs*)(0x02640000))->QSEM[semNum]) & (0x0000FF00u)) >> (0x00000008u));
}

/** ============================================================================
 *   @n@b CSL_semGetFlags
 *
 *   @b Description
 *   @n This function returns the contents of the SEMFLAG register for a specific
 *      master. This is used in the indirect or combined access method to determine
 *      if a resource has been acquired. The corresponding bit indicates that the 
 *      specific resource number which had been requested is now available.
 *
 *   @b Arguments
     @verbatim
          masterId      Master ID for which the SEMFLAG register is read.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n Uint32
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n SEM_SEMFLAGL_CLEAR
 *
 *   @b Example
 *   @verbatim

        Uint32  semFlags;

        // Read the bits of the semaphore flag register for master 0.
        semFlags = CSL_semGetFlags(0);

     @endverbatim
 * =============================================================================
 */
static inline Uint32 CSL_semGetFlags(Uint8 masterId)
{
    return (Uint32)((CSL_SemRegs*)(0x02640000))->SEMFLAGL_CLEAR[masterId];
}

/** ============================================================================
 *   @n@b CSL_semClearFlags
 *
 *   @b Description
 *   @n This function is used by the host by the host to inform the SEM Module 
 *      that the resource which had been marked as FREE has been processed by
 *      the host.
 *
 *   @b Arguments
     @verbatim
          masterId      Master ID for which the SEMFLAG register is read.
          semFlags      Semaphore Flags retreived through the CSL_semGetFlags API.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Writes
 *   @n SEM_SEMFLAGL_CLEAR
 *
 *   @b Affects
 *   @n SEM_SEMFLAGL_CLEAR
 *
 *   @b Example
 *   @verbatim

        Uint32  semFlags;

        // Read the bits of the semaphore flag register for master 0.
        semFlags = CSL_semGetFlags(0);
        ...
        // Clear the bits of the semaphore flag register for master 0.
        CSL_semClearFlags (0, semFlags);

     @endverbatim
 * =============================================================================
 */
static inline void CSL_semClearFlags(Uint8 masterId, Uint32 semFlags)
{
    /* Write the value to the CLEAR Register. */ 
    ((CSL_SemRegs*)(0x02640000))->SEMFLAGL_CLEAR[masterId] = semFlags;
}

/** ============================================================================
 *   @n@b CSL_semGetErrorCode
 *
 *   @b Description
 *   @n This function is used to get the Error code.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  Error Code 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n SEM_SEMERR_ERR
 *
 *   @b Example
 *   @verbatim

        Uint8  errCode;

        // Check if there is an error which has been reported.
        errCode = CSL_semGetErrorCode();
        if (errCode != 0)
        {
            // Semaphore Module has reported an Error. 
        }

     @endverbatim
 * =============================================================================
 */
static inline Uint8 CSL_semGetErrorCode (void)
{
    return (Uint8)(((((CSL_SemRegs*)(0x02640000))->SEMERR) & (0x00000007u)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CSL_semGetErrorSemaphoreNumber
 *
 *   @b Description
 *   @n This function is used to get the semaphore number which is in error.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  Semaphore Number which caused the error.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n SEM_SEMERR_SEMNUM
 *
 *   @b Example
 *   @verbatim

        Uint8  errCode;
        Uint8  semNumber;

        // Check if there is an error which has been reported.
        errCode = CSL_semGetErrorCode();
        if (errCode != 0)
        {
            // Semaphore Module has reported an error; get the semaphore number. 
            semNumber = CSL_semGetErrorSemaphoreNumber(); 
            ...
        }

     @endverbatim
 * =============================================================================
 */
static inline Uint8 CSL_semGetErrorSemaphoreNumber (void)
{
    return (Uint8)(((((CSL_SemRegs*)(0x02640000))->SEMERR) & (0x000001F8u)) >> (0x00000003u));
}

/** ============================================================================
 *   @n@b CSL_semGetErrorFaultID
 *
 *   @b Description
 *   @n This function is used to get the resource owner which caused the error.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  Resource Number which caused the error.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n SEM_SEMERR_FAULTID
 *
 *   @b Example
 *   @verbatim

        Uint8  errCode;
        Uint8  semNumber;
        Uint8  faultId;

        // Check if there is an error which has been reported.
        errCode = CSL_semGetErrorCode();
        if (errCode != 0)
        {
            // Semaphore Module has reported an error; get the semaphore number. 
            semNumber = CSL_semGetErrorSemaphoreNumber(); 

            // Get the fault id. 
            faultId = CSL_semGetErrorFaultID();
            ...
        }

     @endverbatim
 * =============================================================================
 */
static inline Uint8 CSL_semGetErrorFaultID (void)
{
    return (Uint8)(((((CSL_SemRegs*)(0x02640000))->SEMERR) & (0x0000FE00u)) >> (0x00000009u));
}

/** ============================================================================
 *   @n@b CSL_semClearError
 *
 *   @b Description
 *   @n This function is used to clear the semaphore module error.
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
 *   @n  None
 *
 *   @b Writes
 *   @n SEM_SEMERR_CLEAR_CLRERR=1
 *
 *   @b Example
 *   @verbatim

        Uint8  errCode;
        Uint8  semNumber;
        Uint8  faultId;

        // Check if there is an error which has been reported.
        errCode = CSL_semGetErrorCode();
        if (errCode != 0)
        {
            // Semaphore Module has reported an error; get the semaphore number. 
            semNumber = CSL_semGetErrorSemaphoreNumber(); 

            // Get the fault id. 
            faultId = CSL_semGetErrorFaultID();
            ...

            // Clear the error.
            CSL_semClearError ();
        }

     @endverbatim
 * =============================================================================
 */
static inline void CSL_semClearError (void)
{
    ((CSL_SemRegs*)(0x02640000))->SEMERR_CLEAR = (((1) << (0x00000000u)) & (0x00000001u));
}

/**
@}
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


typedef enum HSEM_NUM
{
	HSEM_IIPC = 0,
	
	HSEM_COMMAND_C0,
	HSEM_COMMAND_C1,
	HSEM_COMMAND_C2,
	HSEM_COMMAND_C3,
	HSEM_COMMAND_C4,
	HSEM_COMMAND_C5,
	HSEM_COMMAND_C6,
	HSEM_COMMAND_C7,

	HSEM_BURSTINFO_C1,
	HSEM_BURSTINFO_C2,
	HSEM_BURSTINFO_C3,
	HSEM_BURSTINFO_C4,
	HSEM_BURSTINFO_C5,
	HSEM_BURSTINFO_C6,
	HSEM_BURSTINFO_C7,


	HSEM_BURST_C0,
	HSEM_L2PACKET_C1,
	HSEM_L2PACKET_C2,
	HSEM_L2PACKET_C3,
	HSEM_L2PACKET_C4,
	HSEM_L2PACKET_C5,
	HSEM_L2PACKET_C6,
	HSEM_L2PACKET_C7,
//###### commented for testing : by remesh
//	HSEM_L2PACKET_C0,
//	HSEM_BURST_C1,
//	HSEM_BURST_C2,
//	HSEM_BURST_C3,
//	HSEM_BURST_C4,
//	HSEM_BURST_C5,
//	HSEM_BURST_C6,
//	HSEM_BURST_C7,
// end of commented lines
	HSEM_GBTS,
	HSEM_EMAC,

	HSEM_TJOB =28,
	HSEM_LAST = 29,
	MAX_SEM = 32,
	HSEM_INVALID
}HSEM_NUM;

typedef struct stHSEM
{
	//CSL_SemObj    oSemObj; // not required in c6678
	//CSL_SemParam  oParam; // not required in c6678
	//volatile CSL_SemHandle hSemHandle; // not required in c6678
	HSEM_NUM Sem_Number; // included by remesh to make HSEM_Init(),HSEM_Lock(),HSEM_Unlock() compactable with c6678 CSL APIs
}Hsem;


extern void HSEM_ModuleInit();
extern void HSEM_Init(Hsem *pThis, UINT8 nSemNum);
extern void HSEM_Lock(Hsem *pThis);
extern void HSEM_Unlock(Hsem *pThis);

/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Task.h> (Utilities.pjt)
//
//  Subsystem: 
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for creating 
//  tasks, Signals, Binary Sem Locks. This module shall be considered
//  as OS absraction.
//
//  Dependencies, Limitations, and Design Notes:
//  	
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/


// #include <xdc\std.h> // its included in DataType.h
//#include <tsk.h>
/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:35; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */



/*
 * ======== module ti.sysbios.knl.Clock ========
 */

typedef struct ti_sysbios_knl_Clock_Module_State ti_sysbios_knl_Clock_Module_State;
typedef struct ti_sysbios_knl_Clock_Params ti_sysbios_knl_Clock_Params;
typedef struct ti_sysbios_knl_Clock_Object ti_sysbios_knl_Clock_Object;
typedef struct ti_sysbios_knl_Clock_Struct ti_sysbios_knl_Clock_Struct;
typedef ti_sysbios_knl_Clock_Object* ti_sysbios_knl_Clock_Handle;
typedef struct ti_sysbios_knl_Clock_Object__ ti_sysbios_knl_Clock_Instance_State;
typedef ti_sysbios_knl_Clock_Object* ti_sysbios_knl_Clock_Instance;

/*
 * ======== module ti.sysbios.knl.Idle ========
 */


/*
 * ======== module ti.sysbios.knl.Intrinsics ========
 */

typedef struct ti_sysbios_knl_Intrinsics_Fxns__ ti_sysbios_knl_Intrinsics_Fxns__;
typedef const ti_sysbios_knl_Intrinsics_Fxns__* ti_sysbios_knl_Intrinsics_Module;

/*
 * ======== module ti.sysbios.knl.Event ========
 */

typedef struct ti_sysbios_knl_Event_PendElem ti_sysbios_knl_Event_PendElem;
typedef struct ti_sysbios_knl_Event_Params ti_sysbios_knl_Event_Params;
typedef struct ti_sysbios_knl_Event_Object ti_sysbios_knl_Event_Object;
typedef struct ti_sysbios_knl_Event_Struct ti_sysbios_knl_Event_Struct;
typedef ti_sysbios_knl_Event_Object* ti_sysbios_knl_Event_Handle;
typedef struct ti_sysbios_knl_Event_Object__ ti_sysbios_knl_Event_Instance_State;
typedef ti_sysbios_knl_Event_Object* ti_sysbios_knl_Event_Instance;

/*
 * ======== module ti.sysbios.knl.Mailbox ========
 */

typedef struct ti_sysbios_knl_Mailbox_MbxElem ti_sysbios_knl_Mailbox_MbxElem;
typedef struct ti_sysbios_knl_Mailbox_Params ti_sysbios_knl_Mailbox_Params;
typedef struct ti_sysbios_knl_Mailbox_Object ti_sysbios_knl_Mailbox_Object;
typedef struct ti_sysbios_knl_Mailbox_Struct ti_sysbios_knl_Mailbox_Struct;
typedef ti_sysbios_knl_Mailbox_Object* ti_sysbios_knl_Mailbox_Handle;
typedef struct ti_sysbios_knl_Mailbox_Object__ ti_sysbios_knl_Mailbox_Instance_State;
typedef ti_sysbios_knl_Mailbox_Object* ti_sysbios_knl_Mailbox_Instance;

/*
 * ======== module ti.sysbios.knl.Queue ========
 */

typedef struct ti_sysbios_knl_Queue_Elem ti_sysbios_knl_Queue_Elem;
typedef struct ti_sysbios_knl_Queue_Params ti_sysbios_knl_Queue_Params;
typedef struct ti_sysbios_knl_Queue_Object ti_sysbios_knl_Queue_Object;
typedef struct ti_sysbios_knl_Queue_Struct ti_sysbios_knl_Queue_Struct;
typedef ti_sysbios_knl_Queue_Object* ti_sysbios_knl_Queue_Handle;
typedef struct ti_sysbios_knl_Queue_Object__ ti_sysbios_knl_Queue_Instance_State;
typedef ti_sysbios_knl_Queue_Object* ti_sysbios_knl_Queue_Instance;

/*
 * ======== module ti.sysbios.knl.Semaphore ========
 */

typedef struct ti_sysbios_knl_Semaphore_PendElem ti_sysbios_knl_Semaphore_PendElem;
typedef struct ti_sysbios_knl_Semaphore_Params ti_sysbios_knl_Semaphore_Params;
typedef struct ti_sysbios_knl_Semaphore_Object ti_sysbios_knl_Semaphore_Object;
typedef struct ti_sysbios_knl_Semaphore_Struct ti_sysbios_knl_Semaphore_Struct;
typedef ti_sysbios_knl_Semaphore_Object* ti_sysbios_knl_Semaphore_Handle;
typedef struct ti_sysbios_knl_Semaphore_Object__ ti_sysbios_knl_Semaphore_Instance_State;
typedef ti_sysbios_knl_Semaphore_Object* ti_sysbios_knl_Semaphore_Instance;

/*
 * ======== module ti.sysbios.knl.Swi ========
 */

typedef struct ti_sysbios_knl_Swi_HookSet ti_sysbios_knl_Swi_HookSet;
typedef struct ti_sysbios_knl_Swi_Module_State ti_sysbios_knl_Swi_Module_State;
typedef struct ti_sysbios_knl_Swi_Params ti_sysbios_knl_Swi_Params;
typedef struct ti_sysbios_knl_Swi_Object ti_sysbios_knl_Swi_Object;
typedef struct ti_sysbios_knl_Swi_Struct ti_sysbios_knl_Swi_Struct;
typedef ti_sysbios_knl_Swi_Object* ti_sysbios_knl_Swi_Handle;
typedef struct ti_sysbios_knl_Swi_Object__ ti_sysbios_knl_Swi_Instance_State;
typedef ti_sysbios_knl_Swi_Object* ti_sysbios_knl_Swi_Instance;

/*
 * ======== module ti.sysbios.knl.Task ========
 */

typedef struct ti_sysbios_knl_Task_Stat ti_sysbios_knl_Task_Stat;
typedef struct ti_sysbios_knl_Task_HookSet ti_sysbios_knl_Task_HookSet;
typedef struct ti_sysbios_knl_Task_PendElem ti_sysbios_knl_Task_PendElem;
typedef struct ti_sysbios_knl_Task_Module_State ti_sysbios_knl_Task_Module_State;
typedef struct ti_sysbios_knl_Task_Params ti_sysbios_knl_Task_Params;
typedef struct ti_sysbios_knl_Task_Object ti_sysbios_knl_Task_Object;
typedef struct ti_sysbios_knl_Task_Struct ti_sysbios_knl_Task_Struct;
typedef ti_sysbios_knl_Task_Object* ti_sysbios_knl_Task_Handle;
typedef struct ti_sysbios_knl_Task_Object__ ti_sysbios_knl_Task_Instance_State;
typedef ti_sysbios_knl_Task_Object* ti_sysbios_knl_Task_Instance;

/*
 * ======== module ti.sysbios.knl.Intrinsics_SupportProxy ========
 */

typedef struct ti_sysbios_knl_Intrinsics_SupportProxy_Fxns__ ti_sysbios_knl_Intrinsics_SupportProxy_Fxns__;
typedef const ti_sysbios_knl_Intrinsics_SupportProxy_Fxns__* ti_sysbios_knl_Intrinsics_SupportProxy_Module;

/*
 * ======== module ti.sysbios.knl.Task_SupportProxy ========
 */

typedef struct ti_sysbios_knl_Task_SupportProxy_Fxns__ ti_sysbios_knl_Task_SupportProxy_Fxns__;
typedef const ti_sysbios_knl_Task_SupportProxy_Fxns__* ti_sysbios_knl_Task_SupportProxy_Module;



/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
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
 * @(#) xdc-y22
 */



/*
 * ======== interface ti.sysbios.interfaces.IHwi ========
 */

typedef struct ti_sysbios_interfaces_IHwi_HookSet ti_sysbios_interfaces_IHwi_HookSet;
typedef struct ti_sysbios_interfaces_IHwi_StackInfo ti_sysbios_interfaces_IHwi_StackInfo;
typedef struct ti_sysbios_interfaces_IHwi_Fxns__ ti_sysbios_interfaces_IHwi_Fxns__;
typedef const ti_sysbios_interfaces_IHwi_Fxns__* ti_sysbios_interfaces_IHwi_Module;
typedef struct ti_sysbios_interfaces_IHwi_Params ti_sysbios_interfaces_IHwi_Params;
typedef struct ti_sysbios_interfaces_IHwi___Object { ti_sysbios_interfaces_IHwi_Fxns__* __fxns; xdc_Bits32 __label; } *ti_sysbios_interfaces_IHwi_Handle;

/*
 * ======== interface ti.sysbios.interfaces.ITaskSupport ========
 */

typedef struct ti_sysbios_interfaces_ITaskSupport_Fxns__ ti_sysbios_interfaces_ITaskSupport_Fxns__;
typedef const ti_sysbios_interfaces_ITaskSupport_Fxns__* ti_sysbios_interfaces_ITaskSupport_Module;

/*
 * ======== interface ti.sysbios.interfaces.ITimer ========
 */

typedef struct ti_sysbios_interfaces_ITimer_Fxns__ ti_sysbios_interfaces_ITimer_Fxns__;
typedef const ti_sysbios_interfaces_ITimer_Fxns__* ti_sysbios_interfaces_ITimer_Module;
typedef struct ti_sysbios_interfaces_ITimer_Params ti_sysbios_interfaces_ITimer_Params;
typedef struct ti_sysbios_interfaces_ITimer___Object { ti_sysbios_interfaces_ITimer_Fxns__* __fxns; xdc_Bits32 __label; } *ti_sysbios_interfaces_ITimer_Handle;

/*
 * ======== interface ti.sysbios.interfaces.ITimerSupport ========
 */

typedef struct ti_sysbios_interfaces_ITimerSupport_Fxns__ ti_sysbios_interfaces_ITimerSupport_Fxns__;
typedef const ti_sysbios_interfaces_ITimerSupport_Fxns__* ti_sysbios_interfaces_ITimerSupport_Module;

/*
 * ======== interface ti.sysbios.interfaces.ITimestamp ========
 */

typedef struct ti_sysbios_interfaces_ITimestamp_Fxns__ ti_sysbios_interfaces_ITimestamp_Fxns__;
typedef const ti_sysbios_interfaces_ITimestamp_Fxns__* ti_sysbios_interfaces_ITimestamp_Module;

/*
 * ======== interface ti.sysbios.interfaces.IIntrinsicsSupport ========
 */

typedef struct ti_sysbios_interfaces_IIntrinsicsSupport_Fxns__ ti_sysbios_interfaces_IIntrinsicsSupport_Fxns__;
typedef const ti_sysbios_interfaces_IIntrinsicsSupport_Fxns__* ti_sysbios_interfaces_IIntrinsicsSupport_Module;

/*
 * ======== interface ti.sysbios.interfaces.ICache ========
 */

typedef struct ti_sysbios_interfaces_ICache_Fxns__ ti_sysbios_interfaces_ICache_Fxns__;
typedef const ti_sysbios_interfaces_ICache_Fxns__* ti_sysbios_interfaces_ICache_Module;



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

/* FuncPtr */
typedef void (*ti_sysbios_interfaces_ITaskSupport_FuncPtr)(void);


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_interfaces_ITaskSupport_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*start)(xdc_Ptr, ti_sysbios_interfaces_ITaskSupport_FuncPtr, ti_sysbios_interfaces_ITaskSupport_FuncPtr, xdc_runtime_Error_Block*);
    void (*swap)(xdc_Ptr*, xdc_Ptr*);
    xdc_Bool (*checkStack)(xdc_Char*, xdc_SizeT);
    xdc_SizeT (*stackUsed)(xdc_Char*, xdc_SizeT);
    xdc_UInt (*getStackAlignment)(void);
    xdc_SizeT (*getDefaultStackSize)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base ti_sysbios_interfaces_ITaskSupport_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sysbios_interfaces_ITaskSupport_Module_id( ti_sysbios_interfaces_ITaskSupport_Module mod )
{
    return mod->__sysp->__mid;
}

/* start */
static inline xdc_Ptr ti_sysbios_interfaces_ITaskSupport_start( ti_sysbios_interfaces_ITaskSupport_Module __inst, xdc_Ptr curTask, ti_sysbios_interfaces_ITaskSupport_FuncPtr enter, ti_sysbios_interfaces_ITaskSupport_FuncPtr exit, xdc_runtime_Error_Block* eb )
{
    return __inst->start(curTask, enter, exit, eb);
}

/* swap */
static inline void ti_sysbios_interfaces_ITaskSupport_swap( ti_sysbios_interfaces_ITaskSupport_Module __inst, xdc_Ptr* oldtskContext, xdc_Ptr* newtskContext )
{
    __inst->swap(oldtskContext, newtskContext);
}

/* checkStack */
static inline xdc_Bool ti_sysbios_interfaces_ITaskSupport_checkStack( ti_sysbios_interfaces_ITaskSupport_Module __inst, xdc_Char* stack, xdc_SizeT size )
{
    return __inst->checkStack(stack, size);
}

/* stackUsed */
static inline xdc_SizeT ti_sysbios_interfaces_ITaskSupport_stackUsed( ti_sysbios_interfaces_ITaskSupport_Module __inst, xdc_Char* stack, xdc_SizeT size )
{
    return __inst->stackUsed(stack, size);
}

/* getStackAlignment */
static inline xdc_UInt ti_sysbios_interfaces_ITaskSupport_getStackAlignment( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return __inst->getStackAlignment();
}

/* getDefaultStackSize */
static inline xdc_SizeT ti_sysbios_interfaces_ITaskSupport_getDefaultStackSize( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return __inst->getDefaultStackSize();
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* start_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_interfaces_ITaskSupport_start_FxnT)(xdc_Ptr, ti_sysbios_interfaces_ITaskSupport_FuncPtr, ti_sysbios_interfaces_ITaskSupport_FuncPtr, xdc_runtime_Error_Block*);
static inline ti_sysbios_interfaces_ITaskSupport_start_FxnT ti_sysbios_interfaces_ITaskSupport_start_fxnP( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return (ti_sysbios_interfaces_ITaskSupport_start_FxnT)__inst->start;
}

/* swap_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITaskSupport_swap_FxnT)(xdc_Ptr*, xdc_Ptr*);
static inline ti_sysbios_interfaces_ITaskSupport_swap_FxnT ti_sysbios_interfaces_ITaskSupport_swap_fxnP( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return (ti_sysbios_interfaces_ITaskSupport_swap_FxnT)__inst->swap;
}

/* checkStack_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_interfaces_ITaskSupport_checkStack_FxnT)(xdc_Char*, xdc_SizeT);
static inline ti_sysbios_interfaces_ITaskSupport_checkStack_FxnT ti_sysbios_interfaces_ITaskSupport_checkStack_fxnP( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return (ti_sysbios_interfaces_ITaskSupport_checkStack_FxnT)__inst->checkStack;
}

/* stackUsed_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_sysbios_interfaces_ITaskSupport_stackUsed_FxnT)(xdc_Char*, xdc_SizeT);
static inline ti_sysbios_interfaces_ITaskSupport_stackUsed_FxnT ti_sysbios_interfaces_ITaskSupport_stackUsed_fxnP( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return (ti_sysbios_interfaces_ITaskSupport_stackUsed_FxnT)__inst->stackUsed;
}

/* getStackAlignment_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_interfaces_ITaskSupport_getStackAlignment_FxnT)(void);
static inline ti_sysbios_interfaces_ITaskSupport_getStackAlignment_FxnT ti_sysbios_interfaces_ITaskSupport_getStackAlignment_fxnP( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return (ti_sysbios_interfaces_ITaskSupport_getStackAlignment_FxnT)__inst->getStackAlignment;
}

/* getDefaultStackSize_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_sysbios_interfaces_ITaskSupport_getDefaultStackSize_FxnT)(void);
static inline ti_sysbios_interfaces_ITaskSupport_getDefaultStackSize_FxnT ti_sysbios_interfaces_ITaskSupport_getDefaultStackSize_fxnP( ti_sysbios_interfaces_ITaskSupport_Module __inst )
{
    return (ti_sysbios_interfaces_ITaskSupport_getDefaultStackSize_FxnT)__inst->getDefaultStackSize;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) ti.sysbios.interfaces; 2, 0, 0, 0,545; 3-20-2012 14:03:23; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  ======== Assert__prologue.h ========
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
 * ======== STATE STRUCTURES ========
 */


/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:33; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */


/*
 *  ======== xdc_runtime_Assert_Id ========
 */
typedef xdc_Bits32 xdc_runtime_Assert_Id;

/*
 *  ======== Module__MID ========
 *  This definition allows non-module code to
 *  use the Assert module.  This symbol is normally defined in each
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

/* Id */


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Assert_Module__diagsEnabled;
extern far const CT__xdc_runtime_Assert_Module__diagsEnabled xdc_runtime_Assert_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Assert_Module__diagsIncluded;
extern far const CT__xdc_runtime_Assert_Module__diagsIncluded xdc_runtime_Assert_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_Assert_Module__diagsMask;
extern far const CT__xdc_runtime_Assert_Module__diagsMask xdc_runtime_Assert_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Assert_Module__gateObj;
extern far const CT__xdc_runtime_Assert_Module__gateObj xdc_runtime_Assert_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Assert_Module__gatePrms;
extern far const CT__xdc_runtime_Assert_Module__gatePrms xdc_runtime_Assert_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Assert_Module__id;
extern far const CT__xdc_runtime_Assert_Module__id xdc_runtime_Assert_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Assert_Module__loggerDefined;
extern far const CT__xdc_runtime_Assert_Module__loggerDefined xdc_runtime_Assert_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Assert_Module__loggerObj;
extern far const CT__xdc_runtime_Assert_Module__loggerObj xdc_runtime_Assert_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Assert_Module__loggerFxn0;
extern far const CT__xdc_runtime_Assert_Module__loggerFxn0 xdc_runtime_Assert_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Assert_Module__loggerFxn1;
extern far const CT__xdc_runtime_Assert_Module__loggerFxn1 xdc_runtime_Assert_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Assert_Module__loggerFxn2;
extern far const CT__xdc_runtime_Assert_Module__loggerFxn2 xdc_runtime_Assert_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Assert_Module__loggerFxn4;
extern far const CT__xdc_runtime_Assert_Module__loggerFxn4 xdc_runtime_Assert_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Assert_Module__loggerFxn8;
extern far const CT__xdc_runtime_Assert_Module__loggerFxn8 xdc_runtime_Assert_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_Assert_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_Assert_Module__startupDoneFxn xdc_runtime_Assert_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Assert_Object__count;
extern far const CT__xdc_runtime_Assert_Object__count xdc_runtime_Assert_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Assert_Object__heap;
extern far const CT__xdc_runtime_Assert_Object__heap xdc_runtime_Assert_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Assert_Object__sizeof;
extern far const CT__xdc_runtime_Assert_Object__sizeof xdc_runtime_Assert_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Assert_Object__table;
extern far const CT__xdc_runtime_Assert_Object__table xdc_runtime_Assert_Object__table__C;

/* E_assertFailed */
typedef xdc_runtime_Error_Id CT__xdc_runtime_Assert_E_assertFailed;
extern far const CT__xdc_runtime_Assert_E_assertFailed xdc_runtime_Assert_E_assertFailed__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_Assert_Module__startupDone__S( void );

/* raise__I */

extern void xdc_runtime_Assert_raise__I( xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Assert_Id id );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_Assert_Module__id xdc_runtime_Assert_Module_id( void ) 
{
    return xdc_runtime_Assert_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Assert_Module_hasMask( void ) 
{
    return xdc_runtime_Assert_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Assert_Module_getMask( void ) 
{
    return xdc_runtime_Assert_Module__diagsMask__C != 0 ? *xdc_runtime_Assert_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_Assert_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_Assert_Module__diagsMask__C != 0) *xdc_runtime_Assert_Module__diagsMask__C = mask;
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
 *  ======== xdc_runtime_Assert_getMask ========
 *  Convert an id into a mask
 */

/*
 *  ======== xdc_runtime_Assert_isTrue ========
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
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:32; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
 *     CONVERTORS
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
 * @(#) xdc-y22
 */



/*
 * ======== module ti.sysbios.hal.Hwi ========
 */

typedef struct ti_sysbios_hal_Hwi_Fxns__ ti_sysbios_hal_Hwi_Fxns__;
typedef const ti_sysbios_hal_Hwi_Fxns__* ti_sysbios_hal_Hwi_Module;
typedef struct ti_sysbios_hal_Hwi_Params ti_sysbios_hal_Hwi_Params;
typedef struct ti_sysbios_hal_Hwi_Object ti_sysbios_hal_Hwi_Object;
typedef struct ti_sysbios_hal_Hwi_Struct ti_sysbios_hal_Hwi_Struct;
typedef ti_sysbios_hal_Hwi_Object* ti_sysbios_hal_Hwi_Handle;
typedef struct ti_sysbios_hal_Hwi_Object__ ti_sysbios_hal_Hwi_Instance_State;
typedef ti_sysbios_hal_Hwi_Object* ti_sysbios_hal_Hwi_Instance;

/*
 * ======== module ti.sysbios.hal.Timer ========
 */

typedef struct ti_sysbios_hal_Timer_Fxns__ ti_sysbios_hal_Timer_Fxns__;
typedef const ti_sysbios_hal_Timer_Fxns__* ti_sysbios_hal_Timer_Module;
typedef struct ti_sysbios_hal_Timer_Params ti_sysbios_hal_Timer_Params;
typedef struct ti_sysbios_hal_Timer_Object ti_sysbios_hal_Timer_Object;
typedef struct ti_sysbios_hal_Timer_Struct ti_sysbios_hal_Timer_Struct;
typedef ti_sysbios_hal_Timer_Object* ti_sysbios_hal_Timer_Handle;
typedef struct ti_sysbios_hal_Timer_Object__ ti_sysbios_hal_Timer_Instance_State;
typedef ti_sysbios_hal_Timer_Object* ti_sysbios_hal_Timer_Instance;

/*
 * ======== module ti.sysbios.hal.TimerNull ========
 */

typedef struct ti_sysbios_hal_TimerNull_Fxns__ ti_sysbios_hal_TimerNull_Fxns__;
typedef const ti_sysbios_hal_TimerNull_Fxns__* ti_sysbios_hal_TimerNull_Module;
typedef struct ti_sysbios_hal_TimerNull_Params ti_sysbios_hal_TimerNull_Params;
typedef struct ti_sysbios_hal_TimerNull_Object ti_sysbios_hal_TimerNull_Object;
typedef struct ti_sysbios_hal_TimerNull_Struct ti_sysbios_hal_TimerNull_Struct;
typedef ti_sysbios_hal_TimerNull_Object* ti_sysbios_hal_TimerNull_Handle;
typedef struct ti_sysbios_hal_TimerNull_Object__ ti_sysbios_hal_TimerNull_Instance_State;
typedef ti_sysbios_hal_TimerNull_Object* ti_sysbios_hal_TimerNull_Instance;

/*
 * ======== module ti.sysbios.hal.Cache ========
 */

typedef struct ti_sysbios_hal_Cache_Fxns__ ti_sysbios_hal_Cache_Fxns__;
typedef const ti_sysbios_hal_Cache_Fxns__* ti_sysbios_hal_Cache_Module;

/*
 * ======== module ti.sysbios.hal.CacheNull ========
 */

typedef struct ti_sysbios_hal_CacheNull_Fxns__ ti_sysbios_hal_CacheNull_Fxns__;
typedef const ti_sysbios_hal_CacheNull_Fxns__* ti_sysbios_hal_CacheNull_Module;

/*
 * ======== module ti.sysbios.hal.Hwi_HwiProxy ========
 */

typedef struct ti_sysbios_hal_Hwi_HwiProxy_Fxns__ ti_sysbios_hal_Hwi_HwiProxy_Fxns__;
typedef const ti_sysbios_hal_Hwi_HwiProxy_Fxns__* ti_sysbios_hal_Hwi_HwiProxy_Module;
typedef struct ti_sysbios_hal_Hwi_HwiProxy_Params ti_sysbios_hal_Hwi_HwiProxy_Params;
typedef struct ti_sysbios_interfaces_IHwi___Object *ti_sysbios_hal_Hwi_HwiProxy_Handle;

/*
 * ======== module ti.sysbios.hal.Timer_TimerProxy ========
 */

typedef struct ti_sysbios_hal_Timer_TimerProxy_Fxns__ ti_sysbios_hal_Timer_TimerProxy_Fxns__;
typedef const ti_sysbios_hal_Timer_TimerProxy_Fxns__* ti_sysbios_hal_Timer_TimerProxy_Module;
typedef struct ti_sysbios_hal_Timer_TimerProxy_Params ti_sysbios_hal_Timer_TimerProxy_Params;
typedef struct ti_sysbios_interfaces_ITimer___Object *ti_sysbios_hal_Timer_TimerProxy_Handle;

/*
 * ======== module ti.sysbios.hal.Cache_CacheProxy ========
 */

typedef struct ti_sysbios_hal_Cache_CacheProxy_Fxns__ ti_sysbios_hal_Cache_CacheProxy_Fxns__;
typedef const ti_sysbios_hal_Cache_CacheProxy_Fxns__* ti_sysbios_hal_Cache_CacheProxy_Module;



/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
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

/* FuncPtr */
typedef void (*ti_sysbios_interfaces_ITimer_FuncPtr)(xdc_UArg);

/* ANY */

/* StartMode */
enum ti_sysbios_interfaces_ITimer_StartMode {
    ti_sysbios_interfaces_ITimer_StartMode_AUTO,
    ti_sysbios_interfaces_ITimer_StartMode_USER
};
typedef enum ti_sysbios_interfaces_ITimer_StartMode ti_sysbios_interfaces_ITimer_StartMode;

/* RunMode */
enum ti_sysbios_interfaces_ITimer_RunMode {
    ti_sysbios_interfaces_ITimer_RunMode_CONTINUOUS,
    ti_sysbios_interfaces_ITimer_RunMode_ONESHOT,
    ti_sysbios_interfaces_ITimer_RunMode_DYNAMIC
};
typedef enum ti_sysbios_interfaces_ITimer_RunMode ti_sysbios_interfaces_ITimer_RunMode;

/* Status */
enum ti_sysbios_interfaces_ITimer_Status {
    ti_sysbios_interfaces_ITimer_Status_INUSE,
    ti_sysbios_interfaces_ITimer_Status_FREE
};
typedef enum ti_sysbios_interfaces_ITimer_Status ti_sysbios_interfaces_ITimer_Status;

/* PeriodType */
enum ti_sysbios_interfaces_ITimer_PeriodType {
    ti_sysbios_interfaces_ITimer_PeriodType_MICROSECS,
    ti_sysbios_interfaces_ITimer_PeriodType_COUNTS
};
typedef enum ti_sysbios_interfaces_ITimer_PeriodType ti_sysbios_interfaces_ITimer_PeriodType;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_interfaces_ITimer_Args__create {
    xdc_Int id;
    ti_sysbios_interfaces_ITimer_FuncPtr tickFxn;
} ti_sysbios_interfaces_ITimer_Args__create;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_interfaces_ITimer_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_interfaces_ITimer_RunMode runMode;
    ti_sysbios_interfaces_ITimer_StartMode startMode;
    xdc_UArg arg;
    xdc_UInt32 period;
    ti_sysbios_interfaces_ITimer_PeriodType periodType;
    xdc_runtime_Types_FreqHz extFreq;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_interfaces_ITimer_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_UInt (*getNumTimers)(void);
    ti_sysbios_interfaces_ITimer_Status (*getStatus)(xdc_UInt);
    void (*startup)(void);
    xdc_UInt32 (*getMaxTicks)(void*, xdc_UInt32);
    void (*setNextTick)(void*, xdc_UInt32, xdc_UInt32);
    void (*start)(void*);
    void (*stop)(void*);
    void (*setPeriod)(void*, xdc_UInt32);
    xdc_Bool (*setPeriodMicroSecs)(void*, xdc_UInt32);
    xdc_UInt32 (*getPeriod)(void*);
    xdc_UInt32 (*getCount)(void*);
    void (*getFreq)(void*, xdc_runtime_Types_FreqHz*);
    ti_sysbios_interfaces_ITimer_FuncPtr (*getFunc)(void*, xdc_UArg*);
    void (*setFunc)(void*, ti_sysbios_interfaces_ITimer_FuncPtr, xdc_UArg);
    void (*trigger)(void*, xdc_UInt32);
    xdc_UInt32 (*getExpiredCounts)(void*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base ti_sysbios_interfaces_ITimer_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
static inline ti_sysbios_interfaces_ITimer_Handle ti_sysbios_interfaces_ITimer_create( ti_sysbios_interfaces_ITimer_Module __mod, xdc_Int id, ti_sysbios_interfaces_ITimer_FuncPtr tickFxn, const ti_sysbios_interfaces_ITimer_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_interfaces_ITimer_Args__create __args;
    __args.id = id;
    __args.tickFxn = tickFxn;
    return (ti_sysbios_interfaces_ITimer_Handle) __mod->__sysp->__create(0, 0, &__args, (const xdc_UChar*)__prms, sizeof (ti_sysbios_interfaces_ITimer_Params), __eb);
}

/* delete */
static inline void ti_sysbios_interfaces_ITimer_delete( ti_sysbios_interfaces_ITimer_Handle* instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}

/* Handle_to_Module */
static inline ti_sysbios_interfaces_ITimer_Module ti_sysbios_interfaces_ITimer_Handle_to_Module( ti_sysbios_interfaces_ITimer_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_interfaces_ITimer_Handle_label( ti_sysbios_interfaces_ITimer_Handle inst, xdc_runtime_Types_Label* lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sysbios_interfaces_ITimer_Module_id( ti_sysbios_interfaces_ITimer_Module mod )
{
    return mod->__sysp->__mid;
}

/* getNumTimers */
static inline xdc_UInt ti_sysbios_interfaces_ITimer_getNumTimers( ti_sysbios_interfaces_ITimer_Module __inst )
{
    return __inst->getNumTimers();
}

/* getStatus */
static inline ti_sysbios_interfaces_ITimer_Status ti_sysbios_interfaces_ITimer_getStatus( ti_sysbios_interfaces_ITimer_Module __inst, xdc_UInt id )
{
    return __inst->getStatus(id);
}

/* startup */
static inline void ti_sysbios_interfaces_ITimer_startup( ti_sysbios_interfaces_ITimer_Module __inst )
{
    __inst->startup();
}

/* getMaxTicks */
static inline xdc_UInt32 ti_sysbios_interfaces_ITimer_getMaxTicks( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_UInt32 periodCounts )
{
    return __inst->__fxns->getMaxTicks((void*)__inst, periodCounts);
}

/* setNextTick */
static inline void ti_sysbios_interfaces_ITimer_setNextTick( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_UInt32 newPeriod, xdc_UInt32 countsPerTick )
{
    __inst->__fxns->setNextTick((void*)__inst, newPeriod, countsPerTick);
}

/* start */
static inline void ti_sysbios_interfaces_ITimer_start( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    __inst->__fxns->start((void*)__inst);
}

/* stop */
static inline void ti_sysbios_interfaces_ITimer_stop( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    __inst->__fxns->stop((void*)__inst);
}

/* setPeriod */
static inline void ti_sysbios_interfaces_ITimer_setPeriod( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_UInt32 period )
{
    __inst->__fxns->setPeriod((void*)__inst, period);
}

/* setPeriodMicroSecs */
static inline xdc_Bool ti_sysbios_interfaces_ITimer_setPeriodMicroSecs( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_UInt32 microsecs )
{
    return __inst->__fxns->setPeriodMicroSecs((void*)__inst, microsecs);
}

/* getPeriod */
static inline xdc_UInt32 ti_sysbios_interfaces_ITimer_getPeriod( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return __inst->__fxns->getPeriod((void*)__inst);
}

/* getCount */
static inline xdc_UInt32 ti_sysbios_interfaces_ITimer_getCount( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return __inst->__fxns->getCount((void*)__inst);
}

/* getFreq */
static inline void ti_sysbios_interfaces_ITimer_getFreq( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_runtime_Types_FreqHz* freq )
{
    __inst->__fxns->getFreq((void*)__inst, freq);
}

/* getFunc */
static inline ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_interfaces_ITimer_getFunc( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_UArg* arg )
{
    return __inst->__fxns->getFunc((void*)__inst, arg);
}

/* setFunc */
static inline void ti_sysbios_interfaces_ITimer_setFunc( ti_sysbios_interfaces_ITimer_Handle __inst, ti_sysbios_interfaces_ITimer_FuncPtr fxn, xdc_UArg arg )
{
    __inst->__fxns->setFunc((void*)__inst, fxn, arg);
}

/* trigger */
static inline void ti_sysbios_interfaces_ITimer_trigger( ti_sysbios_interfaces_ITimer_Handle __inst, xdc_UInt32 cycles )
{
    __inst->__fxns->trigger((void*)__inst, cycles);
}

/* getExpiredCounts */
static inline xdc_UInt32 ti_sysbios_interfaces_ITimer_getExpiredCounts( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return __inst->__fxns->getExpiredCounts((void*)__inst);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getNumTimers_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_interfaces_ITimer_getNumTimers_FxnT)(void);
static inline ti_sysbios_interfaces_ITimer_getNumTimers_FxnT ti_sysbios_interfaces_ITimer_getNumTimers_fxnP( ti_sysbios_interfaces_ITimer_Module __inst )
{
    return (ti_sysbios_interfaces_ITimer_getNumTimers_FxnT)__inst->getNumTimers;
}

/* getStatus_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_ITimer_Status (*ti_sysbios_interfaces_ITimer_getStatus_FxnT)(xdc_UInt);
static inline ti_sysbios_interfaces_ITimer_getStatus_FxnT ti_sysbios_interfaces_ITimer_getStatus_fxnP( ti_sysbios_interfaces_ITimer_Module __inst )
{
    return (ti_sysbios_interfaces_ITimer_getStatus_FxnT)__inst->getStatus;
}

/* startup_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_startup_FxnT)(void);
static inline ti_sysbios_interfaces_ITimer_startup_FxnT ti_sysbios_interfaces_ITimer_startup_fxnP( ti_sysbios_interfaces_ITimer_Module __inst )
{
    return (ti_sysbios_interfaces_ITimer_startup_FxnT)__inst->startup;
}

/* getMaxTicks_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_interfaces_ITimer_getMaxTicks_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_interfaces_ITimer_getMaxTicks_FxnT ti_sysbios_interfaces_ITimer_getMaxTicks_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_getMaxTicks_FxnT)__inst->__fxns->getMaxTicks;
}

/* setNextTick_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_setNextTick_FxnT)(void*, xdc_UInt32, xdc_UInt32);
static inline ti_sysbios_interfaces_ITimer_setNextTick_FxnT ti_sysbios_interfaces_ITimer_setNextTick_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_setNextTick_FxnT)__inst->__fxns->setNextTick;
}

/* start_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_start_FxnT)(void*);
static inline ti_sysbios_interfaces_ITimer_start_FxnT ti_sysbios_interfaces_ITimer_start_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_start_FxnT)__inst->__fxns->start;
}

/* stop_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_stop_FxnT)(void*);
static inline ti_sysbios_interfaces_ITimer_stop_FxnT ti_sysbios_interfaces_ITimer_stop_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_stop_FxnT)__inst->__fxns->stop;
}

/* setPeriod_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_setPeriod_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_interfaces_ITimer_setPeriod_FxnT ti_sysbios_interfaces_ITimer_setPeriod_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_setPeriod_FxnT)__inst->__fxns->setPeriod;
}

/* setPeriodMicroSecs_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_interfaces_ITimer_setPeriodMicroSecs_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_interfaces_ITimer_setPeriodMicroSecs_FxnT ti_sysbios_interfaces_ITimer_setPeriodMicroSecs_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_setPeriodMicroSecs_FxnT)__inst->__fxns->setPeriodMicroSecs;
}

/* getPeriod_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_interfaces_ITimer_getPeriod_FxnT)(void*);
static inline ti_sysbios_interfaces_ITimer_getPeriod_FxnT ti_sysbios_interfaces_ITimer_getPeriod_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_getPeriod_FxnT)__inst->__fxns->getPeriod;
}

/* getCount_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_interfaces_ITimer_getCount_FxnT)(void*);
static inline ti_sysbios_interfaces_ITimer_getCount_FxnT ti_sysbios_interfaces_ITimer_getCount_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_getCount_FxnT)__inst->__fxns->getCount;
}

/* getFreq_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_getFreq_FxnT)(void*, xdc_runtime_Types_FreqHz*);
static inline ti_sysbios_interfaces_ITimer_getFreq_FxnT ti_sysbios_interfaces_ITimer_getFreq_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_getFreq_FxnT)__inst->__fxns->getFreq;
}

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_ITimer_FuncPtr (*ti_sysbios_interfaces_ITimer_getFunc_FxnT)(void*, xdc_UArg*);
static inline ti_sysbios_interfaces_ITimer_getFunc_FxnT ti_sysbios_interfaces_ITimer_getFunc_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_getFunc_FxnT)__inst->__fxns->getFunc;
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_setFunc_FxnT)(void*, ti_sysbios_interfaces_ITimer_FuncPtr, xdc_UArg);
static inline ti_sysbios_interfaces_ITimer_setFunc_FxnT ti_sysbios_interfaces_ITimer_setFunc_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_setFunc_FxnT)__inst->__fxns->setFunc;
}

/* trigger_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_ITimer_trigger_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_interfaces_ITimer_trigger_FxnT ti_sysbios_interfaces_ITimer_trigger_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_trigger_FxnT)__inst->__fxns->trigger;
}

/* getExpiredCounts_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_interfaces_ITimer_getExpiredCounts_FxnT)(void*);
static inline ti_sysbios_interfaces_ITimer_getExpiredCounts_FxnT ti_sysbios_interfaces_ITimer_getExpiredCounts_fxnP( ti_sysbios_interfaces_ITimer_Handle __inst )
{
    return (ti_sysbios_interfaces_ITimer_getExpiredCounts_FxnT)__inst->__fxns->getExpiredCounts;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) ti.sysbios.interfaces; 2, 0, 0, 0,545; 3-20-2012 14:03:23; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
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
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
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
 *  @(#) ti.sysbios.interfaces; 2, 0, 0, 0,545; 3-20-2012 14:03:23; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FuncPtr */
typedef ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_TimerProxy_FuncPtr;

/* ANY */

/* StartMode */
typedef ti_sysbios_interfaces_ITimer_StartMode ti_sysbios_hal_Timer_TimerProxy_StartMode;

/* RunMode */
typedef ti_sysbios_interfaces_ITimer_RunMode ti_sysbios_hal_Timer_TimerProxy_RunMode;

/* Status */
typedef ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_TimerProxy_Status;

/* PeriodType */
typedef ti_sysbios_interfaces_ITimer_PeriodType ti_sysbios_hal_Timer_TimerProxy_PeriodType;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_hal_Timer_TimerProxy_Args__create {
    xdc_Int id;
    ti_sysbios_interfaces_ITimer_FuncPtr tickFxn;
} ti_sysbios_hal_Timer_TimerProxy_Args__create;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_hal_Timer_TimerProxy_Module__diagsEnabled;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__diagsEnabled ti_sysbios_hal_Timer_TimerProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_hal_Timer_TimerProxy_Module__diagsIncluded;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__diagsIncluded ti_sysbios_hal_Timer_TimerProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_hal_Timer_TimerProxy_Module__diagsMask;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__diagsMask ti_sysbios_hal_Timer_TimerProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_TimerProxy_Module__gateObj;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__gateObj ti_sysbios_hal_Timer_TimerProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_TimerProxy_Module__gatePrms;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__gatePrms ti_sysbios_hal_Timer_TimerProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_hal_Timer_TimerProxy_Module__id;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__id ti_sysbios_hal_Timer_TimerProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerDefined;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerDefined ti_sysbios_hal_Timer_TimerProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerObj;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerObj ti_sysbios_hal_Timer_TimerProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn0;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn0 ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn1;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn1 ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn2;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn2 ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn4;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn4 ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn8;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn8 ti_sysbios_hal_Timer_TimerProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_hal_Timer_TimerProxy_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Module__startupDoneFxn ti_sysbios_hal_Timer_TimerProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_hal_Timer_TimerProxy_Object__count;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Object__count ti_sysbios_hal_Timer_TimerProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_hal_Timer_TimerProxy_Object__heap;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Object__heap ti_sysbios_hal_Timer_TimerProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_hal_Timer_TimerProxy_Object__sizeof;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Object__sizeof ti_sysbios_hal_Timer_TimerProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_TimerProxy_Object__table;
extern far const CT__ti_sysbios_hal_Timer_TimerProxy_Object__table ti_sysbios_hal_Timer_TimerProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_hal_Timer_TimerProxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_interfaces_ITimer_RunMode runMode;
    ti_sysbios_interfaces_ITimer_StartMode startMode;
    xdc_UArg arg;
    xdc_UInt32 period;
    ti_sysbios_interfaces_ITimer_PeriodType periodType;
    xdc_runtime_Types_FreqHz extFreq;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_hal_Timer_TimerProxy_Struct {
    const ti_sysbios_hal_Timer_TimerProxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_hal_Timer_TimerProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_UInt (*getNumTimers)(void);
    ti_sysbios_interfaces_ITimer_Status (*getStatus)(xdc_UInt);
    void (*startup)(void);
    xdc_UInt32 (*getMaxTicks)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_UInt32);
    void (*setNextTick)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_UInt32, xdc_UInt32);
    void (*start)(ti_sysbios_hal_Timer_TimerProxy_Handle);
    void (*stop)(ti_sysbios_hal_Timer_TimerProxy_Handle);
    void (*setPeriod)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_UInt32);
    xdc_Bool (*setPeriodMicroSecs)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_UInt32);
    xdc_UInt32 (*getPeriod)(ti_sysbios_hal_Timer_TimerProxy_Handle);
    xdc_UInt32 (*getCount)(ti_sysbios_hal_Timer_TimerProxy_Handle);
    void (*getFreq)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_runtime_Types_FreqHz*);
    ti_sysbios_interfaces_ITimer_FuncPtr (*getFunc)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_UArg*);
    void (*setFunc)(ti_sysbios_hal_Timer_TimerProxy_Handle, ti_sysbios_interfaces_ITimer_FuncPtr, xdc_UArg);
    void (*trigger)(ti_sysbios_hal_Timer_TimerProxy_Handle, xdc_UInt32);
    xdc_UInt32 (*getExpiredCounts)(ti_sysbios_hal_Timer_TimerProxy_Handle);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const ti_sysbios_hal_Timer_TimerProxy_Fxns__ ti_sysbios_hal_Timer_TimerProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_hal_Timer_TimerProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_hal_Timer_TimerProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_hal_Timer_TimerProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_hal_Timer_TimerProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_hal_Timer_TimerProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_hal_Timer_TimerProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_hal_Timer_TimerProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_hal_Timer_TimerProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_hal_Timer_TimerProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool ti_sysbios_hal_Timer_TimerProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr ti_sysbios_hal_Timer_TimerProxy_Proxy__delegate__S( void );

/* getNumTimers__E */

extern xdc_UInt ti_sysbios_hal_Timer_TimerProxy_getNumTimers__E( void );

extern xdc_UInt ti_sysbios_hal_Timer_TimerProxy_getNumTimers__R( void );

/* getStatus__E */

extern ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_TimerProxy_getStatus__E( xdc_UInt id );

extern ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_TimerProxy_getStatus__R( xdc_UInt id );

/* startup__E */

extern void ti_sysbios_hal_Timer_TimerProxy_startup__E( void );

extern void ti_sysbios_hal_Timer_TimerProxy_startup__R( void );

/* getMaxTicks__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getMaxTicks__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 periodCounts );

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getMaxTicks__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 periodCounts );

/* setNextTick__E */

extern void ti_sysbios_hal_Timer_TimerProxy_setNextTick__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 newPeriod, xdc_UInt32 countsPerTick );

extern void ti_sysbios_hal_Timer_TimerProxy_setNextTick__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 newPeriod, xdc_UInt32 countsPerTick );

/* start__E */

extern void ti_sysbios_hal_Timer_TimerProxy_start__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

extern void ti_sysbios_hal_Timer_TimerProxy_start__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

/* stop__E */

extern void ti_sysbios_hal_Timer_TimerProxy_stop__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

extern void ti_sysbios_hal_Timer_TimerProxy_stop__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

/* setPeriod__E */

extern void ti_sysbios_hal_Timer_TimerProxy_setPeriod__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 period );

extern void ti_sysbios_hal_Timer_TimerProxy_setPeriod__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 period );

/* setPeriodMicroSecs__E */

extern xdc_Bool ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 microsecs );

extern xdc_Bool ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 microsecs );

/* getPeriod__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getPeriod__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getPeriod__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

/* getCount__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getCount__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getCount__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

/* getFreq__E */

extern void ti_sysbios_hal_Timer_TimerProxy_getFreq__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_runtime_Types_FreqHz* freq );

extern void ti_sysbios_hal_Timer_TimerProxy_getFreq__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_runtime_Types_FreqHz* freq );

/* getFunc__E */

extern ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_TimerProxy_getFunc__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UArg* arg );

extern ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_TimerProxy_getFunc__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UArg* arg );

/* setFunc__E */

extern void ti_sysbios_hal_Timer_TimerProxy_setFunc__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, ti_sysbios_interfaces_ITimer_FuncPtr fxn, xdc_UArg arg );

extern void ti_sysbios_hal_Timer_TimerProxy_setFunc__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, ti_sysbios_interfaces_ITimer_FuncPtr fxn, xdc_UArg arg );

/* trigger__E */

extern void ti_sysbios_hal_Timer_TimerProxy_trigger__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 cycles );

extern void ti_sysbios_hal_Timer_TimerProxy_trigger__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst, xdc_UInt32 cycles );

/* getExpiredCounts__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts__E( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );

extern xdc_UInt32 ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts__R( ti_sysbios_hal_Timer_TimerProxy_Handle __inst );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getMaxTicks_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_TimerProxy_getMaxTicks_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_TimerProxy_getMaxTicks_FxnT ti_sysbios_hal_Timer_TimerProxy_getMaxTicks_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_getMaxTicks_FxnT)ti_sysbios_hal_Timer_TimerProxy_getMaxTicks__E; 
}

/* setNextTick_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_setNextTick_FxnT)(void*, xdc_UInt32, xdc_UInt32);
static inline ti_sysbios_hal_Timer_TimerProxy_setNextTick_FxnT ti_sysbios_hal_Timer_TimerProxy_setNextTick_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_setNextTick_FxnT)ti_sysbios_hal_Timer_TimerProxy_setNextTick__E; 
}

/* start_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_start_FxnT)(void*);
static inline ti_sysbios_hal_Timer_TimerProxy_start_FxnT ti_sysbios_hal_Timer_TimerProxy_start_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_start_FxnT)ti_sysbios_hal_Timer_TimerProxy_start__E; 
}

/* stop_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_stop_FxnT)(void*);
static inline ti_sysbios_hal_Timer_TimerProxy_stop_FxnT ti_sysbios_hal_Timer_TimerProxy_stop_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_stop_FxnT)ti_sysbios_hal_Timer_TimerProxy_stop__E; 
}

/* setPeriod_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_setPeriod_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_TimerProxy_setPeriod_FxnT ti_sysbios_hal_Timer_TimerProxy_setPeriod_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_setPeriod_FxnT)ti_sysbios_hal_Timer_TimerProxy_setPeriod__E; 
}

/* setPeriodMicroSecs_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs_FxnT ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs_FxnT)ti_sysbios_hal_Timer_TimerProxy_setPeriodMicroSecs__E; 
}

/* getPeriod_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_TimerProxy_getPeriod_FxnT)(void*);
static inline ti_sysbios_hal_Timer_TimerProxy_getPeriod_FxnT ti_sysbios_hal_Timer_TimerProxy_getPeriod_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_getPeriod_FxnT)ti_sysbios_hal_Timer_TimerProxy_getPeriod__E; 
}

/* getCount_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_TimerProxy_getCount_FxnT)(void*);
static inline ti_sysbios_hal_Timer_TimerProxy_getCount_FxnT ti_sysbios_hal_Timer_TimerProxy_getCount_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_getCount_FxnT)ti_sysbios_hal_Timer_TimerProxy_getCount__E; 
}

/* getFreq_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_getFreq_FxnT)(void*, xdc_runtime_Types_FreqHz*);
static inline ti_sysbios_hal_Timer_TimerProxy_getFreq_FxnT ti_sysbios_hal_Timer_TimerProxy_getFreq_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_getFreq_FxnT)ti_sysbios_hal_Timer_TimerProxy_getFreq__E; 
}

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_ITimer_FuncPtr (*ti_sysbios_hal_Timer_TimerProxy_getFunc_FxnT)(void*, xdc_UArg*);
static inline ti_sysbios_hal_Timer_TimerProxy_getFunc_FxnT ti_sysbios_hal_Timer_TimerProxy_getFunc_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_getFunc_FxnT)ti_sysbios_hal_Timer_TimerProxy_getFunc__E; 
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_setFunc_FxnT)(void*, ti_sysbios_interfaces_ITimer_FuncPtr, xdc_UArg);
static inline ti_sysbios_hal_Timer_TimerProxy_setFunc_FxnT ti_sysbios_hal_Timer_TimerProxy_setFunc_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_setFunc_FxnT)ti_sysbios_hal_Timer_TimerProxy_setFunc__E; 
}

/* trigger_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_TimerProxy_trigger_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_TimerProxy_trigger_FxnT ti_sysbios_hal_Timer_TimerProxy_trigger_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_trigger_FxnT)ti_sysbios_hal_Timer_TimerProxy_trigger__E; 
}

/* getExpiredCounts_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts_FxnT)(void*);
static inline ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts_FxnT ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts_fxnP( void )
{
    return (ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts_FxnT)ti_sysbios_hal_Timer_TimerProxy_getExpiredCounts__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sysbios_interfaces_ITimer_Module ti_sysbios_hal_Timer_TimerProxy_Module_upCast( void )
{
    return (ti_sysbios_interfaces_ITimer_Module)ti_sysbios_hal_Timer_TimerProxy_Proxy__delegate__S();
}

/* Module_to_ti_sysbios_interfaces_ITimer */

/* Handle_upCast */
static inline ti_sysbios_interfaces_ITimer_Handle ti_sysbios_hal_Timer_TimerProxy_Handle_upCast( ti_sysbios_hal_Timer_TimerProxy_Handle i )
{
    return (ti_sysbios_interfaces_ITimer_Handle)i;
}

/* Handle_to_ti_sysbios_interfaces_ITimer */

/* Handle_downCast */
static inline ti_sysbios_hal_Timer_TimerProxy_Handle ti_sysbios_hal_Timer_TimerProxy_Handle_downCast( ti_sysbios_interfaces_ITimer_Handle i )
{
    ti_sysbios_interfaces_ITimer_Handle i2 = (ti_sysbios_interfaces_ITimer_Handle)i;
if (ti_sysbios_hal_Timer_TimerProxy_Proxy__abstract__S()) return (ti_sysbios_hal_Timer_TimerProxy_Handle)i;
    return (void*)i2->__fxns == (void*)ti_sysbios_hal_Timer_TimerProxy_Proxy__delegate__S() ? (ti_sysbios_hal_Timer_TimerProxy_Handle)i : 0;
}

/* Handle_from_ti_sysbios_interfaces_ITimer */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_hal_Timer_TimerProxy_Module__id ti_sysbios_hal_Timer_TimerProxy_Module_id( void ) 
{
    return ti_sysbios_hal_Timer_TimerProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */

/* Params_init */
static inline void ti_sysbios_hal_Timer_TimerProxy_Params_init( ti_sysbios_hal_Timer_TimerProxy_Params* prms ) 
{
    if (prms) {
        ti_sysbios_hal_Timer_TimerProxy_Params__init__S(prms, 0, sizeof(ti_sysbios_hal_Timer_TimerProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_hal_Timer_TimerProxy_Params_copy( ti_sysbios_hal_Timer_TimerProxy_Params* dst, const ti_sysbios_hal_Timer_TimerProxy_Params* src ) 
{
    if (dst) {
        ti_sysbios_hal_Timer_TimerProxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_hal_Timer_TimerProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline ti_sysbios_hal_Timer_TimerProxy_Handle ti_sysbios_hal_Timer_TimerProxy_create( xdc_Int id, ti_sysbios_interfaces_ITimer_FuncPtr tickFxn, const ti_sysbios_hal_Timer_TimerProxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_hal_Timer_TimerProxy_Args__create __args;
    __args.id = id;
    __args.tickFxn = tickFxn;
    return (ti_sysbios_hal_Timer_TimerProxy_Handle)ti_sysbios_hal_Timer_TimerProxy_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_hal_Timer_TimerProxy_Params), __eb);
}

/* delete */
static inline void ti_sysbios_hal_Timer_TimerProxy_delete( ti_sysbios_hal_Timer_TimerProxy_Handle* instp )
{
    ti_sysbios_hal_Timer_TimerProxy_Object__delete__S(instp);
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

/* FuncPtr */
typedef ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_FuncPtr;

/* ANY */

/* StartMode */
typedef ti_sysbios_interfaces_ITimer_StartMode ti_sysbios_hal_Timer_StartMode;

/* RunMode */
typedef ti_sysbios_interfaces_ITimer_RunMode ti_sysbios_hal_Timer_RunMode;

/* Status */
typedef ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_Status;

/* PeriodType */
typedef ti_sysbios_interfaces_ITimer_PeriodType ti_sysbios_hal_Timer_PeriodType;

/* StartMode_AUTO */

/* StartMode_USER */

/* RunMode_CONTINUOUS */

/* RunMode_ONESHOT */

/* RunMode_DYNAMIC */

/* Status_INUSE */

/* Status_FREE */

/* PeriodType_MICROSECS */

/* PeriodType_COUNTS */


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_hal_Timer_Args__create {
    xdc_Int id;
    ti_sysbios_hal_Timer_FuncPtr tickFxn;
} ti_sysbios_hal_Timer_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_hal_Timer_Module__diagsEnabled;
extern far const CT__ti_sysbios_hal_Timer_Module__diagsEnabled ti_sysbios_hal_Timer_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_hal_Timer_Module__diagsIncluded;
extern far const CT__ti_sysbios_hal_Timer_Module__diagsIncluded ti_sysbios_hal_Timer_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_hal_Timer_Module__diagsMask;
extern far const CT__ti_sysbios_hal_Timer_Module__diagsMask ti_sysbios_hal_Timer_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_Module__gateObj;
extern far const CT__ti_sysbios_hal_Timer_Module__gateObj ti_sysbios_hal_Timer_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_Module__gatePrms;
extern far const CT__ti_sysbios_hal_Timer_Module__gatePrms ti_sysbios_hal_Timer_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_hal_Timer_Module__id;
extern far const CT__ti_sysbios_hal_Timer_Module__id ti_sysbios_hal_Timer_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_hal_Timer_Module__loggerDefined;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerDefined ti_sysbios_hal_Timer_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_Module__loggerObj;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerObj ti_sysbios_hal_Timer_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_hal_Timer_Module__loggerFxn0;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerFxn0 ti_sysbios_hal_Timer_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_hal_Timer_Module__loggerFxn1;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerFxn1 ti_sysbios_hal_Timer_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_hal_Timer_Module__loggerFxn2;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerFxn2 ti_sysbios_hal_Timer_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_hal_Timer_Module__loggerFxn4;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerFxn4 ti_sysbios_hal_Timer_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_hal_Timer_Module__loggerFxn8;
extern far const CT__ti_sysbios_hal_Timer_Module__loggerFxn8 ti_sysbios_hal_Timer_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_hal_Timer_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_hal_Timer_Module__startupDoneFxn ti_sysbios_hal_Timer_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_hal_Timer_Object__count;
extern far const CT__ti_sysbios_hal_Timer_Object__count ti_sysbios_hal_Timer_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_hal_Timer_Object__heap;
extern far const CT__ti_sysbios_hal_Timer_Object__heap ti_sysbios_hal_Timer_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_hal_Timer_Object__sizeof;
extern far const CT__ti_sysbios_hal_Timer_Object__sizeof ti_sysbios_hal_Timer_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_hal_Timer_Object__table;
extern far const CT__ti_sysbios_hal_Timer_Object__table ti_sysbios_hal_Timer_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_hal_Timer_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_interfaces_ITimer_RunMode runMode;
    ti_sysbios_interfaces_ITimer_StartMode startMode;
    xdc_UArg arg;
    xdc_UInt32 period;
    ti_sysbios_interfaces_ITimer_PeriodType periodType;
    xdc_runtime_Types_FreqHz extFreq;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_hal_Timer_Struct {
    const ti_sysbios_hal_Timer_Fxns__* __fxns;
    ti_sysbios_hal_Timer_TimerProxy_Handle __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_hal_Timer_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_UInt (*getNumTimers)(void);
    ti_sysbios_interfaces_ITimer_Status (*getStatus)(xdc_UInt);
    void (*startup)(void);
    xdc_UInt32 (*getMaxTicks)(ti_sysbios_hal_Timer_Handle, xdc_UInt32);
    void (*setNextTick)(ti_sysbios_hal_Timer_Handle, xdc_UInt32, xdc_UInt32);
    void (*start)(ti_sysbios_hal_Timer_Handle);
    void (*stop)(ti_sysbios_hal_Timer_Handle);
    void (*setPeriod)(ti_sysbios_hal_Timer_Handle, xdc_UInt32);
    xdc_Bool (*setPeriodMicroSecs)(ti_sysbios_hal_Timer_Handle, xdc_UInt32);
    xdc_UInt32 (*getPeriod)(ti_sysbios_hal_Timer_Handle);
    xdc_UInt32 (*getCount)(ti_sysbios_hal_Timer_Handle);
    void (*getFreq)(ti_sysbios_hal_Timer_Handle, xdc_runtime_Types_FreqHz*);
    ti_sysbios_interfaces_ITimer_FuncPtr (*getFunc)(ti_sysbios_hal_Timer_Handle, xdc_UArg*);
    void (*setFunc)(ti_sysbios_hal_Timer_Handle, ti_sysbios_interfaces_ITimer_FuncPtr, xdc_UArg);
    void (*trigger)(ti_sysbios_hal_Timer_Handle, xdc_UInt32);
    xdc_UInt32 (*getExpiredCounts)(ti_sysbios_hal_Timer_Handle);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const ti_sysbios_hal_Timer_Fxns__ ti_sysbios_hal_Timer_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int ti_sysbios_hal_Timer_Module_startup__E( xdc_Int state );

extern xdc_Int ti_sysbios_hal_Timer_Module_startup__F( xdc_Int state );

extern xdc_Int ti_sysbios_hal_Timer_Module_startup__R( xdc_Int state );

/* Instance_init__F */

extern int ti_sysbios_hal_Timer_Instance_init__F( ti_sysbios_hal_Timer_Object*, xdc_Int id, ti_sysbios_hal_Timer_FuncPtr tickFxn, const ti_sysbios_hal_Timer_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */

extern void ti_sysbios_hal_Timer_Instance_finalize__F( ti_sysbios_hal_Timer_Object* , int );

/* Instance_init__R */

extern int ti_sysbios_hal_Timer_Instance_init__R( ti_sysbios_hal_Timer_Object*, xdc_Int id, ti_sysbios_hal_Timer_FuncPtr tickFxn, const ti_sysbios_hal_Timer_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */

extern void ti_sysbios_hal_Timer_Instance_finalize__R( ti_sysbios_hal_Timer_Object* , int );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_hal_Timer_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_hal_Timer_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_hal_Timer_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_hal_Timer_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_hal_Timer_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_hal_Timer_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_hal_Timer_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_hal_Timer_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_hal_Timer_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* getNumTimers__E */

extern xdc_UInt ti_sysbios_hal_Timer_getNumTimers__E( void );

extern xdc_UInt ti_sysbios_hal_Timer_getNumTimers__F( void );
extern xdc_UInt ti_sysbios_hal_Timer_getNumTimers__R( void );

/* getStatus__E */

extern ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_getStatus__E( xdc_UInt id );

extern ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_getStatus__F( xdc_UInt id );
extern ti_sysbios_interfaces_ITimer_Status ti_sysbios_hal_Timer_getStatus__R( xdc_UInt id );

/* startup__E */

extern void ti_sysbios_hal_Timer_startup__E( void );

extern void ti_sysbios_hal_Timer_startup__F( void );
extern void ti_sysbios_hal_Timer_startup__R( void );

/* getMaxTicks__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_getMaxTicks__E( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 periodCounts );

extern xdc_UInt32 ti_sysbios_hal_Timer_getMaxTicks__F( ti_sysbios_hal_Timer_Object* __inst, xdc_UInt32 periodCounts );
extern xdc_UInt32 ti_sysbios_hal_Timer_getMaxTicks__R( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 periodCounts );

/* setNextTick__E */

extern void ti_sysbios_hal_Timer_setNextTick__E( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 newPeriod, xdc_UInt32 countsPerTick );

extern void ti_sysbios_hal_Timer_setNextTick__F( ti_sysbios_hal_Timer_Object* __inst, xdc_UInt32 newPeriod, xdc_UInt32 countsPerTick );
extern void ti_sysbios_hal_Timer_setNextTick__R( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 newPeriod, xdc_UInt32 countsPerTick );

/* start__E */

extern void ti_sysbios_hal_Timer_start__E( ti_sysbios_hal_Timer_Handle __inst );

extern void ti_sysbios_hal_Timer_start__F( ti_sysbios_hal_Timer_Object* __inst );
extern void ti_sysbios_hal_Timer_start__R( ti_sysbios_hal_Timer_Handle __inst );

/* stop__E */

extern void ti_sysbios_hal_Timer_stop__E( ti_sysbios_hal_Timer_Handle __inst );

extern void ti_sysbios_hal_Timer_stop__F( ti_sysbios_hal_Timer_Object* __inst );
extern void ti_sysbios_hal_Timer_stop__R( ti_sysbios_hal_Timer_Handle __inst );

/* setPeriod__E */

extern void ti_sysbios_hal_Timer_setPeriod__E( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 period );

extern void ti_sysbios_hal_Timer_setPeriod__F( ti_sysbios_hal_Timer_Object* __inst, xdc_UInt32 period );
extern void ti_sysbios_hal_Timer_setPeriod__R( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 period );

/* setPeriodMicroSecs__E */

extern xdc_Bool ti_sysbios_hal_Timer_setPeriodMicroSecs__E( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 microsecs );

extern xdc_Bool ti_sysbios_hal_Timer_setPeriodMicroSecs__F( ti_sysbios_hal_Timer_Object* __inst, xdc_UInt32 microsecs );
extern xdc_Bool ti_sysbios_hal_Timer_setPeriodMicroSecs__R( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 microsecs );

/* getPeriod__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_getPeriod__E( ti_sysbios_hal_Timer_Handle __inst );

extern xdc_UInt32 ti_sysbios_hal_Timer_getPeriod__F( ti_sysbios_hal_Timer_Object* __inst );
extern xdc_UInt32 ti_sysbios_hal_Timer_getPeriod__R( ti_sysbios_hal_Timer_Handle __inst );

/* getCount__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_getCount__E( ti_sysbios_hal_Timer_Handle __inst );

extern xdc_UInt32 ti_sysbios_hal_Timer_getCount__F( ti_sysbios_hal_Timer_Object* __inst );
extern xdc_UInt32 ti_sysbios_hal_Timer_getCount__R( ti_sysbios_hal_Timer_Handle __inst );

/* getFreq__E */

extern void ti_sysbios_hal_Timer_getFreq__E( ti_sysbios_hal_Timer_Handle __inst, xdc_runtime_Types_FreqHz* freq );

extern void ti_sysbios_hal_Timer_getFreq__F( ti_sysbios_hal_Timer_Object* __inst, xdc_runtime_Types_FreqHz* freq );
extern void ti_sysbios_hal_Timer_getFreq__R( ti_sysbios_hal_Timer_Handle __inst, xdc_runtime_Types_FreqHz* freq );

/* getFunc__E */

extern ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_getFunc__E( ti_sysbios_hal_Timer_Handle __inst, xdc_UArg* arg );

extern ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_getFunc__F( ti_sysbios_hal_Timer_Object* __inst, xdc_UArg* arg );
extern ti_sysbios_interfaces_ITimer_FuncPtr ti_sysbios_hal_Timer_getFunc__R( ti_sysbios_hal_Timer_Handle __inst, xdc_UArg* arg );

/* setFunc__E */

extern void ti_sysbios_hal_Timer_setFunc__E( ti_sysbios_hal_Timer_Handle __inst, ti_sysbios_interfaces_ITimer_FuncPtr fxn, xdc_UArg arg );

extern void ti_sysbios_hal_Timer_setFunc__F( ti_sysbios_hal_Timer_Object* __inst, ti_sysbios_interfaces_ITimer_FuncPtr fxn, xdc_UArg arg );
extern void ti_sysbios_hal_Timer_setFunc__R( ti_sysbios_hal_Timer_Handle __inst, ti_sysbios_interfaces_ITimer_FuncPtr fxn, xdc_UArg arg );

/* trigger__E */

extern void ti_sysbios_hal_Timer_trigger__E( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 cycles );

extern void ti_sysbios_hal_Timer_trigger__F( ti_sysbios_hal_Timer_Object* __inst, xdc_UInt32 cycles );
extern void ti_sysbios_hal_Timer_trigger__R( ti_sysbios_hal_Timer_Handle __inst, xdc_UInt32 cycles );

/* getExpiredCounts__E */

extern xdc_UInt32 ti_sysbios_hal_Timer_getExpiredCounts__E( ti_sysbios_hal_Timer_Handle __inst );

extern xdc_UInt32 ti_sysbios_hal_Timer_getExpiredCounts__F( ti_sysbios_hal_Timer_Object* __inst );
extern xdc_UInt32 ti_sysbios_hal_Timer_getExpiredCounts__R( ti_sysbios_hal_Timer_Handle __inst );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getMaxTicks_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_getMaxTicks_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_getMaxTicks_FxnT ti_sysbios_hal_Timer_getMaxTicks_fxnP( void )
{
    return (ti_sysbios_hal_Timer_getMaxTicks_FxnT)ti_sysbios_hal_Timer_getMaxTicks__E; 
}

/* setNextTick_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_setNextTick_FxnT)(void*, xdc_UInt32, xdc_UInt32);
static inline ti_sysbios_hal_Timer_setNextTick_FxnT ti_sysbios_hal_Timer_setNextTick_fxnP( void )
{
    return (ti_sysbios_hal_Timer_setNextTick_FxnT)ti_sysbios_hal_Timer_setNextTick__E; 
}

/* start_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_start_FxnT)(void*);
static inline ti_sysbios_hal_Timer_start_FxnT ti_sysbios_hal_Timer_start_fxnP( void )
{
    return (ti_sysbios_hal_Timer_start_FxnT)ti_sysbios_hal_Timer_start__E; 
}

/* stop_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_stop_FxnT)(void*);
static inline ti_sysbios_hal_Timer_stop_FxnT ti_sysbios_hal_Timer_stop_fxnP( void )
{
    return (ti_sysbios_hal_Timer_stop_FxnT)ti_sysbios_hal_Timer_stop__E; 
}

/* setPeriod_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_setPeriod_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_setPeriod_FxnT ti_sysbios_hal_Timer_setPeriod_fxnP( void )
{
    return (ti_sysbios_hal_Timer_setPeriod_FxnT)ti_sysbios_hal_Timer_setPeriod__E; 
}

/* setPeriodMicroSecs_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_hal_Timer_setPeriodMicroSecs_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_setPeriodMicroSecs_FxnT ti_sysbios_hal_Timer_setPeriodMicroSecs_fxnP( void )
{
    return (ti_sysbios_hal_Timer_setPeriodMicroSecs_FxnT)ti_sysbios_hal_Timer_setPeriodMicroSecs__E; 
}

/* getPeriod_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_getPeriod_FxnT)(void*);
static inline ti_sysbios_hal_Timer_getPeriod_FxnT ti_sysbios_hal_Timer_getPeriod_fxnP( void )
{
    return (ti_sysbios_hal_Timer_getPeriod_FxnT)ti_sysbios_hal_Timer_getPeriod__E; 
}

/* getCount_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_getCount_FxnT)(void*);
static inline ti_sysbios_hal_Timer_getCount_FxnT ti_sysbios_hal_Timer_getCount_fxnP( void )
{
    return (ti_sysbios_hal_Timer_getCount_FxnT)ti_sysbios_hal_Timer_getCount__E; 
}

/* getFreq_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_getFreq_FxnT)(void*, xdc_runtime_Types_FreqHz*);
static inline ti_sysbios_hal_Timer_getFreq_FxnT ti_sysbios_hal_Timer_getFreq_fxnP( void )
{
    return (ti_sysbios_hal_Timer_getFreq_FxnT)ti_sysbios_hal_Timer_getFreq__E; 
}

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_ITimer_FuncPtr (*ti_sysbios_hal_Timer_getFunc_FxnT)(void*, xdc_UArg*);
static inline ti_sysbios_hal_Timer_getFunc_FxnT ti_sysbios_hal_Timer_getFunc_fxnP( void )
{
    return (ti_sysbios_hal_Timer_getFunc_FxnT)ti_sysbios_hal_Timer_getFunc__E; 
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_setFunc_FxnT)(void*, ti_sysbios_interfaces_ITimer_FuncPtr, xdc_UArg);
static inline ti_sysbios_hal_Timer_setFunc_FxnT ti_sysbios_hal_Timer_setFunc_fxnP( void )
{
    return (ti_sysbios_hal_Timer_setFunc_FxnT)ti_sysbios_hal_Timer_setFunc__E; 
}

/* trigger_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Timer_trigger_FxnT)(void*, xdc_UInt32);
static inline ti_sysbios_hal_Timer_trigger_FxnT ti_sysbios_hal_Timer_trigger_fxnP( void )
{
    return (ti_sysbios_hal_Timer_trigger_FxnT)ti_sysbios_hal_Timer_trigger__E; 
}

/* getExpiredCounts_{FxnT,fxnP} */
typedef xdc_UInt32 (*ti_sysbios_hal_Timer_getExpiredCounts_FxnT)(void*);
static inline ti_sysbios_hal_Timer_getExpiredCounts_FxnT ti_sysbios_hal_Timer_getExpiredCounts_fxnP( void )
{
    return (ti_sysbios_hal_Timer_getExpiredCounts_FxnT)ti_sysbios_hal_Timer_getExpiredCounts__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sysbios_interfaces_ITimer_Module ti_sysbios_hal_Timer_Module_upCast( void )
{
    return (ti_sysbios_interfaces_ITimer_Module)&ti_sysbios_hal_Timer_Module__FXNS__C;
}

/* Module_to_ti_sysbios_interfaces_ITimer */

/* Handle_upCast */
static inline ti_sysbios_interfaces_ITimer_Handle ti_sysbios_hal_Timer_Handle_upCast( ti_sysbios_hal_Timer_Handle i )
{
    return (ti_sysbios_interfaces_ITimer_Handle)i;
}

/* Handle_to_ti_sysbios_interfaces_ITimer */

/* Handle_downCast */
static inline ti_sysbios_hal_Timer_Handle ti_sysbios_hal_Timer_Handle_downCast( ti_sysbios_interfaces_ITimer_Handle i )
{
    ti_sysbios_interfaces_ITimer_Handle i2 = (ti_sysbios_interfaces_ITimer_Handle)i;
    return (void*)i2->__fxns == (void*)&ti_sysbios_hal_Timer_Module__FXNS__C ? (ti_sysbios_hal_Timer_Handle)i : 0;
}

/* Handle_from_ti_sysbios_interfaces_ITimer */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_hal_Timer_Module__id ti_sysbios_hal_Timer_Module_id( void ) 
{
    return ti_sysbios_hal_Timer_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_hal_Timer_Module_hasMask( void ) 
{
    return ti_sysbios_hal_Timer_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_hal_Timer_Module_getMask( void ) 
{
    return ti_sysbios_hal_Timer_Module__diagsMask__C != 0 ? *ti_sysbios_hal_Timer_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_hal_Timer_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_hal_Timer_Module__diagsMask__C != 0) *ti_sysbios_hal_Timer_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_hal_Timer_Params_init( ti_sysbios_hal_Timer_Params* prms ) 
{
    if (prms) {
        ti_sysbios_hal_Timer_Params__init__S(prms, 0, sizeof(ti_sysbios_hal_Timer_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_hal_Timer_Params_copy( ti_sysbios_hal_Timer_Params* dst, const ti_sysbios_hal_Timer_Params* src ) 
{
    if (dst) {
        ti_sysbios_hal_Timer_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_hal_Timer_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_hal_Timer_Handle ti_sysbios_hal_Timer_Object_get( ti_sysbios_hal_Timer_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_hal_Timer_Handle)ti_sysbios_hal_Timer_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_hal_Timer_Handle ti_sysbios_hal_Timer_Object_first( void )
{
    return (ti_sysbios_hal_Timer_Handle)ti_sysbios_hal_Timer_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_hal_Timer_Handle ti_sysbios_hal_Timer_Object_next( ti_sysbios_hal_Timer_Object* obj )
{
    return (ti_sysbios_hal_Timer_Handle)ti_sysbios_hal_Timer_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_hal_Timer_Handle_label( ti_sysbios_hal_Timer_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_hal_Timer_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_hal_Timer_Handle_name( ti_sysbios_hal_Timer_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_hal_Timer_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_hal_Timer_Handle ti_sysbios_hal_Timer_create( xdc_Int id, ti_sysbios_hal_Timer_FuncPtr tickFxn, const ti_sysbios_hal_Timer_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_hal_Timer_Args__create __args;
    __args.id = id;
    __args.tickFxn = tickFxn;
    return (ti_sysbios_hal_Timer_Handle)ti_sysbios_hal_Timer_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_hal_Timer_Params), __eb);
}

/* construct */
static inline void ti_sysbios_hal_Timer_construct( ti_sysbios_hal_Timer_Struct* __obj, xdc_Int id, ti_sysbios_hal_Timer_FuncPtr tickFxn, const ti_sysbios_hal_Timer_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_hal_Timer_Args__create __args;
    __args.id = id;
    __args.tickFxn = tickFxn;
    ti_sysbios_hal_Timer_Object__create__S(__obj, sizeof (ti_sysbios_hal_Timer_Struct), &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_hal_Timer_Params), __eb);
}

/* delete */
static inline void ti_sysbios_hal_Timer_delete( ti_sysbios_hal_Timer_Handle* instp )
{
    ti_sysbios_hal_Timer_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_hal_Timer_destruct( ti_sysbios_hal_Timer_Struct* obj )
{
    ti_sysbios_hal_Timer_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_hal_Timer_Handle ti_sysbios_hal_Timer_handle( ti_sysbios_hal_Timer_Struct* str )
{
    return (ti_sysbios_hal_Timer_Handle)str;
}

/* struct */
static inline ti_sysbios_hal_Timer_Struct* ti_sysbios_hal_Timer_struct( ti_sysbios_hal_Timer_Handle inst )
{
    return (ti_sysbios_hal_Timer_Struct*)inst;
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
 *  @(#) ti.sysbios.hal; 2, 0, 0, 0,547; 3-20-2012 14:03:16; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:32; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:32; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Elem */
struct ti_sysbios_knl_Queue_Elem {
    ti_sysbios_knl_Queue_Elem*volatile  next;
    ti_sysbios_knl_Queue_Elem*volatile  prev;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Queue_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Queue_Module__diagsEnabled ti_sysbios_knl_Queue_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Queue_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Queue_Module__diagsIncluded ti_sysbios_knl_Queue_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Queue_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Queue_Module__diagsMask ti_sysbios_knl_Queue_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Queue_Module__gateObj;
extern far const CT__ti_sysbios_knl_Queue_Module__gateObj ti_sysbios_knl_Queue_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Queue_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Queue_Module__gatePrms ti_sysbios_knl_Queue_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Queue_Module__id;
extern far const CT__ti_sysbios_knl_Queue_Module__id ti_sysbios_knl_Queue_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Queue_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerDefined ti_sysbios_knl_Queue_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Queue_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerObj ti_sysbios_knl_Queue_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Queue_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerFxn0 ti_sysbios_knl_Queue_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Queue_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerFxn1 ti_sysbios_knl_Queue_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Queue_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerFxn2 ti_sysbios_knl_Queue_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Queue_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerFxn4 ti_sysbios_knl_Queue_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Queue_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Queue_Module__loggerFxn8 ti_sysbios_knl_Queue_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Queue_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Queue_Module__startupDoneFxn ti_sysbios_knl_Queue_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Queue_Object__count;
extern far const CT__ti_sysbios_knl_Queue_Object__count ti_sysbios_knl_Queue_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Queue_Object__heap;
extern far const CT__ti_sysbios_knl_Queue_Object__heap ti_sysbios_knl_Queue_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Queue_Object__sizeof;
extern far const CT__ti_sysbios_knl_Queue_Object__sizeof ti_sysbios_knl_Queue_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Queue_Object__table;
extern far const CT__ti_sysbios_knl_Queue_Object__table ti_sysbios_knl_Queue_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_knl_Queue_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_knl_Queue_Struct {
    ti_sysbios_knl_Queue_Elem __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Instance_init__F */

extern void ti_sysbios_knl_Queue_Instance_init__F( ti_sysbios_knl_Queue_Object*, const ti_sysbios_knl_Queue_Params* );

/* Instance_init__R */

extern void ti_sysbios_knl_Queue_Instance_init__R( ti_sysbios_knl_Queue_Object*, const ti_sysbios_knl_Queue_Params* );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Queue_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Queue_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Queue_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Queue_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Queue_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Queue_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Queue_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Queue_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Queue_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* elemClear__E */

extern void ti_sysbios_knl_Queue_elemClear__E( ti_sysbios_knl_Queue_Elem* qelem );

extern void ti_sysbios_knl_Queue_elemClear__F( ti_sysbios_knl_Queue_Elem* qelem );
extern void ti_sysbios_knl_Queue_elemClear__R( ti_sysbios_knl_Queue_Elem* qelem );

/* insert__E */

extern void ti_sysbios_knl_Queue_insert__E( ti_sysbios_knl_Queue_Elem* qelem, ti_sysbios_knl_Queue_Elem* elem );

extern void ti_sysbios_knl_Queue_insert__F( ti_sysbios_knl_Queue_Elem* qelem, ti_sysbios_knl_Queue_Elem* elem );
extern void ti_sysbios_knl_Queue_insert__R( ti_sysbios_knl_Queue_Elem* qelem, ti_sysbios_knl_Queue_Elem* elem );

/* next__E */

extern xdc_Ptr ti_sysbios_knl_Queue_next__E( ti_sysbios_knl_Queue_Elem* qelem );

extern xdc_Ptr ti_sysbios_knl_Queue_next__F( ti_sysbios_knl_Queue_Elem* qelem );
extern xdc_Ptr ti_sysbios_knl_Queue_next__R( ti_sysbios_knl_Queue_Elem* qelem );

/* prev__E */

extern xdc_Ptr ti_sysbios_knl_Queue_prev__E( ti_sysbios_knl_Queue_Elem* qelem );

extern xdc_Ptr ti_sysbios_knl_Queue_prev__F( ti_sysbios_knl_Queue_Elem* qelem );
extern xdc_Ptr ti_sysbios_knl_Queue_prev__R( ti_sysbios_knl_Queue_Elem* qelem );

/* remove__E */

extern void ti_sysbios_knl_Queue_remove__E( ti_sysbios_knl_Queue_Elem* qelem );

extern void ti_sysbios_knl_Queue_remove__F( ti_sysbios_knl_Queue_Elem* qelem );
extern void ti_sysbios_knl_Queue_remove__R( ti_sysbios_knl_Queue_Elem* qelem );

/* isQueued__E */

extern xdc_Bool ti_sysbios_knl_Queue_isQueued__E( ti_sysbios_knl_Queue_Elem* qelem );

extern xdc_Bool ti_sysbios_knl_Queue_isQueued__F( ti_sysbios_knl_Queue_Elem* qelem );
extern xdc_Bool ti_sysbios_knl_Queue_isQueued__R( ti_sysbios_knl_Queue_Elem* qelem );

/* dequeue__E */

extern xdc_Ptr ti_sysbios_knl_Queue_dequeue__E( ti_sysbios_knl_Queue_Handle __inst );

extern xdc_Ptr ti_sysbios_knl_Queue_dequeue__F( ti_sysbios_knl_Queue_Object* __inst );
extern xdc_Ptr ti_sysbios_knl_Queue_dequeue__R( ti_sysbios_knl_Queue_Handle __inst );

/* empty__E */

extern xdc_Bool ti_sysbios_knl_Queue_empty__E( ti_sysbios_knl_Queue_Handle __inst );

extern xdc_Bool ti_sysbios_knl_Queue_empty__F( ti_sysbios_knl_Queue_Object* __inst );
extern xdc_Bool ti_sysbios_knl_Queue_empty__R( ti_sysbios_knl_Queue_Handle __inst );

/* enqueue__E */

extern void ti_sysbios_knl_Queue_enqueue__E( ti_sysbios_knl_Queue_Handle __inst, ti_sysbios_knl_Queue_Elem* elem );

extern void ti_sysbios_knl_Queue_enqueue__F( ti_sysbios_knl_Queue_Object* __inst, ti_sysbios_knl_Queue_Elem* elem );
extern void ti_sysbios_knl_Queue_enqueue__R( ti_sysbios_knl_Queue_Handle __inst, ti_sysbios_knl_Queue_Elem* elem );

/* get__E */

extern xdc_Ptr ti_sysbios_knl_Queue_get__E( ti_sysbios_knl_Queue_Handle __inst );

extern xdc_Ptr ti_sysbios_knl_Queue_get__F( ti_sysbios_knl_Queue_Object* __inst );
extern xdc_Ptr ti_sysbios_knl_Queue_get__R( ti_sysbios_knl_Queue_Handle __inst );

/* head__E */

extern xdc_Ptr ti_sysbios_knl_Queue_head__E( ti_sysbios_knl_Queue_Handle __inst );

extern xdc_Ptr ti_sysbios_knl_Queue_head__F( ti_sysbios_knl_Queue_Object* __inst );
extern xdc_Ptr ti_sysbios_knl_Queue_head__R( ti_sysbios_knl_Queue_Handle __inst );

/* put__E */

extern void ti_sysbios_knl_Queue_put__E( ti_sysbios_knl_Queue_Handle __inst, ti_sysbios_knl_Queue_Elem* elem );

extern void ti_sysbios_knl_Queue_put__F( ti_sysbios_knl_Queue_Object* __inst, ti_sysbios_knl_Queue_Elem* elem );
extern void ti_sysbios_knl_Queue_put__R( ti_sysbios_knl_Queue_Handle __inst, ti_sysbios_knl_Queue_Elem* elem );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* dequeue_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_knl_Queue_dequeue_FxnT)(void*);
static inline ti_sysbios_knl_Queue_dequeue_FxnT ti_sysbios_knl_Queue_dequeue_fxnP( void )
{
    return (ti_sysbios_knl_Queue_dequeue_FxnT)ti_sysbios_knl_Queue_dequeue__E; 
}

/* empty_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_knl_Queue_empty_FxnT)(void*);
static inline ti_sysbios_knl_Queue_empty_FxnT ti_sysbios_knl_Queue_empty_fxnP( void )
{
    return (ti_sysbios_knl_Queue_empty_FxnT)ti_sysbios_knl_Queue_empty__E; 
}

/* enqueue_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Queue_enqueue_FxnT)(void*, ti_sysbios_knl_Queue_Elem*);
static inline ti_sysbios_knl_Queue_enqueue_FxnT ti_sysbios_knl_Queue_enqueue_fxnP( void )
{
    return (ti_sysbios_knl_Queue_enqueue_FxnT)ti_sysbios_knl_Queue_enqueue__E; 
}

/* get_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_knl_Queue_get_FxnT)(void*);
static inline ti_sysbios_knl_Queue_get_FxnT ti_sysbios_knl_Queue_get_fxnP( void )
{
    return (ti_sysbios_knl_Queue_get_FxnT)ti_sysbios_knl_Queue_get__E; 
}

/* head_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_knl_Queue_head_FxnT)(void*);
static inline ti_sysbios_knl_Queue_head_FxnT ti_sysbios_knl_Queue_head_fxnP( void )
{
    return (ti_sysbios_knl_Queue_head_FxnT)ti_sysbios_knl_Queue_head__E; 
}

/* put_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Queue_put_FxnT)(void*, ti_sysbios_knl_Queue_Elem*);
static inline ti_sysbios_knl_Queue_put_FxnT ti_sysbios_knl_Queue_put_fxnP( void )
{
    return (ti_sysbios_knl_Queue_put_FxnT)ti_sysbios_knl_Queue_put__E; 
}


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Queue_Module__id ti_sysbios_knl_Queue_Module_id( void ) 
{
    return ti_sysbios_knl_Queue_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_knl_Queue_Module_hasMask( void ) 
{
    return ti_sysbios_knl_Queue_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_knl_Queue_Module_getMask( void ) 
{
    return ti_sysbios_knl_Queue_Module__diagsMask__C != 0 ? *ti_sysbios_knl_Queue_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_knl_Queue_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_knl_Queue_Module__diagsMask__C != 0) *ti_sysbios_knl_Queue_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_knl_Queue_Params_init( ti_sysbios_knl_Queue_Params* prms ) 
{
    if (prms) {
        ti_sysbios_knl_Queue_Params__init__S(prms, 0, sizeof(ti_sysbios_knl_Queue_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_knl_Queue_Params_copy( ti_sysbios_knl_Queue_Params* dst, const ti_sysbios_knl_Queue_Params* src ) 
{
    if (dst) {
        ti_sysbios_knl_Queue_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_knl_Queue_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Queue_Object_get( ti_sysbios_knl_Queue_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_knl_Queue_Handle)ti_sysbios_knl_Queue_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Queue_Object_first( void )
{
    return (ti_sysbios_knl_Queue_Handle)ti_sysbios_knl_Queue_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Queue_Object_next( ti_sysbios_knl_Queue_Object* obj )
{
    return (ti_sysbios_knl_Queue_Handle)ti_sysbios_knl_Queue_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_knl_Queue_Handle_label( ti_sysbios_knl_Queue_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_knl_Queue_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_knl_Queue_Handle_name( ti_sysbios_knl_Queue_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_knl_Queue_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Queue_create( const ti_sysbios_knl_Queue_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (ti_sysbios_knl_Queue_Handle)ti_sysbios_knl_Queue_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Queue_Params), __eb);
}

/* construct */
static inline void ti_sysbios_knl_Queue_construct( ti_sysbios_knl_Queue_Struct* __obj, const ti_sysbios_knl_Queue_Params* __prms )
{
    ti_sysbios_knl_Queue_Object__create__S(__obj, sizeof (ti_sysbios_knl_Queue_Struct), 0, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Queue_Params), 0);
}

/* delete */
static inline void ti_sysbios_knl_Queue_delete( ti_sysbios_knl_Queue_Handle* instp )
{
    ti_sysbios_knl_Queue_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_knl_Queue_destruct( ti_sysbios_knl_Queue_Struct* obj )
{
    ti_sysbios_knl_Queue_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Queue_handle( ti_sysbios_knl_Queue_Struct* str )
{
    return (ti_sysbios_knl_Queue_Handle)str;
}

/* struct */
static inline ti_sysbios_knl_Queue_Struct* ti_sysbios_knl_Queue_struct( ti_sysbios_knl_Queue_Handle inst )
{
    return (ti_sysbios_knl_Queue_Struct*)inst;
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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

/* FuncPtr */
typedef void (*ti_sysbios_knl_Swi_FuncPtr)(xdc_UArg, xdc_UArg);

/* HookSet */
struct ti_sysbios_knl_Swi_HookSet {
    void (*registerFxn)(xdc_Int);
    void (*createFxn)(ti_sysbios_knl_Swi_Handle, xdc_runtime_Error_Block*);
    void (*readyFxn)(ti_sysbios_knl_Swi_Handle);
    void (*beginFxn)(ti_sysbios_knl_Swi_Handle);
    void (*endFxn)(ti_sysbios_knl_Swi_Handle);
    void (*deleteFxn)(ti_sysbios_knl_Swi_Handle);
};


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_knl_Swi_Args__create {
    ti_sysbios_knl_Swi_FuncPtr fxn;
} ti_sysbios_knl_Swi_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Instance_State */
typedef xdc_Ptr __T1_ti_sysbios_knl_Swi_Instance_State__hookEnv;
typedef xdc_Ptr *__ARRAY1_ti_sysbios_knl_Swi_Instance_State__hookEnv;
typedef __ARRAY1_ti_sysbios_knl_Swi_Instance_State__hookEnv __TA_ti_sysbios_knl_Swi_Instance_State__hookEnv;

/* Module_State */
typedef ti_sysbios_knl_Queue_Instance_State __T1_ti_sysbios_knl_Swi_Module_State__readyQ;
typedef ti_sysbios_knl_Queue_Instance_State *__ARRAY1_ti_sysbios_knl_Swi_Module_State__readyQ;
typedef __ARRAY1_ti_sysbios_knl_Swi_Module_State__readyQ __TA_ti_sysbios_knl_Swi_Module_State__readyQ;
typedef ti_sysbios_knl_Swi_Handle __T1_ti_sysbios_knl_Swi_Module_State__constructedSwis;
typedef ti_sysbios_knl_Swi_Handle *__ARRAY1_ti_sysbios_knl_Swi_Module_State__constructedSwis;
typedef __ARRAY1_ti_sysbios_knl_Swi_Module_State__constructedSwis __TA_ti_sysbios_knl_Swi_Module_State__constructedSwis;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Swi_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Swi_Module__diagsEnabled ti_sysbios_knl_Swi_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Swi_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Swi_Module__diagsIncluded ti_sysbios_knl_Swi_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Swi_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Swi_Module__diagsMask ti_sysbios_knl_Swi_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Swi_Module__gateObj;
extern far const CT__ti_sysbios_knl_Swi_Module__gateObj ti_sysbios_knl_Swi_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Swi_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Swi_Module__gatePrms ti_sysbios_knl_Swi_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Swi_Module__id;
extern far const CT__ti_sysbios_knl_Swi_Module__id ti_sysbios_knl_Swi_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Swi_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerDefined ti_sysbios_knl_Swi_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Swi_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerObj ti_sysbios_knl_Swi_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Swi_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerFxn0 ti_sysbios_knl_Swi_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Swi_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerFxn1 ti_sysbios_knl_Swi_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Swi_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerFxn2 ti_sysbios_knl_Swi_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Swi_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerFxn4 ti_sysbios_knl_Swi_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Swi_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Swi_Module__loggerFxn8 ti_sysbios_knl_Swi_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Swi_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Swi_Module__startupDoneFxn ti_sysbios_knl_Swi_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Swi_Object__count;
extern far const CT__ti_sysbios_knl_Swi_Object__count ti_sysbios_knl_Swi_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Swi_Object__heap;
extern far const CT__ti_sysbios_knl_Swi_Object__heap ti_sysbios_knl_Swi_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Swi_Object__sizeof;
extern far const CT__ti_sysbios_knl_Swi_Object__sizeof ti_sysbios_knl_Swi_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Swi_Object__table;
extern far const CT__ti_sysbios_knl_Swi_Object__table ti_sysbios_knl_Swi_Object__table__C;

/* LM_begin */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Swi_LM_begin;
extern far const CT__ti_sysbios_knl_Swi_LM_begin ti_sysbios_knl_Swi_LM_begin__C;

/* LD_end */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Swi_LD_end;
extern far const CT__ti_sysbios_knl_Swi_LD_end ti_sysbios_knl_Swi_LD_end__C;

/* LM_post */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Swi_LM_post;
extern far const CT__ti_sysbios_knl_Swi_LM_post ti_sysbios_knl_Swi_LM_post__C;

/* A_swiDisabled */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Swi_A_swiDisabled;
extern far const CT__ti_sysbios_knl_Swi_A_swiDisabled ti_sysbios_knl_Swi_A_swiDisabled__C;

/* A_badPriority */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Swi_A_badPriority;
extern far const CT__ti_sysbios_knl_Swi_A_badPriority ti_sysbios_knl_Swi_A_badPriority__C;

/* numPriorities */
typedef xdc_UInt CT__ti_sysbios_knl_Swi_numPriorities;
extern far const CT__ti_sysbios_knl_Swi_numPriorities ti_sysbios_knl_Swi_numPriorities__C;

/* hooks */
typedef ti_sysbios_knl_Swi_HookSet __T1_ti_sysbios_knl_Swi_hooks;
typedef struct { int length; ti_sysbios_knl_Swi_HookSet *elem; } __ARRAY1_ti_sysbios_knl_Swi_hooks;
typedef __ARRAY1_ti_sysbios_knl_Swi_hooks __TA_ti_sysbios_knl_Swi_hooks;
typedef __TA_ti_sysbios_knl_Swi_hooks CT__ti_sysbios_knl_Swi_hooks;
extern far const CT__ti_sysbios_knl_Swi_hooks ti_sysbios_knl_Swi_hooks__C;

/* taskDisable */
typedef xdc_UInt (*CT__ti_sysbios_knl_Swi_taskDisable)(void);
extern far const CT__ti_sysbios_knl_Swi_taskDisable ti_sysbios_knl_Swi_taskDisable__C;

/* taskRestore */
typedef void (*CT__ti_sysbios_knl_Swi_taskRestore)(xdc_UInt);
extern far const CT__ti_sysbios_knl_Swi_taskRestore ti_sysbios_knl_Swi_taskRestore__C;

/* numConstructedSwis */
typedef xdc_UInt CT__ti_sysbios_knl_Swi_numConstructedSwis;
extern far const CT__ti_sysbios_knl_Swi_numConstructedSwis ti_sysbios_knl_Swi_numConstructedSwis__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_knl_Swi_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_UArg arg0;
    xdc_UArg arg1;
    xdc_UInt priority;
    xdc_UInt trigger;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_knl_Swi_Struct {
    ti_sysbios_knl_Queue_Elem __f0;
    ti_sysbios_knl_Swi_FuncPtr __f1;
    xdc_UArg __f2;
    xdc_UArg __f3;
    xdc_UInt __f4;
    xdc_UInt __f5;
    xdc_Bool __f6;
    xdc_UInt __f7;
    xdc_UInt __f8;
    ti_sysbios_knl_Queue_Handle __f9;
    __TA_ti_sysbios_knl_Swi_Instance_State__hookEnv __f10;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int ti_sysbios_knl_Swi_Module_startup__E( xdc_Int state );

extern xdc_Int ti_sysbios_knl_Swi_Module_startup__F( xdc_Int state );

extern xdc_Int ti_sysbios_knl_Swi_Module_startup__R( xdc_Int state );

/* Instance_init__F */

extern int ti_sysbios_knl_Swi_Instance_init__F( ti_sysbios_knl_Swi_Object*, ti_sysbios_knl_Swi_FuncPtr fxn, const ti_sysbios_knl_Swi_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */

extern void ti_sysbios_knl_Swi_Instance_finalize__F( ti_sysbios_knl_Swi_Object* , int );

/* Instance_init__R */

extern int ti_sysbios_knl_Swi_Instance_init__R( ti_sysbios_knl_Swi_Object*, ti_sysbios_knl_Swi_FuncPtr fxn, const ti_sysbios_knl_Swi_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */

extern void ti_sysbios_knl_Swi_Instance_finalize__R( ti_sysbios_knl_Swi_Object* , int );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Swi_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Swi_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Swi_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Swi_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Swi_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Swi_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Swi_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Swi_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Swi_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* startup__E */

extern void ti_sysbios_knl_Swi_startup__E( void );

extern void ti_sysbios_knl_Swi_startup__F( void );
extern void ti_sysbios_knl_Swi_startup__R( void );

/* enabled__E */

extern xdc_Bool ti_sysbios_knl_Swi_enabled__E( void );

extern xdc_Bool ti_sysbios_knl_Swi_enabled__F( void );
extern xdc_Bool ti_sysbios_knl_Swi_enabled__R( void );

/* disable__E */

extern xdc_UInt ti_sysbios_knl_Swi_disable__E( void );

extern xdc_UInt ti_sysbios_knl_Swi_disable__F( void );
extern xdc_UInt ti_sysbios_knl_Swi_disable__R( void );

/* enable__E */

extern void ti_sysbios_knl_Swi_enable__E( void );

extern void ti_sysbios_knl_Swi_enable__F( void );
extern void ti_sysbios_knl_Swi_enable__R( void );

/* restore__E */

extern void ti_sysbios_knl_Swi_restore__E( xdc_UInt key );

extern void ti_sysbios_knl_Swi_restore__F( xdc_UInt key );
extern void ti_sysbios_knl_Swi_restore__R( xdc_UInt key );

/* restoreHwi__E */

extern void ti_sysbios_knl_Swi_restoreHwi__E( xdc_UInt key );

extern void ti_sysbios_knl_Swi_restoreHwi__F( xdc_UInt key );
extern void ti_sysbios_knl_Swi_restoreHwi__R( xdc_UInt key );

/* self__E */

extern ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_self__E( void );

extern ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_self__F( void );
extern ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_self__R( void );

/* getTrigger__E */

extern xdc_UInt ti_sysbios_knl_Swi_getTrigger__E( void );

extern xdc_UInt ti_sysbios_knl_Swi_getTrigger__F( void );
extern xdc_UInt ti_sysbios_knl_Swi_getTrigger__R( void );

/* raisePri__E */

extern xdc_UInt ti_sysbios_knl_Swi_raisePri__E( xdc_UInt priority );

extern xdc_UInt ti_sysbios_knl_Swi_raisePri__F( xdc_UInt priority );
extern xdc_UInt ti_sysbios_knl_Swi_raisePri__R( xdc_UInt priority );

/* restorePri__E */

extern void ti_sysbios_knl_Swi_restorePri__E( xdc_UInt key );

extern void ti_sysbios_knl_Swi_restorePri__F( xdc_UInt key );
extern void ti_sysbios_knl_Swi_restorePri__R( xdc_UInt key );

/* andn__E */

extern void ti_sysbios_knl_Swi_andn__E( ti_sysbios_knl_Swi_Handle __inst, xdc_UInt mask );

extern void ti_sysbios_knl_Swi_andn__F( ti_sysbios_knl_Swi_Object* __inst, xdc_UInt mask );
extern void ti_sysbios_knl_Swi_andn__R( ti_sysbios_knl_Swi_Handle __inst, xdc_UInt mask );

/* dec__E */

extern void ti_sysbios_knl_Swi_dec__E( ti_sysbios_knl_Swi_Handle __inst );

extern void ti_sysbios_knl_Swi_dec__F( ti_sysbios_knl_Swi_Object* __inst );
extern void ti_sysbios_knl_Swi_dec__R( ti_sysbios_knl_Swi_Handle __inst );

/* getHookContext__E */

extern xdc_Ptr ti_sysbios_knl_Swi_getHookContext__E( ti_sysbios_knl_Swi_Handle __inst, xdc_Int id );

extern xdc_Ptr ti_sysbios_knl_Swi_getHookContext__F( ti_sysbios_knl_Swi_Object* __inst, xdc_Int id );
extern xdc_Ptr ti_sysbios_knl_Swi_getHookContext__R( ti_sysbios_knl_Swi_Handle __inst, xdc_Int id );

/* setHookContext__E */

extern void ti_sysbios_knl_Swi_setHookContext__E( ti_sysbios_knl_Swi_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

extern void ti_sysbios_knl_Swi_setHookContext__F( ti_sysbios_knl_Swi_Object* __inst, xdc_Int id, xdc_Ptr hookContext );
extern void ti_sysbios_knl_Swi_setHookContext__R( ti_sysbios_knl_Swi_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

/* getPri__E */

extern xdc_UInt ti_sysbios_knl_Swi_getPri__E( ti_sysbios_knl_Swi_Handle __inst );

extern xdc_UInt ti_sysbios_knl_Swi_getPri__F( ti_sysbios_knl_Swi_Object* __inst );
extern xdc_UInt ti_sysbios_knl_Swi_getPri__R( ti_sysbios_knl_Swi_Handle __inst );

/* getFunc__E */

extern ti_sysbios_knl_Swi_FuncPtr ti_sysbios_knl_Swi_getFunc__E( ti_sysbios_knl_Swi_Handle __inst, xdc_UArg* arg0, xdc_UArg* arg1 );

extern ti_sysbios_knl_Swi_FuncPtr ti_sysbios_knl_Swi_getFunc__F( ti_sysbios_knl_Swi_Object* __inst, xdc_UArg* arg0, xdc_UArg* arg1 );
extern ti_sysbios_knl_Swi_FuncPtr ti_sysbios_knl_Swi_getFunc__R( ti_sysbios_knl_Swi_Handle __inst, xdc_UArg* arg0, xdc_UArg* arg1 );

/* inc__E */

extern void ti_sysbios_knl_Swi_inc__E( ti_sysbios_knl_Swi_Handle __inst );

extern void ti_sysbios_knl_Swi_inc__F( ti_sysbios_knl_Swi_Object* __inst );
extern void ti_sysbios_knl_Swi_inc__R( ti_sysbios_knl_Swi_Handle __inst );

/* or__E */

extern void ti_sysbios_knl_Swi_or__E( ti_sysbios_knl_Swi_Handle __inst, xdc_UInt mask );

extern void ti_sysbios_knl_Swi_or__F( ti_sysbios_knl_Swi_Object* __inst, xdc_UInt mask );
extern void ti_sysbios_knl_Swi_or__R( ti_sysbios_knl_Swi_Handle __inst, xdc_UInt mask );

/* post__E */

extern void ti_sysbios_knl_Swi_post__E( ti_sysbios_knl_Swi_Handle __inst );

extern void ti_sysbios_knl_Swi_post__F( ti_sysbios_knl_Swi_Object* __inst );
extern void ti_sysbios_knl_Swi_post__R( ti_sysbios_knl_Swi_Handle __inst );

/* schedule__I */

extern void ti_sysbios_knl_Swi_schedule__I( void );

/* run__I */

extern void ti_sysbios_knl_Swi_run__I( ti_sysbios_knl_Swi_Object* swi );

/* postInit__I */

extern xdc_Int ti_sysbios_knl_Swi_postInit__I( ti_sysbios_knl_Swi_Object* swi, xdc_runtime_Error_Block* eb );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* andn_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Swi_andn_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Swi_andn_FxnT ti_sysbios_knl_Swi_andn_fxnP( void )
{
    return (ti_sysbios_knl_Swi_andn_FxnT)ti_sysbios_knl_Swi_andn__E; 
}

/* dec_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Swi_dec_FxnT)(void*);
static inline ti_sysbios_knl_Swi_dec_FxnT ti_sysbios_knl_Swi_dec_fxnP( void )
{
    return (ti_sysbios_knl_Swi_dec_FxnT)ti_sysbios_knl_Swi_dec__E; 
}

/* getHookContext_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_knl_Swi_getHookContext_FxnT)(void*, xdc_Int);
static inline ti_sysbios_knl_Swi_getHookContext_FxnT ti_sysbios_knl_Swi_getHookContext_fxnP( void )
{
    return (ti_sysbios_knl_Swi_getHookContext_FxnT)ti_sysbios_knl_Swi_getHookContext__E; 
}

/* setHookContext_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Swi_setHookContext_FxnT)(void*, xdc_Int, xdc_Ptr);
static inline ti_sysbios_knl_Swi_setHookContext_FxnT ti_sysbios_knl_Swi_setHookContext_fxnP( void )
{
    return (ti_sysbios_knl_Swi_setHookContext_FxnT)ti_sysbios_knl_Swi_setHookContext__E; 
}

/* getPri_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_knl_Swi_getPri_FxnT)(void*);
static inline ti_sysbios_knl_Swi_getPri_FxnT ti_sysbios_knl_Swi_getPri_fxnP( void )
{
    return (ti_sysbios_knl_Swi_getPri_FxnT)ti_sysbios_knl_Swi_getPri__E; 
}

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_knl_Swi_FuncPtr (*ti_sysbios_knl_Swi_getFunc_FxnT)(void*, xdc_UArg*, xdc_UArg*);
static inline ti_sysbios_knl_Swi_getFunc_FxnT ti_sysbios_knl_Swi_getFunc_fxnP( void )
{
    return (ti_sysbios_knl_Swi_getFunc_FxnT)ti_sysbios_knl_Swi_getFunc__E; 
}

/* inc_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Swi_inc_FxnT)(void*);
static inline ti_sysbios_knl_Swi_inc_FxnT ti_sysbios_knl_Swi_inc_fxnP( void )
{
    return (ti_sysbios_knl_Swi_inc_FxnT)ti_sysbios_knl_Swi_inc__E; 
}

/* or_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Swi_or_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Swi_or_FxnT ti_sysbios_knl_Swi_or_fxnP( void )
{
    return (ti_sysbios_knl_Swi_or_FxnT)ti_sysbios_knl_Swi_or__E; 
}

/* post_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Swi_post_FxnT)(void*);
static inline ti_sysbios_knl_Swi_post_FxnT ti_sysbios_knl_Swi_post_fxnP( void )
{
    return (ti_sysbios_knl_Swi_post_FxnT)ti_sysbios_knl_Swi_post__E; 
}


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Swi_Module__id ti_sysbios_knl_Swi_Module_id( void ) 
{
    return ti_sysbios_knl_Swi_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_knl_Swi_Module_hasMask( void ) 
{
    return ti_sysbios_knl_Swi_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_knl_Swi_Module_getMask( void ) 
{
    return ti_sysbios_knl_Swi_Module__diagsMask__C != 0 ? *ti_sysbios_knl_Swi_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_knl_Swi_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_knl_Swi_Module__diagsMask__C != 0) *ti_sysbios_knl_Swi_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_knl_Swi_Params_init( ti_sysbios_knl_Swi_Params* prms ) 
{
    if (prms) {
        ti_sysbios_knl_Swi_Params__init__S(prms, 0, sizeof(ti_sysbios_knl_Swi_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_knl_Swi_Params_copy( ti_sysbios_knl_Swi_Params* dst, const ti_sysbios_knl_Swi_Params* src ) 
{
    if (dst) {
        ti_sysbios_knl_Swi_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_knl_Swi_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_Object_get( ti_sysbios_knl_Swi_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_knl_Swi_Handle)ti_sysbios_knl_Swi_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_Object_first( void )
{
    return (ti_sysbios_knl_Swi_Handle)ti_sysbios_knl_Swi_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_Object_next( ti_sysbios_knl_Swi_Object* obj )
{
    return (ti_sysbios_knl_Swi_Handle)ti_sysbios_knl_Swi_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_knl_Swi_Handle_label( ti_sysbios_knl_Swi_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_knl_Swi_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_knl_Swi_Handle_name( ti_sysbios_knl_Swi_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_knl_Swi_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_create( ti_sysbios_knl_Swi_FuncPtr fxn, const ti_sysbios_knl_Swi_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_knl_Swi_Args__create __args;
    __args.fxn = fxn;
    return (ti_sysbios_knl_Swi_Handle)ti_sysbios_knl_Swi_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Swi_Params), __eb);
}

/* construct */
static inline void ti_sysbios_knl_Swi_construct( ti_sysbios_knl_Swi_Struct* __obj, ti_sysbios_knl_Swi_FuncPtr fxn, const ti_sysbios_knl_Swi_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_knl_Swi_Args__create __args;
    __args.fxn = fxn;
    ti_sysbios_knl_Swi_Object__create__S(__obj, sizeof (ti_sysbios_knl_Swi_Struct), &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Swi_Params), __eb);
}

/* delete */
static inline void ti_sysbios_knl_Swi_delete( ti_sysbios_knl_Swi_Handle* instp )
{
    ti_sysbios_knl_Swi_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_knl_Swi_destruct( ti_sysbios_knl_Swi_Struct* obj )
{
    ti_sysbios_knl_Swi_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_knl_Swi_Handle ti_sysbios_knl_Swi_handle( ti_sysbios_knl_Swi_Struct* str )
{
    return (ti_sysbios_knl_Swi_Handle)str;
}

/* struct */
static inline ti_sysbios_knl_Swi_Struct* ti_sysbios_knl_Swi_struct( ti_sysbios_knl_Swi_Handle inst )
{
    return (ti_sysbios_knl_Swi_Struct*)inst;
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:34; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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

/* TickSource */
enum ti_sysbios_knl_Clock_TickSource {
    ti_sysbios_knl_Clock_TickSource_TIMER,
    ti_sysbios_knl_Clock_TickSource_USER,
    ti_sysbios_knl_Clock_TickSource_NULL
};
typedef enum ti_sysbios_knl_Clock_TickSource ti_sysbios_knl_Clock_TickSource;

/* TickMode */
enum ti_sysbios_knl_Clock_TickMode {
    ti_sysbios_knl_Clock_TickMode_PERIODIC,
    ti_sysbios_knl_Clock_TickMode_DYNAMIC
};
typedef enum ti_sysbios_knl_Clock_TickMode ti_sysbios_knl_Clock_TickMode;

/* FuncPtr */
typedef void (*ti_sysbios_knl_Clock_FuncPtr)(xdc_UArg);


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_knl_Clock_Args__create {
    ti_sysbios_knl_Clock_FuncPtr clockFxn;
    xdc_UInt timeout;
} ti_sysbios_knl_Clock_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Clock_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Clock_Module__diagsEnabled ti_sysbios_knl_Clock_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Clock_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Clock_Module__diagsIncluded ti_sysbios_knl_Clock_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Clock_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Clock_Module__diagsMask ti_sysbios_knl_Clock_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Clock_Module__gateObj;
extern far const CT__ti_sysbios_knl_Clock_Module__gateObj ti_sysbios_knl_Clock_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Clock_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Clock_Module__gatePrms ti_sysbios_knl_Clock_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Clock_Module__id;
extern far const CT__ti_sysbios_knl_Clock_Module__id ti_sysbios_knl_Clock_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Clock_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerDefined ti_sysbios_knl_Clock_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Clock_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerObj ti_sysbios_knl_Clock_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Clock_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerFxn0 ti_sysbios_knl_Clock_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Clock_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerFxn1 ti_sysbios_knl_Clock_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Clock_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerFxn2 ti_sysbios_knl_Clock_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Clock_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerFxn4 ti_sysbios_knl_Clock_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Clock_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Clock_Module__loggerFxn8 ti_sysbios_knl_Clock_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Clock_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Clock_Module__startupDoneFxn ti_sysbios_knl_Clock_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Clock_Object__count;
extern far const CT__ti_sysbios_knl_Clock_Object__count ti_sysbios_knl_Clock_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Clock_Object__heap;
extern far const CT__ti_sysbios_knl_Clock_Object__heap ti_sysbios_knl_Clock_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Clock_Object__sizeof;
extern far const CT__ti_sysbios_knl_Clock_Object__sizeof ti_sysbios_knl_Clock_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Clock_Object__table;
extern far const CT__ti_sysbios_knl_Clock_Object__table ti_sysbios_knl_Clock_Object__table__C;

/* LW_delayed */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Clock_LW_delayed;
extern far const CT__ti_sysbios_knl_Clock_LW_delayed ti_sysbios_knl_Clock_LW_delayed__C;

/* LM_tick */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Clock_LM_tick;
extern far const CT__ti_sysbios_knl_Clock_LM_tick ti_sysbios_knl_Clock_LM_tick__C;

/* LM_begin */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Clock_LM_begin;
extern far const CT__ti_sysbios_knl_Clock_LM_begin ti_sysbios_knl_Clock_LM_begin__C;

/* A_clockDisabled */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Clock_A_clockDisabled;
extern far const CT__ti_sysbios_knl_Clock_A_clockDisabled ti_sysbios_knl_Clock_A_clockDisabled__C;

/* A_badThreadType */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Clock_A_badThreadType;
extern far const CT__ti_sysbios_knl_Clock_A_badThreadType ti_sysbios_knl_Clock_A_badThreadType__C;

/* tickSource */
typedef ti_sysbios_knl_Clock_TickSource CT__ti_sysbios_knl_Clock_tickSource;
extern far const CT__ti_sysbios_knl_Clock_tickSource ti_sysbios_knl_Clock_tickSource__C;

/* tickMode */
typedef ti_sysbios_knl_Clock_TickMode CT__ti_sysbios_knl_Clock_tickMode;
extern far const CT__ti_sysbios_knl_Clock_tickMode ti_sysbios_knl_Clock_tickMode__C;

/* timerId */
typedef xdc_UInt CT__ti_sysbios_knl_Clock_timerId;
extern far const CT__ti_sysbios_knl_Clock_timerId ti_sysbios_knl_Clock_timerId__C;

/* tickPeriod */
typedef xdc_UInt32 CT__ti_sysbios_knl_Clock_tickPeriod;
extern far const CT__ti_sysbios_knl_Clock_tickPeriod ti_sysbios_knl_Clock_tickPeriod__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_knl_Clock_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_Bool startFlag;
    xdc_UInt period;
    xdc_UArg arg;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_knl_Clock_Struct {
    ti_sysbios_knl_Queue_Elem __f0;
    xdc_UInt32 __f1;
    xdc_UInt32 __f2;
    xdc_UInt32 __f3;
    volatile xdc_Bool __f4;
    ti_sysbios_knl_Clock_FuncPtr __f5;
    xdc_UArg __f6;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int ti_sysbios_knl_Clock_Module_startup__E( xdc_Int state );

extern xdc_Int ti_sysbios_knl_Clock_Module_startup__F( xdc_Int state );

extern xdc_Int ti_sysbios_knl_Clock_Module_startup__R( xdc_Int state );

/* Instance_init__F */

extern void ti_sysbios_knl_Clock_Instance_init__F( ti_sysbios_knl_Clock_Object*, ti_sysbios_knl_Clock_FuncPtr clockFxn, xdc_UInt timeout, const ti_sysbios_knl_Clock_Params* );

/* Instance_finalize__F */

extern void ti_sysbios_knl_Clock_Instance_finalize__F( ti_sysbios_knl_Clock_Object* );

/* Instance_init__R */

extern void ti_sysbios_knl_Clock_Instance_init__R( ti_sysbios_knl_Clock_Object*, ti_sysbios_knl_Clock_FuncPtr clockFxn, xdc_UInt timeout, const ti_sysbios_knl_Clock_Params* );

/* Instance_finalize__R */

extern void ti_sysbios_knl_Clock_Instance_finalize__R( ti_sysbios_knl_Clock_Object* );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Clock_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Clock_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Clock_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Clock_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Clock_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Clock_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Clock_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Clock_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Clock_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* getTicks__E */

extern xdc_UInt32 ti_sysbios_knl_Clock_getTicks__E( void );

extern xdc_UInt32 ti_sysbios_knl_Clock_getTicks__F( void );
extern xdc_UInt32 ti_sysbios_knl_Clock_getTicks__R( void );

/* getTimerHandle__E */

extern ti_sysbios_hal_Timer_Handle ti_sysbios_knl_Clock_getTimerHandle__E( void );

extern ti_sysbios_hal_Timer_Handle ti_sysbios_knl_Clock_getTimerHandle__F( void );
extern ti_sysbios_hal_Timer_Handle ti_sysbios_knl_Clock_getTimerHandle__R( void );

/* tickStop__E */

extern void ti_sysbios_knl_Clock_tickStop__E( void );

extern void ti_sysbios_knl_Clock_tickStop__F( void );
extern void ti_sysbios_knl_Clock_tickStop__R( void );

/* tickReconfig__E */

extern xdc_Bool ti_sysbios_knl_Clock_tickReconfig__E( void );

extern xdc_Bool ti_sysbios_knl_Clock_tickReconfig__F( void );
extern xdc_Bool ti_sysbios_knl_Clock_tickReconfig__R( void );

/* tickStart__E */

extern void ti_sysbios_knl_Clock_tickStart__E( void );

extern void ti_sysbios_knl_Clock_tickStart__F( void );
extern void ti_sysbios_knl_Clock_tickStart__R( void );

/* tick__E */

extern void ti_sysbios_knl_Clock_tick__E( void );

extern void ti_sysbios_knl_Clock_tick__F( void );
extern void ti_sysbios_knl_Clock_tick__R( void );

/* workFunc__E */

extern void ti_sysbios_knl_Clock_workFunc__E( xdc_UArg arg0, xdc_UArg arg1 );

extern void ti_sysbios_knl_Clock_workFunc__F( xdc_UArg arg0, xdc_UArg arg1 );
extern void ti_sysbios_knl_Clock_workFunc__R( xdc_UArg arg0, xdc_UArg arg1 );

/* workFuncDynamic__E */

extern void ti_sysbios_knl_Clock_workFuncDynamic__E( xdc_UArg arg0, xdc_UArg arg1 );

extern void ti_sysbios_knl_Clock_workFuncDynamic__F( xdc_UArg arg0, xdc_UArg arg1 );
extern void ti_sysbios_knl_Clock_workFuncDynamic__R( xdc_UArg arg0, xdc_UArg arg1 );

/* logTick__E */

extern void ti_sysbios_knl_Clock_logTick__E( void );

extern void ti_sysbios_knl_Clock_logTick__F( void );
extern void ti_sysbios_knl_Clock_logTick__R( void );

/* getCompletedTicks__E */

extern xdc_UInt32 ti_sysbios_knl_Clock_getCompletedTicks__E( void );

extern xdc_UInt32 ti_sysbios_knl_Clock_getCompletedTicks__F( void );
extern xdc_UInt32 ti_sysbios_knl_Clock_getCompletedTicks__R( void );

/* getTickPeriod__E */

extern xdc_UInt32 ti_sysbios_knl_Clock_getTickPeriod__E( void );

extern xdc_UInt32 ti_sysbios_knl_Clock_getTickPeriod__F( void );
extern xdc_UInt32 ti_sysbios_knl_Clock_getTickPeriod__R( void );

/* setupTimerToSkipTicks__E */

extern void ti_sysbios_knl_Clock_setupTimerToSkipTicks__E( xdc_UInt skips );

extern void ti_sysbios_knl_Clock_setupTimerToSkipTicks__F( xdc_UInt skips );
extern void ti_sysbios_knl_Clock_setupTimerToSkipTicks__R( xdc_UInt skips );

/* start__E */

extern void ti_sysbios_knl_Clock_start__E( ti_sysbios_knl_Clock_Handle __inst );

extern void ti_sysbios_knl_Clock_start__F( ti_sysbios_knl_Clock_Object* __inst );
extern void ti_sysbios_knl_Clock_start__R( ti_sysbios_knl_Clock_Handle __inst );

/* startI__E */

extern void ti_sysbios_knl_Clock_startI__E( ti_sysbios_knl_Clock_Handle __inst );

extern void ti_sysbios_knl_Clock_startI__F( ti_sysbios_knl_Clock_Object* __inst );
extern void ti_sysbios_knl_Clock_startI__R( ti_sysbios_knl_Clock_Handle __inst );

/* stop__E */

extern void ti_sysbios_knl_Clock_stop__E( ti_sysbios_knl_Clock_Handle __inst );

extern void ti_sysbios_knl_Clock_stop__F( ti_sysbios_knl_Clock_Object* __inst );
extern void ti_sysbios_knl_Clock_stop__R( ti_sysbios_knl_Clock_Handle __inst );

/* setPeriod__E */

extern void ti_sysbios_knl_Clock_setPeriod__E( ti_sysbios_knl_Clock_Handle __inst, xdc_UInt period );

extern void ti_sysbios_knl_Clock_setPeriod__F( ti_sysbios_knl_Clock_Object* __inst, xdc_UInt period );
extern void ti_sysbios_knl_Clock_setPeriod__R( ti_sysbios_knl_Clock_Handle __inst, xdc_UInt period );

/* setTimeout__E */

extern void ti_sysbios_knl_Clock_setTimeout__E( ti_sysbios_knl_Clock_Handle __inst, xdc_UInt timeout );

extern void ti_sysbios_knl_Clock_setTimeout__F( ti_sysbios_knl_Clock_Object* __inst, xdc_UInt timeout );
extern void ti_sysbios_knl_Clock_setTimeout__R( ti_sysbios_knl_Clock_Handle __inst, xdc_UInt timeout );

/* setFunc__E */

extern void ti_sysbios_knl_Clock_setFunc__E( ti_sysbios_knl_Clock_Handle __inst, ti_sysbios_knl_Clock_FuncPtr fxn, xdc_UArg arg );

extern void ti_sysbios_knl_Clock_setFunc__F( ti_sysbios_knl_Clock_Object* __inst, ti_sysbios_knl_Clock_FuncPtr fxn, xdc_UArg arg );
extern void ti_sysbios_knl_Clock_setFunc__R( ti_sysbios_knl_Clock_Handle __inst, ti_sysbios_knl_Clock_FuncPtr fxn, xdc_UArg arg );

/* getPeriod__E */

extern xdc_UInt ti_sysbios_knl_Clock_getPeriod__E( ti_sysbios_knl_Clock_Handle __inst );

extern xdc_UInt ti_sysbios_knl_Clock_getPeriod__F( ti_sysbios_knl_Clock_Object* __inst );
extern xdc_UInt ti_sysbios_knl_Clock_getPeriod__R( ti_sysbios_knl_Clock_Handle __inst );

/* getTimeout__E */

extern xdc_UInt ti_sysbios_knl_Clock_getTimeout__E( ti_sysbios_knl_Clock_Handle __inst );

extern xdc_UInt ti_sysbios_knl_Clock_getTimeout__F( ti_sysbios_knl_Clock_Object* __inst );
extern xdc_UInt ti_sysbios_knl_Clock_getTimeout__R( ti_sysbios_knl_Clock_Handle __inst );

/* doTick__I */

extern void ti_sysbios_knl_Clock_doTick__I( xdc_UArg arg );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* start_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Clock_start_FxnT)(void*);
static inline ti_sysbios_knl_Clock_start_FxnT ti_sysbios_knl_Clock_start_fxnP( void )
{
    return (ti_sysbios_knl_Clock_start_FxnT)ti_sysbios_knl_Clock_start__E; 
}

/* startI_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Clock_startI_FxnT)(void*);
static inline ti_sysbios_knl_Clock_startI_FxnT ti_sysbios_knl_Clock_startI_fxnP( void )
{
    return (ti_sysbios_knl_Clock_startI_FxnT)ti_sysbios_knl_Clock_startI__E; 
}

/* stop_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Clock_stop_FxnT)(void*);
static inline ti_sysbios_knl_Clock_stop_FxnT ti_sysbios_knl_Clock_stop_fxnP( void )
{
    return (ti_sysbios_knl_Clock_stop_FxnT)ti_sysbios_knl_Clock_stop__E; 
}

/* setPeriod_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Clock_setPeriod_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Clock_setPeriod_FxnT ti_sysbios_knl_Clock_setPeriod_fxnP( void )
{
    return (ti_sysbios_knl_Clock_setPeriod_FxnT)ti_sysbios_knl_Clock_setPeriod__E; 
}

/* setTimeout_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Clock_setTimeout_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Clock_setTimeout_FxnT ti_sysbios_knl_Clock_setTimeout_fxnP( void )
{
    return (ti_sysbios_knl_Clock_setTimeout_FxnT)ti_sysbios_knl_Clock_setTimeout__E; 
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Clock_setFunc_FxnT)(void*, ti_sysbios_knl_Clock_FuncPtr, xdc_UArg);
static inline ti_sysbios_knl_Clock_setFunc_FxnT ti_sysbios_knl_Clock_setFunc_fxnP( void )
{
    return (ti_sysbios_knl_Clock_setFunc_FxnT)ti_sysbios_knl_Clock_setFunc__E; 
}

/* getPeriod_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_knl_Clock_getPeriod_FxnT)(void*);
static inline ti_sysbios_knl_Clock_getPeriod_FxnT ti_sysbios_knl_Clock_getPeriod_fxnP( void )
{
    return (ti_sysbios_knl_Clock_getPeriod_FxnT)ti_sysbios_knl_Clock_getPeriod__E; 
}

/* getTimeout_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_knl_Clock_getTimeout_FxnT)(void*);
static inline ti_sysbios_knl_Clock_getTimeout_FxnT ti_sysbios_knl_Clock_getTimeout_fxnP( void )
{
    return (ti_sysbios_knl_Clock_getTimeout_FxnT)ti_sysbios_knl_Clock_getTimeout__E; 
}


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Clock_Module__id ti_sysbios_knl_Clock_Module_id( void ) 
{
    return ti_sysbios_knl_Clock_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_knl_Clock_Module_hasMask( void ) 
{
    return ti_sysbios_knl_Clock_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_knl_Clock_Module_getMask( void ) 
{
    return ti_sysbios_knl_Clock_Module__diagsMask__C != 0 ? *ti_sysbios_knl_Clock_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_knl_Clock_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_knl_Clock_Module__diagsMask__C != 0) *ti_sysbios_knl_Clock_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_knl_Clock_Params_init( ti_sysbios_knl_Clock_Params* prms ) 
{
    if (prms) {
        ti_sysbios_knl_Clock_Params__init__S(prms, 0, sizeof(ti_sysbios_knl_Clock_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_knl_Clock_Params_copy( ti_sysbios_knl_Clock_Params* dst, const ti_sysbios_knl_Clock_Params* src ) 
{
    if (dst) {
        ti_sysbios_knl_Clock_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_knl_Clock_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_knl_Clock_Handle ti_sysbios_knl_Clock_Object_get( ti_sysbios_knl_Clock_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_knl_Clock_Handle)ti_sysbios_knl_Clock_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_knl_Clock_Handle ti_sysbios_knl_Clock_Object_first( void )
{
    return (ti_sysbios_knl_Clock_Handle)ti_sysbios_knl_Clock_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_knl_Clock_Handle ti_sysbios_knl_Clock_Object_next( ti_sysbios_knl_Clock_Object* obj )
{
    return (ti_sysbios_knl_Clock_Handle)ti_sysbios_knl_Clock_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_knl_Clock_Handle_label( ti_sysbios_knl_Clock_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_knl_Clock_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_knl_Clock_Handle_name( ti_sysbios_knl_Clock_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_knl_Clock_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_knl_Clock_Handle ti_sysbios_knl_Clock_create( ti_sysbios_knl_Clock_FuncPtr clockFxn, xdc_UInt timeout, const ti_sysbios_knl_Clock_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_knl_Clock_Args__create __args;
    __args.clockFxn = clockFxn;
    __args.timeout = timeout;
    return (ti_sysbios_knl_Clock_Handle)ti_sysbios_knl_Clock_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Clock_Params), __eb);
}

/* construct */
static inline void ti_sysbios_knl_Clock_construct( ti_sysbios_knl_Clock_Struct* __obj, ti_sysbios_knl_Clock_FuncPtr clockFxn, xdc_UInt timeout, const ti_sysbios_knl_Clock_Params* __prms )
{
    ti_sysbios_knl_Clock_Args__create __args;
    __args.clockFxn = clockFxn;
    __args.timeout = timeout;
    ti_sysbios_knl_Clock_Object__create__S(__obj, sizeof (ti_sysbios_knl_Clock_Struct), &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Clock_Params), 0);
}

/* delete */
static inline void ti_sysbios_knl_Clock_delete( ti_sysbios_knl_Clock_Handle* instp )
{
    ti_sysbios_knl_Clock_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_knl_Clock_destruct( ti_sysbios_knl_Clock_Struct* obj )
{
    ti_sysbios_knl_Clock_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_knl_Clock_Handle ti_sysbios_knl_Clock_handle( ti_sysbios_knl_Clock_Struct* str )
{
    return (ti_sysbios_knl_Clock_Handle)str;
}

/* struct */
static inline ti_sysbios_knl_Clock_Struct* ti_sysbios_knl_Clock_struct( ti_sysbios_knl_Clock_Handle inst )
{
    return (ti_sysbios_knl_Clock_Struct*)inst;
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:32; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     MODULE-WIDE CONFIGS
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
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
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
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
 *  @(#) ti.sysbios.interfaces; 2, 0, 0, 0,545; 3-20-2012 14:03:23; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FuncPtr */
typedef ti_sysbios_interfaces_ITaskSupport_FuncPtr ti_sysbios_knl_Task_SupportProxy_FuncPtr;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Task_SupportProxy_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__diagsEnabled ti_sysbios_knl_Task_SupportProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Task_SupportProxy_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__diagsIncluded ti_sysbios_knl_Task_SupportProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Task_SupportProxy_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__diagsMask ti_sysbios_knl_Task_SupportProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_SupportProxy_Module__gateObj;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__gateObj ti_sysbios_knl_Task_SupportProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_SupportProxy_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__gatePrms ti_sysbios_knl_Task_SupportProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Task_SupportProxy_Module__id;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__id ti_sysbios_knl_Task_SupportProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerDefined ti_sysbios_knl_Task_SupportProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerObj ti_sysbios_knl_Task_SupportProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn0 ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn1 ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn2 ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn4 ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn8 ti_sysbios_knl_Task_SupportProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Task_SupportProxy_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Module__startupDoneFxn ti_sysbios_knl_Task_SupportProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Task_SupportProxy_Object__count;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Object__count ti_sysbios_knl_Task_SupportProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Task_SupportProxy_Object__heap;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Object__heap ti_sysbios_knl_Task_SupportProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Task_SupportProxy_Object__sizeof;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Object__sizeof ti_sysbios_knl_Task_SupportProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_SupportProxy_Object__table;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_Object__table ti_sysbios_knl_Task_SupportProxy_Object__table__C;

/* defaultStackSize */
typedef xdc_SizeT CT__ti_sysbios_knl_Task_SupportProxy_defaultStackSize;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_defaultStackSize ti_sysbios_knl_Task_SupportProxy_defaultStackSize__C;

/* stackAlignment */
typedef xdc_UInt CT__ti_sysbios_knl_Task_SupportProxy_stackAlignment;
extern far const CT__ti_sysbios_knl_Task_SupportProxy_stackAlignment ti_sysbios_knl_Task_SupportProxy_stackAlignment__C;


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_knl_Task_SupportProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*start)(xdc_Ptr, ti_sysbios_interfaces_ITaskSupport_FuncPtr, ti_sysbios_interfaces_ITaskSupport_FuncPtr, xdc_runtime_Error_Block*);
    void (*swap)(xdc_Ptr*, xdc_Ptr*);
    xdc_Bool (*checkStack)(xdc_Char*, xdc_SizeT);
    xdc_SizeT (*stackUsed)(xdc_Char*, xdc_SizeT);
    xdc_UInt (*getStackAlignment)(void);
    xdc_SizeT (*getDefaultStackSize)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const ti_sysbios_knl_Task_SupportProxy_Fxns__ ti_sysbios_knl_Task_SupportProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Task_SupportProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Task_SupportProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Task_SupportProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Task_SupportProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Task_SupportProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool ti_sysbios_knl_Task_SupportProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_Proxy__delegate__S( void );

/* start__E */

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_start__E( xdc_Ptr curTask, ti_sysbios_interfaces_ITaskSupport_FuncPtr enter, ti_sysbios_interfaces_ITaskSupport_FuncPtr exit, xdc_runtime_Error_Block* eb );

extern xdc_Ptr ti_sysbios_knl_Task_SupportProxy_start__R( xdc_Ptr curTask, ti_sysbios_interfaces_ITaskSupport_FuncPtr enter, ti_sysbios_interfaces_ITaskSupport_FuncPtr exit, xdc_runtime_Error_Block* eb );

/* swap__E */

extern void ti_sysbios_knl_Task_SupportProxy_swap__E( xdc_Ptr* oldtskContext, xdc_Ptr* newtskContext );

extern void ti_sysbios_knl_Task_SupportProxy_swap__R( xdc_Ptr* oldtskContext, xdc_Ptr* newtskContext );

/* checkStack__E */

extern xdc_Bool ti_sysbios_knl_Task_SupportProxy_checkStack__E( xdc_Char* stack, xdc_SizeT size );

extern xdc_Bool ti_sysbios_knl_Task_SupportProxy_checkStack__R( xdc_Char* stack, xdc_SizeT size );

/* stackUsed__E */

extern xdc_SizeT ti_sysbios_knl_Task_SupportProxy_stackUsed__E( xdc_Char* stack, xdc_SizeT size );

extern xdc_SizeT ti_sysbios_knl_Task_SupportProxy_stackUsed__R( xdc_Char* stack, xdc_SizeT size );

/* getStackAlignment__E */

extern xdc_UInt ti_sysbios_knl_Task_SupportProxy_getStackAlignment__E( void );

extern xdc_UInt ti_sysbios_knl_Task_SupportProxy_getStackAlignment__R( void );

/* getDefaultStackSize__E */

extern xdc_SizeT ti_sysbios_knl_Task_SupportProxy_getDefaultStackSize__E( void );

extern xdc_SizeT ti_sysbios_knl_Task_SupportProxy_getDefaultStackSize__R( void );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sysbios_interfaces_ITaskSupport_Module ti_sysbios_knl_Task_SupportProxy_Module_upCast( void )
{
    return (ti_sysbios_interfaces_ITaskSupport_Module)ti_sysbios_knl_Task_SupportProxy_Proxy__delegate__S();
}

/* Module_to_ti_sysbios_interfaces_ITaskSupport */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Task_SupportProxy_Module__id ti_sysbios_knl_Task_SupportProxy_Module_id( void ) 
{
    return ti_sysbios_knl_Task_SupportProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FuncPtr */
typedef void (*ti_sysbios_knl_Task_FuncPtr)(xdc_UArg, xdc_UArg);

/* AllBlockedFuncPtr */
typedef void (*ti_sysbios_knl_Task_AllBlockedFuncPtr)(void);

/* Mode */
enum ti_sysbios_knl_Task_Mode {
    ti_sysbios_knl_Task_Mode_RUNNING,
    ti_sysbios_knl_Task_Mode_READY,
    ti_sysbios_knl_Task_Mode_BLOCKED,
    ti_sysbios_knl_Task_Mode_TERMINATED,
    ti_sysbios_knl_Task_Mode_INACTIVE
};
typedef enum ti_sysbios_knl_Task_Mode ti_sysbios_knl_Task_Mode;

/* Stat */
struct ti_sysbios_knl_Task_Stat {
    xdc_Int priority;
    xdc_Ptr stack;
    xdc_SizeT stackSize;
    xdc_runtime_IHeap_Handle stackHeap;
    xdc_Ptr env;
    ti_sysbios_knl_Task_Mode mode;
    xdc_Ptr sp;
    xdc_SizeT used;
};

/* HookSet */
struct ti_sysbios_knl_Task_HookSet {
    void (*registerFxn)(xdc_Int);
    void (*createFxn)(ti_sysbios_knl_Task_Handle, xdc_runtime_Error_Block*);
    void (*readyFxn)(ti_sysbios_knl_Task_Handle);
    void (*switchFxn)(ti_sysbios_knl_Task_Handle, ti_sysbios_knl_Task_Handle);
    void (*exitFxn)(ti_sysbios_knl_Task_Handle);
    void (*deleteFxn)(ti_sysbios_knl_Task_Handle);
};


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_knl_Task_Args__create {
    ti_sysbios_knl_Task_FuncPtr fxn;
} ti_sysbios_knl_Task_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* PendElem */
struct ti_sysbios_knl_Task_PendElem {
    ti_sysbios_knl_Queue_Elem qElem;
    ti_sysbios_knl_Task_Handle task;
    ti_sysbios_knl_Clock_Handle clock;
};

/* Instance_State */
typedef xdc_Char __T1_ti_sysbios_knl_Task_Instance_State__stack;
typedef xdc_Char *__ARRAY1_ti_sysbios_knl_Task_Instance_State__stack;
typedef __ARRAY1_ti_sysbios_knl_Task_Instance_State__stack __TA_ti_sysbios_knl_Task_Instance_State__stack;
typedef xdc_Ptr __T1_ti_sysbios_knl_Task_Instance_State__hookEnv;
typedef xdc_Ptr *__ARRAY1_ti_sysbios_knl_Task_Instance_State__hookEnv;
typedef __ARRAY1_ti_sysbios_knl_Task_Instance_State__hookEnv __TA_ti_sysbios_knl_Task_Instance_State__hookEnv;

/* Module_State */
typedef ti_sysbios_knl_Queue_Instance_State __T1_ti_sysbios_knl_Task_Module_State__readyQ;
typedef ti_sysbios_knl_Queue_Instance_State *__ARRAY1_ti_sysbios_knl_Task_Module_State__readyQ;
typedef __ARRAY1_ti_sysbios_knl_Task_Module_State__readyQ __TA_ti_sysbios_knl_Task_Module_State__readyQ;
typedef ti_sysbios_knl_Task_Handle __T1_ti_sysbios_knl_Task_Module_State__constructedTasks;
typedef ti_sysbios_knl_Task_Handle *__ARRAY1_ti_sysbios_knl_Task_Module_State__constructedTasks;
typedef __ARRAY1_ti_sysbios_knl_Task_Module_State__constructedTasks __TA_ti_sysbios_knl_Task_Module_State__constructedTasks;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Task_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Task_Module__diagsEnabled ti_sysbios_knl_Task_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Task_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Task_Module__diagsIncluded ti_sysbios_knl_Task_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Task_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Task_Module__diagsMask ti_sysbios_knl_Task_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_Module__gateObj;
extern far const CT__ti_sysbios_knl_Task_Module__gateObj ti_sysbios_knl_Task_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Task_Module__gatePrms ti_sysbios_knl_Task_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Task_Module__id;
extern far const CT__ti_sysbios_knl_Task_Module__id ti_sysbios_knl_Task_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Task_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Task_Module__loggerDefined ti_sysbios_knl_Task_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Task_Module__loggerObj ti_sysbios_knl_Task_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Task_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Task_Module__loggerFxn0 ti_sysbios_knl_Task_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Task_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Task_Module__loggerFxn1 ti_sysbios_knl_Task_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Task_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Task_Module__loggerFxn2 ti_sysbios_knl_Task_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Task_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Task_Module__loggerFxn4 ti_sysbios_knl_Task_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Task_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Task_Module__loggerFxn8 ti_sysbios_knl_Task_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Task_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Task_Module__startupDoneFxn ti_sysbios_knl_Task_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Task_Object__count;
extern far const CT__ti_sysbios_knl_Task_Object__count ti_sysbios_knl_Task_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Task_Object__heap;
extern far const CT__ti_sysbios_knl_Task_Object__heap ti_sysbios_knl_Task_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Task_Object__sizeof;
extern far const CT__ti_sysbios_knl_Task_Object__sizeof ti_sysbios_knl_Task_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Task_Object__table;
extern far const CT__ti_sysbios_knl_Task_Object__table ti_sysbios_knl_Task_Object__table__C;

/* LM_switch */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LM_switch;
extern far const CT__ti_sysbios_knl_Task_LM_switch ti_sysbios_knl_Task_LM_switch__C;

/* LM_sleep */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LM_sleep;
extern far const CT__ti_sysbios_knl_Task_LM_sleep ti_sysbios_knl_Task_LM_sleep__C;

/* LD_ready */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LD_ready;
extern far const CT__ti_sysbios_knl_Task_LD_ready ti_sysbios_knl_Task_LD_ready__C;

/* LD_block */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LD_block;
extern far const CT__ti_sysbios_knl_Task_LD_block ti_sysbios_knl_Task_LD_block__C;

/* LM_yield */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LM_yield;
extern far const CT__ti_sysbios_knl_Task_LM_yield ti_sysbios_knl_Task_LM_yield__C;

/* LM_setPri */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LM_setPri;
extern far const CT__ti_sysbios_knl_Task_LM_setPri ti_sysbios_knl_Task_LM_setPri__C;

/* LD_exit */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Task_LD_exit;
extern far const CT__ti_sysbios_knl_Task_LD_exit ti_sysbios_knl_Task_LD_exit__C;

/* E_stackOverflow */
typedef xdc_runtime_Error_Id CT__ti_sysbios_knl_Task_E_stackOverflow;
extern far const CT__ti_sysbios_knl_Task_E_stackOverflow ti_sysbios_knl_Task_E_stackOverflow__C;

/* E_spOutOfBounds */
typedef xdc_runtime_Error_Id CT__ti_sysbios_knl_Task_E_spOutOfBounds;
extern far const CT__ti_sysbios_knl_Task_E_spOutOfBounds ti_sysbios_knl_Task_E_spOutOfBounds__C;

/* A_badThreadType */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Task_A_badThreadType;
extern far const CT__ti_sysbios_knl_Task_A_badThreadType ti_sysbios_knl_Task_A_badThreadType__C;

/* A_badTaskState */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Task_A_badTaskState;
extern far const CT__ti_sysbios_knl_Task_A_badTaskState ti_sysbios_knl_Task_A_badTaskState__C;

/* A_noPendElem */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Task_A_noPendElem;
extern far const CT__ti_sysbios_knl_Task_A_noPendElem ti_sysbios_knl_Task_A_noPendElem__C;

/* A_taskDisabled */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Task_A_taskDisabled;
extern far const CT__ti_sysbios_knl_Task_A_taskDisabled ti_sysbios_knl_Task_A_taskDisabled__C;

/* A_badPriority */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Task_A_badPriority;
extern far const CT__ti_sysbios_knl_Task_A_badPriority ti_sysbios_knl_Task_A_badPriority__C;

/* A_badTimeout */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Task_A_badTimeout;
extern far const CT__ti_sysbios_knl_Task_A_badTimeout ti_sysbios_knl_Task_A_badTimeout__C;

/* numPriorities */
typedef xdc_UInt CT__ti_sysbios_knl_Task_numPriorities;
extern far const CT__ti_sysbios_knl_Task_numPriorities ti_sysbios_knl_Task_numPriorities__C;

/* defaultStackSize */
typedef xdc_SizeT CT__ti_sysbios_knl_Task_defaultStackSize;
extern far const CT__ti_sysbios_knl_Task_defaultStackSize ti_sysbios_knl_Task_defaultStackSize__C;

/* defaultStackHeap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Task_defaultStackHeap;
extern far const CT__ti_sysbios_knl_Task_defaultStackHeap ti_sysbios_knl_Task_defaultStackHeap__C;

/* allBlockedFunc */
typedef ti_sysbios_knl_Task_AllBlockedFuncPtr CT__ti_sysbios_knl_Task_allBlockedFunc;
extern far const CT__ti_sysbios_knl_Task_allBlockedFunc ti_sysbios_knl_Task_allBlockedFunc__C;

/* initStackFlag */
typedef xdc_Bool CT__ti_sysbios_knl_Task_initStackFlag;
extern far const CT__ti_sysbios_knl_Task_initStackFlag ti_sysbios_knl_Task_initStackFlag__C;

/* deleteTerminatedTasks */
typedef xdc_Bool CT__ti_sysbios_knl_Task_deleteTerminatedTasks;
extern far const CT__ti_sysbios_knl_Task_deleteTerminatedTasks ti_sysbios_knl_Task_deleteTerminatedTasks__C;

/* hooks */
typedef ti_sysbios_knl_Task_HookSet __T1_ti_sysbios_knl_Task_hooks;
typedef struct { int length; ti_sysbios_knl_Task_HookSet *elem; } __ARRAY1_ti_sysbios_knl_Task_hooks;
typedef __ARRAY1_ti_sysbios_knl_Task_hooks __TA_ti_sysbios_knl_Task_hooks;
typedef __TA_ti_sysbios_knl_Task_hooks CT__ti_sysbios_knl_Task_hooks;
extern far const CT__ti_sysbios_knl_Task_hooks ti_sysbios_knl_Task_hooks__C;

/* numConstructedTasks */
typedef xdc_UInt CT__ti_sysbios_knl_Task_numConstructedTasks;
extern far const CT__ti_sysbios_knl_Task_numConstructedTasks ti_sysbios_knl_Task_numConstructedTasks__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_knl_Task_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_UArg arg0;
    xdc_UArg arg1;
    xdc_Int priority;
    xdc_Ptr stack;
    xdc_SizeT stackSize;
    xdc_runtime_IHeap_Handle stackHeap;
    xdc_Ptr env;
    xdc_Bool vitalTaskFlag;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_knl_Task_Struct {
    ti_sysbios_knl_Queue_Elem __f0;
    volatile xdc_Int __f1;
    xdc_UInt __f2;
    xdc_Ptr __f3;
    ti_sysbios_knl_Task_Mode __f4;
    ti_sysbios_knl_Task_PendElem* __f5;
    xdc_SizeT __f6;
    __TA_ti_sysbios_knl_Task_Instance_State__stack __f7;
    xdc_runtime_IHeap_Handle __f8;
    ti_sysbios_knl_Task_FuncPtr __f9;
    xdc_UArg __f10;
    xdc_UArg __f11;
    xdc_Ptr __f12;
    __TA_ti_sysbios_knl_Task_Instance_State__hookEnv __f13;
    xdc_Bool __f14;
    ti_sysbios_knl_Queue_Handle __f15;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int ti_sysbios_knl_Task_Module_startup__E( xdc_Int state );

extern xdc_Int ti_sysbios_knl_Task_Module_startup__F( xdc_Int state );

extern xdc_Int ti_sysbios_knl_Task_Module_startup__R( xdc_Int state );

/* Instance_init__F */

extern int ti_sysbios_knl_Task_Instance_init__F( ti_sysbios_knl_Task_Object*, ti_sysbios_knl_Task_FuncPtr fxn, const ti_sysbios_knl_Task_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */

extern void ti_sysbios_knl_Task_Instance_finalize__F( ti_sysbios_knl_Task_Object* , int );

/* Instance_init__R */

extern int ti_sysbios_knl_Task_Instance_init__R( ti_sysbios_knl_Task_Object*, ti_sysbios_knl_Task_FuncPtr fxn, const ti_sysbios_knl_Task_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */

extern void ti_sysbios_knl_Task_Instance_finalize__R( ti_sysbios_knl_Task_Object* , int );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Task_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Task_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Task_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Task_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Task_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Task_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Task_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Task_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Task_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* startup__E */

extern void ti_sysbios_knl_Task_startup__E( void );

extern void ti_sysbios_knl_Task_startup__F( void );
extern void ti_sysbios_knl_Task_startup__R( void );

/* disable__E */

extern xdc_UInt ti_sysbios_knl_Task_disable__E( void );

extern xdc_UInt ti_sysbios_knl_Task_disable__F( void );
extern xdc_UInt ti_sysbios_knl_Task_disable__R( void );

/* enable__E */

extern void ti_sysbios_knl_Task_enable__E( void );

extern void ti_sysbios_knl_Task_enable__F( void );
extern void ti_sysbios_knl_Task_enable__R( void );

/* restore__E */

extern void ti_sysbios_knl_Task_restore__E( xdc_UInt key );

extern void ti_sysbios_knl_Task_restore__F( xdc_UInt key );
extern void ti_sysbios_knl_Task_restore__R( xdc_UInt key );

/* restoreHwi__E */

extern void ti_sysbios_knl_Task_restoreHwi__E( xdc_UInt key );

extern void ti_sysbios_knl_Task_restoreHwi__F( xdc_UInt key );
extern void ti_sysbios_knl_Task_restoreHwi__R( xdc_UInt key );

/* self__E */

extern ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_self__E( void );

extern ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_self__F( void );
extern ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_self__R( void );

/* checkStacks__E */

extern void ti_sysbios_knl_Task_checkStacks__E( ti_sysbios_knl_Task_Handle oldTask, ti_sysbios_knl_Task_Handle newTask );

extern void ti_sysbios_knl_Task_checkStacks__F( ti_sysbios_knl_Task_Handle oldTask, ti_sysbios_knl_Task_Handle newTask );
extern void ti_sysbios_knl_Task_checkStacks__R( ti_sysbios_knl_Task_Handle oldTask, ti_sysbios_knl_Task_Handle newTask );

/* exit__E */

extern void ti_sysbios_knl_Task_exit__E( void );

extern void ti_sysbios_knl_Task_exit__F( void );
extern void ti_sysbios_knl_Task_exit__R( void );

/* sleep__E */

extern void ti_sysbios_knl_Task_sleep__E( xdc_UInt nticks );

extern void ti_sysbios_knl_Task_sleep__F( xdc_UInt nticks );
extern void ti_sysbios_knl_Task_sleep__R( xdc_UInt nticks );

/* yield__E */

extern void ti_sysbios_knl_Task_yield__E( void );

extern void ti_sysbios_knl_Task_yield__F( void );
extern void ti_sysbios_knl_Task_yield__R( void );

/* getIdleTask__E */

extern ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_getIdleTask__E( void );

extern ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_getIdleTask__F( void );
extern ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_getIdleTask__R( void );

/* getArg0__E */

extern xdc_UArg ti_sysbios_knl_Task_getArg0__E( ti_sysbios_knl_Task_Handle __inst );

extern xdc_UArg ti_sysbios_knl_Task_getArg0__F( ti_sysbios_knl_Task_Object* __inst );
extern xdc_UArg ti_sysbios_knl_Task_getArg0__R( ti_sysbios_knl_Task_Handle __inst );

/* getArg1__E */

extern xdc_UArg ti_sysbios_knl_Task_getArg1__E( ti_sysbios_knl_Task_Handle __inst );

extern xdc_UArg ti_sysbios_knl_Task_getArg1__F( ti_sysbios_knl_Task_Object* __inst );
extern xdc_UArg ti_sysbios_knl_Task_getArg1__R( ti_sysbios_knl_Task_Handle __inst );

/* getEnv__E */

extern xdc_Ptr ti_sysbios_knl_Task_getEnv__E( ti_sysbios_knl_Task_Handle __inst );

extern xdc_Ptr ti_sysbios_knl_Task_getEnv__F( ti_sysbios_knl_Task_Object* __inst );
extern xdc_Ptr ti_sysbios_knl_Task_getEnv__R( ti_sysbios_knl_Task_Handle __inst );

/* getHookContext__E */

extern xdc_Ptr ti_sysbios_knl_Task_getHookContext__E( ti_sysbios_knl_Task_Handle __inst, xdc_Int id );

extern xdc_Ptr ti_sysbios_knl_Task_getHookContext__F( ti_sysbios_knl_Task_Object* __inst, xdc_Int id );
extern xdc_Ptr ti_sysbios_knl_Task_getHookContext__R( ti_sysbios_knl_Task_Handle __inst, xdc_Int id );

/* getPri__E */

extern xdc_Int ti_sysbios_knl_Task_getPri__E( ti_sysbios_knl_Task_Handle __inst );

extern xdc_Int ti_sysbios_knl_Task_getPri__F( ti_sysbios_knl_Task_Object* __inst );
extern xdc_Int ti_sysbios_knl_Task_getPri__R( ti_sysbios_knl_Task_Handle __inst );

/* setArg0__E */

extern void ti_sysbios_knl_Task_setArg0__E( ti_sysbios_knl_Task_Handle __inst, xdc_UArg arg );

extern void ti_sysbios_knl_Task_setArg0__F( ti_sysbios_knl_Task_Object* __inst, xdc_UArg arg );
extern void ti_sysbios_knl_Task_setArg0__R( ti_sysbios_knl_Task_Handle __inst, xdc_UArg arg );

/* setArg1__E */

extern void ti_sysbios_knl_Task_setArg1__E( ti_sysbios_knl_Task_Handle __inst, xdc_UArg arg );

extern void ti_sysbios_knl_Task_setArg1__F( ti_sysbios_knl_Task_Object* __inst, xdc_UArg arg );
extern void ti_sysbios_knl_Task_setArg1__R( ti_sysbios_knl_Task_Handle __inst, xdc_UArg arg );

/* setEnv__E */

extern void ti_sysbios_knl_Task_setEnv__E( ti_sysbios_knl_Task_Handle __inst, xdc_Ptr env );

extern void ti_sysbios_knl_Task_setEnv__F( ti_sysbios_knl_Task_Object* __inst, xdc_Ptr env );
extern void ti_sysbios_knl_Task_setEnv__R( ti_sysbios_knl_Task_Handle __inst, xdc_Ptr env );

/* setHookContext__E */

extern void ti_sysbios_knl_Task_setHookContext__E( ti_sysbios_knl_Task_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

extern void ti_sysbios_knl_Task_setHookContext__F( ti_sysbios_knl_Task_Object* __inst, xdc_Int id, xdc_Ptr hookContext );
extern void ti_sysbios_knl_Task_setHookContext__R( ti_sysbios_knl_Task_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

/* setPri__E */

extern xdc_UInt ti_sysbios_knl_Task_setPri__E( ti_sysbios_knl_Task_Handle __inst, xdc_Int newpri );

extern xdc_UInt ti_sysbios_knl_Task_setPri__F( ti_sysbios_knl_Task_Object* __inst, xdc_Int newpri );
extern xdc_UInt ti_sysbios_knl_Task_setPri__R( ti_sysbios_knl_Task_Handle __inst, xdc_Int newpri );

/* stat__E */

extern void ti_sysbios_knl_Task_stat__E( ti_sysbios_knl_Task_Handle __inst, ti_sysbios_knl_Task_Stat* statbuf );

extern void ti_sysbios_knl_Task_stat__F( ti_sysbios_knl_Task_Object* __inst, ti_sysbios_knl_Task_Stat* statbuf );
extern void ti_sysbios_knl_Task_stat__R( ti_sysbios_knl_Task_Handle __inst, ti_sysbios_knl_Task_Stat* statbuf );

/* getMode__E */

extern ti_sysbios_knl_Task_Mode ti_sysbios_knl_Task_getMode__E( ti_sysbios_knl_Task_Handle __inst );

extern ti_sysbios_knl_Task_Mode ti_sysbios_knl_Task_getMode__F( ti_sysbios_knl_Task_Object* __inst );
extern ti_sysbios_knl_Task_Mode ti_sysbios_knl_Task_getMode__R( ti_sysbios_knl_Task_Handle __inst );

/* block__E */

extern void ti_sysbios_knl_Task_block__E( ti_sysbios_knl_Task_Handle __inst );

extern void ti_sysbios_knl_Task_block__F( ti_sysbios_knl_Task_Object* __inst );
extern void ti_sysbios_knl_Task_block__R( ti_sysbios_knl_Task_Handle __inst );

/* unblock__E */

extern void ti_sysbios_knl_Task_unblock__E( ti_sysbios_knl_Task_Handle __inst );

extern void ti_sysbios_knl_Task_unblock__F( ti_sysbios_knl_Task_Object* __inst );
extern void ti_sysbios_knl_Task_unblock__R( ti_sysbios_knl_Task_Handle __inst );

/* blockI__E */

extern void ti_sysbios_knl_Task_blockI__E( ti_sysbios_knl_Task_Handle __inst );

extern void ti_sysbios_knl_Task_blockI__F( ti_sysbios_knl_Task_Object* __inst );
extern void ti_sysbios_knl_Task_blockI__R( ti_sysbios_knl_Task_Handle __inst );

/* unblockI__E */

extern void ti_sysbios_knl_Task_unblockI__E( ti_sysbios_knl_Task_Handle __inst, xdc_UInt hwiKey );

extern void ti_sysbios_knl_Task_unblockI__F( ti_sysbios_knl_Task_Object* __inst, xdc_UInt hwiKey );
extern void ti_sysbios_knl_Task_unblockI__R( ti_sysbios_knl_Task_Handle __inst, xdc_UInt hwiKey );

/* schedule__I */

extern void ti_sysbios_knl_Task_schedule__I( void );

/* enter__I */

extern void ti_sysbios_knl_Task_enter__I( void );

/* sleepTimeout__I */

extern void ti_sysbios_knl_Task_sleepTimeout__I( xdc_UArg arg );

/* postInit__I */

extern xdc_Int ti_sysbios_knl_Task_postInit__I( ti_sysbios_knl_Task_Object* swi, xdc_runtime_Error_Block* eb );

/* allBlockedFunction__I */

extern void ti_sysbios_knl_Task_allBlockedFunction__I( void );

/* deleteTerminatedTasksFunc__I */

extern void ti_sysbios_knl_Task_deleteTerminatedTasksFunc__I( void );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getArg0_{FxnT,fxnP} */
typedef xdc_UArg (*ti_sysbios_knl_Task_getArg0_FxnT)(void*);
static inline ti_sysbios_knl_Task_getArg0_FxnT ti_sysbios_knl_Task_getArg0_fxnP( void )
{
    return (ti_sysbios_knl_Task_getArg0_FxnT)ti_sysbios_knl_Task_getArg0__E; 
}

/* getArg1_{FxnT,fxnP} */
typedef xdc_UArg (*ti_sysbios_knl_Task_getArg1_FxnT)(void*);
static inline ti_sysbios_knl_Task_getArg1_FxnT ti_sysbios_knl_Task_getArg1_fxnP( void )
{
    return (ti_sysbios_knl_Task_getArg1_FxnT)ti_sysbios_knl_Task_getArg1__E; 
}

/* getEnv_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_knl_Task_getEnv_FxnT)(void*);
static inline ti_sysbios_knl_Task_getEnv_FxnT ti_sysbios_knl_Task_getEnv_fxnP( void )
{
    return (ti_sysbios_knl_Task_getEnv_FxnT)ti_sysbios_knl_Task_getEnv__E; 
}

/* getHookContext_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_knl_Task_getHookContext_FxnT)(void*, xdc_Int);
static inline ti_sysbios_knl_Task_getHookContext_FxnT ti_sysbios_knl_Task_getHookContext_fxnP( void )
{
    return (ti_sysbios_knl_Task_getHookContext_FxnT)ti_sysbios_knl_Task_getHookContext__E; 
}

/* getPri_{FxnT,fxnP} */
typedef xdc_Int (*ti_sysbios_knl_Task_getPri_FxnT)(void*);
static inline ti_sysbios_knl_Task_getPri_FxnT ti_sysbios_knl_Task_getPri_fxnP( void )
{
    return (ti_sysbios_knl_Task_getPri_FxnT)ti_sysbios_knl_Task_getPri__E; 
}

/* setArg0_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_setArg0_FxnT)(void*, xdc_UArg);
static inline ti_sysbios_knl_Task_setArg0_FxnT ti_sysbios_knl_Task_setArg0_fxnP( void )
{
    return (ti_sysbios_knl_Task_setArg0_FxnT)ti_sysbios_knl_Task_setArg0__E; 
}

/* setArg1_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_setArg1_FxnT)(void*, xdc_UArg);
static inline ti_sysbios_knl_Task_setArg1_FxnT ti_sysbios_knl_Task_setArg1_fxnP( void )
{
    return (ti_sysbios_knl_Task_setArg1_FxnT)ti_sysbios_knl_Task_setArg1__E; 
}

/* setEnv_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_setEnv_FxnT)(void*, xdc_Ptr);
static inline ti_sysbios_knl_Task_setEnv_FxnT ti_sysbios_knl_Task_setEnv_fxnP( void )
{
    return (ti_sysbios_knl_Task_setEnv_FxnT)ti_sysbios_knl_Task_setEnv__E; 
}

/* setHookContext_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_setHookContext_FxnT)(void*, xdc_Int, xdc_Ptr);
static inline ti_sysbios_knl_Task_setHookContext_FxnT ti_sysbios_knl_Task_setHookContext_fxnP( void )
{
    return (ti_sysbios_knl_Task_setHookContext_FxnT)ti_sysbios_knl_Task_setHookContext__E; 
}

/* setPri_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_knl_Task_setPri_FxnT)(void*, xdc_Int);
static inline ti_sysbios_knl_Task_setPri_FxnT ti_sysbios_knl_Task_setPri_fxnP( void )
{
    return (ti_sysbios_knl_Task_setPri_FxnT)ti_sysbios_knl_Task_setPri__E; 
}

/* stat_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_stat_FxnT)(void*, ti_sysbios_knl_Task_Stat*);
static inline ti_sysbios_knl_Task_stat_FxnT ti_sysbios_knl_Task_stat_fxnP( void )
{
    return (ti_sysbios_knl_Task_stat_FxnT)ti_sysbios_knl_Task_stat__E; 
}

/* getMode_{FxnT,fxnP} */
typedef ti_sysbios_knl_Task_Mode (*ti_sysbios_knl_Task_getMode_FxnT)(void*);
static inline ti_sysbios_knl_Task_getMode_FxnT ti_sysbios_knl_Task_getMode_fxnP( void )
{
    return (ti_sysbios_knl_Task_getMode_FxnT)ti_sysbios_knl_Task_getMode__E; 
}

/* block_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_block_FxnT)(void*);
static inline ti_sysbios_knl_Task_block_FxnT ti_sysbios_knl_Task_block_fxnP( void )
{
    return (ti_sysbios_knl_Task_block_FxnT)ti_sysbios_knl_Task_block__E; 
}

/* unblock_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_unblock_FxnT)(void*);
static inline ti_sysbios_knl_Task_unblock_FxnT ti_sysbios_knl_Task_unblock_fxnP( void )
{
    return (ti_sysbios_knl_Task_unblock_FxnT)ti_sysbios_knl_Task_unblock__E; 
}

/* blockI_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_blockI_FxnT)(void*);
static inline ti_sysbios_knl_Task_blockI_FxnT ti_sysbios_knl_Task_blockI_fxnP( void )
{
    return (ti_sysbios_knl_Task_blockI_FxnT)ti_sysbios_knl_Task_blockI__E; 
}

/* unblockI_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Task_unblockI_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Task_unblockI_FxnT ti_sysbios_knl_Task_unblockI_fxnP( void )
{
    return (ti_sysbios_knl_Task_unblockI_FxnT)ti_sysbios_knl_Task_unblockI__E; 
}


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Task_Module__id ti_sysbios_knl_Task_Module_id( void ) 
{
    return ti_sysbios_knl_Task_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_knl_Task_Module_hasMask( void ) 
{
    return ti_sysbios_knl_Task_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_knl_Task_Module_getMask( void ) 
{
    return ti_sysbios_knl_Task_Module__diagsMask__C != 0 ? *ti_sysbios_knl_Task_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_knl_Task_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_knl_Task_Module__diagsMask__C != 0) *ti_sysbios_knl_Task_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_knl_Task_Params_init( ti_sysbios_knl_Task_Params* prms ) 
{
    if (prms) {
        ti_sysbios_knl_Task_Params__init__S(prms, 0, sizeof(ti_sysbios_knl_Task_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_knl_Task_Params_copy( ti_sysbios_knl_Task_Params* dst, const ti_sysbios_knl_Task_Params* src ) 
{
    if (dst) {
        ti_sysbios_knl_Task_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_knl_Task_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_Object_get( ti_sysbios_knl_Task_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_knl_Task_Handle)ti_sysbios_knl_Task_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_Object_first( void )
{
    return (ti_sysbios_knl_Task_Handle)ti_sysbios_knl_Task_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_Object_next( ti_sysbios_knl_Task_Object* obj )
{
    return (ti_sysbios_knl_Task_Handle)ti_sysbios_knl_Task_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_knl_Task_Handle_label( ti_sysbios_knl_Task_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_knl_Task_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_knl_Task_Handle_name( ti_sysbios_knl_Task_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_knl_Task_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_create( ti_sysbios_knl_Task_FuncPtr fxn, const ti_sysbios_knl_Task_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_knl_Task_Args__create __args;
    __args.fxn = fxn;
    return (ti_sysbios_knl_Task_Handle)ti_sysbios_knl_Task_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Task_Params), __eb);
}

/* construct */
static inline void ti_sysbios_knl_Task_construct( ti_sysbios_knl_Task_Struct* __obj, ti_sysbios_knl_Task_FuncPtr fxn, const ti_sysbios_knl_Task_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_knl_Task_Args__create __args;
    __args.fxn = fxn;
    ti_sysbios_knl_Task_Object__create__S(__obj, sizeof (ti_sysbios_knl_Task_Struct), &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Task_Params), __eb);
}

/* delete */
static inline void ti_sysbios_knl_Task_delete( ti_sysbios_knl_Task_Handle* instp )
{
    ti_sysbios_knl_Task_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_knl_Task_destruct( ti_sysbios_knl_Task_Struct* obj )
{
    ti_sysbios_knl_Task_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_knl_Task_Handle ti_sysbios_knl_Task_handle( ti_sysbios_knl_Task_Struct* str )
{
    return (ti_sysbios_knl_Task_Handle)str;
}

/* struct */
static inline ti_sysbios_knl_Task_Struct* ti_sysbios_knl_Task_struct( ti_sysbios_knl_Task_Handle inst )
{
    return (ti_sysbios_knl_Task_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  ======== Task_selfMacro ========
 */

/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:35; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */





/*
 * ======== STATE STRUCTURES ========
 */



/* Module_State */
struct ti_sysbios_knl_Task_Module_State {
    xdc_Bool locked;
    volatile xdc_UInt curSet;
    xdc_Bool workFlag;
    xdc_UInt vitalTasks;
    ti_sysbios_knl_Task_Handle curTask;
    ti_sysbios_knl_Queue_Handle curQ;
    __TA_ti_sysbios_knl_Task_Module_State__readyQ readyQ;
    ti_sysbios_knl_Task_Handle idleTask;
    __TA_ti_sysbios_knl_Task_Module_State__constructedTasks constructedTasks;
    char __dummy;
};

/* Module__state__V */
extern struct ti_sysbios_knl_Task_Module_State__ ti_sysbios_knl_Task_Module__state__V;

/* Object */
struct ti_sysbios_knl_Task_Object {
    ti_sysbios_knl_Queue_Elem qElem;
    volatile xdc_Int priority;
    xdc_UInt mask;
    xdc_Ptr context;
    ti_sysbios_knl_Task_Mode mode;
    ti_sysbios_knl_Task_PendElem* pendElem;
    xdc_SizeT stackSize;
    __TA_ti_sysbios_knl_Task_Instance_State__stack stack;
    xdc_runtime_IHeap_Handle stackHeap;
    ti_sysbios_knl_Task_FuncPtr fxn;
    xdc_UArg arg0;
    xdc_UArg arg1;
    xdc_Ptr env;
    __TA_ti_sysbios_knl_Task_Instance_State__hookEnv hookEnv;
    xdc_Bool vitalTaskFlag;
    ti_sysbios_knl_Queue_Handle readyQ;
};

/* Module_State_inactiveQ */
extern far const xdc_SizeT ti_sysbios_knl_Task_Module_State_inactiveQ__O;
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Task_Module_State_inactiveQ()
{
    return (ti_sysbios_knl_Queue_Handle)(((char*)&ti_sysbios_knl_Task_Module__state__V) + ti_sysbios_knl_Task_Module_State_inactiveQ__O);
}

/* Module_State_terminatedQ */
extern far const xdc_SizeT ti_sysbios_knl_Task_Module_State_terminatedQ__O;
static inline ti_sysbios_knl_Queue_Handle ti_sysbios_knl_Task_Module_State_terminatedQ()
{
    return (ti_sysbios_knl_Queue_Handle)(((char*)&ti_sysbios_knl_Task_Module__state__V) + ti_sysbios_knl_Task_Module_State_terminatedQ__O);
}




/*
 * ======== PREFIX ALIASES ========
 */



/* module prefix */

/* proxies */
/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     MODULE-WIDE CONFIGS
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
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
 * ======== PREFIX ALIASES ========
 */



/* module prefix */


/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:34; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

//D:\TInew\bios_6_33_04_39\packages#include <Task.h>
/*****************************************************************************/
/* string.h   v7.3.4                                                         */
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



//#include <sys.h>
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
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_ISystemSupport_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    void (*abort)(xdc_String);
    void (*exit)(xdc_Int);
    void (*flush)(void);
    void (*putch)(xdc_Char);
    xdc_Bool (*ready)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base xdc_runtime_ISystemSupport_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_ISystemSupport_Module_id( xdc_runtime_ISystemSupport_Module mod )
{
    return mod->__sysp->__mid;
}

/* abort */
static inline void xdc_runtime_ISystemSupport_abort( xdc_runtime_ISystemSupport_Module __inst, xdc_String str )
{
    __inst->abort(str);
}

/* exit */
static inline void xdc_runtime_ISystemSupport_exit( xdc_runtime_ISystemSupport_Module __inst, xdc_Int stat )
{
    __inst->exit(stat);
}

/* flush */
static inline void xdc_runtime_ISystemSupport_flush( xdc_runtime_ISystemSupport_Module __inst )
{
    __inst->flush();
}

/* putch */
static inline void xdc_runtime_ISystemSupport_putch( xdc_runtime_ISystemSupport_Module __inst, xdc_Char ch )
{
    __inst->putch(ch);
}

/* ready */
static inline xdc_Bool xdc_runtime_ISystemSupport_ready( xdc_runtime_ISystemSupport_Module __inst )
{
    return __inst->ready();
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* abort_{FxnT,fxnP} */
typedef void (*xdc_runtime_ISystemSupport_abort_FxnT)(xdc_String);
static inline xdc_runtime_ISystemSupport_abort_FxnT xdc_runtime_ISystemSupport_abort_fxnP( xdc_runtime_ISystemSupport_Module __inst )
{
    return (xdc_runtime_ISystemSupport_abort_FxnT)__inst->abort;
}

/* exit_{FxnT,fxnP} */
typedef void (*xdc_runtime_ISystemSupport_exit_FxnT)(xdc_Int);
static inline xdc_runtime_ISystemSupport_exit_FxnT xdc_runtime_ISystemSupport_exit_fxnP( xdc_runtime_ISystemSupport_Module __inst )
{
    return (xdc_runtime_ISystemSupport_exit_FxnT)__inst->exit;
}

/* flush_{FxnT,fxnP} */
typedef void (*xdc_runtime_ISystemSupport_flush_FxnT)(void);
static inline xdc_runtime_ISystemSupport_flush_FxnT xdc_runtime_ISystemSupport_flush_fxnP( xdc_runtime_ISystemSupport_Module __inst )
{
    return (xdc_runtime_ISystemSupport_flush_FxnT)__inst->flush;
}

/* putch_{FxnT,fxnP} */
typedef void (*xdc_runtime_ISystemSupport_putch_FxnT)(xdc_Char);
static inline xdc_runtime_ISystemSupport_putch_FxnT xdc_runtime_ISystemSupport_putch_fxnP( xdc_runtime_ISystemSupport_Module __inst )
{
    return (xdc_runtime_ISystemSupport_putch_FxnT)__inst->putch;
}

/* ready_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_ISystemSupport_ready_FxnT)(void);
static inline xdc_runtime_ISystemSupport_ready_FxnT xdc_runtime_ISystemSupport_ready_fxnP( xdc_runtime_ISystemSupport_Module __inst )
{
    return (xdc_runtime_ISystemSupport_ready_FxnT)__inst->ready;
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
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:32; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
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
 *     MODULE-WIDE CONFIGS
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
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
typedef xdc_Bits32 CT__xdc_runtime_System_SupportProxy_Module__diagsEnabled;
extern far const CT__xdc_runtime_System_SupportProxy_Module__diagsEnabled xdc_runtime_System_SupportProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_System_SupportProxy_Module__diagsIncluded;
extern far const CT__xdc_runtime_System_SupportProxy_Module__diagsIncluded xdc_runtime_System_SupportProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_System_SupportProxy_Module__diagsMask;
extern far const CT__xdc_runtime_System_SupportProxy_Module__diagsMask xdc_runtime_System_SupportProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_System_SupportProxy_Module__gateObj;
extern far const CT__xdc_runtime_System_SupportProxy_Module__gateObj xdc_runtime_System_SupportProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_System_SupportProxy_Module__gatePrms;
extern far const CT__xdc_runtime_System_SupportProxy_Module__gatePrms xdc_runtime_System_SupportProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_System_SupportProxy_Module__id;
extern far const CT__xdc_runtime_System_SupportProxy_Module__id xdc_runtime_System_SupportProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_System_SupportProxy_Module__loggerDefined;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerDefined xdc_runtime_System_SupportProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_System_SupportProxy_Module__loggerObj;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerObj xdc_runtime_System_SupportProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_System_SupportProxy_Module__loggerFxn0;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerFxn0 xdc_runtime_System_SupportProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_System_SupportProxy_Module__loggerFxn1;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerFxn1 xdc_runtime_System_SupportProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_System_SupportProxy_Module__loggerFxn2;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerFxn2 xdc_runtime_System_SupportProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_System_SupportProxy_Module__loggerFxn4;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerFxn4 xdc_runtime_System_SupportProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_System_SupportProxy_Module__loggerFxn8;
extern far const CT__xdc_runtime_System_SupportProxy_Module__loggerFxn8 xdc_runtime_System_SupportProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_System_SupportProxy_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_System_SupportProxy_Module__startupDoneFxn xdc_runtime_System_SupportProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_System_SupportProxy_Object__count;
extern far const CT__xdc_runtime_System_SupportProxy_Object__count xdc_runtime_System_SupportProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_System_SupportProxy_Object__heap;
extern far const CT__xdc_runtime_System_SupportProxy_Object__heap xdc_runtime_System_SupportProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_System_SupportProxy_Object__sizeof;
extern far const CT__xdc_runtime_System_SupportProxy_Object__sizeof xdc_runtime_System_SupportProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_System_SupportProxy_Object__table;
extern far const CT__xdc_runtime_System_SupportProxy_Object__table xdc_runtime_System_SupportProxy_Object__table__C;


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_System_SupportProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    void (*abort)(xdc_String);
    void (*exit)(xdc_Int);
    void (*flush)(void);
    void (*putch)(xdc_Char);
    xdc_Bool (*ready)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const xdc_runtime_System_SupportProxy_Fxns__ xdc_runtime_System_SupportProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* xdc_runtime_System_SupportProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_System_SupportProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr xdc_runtime_System_SupportProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void xdc_runtime_System_SupportProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void xdc_runtime_System_SupportProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr xdc_runtime_System_SupportProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr xdc_runtime_System_SupportProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr xdc_runtime_System_SupportProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void xdc_runtime_System_SupportProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool xdc_runtime_System_SupportProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr xdc_runtime_System_SupportProxy_Proxy__delegate__S( void );

/* abort__E */

extern void xdc_runtime_System_SupportProxy_abort__E( xdc_String str );

extern void xdc_runtime_System_SupportProxy_abort__R( xdc_String str );

/* exit__E */

extern void xdc_runtime_System_SupportProxy_exit__E( xdc_Int stat );

extern void xdc_runtime_System_SupportProxy_exit__R( xdc_Int stat );

/* flush__E */

extern void xdc_runtime_System_SupportProxy_flush__E( void );

extern void xdc_runtime_System_SupportProxy_flush__R( void );

/* putch__E */

extern void xdc_runtime_System_SupportProxy_putch__E( xdc_Char ch );

extern void xdc_runtime_System_SupportProxy_putch__R( xdc_Char ch );

/* ready__E */

extern xdc_Bool xdc_runtime_System_SupportProxy_ready__E( void );

extern xdc_Bool xdc_runtime_System_SupportProxy_ready__R( void );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_ISystemSupport_Module xdc_runtime_System_SupportProxy_Module_upCast( void )
{
    return (xdc_runtime_ISystemSupport_Module)xdc_runtime_System_SupportProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_ISystemSupport */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_System_SupportProxy_Module__id xdc_runtime_System_SupportProxy_Module_id( void ) 
{
    return xdc_runtime_System_SupportProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
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
typedef xdc_Bits32 CT__xdc_runtime_System_Module_GateProxy_Module__diagsEnabled;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__diagsEnabled xdc_runtime_System_Module_GateProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_System_Module_GateProxy_Module__diagsIncluded;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__diagsIncluded xdc_runtime_System_Module_GateProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_System_Module_GateProxy_Module__diagsMask;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__diagsMask xdc_runtime_System_Module_GateProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_System_Module_GateProxy_Module__gateObj;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__gateObj xdc_runtime_System_Module_GateProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_System_Module_GateProxy_Module__gatePrms;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__gatePrms xdc_runtime_System_Module_GateProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_System_Module_GateProxy_Module__id;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__id xdc_runtime_System_Module_GateProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_System_Module_GateProxy_Module__loggerDefined;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerDefined xdc_runtime_System_Module_GateProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_System_Module_GateProxy_Module__loggerObj;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerObj xdc_runtime_System_Module_GateProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn0;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn0 xdc_runtime_System_Module_GateProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn1;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn1 xdc_runtime_System_Module_GateProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn2;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn2 xdc_runtime_System_Module_GateProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn4;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn4 xdc_runtime_System_Module_GateProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn8;
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__loggerFxn8 xdc_runtime_System_Module_GateProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_System_Module_GateProxy_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_System_Module_GateProxy_Module__startupDoneFxn xdc_runtime_System_Module_GateProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_System_Module_GateProxy_Object__count;
extern far const CT__xdc_runtime_System_Module_GateProxy_Object__count xdc_runtime_System_Module_GateProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_System_Module_GateProxy_Object__heap;
extern far const CT__xdc_runtime_System_Module_GateProxy_Object__heap xdc_runtime_System_Module_GateProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_System_Module_GateProxy_Object__sizeof;
extern far const CT__xdc_runtime_System_Module_GateProxy_Object__sizeof xdc_runtime_System_Module_GateProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_System_Module_GateProxy_Object__table;
extern far const CT__xdc_runtime_System_Module_GateProxy_Object__table xdc_runtime_System_Module_GateProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_System_Module_GateProxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_System_Module_GateProxy_Struct {
    const xdc_runtime_System_Module_GateProxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_System_Module_GateProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(xdc_runtime_System_Module_GateProxy_Handle);
    void (*leave)(xdc_runtime_System_Module_GateProxy_Handle, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const xdc_runtime_System_Module_GateProxy_Fxns__ xdc_runtime_System_Module_GateProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* xdc_runtime_System_Module_GateProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_System_Module_GateProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr xdc_runtime_System_Module_GateProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void xdc_runtime_System_Module_GateProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void xdc_runtime_System_Module_GateProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr xdc_runtime_System_Module_GateProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr xdc_runtime_System_Module_GateProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr xdc_runtime_System_Module_GateProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void xdc_runtime_System_Module_GateProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool xdc_runtime_System_Module_GateProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr xdc_runtime_System_Module_GateProxy_Proxy__delegate__S( void );

/* query__E */

extern xdc_Bool xdc_runtime_System_Module_GateProxy_query__E( xdc_Int qual );

extern xdc_Bool xdc_runtime_System_Module_GateProxy_query__R( xdc_Int qual );

/* enter__E */

extern xdc_IArg xdc_runtime_System_Module_GateProxy_enter__E( xdc_runtime_System_Module_GateProxy_Handle __inst );

extern xdc_IArg xdc_runtime_System_Module_GateProxy_enter__R( xdc_runtime_System_Module_GateProxy_Handle __inst );

/* leave__E */

extern void xdc_runtime_System_Module_GateProxy_leave__E( xdc_runtime_System_Module_GateProxy_Handle __inst, xdc_IArg key );

extern void xdc_runtime_System_Module_GateProxy_leave__R( xdc_runtime_System_Module_GateProxy_Handle __inst, xdc_IArg key );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* enter_{FxnT,fxnP} */
typedef xdc_IArg (*xdc_runtime_System_Module_GateProxy_enter_FxnT)(void*);
static inline xdc_runtime_System_Module_GateProxy_enter_FxnT xdc_runtime_System_Module_GateProxy_enter_fxnP( void )
{
    return (xdc_runtime_System_Module_GateProxy_enter_FxnT)xdc_runtime_System_Module_GateProxy_enter__E; 
}

/* leave_{FxnT,fxnP} */
typedef void (*xdc_runtime_System_Module_GateProxy_leave_FxnT)(void*, xdc_IArg);
static inline xdc_runtime_System_Module_GateProxy_leave_FxnT xdc_runtime_System_Module_GateProxy_leave_fxnP( void )
{
    return (xdc_runtime_System_Module_GateProxy_leave_FxnT)xdc_runtime_System_Module_GateProxy_leave__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IGateProvider_Module xdc_runtime_System_Module_GateProxy_Module_upCast( void )
{
    return (xdc_runtime_IGateProvider_Module)xdc_runtime_System_Module_GateProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */

/* Handle_upCast */
static inline xdc_runtime_IGateProvider_Handle xdc_runtime_System_Module_GateProxy_Handle_upCast( xdc_runtime_System_Module_GateProxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */

/* Handle_downCast */
static inline xdc_runtime_System_Module_GateProxy_Handle xdc_runtime_System_Module_GateProxy_Handle_downCast( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
if (xdc_runtime_System_Module_GateProxy_Proxy__abstract__S()) return (xdc_runtime_System_Module_GateProxy_Handle)i;
    return (void*)i2->__fxns == (void*)xdc_runtime_System_Module_GateProxy_Proxy__delegate__S() ? (xdc_runtime_System_Module_GateProxy_Handle)i : 0;
}

/* Handle_from_xdc_runtime_IGateProvider */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_System_Module_GateProxy_Module__id xdc_runtime_System_Module_GateProxy_Module_id( void ) 
{
    return xdc_runtime_System_Module_GateProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */

/* Params_init */
static inline void xdc_runtime_System_Module_GateProxy_Params_init( xdc_runtime_System_Module_GateProxy_Params* prms ) 
{
    if (prms) {
        xdc_runtime_System_Module_GateProxy_Params__init__S(prms, 0, sizeof(xdc_runtime_System_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_System_Module_GateProxy_Params_copy( xdc_runtime_System_Module_GateProxy_Params* dst, const xdc_runtime_System_Module_GateProxy_Params* src ) 
{
    if (dst) {
        xdc_runtime_System_Module_GateProxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(xdc_runtime_System_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline xdc_runtime_System_Module_GateProxy_Handle xdc_runtime_System_Module_GateProxy_create( const xdc_runtime_System_Module_GateProxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (xdc_runtime_System_Module_GateProxy_Handle)xdc_runtime_System_Module_GateProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_System_Module_GateProxy_Params), __eb);
}

/* delete */
static inline void xdc_runtime_System_Module_GateProxy_delete( xdc_runtime_System_Module_GateProxy_Handle* instp )
{
    xdc_runtime_System_Module_GateProxy_Object__delete__S(instp);
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

/* AtexitHandler */
typedef void (*xdc_runtime_System_AtexitHandler)(xdc_Int);

/* STATUS_UNKNOWN */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* ParseData */
struct xdc_runtime_System_ParseData {
    xdc_Int width;
    xdc_Bool lFlag;
    xdc_Bool lJust;
    xdc_Int precis;
    xdc_Int len;
    xdc_Int zpad;
    xdc_Char* end;
    xdc_Bool aFlag;
    xdc_Char* ptr;
};

/* ExtendFxn */
typedef xdc_Int (*xdc_runtime_System_ExtendFxn)(xdc_Char**, xdc_Char**, xdc_VaList*, xdc_runtime_System_ParseData*);

/* Module_State */
typedef xdc_runtime_System_AtexitHandler __T1_xdc_runtime_System_Module_State__atexitHandlers;
typedef xdc_runtime_System_AtexitHandler *__ARRAY1_xdc_runtime_System_Module_State__atexitHandlers;
typedef __ARRAY1_xdc_runtime_System_Module_State__atexitHandlers __TA_xdc_runtime_System_Module_State__atexitHandlers;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_System_Module__diagsEnabled;
extern far const CT__xdc_runtime_System_Module__diagsEnabled xdc_runtime_System_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_System_Module__diagsIncluded;
extern far const CT__xdc_runtime_System_Module__diagsIncluded xdc_runtime_System_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__xdc_runtime_System_Module__diagsMask;
extern far const CT__xdc_runtime_System_Module__diagsMask xdc_runtime_System_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_System_Module__gateObj;
extern far const CT__xdc_runtime_System_Module__gateObj xdc_runtime_System_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_System_Module__gatePrms;
extern far const CT__xdc_runtime_System_Module__gatePrms xdc_runtime_System_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_System_Module__id;
extern far const CT__xdc_runtime_System_Module__id xdc_runtime_System_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_System_Module__loggerDefined;
extern far const CT__xdc_runtime_System_Module__loggerDefined xdc_runtime_System_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_System_Module__loggerObj;
extern far const CT__xdc_runtime_System_Module__loggerObj xdc_runtime_System_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_System_Module__loggerFxn0;
extern far const CT__xdc_runtime_System_Module__loggerFxn0 xdc_runtime_System_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_System_Module__loggerFxn1;
extern far const CT__xdc_runtime_System_Module__loggerFxn1 xdc_runtime_System_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_System_Module__loggerFxn2;
extern far const CT__xdc_runtime_System_Module__loggerFxn2 xdc_runtime_System_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_System_Module__loggerFxn4;
extern far const CT__xdc_runtime_System_Module__loggerFxn4 xdc_runtime_System_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_System_Module__loggerFxn8;
extern far const CT__xdc_runtime_System_Module__loggerFxn8 xdc_runtime_System_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__xdc_runtime_System_Module__startupDoneFxn)(void);
extern far const CT__xdc_runtime_System_Module__startupDoneFxn xdc_runtime_System_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__xdc_runtime_System_Object__count;
extern far const CT__xdc_runtime_System_Object__count xdc_runtime_System_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_System_Object__heap;
extern far const CT__xdc_runtime_System_Object__heap xdc_runtime_System_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_System_Object__sizeof;
extern far const CT__xdc_runtime_System_Object__sizeof xdc_runtime_System_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_System_Object__table;
extern far const CT__xdc_runtime_System_Object__table xdc_runtime_System_Object__table__C;

/* A_cannotFitIntoArg */
typedef xdc_runtime_Assert_Id CT__xdc_runtime_System_A_cannotFitIntoArg;
extern far const CT__xdc_runtime_System_A_cannotFitIntoArg xdc_runtime_System_A_cannotFitIntoArg__C;

/* maxAtexitHandlers */
typedef xdc_Int CT__xdc_runtime_System_maxAtexitHandlers;
extern far const CT__xdc_runtime_System_maxAtexitHandlers xdc_runtime_System_maxAtexitHandlers__C;

/* extendFxn */
typedef xdc_runtime_System_ExtendFxn CT__xdc_runtime_System_extendFxn;
extern far const CT__xdc_runtime_System_extendFxn xdc_runtime_System_extendFxn__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int xdc_runtime_System_Module_startup__E( xdc_Int state );

extern xdc_Int xdc_runtime_System_Module_startup__F( xdc_Int state );

extern xdc_Int xdc_runtime_System_Module_startup__R( xdc_Int state );

/* Module__startupDone__S */

extern xdc_Bool xdc_runtime_System_Module__startupDone__S( void );

/* abort__E */

extern void xdc_runtime_System_abort__E( xdc_String str );

extern void xdc_runtime_System_abort__F( xdc_String str );
extern void xdc_runtime_System_abort__R( xdc_String str );

/* atexit__E */

extern xdc_Bool xdc_runtime_System_atexit__E( xdc_runtime_System_AtexitHandler handler );

extern xdc_Bool xdc_runtime_System_atexit__F( xdc_runtime_System_AtexitHandler handler );
extern xdc_Bool xdc_runtime_System_atexit__R( xdc_runtime_System_AtexitHandler handler );

/* exit__E */

extern void xdc_runtime_System_exit__E( xdc_Int stat );

extern void xdc_runtime_System_exit__F( xdc_Int stat );
extern void xdc_runtime_System_exit__R( xdc_Int stat );

/* putch__E */

extern void xdc_runtime_System_putch__E( xdc_Char ch );

extern void xdc_runtime_System_putch__F( xdc_Char ch );
extern void xdc_runtime_System_putch__R( xdc_Char ch );

/* flush__E */

extern void xdc_runtime_System_flush__E( void );

extern void xdc_runtime_System_flush__F( void );
extern void xdc_runtime_System_flush__R( void );

/* printf__E */

extern xdc_Int xdc_runtime_System_printf__E( xdc_String fmt, ... );

extern xdc_Int xdc_runtime_System_printf_va__E( xdc_String fmt, va_list _va );

extern xdc_Int xdc_runtime_System_printf_va__F( xdc_String fmt, va_list _va );
extern xdc_Int xdc_runtime_System_printf_va__R( xdc_String fmt, va_list _va );

/* aprintf__E */

extern xdc_Int xdc_runtime_System_aprintf__E( xdc_String fmt, ... );

extern xdc_Int xdc_runtime_System_aprintf_va__E( xdc_String fmt, va_list _va );

extern xdc_Int xdc_runtime_System_aprintf_va__F( xdc_String fmt, va_list _va );
extern xdc_Int xdc_runtime_System_aprintf_va__R( xdc_String fmt, va_list _va );

/* sprintf__E */

extern xdc_Int xdc_runtime_System_sprintf__E( xdc_Char buf[], xdc_String fmt, ... );

extern xdc_Int xdc_runtime_System_sprintf_va__E( xdc_Char buf[], xdc_String fmt, va_list _va );

extern xdc_Int xdc_runtime_System_sprintf_va__F( xdc_Char buf[], xdc_String fmt, va_list _va );
extern xdc_Int xdc_runtime_System_sprintf_va__R( xdc_Char buf[], xdc_String fmt, va_list _va );

/* asprintf__E */

extern xdc_Int xdc_runtime_System_asprintf__E( xdc_Char buf[], xdc_String fmt, ... );

extern xdc_Int xdc_runtime_System_asprintf_va__E( xdc_Char buf[], xdc_String fmt, va_list _va );

extern xdc_Int xdc_runtime_System_asprintf_va__F( xdc_Char buf[], xdc_String fmt, va_list _va );
extern xdc_Int xdc_runtime_System_asprintf_va__R( xdc_Char buf[], xdc_String fmt, va_list _va );

/* vprintf__E */

extern xdc_Int xdc_runtime_System_vprintf__E( xdc_String fmt, xdc_VaList va );

extern xdc_Int xdc_runtime_System_vprintf__F( xdc_String fmt, xdc_VaList va );
extern xdc_Int xdc_runtime_System_vprintf__R( xdc_String fmt, xdc_VaList va );

/* avprintf__E */

extern xdc_Int xdc_runtime_System_avprintf__E( xdc_String fmt, xdc_VaList va );

extern xdc_Int xdc_runtime_System_avprintf__F( xdc_String fmt, xdc_VaList va );
extern xdc_Int xdc_runtime_System_avprintf__R( xdc_String fmt, xdc_VaList va );

/* vsprintf__E */

extern xdc_Int xdc_runtime_System_vsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va );

extern xdc_Int xdc_runtime_System_vsprintf__F( xdc_Char buf[], xdc_String fmt, xdc_VaList va );
extern xdc_Int xdc_runtime_System_vsprintf__R( xdc_Char buf[], xdc_String fmt, xdc_VaList va );

/* avsprintf__E */

extern xdc_Int xdc_runtime_System_avsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va );

extern xdc_Int xdc_runtime_System_avsprintf__F( xdc_Char buf[], xdc_String fmt, xdc_VaList va );
extern xdc_Int xdc_runtime_System_avsprintf__R( xdc_Char buf[], xdc_String fmt, xdc_VaList va );

/* printfExtend__I */

extern xdc_Int xdc_runtime_System_printfExtend__I( xdc_Char** bufp, xdc_Char** fmt, xdc_VaList* va, xdc_runtime_System_ParseData* parse );

/* doPrint__I */

extern xdc_Int xdc_runtime_System_doPrint__I( xdc_Char buf[], xdc_String fmt, xdc_VaList* pva, xdc_Bool aFlag );

/* formatNum__I */

extern xdc_Char* xdc_runtime_System_formatNum__I( xdc_Char* ptr, xdc_UInt32 n, xdc_Int zpad, xdc_Int base );

/* lastFxn__I */

extern void xdc_runtime_System_lastFxn__I( void );

/* putchar__I */

extern void xdc_runtime_System_putchar__I( xdc_Char** bufp, xdc_Char ch );

/* rtsExit__I */

extern void xdc_runtime_System_rtsExit__I( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__xdc_runtime_System_Module__id xdc_runtime_System_Module_id( void ) 
{
    return xdc_runtime_System_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_System_Module_hasMask( void ) 
{
    return xdc_runtime_System_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_System_Module_getMask( void ) 
{
    return xdc_runtime_System_Module__diagsMask__C != 0 ? *xdc_runtime_System_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void xdc_runtime_System_Module_setMask( xdc_Bits16 mask ) 
{
    if (xdc_runtime_System_Module__diagsMask__C != 0) *xdc_runtime_System_Module__diagsMask__C = mask;
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



/* module prefix */

/* proxies */
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
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
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
 * ======== PREFIX ALIASES ========
 */



/* module prefix */


/* proxies */
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
 * ======== PREFIX ALIASES ========
 */



/* module prefix */


/*
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:34; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

//#include <sem.h>
/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:32; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:32; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:34; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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

/* Id_00 */

/* Id_01 */

/* Id_02 */

/* Id_03 */

/* Id_04 */

/* Id_05 */

/* Id_06 */

/* Id_07 */

/* Id_08 */

/* Id_09 */

/* Id_10 */

/* Id_11 */

/* Id_12 */

/* Id_13 */

/* Id_14 */

/* Id_15 */

/* Id_16 */

/* Id_17 */

/* Id_18 */

/* Id_19 */

/* Id_20 */

/* Id_21 */

/* Id_22 */

/* Id_23 */

/* Id_24 */

/* Id_25 */

/* Id_26 */

/* Id_27 */

/* Id_28 */

/* Id_29 */

/* Id_30 */

/* Id_31 */

/* Id_NONE */


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* PendState */
enum ti_sysbios_knl_Event_PendState {
    ti_sysbios_knl_Event_PendState_TIMEOUT = 0,
    ti_sysbios_knl_Event_PendState_POSTED = 1,
    ti_sysbios_knl_Event_PendState_CLOCK_WAIT = 2,
    ti_sysbios_knl_Event_PendState_WAIT_FOREVER = 3
};
typedef enum ti_sysbios_knl_Event_PendState ti_sysbios_knl_Event_PendState;

/* PendElem */
struct ti_sysbios_knl_Event_PendElem {
    ti_sysbios_knl_Task_PendElem tpElem;
    ti_sysbios_knl_Event_PendState pendState;
    xdc_UInt matchingEvents;
    xdc_UInt andMask;
    xdc_UInt orMask;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Event_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Event_Module__diagsEnabled ti_sysbios_knl_Event_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Event_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Event_Module__diagsIncluded ti_sysbios_knl_Event_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Event_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Event_Module__diagsMask ti_sysbios_knl_Event_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Event_Module__gateObj;
extern far const CT__ti_sysbios_knl_Event_Module__gateObj ti_sysbios_knl_Event_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Event_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Event_Module__gatePrms ti_sysbios_knl_Event_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Event_Module__id;
extern far const CT__ti_sysbios_knl_Event_Module__id ti_sysbios_knl_Event_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Event_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Event_Module__loggerDefined ti_sysbios_knl_Event_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Event_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Event_Module__loggerObj ti_sysbios_knl_Event_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Event_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Event_Module__loggerFxn0 ti_sysbios_knl_Event_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Event_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Event_Module__loggerFxn1 ti_sysbios_knl_Event_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Event_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Event_Module__loggerFxn2 ti_sysbios_knl_Event_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Event_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Event_Module__loggerFxn4 ti_sysbios_knl_Event_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Event_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Event_Module__loggerFxn8 ti_sysbios_knl_Event_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Event_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Event_Module__startupDoneFxn ti_sysbios_knl_Event_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Event_Object__count;
extern far const CT__ti_sysbios_knl_Event_Object__count ti_sysbios_knl_Event_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Event_Object__heap;
extern far const CT__ti_sysbios_knl_Event_Object__heap ti_sysbios_knl_Event_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Event_Object__sizeof;
extern far const CT__ti_sysbios_knl_Event_Object__sizeof ti_sysbios_knl_Event_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Event_Object__table;
extern far const CT__ti_sysbios_knl_Event_Object__table ti_sysbios_knl_Event_Object__table__C;

/* LM_post */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Event_LM_post;
extern far const CT__ti_sysbios_knl_Event_LM_post ti_sysbios_knl_Event_LM_post__C;

/* LM_pend */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Event_LM_pend;
extern far const CT__ti_sysbios_knl_Event_LM_pend ti_sysbios_knl_Event_LM_pend__C;

/* A_nullEventMasks */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Event_A_nullEventMasks;
extern far const CT__ti_sysbios_knl_Event_A_nullEventMasks ti_sysbios_knl_Event_A_nullEventMasks__C;

/* A_nullEventId */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Event_A_nullEventId;
extern far const CT__ti_sysbios_knl_Event_A_nullEventId ti_sysbios_knl_Event_A_nullEventId__C;

/* A_eventInUse */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Event_A_eventInUse;
extern far const CT__ti_sysbios_knl_Event_A_eventInUse ti_sysbios_knl_Event_A_eventInUse__C;

/* A_badContext */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Event_A_badContext;
extern far const CT__ti_sysbios_knl_Event_A_badContext ti_sysbios_knl_Event_A_badContext__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_knl_Event_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_knl_Event_Struct {
    volatile xdc_UInt __f0;
    ti_sysbios_knl_Queue_Struct __f1;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Instance_init__F */

extern void ti_sysbios_knl_Event_Instance_init__F( ti_sysbios_knl_Event_Object*, const ti_sysbios_knl_Event_Params* );

/* Instance_init__R */

extern void ti_sysbios_knl_Event_Instance_init__R( ti_sysbios_knl_Event_Object*, const ti_sysbios_knl_Event_Params* );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Event_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Event_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Event_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Event_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Event_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Event_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Event_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Event_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Event_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* pend__E */

extern xdc_UInt ti_sysbios_knl_Event_pend__E( ti_sysbios_knl_Event_Handle __inst, xdc_UInt andMask, xdc_UInt orMask, xdc_UInt timeout );

extern xdc_UInt ti_sysbios_knl_Event_pend__F( ti_sysbios_knl_Event_Object* __inst, xdc_UInt andMask, xdc_UInt orMask, xdc_UInt timeout );
extern xdc_UInt ti_sysbios_knl_Event_pend__R( ti_sysbios_knl_Event_Handle __inst, xdc_UInt andMask, xdc_UInt orMask, xdc_UInt timeout );

/* post__E */

extern void ti_sysbios_knl_Event_post__E( ti_sysbios_knl_Event_Handle __inst, xdc_UInt eventMask );

extern void ti_sysbios_knl_Event_post__F( ti_sysbios_knl_Event_Object* __inst, xdc_UInt eventMask );
extern void ti_sysbios_knl_Event_post__R( ti_sysbios_knl_Event_Handle __inst, xdc_UInt eventMask );

/* getPostedEvents__E */

extern xdc_UInt ti_sysbios_knl_Event_getPostedEvents__E( ti_sysbios_knl_Event_Handle __inst );

extern xdc_UInt ti_sysbios_knl_Event_getPostedEvents__F( ti_sysbios_knl_Event_Object* __inst );
extern xdc_UInt ti_sysbios_knl_Event_getPostedEvents__R( ti_sysbios_knl_Event_Handle __inst );

/* sync__E */

extern void ti_sysbios_knl_Event_sync__E( ti_sysbios_knl_Event_Handle __inst, xdc_UInt eventId, xdc_UInt count );

extern void ti_sysbios_knl_Event_sync__F( ti_sysbios_knl_Event_Object* __inst, xdc_UInt eventId, xdc_UInt count );
extern void ti_sysbios_knl_Event_sync__R( ti_sysbios_knl_Event_Handle __inst, xdc_UInt eventId, xdc_UInt count );

/* pendTimeout__I */

extern void ti_sysbios_knl_Event_pendTimeout__I( xdc_UArg arg );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* pend_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_knl_Event_pend_FxnT)(void*, xdc_UInt, xdc_UInt, xdc_UInt);
static inline ti_sysbios_knl_Event_pend_FxnT ti_sysbios_knl_Event_pend_fxnP( void )
{
    return (ti_sysbios_knl_Event_pend_FxnT)ti_sysbios_knl_Event_pend__E; 
}

/* post_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Event_post_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Event_post_FxnT ti_sysbios_knl_Event_post_fxnP( void )
{
    return (ti_sysbios_knl_Event_post_FxnT)ti_sysbios_knl_Event_post__E; 
}

/* getPostedEvents_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_knl_Event_getPostedEvents_FxnT)(void*);
static inline ti_sysbios_knl_Event_getPostedEvents_FxnT ti_sysbios_knl_Event_getPostedEvents_fxnP( void )
{
    return (ti_sysbios_knl_Event_getPostedEvents_FxnT)ti_sysbios_knl_Event_getPostedEvents__E; 
}

/* sync_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Event_sync_FxnT)(void*, xdc_UInt, xdc_UInt);
static inline ti_sysbios_knl_Event_sync_FxnT ti_sysbios_knl_Event_sync_fxnP( void )
{
    return (ti_sysbios_knl_Event_sync_FxnT)ti_sysbios_knl_Event_sync__E; 
}


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Event_Module__id ti_sysbios_knl_Event_Module_id( void ) 
{
    return ti_sysbios_knl_Event_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_knl_Event_Module_hasMask( void ) 
{
    return ti_sysbios_knl_Event_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_knl_Event_Module_getMask( void ) 
{
    return ti_sysbios_knl_Event_Module__diagsMask__C != 0 ? *ti_sysbios_knl_Event_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_knl_Event_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_knl_Event_Module__diagsMask__C != 0) *ti_sysbios_knl_Event_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_knl_Event_Params_init( ti_sysbios_knl_Event_Params* prms ) 
{
    if (prms) {
        ti_sysbios_knl_Event_Params__init__S(prms, 0, sizeof(ti_sysbios_knl_Event_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_knl_Event_Params_copy( ti_sysbios_knl_Event_Params* dst, const ti_sysbios_knl_Event_Params* src ) 
{
    if (dst) {
        ti_sysbios_knl_Event_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_knl_Event_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_knl_Event_Handle ti_sysbios_knl_Event_Object_get( ti_sysbios_knl_Event_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_knl_Event_Handle)ti_sysbios_knl_Event_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_knl_Event_Handle ti_sysbios_knl_Event_Object_first( void )
{
    return (ti_sysbios_knl_Event_Handle)ti_sysbios_knl_Event_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_knl_Event_Handle ti_sysbios_knl_Event_Object_next( ti_sysbios_knl_Event_Object* obj )
{
    return (ti_sysbios_knl_Event_Handle)ti_sysbios_knl_Event_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_knl_Event_Handle_label( ti_sysbios_knl_Event_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_knl_Event_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_knl_Event_Handle_name( ti_sysbios_knl_Event_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_knl_Event_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_knl_Event_Handle ti_sysbios_knl_Event_create( const ti_sysbios_knl_Event_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (ti_sysbios_knl_Event_Handle)ti_sysbios_knl_Event_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Event_Params), __eb);
}

/* construct */
static inline void ti_sysbios_knl_Event_construct( ti_sysbios_knl_Event_Struct* __obj, const ti_sysbios_knl_Event_Params* __prms )
{
    ti_sysbios_knl_Event_Object__create__S(__obj, sizeof (ti_sysbios_knl_Event_Struct), 0, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Event_Params), 0);
}

/* delete */
static inline void ti_sysbios_knl_Event_delete( ti_sysbios_knl_Event_Handle* instp )
{
    ti_sysbios_knl_Event_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_knl_Event_destruct( ti_sysbios_knl_Event_Struct* obj )
{
    ti_sysbios_knl_Event_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_knl_Event_Handle ti_sysbios_knl_Event_handle( ti_sysbios_knl_Event_Struct* str )
{
    return (ti_sysbios_knl_Event_Handle)str;
}

/* struct */
static inline ti_sysbios_knl_Event_Struct* ti_sysbios_knl_Event_struct( ti_sysbios_knl_Event_Handle inst )
{
    return (ti_sysbios_knl_Event_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */





/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:32; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  @(#) xdc.runtime; 2, 1, 0,375; 4-27-2012 14:30:32; /db/ztree/library/trees/xdc/xdc-y25x/src/packages/
 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:32; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
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
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:34; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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

/* Mode */
enum ti_sysbios_knl_Semaphore_Mode {
    ti_sysbios_knl_Semaphore_Mode_COUNTING,
    ti_sysbios_knl_Semaphore_Mode_BINARY
};
typedef enum ti_sysbios_knl_Semaphore_Mode ti_sysbios_knl_Semaphore_Mode;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_knl_Semaphore_Args__create {
    xdc_Int count;
} ti_sysbios_knl_Semaphore_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* PendState */
enum ti_sysbios_knl_Semaphore_PendState {
    ti_sysbios_knl_Semaphore_PendState_TIMEOUT = 0,
    ti_sysbios_knl_Semaphore_PendState_POSTED = 1,
    ti_sysbios_knl_Semaphore_PendState_CLOCK_WAIT = 2,
    ti_sysbios_knl_Semaphore_PendState_WAIT_FOREVER = 3
};
typedef enum ti_sysbios_knl_Semaphore_PendState ti_sysbios_knl_Semaphore_PendState;

/* PendElem */
struct ti_sysbios_knl_Semaphore_PendElem {
    ti_sysbios_knl_Task_PendElem tpElem;
    ti_sysbios_knl_Semaphore_PendState pendState;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_knl_Semaphore_Module__diagsEnabled;
extern far const CT__ti_sysbios_knl_Semaphore_Module__diagsEnabled ti_sysbios_knl_Semaphore_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_knl_Semaphore_Module__diagsIncluded;
extern far const CT__ti_sysbios_knl_Semaphore_Module__diagsIncluded ti_sysbios_knl_Semaphore_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_knl_Semaphore_Module__diagsMask;
extern far const CT__ti_sysbios_knl_Semaphore_Module__diagsMask ti_sysbios_knl_Semaphore_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Semaphore_Module__gateObj;
extern far const CT__ti_sysbios_knl_Semaphore_Module__gateObj ti_sysbios_knl_Semaphore_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_knl_Semaphore_Module__gatePrms;
extern far const CT__ti_sysbios_knl_Semaphore_Module__gatePrms ti_sysbios_knl_Semaphore_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_knl_Semaphore_Module__id;
extern far const CT__ti_sysbios_knl_Semaphore_Module__id ti_sysbios_knl_Semaphore_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_knl_Semaphore_Module__loggerDefined;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerDefined ti_sysbios_knl_Semaphore_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_knl_Semaphore_Module__loggerObj;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerObj ti_sysbios_knl_Semaphore_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_knl_Semaphore_Module__loggerFxn0;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerFxn0 ti_sysbios_knl_Semaphore_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_knl_Semaphore_Module__loggerFxn1;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerFxn1 ti_sysbios_knl_Semaphore_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_knl_Semaphore_Module__loggerFxn2;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerFxn2 ti_sysbios_knl_Semaphore_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_knl_Semaphore_Module__loggerFxn4;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerFxn4 ti_sysbios_knl_Semaphore_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_knl_Semaphore_Module__loggerFxn8;
extern far const CT__ti_sysbios_knl_Semaphore_Module__loggerFxn8 ti_sysbios_knl_Semaphore_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_knl_Semaphore_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_knl_Semaphore_Module__startupDoneFxn ti_sysbios_knl_Semaphore_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_knl_Semaphore_Object__count;
extern far const CT__ti_sysbios_knl_Semaphore_Object__count ti_sysbios_knl_Semaphore_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_knl_Semaphore_Object__heap;
extern far const CT__ti_sysbios_knl_Semaphore_Object__heap ti_sysbios_knl_Semaphore_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_knl_Semaphore_Object__sizeof;
extern far const CT__ti_sysbios_knl_Semaphore_Object__sizeof ti_sysbios_knl_Semaphore_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_knl_Semaphore_Object__table;
extern far const CT__ti_sysbios_knl_Semaphore_Object__table ti_sysbios_knl_Semaphore_Object__table__C;

/* LM_post */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Semaphore_LM_post;
extern far const CT__ti_sysbios_knl_Semaphore_LM_post ti_sysbios_knl_Semaphore_LM_post__C;

/* LM_pend */
typedef xdc_runtime_Log_Event CT__ti_sysbios_knl_Semaphore_LM_pend;
extern far const CT__ti_sysbios_knl_Semaphore_LM_pend ti_sysbios_knl_Semaphore_LM_pend__C;

/* A_noEvents */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Semaphore_A_noEvents;
extern far const CT__ti_sysbios_knl_Semaphore_A_noEvents ti_sysbios_knl_Semaphore_A_noEvents__C;

/* A_invTimeout */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Semaphore_A_invTimeout;
extern far const CT__ti_sysbios_knl_Semaphore_A_invTimeout ti_sysbios_knl_Semaphore_A_invTimeout__C;

/* A_badContext */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_knl_Semaphore_A_badContext;
extern far const CT__ti_sysbios_knl_Semaphore_A_badContext ti_sysbios_knl_Semaphore_A_badContext__C;

/* supportsEvents */
typedef xdc_Bool CT__ti_sysbios_knl_Semaphore_supportsEvents;
extern far const CT__ti_sysbios_knl_Semaphore_supportsEvents ti_sysbios_knl_Semaphore_supportsEvents__C;

/* eventPost */
typedef void (*CT__ti_sysbios_knl_Semaphore_eventPost)(ti_sysbios_knl_Event_Handle, xdc_UInt);
extern far const CT__ti_sysbios_knl_Semaphore_eventPost ti_sysbios_knl_Semaphore_eventPost__C;

/* eventSync */
typedef void (*CT__ti_sysbios_knl_Semaphore_eventSync)(ti_sysbios_knl_Event_Handle, xdc_UInt, xdc_UInt);
extern far const CT__ti_sysbios_knl_Semaphore_eventSync ti_sysbios_knl_Semaphore_eventSync__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_knl_Semaphore_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_knl_Event_Handle event;
    xdc_UInt eventId;
    ti_sysbios_knl_Semaphore_Mode mode;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_knl_Semaphore_Struct {
    ti_sysbios_knl_Event_Handle __f0;
    xdc_UInt __f1;
    ti_sysbios_knl_Semaphore_Mode __f2;
    volatile xdc_UInt16 __f3;
    ti_sysbios_knl_Queue_Struct __f4;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Instance_init__F */

extern void ti_sysbios_knl_Semaphore_Instance_init__F( ti_sysbios_knl_Semaphore_Object*, xdc_Int count, const ti_sysbios_knl_Semaphore_Params* );

/* Instance_finalize__F */

extern void ti_sysbios_knl_Semaphore_Instance_finalize__F( ti_sysbios_knl_Semaphore_Object* );

/* Instance_init__R */

extern void ti_sysbios_knl_Semaphore_Instance_init__R( ti_sysbios_knl_Semaphore_Object*, xdc_Int count, const ti_sysbios_knl_Semaphore_Params* );

/* Instance_finalize__R */

extern void ti_sysbios_knl_Semaphore_Instance_finalize__R( ti_sysbios_knl_Semaphore_Object* );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_knl_Semaphore_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_knl_Semaphore_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_knl_Semaphore_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_knl_Semaphore_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_knl_Semaphore_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_knl_Semaphore_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_knl_Semaphore_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_knl_Semaphore_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_knl_Semaphore_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* getCount__E */

extern xdc_Int ti_sysbios_knl_Semaphore_getCount__E( ti_sysbios_knl_Semaphore_Handle __inst );

extern xdc_Int ti_sysbios_knl_Semaphore_getCount__F( ti_sysbios_knl_Semaphore_Object* __inst );
extern xdc_Int ti_sysbios_knl_Semaphore_getCount__R( ti_sysbios_knl_Semaphore_Handle __inst );

/* pend__E */

extern xdc_Bool ti_sysbios_knl_Semaphore_pend__E( ti_sysbios_knl_Semaphore_Handle __inst, xdc_UInt timeout );

extern xdc_Bool ti_sysbios_knl_Semaphore_pend__F( ti_sysbios_knl_Semaphore_Object* __inst, xdc_UInt timeout );
extern xdc_Bool ti_sysbios_knl_Semaphore_pend__R( ti_sysbios_knl_Semaphore_Handle __inst, xdc_UInt timeout );

/* post__E */

extern void ti_sysbios_knl_Semaphore_post__E( ti_sysbios_knl_Semaphore_Handle __inst );

extern void ti_sysbios_knl_Semaphore_post__F( ti_sysbios_knl_Semaphore_Object* __inst );
extern void ti_sysbios_knl_Semaphore_post__R( ti_sysbios_knl_Semaphore_Handle __inst );

/* registerEvent__E */

extern void ti_sysbios_knl_Semaphore_registerEvent__E( ti_sysbios_knl_Semaphore_Handle __inst, ti_sysbios_knl_Event_Handle event, xdc_UInt eventId );

extern void ti_sysbios_knl_Semaphore_registerEvent__F( ti_sysbios_knl_Semaphore_Object* __inst, ti_sysbios_knl_Event_Handle event, xdc_UInt eventId );
extern void ti_sysbios_knl_Semaphore_registerEvent__R( ti_sysbios_knl_Semaphore_Handle __inst, ti_sysbios_knl_Event_Handle event, xdc_UInt eventId );

/* reset__E */

extern void ti_sysbios_knl_Semaphore_reset__E( ti_sysbios_knl_Semaphore_Handle __inst, xdc_Int count );

extern void ti_sysbios_knl_Semaphore_reset__F( ti_sysbios_knl_Semaphore_Object* __inst, xdc_Int count );
extern void ti_sysbios_knl_Semaphore_reset__R( ti_sysbios_knl_Semaphore_Handle __inst, xdc_Int count );

/* pendTimeout__I */

extern void ti_sysbios_knl_Semaphore_pendTimeout__I( xdc_UArg arg );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getCount_{FxnT,fxnP} */
typedef xdc_Int (*ti_sysbios_knl_Semaphore_getCount_FxnT)(void*);
static inline ti_sysbios_knl_Semaphore_getCount_FxnT ti_sysbios_knl_Semaphore_getCount_fxnP( void )
{
    return (ti_sysbios_knl_Semaphore_getCount_FxnT)ti_sysbios_knl_Semaphore_getCount__E; 
}

/* pend_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_knl_Semaphore_pend_FxnT)(void*, xdc_UInt);
static inline ti_sysbios_knl_Semaphore_pend_FxnT ti_sysbios_knl_Semaphore_pend_fxnP( void )
{
    return (ti_sysbios_knl_Semaphore_pend_FxnT)ti_sysbios_knl_Semaphore_pend__E; 
}

/* post_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Semaphore_post_FxnT)(void*);
static inline ti_sysbios_knl_Semaphore_post_FxnT ti_sysbios_knl_Semaphore_post_fxnP( void )
{
    return (ti_sysbios_knl_Semaphore_post_FxnT)ti_sysbios_knl_Semaphore_post__E; 
}

/* registerEvent_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Semaphore_registerEvent_FxnT)(void*, ti_sysbios_knl_Event_Handle, xdc_UInt);
static inline ti_sysbios_knl_Semaphore_registerEvent_FxnT ti_sysbios_knl_Semaphore_registerEvent_fxnP( void )
{
    return (ti_sysbios_knl_Semaphore_registerEvent_FxnT)ti_sysbios_knl_Semaphore_registerEvent__E; 
}

/* reset_{FxnT,fxnP} */
typedef void (*ti_sysbios_knl_Semaphore_reset_FxnT)(void*, xdc_Int);
static inline ti_sysbios_knl_Semaphore_reset_FxnT ti_sysbios_knl_Semaphore_reset_fxnP( void )
{
    return (ti_sysbios_knl_Semaphore_reset_FxnT)ti_sysbios_knl_Semaphore_reset__E; 
}


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_knl_Semaphore_Module__id ti_sysbios_knl_Semaphore_Module_id( void ) 
{
    return ti_sysbios_knl_Semaphore_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_knl_Semaphore_Module_hasMask( void ) 
{
    return ti_sysbios_knl_Semaphore_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_knl_Semaphore_Module_getMask( void ) 
{
    return ti_sysbios_knl_Semaphore_Module__diagsMask__C != 0 ? *ti_sysbios_knl_Semaphore_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_knl_Semaphore_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_knl_Semaphore_Module__diagsMask__C != 0) *ti_sysbios_knl_Semaphore_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_knl_Semaphore_Params_init( ti_sysbios_knl_Semaphore_Params* prms ) 
{
    if (prms) {
        ti_sysbios_knl_Semaphore_Params__init__S(prms, 0, sizeof(ti_sysbios_knl_Semaphore_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_knl_Semaphore_Params_copy( ti_sysbios_knl_Semaphore_Params* dst, const ti_sysbios_knl_Semaphore_Params* src ) 
{
    if (dst) {
        ti_sysbios_knl_Semaphore_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_knl_Semaphore_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_knl_Semaphore_Handle ti_sysbios_knl_Semaphore_Object_get( ti_sysbios_knl_Semaphore_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_knl_Semaphore_Handle)ti_sysbios_knl_Semaphore_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_knl_Semaphore_Handle ti_sysbios_knl_Semaphore_Object_first( void )
{
    return (ti_sysbios_knl_Semaphore_Handle)ti_sysbios_knl_Semaphore_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_knl_Semaphore_Handle ti_sysbios_knl_Semaphore_Object_next( ti_sysbios_knl_Semaphore_Object* obj )
{
    return (ti_sysbios_knl_Semaphore_Handle)ti_sysbios_knl_Semaphore_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_knl_Semaphore_Handle_label( ti_sysbios_knl_Semaphore_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_knl_Semaphore_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_knl_Semaphore_Handle_name( ti_sysbios_knl_Semaphore_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_knl_Semaphore_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_knl_Semaphore_Handle ti_sysbios_knl_Semaphore_create( xdc_Int count, const ti_sysbios_knl_Semaphore_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_knl_Semaphore_Args__create __args;
    __args.count = count;
    return (ti_sysbios_knl_Semaphore_Handle)ti_sysbios_knl_Semaphore_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Semaphore_Params), __eb);
}

/* construct */
static inline void ti_sysbios_knl_Semaphore_construct( ti_sysbios_knl_Semaphore_Struct* __obj, xdc_Int count, const ti_sysbios_knl_Semaphore_Params* __prms )
{
    ti_sysbios_knl_Semaphore_Args__create __args;
    __args.count = count;
    ti_sysbios_knl_Semaphore_Object__create__S(__obj, sizeof (ti_sysbios_knl_Semaphore_Struct), &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_knl_Semaphore_Params), 0);
}

/* delete */
static inline void ti_sysbios_knl_Semaphore_delete( ti_sysbios_knl_Semaphore_Handle* instp )
{
    ti_sysbios_knl_Semaphore_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_knl_Semaphore_destruct( ti_sysbios_knl_Semaphore_Struct* obj )
{
    ti_sysbios_knl_Semaphore_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_knl_Semaphore_Handle ti_sysbios_knl_Semaphore_handle( ti_sysbios_knl_Semaphore_Struct* str )
{
    return (ti_sysbios_knl_Semaphore_Handle)str;
}

/* struct */
static inline ti_sysbios_knl_Semaphore_Struct* ti_sysbios_knl_Semaphore_struct( ti_sysbios_knl_Semaphore_Handle inst )
{
    return (ti_sysbios_knl_Semaphore_Struct*)inst;
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



/* module prefix */

/*
 *  @(#) ti.sysbios.knl; 2, 0, 0, 0,545; 3-20-2012 14:03:33; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

//D:\TInew\bios_6_33_04_39\packages
/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
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
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

/*
 *  @(#) ti.sysbios; 2, 0, 0, 0,566; 3-20-2012 14:01:21; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */



/*
 * ======== module ti.sysbios.BIOS ========
 */

typedef struct ti_sysbios_BIOS_intSize ti_sysbios_BIOS_intSize;
typedef struct ti_sysbios_BIOS_Module_State ti_sysbios_BIOS_Module_State;

/*
 * ======== module ti.sysbios.BIOS_RtsGateProxy ========
 */

typedef struct ti_sysbios_BIOS_RtsGateProxy_Fxns__ ti_sysbios_BIOS_RtsGateProxy_Fxns__;
typedef const ti_sysbios_BIOS_RtsGateProxy_Fxns__* ti_sysbios_BIOS_RtsGateProxy_Module;
typedef struct ti_sysbios_BIOS_RtsGateProxy_Params ti_sysbios_BIOS_RtsGateProxy_Params;
typedef struct xdc_runtime_IGateProvider___Object *ti_sysbios_BIOS_RtsGateProxy_Handle;



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
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
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
typedef xdc_Bits32 CT__ti_sysbios_BIOS_RtsGateProxy_Module__diagsEnabled;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__diagsEnabled ti_sysbios_BIOS_RtsGateProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_BIOS_RtsGateProxy_Module__diagsIncluded;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__diagsIncluded ti_sysbios_BIOS_RtsGateProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_BIOS_RtsGateProxy_Module__diagsMask;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__diagsMask ti_sysbios_BIOS_RtsGateProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_BIOS_RtsGateProxy_Module__gateObj;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__gateObj ti_sysbios_BIOS_RtsGateProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_BIOS_RtsGateProxy_Module__gatePrms;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__gatePrms ti_sysbios_BIOS_RtsGateProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_BIOS_RtsGateProxy_Module__id;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__id ti_sysbios_BIOS_RtsGateProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerDefined;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerDefined ti_sysbios_BIOS_RtsGateProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerObj;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerObj ti_sysbios_BIOS_RtsGateProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn0;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn0 ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn1;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn1 ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn2;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn2 ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn4;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn4 ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn8;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn8 ti_sysbios_BIOS_RtsGateProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_BIOS_RtsGateProxy_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Module__startupDoneFxn ti_sysbios_BIOS_RtsGateProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_BIOS_RtsGateProxy_Object__count;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Object__count ti_sysbios_BIOS_RtsGateProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_BIOS_RtsGateProxy_Object__heap;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Object__heap ti_sysbios_BIOS_RtsGateProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_BIOS_RtsGateProxy_Object__sizeof;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Object__sizeof ti_sysbios_BIOS_RtsGateProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_BIOS_RtsGateProxy_Object__table;
extern far const CT__ti_sysbios_BIOS_RtsGateProxy_Object__table ti_sysbios_BIOS_RtsGateProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_BIOS_RtsGateProxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_BIOS_RtsGateProxy_Struct {
    const ti_sysbios_BIOS_RtsGateProxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_BIOS_RtsGateProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_sysbios_BIOS_RtsGateProxy_Handle);
    void (*leave)(ti_sysbios_BIOS_RtsGateProxy_Handle, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const ti_sysbios_BIOS_RtsGateProxy_Fxns__ ti_sysbios_BIOS_RtsGateProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_BIOS_RtsGateProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_BIOS_RtsGateProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_BIOS_RtsGateProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_BIOS_RtsGateProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_BIOS_RtsGateProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_BIOS_RtsGateProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_BIOS_RtsGateProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_BIOS_RtsGateProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_BIOS_RtsGateProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool ti_sysbios_BIOS_RtsGateProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr ti_sysbios_BIOS_RtsGateProxy_Proxy__delegate__S( void );

/* query__E */

extern xdc_Bool ti_sysbios_BIOS_RtsGateProxy_query__E( xdc_Int qual );

extern xdc_Bool ti_sysbios_BIOS_RtsGateProxy_query__R( xdc_Int qual );

/* enter__E */

extern xdc_IArg ti_sysbios_BIOS_RtsGateProxy_enter__E( ti_sysbios_BIOS_RtsGateProxy_Handle __inst );

extern xdc_IArg ti_sysbios_BIOS_RtsGateProxy_enter__R( ti_sysbios_BIOS_RtsGateProxy_Handle __inst );

/* leave__E */

extern void ti_sysbios_BIOS_RtsGateProxy_leave__E( ti_sysbios_BIOS_RtsGateProxy_Handle __inst, xdc_IArg key );

extern void ti_sysbios_BIOS_RtsGateProxy_leave__R( ti_sysbios_BIOS_RtsGateProxy_Handle __inst, xdc_IArg key );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* enter_{FxnT,fxnP} */
typedef xdc_IArg (*ti_sysbios_BIOS_RtsGateProxy_enter_FxnT)(void*);
static inline ti_sysbios_BIOS_RtsGateProxy_enter_FxnT ti_sysbios_BIOS_RtsGateProxy_enter_fxnP( void )
{
    return (ti_sysbios_BIOS_RtsGateProxy_enter_FxnT)ti_sysbios_BIOS_RtsGateProxy_enter__E; 
}

/* leave_{FxnT,fxnP} */
typedef void (*ti_sysbios_BIOS_RtsGateProxy_leave_FxnT)(void*, xdc_IArg);
static inline ti_sysbios_BIOS_RtsGateProxy_leave_FxnT ti_sysbios_BIOS_RtsGateProxy_leave_fxnP( void )
{
    return (ti_sysbios_BIOS_RtsGateProxy_leave_FxnT)ti_sysbios_BIOS_RtsGateProxy_leave__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IGateProvider_Module ti_sysbios_BIOS_RtsGateProxy_Module_upCast( void )
{
    return (xdc_runtime_IGateProvider_Module)ti_sysbios_BIOS_RtsGateProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */

/* Handle_upCast */
static inline xdc_runtime_IGateProvider_Handle ti_sysbios_BIOS_RtsGateProxy_Handle_upCast( ti_sysbios_BIOS_RtsGateProxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */

/* Handle_downCast */
static inline ti_sysbios_BIOS_RtsGateProxy_Handle ti_sysbios_BIOS_RtsGateProxy_Handle_downCast( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
if (ti_sysbios_BIOS_RtsGateProxy_Proxy__abstract__S()) return (ti_sysbios_BIOS_RtsGateProxy_Handle)i;
    return (void*)i2->__fxns == (void*)ti_sysbios_BIOS_RtsGateProxy_Proxy__delegate__S() ? (ti_sysbios_BIOS_RtsGateProxy_Handle)i : 0;
}

/* Handle_from_xdc_runtime_IGateProvider */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_BIOS_RtsGateProxy_Module__id ti_sysbios_BIOS_RtsGateProxy_Module_id( void ) 
{
    return ti_sysbios_BIOS_RtsGateProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */

/* Params_init */
static inline void ti_sysbios_BIOS_RtsGateProxy_Params_init( ti_sysbios_BIOS_RtsGateProxy_Params* prms ) 
{
    if (prms) {
        ti_sysbios_BIOS_RtsGateProxy_Params__init__S(prms, 0, sizeof(ti_sysbios_BIOS_RtsGateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_BIOS_RtsGateProxy_Params_copy( ti_sysbios_BIOS_RtsGateProxy_Params* dst, const ti_sysbios_BIOS_RtsGateProxy_Params* src ) 
{
    if (dst) {
        ti_sysbios_BIOS_RtsGateProxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_BIOS_RtsGateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline ti_sysbios_BIOS_RtsGateProxy_Handle ti_sysbios_BIOS_RtsGateProxy_create( const ti_sysbios_BIOS_RtsGateProxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (ti_sysbios_BIOS_RtsGateProxy_Handle)ti_sysbios_BIOS_RtsGateProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(ti_sysbios_BIOS_RtsGateProxy_Params), __eb);
}

/* delete */
static inline void ti_sysbios_BIOS_RtsGateProxy_delete( ti_sysbios_BIOS_RtsGateProxy_Handle* instp )
{
    ti_sysbios_BIOS_RtsGateProxy_Object__delete__S(instp);
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

/* ThreadType */
enum ti_sysbios_BIOS_ThreadType {
    ti_sysbios_BIOS_ThreadType_Hwi,
    ti_sysbios_BIOS_ThreadType_Swi,
    ti_sysbios_BIOS_ThreadType_Task,
    ti_sysbios_BIOS_ThreadType_Main
};
typedef enum ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_ThreadType;

/* RtsLockType */
enum ti_sysbios_BIOS_RtsLockType {
    ti_sysbios_BIOS_NoLocking,
    ti_sysbios_BIOS_GateHwi,
    ti_sysbios_BIOS_GateSwi,
    ti_sysbios_BIOS_GateMutex,
    ti_sysbios_BIOS_GateMutexPri
};
typedef enum ti_sysbios_BIOS_RtsLockType ti_sysbios_BIOS_RtsLockType;

/* LibType */
enum ti_sysbios_BIOS_LibType {
    ti_sysbios_BIOS_LibType_Instrumented,
    ti_sysbios_BIOS_LibType_NonInstrumented,
    ti_sysbios_BIOS_LibType_Custom,
    ti_sysbios_BIOS_LibType_Debug
};
typedef enum ti_sysbios_BIOS_LibType ti_sysbios_BIOS_LibType;

/* WAIT_FOREVER */

/* NO_WAIT */

/* StartupFuncPtr */
typedef void (*ti_sysbios_BIOS_StartupFuncPtr)(void);


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* intSize */
struct ti_sysbios_BIOS_intSize {
    xdc_Int intSize;
};

/* StartFuncPtr */
typedef void (*ti_sysbios_BIOS_StartFuncPtr)(void);


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_BIOS_Module__diagsEnabled;
extern far const CT__ti_sysbios_BIOS_Module__diagsEnabled ti_sysbios_BIOS_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_BIOS_Module__diagsIncluded;
extern far const CT__ti_sysbios_BIOS_Module__diagsIncluded ti_sysbios_BIOS_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_BIOS_Module__diagsMask;
extern far const CT__ti_sysbios_BIOS_Module__diagsMask ti_sysbios_BIOS_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_BIOS_Module__gateObj;
extern far const CT__ti_sysbios_BIOS_Module__gateObj ti_sysbios_BIOS_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_BIOS_Module__gatePrms;
extern far const CT__ti_sysbios_BIOS_Module__gatePrms ti_sysbios_BIOS_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_BIOS_Module__id;
extern far const CT__ti_sysbios_BIOS_Module__id ti_sysbios_BIOS_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_BIOS_Module__loggerDefined;
extern far const CT__ti_sysbios_BIOS_Module__loggerDefined ti_sysbios_BIOS_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_BIOS_Module__loggerObj;
extern far const CT__ti_sysbios_BIOS_Module__loggerObj ti_sysbios_BIOS_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_BIOS_Module__loggerFxn0;
extern far const CT__ti_sysbios_BIOS_Module__loggerFxn0 ti_sysbios_BIOS_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_BIOS_Module__loggerFxn1;
extern far const CT__ti_sysbios_BIOS_Module__loggerFxn1 ti_sysbios_BIOS_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_BIOS_Module__loggerFxn2;
extern far const CT__ti_sysbios_BIOS_Module__loggerFxn2 ti_sysbios_BIOS_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_BIOS_Module__loggerFxn4;
extern far const CT__ti_sysbios_BIOS_Module__loggerFxn4 ti_sysbios_BIOS_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_BIOS_Module__loggerFxn8;
extern far const CT__ti_sysbios_BIOS_Module__loggerFxn8 ti_sysbios_BIOS_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_BIOS_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_BIOS_Module__startupDoneFxn ti_sysbios_BIOS_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_BIOS_Object__count;
extern far const CT__ti_sysbios_BIOS_Object__count ti_sysbios_BIOS_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_BIOS_Object__heap;
extern far const CT__ti_sysbios_BIOS_Object__heap ti_sysbios_BIOS_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_BIOS_Object__sizeof;
extern far const CT__ti_sysbios_BIOS_Object__sizeof ti_sysbios_BIOS_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_BIOS_Object__table;
extern far const CT__ti_sysbios_BIOS_Object__table ti_sysbios_BIOS_Object__table__C;

/* smpEnabled */
typedef xdc_Bool CT__ti_sysbios_BIOS_smpEnabled;
extern far const CT__ti_sysbios_BIOS_smpEnabled ti_sysbios_BIOS_smpEnabled__C;

/* cpuFreq */
typedef xdc_runtime_Types_FreqHz CT__ti_sysbios_BIOS_cpuFreq;
extern far const CT__ti_sysbios_BIOS_cpuFreq ti_sysbios_BIOS_cpuFreq__C;

/* taskEnabled */
typedef xdc_Bool CT__ti_sysbios_BIOS_taskEnabled;
extern far const CT__ti_sysbios_BIOS_taskEnabled ti_sysbios_BIOS_taskEnabled__C;

/* swiEnabled */
typedef xdc_Bool CT__ti_sysbios_BIOS_swiEnabled;
extern far const CT__ti_sysbios_BIOS_swiEnabled ti_sysbios_BIOS_swiEnabled__C;

/* clockEnabled */
typedef xdc_Bool CT__ti_sysbios_BIOS_clockEnabled;
extern far const CT__ti_sysbios_BIOS_clockEnabled ti_sysbios_BIOS_clockEnabled__C;

/* heapSize */
typedef xdc_SizeT CT__ti_sysbios_BIOS_heapSize;
extern far const CT__ti_sysbios_BIOS_heapSize ti_sysbios_BIOS_heapSize__C;

/* heapSection */
typedef xdc_String CT__ti_sysbios_BIOS_heapSection;
extern far const CT__ti_sysbios_BIOS_heapSection ti_sysbios_BIOS_heapSection__C;

/* installedErrorHook */
typedef void (*CT__ti_sysbios_BIOS_installedErrorHook)(xdc_runtime_Error_Block*);
extern far const CT__ti_sysbios_BIOS_installedErrorHook ti_sysbios_BIOS_installedErrorHook__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_BIOS_Module__startupDone__S( void );

/* start__E */

extern void ti_sysbios_BIOS_start__E( void );

extern void ti_sysbios_BIOS_start__F( void );
extern void ti_sysbios_BIOS_start__R( void );

/* exit__E */

extern void ti_sysbios_BIOS_exit__E( xdc_Int stat );

extern void ti_sysbios_BIOS_exit__F( xdc_Int stat );
extern void ti_sysbios_BIOS_exit__R( xdc_Int stat );

/* getThreadType__E */

extern ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_getThreadType__E( void );

extern ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_getThreadType__F( void );
extern ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_getThreadType__R( void );

/* setThreadType__E */

extern ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_setThreadType__E( ti_sysbios_BIOS_ThreadType ttype );

extern ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_setThreadType__F( ti_sysbios_BIOS_ThreadType ttype );
extern ti_sysbios_BIOS_ThreadType ti_sysbios_BIOS_setThreadType__R( ti_sysbios_BIOS_ThreadType ttype );

/* setCpuFreq__E */

extern void ti_sysbios_BIOS_setCpuFreq__E( xdc_runtime_Types_FreqHz* freq );

extern void ti_sysbios_BIOS_setCpuFreq__F( xdc_runtime_Types_FreqHz* freq );
extern void ti_sysbios_BIOS_setCpuFreq__R( xdc_runtime_Types_FreqHz* freq );

/* getCpuFreq__E */

extern void ti_sysbios_BIOS_getCpuFreq__E( xdc_runtime_Types_FreqHz* freq );

extern void ti_sysbios_BIOS_getCpuFreq__F( xdc_runtime_Types_FreqHz* freq );
extern void ti_sysbios_BIOS_getCpuFreq__R( xdc_runtime_Types_FreqHz* freq );

/* errorRaiseHook__I */

extern void ti_sysbios_BIOS_errorRaiseHook__I( xdc_runtime_Error_Block* eb );

/* startFunc__I */

extern void ti_sysbios_BIOS_startFunc__I( void );

/* registerRTSLock__I */

extern void ti_sysbios_BIOS_registerRTSLock__I( void );

/* removeRTSLock__I */

extern void ti_sysbios_BIOS_removeRTSLock__I( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_BIOS_Module__id ti_sysbios_BIOS_Module_id( void ) 
{
    return ti_sysbios_BIOS_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_BIOS_Module_hasMask( void ) 
{
    return ti_sysbios_BIOS_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_BIOS_Module_getMask( void ) 
{
    return ti_sysbios_BIOS_Module__diagsMask__C != 0 ? *ti_sysbios_BIOS_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_BIOS_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_BIOS_Module__diagsMask__C != 0) *ti_sysbios_BIOS_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */


/*
 *  @(#) ti.sysbios; 2, 0, 0, 0,566; 3-20-2012 14:01:21; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */





/*
 * ======== STATE STRUCTURES ========
 */



/*
 * ======== PREFIX ALIASES ========
 */



/* module prefix */

/* proxies */
/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
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
 * ======== PREFIX ALIASES ========
 */



/* module prefix */


/*
 *  @(#) ti.sysbios; 2, 0, 0, 0,566; 3-20-2012 14:01:20; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */







typedef void (*pfnTask)(void *);

typedef enum TaskStack
{
	TSK_STACKSIZE_1024 = 1024,
	TSK_STACKSIZE_2048 = 2048,
	TSK_STACKSIZE_3072 = 3072,
	TSK_STACKSIZE_4096 = 4096,
	TSK_STACKSIZE_8192 = 8192
}TaskStack;

typedef enum TaskPri
{
	TSK_PRIORITY_0   = 0,
	TSK_PRIORITY_1,
	TSK_PRIORITY_2,
	TSK_PRIORITY_3,
	TSK_PRIORITY_4,
	TSK_PRIORITY_5,
	TSK_PRIORITY_6,
	TSK_PRIORITY_7,
	TSK_PRIORITY_8,
	TSK_PRIORITY_9,
	TSK_PRIORITY_10,
	TSK_PRIORITY_11,
	TSK_PRIORITY_12,
	TSK_PRIORITY_13,
	TSK_PRIORITY_14,
	TSK_PRIORITY_15
}TaskPri;

typedef struct stSteTask
{
	UINT8       Name[20];
	TaskPri     hPriority;
	//TSK_Handle Handle;
	ti_sysbios_knl_Task_Handle Handle;
	//TSK_Attrs  tskattrs;
	ti_sysbios_knl_Task_Params tskattrs;
    void (*pfnTask)(void *);
}Task;

// Creates a task in a non-running state
extern BOOL Task_Init(Task *pThis, String sName,  pfnTask pfn , void *pArg);
// Creates a task in a non-running state - Different version has prio and stack size
extern BOOL Task_Init1(Task *pThis, String Name,  pfnTask pfn , void *pArg, TaskStack  eStacksize, TaskPri ePriority );

/* Start the Task */
void Task_Start(Task *pThis);

/* Stop the Task */
extern void Task_Stop(Task *pThis);

/*Given the task, Sets Task priority */
extern void Task_SetPri(Task *pThis, TaskPri ePriority);

/*Mutex and Sigal based on the Semaphore. */

typedef struct stMutex
{
	char Name[20];
	//volatile SEM_Handle Handle;
	volatile ti_sysbios_knl_Semaphore_Handle Handle;
}Mutex;


extern BOOL Mutex_Init( Mutex *pThis , char *name, UINT8 InitState);
extern void Mutex_Lock( Mutex *pThis );
extern void Mutex_Unlock( Mutex *pThis );
extern BOOL Mutex_Lock_Timeout( Mutex *pThis);


/* A wrapper intertask signal based on Semaphore variable */
typedef Mutex Signal;

extern BOOL Signal_Init( Signal *pThis, String name);
extern void Signal_Pend( Signal *pThis);
extern void Signal_Enable(Signal *pThis);
extern BOOL Signal_Poll( Signal *pThis, UINT16 nTimeout);
extern void Signal_Post( Signal *pThis );

extern void Signal_Broadcast( Signal *pThis);

//#include <log.h>
//#include<xdc/runtime/LoggerBuf.h> // should be removed this include file
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


//CSL_SemContext  semcontext;
//CSL_Status      semstat;

extern far const int Core_Num;


//#pragma CODE_SECTION(HSEM_ModuleInit,".textDDR")

void HSEM_ModuleInit()
{
	//Hsem oDummySem;
	//UINT8 nSemIndex = 0;
	Uint8 nSemIndex = 0;
	 Bool isFree;



	/*if (CSL_SOK != CSL_semInit(&semcontext))
	{
		LOG_TRACE0( "CSL_semInit error ");
	}

	HSEM_Init(&oDummySem, HSEM_LAST);

	for (nSemIndex = 0; nSemIndex <= HSEM_LAST ; ++nSemIndex)
	{
		oDummySem.hSemHandle->regs->DIRECT[nSemIndex] = 1; // Makes forcefull free
	}
	CSL_semClose(oDummySem.hSemHandle);*/ // not required in C6678

	for (nSemIndex = 0; nSemIndex <= HSEM_LAST ; ++nSemIndex)
	{
		// Check if Semaphore is Free or not.
		   isFree = CSL_semIsFree(nSemIndex);
		 // if the semaphore is not free, force the semaphore to free
		    if((!isFree))
		        {
		        // Release the semaphore.
		           CSL_semReleaseSemaphore(nSemIndex);

		        }

	}
}

//#pragma CODE_SECTION(HSEM_Init,".textDDR")

void HSEM_Init(Hsem *pThis, UINT8 nSemNum)
{
//	CSL_Status      semstat; // not required for C6678
	Bool isFree; // for c6678

	pThis->Sem_Number = (HSEM_NUM)nSemNum;  // for c6678

	if(nSemNum >= HSEM_INVALID)
	{
		return;
	}
	else
	{

	;
//	pThis->oParam.flags = nSemNum; // not required for c6678 API
	
/*	pThis->hSemHandle = CSL_semOpen(&pThis->oSemObj, CSL_SEM, &pThis->oParam, &semstat);
	if (semstat != CSL_SOK)
	{
		LOG_TRACE0("Sem open error");

		// To Raise Exception
	}*/

	//pThis->hSemHandle->regs->DIRECT[nSemNum] = 1; // Makes forcefull free
//##############  above commented lines are not required for c6678 API #############
	 // Makes forcefull free


	 isFree = CSL_semIsFree (nSemNum); 	// Check if Semaphore is Free or not.
	 // if the semaphore is not free, forcefully make the semaphore to free
	  if((!isFree))
		{
		// Release the semaphore.
		  CSL_semReleaseSemaphore (nSemNum);

	    }

	}
//	HSEM_Unlock(pThis);

}

void HSEM_Lock(Hsem *pThis)
{
	//volatile CSL_SemVal semVal; // not required for C6678

	while(1)
	{
		/*if (CSL_SOK != CSL_semGetHwStatus(pThis->hSemHandle, CSL_SEM_QUERY_STATUS, (void *)&semVal ))
		{
			LOG_TRACE0("CSL_semGetHwStatus error");
		}

		if(semVal.semFree == CSL_SEM_FREE)
		{
			break;
		}*/
//##############  above commented lines are not required for c6678 API #############
		if(CSL_semIsFree (pThis->Sem_Number))
		{
			break;
		}
		else
		{
			//LOG_TRACE1( "lock waitng for sem %d ", pThis->hSemHandle->semNum); // old

	//		LOG_TRACE1( "lock waitng for sem %d ", pThis->Sem_Number); // new

			//TSK_yield();// DSPBIOS function
			ti_sysbios_knl_Task_yield__E();// SYSBIOS function
		}

	}

	while(1)
	{
		//if (CSL_SOK != CSL_semHwControl(pThis->hSemHandle, CSL_SEM_CMD_WRITE_POST_DIRECT,(CSL_SemVal *) &semVal))
	//	{
	//		LOG_TRACE0("CSL_semHwControl error");
	//	}
         if(!CSL_semAcquireDirect(pThis->Sem_Number))
         {
        	 ;
         }
	//	if (CSL_SOK != CSL_semGetHwStatus(pThis->hSemHandle, CSL_SEM_QUERY_STATUS,(CSL_SemVal *) &semVal))
	//	{
	//		LOG_TRACE0("CSL_semHwControl error");
	//	}

	//	if ((semVal.semFree != CSL_SEM_FREE) && (semVal.semOwner == Core_Num ))
	//	{
	//		break;
	//	}

         if((!CSL_semIsFree (pThis->Sem_Number)) &&(CSL_semGetResourceOwner(pThis->Sem_Number)== Core_Num))
         {
        	 break;
         }
		else
		{
			//LOG_TRACE1( "HSEM: lock acquiring sem %d ", pThis->hSemHandle->semNum);
			;
			//TSK_yield();// DSPBIOS function
			ti_sysbios_knl_Task_yield__E();// SYSBIOS function

		}

	}
//	LOG_TRACE("HSem Locked %x", pThis->oParam.flags );
}


void HSEM_Unlock(Hsem *pThis)
{

	//volatile CSL_SemVal semVal; // not required for C6678

//	LOG_FATAL( "Testing HSem %x",pThis);

while(1)
	{
		//if (CSL_SOK != CSL_semHwControl(pThis->hSemHandle, CSL_SEM_CMD_FREE_DIRECT, NULL))
	//	{
		//	LOG_TRACE0("CSL_semGetHwStatus error");
	//	}
    //	if (CSL_SOK != CSL_semGetHwStatus(pThis->hSemHandle, CSL_SEM_QUERY_STATUS, (void *)&semVal ))
	//	{
		//	LOG_TRACE0("CSL_semGetHwStatus error");
	//	}
	//	if (semVal.semFree == CSL_SEM_FREE)
	if(CSL_semIsFree (pThis->Sem_Number))
		{
			break;
		}
		else
		{
			CSL_semReleaseSemaphore(pThis->Sem_Number);
			//LOG_TRACE1( "unlock waitng for sem %d" , pThis->hSemHandle->semNum);
	//		LOG_TRACE1( "unlock waitng for sem %d" , pThis->Sem_Number);
			//TSK_yield();// DSPBIOS function
	//		Task_yield();// SYSBIOS function

		}

		

	}



}
