

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
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Timer.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the users to have a APIs that will initialize Timers, gets 
//  Time Lapsed in us, ms and secs, 
//
//  Dependencies, Limitations, and Design Notes:
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
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



/**
 *   @file  csl_tmr.h
 *
 *   @brief   
 *      This is the main header file for the TIMER Module which defines
 *      all the data structures and exported API.
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

/** @defgroup CSL_TIMER_API TIMER
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 * The timer can be configured as a general-purpose 64-bit timer, dual general-purpose 32-bit
 * timers, or a watchdog timer. When configured as a dual 32-bit timers, each half can operate in
 * conjunction (chain mode) or independently (unchained mode) of each other. The timer can be
 * configured in one of three modes using the timer mode (TIMMODE) bits in the timer global control
 * register (TGCR): a 64-bit general-purpose (GP) timer, dual 32-bit timers (Timer Low and Timer
 * High), or a watchdog timer. When configured as dual 32-bit timers, each half can operate
 * dependently (chain mode) or independently (unchained mode) of each other. At reset, the timer is
 * configured as a 64-bit GP timer. The watchdog timer function can be enabled if desired, via the
 * TIMMODE bits in timer global control register (TGCR) and WDEN bit in the watchdog timer
 * control register WDTCR). Once the timer is configured as a watchdog timer, it cannot be reconfigured
 * as a regular timer until a device reset occurs. The timer has one input pin (TINPL) and
 * one output pin (TOUTL). The timer control register (TCR) controls the function of the input and
 * output pin.
 * The timers can be used to: time events, count events, generate pulses, interrupt the CPU, and
 * send synchronization events to the EDMA.
 *
 *  @subsection References
 *    -# Timer User's Guide SPRU818.pdf (December 2005)
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
 *   @file  cslr_tmr.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for TIMER
 *
 */


/* CSL Modification:
 *  The file has been modified from the AUTOGEN file for the following
 *  reasons:-
 *      a) Modified the header file includes to be RTSC compliant
 */


/*************************************************************************** Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint8 RSVD0[4];
    volatile Uint32 EMUMGT_CLKSPD;
    volatile Uint8 RSVD1[8];
    volatile Uint32 CNTLO;
    volatile Uint32 CNTHI;
    volatile Uint32 PRDLO;
    volatile Uint32 PRDHI;
    volatile Uint32 TCR;
    volatile Uint32 TGCR;
    volatile Uint32 WDTCR;
} CSL_TmrRegs;


/*************************************************************************** Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_TmrRegs             *CSL_TmrRegsOvly;


/*************************************************************************** Field Definition Macros
\**************************************************************************/

/* EMUMGT_CLKSPD */


/*----CLKDIV Tokens----*/




/* CNTLO */



/* CNTHI */



/* PRDLO */



/* PRDHI */



/* TCR */





/* Timer in stop mode */









/* Timer in stop mode */








/* TGCR */





/* Strat the timer */

/* the timer in reset mode */


/* Strat the timer */

/* the timer in reset mode */


/* WDTCR */


/*----WDKEY Tokens----*/



/*----WDEN Tokens----*/




/**
@defgroup CSL_TIMER_SYMBOL  TIMER Symbols Defined
@ingroup CSL_TIMER_API
*/
/**
@defgroup CSL_TIMER_DATASTRUCT  TIMER Data Structures
@ingroup CSL_TIMER_API
*/
/**
@defgroup CSL_TIMER_FUNCTION  TIMER Functions
@ingroup CSL_TIMER_API
*/
/**
@defgroup CSL_TIMER_ENUM TIMER Enumerated Data Types
@ingroup CSL_TIMER_API
*/

/**
@addtogroup CSL_TIMER_ENUM
@{
*/

/**
 * General purpose global type def declarations
 */

/**
 *  @brief This enum describes the commands used to control the GP timer through
 *  CSL_tmrHwControl()
 */
typedef enum {
    /**
     * @brief   Loads the GP Timer Period Register Low
     * @param   Uint32 *
     */
    CSL_TMR_CMD_LOAD_PRDLO = 0,

    /**
     * @brief   Loads the GP Timer Period Register High
     * @param   Uint32 *
     */
    CSL_TMR_CMD_LOAD_PRDHI = 1,

    /**
     * @brief   Loads the GP Timer Pre-scalar value for CNTHI
     * @param   Uint8 *
     */
    CSL_TMR_CMD_LOAD_PSCHI = 2,

    /**
     * @brief   Enable the GP timer Low
     * @param   CSL_TmrEnamode
     */
    CSL_TMR_CMD_START_TIMLO = 3,

    /**
     * @brief   Enable the GP timer High
     * @param   CSL_TmrEnamode
     */
    CSL_TMR_CMD_START_TIMHI = 4,

    /**
     * @brief   Stop the GP timer Low
     * @param   None
     */
    CSL_TMR_CMD_STOP_TIMLO = 5,

    /**
     * @brief   Stop the GP timer High
     * @param   None
     */
    CSL_TMR_CMD_STOP_TIMHI = 6,

    /**
     * @brief   Reset the GP timer Low
     * @param   None
     */
    CSL_TMR_CMD_RESET_TIMLO = 7,

    /**
     * @brief   Reset the GP timer High
     * @param   None
     */
    CSL_TMR_CMD_RESET_TIMHI = 8,

    /**
     * @brief   Start the timer in GPtimer64 OR Chained mode
     * @param   None
     */
    CSL_TMR_CMD_START64 = 9,

    /**
     * @brief   Stop the timer of GPtimer64 OR Chained
     * @param   CSL_TmrEnamode
     */
    CSL_TMR_CMD_STOP64 = 10,

    /**
     * @brief   Reset the timer of GPtimer64 OR Chained
     * @param   None
     */
    CSL_TMR_CMD_RESET64 = 11,

    /**
     * @brief	Enable the timer in watchdog mode
     * @param	CSL_TmrEnamode
     */
    CSL_TMR_CMD_START_WDT = 12,

    /**
     * @brief	Loads the watchdog key
     * @param	Uint16
     */
    CSL_TMR_CMD_LOAD_WDKEY = 13
} CSL_TmrHwControlCmd;

/**
 *  @brief This enum describes the commands used to get status of various parameters of the
 *  GP timer. These values are used in CSL_tmrGetHwStatus()
 */
typedef enum {
    /**
     * @brief   Gets the current value of the GP timer CNTLO register
     * @param   Uint32 *
     */
    CSL_TMR_QUERY_COUNT_LO = 0,

    /**
     * @brief   Gets the current value of the GP timer CNTHI register
     * @param   Uint32 *
     */
    CSL_TMR_QUERY_COUNT_HI = 1,
    /**
     * @brief   This query command returns the status
     *          about whether the CNTLO is running or stopped
     *
     * @param   CSL_TmrTstat
     */
    CSL_TMR_QUERY_TSTAT_LO = 2,

    /**
     * @brief   This query command returns the status
     *          about whether the CNTHI is running or stopped
     *
     * @param   CSL_TmrTstat
     */
    CSL_TMR_QUERY_TSTAT_HI = 3,

    /**
     * @brief	This query command returns the status about whether the timer
     *		is in watchdog mode or not
     * @param	CSL_WdflagBitStatus
     */
    CSL_TMR_QUERY_WDFLAG_STATUS = 4
} CSL_TmrHwStatusQuery;

/**
 *  @brief This enum describes whether the Timer Clock input is gated or not gated.
 */
typedef enum {
    /** timer input not gated */
    CSL_TMR_CLOCK_INP_NOGATE = 0,

    /** timer input gated */
    CSL_TMR_CLOCK_INP_GATE = 1
} CSL_TmrIpGate;

/**
 *  @brief This enum describes the Timer Clock source selection.
 */
typedef enum {
    /** timer clock INTERNAL source selection */
    CSL_TMR_CLKSRC_INTERNAL = 0,

    /** timer clock Timer input pin source selection */
    CSL_TMR_CLKSRC_TMRINP = 1
} CSL_TmrClksrc;

/**
 *  @brief This enum describes the enabling/disabling of Timer.
 */
typedef enum {
    /** The timer is disabled and maintains current value */
    CSL_TMR_ENAMODE_DISABLE = 0,

    /**  The timer is enabled one time */
    CSL_TMR_ENAMODE_ENABLE = 1,

    /**  The timer is enabled continuously */
    CSL_TMR_ENAMODE_CONT = 2
} CSL_TmrEnamode;

/**
 *  @brief This enum describes the Timer Clock cycles (1/2/3/4).
 */
typedef enum {
    /** One timer clock cycle */
    CSL_TMR_PWID_ONECLK = 0,

    /** Two timer clock cycle */
    CSL_TMR_PWID_TWOCLKS = 1,

    /** Three timer clock cycle */
    CSL_TMR_PWID_THREECLKS = 2,

    /** Four timer clock cycle */
    CSL_TMR_PWID_FOURCLKS = 3
} CSL_TmrPulseWidth;

/**
 *  @brief This enum describes the mode of Timer Clock (Pulse/Clock).
 */
typedef enum {
    /** Pulse mode */
    CSL_TMR_CP_PULSE = 0,

    /** Clock mode */
    CSL_TMR_CP_CLOCK = 1
} CSL_TmrClockPulse;

/**
 *  @brief This enum describes the Timer input inverter control
 */
typedef enum {
    /** Un inverted timer input drives timer */
    CSL_TMR_INVINP_UNINVERTED = 0,

    /** Inverted timer input drives timer */
    CSL_TMR_INVINP_INVERTED = 1
} CSL_TmrInvInp;

/**
 *  @brief This enum describes the Timer output inverter control
 */
typedef enum {
    /** Un inverted timer output */
    CSL_TMR_INVOUTP_UNINVERTED = 0,

    /** Inverted timer output */
    CSL_TMR_INVOUTP_INVERTED = 1
} CSL_TmrInvOutp;

/**
 *  @brief This enum describes the mode of Timer (GPT/WDT/Chained/Unchained).
 */
typedef enum {
    /** The timer is in 64-bit GP timer mode */
    CSL_TMR_TIMMODE_GPT = 0,

    /** The timer is in dual 32-bit timer, unchained mode */
    CSL_TMR_TIMMODE_DUAL_UNCHAINED = 1,

    /** The timer is in 64-bit Watchdog timer mode */
    CSL_TMR_TIMMODE_WDT = 2,

    /** The timer is in dual 32-bit timer, chained mode */
    CSL_TMR_TIMMODE_DUAL_CHAINED = 3
} CSL_TmrMode;

/**
 *  @brief This enum describes the reset condition of Timer (ON/OFF).
 */
typedef enum {
    /** timer TIMxx is in reset */
    CSL_TMR_TIMxxRS_RESET_ON = 0,

    /** timer CNTHI is not in reset. CNTHI can be used as a 32-bit timer */
    CSL_TMR_TIMxxRS_RESET_OFF = 1
} CSL_TmrState;

/**  @brief This enum describes the status of Timer.
 */
typedef enum {
    /** Timer status drives High */
    CSL_TMR_TSTAT_HIGH = 1,

    /** Timer status drives Low */
    CSL_TMR_TSTAT_LOW = 0
} CSL_TmrTstat;

/** @brief This enumeration describes the flag bit status of the timer in watchdog mode
 */
typedef enum {
	/** No watchdog timeout occurred */
	CSL_TMR_WDFLAG_NOTIMEOUT = 0,

	/** Watchdog timeout occurred */
	CSL_TMR_WDFLAG_TIMEOUT = 1
} CSL_TmrWdflagBitStatus;

/**
@}
*/

/** @addtogroup CSL_TIMER_DATASTRUCT
 @{ */

/**
 * @brief Hardware setup structure.
 */
typedef struct {
    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 tmrTimerPeriodLo;

    /** 32 bit load value to be loaded to Timer Period Register High */
    Uint32 tmrTimerPeriodHi;

    /** 32 bit load value to be loaded to Timer Counter Register Low */
    Uint32 tmrTimerCounterLo;

    /** 32 bit load value to be loaded to Timer Counter Register High */
    Uint32 tmrTimerCounterHi;

    /** TIEN determines if the timer clock is gated by the timer input.
     *  Applicable only when CLKSRC=0
     */
    CSL_TmrIpGate tmrIpGateHi;

    /** CLKSRC determines the selected clock source for the timer */
    CSL_TmrClksrc tmrClksrcHi;

    /** Pulse width. used in pulse mode (C/P_=0) by the timer */
    CSL_TmrPulseWidth tmrPulseWidthHi;

    /** Clock/Pulse mode for timerHigh output */
    CSL_TmrClockPulse tmrClockPulseHi;

    /** Timer input inverter control. Only affects operation
     *  if CLKSRC=1, Timer Input pin
     */
    CSL_TmrInvInp tmrInvInpHi;

    /** Timer output inverter control */
    CSL_TmrInvOutp tmrInvOutpHi;

    /** TIEN determines if the timer clock is gated by the timer input.
     *  Applicable only when CLKSRC=0
     */
    CSL_TmrIpGate tmrIpGateLo;

    /** CLKSRC determines the selected clock source for the timer */
    CSL_TmrClksrc tmrClksrcLo;

    /** Pulse width. used in pulse mode (C/P_=0) by the timer */
    CSL_TmrPulseWidth tmrPulseWidthLo;

    /** Clock/Pulse mode for timerLow output */
    CSL_TmrClockPulse tmrClockPulseLo;

    /** Timer input inverter control. Only affects operation
     *  if CLKSRC=1, Timer Input pin
     */
    CSL_TmrInvInp tmrInvInpLo;

    /** Timer output inverter control */
    CSL_TmrInvOutp tmrInvOutpLo;

    /** CNTHI pre-scalar counter specifies the count for CNTHI */
    Uint8 tmrPreScalarCounterHi;

    /** Configures the GP timer in GP mode or in
     *  general purpose timer mode or Dual 32 bit timer mode
     */
    CSL_TmrMode tmrTimerMode;
} CSL_TmrHwSetup;

/**
 *  @brief Config-structure Used to configure the GP timer using CSL_tmrHwSetupRaw()
 */
typedef struct {
    /** Timer Counter Register Low */
    Uint32 CNTLO;
    /** Timer Counter Register High */
    Uint32 CNTHI;
    /** Timer Period Register Low */
    Uint32 PRDLO;
    /** Timer Period Register High */
    Uint32 PRDHI;
    /** Timer Control Register */
    Uint32 TCR;
    /** Timer Global Control Register */
    Uint32 TGCR;
    /** Watchdog Timer Control Register */
    Uint32 WDTCR;
} CSL_TmrConfig;

/**
 * @brief Module specific context information. Present implementation of GP
 *        timer CSL doesn't have any context information.
 */
typedef struct {
    /** Context information of GP timer CSL.
     *  The below declaration is just a place-holder for future implementation.
     */
    Uint16 contextInfo;
} CSL_TmrContext;

/** @brief Module specific parameters. Present implementation of GP timer CSL
 *         doesn't have any module specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters. The below
     *  declaration is just a place-holder for future implementation.
     */
    CSL_BitMask16 flags;
} CSL_TmrParam;

/** @brief This structure contains the base-address information for the
 *         peripheral instance
 */
typedef struct {
    /** Base-address of the configuration registers of the peripheral
     */
    CSL_TmrRegsOvly regs;
} CSL_TmrBaseAddress;

/**
 * @brief  Watchdog timer object structure.
 */
typedef struct {
    /** Pointer to the register overlay structure of the GP timer */
    CSL_TmrRegsOvly regs;

    /** Instance of GP timer being referred by this object  */
    CSL_InstNum tmrNum;
} CSL_TmrObj;


/**
 * @brief This data type is used to return the handle to the CSL of the GP timer
 */
typedef CSL_TmrObj *CSL_TmrHandle;

/**
@}
*/

/**
@addtogroup CSL_TIMER_SYMBOL
@{
*/

/** @brief Default hardware setup parameters */

/** @brief Default values for config structure */

/**
@}
*/

/** @addtogroup CSL_TIMER_FUNCTION
 @{ */

/*******************************************************************************
 * Timer global function declarations
 ******************************************************************************/

extern CSL_Status CSL_tmrInit (
    CSL_TmrContext *pContext
);

extern CSL_TmrHandle CSL_tmrOpen (
    CSL_TmrObj   *tmrObj,
    CSL_InstNum  tmrNum,
    CSL_TmrParam *pTmrParam,
    CSL_Status   *status
);

extern CSL_Status CSL_tmrGetBaseAddress (
    CSL_InstNum        tmrNum,
    CSL_TmrParam       *pTmrParam,
    CSL_TmrBaseAddress *pBaseAddress
);

extern CSL_Status CSL_tmrClose (
    CSL_TmrHandle hTmr
);

extern CSL_Status CSL_tmrHwSetup (
    CSL_TmrHandle  hTmr,
    CSL_TmrHwSetup *hwSetup
);

extern CSL_Status CSL_tmrHwControl(
    CSL_TmrHandle       hTmr,
    CSL_TmrHwControlCmd cmd,
    void                *cmdArg
);

extern CSL_Status CSL_tmrGetHwStatus (
    CSL_TmrHandle        hTmr,
    CSL_TmrHwStatusQuery query,
    void                 *response
);

extern CSL_Status CSL_tmrHwSetupRaw (
    CSL_TmrHandle hTmr,
    CSL_TmrConfig *config
);

extern CSL_Status CSL_tmrGetHwSetup (
    CSL_TmrHandle  hTmr,
    CSL_TmrHwSetup *hwSetup
);

/**
@}
*/



//#include <ti/csl/src/intc/csl_intc.h>
//#include <ti/csl/src/intc/csl_intcAux.h>
/**
 *   @file  csl_tmrAux.h
 *
 *   @brief   
 *      This is the TIMER Auxilary Header File which exposes the various
 *      CSL Functional Layer API's to configure the TIMER Module.
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




/** @addtogroup CSL_TIMER_FUNCTION
 @{ */
        
/** ============================================================================
 *   @n@b CSL_tmrGetTimHiCount
 *
 *   @b Description
 *   @n This function gets the value of the CNTHI counter
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Pointer to the object that holds reference to the
                     instance of TIMER requested after the call
         countHi     Output parameter to get the CNTHI value
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n The argument countHi is populated with the contents of the CNTHI register
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  TMR_CNTHI_CNT
 *
 *   @b  Example
 *   @verbatim
        CSL_TmrHandle   hTmr;
        Unit32*         countHi;
        ...
        CSL_tmrGetTimHiCount(hTmr, &countHi);
        ...
     @endverbatim
 * ============================================================================
 */
static inline void CSL_tmrGetTimHiCount (CSL_TmrHandle hTmr,Uint32 *countHi)
{
    *countHi = (((hTmr->regs->CNTHI) & (0xFFFFFFFFu)) >> (0x00000000u));
}

/** ===========================================================================
 *   @n@b CSL_tmrGetTimLoCount
 *
 *   @b Description
 *   @n This function gets the value of the CNTLO counter
 *
 *   @b Arguments
 *   @verbatim
         hTmr       Pointer to the object that holds reference to the
                    instance of TIMER requested after the call
         countLo    Output parameter to get the CNTLO value
     @endverbatim
 *
 *   <b> Return Value </b>  
 *      None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n The argument countLo is populated with the contents of the CNTLO register
 *
 *   @b Reads
 *   @n TMR_CNTLO_CNT
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        Unit32        *countLo;
        ...
        CSL_tmrGetTimLoCount(hTmr, &countLo);
        ...
     @endverbatim
 * ============================================================================
 */
static inline void CSL_tmrGetTimLoCount (CSL_TmrHandle hTmr,Uint32* countLo)
{
    *countLo = (((hTmr->regs->CNTLO) & (0xFFFFFFFFu)) >> (0x00000000u));
}

/** ===========================================================================
 *   @n@b CSL_tmrGetTstatLoStatus
 *
 *   @b Description
 *   @n This function gets the status of the TINTLO
 *
 *   @b Arguments
 *   @verbatim
         hTmr   Pointer to the object that holds reference to the
                instance of TIMER requested after the call
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n CSL_TmrTstatLo - TINTLO status value
 *   @li CSL_TMR_TSTAT_LO_LOW  - Data low
 *   @li CSL_TMR_TSTAT_LO_HIGH - Data High
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Reads
 *   @n TMR_TCR_TSTAT_LO
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle  hTmr;
        CSL_TmrTstatLo statusLo;
        ...
        statusLo = CSL_tmrGetTstatLoStatus(hTmr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_TmrTstat CSL_tmrGetTstatLoStatus (CSL_TmrHandle hTmr)
{        
    return (CSL_TmrTstat)(((hTmr->regs->TCR) & (0x00000001u)) >> (0x00000000u));
}

/** ===========================================================================
 *   @n@b CSL_tmrGetTstatHiStatus
 *
 *   @b Description
 *   @n This function gets the status of the TINTHI
 *
 *   @b Arguments
 *   @verbatim
         hTmr   Pointer to the object that holds reference to the
                instance of TIMER requested after the call
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n CSL_TmrTstatHi - TINTHI status value
 *   @li CSL_TMR_TSTATHI_LOW  - Data low
 *   @li CSL_TMR_TSTATHI_HIGH - Data High
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Reads
 *   @n TMR_TCR_TSTAT_HI
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle  hTmr;
        CSL_TmrTstatHi statusHi;
        ...
        statusHi = CSL_tmrGetTstatHiStatus(hTmr);
        ...
     @endverbatim
 * ============================================================================
 */
static inline CSL_TmrTstat CSL_tmrGetTstatHiStatus (CSL_TmrHandle hTmr)
{
    return (CSL_TmrTstat)(((hTmr->regs->TCR) & (0x00010000u)) >> (0x00000010u));
}

/** ===========================================================================
 *   @n@b CSL_tmrGetWdflagStatus
 *
 *   @b Description
 *   @n This function gets the status of the WDFLAG
 *
 *   @b Arguments
 *   @verbatim
         hTmr   Pointer to the object that holds reference to the
                instance of TIMER requested after the call
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n CSL_TmrFlagBitStatus - WDFLAG status value
 *   @li  CSL_TMR_WDFLAG_NOTIMEOUT  - no watchdog timeout occurred
 *   @li  CSL_TMR_WDFLAG_TIMEOUT    - watchdog timeout occurred
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called and the
 *       Timer should be set in WATCHDOG mode
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Reads
 *   @n TMR_WDTCR_WDFLAG
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle          hTmr;
        CSL_TmrWdflagBitStatus status;
        ...
        status = CSL_tmrGetWdflagStatus(hTmr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_TmrWdflagBitStatus CSL_tmrGetWdflagStatus (CSL_TmrHandle hTmr)
{
    return (CSL_TmrWdflagBitStatus)(((hTmr->regs->WDTCR) & (0x00008000u)) >> (0x0000000Fu));
}

/** ============================================================================
 *   @n@b CSL_TmrLoadPrdLo
 *
 *   @b Description
 *      Loads the General purpose timer LOW period register.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Gptimer instance
         loadVal     Value to be loaded to the Gptimer period register Low
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n None
 *
 *   <b> Pre Condition </b>
 *   @n Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n Period register is loaded with the given value.
 *
 *   @b Writes
 *   @n TMR_PRDLO_PRDLO
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        Uint32       loadVal;

        loadVal = 10;
        CSL_TmrLoadPrdLo(hWdt, &loadVal);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrLoadPrdLo (CSL_TmrHandle hTmr,Uint32* loadVal)
{
    ((hTmr->regs->PRDLO) = ((hTmr->regs->PRDLO) & ~(0xFFFFFFFFu)) | (((*loadVal) << (0x00000000u)) & (0xFFFFFFFFu))); 
}

/** ============================================================================
 *   @n@b CSL_TmrLoadPrdHi
 *
 *   @b Description
 *      Loads the General purpose timer HIGH period register 
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the GPtimer instance
         loadVal     Value to be loaded to the Gptimer period register High
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  Period register is loaded with the given value.
 *
 *   @b Writes
 *   @n TMR_PRDHI_PRDHI
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle   hTmr;
        Uint32          loadVal;
        ...
        loadVal = 10;
        CSL_TmrLoadPrdHi(hWdt, &loadVal);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrLoadPrdHi (CSL_TmrHandle hTmr,Uint32* loadVal)
{
    ((hTmr->regs->PRDHI) = ((hTmr->regs->PRDHI) & ~(0xFFFFFFFFu)) | (((*loadVal) << (0x00000000u)) & (0xFFFFFFFFu))); 
}

/** ============================================================================
 *   @n@b CSL_TmrLoadPrescalarHi
 *
 *   @b Description
 *      Configures the prescalar values for the HIGH Timer.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer Instance
         loadVal     Value to be loaded to the PRESCALAR bits in the TGCR register
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  Gptimer pre scalar register is loaded with the given value.
 *
 *   @b Writes
 *   @n TMR_TGCR_PSCHI
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        Uint8         *loadVal;
        ...
        CSL_TmrLoadPrescalarHi(hWdt, &loadVal);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrLoadPrescalarHi (CSL_TmrHandle hTmr, Uint8* loadVal)
{
    ((hTmr->regs->TGCR) = ((hTmr->regs->TGCR) & ~(0x00000F00u)) | (((*loadVal) << (0x00000008u)) & (0x00000F00u)));
}

/** ============================================================================
 *   @n@b CSL_TmrStartHi
 *
 *   @b Description
 *      The functions starts the HIGH timer.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer instance
         countMode   Specifies the timer counting mode (OFF/CONTINIOUS/SINGLE Shot)
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The HIGH timer is brought out of reset and is activated in the 
 *       provided counting mode.
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMHIRS=1,TMR_TCR_ENAMODE_HI
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle  hTmr;
        ...
        CSL_TmrStartHi(hTmr, CSL_TMR_ENAMODE_ENABLE);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStartHi (CSL_TmrHandle hTmr, CSL_TmrEnamode countMode)
{
    /* Bring the HIGH Timer out of reset. */
    (((hTmr->regs->TGCR)) = (((hTmr->regs->TGCR)) & ~(0x00000002u)) | ((((0x00000001u)) << (0x00000001u)) & (0x00000002u)));

    /* Configure the HIGH TIMER with the appropriate counting mode. */
    ((hTmr->regs->TCR) = ((hTmr->regs->TCR) & ~(0x00C00000u)) | (((countMode) << (0x00000016u)) & (0x00C00000u)));
    return;
}

/** ============================================================================
 *   @n@b CSL_TmrStartLo
 *
 *   @b Description
 *      The function starts the LOW Timer.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Gptimer instance
         countMode   Specifies the timer counting mode (OFF/CONTINIOUS/SINGLE Shot)
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The LOW timer is brought out of reset and is activated in the 
 *       provided counting mode.
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMLORS=1,TMR_TCR_ENAMODE_LO
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle  hTmr;
        ...
        CSL_TmrStartLo(hTmr, CSL_TMR_ENAMODE_ENABLE);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStartLo (CSL_TmrHandle hTmr, CSL_TmrEnamode countMode)
{
    /* Bring the LOW Timer out of reset. */
    (((hTmr->regs->TGCR)) = (((hTmr->regs->TGCR)) & ~(0x00000001u)) | ((((0x00000001u)) << (0x00000000u)) & (0x00000001u)));

    /* Configure the LOW TIMER with the appropriate counting mode. */
    ((hTmr->regs->TCR) = ((hTmr->regs->TCR) & ~(0x000000C0u)) | (((countMode) << (0x00000006u)) & (0x000000C0u)));
}

/** ===========================================================================
 *   @n@b CSL_TmrStart64
 *
 *   @b Description
 *      The function starts the 64bit Timer by bringing both the LOW and HIGH
 *      timer out of reset.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Gptimer instance
         countMode   Specifies the timer counting mode (OFF/CONTINIOUS/SINGLE Shot)
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n   Set the GP OR chained timer counting mode and
 *		  timer Low and High reset register.
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMLORS=1,TMR_TGCR_TIMHIRS=1,
 *   @n TMR_TCR_ENAMODE_LO,TMR_TCR_ENAMODE_HI
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle  hTmr;
        ...
        CSL_TmrStart64(hTmr, CSL_TMR_ENAMODE_ENABLE);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStart64 (CSL_TmrHandle  hTmr, CSL_TmrEnamode countMode)
{
    Uint32 tmpReg;

    /* Bring the LOW and HIGH Timer outs of reset. */
    tmpReg = hTmr->regs->TGCR;
    (((tmpReg)) = (((tmpReg)) & ~(0x00000001u)) | ((((0x00000001u)) << (0x00000000u)) & (0x00000001u)));
    (((tmpReg)) = (((tmpReg)) & ~(0x00000002u)) | ((((0x00000001u)) << (0x00000001u)) & (0x00000002u)));
    hTmr->regs->TGCR = tmpReg; 

    /* Configure the counting mode for both the LOW and HIGH Timers. */
    tmpReg = hTmr->regs->TCR;
    ((tmpReg) = ((tmpReg) & ~(0x000000C0u)) | (((countMode) << (0x00000006u)) & (0x000000C0u)));
    ((tmpReg) = ((tmpReg) & ~(0x00C00000u)) | (((countMode) << (0x00000016u)) & (0x00C00000u)));
    hTmr->regs->TCR = tmpReg;
}

/** ===========================================================================
 *   @n@b CSL_TmrStopLo
 *
 *   @b Description
 *      The function stops the LOW Timer
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  Low Timer is disabled.
 *
 *   @b Writes
 *   @n TMR_TCR_ENAMODE_LO=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        ...
        CSL_TmrStopLo(hTmr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStopLo (CSL_TmrHandle hTmr)
{
    (((hTmr->regs->TCR)) = (((hTmr->regs->TCR)) & ~(0x000000C0u)) | ((((0x00000000u)) << (0x00000006u)) & (0x000000C0u)));
}

/** ===========================================================================
 *   @n@b CSL_TmrStopHi
 *
 *   @b Description
 *      The function stops the HIGH Timer
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  High Timer is disabled.
 *
 *   @b Writes
 *   @n TMR_TCR_ENAMODE_HI=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        ...
        CSL_TmrStopHi(hTmr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStopHi (CSL_TmrHandle hTmr)
{
    (((hTmr->regs->TCR)) = (((hTmr->regs->TCR)) & ~(0x00C00000u)) | ((((0x00000000u)) << (0x00000016u)) & (0x00C00000u)));
}

/** ===========================================================================
 *   @n@b CSL_TmrStop64
 *
 *   @b Description
 *      The function stops the 64bit timer.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The 64bit timer is stopped 
 *
 *   @b Writes
 *   @n TMR_TCR_ENAMODE_LO=0,TMR_TCR_ENAMODE_HI=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        ...
        CSL_TmrStop64(hWdt);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStop64 (CSL_TmrHandle hTmr)
{
    Uint32 tmpReg;

    /* Disable the LOW and HIGH Timers. */
    tmpReg = hTmr->regs->TCR;
    (((tmpReg)) = (((tmpReg)) & ~(0x000000C0u)) | ((((0x00000000u)) << (0x00000006u)) & (0x000000C0u)));
    (((tmpReg)) = (((tmpReg)) & ~(0x00C00000u)) | ((((0x00000000u)) << (0x00000016u)) & (0x00C00000u)));
    hTmr->regs->TCR = tmpReg;
}

/** ===========================================================================
 *   @n@b CSL_TmrResetHi
 *
 *   @b Description
 *      The HIGH timer is moved to RESET state.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the HIGH timer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n High timer is reset. 
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMHIRS=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        ...
        CSL_TmrResetHi(hTmr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrResetHi (CSL_TmrHandle hTmr)
{
    (((hTmr->regs->TGCR)) = (((hTmr->regs->TGCR)) & ~(0x00000002u)) | ((((0x00000000u)) << (0x00000001u)) & (0x00000002u)));
}

/** ===========================================================================
 *   @n@b CSL_TmrResetLo
 *
 *   @b Description
 *      The LOW timer is moved to RESET state.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Gptimer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n None
 *
 *   <b> Pre Condition </b>
 *   @n Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n Low Timer is Reset 
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMLORS=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        ...
        CSL_TmrResetLo(hWdt);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrResetLo (CSL_TmrHandle hTmr)
{
    (((hTmr->regs->TGCR)) = (((hTmr->regs->TGCR)) & ~(0x00000001u)) | ((((0x00000000u)) << (0x00000000u)) & (0x00000001u)));
}

/** ===========================================================================
 *   @n@b CSL_TmrReset64
 *
 *   @b Description
 *      The function resets the 64bit timer.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  64bit Timer is reset.
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMLORS=0,TMR_TGCR_TIMHIRS=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hTmr;
        ...
        CSL_TmrReset64(hTmr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrReset64 (CSL_TmrHandle hTmr)
{
    Uint32 tmpReg = hTmr->regs->TGCR;

    /* Move both the Low and High Timers into reset. */
    (((tmpReg)) = (((tmpReg)) & ~(0x00000001u)) | ((((0x00000000u)) << (0x00000000u)) & (0x00000001u)));
    (((tmpReg)) = (((tmpReg)) & ~(0x00000002u)) | ((((0x00000000u)) << (0x00000001u)) & (0x00000002u)));
    hTmr->regs->TGCR = tmpReg;
}

/** ===========================================================================
 *   @n@b CSL_TmrStartWdt
 *
 *   @b Description
 *      The function starts the timer in Watch Dog Mode.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Timer instance
         countMode   Specifies the timer counting mode (OFF/CONTINIOUS/SINGLE Shot)
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  Timer has been started in WATCH Dog Mode.
 *
 *   @b Writes
 *   @n TMR_TGCR_TIMLORS=1,TMR_TGCR_TIMHIRS=1,TMR_WDTCR_WDEN=1,TMR_TCR_ENAMODE_LO,TMR_TCR_ENAMODE_HI;
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle  hWdt;
        ...
        CSL_TmrStartWdt(hWdt, CSL_TMR_ENAMODE_CONT);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrStartWdt (CSL_TmrHandle  hTmr,CSL_TmrEnamode countMode)
{
    Uint32 tmpReg = hTmr->regs->TGCR;

    /* Bring the LOW and HIGH Timers out of reset. */
    (((tmpReg)) = (((tmpReg)) & ~(0x00000001u)) | ((((0x00000001u)) << (0x00000000u)) & (0x00000001u)));
    (((tmpReg)) = (((tmpReg)) & ~(0x00000002u)) | ((((0x00000001u)) << (0x00000001u)) & (0x00000002u)));
    hTmr->regs->TGCR = tmpReg;

    /* Enable the Watch Dog Timer */
    (((hTmr->regs->WDTCR)) = (((hTmr->regs->WDTCR)) & ~(0x00004000u)) | ((((0x00000001u)) << (0x0000000Eu)) & (0x00004000u)));

    /* Enable the LOW and HIGH Timers to operate */
    tmpReg = hTmr->regs->TCR;
    ((tmpReg) = ((tmpReg) & ~(0x000000C0u)) | (((countMode) << (0x00000006u)) & (0x000000C0u)));
    ((tmpReg) = ((tmpReg) & ~(0x00C00000u)) | (((countMode) << (0x00000016u)) & (0x00C00000u)));
    hTmr->regs->TCR = tmpReg;
}

/** ===========================================================================
 *   @n@b CSL_TmrLoadtWdkey
 *
 *   @b Description
 *      The function loads the watch dog timer with the appropriate key.
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the Gptimer instance
         cmd         Specifies the WATCHDOG Key. This can only be either of 
                     the following:-
                        - CSL_TMR_WDTCR_WDKEY_CMD1
                        - CSL_TMR_WDTCR_WDKEY_CMD2
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n   Loads the  WDKEY in WDTCR register.
 *
 *   @b Writes
 *   @n TMR_WDTCR_WDKEY
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hWdt;
        ...
        CSL_TmrLoadWdkey(hWdt, CSL_TMR_WDTCR_WDKEY_CMD1);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrLoadWdkey (CSL_TmrHandle hTmr, Uint16 cmd)
{
    ((hTmr->regs->WDTCR) = ((hTmr->regs->WDTCR) & ~(0xFFFF0000u)) | (((cmd) << (0x00000010u)) & (0xFFFF0000u)));
}

/** ===========================================================================
 *   @n@b CSL_TmrDisableWdt
 *
 *   @b Description
 *      The function disables the Watch Dog Timer.
 *
 *   @b Arguments
 *   @verbatim
        hTmr         Handle to the Timer instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *       None
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_tmrInit() and @a CSL_tmrOpen() must be called.
 *
 *   <b> Post Condition </b>
 *   @n   The Watch Dog timer is disabled.
 *
 *   @b Writes
 *   @n TMR_WDTCR_WDEN=0
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle hWdt;
        ...
        CSL_TmrDisableWdt(hWdt);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_TmrDisableWdt (CSL_TmrHandle hTmr)
{
    (((hTmr->regs->WDTCR)) = (((hTmr->regs->WDTCR)) & ~(0x00004000u)) | ((((0x00000000u)) << (0x0000000Eu)) & (0x00004000u)));
}

/**
@}
*/



extern CSL_Status CSL_tmrInit  ( CSL_TmrContext *  pContext   );

/*===============================================================================
//  Copyright(C):
//
//  FILENAME: <Intr.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  	To create haseless library to initialize, enable and
//		disable the Interrupt,
//  
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


//#include <ti/csl/src/intc/csl_intc.h>
//#include <ti/csl/src/intc/csl_intcAux.h>
//#include <ti/csl/csl_cic.h>//in CCS5 this include file is not present, that's why removed by remesh
/**
 *   @file  csl_cpIntc.h
 *
 *   @brief   
 *      This is the main header file for the CPINTC Module which defines
 *      all the data structures and exported API.
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

/** @defgroup CSL_CPINTC_API CPINTC
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 *  The CPINTC is the interrupt controller which handles the system interrupts
 *  for the host, processes & prioritizes them and then is responsible for 
 *  delivering these to the host.
 *
 * @subsection References
 *   -# CPINTC Architecture Specification.
 *
 * @subsection Assumptions
 *    The abbreviations CPINTC, cpintc have been used throughout this
 *    document to refer to Interrupt Controller.
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
 *      a) Modified Registers CH_MAP_REG0-CH_MAP_REG255 to an array of bytes of CHMAP[1024]
 *      b) Modified Registers HINT_MAP_REG0-HINT_MAP_REG63 to an array of HINTMAP[64]
 *      c) Modified Registers RAW_STATUS_REG0-RAW_STATUS_REG31 to an array of RAW_STATUS_REG[32]
 *      d) Modified Registers ENA_STATUS_REG0-ENA_STATUS_REG32 to an array of ENA_STATUS_REG[32]
 *      e) Modified Registers ENABLE_REG0-ENABLE_REG31 to an array of ENABLE_REG[32]
 *      f) Modified Registers ENABLE_CLR_REG0-ENABLE_CLR_REG31 to an array of ENABLE_CLR_REG[32]
 *      g) Modified Registers PRI_HINT_REG0-PRI_HINT_REG255 to an array of PRI_HINT_REG[256]
 *      h) Modified Registers POLARITY_REG0-POLARITY_REG31 to an array of POLARITY_REG[32]
 *      i) Modified Registers TYPE_REG0-TYPE_REG31 to an array of TYPE_REG[32]
 *      j) Modified Registers DBG_SELECT_REG0-DBG_SELECT_REG63 to an array of DBG_SELECT_REG[64]
 *      k) Modified Registers SECURE_ENABLE_REG0-SECURE_ENABLE_REG31 to an array of SECURE_ENABLE_REG[32]
 *      l) Modified Registers SECURE_ENABLE_CLR_REG0-SECURE_ENABLE_CLR_REG31 to an array of SECURE_ENABLE_CLR_REG[32]
 *      m) Modified Registers NEST_LEVEL_REG0-NEST_LEVEL_REG255 to an array of NEST_LEVEL_REG[256]
 *      n) Modified Registers ENABLE_HINT_REG0-ENABLE_HINT_REG7 to an array of ENABLE_HINT_REG[8]
 *      o) Modified Registers VECTOR_ADDRESS_REG_0-VECTOR_ADDRESS_REG_1023 to an array of VECTOR_ADDRESS_REG[1024]
 *      p) Modified the header file includes to be RTSC compliant
 */


/* Minimum unit = 1 byte */

/*************************************************************************** Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 REVISION_REG;
    volatile Uint32 CONTROL_REG;
    volatile Uint8 RSVD0[4];
    volatile Uint32 HOST_CONTROL_REG;
    volatile Uint32 GLOBAL_ENABLE_HINT_REG;
    volatile Uint8 RSVD1[8];
    volatile Uint32 GLB_NEST_LEVEL_REG;
    volatile Uint32 STATUS_SET_INDEX_REG;
    volatile Uint32 STATUS_CLR_INDEX_REG;
    volatile Uint32 ENABLE_SET_INDEX_REG;
    volatile Uint32 ENABLE_CLR_INDEX_REG;
    volatile Uint8 RSVD2[4];
    volatile Uint32 HINT_ENABLE_SET_INDEX_REG;
    volatile Uint32 HINT_ENABLE_CLR_INDEX_REG;
    volatile Uint8 RSVD3[28];
    volatile Uint32 VECTOR_NULL_REG;
    volatile Uint8 RSVD4[36];
    volatile Uint32 GLB_PRI_INTR_REG;
    volatile Uint32 GLB_VECTOR_ADDR_REG;
    volatile Uint8 RSVD5[8];
    volatile Uint32 GLOBAL_SECURE_ENABLE_REG;
    volatile Uint32 SECURE_PRI_INTR_REG;
    volatile Uint8 RSVD6[360];
    volatile Uint32 RAW_STATUS_REG[32];
    volatile Uint32 ENA_STATUS_REG[32];
    volatile Uint32 ENABLE_REG[32];
    volatile Uint32 ENABLE_CLR_REG[32];
    volatile Uint8  CH_MAP[1024];
    volatile Uint32 HINT_MAP[64];
    volatile Uint32 PRI_HINT_REG[256];
    volatile Uint32 POLARITY_REG[32];
    volatile Uint32 TYPE_REG[32];
    volatile Uint8 RSVD7[256];
    volatile Uint32 DBG_SELECT_REG[64];
    volatile Uint32 SECURE_ENABLE_REG[32];
    volatile Uint32 SECURE_ENABLE_CLR_REG[32];
    volatile Uint32 NEST_LEVEL_REG[256];
    volatile Uint32 ENABLE_HINT_REG[8];
    volatile Uint8 RSVD8[2784];
    volatile Uint32 VECTOR_ADDRESS_REG[1024];
} CSL_CPINTCRegs;

/*************************************************************************** Field Definition Macros
\**************************************************************************/

/* revision_reg */








/* control_reg */





/* host_control_reg */



/* global_enable_hint_reg */



/* glb_nest_level_reg */



/* status_set_index_reg */



/* status_clr_index_reg */



/* enable_set_index_reg */



/* enable_clr_index_reg */



/* hint_enable_set_index_reg */



/* hint_enable_clr_index_reg */



/* vector_null_reg */



/* glb_pri_intr_reg */




/* glb_vector_addr_reg */



/* global_secure_enable_reg */




/* secure_pri_intr_reg */




/* raw_status_reg0 */


































/* raw_status_reg1 */


































/* raw_status_reg2 */


































/* raw_status_reg3 */


































/* raw_status_reg4 */


































/* raw_status_reg5 */


































/* raw_status_reg6 */


































/* raw_status_reg7 */


































/* raw_status_reg8 */


































/* raw_status_reg9 */


































/* raw_status_reg10 */


































/* raw_status_reg11 */


































/* raw_status_reg12 */


































/* raw_status_reg13 */


































/* raw_status_reg14 */


































/* raw_status_reg15 */


































/* raw_status_reg16 */


































/* raw_status_reg17 */


































/* raw_status_reg18 */


































/* raw_status_reg19 */


































/* raw_status_reg20 */


































/* raw_status_reg21 */


































/* raw_status_reg22 */


































/* raw_status_reg23 */


































/* raw_status_reg24 */


































/* raw_status_reg25 */


































/* raw_status_reg26 */


































/* raw_status_reg27 */


































/* raw_status_reg28 */


































/* raw_status_reg29 */


































/* raw_status_reg30 */


































/* raw_status_reg31 */


































/* ena_status_reg0 */


































/* ena_status_reg1 */


































/* ena_status_reg2 */


































/* ena_status_reg3 */


































/* ena_status_reg4 */


































/* ena_status_reg5 */


































/* ena_status_reg6 */


































/* ena_status_reg7 */


































/* ena_status_reg8 */


































/* ena_status_reg9 */


































/* ena_status_reg10 */


































/* ena_status_reg11 */


































/* ena_status_reg12 */


































/* ena_status_reg13 */


































/* ena_status_reg14 */


































/* ena_status_reg15 */


































/* ena_status_reg16 */


































/* ena_status_reg17 */


































/* ena_status_reg18 */


































/* ena_status_reg19 */


































/* ena_status_reg20 */


































/* ena_status_reg21 */


































/* ena_status_reg22 */


































/* ena_status_reg23 */


































/* ena_status_reg24 */


































/* ena_status_reg25 */


































/* ena_status_reg26 */


































/* ena_status_reg27 */


































/* ena_status_reg28 */


































/* ena_status_reg29 */


































/* ena_status_reg30 */


































/* ena_status_reg31 */


































/* enable_reg0 */


































/* enable_reg1 */


































/* enable_reg2 */


































/* enable_reg3 */


































/* enable_reg4 */


































/* enable_reg5 */


































/* enable_reg6 */


































/* enable_reg7 */


































/* enable_reg8 */


































/* enable_reg9 */


































/* enable_reg10 */


































/* enable_reg11 */


































/* enable_reg12 */


































/* enable_reg13 */


































/* enable_reg14 */


































/* enable_reg15 */


































/* enable_reg16 */


































/* enable_reg17 */


































/* enable_reg18 */


































/* enable_reg19 */


































/* enable_reg20 */


































/* enable_reg21 */


































/* enable_reg22 */


































/* enable_reg23 */


































/* enable_reg24 */


































/* enable_reg25 */


































/* enable_reg26 */


































/* enable_reg27 */


































/* enable_reg28 */


































/* enable_reg29 */


































/* enable_reg30 */


































/* enable_reg31 */


































/* enable_clr_reg0 */


































/* enable_clr_reg1 */


































/* enable_clr_reg2 */


































/* enable_clr_reg3 */


































/* enable_clr_reg4 */


































/* enable_clr_reg5 */


































/* enable_clr_reg6 */


































/* enable_clr_reg7 */


































/* enable_clr_reg8 */


































/* enable_clr_reg9 */


































/* enable_clr_reg10 */


































/* enable_clr_reg11 */


































/* enable_clr_reg12 */


































/* enable_clr_reg13 */


































/* enable_clr_reg14 */


































/* enable_clr_reg15 */


































/* enable_clr_reg16 */


































/* enable_clr_reg17 */


































/* enable_clr_reg18 */


































/* enable_clr_reg19 */


































/* enable_clr_reg20 */


































/* enable_clr_reg21 */


































/* enable_clr_reg22 */


































/* enable_clr_reg23 */


































/* enable_clr_reg24 */


































/* enable_clr_reg25 */


































/* enable_clr_reg26 */


































/* enable_clr_reg27 */


































/* enable_clr_reg28 */


































/* enable_clr_reg29 */


































/* enable_clr_reg30 */


































/* enable_clr_reg31 */


































/* ch_map_reg0 */






/* ch_map_reg1 */






/* ch_map_reg2 */






/* ch_map_reg3 */






/* ch_map_reg4 */






/* ch_map_reg5 */






/* ch_map_reg6 */






/* ch_map_reg7 */






/* ch_map_reg8 */






/* ch_map_reg9 */






/* ch_map_reg10 */






/* ch_map_reg11 */






/* ch_map_reg12 */






/* ch_map_reg13 */






/* ch_map_reg14 */






/* ch_map_reg15 */






/* ch_map_reg16 */






/* ch_map_reg17 */






/* ch_map_reg18 */






/* ch_map_reg19 */






/* ch_map_reg20 */






/* ch_map_reg21 */






/* ch_map_reg22 */






/* ch_map_reg23 */






/* ch_map_reg24 */






/* ch_map_reg25 */






/* ch_map_reg26 */






/* ch_map_reg27 */






/* ch_map_reg28 */






/* ch_map_reg29 */






/* ch_map_reg30 */






/* ch_map_reg31 */






/* ch_map_reg32 */






/* ch_map_reg33 */






/* ch_map_reg34 */






/* ch_map_reg35 */






/* ch_map_reg36 */






/* ch_map_reg37 */






/* ch_map_reg38 */






/* ch_map_reg39 */






/* ch_map_reg40 */






/* ch_map_reg41 */






/* ch_map_reg42 */






/* ch_map_reg43 */






/* ch_map_reg44 */






/* ch_map_reg45 */






/* ch_map_reg46 */






/* ch_map_reg47 */






/* ch_map_reg48 */






/* ch_map_reg49 */






/* ch_map_reg50 */






/* ch_map_reg51 */






/* ch_map_reg52 */






/* ch_map_reg53 */






/* ch_map_reg54 */






/* ch_map_reg55 */






/* ch_map_reg56 */






/* ch_map_reg57 */






/* ch_map_reg58 */






/* ch_map_reg59 */






/* ch_map_reg60 */






/* ch_map_reg61 */






/* ch_map_reg62 */






/* ch_map_reg63 */






/* ch_map_reg64 */






/* ch_map_reg65 */






/* ch_map_reg66 */






/* ch_map_reg67 */






/* ch_map_reg68 */






/* ch_map_reg69 */






/* ch_map_reg70 */






/* ch_map_reg71 */






/* ch_map_reg72 */






/* ch_map_reg73 */






/* ch_map_reg74 */






/* ch_map_reg75 */






/* ch_map_reg76 */






/* ch_map_reg77 */






/* ch_map_reg78 */






/* ch_map_reg79 */






/* ch_map_reg80 */






/* ch_map_reg81 */






/* ch_map_reg82 */






/* ch_map_reg83 */






/* ch_map_reg84 */






/* ch_map_reg85 */






/* ch_map_reg86 */






/* ch_map_reg87 */






/* ch_map_reg88 */






/* ch_map_reg89 */






/* ch_map_reg90 */






/* ch_map_reg91 */






/* ch_map_reg92 */






/* ch_map_reg93 */






/* ch_map_reg94 */






/* ch_map_reg95 */






/* ch_map_reg96 */






/* ch_map_reg97 */






/* ch_map_reg98 */






/* ch_map_reg99 */






/* ch_map_reg100 */






/* ch_map_reg101 */






/* ch_map_reg102 */






/* ch_map_reg103 */






/* ch_map_reg104 */






/* ch_map_reg105 */






/* ch_map_reg106 */






/* ch_map_reg107 */






/* ch_map_reg108 */






/* ch_map_reg109 */






/* ch_map_reg110 */






/* ch_map_reg111 */






/* ch_map_reg112 */






/* ch_map_reg113 */






/* ch_map_reg114 */






/* ch_map_reg115 */






/* ch_map_reg116 */






/* ch_map_reg117 */






/* ch_map_reg118 */






/* ch_map_reg119 */






/* ch_map_reg120 */






/* ch_map_reg121 */






/* ch_map_reg122 */






/* ch_map_reg123 */






/* ch_map_reg124 */






/* ch_map_reg125 */






/* ch_map_reg126 */






/* ch_map_reg127 */






/* ch_map_reg128 */






/* ch_map_reg129 */






/* ch_map_reg130 */






/* ch_map_reg131 */






/* ch_map_reg132 */






/* ch_map_reg133 */






/* ch_map_reg134 */






/* ch_map_reg135 */






/* ch_map_reg136 */






/* ch_map_reg137 */






/* ch_map_reg138 */






/* ch_map_reg139 */






/* ch_map_reg140 */






/* ch_map_reg141 */






/* ch_map_reg142 */






/* ch_map_reg143 */






/* ch_map_reg144 */






/* ch_map_reg145 */






/* ch_map_reg146 */






/* ch_map_reg147 */






/* ch_map_reg148 */






/* ch_map_reg149 */






/* ch_map_reg150 */






/* ch_map_reg151 */






/* ch_map_reg152 */






/* ch_map_reg153 */






/* ch_map_reg154 */






/* ch_map_reg155 */






/* ch_map_reg156 */






/* ch_map_reg157 */






/* ch_map_reg158 */






/* ch_map_reg159 */






/* ch_map_reg160 */






/* ch_map_reg161 */






/* ch_map_reg162 */






/* ch_map_reg163 */






/* ch_map_reg164 */






/* ch_map_reg165 */






/* ch_map_reg166 */






/* ch_map_reg167 */






/* ch_map_reg168 */






/* ch_map_reg169 */






/* ch_map_reg170 */






/* ch_map_reg171 */






/* ch_map_reg172 */






/* ch_map_reg173 */






/* ch_map_reg174 */






/* ch_map_reg175 */






/* ch_map_reg176 */






/* ch_map_reg177 */






/* ch_map_reg178 */






/* ch_map_reg179 */






/* ch_map_reg180 */






/* ch_map_reg181 */






/* ch_map_reg182 */






/* ch_map_reg183 */






/* ch_map_reg184 */






/* ch_map_reg185 */






/* ch_map_reg186 */






/* ch_map_reg187 */






/* ch_map_reg188 */






/* ch_map_reg189 */






/* ch_map_reg190 */






/* ch_map_reg191 */






/* ch_map_reg192 */






/* ch_map_reg193 */






/* ch_map_reg194 */






/* ch_map_reg195 */






/* ch_map_reg196 */






/* ch_map_reg197 */






/* ch_map_reg198 */






/* ch_map_reg199 */






/* ch_map_reg200 */






/* ch_map_reg201 */






/* ch_map_reg202 */






/* ch_map_reg203 */






/* ch_map_reg204 */






/* ch_map_reg205 */






/* ch_map_reg206 */






/* ch_map_reg207 */






/* ch_map_reg208 */






/* ch_map_reg209 */






/* ch_map_reg210 */






/* ch_map_reg211 */






/* ch_map_reg212 */






/* ch_map_reg213 */






/* ch_map_reg214 */






/* ch_map_reg215 */






/* ch_map_reg216 */






/* ch_map_reg217 */






/* ch_map_reg218 */






/* ch_map_reg219 */






/* ch_map_reg220 */






/* ch_map_reg221 */






/* ch_map_reg222 */






/* ch_map_reg223 */






/* ch_map_reg224 */






/* ch_map_reg225 */






/* ch_map_reg226 */






/* ch_map_reg227 */






/* ch_map_reg228 */






/* ch_map_reg229 */






/* ch_map_reg230 */






/* ch_map_reg231 */






/* ch_map_reg232 */






/* ch_map_reg233 */






/* ch_map_reg234 */






/* ch_map_reg235 */






/* ch_map_reg236 */






/* ch_map_reg237 */






/* ch_map_reg238 */






/* ch_map_reg239 */






/* ch_map_reg240 */






/* ch_map_reg241 */






/* ch_map_reg242 */






/* ch_map_reg243 */






/* ch_map_reg244 */






/* ch_map_reg245 */






/* ch_map_reg246 */






/* ch_map_reg247 */






/* ch_map_reg248 */






/* ch_map_reg249 */






/* ch_map_reg250 */






/* ch_map_reg251 */






/* ch_map_reg252 */






/* ch_map_reg253 */






/* ch_map_reg254 */






/* ch_map_reg255 */






/* hint_map_reg0 */






/* hint_map_reg1 */






/* hint_map_reg2 */






/* hint_map_reg3 */






/* hint_map_reg4 */






/* hint_map_reg5 */






/* hint_map_reg6 */






/* hint_map_reg7 */






/* hint_map_reg8 */






/* hint_map_reg9 */






/* hint_map_reg10 */






/* hint_map_reg11 */






/* hint_map_reg12 */






/* hint_map_reg13 */






/* hint_map_reg14 */






/* hint_map_reg15 */






/* hint_map_reg16 */






/* hint_map_reg17 */






/* hint_map_reg18 */






/* hint_map_reg19 */






/* hint_map_reg20 */






/* hint_map_reg21 */






/* hint_map_reg22 */






/* hint_map_reg23 */






/* hint_map_reg24 */






/* hint_map_reg25 */






/* hint_map_reg26 */






/* hint_map_reg27 */






/* hint_map_reg28 */






/* hint_map_reg29 */






/* hint_map_reg30 */






/* hint_map_reg31 */






/* hint_map_reg32 */






/* hint_map_reg33 */






/* hint_map_reg34 */






/* hint_map_reg35 */






/* hint_map_reg36 */






/* hint_map_reg37 */






/* hint_map_reg38 */






/* hint_map_reg39 */






/* hint_map_reg40 */






/* hint_map_reg41 */






/* hint_map_reg42 */






/* hint_map_reg43 */






/* hint_map_reg44 */






/* hint_map_reg45 */






/* hint_map_reg46 */






/* hint_map_reg47 */






/* hint_map_reg48 */






/* hint_map_reg49 */






/* hint_map_reg50 */






/* hint_map_reg51 */






/* hint_map_reg52 */






/* hint_map_reg53 */






/* hint_map_reg54 */






/* hint_map_reg55 */






/* hint_map_reg56 */






/* hint_map_reg57 */






/* hint_map_reg58 */






/* hint_map_reg59 */






/* hint_map_reg60 */






/* hint_map_reg61 */






/* hint_map_reg62 */






/* hint_map_reg63 */






/* pri_hint_reg0 */




/* pri_hint_reg1 */




/* pri_hint_reg2 */




/* pri_hint_reg3 */




/* pri_hint_reg4 */




/* pri_hint_reg5 */




/* pri_hint_reg6 */




/* pri_hint_reg7 */




/* pri_hint_reg8 */




/* pri_hint_reg9 */




/* pri_hint_reg10 */




/* pri_hint_reg11 */




/* pri_hint_reg12 */




/* pri_hint_reg13 */




/* pri_hint_reg14 */




/* pri_hint_reg15 */




/* pri_hint_reg16 */




/* pri_hint_reg17 */




/* pri_hint_reg18 */




/* pri_hint_reg19 */




/* pri_hint_reg20 */




/* pri_hint_reg21 */




/* pri_hint_reg22 */




/* pri_hint_reg23 */




/* pri_hint_reg24 */




/* pri_hint_reg25 */




/* pri_hint_reg26 */




/* pri_hint_reg27 */




/* pri_hint_reg28 */




/* pri_hint_reg29 */




/* pri_hint_reg30 */




/* pri_hint_reg31 */




/* pri_hint_reg32 */




/* pri_hint_reg33 */




/* pri_hint_reg34 */




/* pri_hint_reg35 */




/* pri_hint_reg36 */




/* pri_hint_reg37 */




/* pri_hint_reg38 */




/* pri_hint_reg39 */




/* pri_hint_reg40 */




/* pri_hint_reg41 */




/* pri_hint_reg42 */




/* pri_hint_reg43 */




/* pri_hint_reg44 */




/* pri_hint_reg45 */




/* pri_hint_reg46 */




/* pri_hint_reg47 */




/* pri_hint_reg48 */




/* pri_hint_reg49 */




/* pri_hint_reg50 */




/* pri_hint_reg51 */




/* pri_hint_reg52 */




/* pri_hint_reg53 */




/* pri_hint_reg54 */




/* pri_hint_reg55 */




/* pri_hint_reg56 */




/* pri_hint_reg57 */




/* pri_hint_reg58 */




/* pri_hint_reg59 */




/* pri_hint_reg60 */




/* pri_hint_reg61 */




/* pri_hint_reg62 */




/* pri_hint_reg63 */




/* pri_hint_reg64 */




/* pri_hint_reg65 */




/* pri_hint_reg66 */




/* pri_hint_reg67 */




/* pri_hint_reg68 */




/* pri_hint_reg69 */




/* pri_hint_reg70 */




/* pri_hint_reg71 */




/* pri_hint_reg72 */




/* pri_hint_reg73 */




/* pri_hint_reg74 */




/* pri_hint_reg75 */




/* pri_hint_reg76 */




/* pri_hint_reg77 */




/* pri_hint_reg78 */




/* pri_hint_reg79 */




/* pri_hint_reg80 */




/* pri_hint_reg81 */




/* pri_hint_reg82 */




/* pri_hint_reg83 */




/* pri_hint_reg84 */




/* pri_hint_reg85 */




/* pri_hint_reg86 */




/* pri_hint_reg87 */




/* pri_hint_reg88 */




/* pri_hint_reg89 */




/* pri_hint_reg90 */




/* pri_hint_reg91 */




/* pri_hint_reg92 */




/* pri_hint_reg93 */




/* pri_hint_reg94 */




/* pri_hint_reg95 */




/* pri_hint_reg96 */




/* pri_hint_reg97 */




/* pri_hint_reg98 */




/* pri_hint_reg99 */




/* pri_hint_reg100 */




/* pri_hint_reg101 */




/* pri_hint_reg102 */




/* pri_hint_reg103 */




/* pri_hint_reg104 */




/* pri_hint_reg105 */




/* pri_hint_reg106 */




/* pri_hint_reg107 */




/* pri_hint_reg108 */




/* pri_hint_reg109 */




/* pri_hint_reg110 */




/* pri_hint_reg111 */




/* pri_hint_reg112 */




/* pri_hint_reg113 */




/* pri_hint_reg114 */




/* pri_hint_reg115 */




/* pri_hint_reg116 */




/* pri_hint_reg117 */




/* pri_hint_reg118 */




/* pri_hint_reg119 */




/* pri_hint_reg120 */




/* pri_hint_reg121 */




/* pri_hint_reg122 */




/* pri_hint_reg123 */




/* pri_hint_reg124 */




/* pri_hint_reg125 */




/* pri_hint_reg126 */




/* pri_hint_reg127 */




/* pri_hint_reg128 */




/* pri_hint_reg129 */




/* pri_hint_reg130 */




/* pri_hint_reg131 */




/* pri_hint_reg132 */




/* pri_hint_reg133 */




/* pri_hint_reg134 */




/* pri_hint_reg135 */




/* pri_hint_reg136 */




/* pri_hint_reg137 */




/* pri_hint_reg138 */




/* pri_hint_reg139 */




/* pri_hint_reg140 */




/* pri_hint_reg141 */




/* pri_hint_reg142 */




/* pri_hint_reg143 */




/* pri_hint_reg144 */




/* pri_hint_reg145 */




/* pri_hint_reg146 */




/* pri_hint_reg147 */




/* pri_hint_reg148 */




/* pri_hint_reg149 */




/* pri_hint_reg150 */




/* pri_hint_reg151 */




/* pri_hint_reg152 */




/* pri_hint_reg153 */




/* pri_hint_reg154 */




/* pri_hint_reg155 */




/* pri_hint_reg156 */




/* pri_hint_reg157 */




/* pri_hint_reg158 */




/* pri_hint_reg159 */




/* pri_hint_reg160 */




/* pri_hint_reg161 */




/* pri_hint_reg162 */




/* pri_hint_reg163 */




/* pri_hint_reg164 */




/* pri_hint_reg165 */




/* pri_hint_reg166 */




/* pri_hint_reg167 */




/* pri_hint_reg168 */




/* pri_hint_reg169 */




/* pri_hint_reg170 */




/* pri_hint_reg171 */




/* pri_hint_reg172 */




/* pri_hint_reg173 */




/* pri_hint_reg174 */




/* pri_hint_reg175 */




/* pri_hint_reg176 */




/* pri_hint_reg177 */




/* pri_hint_reg178 */




/* pri_hint_reg179 */




/* pri_hint_reg180 */




/* pri_hint_reg181 */




/* pri_hint_reg182 */




/* pri_hint_reg183 */




/* pri_hint_reg184 */




/* pri_hint_reg185 */




/* pri_hint_reg186 */




/* pri_hint_reg187 */




/* pri_hint_reg188 */




/* pri_hint_reg189 */




/* pri_hint_reg190 */




/* pri_hint_reg191 */




/* pri_hint_reg192 */




/* pri_hint_reg193 */




/* pri_hint_reg194 */




/* pri_hint_reg195 */




/* pri_hint_reg196 */




/* pri_hint_reg197 */




/* pri_hint_reg198 */




/* pri_hint_reg199 */




/* pri_hint_reg200 */




/* pri_hint_reg201 */




/* pri_hint_reg202 */




/* pri_hint_reg203 */




/* pri_hint_reg204 */




/* pri_hint_reg205 */




/* pri_hint_reg206 */




/* pri_hint_reg207 */




/* pri_hint_reg208 */




/* pri_hint_reg209 */




/* pri_hint_reg210 */




/* pri_hint_reg211 */




/* pri_hint_reg212 */




/* pri_hint_reg213 */




/* pri_hint_reg214 */




/* pri_hint_reg215 */




/* pri_hint_reg216 */




/* pri_hint_reg217 */




/* pri_hint_reg218 */




/* pri_hint_reg219 */




/* pri_hint_reg220 */




/* pri_hint_reg221 */




/* pri_hint_reg222 */




/* pri_hint_reg223 */




/* pri_hint_reg224 */




/* pri_hint_reg225 */




/* pri_hint_reg226 */




/* pri_hint_reg227 */




/* pri_hint_reg228 */




/* pri_hint_reg229 */




/* pri_hint_reg230 */




/* pri_hint_reg231 */




/* pri_hint_reg232 */




/* pri_hint_reg233 */




/* pri_hint_reg234 */




/* pri_hint_reg235 */




/* pri_hint_reg236 */




/* pri_hint_reg237 */




/* pri_hint_reg238 */




/* pri_hint_reg239 */




/* pri_hint_reg240 */




/* pri_hint_reg241 */




/* pri_hint_reg242 */




/* pri_hint_reg243 */




/* pri_hint_reg244 */




/* pri_hint_reg245 */




/* pri_hint_reg246 */




/* pri_hint_reg247 */




/* pri_hint_reg248 */




/* pri_hint_reg249 */




/* pri_hint_reg250 */




/* pri_hint_reg251 */




/* pri_hint_reg252 */




/* pri_hint_reg253 */




/* pri_hint_reg254 */




/* pri_hint_reg255 */




/* polarity_reg0 */


































/* polarity_reg1 */


































/* polarity_reg2 */


































/* polarity_reg3 */


































/* polarity_reg4 */


































/* polarity_reg5 */


































/* polarity_reg6 */


































/* polarity_reg7 */


































/* polarity_reg8 */


































/* polarity_reg9 */


































/* polarity_reg10 */


































/* polarity_reg11 */


































/* polarity_reg12 */


































/* polarity_reg13 */


































/* polarity_reg14 */


































/* polarity_reg15 */


































/* polarity_reg16 */


































/* polarity_reg17 */


































/* polarity_reg18 */


































/* polarity_reg19 */


































/* polarity_reg20 */


































/* polarity_reg21 */


































/* polarity_reg22 */


































/* polarity_reg23 */


































/* polarity_reg24 */


































/* polarity_reg25 */


































/* polarity_reg26 */


































/* polarity_reg27 */


































/* polarity_reg28 */


































/* polarity_reg29 */


































/* polarity_reg30 */


































/* polarity_reg31 */


































/* type_reg0 */


































/* type_reg1 */


































/* type_reg2 */


































/* type_reg3 */


































/* type_reg4 */


































/* type_reg5 */


































/* type_reg6 */


































/* type_reg7 */


































/* type_reg8 */


































/* type_reg9 */


































/* type_reg10 */


































/* type_reg11 */


































/* type_reg12 */


































/* type_reg13 */


































/* type_reg14 */


































/* type_reg15 */


































/* type_reg16 */


































/* type_reg17 */


































/* type_reg18 */


































/* type_reg19 */


































/* type_reg20 */


































/* type_reg21 */


































/* type_reg22 */


































/* type_reg23 */


































/* type_reg24 */


































/* type_reg25 */


































/* type_reg26 */


































/* type_reg27 */


































/* type_reg28 */


































/* type_reg29 */


































/* type_reg30 */


































/* type_reg31 */


































/* dbg_select_reg0 */




/* dbg_select_reg1 */




/* dbg_select_reg2 */




/* dbg_select_reg3 */




/* dbg_select_reg4 */




/* dbg_select_reg5 */




/* dbg_select_reg6 */




/* dbg_select_reg7 */




/* dbg_select_reg8 */




/* dbg_select_reg9 */




/* dbg_select_reg10 */




/* dbg_select_reg11 */




/* dbg_select_reg12 */




/* dbg_select_reg13 */




/* dbg_select_reg14 */




/* dbg_select_reg15 */




/* dbg_select_reg16 */




/* dbg_select_reg17 */




/* dbg_select_reg18 */




/* dbg_select_reg19 */




/* dbg_select_reg20 */




/* dbg_select_reg21 */




/* dbg_select_reg22 */




/* dbg_select_reg23 */




/* dbg_select_reg24 */




/* dbg_select_reg25 */




/* dbg_select_reg26 */




/* dbg_select_reg27 */




/* dbg_select_reg28 */




/* dbg_select_reg29 */




/* dbg_select_reg30 */




/* dbg_select_reg31 */




/* dbg_select_reg32 */




/* dbg_select_reg33 */




/* dbg_select_reg34 */




/* dbg_select_reg35 */




/* dbg_select_reg36 */




/* dbg_select_reg37 */




/* dbg_select_reg38 */




/* dbg_select_reg39 */




/* dbg_select_reg40 */




/* dbg_select_reg41 */




/* dbg_select_reg42 */




/* dbg_select_reg43 */




/* dbg_select_reg44 */




/* dbg_select_reg45 */




/* dbg_select_reg46 */




/* dbg_select_reg47 */




/* dbg_select_reg48 */




/* dbg_select_reg49 */




/* dbg_select_reg50 */




/* dbg_select_reg51 */




/* dbg_select_reg52 */




/* dbg_select_reg53 */




/* dbg_select_reg54 */




/* dbg_select_reg55 */




/* dbg_select_reg56 */




/* dbg_select_reg57 */




/* dbg_select_reg58 */




/* dbg_select_reg59 */




/* dbg_select_reg60 */




/* dbg_select_reg61 */




/* dbg_select_reg62 */




/* dbg_select_reg63 */




/* secure_enable_reg0 */


































/* secure_enable_reg1 */


































/* secure_enable_reg2 */


































/* secure_enable_reg3 */


































/* secure_enable_reg4 */


































/* secure_enable_reg5 */


































/* secure_enable_reg6 */


































/* secure_enable_reg7 */


































/* secure_enable_reg8 */


































/* secure_enable_reg9 */


































/* secure_enable_reg10 */


































/* secure_enable_reg11 */


































/* secure_enable_reg12 */


































/* secure_enable_reg13 */


































/* secure_enable_reg14 */


































/* secure_enable_reg15 */


































/* secure_enable_reg16 */


































/* secure_enable_reg17 */


































/* secure_enable_reg18 */


































/* secure_enable_reg19 */


































/* secure_enable_reg20 */


































/* secure_enable_reg21 */


































/* secure_enable_reg22 */


































/* secure_enable_reg23 */


































/* secure_enable_reg24 */


































/* secure_enable_reg25 */


































/* secure_enable_reg26 */


































/* secure_enable_reg27 */


































/* secure_enable_reg28 */


































/* secure_enable_reg29 */


































/* secure_enable_reg30 */


































/* secure_enable_reg31 */


































/* secure_enable_clr_reg0 */


































/* secure_enable_clr_reg1 */


































/* secure_enable_clr_reg2 */


































/* secure_enable_clr_reg3 */


































/* secure_enable_clr_reg4 */


































/* secure_enable_clr_reg5 */


































/* secure_enable_clr_reg6 */


































/* secure_enable_clr_reg7 */


































/* secure_enable_clr_reg8 */


































/* secure_enable_clr_reg9 */


































/* secure_enable_clr_reg10 */


































/* secure_enable_clr_reg11 */


































/* secure_enable_clr_reg12 */


































/* secure_enable_clr_reg13 */


































/* secure_enable_clr_reg14 */


































/* secure_enable_clr_reg15 */


































/* secure_enable_clr_reg16 */


































/* secure_enable_clr_reg17 */


































/* secure_enable_clr_reg18 */


































/* secure_enable_clr_reg19 */


































/* secure_enable_clr_reg20 */


































/* secure_enable_clr_reg21 */


































/* secure_enable_clr_reg22 */


































/* secure_enable_clr_reg23 */


































/* secure_enable_clr_reg24 */


































/* secure_enable_clr_reg25 */


































/* secure_enable_clr_reg26 */


































/* secure_enable_clr_reg27 */


































/* secure_enable_clr_reg28 */


































/* secure_enable_clr_reg29 */


































/* secure_enable_clr_reg30 */


































/* secure_enable_clr_reg31 */


































/* nest_level_reg0 */



/* nest_level_reg1 */



/* nest_level_reg2 */



/* nest_level_reg3 */



/* nest_level_reg4 */



/* nest_level_reg5 */



/* nest_level_reg6 */



/* nest_level_reg7 */



/* nest_level_reg8 */



/* nest_level_reg9 */



/* nest_level_reg10 */



/* nest_level_reg11 */



/* nest_level_reg12 */



/* nest_level_reg13 */



/* nest_level_reg14 */



/* nest_level_reg15 */



/* nest_level_reg16 */



/* nest_level_reg17 */



/* nest_level_reg18 */



/* nest_level_reg19 */



/* nest_level_reg20 */



/* nest_level_reg21 */



/* nest_level_reg22 */



/* nest_level_reg23 */



/* nest_level_reg24 */



/* nest_level_reg25 */



/* nest_level_reg26 */



/* nest_level_reg27 */



/* nest_level_reg28 */



/* nest_level_reg29 */



/* nest_level_reg30 */



/* nest_level_reg31 */



/* nest_level_reg32 */



/* nest_level_reg33 */



/* nest_level_reg34 */



/* nest_level_reg35 */



/* nest_level_reg36 */



/* nest_level_reg37 */



/* nest_level_reg38 */



/* nest_level_reg39 */



/* nest_level_reg40 */



/* nest_level_reg41 */



/* nest_level_reg42 */



/* nest_level_reg43 */



/* nest_level_reg44 */



/* nest_level_reg45 */



/* nest_level_reg46 */



/* nest_level_reg47 */



/* nest_level_reg48 */



/* nest_level_reg49 */



/* nest_level_reg50 */



/* nest_level_reg51 */



/* nest_level_reg52 */



/* nest_level_reg53 */



/* nest_level_reg54 */



/* nest_level_reg55 */



/* nest_level_reg56 */



/* nest_level_reg57 */



/* nest_level_reg58 */



/* nest_level_reg59 */



/* nest_level_reg60 */



/* nest_level_reg61 */



/* nest_level_reg62 */



/* nest_level_reg63 */



/* nest_level_reg64 */



/* nest_level_reg65 */



/* nest_level_reg66 */



/* nest_level_reg67 */



/* nest_level_reg68 */



/* nest_level_reg69 */



/* nest_level_reg70 */



/* nest_level_reg71 */



/* nest_level_reg72 */



/* nest_level_reg73 */



/* nest_level_reg74 */



/* nest_level_reg75 */



/* nest_level_reg76 */



/* nest_level_reg77 */



/* nest_level_reg78 */



/* nest_level_reg79 */



/* nest_level_reg80 */



/* nest_level_reg81 */



/* nest_level_reg82 */



/* nest_level_reg83 */



/* nest_level_reg84 */



/* nest_level_reg85 */



/* nest_level_reg86 */



/* nest_level_reg87 */



/* nest_level_reg88 */



/* nest_level_reg89 */



/* nest_level_reg90 */



/* nest_level_reg91 */



/* nest_level_reg92 */



/* nest_level_reg93 */



/* nest_level_reg94 */



/* nest_level_reg95 */



/* nest_level_reg96 */



/* nest_level_reg97 */



/* nest_level_reg98 */



/* nest_level_reg99 */



/* nest_level_reg100 */



/* nest_level_reg101 */



/* nest_level_reg102 */



/* nest_level_reg103 */



/* nest_level_reg104 */



/* nest_level_reg105 */



/* nest_level_reg106 */



/* nest_level_reg107 */



/* nest_level_reg108 */



/* nest_level_reg109 */



/* nest_level_reg110 */



/* nest_level_reg111 */



/* nest_level_reg112 */



/* nest_level_reg113 */



/* nest_level_reg114 */



/* nest_level_reg115 */



/* nest_level_reg116 */



/* nest_level_reg117 */



/* nest_level_reg118 */



/* nest_level_reg119 */



/* nest_level_reg120 */



/* nest_level_reg121 */



/* nest_level_reg122 */



/* nest_level_reg123 */



/* nest_level_reg124 */



/* nest_level_reg125 */



/* nest_level_reg126 */



/* nest_level_reg127 */



/* nest_level_reg128 */



/* nest_level_reg129 */



/* nest_level_reg130 */



/* nest_level_reg131 */



/* nest_level_reg132 */



/* nest_level_reg133 */



/* nest_level_reg134 */



/* nest_level_reg135 */



/* nest_level_reg136 */



/* nest_level_reg137 */



/* nest_level_reg138 */



/* nest_level_reg139 */



/* nest_level_reg140 */



/* nest_level_reg141 */



/* nest_level_reg142 */



/* nest_level_reg143 */



/* nest_level_reg144 */



/* nest_level_reg145 */



/* nest_level_reg146 */



/* nest_level_reg147 */



/* nest_level_reg148 */



/* nest_level_reg149 */



/* nest_level_reg150 */



/* nest_level_reg151 */



/* nest_level_reg152 */



/* nest_level_reg153 */



/* nest_level_reg154 */



/* nest_level_reg155 */



/* nest_level_reg156 */



/* nest_level_reg157 */



/* nest_level_reg158 */



/* nest_level_reg159 */



/* nest_level_reg160 */



/* nest_level_reg161 */



/* nest_level_reg162 */



/* nest_level_reg163 */



/* nest_level_reg164 */



/* nest_level_reg165 */



/* nest_level_reg166 */



/* nest_level_reg167 */



/* nest_level_reg168 */



/* nest_level_reg169 */



/* nest_level_reg170 */



/* nest_level_reg171 */



/* nest_level_reg172 */



/* nest_level_reg173 */



/* nest_level_reg174 */



/* nest_level_reg175 */



/* nest_level_reg176 */



/* nest_level_reg177 */



/* nest_level_reg178 */



/* nest_level_reg179 */



/* nest_level_reg180 */



/* nest_level_reg181 */



/* nest_level_reg182 */



/* nest_level_reg183 */



/* nest_level_reg184 */



/* nest_level_reg185 */



/* nest_level_reg186 */



/* nest_level_reg187 */



/* nest_level_reg188 */



/* nest_level_reg189 */



/* nest_level_reg190 */



/* nest_level_reg191 */



/* nest_level_reg192 */



/* nest_level_reg193 */



/* nest_level_reg194 */



/* nest_level_reg195 */



/* nest_level_reg196 */



/* nest_level_reg197 */



/* nest_level_reg198 */



/* nest_level_reg199 */



/* nest_level_reg200 */



/* nest_level_reg201 */



/* nest_level_reg202 */



/* nest_level_reg203 */



/* nest_level_reg204 */



/* nest_level_reg205 */



/* nest_level_reg206 */



/* nest_level_reg207 */



/* nest_level_reg208 */



/* nest_level_reg209 */



/* nest_level_reg210 */



/* nest_level_reg211 */



/* nest_level_reg212 */



/* nest_level_reg213 */



/* nest_level_reg214 */



/* nest_level_reg215 */



/* nest_level_reg216 */



/* nest_level_reg217 */



/* nest_level_reg218 */



/* nest_level_reg219 */



/* nest_level_reg220 */



/* nest_level_reg221 */



/* nest_level_reg222 */



/* nest_level_reg223 */



/* nest_level_reg224 */



/* nest_level_reg225 */



/* nest_level_reg226 */



/* nest_level_reg227 */



/* nest_level_reg228 */



/* nest_level_reg229 */



/* nest_level_reg230 */



/* nest_level_reg231 */



/* nest_level_reg232 */



/* nest_level_reg233 */



/* nest_level_reg234 */



/* nest_level_reg235 */



/* nest_level_reg236 */



/* nest_level_reg237 */



/* nest_level_reg238 */



/* nest_level_reg239 */



/* nest_level_reg240 */



/* nest_level_reg241 */



/* nest_level_reg242 */



/* nest_level_reg243 */



/* nest_level_reg244 */



/* nest_level_reg245 */



/* nest_level_reg246 */



/* nest_level_reg247 */



/* nest_level_reg248 */



/* nest_level_reg249 */



/* nest_level_reg250 */



/* nest_level_reg251 */



/* nest_level_reg252 */



/* nest_level_reg253 */



/* nest_level_reg254 */



/* nest_level_reg255 */



/* enable_hint_reg0 */


































/* enable_hint_reg1 */


































/* enable_hint_reg2 */


































/* enable_hint_reg3 */


































/* enable_hint_reg4 */


































/* enable_hint_reg5 */


































/* enable_hint_reg6 */


































/* enable_hint_reg7 */


































/* vector_address_reg_0 */



/* vector_address_reg_1 */



/* vector_address_reg_2 */



/* vector_address_reg_3 */



/* vector_address_reg_4 */



/* vector_address_reg_5 */



/* vector_address_reg_6 */



/* vector_address_reg_7 */



/* vector_address_reg_8 */



/* vector_address_reg_9 */



/* vector_address_reg_10 */



/* vector_address_reg_11 */



/* vector_address_reg_12 */



/* vector_address_reg_13 */



/* vector_address_reg_14 */



/* vector_address_reg_15 */



/* vector_address_reg_16 */



/* vector_address_reg_17 */



/* vector_address_reg_18 */



/* vector_address_reg_19 */



/* vector_address_reg_20 */



/* vector_address_reg_21 */



/* vector_address_reg_22 */



/* vector_address_reg_23 */



/* vector_address_reg_24 */



/* vector_address_reg_25 */



/* vector_address_reg_26 */



/* vector_address_reg_27 */



/* vector_address_reg_28 */



/* vector_address_reg_29 */



/* vector_address_reg_30 */



/* vector_address_reg_31 */



/* vector_address_reg_32 */



/* vector_address_reg_33 */



/* vector_address_reg_34 */



/* vector_address_reg_35 */



/* vector_address_reg_36 */



/* vector_address_reg_37 */



/* vector_address_reg_38 */



/* vector_address_reg_39 */



/* vector_address_reg_40 */



/* vector_address_reg_41 */



/* vector_address_reg_42 */



/* vector_address_reg_43 */



/* vector_address_reg_44 */



/* vector_address_reg_45 */



/* vector_address_reg_46 */



/* vector_address_reg_47 */



/* vector_address_reg_48 */



/* vector_address_reg_49 */



/* vector_address_reg_50 */



/* vector_address_reg_51 */



/* vector_address_reg_52 */



/* vector_address_reg_53 */



/* vector_address_reg_54 */



/* vector_address_reg_55 */



/* vector_address_reg_56 */



/* vector_address_reg_57 */



/* vector_address_reg_58 */



/* vector_address_reg_59 */



/* vector_address_reg_60 */



/* vector_address_reg_61 */



/* vector_address_reg_62 */



/* vector_address_reg_63 */



/* vector_address_reg_64 */



/* vector_address_reg_65 */



/* vector_address_reg_66 */



/* vector_address_reg_67 */



/* vector_address_reg_68 */



/* vector_address_reg_69 */



/* vector_address_reg_70 */



/* vector_address_reg_71 */



/* vector_address_reg_72 */



/* vector_address_reg_73 */



/* vector_address_reg_74 */



/* vector_address_reg_75 */



/* vector_address_reg_76 */



/* vector_address_reg_77 */



/* vector_address_reg_78 */



/* vector_address_reg_79 */



/* vector_address_reg_80 */



/* vector_address_reg_81 */



/* vector_address_reg_82 */



/* vector_address_reg_83 */



/* vector_address_reg_84 */



/* vector_address_reg_85 */



/* vector_address_reg_86 */



/* vector_address_reg_87 */



/* vector_address_reg_88 */



/* vector_address_reg_89 */



/* vector_address_reg_90 */



/* vector_address_reg_91 */



/* vector_address_reg_92 */



/* vector_address_reg_93 */



/* vector_address_reg_94 */



/* vector_address_reg_95 */



/* vector_address_reg_96 */



/* vector_address_reg_97 */



/* vector_address_reg_98 */



/* vector_address_reg_99 */



/* vector_address_reg_100 */



/* vector_address_reg_101 */



/* vector_address_reg_102 */



/* vector_address_reg_103 */



/* vector_address_reg_104 */



/* vector_address_reg_105 */



/* vector_address_reg_106 */



/* vector_address_reg_107 */



/* vector_address_reg_108 */



/* vector_address_reg_109 */



/* vector_address_reg_110 */



/* vector_address_reg_111 */



/* vector_address_reg_112 */



/* vector_address_reg_113 */



/* vector_address_reg_114 */



/* vector_address_reg_115 */



/* vector_address_reg_116 */



/* vector_address_reg_117 */



/* vector_address_reg_118 */



/* vector_address_reg_119 */



/* vector_address_reg_120 */



/* vector_address_reg_121 */



/* vector_address_reg_122 */



/* vector_address_reg_123 */



/* vector_address_reg_124 */



/* vector_address_reg_125 */



/* vector_address_reg_126 */



/* vector_address_reg_127 */



/* vector_address_reg_128 */



/* vector_address_reg_129 */



/* vector_address_reg_130 */



/* vector_address_reg_131 */



/* vector_address_reg_132 */



/* vector_address_reg_133 */



/* vector_address_reg_134 */



/* vector_address_reg_135 */



/* vector_address_reg_136 */



/* vector_address_reg_137 */



/* vector_address_reg_138 */



/* vector_address_reg_139 */



/* vector_address_reg_140 */



/* vector_address_reg_141 */



/* vector_address_reg_142 */



/* vector_address_reg_143 */



/* vector_address_reg_144 */



/* vector_address_reg_145 */



/* vector_address_reg_146 */



/* vector_address_reg_147 */



/* vector_address_reg_148 */



/* vector_address_reg_149 */



/* vector_address_reg_150 */



/* vector_address_reg_151 */



/* vector_address_reg_152 */



/* vector_address_reg_153 */



/* vector_address_reg_154 */



/* vector_address_reg_155 */



/* vector_address_reg_156 */



/* vector_address_reg_157 */



/* vector_address_reg_158 */



/* vector_address_reg_159 */



/* vector_address_reg_160 */



/* vector_address_reg_161 */



/* vector_address_reg_162 */



/* vector_address_reg_163 */



/* vector_address_reg_164 */



/* vector_address_reg_165 */



/* vector_address_reg_166 */



/* vector_address_reg_167 */



/* vector_address_reg_168 */



/* vector_address_reg_169 */



/* vector_address_reg_170 */



/* vector_address_reg_171 */



/* vector_address_reg_172 */



/* vector_address_reg_173 */



/* vector_address_reg_174 */



/* vector_address_reg_175 */



/* vector_address_reg_176 */



/* vector_address_reg_177 */



/* vector_address_reg_178 */



/* vector_address_reg_179 */



/* vector_address_reg_180 */



/* vector_address_reg_181 */



/* vector_address_reg_182 */



/* vector_address_reg_183 */



/* vector_address_reg_184 */



/* vector_address_reg_185 */



/* vector_address_reg_186 */



/* vector_address_reg_187 */



/* vector_address_reg_188 */



/* vector_address_reg_189 */



/* vector_address_reg_190 */



/* vector_address_reg_191 */



/* vector_address_reg_192 */



/* vector_address_reg_193 */



/* vector_address_reg_194 */



/* vector_address_reg_195 */



/* vector_address_reg_196 */



/* vector_address_reg_197 */



/* vector_address_reg_198 */



/* vector_address_reg_199 */



/* vector_address_reg_200 */



/* vector_address_reg_201 */



/* vector_address_reg_202 */



/* vector_address_reg_203 */



/* vector_address_reg_204 */



/* vector_address_reg_205 */



/* vector_address_reg_206 */



/* vector_address_reg_207 */



/* vector_address_reg_208 */



/* vector_address_reg_209 */



/* vector_address_reg_210 */



/* vector_address_reg_211 */



/* vector_address_reg_212 */



/* vector_address_reg_213 */



/* vector_address_reg_214 */



/* vector_address_reg_215 */



/* vector_address_reg_216 */



/* vector_address_reg_217 */



/* vector_address_reg_218 */



/* vector_address_reg_219 */



/* vector_address_reg_220 */



/* vector_address_reg_221 */



/* vector_address_reg_222 */



/* vector_address_reg_223 */



/* vector_address_reg_224 */



/* vector_address_reg_225 */



/* vector_address_reg_226 */



/* vector_address_reg_227 */



/* vector_address_reg_228 */



/* vector_address_reg_229 */



/* vector_address_reg_230 */



/* vector_address_reg_231 */



/* vector_address_reg_232 */



/* vector_address_reg_233 */



/* vector_address_reg_234 */



/* vector_address_reg_235 */



/* vector_address_reg_236 */



/* vector_address_reg_237 */



/* vector_address_reg_238 */



/* vector_address_reg_239 */



/* vector_address_reg_240 */



/* vector_address_reg_241 */



/* vector_address_reg_242 */



/* vector_address_reg_243 */



/* vector_address_reg_244 */



/* vector_address_reg_245 */



/* vector_address_reg_246 */



/* vector_address_reg_247 */



/* vector_address_reg_248 */



/* vector_address_reg_249 */



/* vector_address_reg_250 */



/* vector_address_reg_251 */



/* vector_address_reg_252 */



/* vector_address_reg_253 */



/* vector_address_reg_254 */



/* vector_address_reg_255 */



/* vector_address_reg_256 */



/* vector_address_reg_257 */



/* vector_address_reg_258 */



/* vector_address_reg_259 */



/* vector_address_reg_260 */



/* vector_address_reg_261 */



/* vector_address_reg_262 */



/* vector_address_reg_263 */



/* vector_address_reg_264 */



/* vector_address_reg_265 */



/* vector_address_reg_266 */



/* vector_address_reg_267 */



/* vector_address_reg_268 */



/* vector_address_reg_269 */



/* vector_address_reg_270 */



/* vector_address_reg_271 */



/* vector_address_reg_272 */



/* vector_address_reg_273 */



/* vector_address_reg_274 */



/* vector_address_reg_275 */



/* vector_address_reg_276 */



/* vector_address_reg_277 */



/* vector_address_reg_278 */



/* vector_address_reg_279 */



/* vector_address_reg_280 */



/* vector_address_reg_281 */



/* vector_address_reg_282 */



/* vector_address_reg_283 */



/* vector_address_reg_284 */



/* vector_address_reg_285 */



/* vector_address_reg_286 */



/* vector_address_reg_287 */



/* vector_address_reg_288 */



/* vector_address_reg_289 */



/* vector_address_reg_290 */



/* vector_address_reg_291 */



/* vector_address_reg_292 */



/* vector_address_reg_293 */



/* vector_address_reg_294 */



/* vector_address_reg_295 */



/* vector_address_reg_296 */



/* vector_address_reg_297 */



/* vector_address_reg_298 */



/* vector_address_reg_299 */



/* vector_address_reg_300 */



/* vector_address_reg_301 */



/* vector_address_reg_302 */



/* vector_address_reg_303 */



/* vector_address_reg_304 */



/* vector_address_reg_305 */



/* vector_address_reg_306 */



/* vector_address_reg_307 */



/* vector_address_reg_308 */



/* vector_address_reg_309 */



/* vector_address_reg_310 */



/* vector_address_reg_311 */



/* vector_address_reg_312 */



/* vector_address_reg_313 */



/* vector_address_reg_314 */



/* vector_address_reg_315 */



/* vector_address_reg_316 */



/* vector_address_reg_317 */



/* vector_address_reg_318 */



/* vector_address_reg_319 */



/* vector_address_reg_320 */



/* vector_address_reg_321 */



/* vector_address_reg_322 */



/* vector_address_reg_323 */



/* vector_address_reg_324 */



/* vector_address_reg_325 */



/* vector_address_reg_326 */



/* vector_address_reg_327 */



/* vector_address_reg_328 */



/* vector_address_reg_329 */



/* vector_address_reg_330 */



/* vector_address_reg_331 */



/* vector_address_reg_332 */



/* vector_address_reg_333 */



/* vector_address_reg_334 */



/* vector_address_reg_335 */



/* vector_address_reg_336 */



/* vector_address_reg_337 */



/* vector_address_reg_338 */



/* vector_address_reg_339 */



/* vector_address_reg_340 */



/* vector_address_reg_341 */



/* vector_address_reg_342 */



/* vector_address_reg_343 */



/* vector_address_reg_344 */



/* vector_address_reg_345 */



/* vector_address_reg_346 */



/* vector_address_reg_347 */



/* vector_address_reg_348 */



/* vector_address_reg_349 */



/* vector_address_reg_350 */



/* vector_address_reg_351 */



/* vector_address_reg_352 */



/* vector_address_reg_353 */



/* vector_address_reg_354 */



/* vector_address_reg_355 */



/* vector_address_reg_356 */



/* vector_address_reg_357 */



/* vector_address_reg_358 */



/* vector_address_reg_359 */



/* vector_address_reg_360 */



/* vector_address_reg_361 */



/* vector_address_reg_362 */



/* vector_address_reg_363 */



/* vector_address_reg_364 */



/* vector_address_reg_365 */



/* vector_address_reg_366 */



/* vector_address_reg_367 */



/* vector_address_reg_368 */



/* vector_address_reg_369 */



/* vector_address_reg_370 */



/* vector_address_reg_371 */



/* vector_address_reg_372 */



/* vector_address_reg_373 */



/* vector_address_reg_374 */



/* vector_address_reg_375 */



/* vector_address_reg_376 */



/* vector_address_reg_377 */



/* vector_address_reg_378 */



/* vector_address_reg_379 */



/* vector_address_reg_380 */



/* vector_address_reg_381 */



/* vector_address_reg_382 */



/* vector_address_reg_383 */



/* vector_address_reg_384 */



/* vector_address_reg_385 */



/* vector_address_reg_386 */



/* vector_address_reg_387 */



/* vector_address_reg_388 */



/* vector_address_reg_389 */



/* vector_address_reg_390 */



/* vector_address_reg_391 */



/* vector_address_reg_392 */



/* vector_address_reg_393 */



/* vector_address_reg_394 */



/* vector_address_reg_395 */



/* vector_address_reg_396 */



/* vector_address_reg_397 */



/* vector_address_reg_398 */



/* vector_address_reg_399 */



/* vector_address_reg_400 */



/* vector_address_reg_401 */



/* vector_address_reg_402 */



/* vector_address_reg_403 */



/* vector_address_reg_404 */



/* vector_address_reg_405 */



/* vector_address_reg_406 */



/* vector_address_reg_407 */



/* vector_address_reg_408 */



/* vector_address_reg_409 */



/* vector_address_reg_410 */



/* vector_address_reg_411 */



/* vector_address_reg_412 */



/* vector_address_reg_413 */



/* vector_address_reg_414 */



/* vector_address_reg_415 */



/* vector_address_reg_416 */



/* vector_address_reg_417 */



/* vector_address_reg_418 */



/* vector_address_reg_419 */



/* vector_address_reg_420 */



/* vector_address_reg_421 */



/* vector_address_reg_422 */



/* vector_address_reg_423 */



/* vector_address_reg_424 */



/* vector_address_reg_425 */



/* vector_address_reg_426 */



/* vector_address_reg_427 */



/* vector_address_reg_428 */



/* vector_address_reg_429 */



/* vector_address_reg_430 */



/* vector_address_reg_431 */



/* vector_address_reg_432 */



/* vector_address_reg_433 */



/* vector_address_reg_434 */



/* vector_address_reg_435 */



/* vector_address_reg_436 */



/* vector_address_reg_437 */



/* vector_address_reg_438 */



/* vector_address_reg_439 */



/* vector_address_reg_440 */



/* vector_address_reg_441 */



/* vector_address_reg_442 */



/* vector_address_reg_443 */



/* vector_address_reg_444 */



/* vector_address_reg_445 */



/* vector_address_reg_446 */



/* vector_address_reg_447 */



/* vector_address_reg_448 */



/* vector_address_reg_449 */



/* vector_address_reg_450 */



/* vector_address_reg_451 */



/* vector_address_reg_452 */



/* vector_address_reg_453 */



/* vector_address_reg_454 */



/* vector_address_reg_455 */



/* vector_address_reg_456 */



/* vector_address_reg_457 */



/* vector_address_reg_458 */



/* vector_address_reg_459 */



/* vector_address_reg_460 */



/* vector_address_reg_461 */



/* vector_address_reg_462 */



/* vector_address_reg_463 */



/* vector_address_reg_464 */



/* vector_address_reg_465 */



/* vector_address_reg_466 */



/* vector_address_reg_467 */



/* vector_address_reg_468 */



/* vector_address_reg_469 */



/* vector_address_reg_470 */



/* vector_address_reg_471 */



/* vector_address_reg_472 */



/* vector_address_reg_473 */



/* vector_address_reg_474 */



/* vector_address_reg_475 */



/* vector_address_reg_476 */



/* vector_address_reg_477 */



/* vector_address_reg_478 */



/* vector_address_reg_479 */



/* vector_address_reg_480 */



/* vector_address_reg_481 */



/* vector_address_reg_482 */



/* vector_address_reg_483 */



/* vector_address_reg_484 */



/* vector_address_reg_485 */



/* vector_address_reg_486 */



/* vector_address_reg_487 */



/* vector_address_reg_488 */



/* vector_address_reg_489 */



/* vector_address_reg_490 */



/* vector_address_reg_491 */



/* vector_address_reg_492 */



/* vector_address_reg_493 */



/* vector_address_reg_494 */



/* vector_address_reg_495 */



/* vector_address_reg_496 */



/* vector_address_reg_497 */



/* vector_address_reg_498 */



/* vector_address_reg_499 */



/* vector_address_reg_500 */



/* vector_address_reg_501 */



/* vector_address_reg_502 */



/* vector_address_reg_503 */



/* vector_address_reg_504 */



/* vector_address_reg_505 */



/* vector_address_reg_506 */



/* vector_address_reg_507 */



/* vector_address_reg_508 */



/* vector_address_reg_509 */



/* vector_address_reg_510 */



/* vector_address_reg_511 */



/* vector_address_reg_512 */



/* vector_address_reg_513 */



/* vector_address_reg_514 */



/* vector_address_reg_515 */



/* vector_address_reg_516 */



/* vector_address_reg_517 */



/* vector_address_reg_518 */



/* vector_address_reg_519 */



/* vector_address_reg_520 */



/* vector_address_reg_521 */



/* vector_address_reg_522 */



/* vector_address_reg_523 */



/* vector_address_reg_524 */



/* vector_address_reg_525 */



/* vector_address_reg_526 */



/* vector_address_reg_527 */



/* vector_address_reg_528 */



/* vector_address_reg_529 */



/* vector_address_reg_530 */



/* vector_address_reg_531 */



/* vector_address_reg_532 */



/* vector_address_reg_533 */



/* vector_address_reg_534 */



/* vector_address_reg_535 */



/* vector_address_reg_536 */



/* vector_address_reg_537 */



/* vector_address_reg_538 */



/* vector_address_reg_539 */



/* vector_address_reg_540 */



/* vector_address_reg_541 */



/* vector_address_reg_542 */



/* vector_address_reg_543 */



/* vector_address_reg_544 */



/* vector_address_reg_545 */



/* vector_address_reg_546 */



/* vector_address_reg_547 */



/* vector_address_reg_548 */



/* vector_address_reg_549 */



/* vector_address_reg_550 */



/* vector_address_reg_551 */



/* vector_address_reg_552 */



/* vector_address_reg_553 */



/* vector_address_reg_554 */



/* vector_address_reg_555 */



/* vector_address_reg_556 */



/* vector_address_reg_557 */



/* vector_address_reg_558 */



/* vector_address_reg_559 */



/* vector_address_reg_560 */



/* vector_address_reg_561 */



/* vector_address_reg_562 */



/* vector_address_reg_563 */



/* vector_address_reg_564 */



/* vector_address_reg_565 */



/* vector_address_reg_566 */



/* vector_address_reg_567 */



/* vector_address_reg_568 */



/* vector_address_reg_569 */



/* vector_address_reg_570 */



/* vector_address_reg_571 */



/* vector_address_reg_572 */



/* vector_address_reg_573 */



/* vector_address_reg_574 */



/* vector_address_reg_575 */



/* vector_address_reg_576 */



/* vector_address_reg_577 */



/* vector_address_reg_578 */



/* vector_address_reg_579 */



/* vector_address_reg_580 */



/* vector_address_reg_581 */



/* vector_address_reg_582 */



/* vector_address_reg_583 */



/* vector_address_reg_584 */



/* vector_address_reg_585 */



/* vector_address_reg_586 */



/* vector_address_reg_587 */



/* vector_address_reg_588 */



/* vector_address_reg_589 */



/* vector_address_reg_590 */



/* vector_address_reg_591 */



/* vector_address_reg_592 */



/* vector_address_reg_593 */



/* vector_address_reg_594 */



/* vector_address_reg_595 */



/* vector_address_reg_596 */



/* vector_address_reg_597 */



/* vector_address_reg_598 */



/* vector_address_reg_599 */



/* vector_address_reg_600 */



/* vector_address_reg_601 */



/* vector_address_reg_602 */



/* vector_address_reg_603 */



/* vector_address_reg_604 */



/* vector_address_reg_605 */



/* vector_address_reg_606 */



/* vector_address_reg_607 */



/* vector_address_reg_608 */



/* vector_address_reg_609 */



/* vector_address_reg_610 */



/* vector_address_reg_611 */



/* vector_address_reg_612 */



/* vector_address_reg_613 */



/* vector_address_reg_614 */



/* vector_address_reg_615 */



/* vector_address_reg_616 */



/* vector_address_reg_617 */



/* vector_address_reg_618 */



/* vector_address_reg_619 */



/* vector_address_reg_620 */



/* vector_address_reg_621 */



/* vector_address_reg_622 */



/* vector_address_reg_623 */



/* vector_address_reg_624 */



/* vector_address_reg_625 */



/* vector_address_reg_626 */



/* vector_address_reg_627 */



/* vector_address_reg_628 */



/* vector_address_reg_629 */



/* vector_address_reg_630 */



/* vector_address_reg_631 */



/* vector_address_reg_632 */



/* vector_address_reg_633 */



/* vector_address_reg_634 */



/* vector_address_reg_635 */



/* vector_address_reg_636 */



/* vector_address_reg_637 */



/* vector_address_reg_638 */



/* vector_address_reg_639 */



/* vector_address_reg_640 */



/* vector_address_reg_641 */



/* vector_address_reg_642 */



/* vector_address_reg_643 */



/* vector_address_reg_644 */



/* vector_address_reg_645 */



/* vector_address_reg_646 */



/* vector_address_reg_647 */



/* vector_address_reg_648 */



/* vector_address_reg_649 */



/* vector_address_reg_650 */



/* vector_address_reg_651 */



/* vector_address_reg_652 */



/* vector_address_reg_653 */



/* vector_address_reg_654 */



/* vector_address_reg_655 */



/* vector_address_reg_656 */



/* vector_address_reg_657 */



/* vector_address_reg_658 */



/* vector_address_reg_659 */



/* vector_address_reg_660 */



/* vector_address_reg_661 */



/* vector_address_reg_662 */



/* vector_address_reg_663 */



/* vector_address_reg_664 */



/* vector_address_reg_665 */



/* vector_address_reg_666 */



/* vector_address_reg_667 */



/* vector_address_reg_668 */



/* vector_address_reg_669 */



/* vector_address_reg_670 */



/* vector_address_reg_671 */



/* vector_address_reg_672 */



/* vector_address_reg_673 */



/* vector_address_reg_674 */



/* vector_address_reg_675 */



/* vector_address_reg_676 */



/* vector_address_reg_677 */



/* vector_address_reg_678 */



/* vector_address_reg_679 */



/* vector_address_reg_680 */



/* vector_address_reg_681 */



/* vector_address_reg_682 */



/* vector_address_reg_683 */



/* vector_address_reg_684 */



/* vector_address_reg_685 */



/* vector_address_reg_686 */



/* vector_address_reg_687 */



/* vector_address_reg_688 */



/* vector_address_reg_689 */



/* vector_address_reg_690 */



/* vector_address_reg_691 */



/* vector_address_reg_692 */



/* vector_address_reg_693 */



/* vector_address_reg_694 */



/* vector_address_reg_695 */



/* vector_address_reg_696 */



/* vector_address_reg_697 */



/* vector_address_reg_698 */



/* vector_address_reg_699 */



/* vector_address_reg_700 */



/* vector_address_reg_701 */



/* vector_address_reg_702 */



/* vector_address_reg_703 */



/* vector_address_reg_704 */



/* vector_address_reg_705 */



/* vector_address_reg_706 */



/* vector_address_reg_707 */



/* vector_address_reg_708 */



/* vector_address_reg_709 */



/* vector_address_reg_710 */



/* vector_address_reg_711 */



/* vector_address_reg_712 */



/* vector_address_reg_713 */



/* vector_address_reg_714 */



/* vector_address_reg_715 */



/* vector_address_reg_716 */



/* vector_address_reg_717 */



/* vector_address_reg_718 */



/* vector_address_reg_719 */



/* vector_address_reg_720 */



/* vector_address_reg_721 */



/* vector_address_reg_722 */



/* vector_address_reg_723 */



/* vector_address_reg_724 */



/* vector_address_reg_725 */



/* vector_address_reg_726 */



/* vector_address_reg_727 */



/* vector_address_reg_728 */



/* vector_address_reg_729 */



/* vector_address_reg_730 */



/* vector_address_reg_731 */



/* vector_address_reg_732 */



/* vector_address_reg_733 */



/* vector_address_reg_734 */



/* vector_address_reg_735 */



/* vector_address_reg_736 */



/* vector_address_reg_737 */



/* vector_address_reg_738 */



/* vector_address_reg_739 */



/* vector_address_reg_740 */



/* vector_address_reg_741 */



/* vector_address_reg_742 */



/* vector_address_reg_743 */



/* vector_address_reg_744 */



/* vector_address_reg_745 */



/* vector_address_reg_746 */



/* vector_address_reg_747 */



/* vector_address_reg_748 */



/* vector_address_reg_749 */



/* vector_address_reg_750 */



/* vector_address_reg_751 */



/* vector_address_reg_752 */



/* vector_address_reg_753 */



/* vector_address_reg_754 */



/* vector_address_reg_755 */



/* vector_address_reg_756 */



/* vector_address_reg_757 */



/* vector_address_reg_758 */



/* vector_address_reg_759 */



/* vector_address_reg_760 */



/* vector_address_reg_761 */



/* vector_address_reg_762 */



/* vector_address_reg_763 */



/* vector_address_reg_764 */



/* vector_address_reg_765 */



/* vector_address_reg_766 */



/* vector_address_reg_767 */



/* vector_address_reg_768 */



/* vector_address_reg_769 */



/* vector_address_reg_770 */



/* vector_address_reg_771 */



/* vector_address_reg_772 */



/* vector_address_reg_773 */



/* vector_address_reg_774 */



/* vector_address_reg_775 */



/* vector_address_reg_776 */



/* vector_address_reg_777 */



/* vector_address_reg_778 */



/* vector_address_reg_779 */



/* vector_address_reg_780 */



/* vector_address_reg_781 */



/* vector_address_reg_782 */



/* vector_address_reg_783 */



/* vector_address_reg_784 */



/* vector_address_reg_785 */



/* vector_address_reg_786 */



/* vector_address_reg_787 */



/* vector_address_reg_788 */



/* vector_address_reg_789 */



/* vector_address_reg_790 */



/* vector_address_reg_791 */



/* vector_address_reg_792 */



/* vector_address_reg_793 */



/* vector_address_reg_794 */



/* vector_address_reg_795 */



/* vector_address_reg_796 */



/* vector_address_reg_797 */



/* vector_address_reg_798 */



/* vector_address_reg_799 */



/* vector_address_reg_800 */



/* vector_address_reg_801 */



/* vector_address_reg_802 */



/* vector_address_reg_803 */



/* vector_address_reg_804 */



/* vector_address_reg_805 */



/* vector_address_reg_806 */



/* vector_address_reg_807 */



/* vector_address_reg_808 */



/* vector_address_reg_809 */



/* vector_address_reg_810 */



/* vector_address_reg_811 */



/* vector_address_reg_812 */



/* vector_address_reg_813 */



/* vector_address_reg_814 */



/* vector_address_reg_815 */



/* vector_address_reg_816 */



/* vector_address_reg_817 */



/* vector_address_reg_818 */



/* vector_address_reg_819 */



/* vector_address_reg_820 */



/* vector_address_reg_821 */



/* vector_address_reg_822 */



/* vector_address_reg_823 */



/* vector_address_reg_824 */



/* vector_address_reg_825 */



/* vector_address_reg_826 */



/* vector_address_reg_827 */



/* vector_address_reg_828 */



/* vector_address_reg_829 */



/* vector_address_reg_830 */



/* vector_address_reg_831 */



/* vector_address_reg_832 */



/* vector_address_reg_833 */



/* vector_address_reg_834 */



/* vector_address_reg_835 */



/* vector_address_reg_836 */



/* vector_address_reg_837 */



/* vector_address_reg_838 */



/* vector_address_reg_839 */



/* vector_address_reg_840 */



/* vector_address_reg_841 */



/* vector_address_reg_842 */



/* vector_address_reg_843 */



/* vector_address_reg_844 */



/* vector_address_reg_845 */



/* vector_address_reg_846 */



/* vector_address_reg_847 */



/* vector_address_reg_848 */



/* vector_address_reg_849 */



/* vector_address_reg_850 */



/* vector_address_reg_851 */



/* vector_address_reg_852 */



/* vector_address_reg_853 */



/* vector_address_reg_854 */



/* vector_address_reg_855 */



/* vector_address_reg_856 */



/* vector_address_reg_857 */



/* vector_address_reg_858 */



/* vector_address_reg_859 */



/* vector_address_reg_860 */



/* vector_address_reg_861 */



/* vector_address_reg_862 */



/* vector_address_reg_863 */



/* vector_address_reg_864 */



/* vector_address_reg_865 */



/* vector_address_reg_866 */



/* vector_address_reg_867 */



/* vector_address_reg_868 */



/* vector_address_reg_869 */



/* vector_address_reg_870 */



/* vector_address_reg_871 */



/* vector_address_reg_872 */



/* vector_address_reg_873 */



/* vector_address_reg_874 */



/* vector_address_reg_875 */



/* vector_address_reg_876 */



/* vector_address_reg_877 */



/* vector_address_reg_878 */



/* vector_address_reg_879 */



/* vector_address_reg_880 */



/* vector_address_reg_881 */



/* vector_address_reg_882 */



/* vector_address_reg_883 */



/* vector_address_reg_884 */



/* vector_address_reg_885 */



/* vector_address_reg_886 */



/* vector_address_reg_887 */



/* vector_address_reg_888 */



/* vector_address_reg_889 */



/* vector_address_reg_890 */



/* vector_address_reg_891 */



/* vector_address_reg_892 */



/* vector_address_reg_893 */



/* vector_address_reg_894 */



/* vector_address_reg_895 */



/* vector_address_reg_896 */



/* vector_address_reg_897 */



/* vector_address_reg_898 */



/* vector_address_reg_899 */



/* vector_address_reg_900 */



/* vector_address_reg_901 */



/* vector_address_reg_902 */



/* vector_address_reg_903 */



/* vector_address_reg_904 */



/* vector_address_reg_905 */



/* vector_address_reg_906 */



/* vector_address_reg_907 */



/* vector_address_reg_908 */



/* vector_address_reg_909 */



/* vector_address_reg_910 */



/* vector_address_reg_911 */



/* vector_address_reg_912 */



/* vector_address_reg_913 */



/* vector_address_reg_914 */



/* vector_address_reg_915 */



/* vector_address_reg_916 */



/* vector_address_reg_917 */



/* vector_address_reg_918 */



/* vector_address_reg_919 */



/* vector_address_reg_920 */



/* vector_address_reg_921 */



/* vector_address_reg_922 */



/* vector_address_reg_923 */



/* vector_address_reg_924 */



/* vector_address_reg_925 */



/* vector_address_reg_926 */



/* vector_address_reg_927 */



/* vector_address_reg_928 */



/* vector_address_reg_929 */



/* vector_address_reg_930 */



/* vector_address_reg_931 */



/* vector_address_reg_932 */



/* vector_address_reg_933 */



/* vector_address_reg_934 */



/* vector_address_reg_935 */



/* vector_address_reg_936 */



/* vector_address_reg_937 */



/* vector_address_reg_938 */



/* vector_address_reg_939 */



/* vector_address_reg_940 */



/* vector_address_reg_941 */



/* vector_address_reg_942 */



/* vector_address_reg_943 */



/* vector_address_reg_944 */



/* vector_address_reg_945 */



/* vector_address_reg_946 */



/* vector_address_reg_947 */



/* vector_address_reg_948 */



/* vector_address_reg_949 */



/* vector_address_reg_950 */



/* vector_address_reg_951 */



/* vector_address_reg_952 */



/* vector_address_reg_953 */



/* vector_address_reg_954 */



/* vector_address_reg_955 */



/* vector_address_reg_956 */



/* vector_address_reg_957 */



/* vector_address_reg_958 */



/* vector_address_reg_959 */



/* vector_address_reg_960 */



/* vector_address_reg_961 */



/* vector_address_reg_962 */



/* vector_address_reg_963 */



/* vector_address_reg_964 */



/* vector_address_reg_965 */



/* vector_address_reg_966 */



/* vector_address_reg_967 */



/* vector_address_reg_968 */



/* vector_address_reg_969 */



/* vector_address_reg_970 */



/* vector_address_reg_971 */



/* vector_address_reg_972 */



/* vector_address_reg_973 */



/* vector_address_reg_974 */



/* vector_address_reg_975 */



/* vector_address_reg_976 */



/* vector_address_reg_977 */



/* vector_address_reg_978 */



/* vector_address_reg_979 */



/* vector_address_reg_980 */



/* vector_address_reg_981 */



/* vector_address_reg_982 */



/* vector_address_reg_983 */



/* vector_address_reg_984 */



/* vector_address_reg_985 */



/* vector_address_reg_986 */



/* vector_address_reg_987 */



/* vector_address_reg_988 */



/* vector_address_reg_989 */



/* vector_address_reg_990 */



/* vector_address_reg_991 */



/* vector_address_reg_992 */



/* vector_address_reg_993 */



/* vector_address_reg_994 */



/* vector_address_reg_995 */



/* vector_address_reg_996 */



/* vector_address_reg_997 */



/* vector_address_reg_998 */



/* vector_address_reg_999 */



/* vector_address_reg_1000 */



/* vector_address_reg_1001 */



/* vector_address_reg_1002 */



/* vector_address_reg_1003 */



/* vector_address_reg_1004 */



/* vector_address_reg_1005 */



/* vector_address_reg_1006 */



/* vector_address_reg_1007 */



/* vector_address_reg_1008 */



/* vector_address_reg_1009 */



/* vector_address_reg_1010 */



/* vector_address_reg_1011 */



/* vector_address_reg_1012 */



/* vector_address_reg_1013 */



/* vector_address_reg_1014 */



/* vector_address_reg_1015 */



/* vector_address_reg_1016 */



/* vector_address_reg_1017 */



/* vector_address_reg_1018 */



/* vector_address_reg_1019 */



/* vector_address_reg_1020 */



/* vector_address_reg_1021 */



/* vector_address_reg_1022 */



/* vector_address_reg_1023 */





/**
@defgroup CSL_CPINTC_SYMBOL  CPINTC Symbols Defined
@ingroup CSL_CPINTC_API
*/
/**
@defgroup CSL_CPINTC_DATASTRUCT  CPINTC Data Structures
@ingroup CSL_CPINTC_API
*/
/**
@defgroup CSL_CPINTC_FUNCTION  CPINTC Functions
@ingroup CSL_CPINTC_API
*/

/** @addtogroup CSL_CPINTC_DATASTRUCT
 @{ */
 
/** @brief Register Overlay Memory map for the CPINTC0 Registers. */
typedef volatile CSL_CPINTCRegs*  CSL_CPINTC_RegsOvly;

/** @brief This is the handle to the CPINTC instance */
typedef Uint32   CSL_CPINTC_Handle;

/** @brief This defines the system interrupt */
typedef Uint32   CSL_CPINTCSystemInterrupt;

/** @brief This defines the host interrupt */
typedef Uint32   CSL_CPINTCHostInterrupt;

/** @brief This defines the channels */
typedef Uint32   CSL_CPINTCChannel;

/** @brief This defines the nesting level */
typedef Uint16   CSL_CPINTCNestingLevel;

/** @brief Enumeration defines the type of Nesting Modes which is supported by the CPINTC */
typedef enum CSL_CPINTCNestingMode
{
    CPINTC_NO_NESTING            = 0x0,
    CPINTC_AUTOMATIC_GLB_NESTING = 0x1,
    CPINTC_AUTOMATIC_IND_NESTING = 0x2,
    CPINTC_MANUAL_NESTING        = 0x3
}CSL_CPINTCNestingMode;

/**
@}
*/

/* Device specific API which opens the CPINTC instance and returns a handle used in all subsequent calls */
extern CSL_CPINTC_Handle CSL_CPINTC_open (Int32 instNum);



//#include <csl_cicAux.h> //in CCS5 this include file is not present, that's why removed by remesh
/**
 *   @file  csl_cpintcAux.h
 *
 *   @brief   
 *      This is the CPINTC Auxilary Header File which exposes the various
 *      CSL Functional Layer API's to configure the CPINTC Module.
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
 



/** @addtogroup CSL_CPINTC_FUNCTION
 @{ */

/** ============================================================================
 *   @n@b CSL_CPINTC_setNestingMode
 *
 *   @b Description
 *   @n This API configures the Interrupt Controller nesting mode.
 *      
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
        nestMode    Nesting Mode to be configured
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The interrupt controller is configured to use the specified nesting mode.
 *
 *   @b  Writes
 *   @n  CPINTC_CONTROL_REG_NEST_MODE
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCNestingMode nestMode;
        CSL_CPINTC_HANDLE     hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_setNestingMode (hnd, nestMode);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_setNestingMode
(
    CSL_CPINTC_Handle       hnd, 
    CSL_CPINTCNestingMode   nestMode
)
{
    /* Write the CONTROL_REG with the specified nesting mode. */        
    ((CSL_CPINTC_RegsOvly)hnd)->CONTROL_REG = (((nestMode) << (0x00000002u)) & (0x0000000Cu));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_getNestingMode
 *
 *   @b Description
 *   @n This API gets the current nesting mode which is configured in the
 *      interrupt controller.
 * 
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
     @endverbatim
 * 
 *      
 *   <b> Return Value </b> 
 *       CSL_CPINTCNestingMode - Current Nesting Mode.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_CONTROL_REG_NEST_MODE
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTC_HANDLE     hnd;
        CSL_CPINTCNestingMode nestMode;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        nestMode = CSL_CPINTC_getNestingMode();
     @endverbatim
 * ===========================================================================
 */
static inline CSL_CPINTCNestingMode CSL_CPINTC_getNestingMode (CSL_CPINTC_Handle hnd)
{
    return (CSL_CPINTCNestingMode)(((((CSL_CPINTC_RegsOvly)hnd)->CONTROL_REG) & (0x0000000Cu)) >> (0x00000002u));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_setNestingLevel
 *
 *   @b Description
 *   @n This API overrides the Interrupt Controller global nesting level that
        is set by automatic nesting	mode
 *      
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
        nestLevel   Nesting Level to be configured
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The interrupt controller is configured to use the specified nesting level.
 *
 *   @b  Writes
 *   @n  CPINTC_GLB_NEST_LEVEL_REG_GLB_NEST_LEVEL
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCNestingLevel nestLevel;
        CSL_CPINTC_HANDLE      hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_setNestingLevel (hnd, nestLevel);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_setNestingLevel
(
    CSL_CPINTC_Handle       hnd, 
    CSL_CPINTCNestingLevel  nestLevel
)
{
	Uint32 writeVal;

	writeVal = nestLevel & 0x1ff;
	writeVal |= 0x80000000;		/* set bit 31 auto_override */
    /* Write the GLB_NEST_LEVEL_REG with the specified nesting mode. */        
    ((CSL_CPINTC_RegsOvly)hnd)->GLB_NEST_LEVEL_REG = writeVal;
}

/** ============================================================================
 *   @n@b CSL_CPINTC_getNestingLevel
 *
 *   @b Description
 *   @n This API gets the current nesting level which is configured in the
 *      interrupt controller.
 * 
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
     @endverbatim
 * 
 *      
 *   <b> Return Value </b> 
 *       CSL_CPINTCNestingLevel - Current Nesting Level.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_GLB_NEST_LEVEL_REG_GLB_NEST_LEVEL
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTC_HANDLE      hnd;
        CSL_CPINTCNestingLevel nestLevel;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        nestLevel = CSL_CPINTC_getNestingLevel();
     @endverbatim
 * ===========================================================================
 */
static inline CSL_CPINTCNestingLevel CSL_CPINTC_getNestingLevel (CSL_CPINTC_Handle hnd)
{
    return (CSL_CPINTCNestingLevel)(((((CSL_CPINTC_RegsOvly)hnd)->GLB_NEST_LEVEL_REG) & (0x000001FFu)) >> (0x00000000u));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_enableAllHostInterrupt
 *
 *   @b Description
 *   @n This API enables all the Host Interrupts in the system.
 * 
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
     @endverbatim
 *       
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  All host interrupts are enabled in the system. Individual Host
 *       interrupts are still enabled/disabled from their individual 
 *       registers
 *
 *   @b  Writes
 *   @n  CPINTC_GLOBAL_ENABLE_HINT_REG_ENABLE_HINT_ANY=1
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTC_HANDLE     hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_enableAllHostInterrupt (hnd);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_enableAllHostInterrupt (CSL_CPINTC_Handle hnd)
{
    /* Enable all host interrupts by writing 1 to the register. */
    ((CSL_CPINTC_RegsOvly)hnd)->GLOBAL_ENABLE_HINT_REG = 
            (((1) << (0x00000000u)) & (0x00000001u));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_disableAllHostInterrupt
 *
 *   @b Description
 *   @n This API disables all the Host Interrupts in the system.
 * 
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
     @endverbatim
 *       
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  All host interrupts are disabled in the system. 
 *
 *   @b  Writes
 *   @n  CPINTC_GLOBAL_ENABLE_HINT_REG_ENABLE_HINT_ANY=0
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTC_HANDLE     hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_disableAllHostInterrupt (hnd);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_disableAllHostInterrupt (CSL_CPINTC_Handle hnd)
{
    /* Disable all host interrupts by writing 0 to the register. */
    ((CSL_CPINTC_RegsOvly)hnd)->GLOBAL_ENABLE_HINT_REG = 
            (((0) << (0x00000000u)) & (0x00000001u));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_enableSysInterrupt
 *
 *   @b Description
 *   @n This API enables the system interrupt in the interrupt controller.
 *      
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        sysIntr    System Interrupt which is to be enabled.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The specific System Interrupt is enabled in the controller and
 *       can now generate host interrupts.
 *
 *   @b  Writes
 *   @n  CPINTC_ENABLE_SET_INDEX_REG_ENABLE_SET_INDEX
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCSystemInterrupt     sysIntr;
        CSL_CPINTC_HANDLE             hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_enableSysInterrupt (hnd, sysIntr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_enableSysInterrupt 
(
    CSL_CPINTC_Handle           hnd,
    CSL_CPINTCSystemInterrupt   sysIntr
)
{
    /* Write the sysIntr to the ENABLE_SET_INDEX_REG to enable the interrupt. */
    ((CSL_CPINTC_RegsOvly)hnd)->ENABLE_SET_INDEX_REG = 
            (((sysIntr) << (0x00000000u)) & (0x000003FFu));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_disableSysInterrupt
 *
 *   @b Description
 *   @n This API disables the system interrupt in the interrupt controller.
 *      
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        sysIntr    System Interrupt which is to be disabled.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The specific System Interrupt is disabled in the controller and
 *       cannot generate host interrupts.
 *
 *   @b  Writes
 *   @n  CPINTC_ENABLE_CLR_INDEX_REG_ENABLE_CLR_INDEX
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCSystemInterrupt     sysIntr;
        CSL_CPINTC_HANDLE             hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_disableSysInterrupt (hnd, sysIntr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_disableSysInterrupt 
(
    CSL_CPINTC_Handle           hnd,
    CSL_CPINTCSystemInterrupt   sysIntr
)
{
    /* Write the sysIntr to the ENABLE_CLR_INDEX_REG to disable the interrupt. */
    ((CSL_CPINTC_RegsOvly)hnd)->ENABLE_CLR_INDEX_REG = 
            (((sysIntr) << (0x00000000u)) & (0x000003FFu));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_clearSysInterrupt
 *
 *   @b Description
 *   @n This API clear the system interrupt in the interrupt controller.
 *      
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        sysIntr    System Interrupt which is to be cleared.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The specific system interrupt has been serviced and is cleared. 
 *
 *   @b  Writes
 *   @n  CPINTC_STATUS_CLR_INDEX_REG_STATUS_CLR_INDEX
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCSystemInterrupt     sysIntr;
        CSL_CPINTC_HANDLE             hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0       
        ...
        CSL_CPINTC_clearSysInterrupt (hnd, sysIntr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_clearSysInterrupt 
(
    CSL_CPINTC_Handle           hnd,
    CSL_CPINTCSystemInterrupt   sysIntr
)
{
    /* Write the sysIntr to the STATUS_CLR_INDEX_REG to clear the interrupt. */
    ((CSL_CPINTC_RegsOvly)hnd)->STATUS_CLR_INDEX_REG = 
            (((sysIntr) << (0x00000000u)) & (0x000003FFu));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_enableHostInterrupt
 *
 *   @b Description
 *   @n This API enables the host interrupt in the interrupt controller.
 *      
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        sysIntr    Host Interrupt which is to be enabled.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The specific Host Interrupt is enabled in the controller and
 *       can now generate host interrupts.
 *
 *   @b  Writes
 *   @n  CPINTC_HINT_ENABLE_SET_INDEX_REG_HINT_ENABLE_SET_INDEX
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCHostInterrupt     hostIntr;
        CSL_CPINTC_HANDLE           hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0       
        ...
        CSL_CPINTC_enableHostInterrupt (hnd, hostIntr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_enableHostInterrupt 
(
    CSL_CPINTC_Handle           hnd,
    CSL_CPINTCHostInterrupt     hostIntr
)
{
    /* Write the hostIntr to the HINT_ENABLE_SET_INDEX_REG to enable the interrupt. */
    ((CSL_CPINTC_RegsOvly)hnd)->HINT_ENABLE_SET_INDEX_REG = 
            (((hostIntr) << (0x00000000u)) & (0x000000FFu));
}

/** ============================================================================
 *   @n@b CSL_CPINTCdisableHostInterrupt
 *
 *   @b Description
 *   @n This API disables the host interrupt in the interrupt controller.
 *      
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        sysIntr    Host Interrupt which is to be disabled.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  The specific Host Interrupt is enabled in the controller and
 *       can now generate host interrupts.
 *
 *   @b  Writes
 *   @n  CPINTC_HINT_ENABLE_CLR_INDEX_REG_HINT_ENABLE_CLR_INDEX
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCHostInterrupt     hostIntr;
        CSL_CPINTC_HANDLE           hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTCdisableHostInterrupt (hnd, hostIntr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_disableHostInterrupt
(
    CSL_CPINTC_Handle           hnd,
    CSL_CPINTCHostInterrupt     hostIntr
)
{
    /* Write the hostIntr to the HINT_ENABLE_CLR_INDEX_REG to disable the interrupt. */
    ((CSL_CPINTC_RegsOvly)hnd)->HINT_ENABLE_CLR_INDEX_REG = 
            (((hostIntr) << (0x00000000u)) & (0x000000FFu));        
}

/** ============================================================================
 *   @n@b CSL_CPINTC_isInterruptPending
 *
 *   @b Description
 *   @n This API is used to check if there are any pending interrupts active
 *      in the system or not.
 * 
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       TRUE  - Interrupts are pending.
 *       FALSE - No interrupts are pending.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_GLB_PRI_INTR_REG_GLB_NONE
 *
 *   @b  Example
 *   @verbatim
        Bool                pendingStatus;
        CSL_CPINTC_HANDLE   hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        pendingStatus = CSL_CPINTCisInterruptPending(hnd);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline Bool CSL_CPINTC_isInterruptPending (CSL_CPINTC_Handle hnd)
{
    Int32   pendStatus;
    
    /* Read the 'GLB_PRI_INTR_REG' to determine if there is a pending interrupt or not? */
    pendStatus = (((((CSL_CPINTC_RegsOvly)hnd)->GLB_PRI_INTR_REG) & (0x80000000u)) >> (0x0000001Fu));
    return (pendStatus == 1) ? 0 : 1; 
}

/** ============================================================================
 *   @n@b CSL_CPINTC_getPendingInterrupt
 *
 *   @b Description
 *   @n This API gets the current highest priority pending interrupt. This API
 *      should only be called after checking if there are pending interrupts 
 *      using the 'CSL_CPINTCisInterruptPending'.
 * 
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_CPINTCHostInterrupt - Highest Priority System Interrupt.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_GLB_PRI_INTR_REG_GLB_PRI_INTR
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCHostInterrupt intr;
        Bool                    pendingStatus;
        CSL_CPINTC_HANDLE       hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        pendingStatus = CSL_CPINTC_isInterruptPending(hnd);
        if (pendingStatus == TRUE)
        {
            intr = CSL_CPINTC_getPendingInterrupt(hnd);
        }
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_CPINTCSystemInterrupt CSL_CPINTC_getPendingInterrupt (CSL_CPINTC_Handle hnd)
{
    return (CSL_CPINTCHostInterrupt)((((((CSL_CPINTC_RegsOvly)hnd)->GLB_PRI_INTR_REG) & (0x000003FFu)) >> (0x00000000u)));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_isHostInterruptPending
 *
 *   @b Description
 *   @n This API is used to check if there are any pending interrupts active
 *      for a particular host.
 * 
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        hostIntr   This is the specific host interrupt output.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       TRUE  - Interrupts are pending.
 *       FALSE - No interrupts are pending.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_PRI_HINT_REG0_NONE_HINT_0..CPINTC_PRI_HINT_REG255_NONE_HINT_255
 *
 *   @b  Example
 *   @verbatim
        Bool                pendingStatus;
        CSL_CPINTC_HANDLE   hnd;
        CSL_CPINTCHostInterrupt host;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        pendingStatus = CSL_CPINTC_isHostInterruptPending(hnd, host);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline Bool CSL_CPINTC_isHostInterruptPending 
(
	CSL_CPINTC_Handle hnd, 
    CSL_CPINTCHostInterrupt     hostIntr
)
{
    Int32   pendStatus;
    
    /* Read the 'PRI_HINT_REG' to determine if there is a pending interrupt for this host */
    pendStatus = (((((CSL_CPINTC_RegsOvly)hnd)->PRI_HINT_REG[hostIntr]) & (0x80000000u)) >> (0x0000001Fu));
    return (pendStatus == 1) ? 0 : 1; 
}

/** ============================================================================
 *   @n@b CSL_CPINTC_getPendingHostInterrupt
 *
 *   @b Description
 *   @n This API gets the current highest priority pending interrupt for a
 *      given host. This API should only be called after checking if there
 *      are pending interrupts using the 'CSL_CPINTCisHostInterruptPending'.
 * 
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        hostIntr   This is the specific host interrupt output.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_CPINTCSystemInterrupt - Highest Priority System Interrupt.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_PRI_HINT_REG0_PRI_HINT_0..CPINTC_PRI_HINT_REG255_PRI_HINT_255
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCSystemInterrupt intr;
        Bool                      pendingStatus;
        CSL_CPINTC_HANDLE         hnd;
        CSL_CPINTCHostInterrupt   host;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        pendingStatus = CSL_CPINTC_isHostInterruptPending(hnd, host);
        if (pendingStatus == TRUE)
        {
            intr = CSL_CPINTC_getPendingHostInterrupt(hnd, host);
        }
        ...
     @endverbatim
 * ===========================================================================
 */
static inline CSL_CPINTCSystemInterrupt CSL_CPINTC_getPendingHostInterrupt 
(
	CSL_CPINTC_Handle hnd,
    CSL_CPINTCHostInterrupt     hostIntr
)
{
    return (CSL_CPINTCSystemInterrupt)((((((CSL_CPINTC_RegsOvly)hnd)->PRI_HINT_REG[hostIntr]) & (0x000003FFu)) >> (0x00000000u)));
}

/** ============================================================================
 *   @n@b CSL_CPINTC_getRawInterruptStatus
 *
 *   @b Description
 *   @n The function is used to get the contents of the RAW Interrupt status
 *      register. 
 * 
 *   @b Arguments
 *   @verbatim
        hnd         This is the handle to the CPINTC instance.
        index       RAW Status Index register which is to be read
        rawStatus   RAW Status which indicates which interrupts are pending.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *   @n None
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Reads
 *   @n  CPINTC_RAW_STATUS_REG
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTC_HANDLE   hnd;
        Uint32              rawStatus;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        // Check if there are any interrupts between 0-31 pending.
        CSL_CPINTC_getRawInterruptStatus(hnd, 0, &rawStatus);
        if (rawStatus != 0)
        {
            // An Interrupt from 0-31 is pending.
        }
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_getRawInterruptStatus 
(
    CSL_CPINTC_Handle   hnd,
    Uint8               index,
    Uint32*             rawStatus
)
{
    *rawStatus = ((CSL_CPINTC_RegsOvly)hnd)->RAW_STATUS_REG[index];
}

/** ============================================================================
 *   @n@b CSL_CPINTC_mapSystemIntrToChannel
 *
 *   @b Description
 *   @n This API is used to map a system interrupt to a specific channel.
 *
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        sysIntr    System Interrupt which is to be mapped
        channel    Channel Number to which the interrupt is to be mapped.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  CPINTC_CH_MAP_REG0_CH_MAP_0..CPINTC_CH_MAP_REG49_CH_MAP_196
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCSystemInterrupt sysIntr;
        CSL_CPINTCChannel         channel;
        CSL_CPINTC_HANDLE         hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_mapSystemIntrToChannel(hnd, sysIntr, channel);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_mapSystemIntrToChannel 
(
    CSL_CPINTC_Handle           hnd,
    CSL_CPINTCSystemInterrupt   sysIntr,
    CSL_CPINTCChannel           channel
)
{

    ((CSL_CPINTC_RegsOvly)hnd)->CH_MAP[sysIntr] = channel;
   return;
}

/** ============================================================================
 *   @n@b CSL_CPINTC_mapChannelToHostInterrupt
 *
 *   @b Description
 *   @n This API is used to map the channel to the host interrupt.
 *
 *   @b Arguments
 *   @verbatim
        hnd        This is the handle to the CPINTC instance.
        channel    Channel Number to be mapped
        sysIntr    Host Interrupt to which the channel is mapped to.
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_CPINTC_open() must be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Writes
 *   @n  CPINTC_HINT_MAP_REG0_HINT_MAP_0..CPINTC_HINT_MAP_REG49_HINT_MAP_196
 *
 *   @b  Example
 *   @verbatim
        CSL_CPINTCHostInterrupt hostIntr;
        CSL_CPINTCChannel       channel;
        CSL_CPINTC_HANDLE       hnd;
        ...
        hnd = CSL_CPINTC_open (0);    // Opens CPINTC Instance 0
        ...
        CSL_CPINTC_mapChannelToHostInterrupt(hnd, channel, hostIntr);
        ...
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_CPINTC_mapChannelToHostInterrupt 
(
    CSL_CPINTC_Handle         hnd,
    CSL_CPINTCChannel         channel,
    CSL_CPINTCHostInterrupt   hostIntr
)
{

    ((CSL_CPINTC_RegsOvly)hnd)->HINT_MAP[hostIntr] = channel;
    return;
}

/**
@}
*/




//#include <std.h>
//#include <xdc/std.h>
//#include <DataType.h>
//#include <hwi.h>
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
 *  @(#) ti.sysbios.hal; 2, 0, 0, 0,547; 3-20-2012 14:03:16; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
typedef void (*ti_sysbios_interfaces_IHwi_FuncPtr)(xdc_UArg);

/* Irp */
typedef xdc_UArg ti_sysbios_interfaces_IHwi_Irp;

/* HookSet */
struct ti_sysbios_interfaces_IHwi_HookSet {
    void (*registerFxn)(xdc_Int);
    void (*createFxn)(ti_sysbios_interfaces_IHwi_Handle, xdc_runtime_Error_Block*);
    void (*beginFxn)(ti_sysbios_interfaces_IHwi_Handle);
    void (*endFxn)(ti_sysbios_interfaces_IHwi_Handle);
    void (*deleteFxn)(ti_sysbios_interfaces_IHwi_Handle);
};

/* MaskingOption */
enum ti_sysbios_interfaces_IHwi_MaskingOption {
    ti_sysbios_interfaces_IHwi_MaskingOption_NONE,
    ti_sysbios_interfaces_IHwi_MaskingOption_ALL,
    ti_sysbios_interfaces_IHwi_MaskingOption_SELF,
    ti_sysbios_interfaces_IHwi_MaskingOption_BITMASK,
    ti_sysbios_interfaces_IHwi_MaskingOption_LOWER
};
typedef enum ti_sysbios_interfaces_IHwi_MaskingOption ti_sysbios_interfaces_IHwi_MaskingOption;

/* StackInfo */
struct ti_sysbios_interfaces_IHwi_StackInfo {
    xdc_SizeT hwiStackPeak;
    xdc_SizeT hwiStackSize;
    xdc_Ptr hwiStackBase;
};


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_interfaces_IHwi_Args__create {
    xdc_Int intNum;
    ti_sysbios_interfaces_IHwi_FuncPtr hwiFxn;
} ti_sysbios_interfaces_IHwi_Args__create;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_interfaces_IHwi_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_interfaces_IHwi_MaskingOption maskSetting;
    xdc_UArg arg;
    xdc_Bool enableInt;
    xdc_Int eventId;
    xdc_Int priority;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_interfaces_IHwi_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*getStackInfo)(ti_sysbios_interfaces_IHwi_StackInfo*, xdc_Bool);
    void (*startup)(void);
    xdc_UInt (*disable)(void);
    xdc_UInt (*enable)(void);
    void (*restore)(xdc_UInt);
    void (*switchFromBootStack)(void);
    void (*post)(xdc_UInt);
    xdc_Char* (*getTaskSP)(void);
    xdc_UInt (*disableInterrupt)(xdc_UInt);
    xdc_UInt (*enableInterrupt)(xdc_UInt);
    void (*restoreInterrupt)(xdc_UInt, xdc_UInt);
    void (*clearInterrupt)(xdc_UInt);
    ti_sysbios_interfaces_IHwi_FuncPtr (*getFunc)(void*, xdc_UArg*);
    void (*setFunc)(void*, ti_sysbios_interfaces_IHwi_FuncPtr, xdc_UArg);
    xdc_Ptr (*getHookContext)(void*, xdc_Int);
    void (*setHookContext)(void*, xdc_Int, xdc_Ptr);
    ti_sysbios_interfaces_IHwi_Irp (*getIrp)(void*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
extern const xdc_runtime_Types_Base ti_sysbios_interfaces_IHwi_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
static inline ti_sysbios_interfaces_IHwi_Handle ti_sysbios_interfaces_IHwi_create( ti_sysbios_interfaces_IHwi_Module __mod, xdc_Int intNum, ti_sysbios_interfaces_IHwi_FuncPtr hwiFxn, const ti_sysbios_interfaces_IHwi_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_interfaces_IHwi_Args__create __args;
    __args.intNum = intNum;
    __args.hwiFxn = hwiFxn;
    return (ti_sysbios_interfaces_IHwi_Handle) __mod->__sysp->__create(0, 0, &__args, (const xdc_UChar*)__prms, sizeof (ti_sysbios_interfaces_IHwi_Params), __eb);
}

/* delete */
static inline void ti_sysbios_interfaces_IHwi_delete( ti_sysbios_interfaces_IHwi_Handle* instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}

/* Handle_to_Module */
static inline ti_sysbios_interfaces_IHwi_Module ti_sysbios_interfaces_IHwi_Handle_to_Module( ti_sysbios_interfaces_IHwi_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_interfaces_IHwi_Handle_label( ti_sysbios_interfaces_IHwi_Handle inst, xdc_runtime_Types_Label* lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_sysbios_interfaces_IHwi_Module_id( ti_sysbios_interfaces_IHwi_Module mod )
{
    return mod->__sysp->__mid;
}

/* getStackInfo */
static inline xdc_Bool ti_sysbios_interfaces_IHwi_getStackInfo( ti_sysbios_interfaces_IHwi_Module __inst, ti_sysbios_interfaces_IHwi_StackInfo* stkInfo, xdc_Bool computeStackDepth )
{
    return __inst->getStackInfo(stkInfo, computeStackDepth);
}

/* startup */
static inline void ti_sysbios_interfaces_IHwi_startup( ti_sysbios_interfaces_IHwi_Module __inst )
{
    __inst->startup();
}

/* disable */
static inline xdc_UInt ti_sysbios_interfaces_IHwi_disable( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return __inst->disable();
}

/* enable */
static inline xdc_UInt ti_sysbios_interfaces_IHwi_enable( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return __inst->enable();
}

/* restore */
static inline void ti_sysbios_interfaces_IHwi_restore( ti_sysbios_interfaces_IHwi_Module __inst, xdc_UInt key )
{
    __inst->restore(key);
}

/* switchFromBootStack */
static inline void ti_sysbios_interfaces_IHwi_switchFromBootStack( ti_sysbios_interfaces_IHwi_Module __inst )
{
    __inst->switchFromBootStack();
}

/* post */
static inline void ti_sysbios_interfaces_IHwi_post( ti_sysbios_interfaces_IHwi_Module __inst, xdc_UInt intNum )
{
    __inst->post(intNum);
}

/* getTaskSP */
static inline xdc_Char* ti_sysbios_interfaces_IHwi_getTaskSP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return __inst->getTaskSP();
}

/* disableInterrupt */
static inline xdc_UInt ti_sysbios_interfaces_IHwi_disableInterrupt( ti_sysbios_interfaces_IHwi_Module __inst, xdc_UInt intNum )
{
    return __inst->disableInterrupt(intNum);
}

/* enableInterrupt */
static inline xdc_UInt ti_sysbios_interfaces_IHwi_enableInterrupt( ti_sysbios_interfaces_IHwi_Module __inst, xdc_UInt intNum )
{
    return __inst->enableInterrupt(intNum);
}

/* restoreInterrupt */
static inline void ti_sysbios_interfaces_IHwi_restoreInterrupt( ti_sysbios_interfaces_IHwi_Module __inst, xdc_UInt intNum, xdc_UInt key )
{
    __inst->restoreInterrupt(intNum, key);
}

/* clearInterrupt */
static inline void ti_sysbios_interfaces_IHwi_clearInterrupt( ti_sysbios_interfaces_IHwi_Module __inst, xdc_UInt intNum )
{
    __inst->clearInterrupt(intNum);
}

/* getFunc */
static inline ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_interfaces_IHwi_getFunc( ti_sysbios_interfaces_IHwi_Handle __inst, xdc_UArg* arg )
{
    return __inst->__fxns->getFunc((void*)__inst, arg);
}

/* setFunc */
static inline void ti_sysbios_interfaces_IHwi_setFunc( ti_sysbios_interfaces_IHwi_Handle __inst, ti_sysbios_interfaces_IHwi_FuncPtr fxn, xdc_UArg arg )
{
    __inst->__fxns->setFunc((void*)__inst, fxn, arg);
}

/* getHookContext */
static inline xdc_Ptr ti_sysbios_interfaces_IHwi_getHookContext( ti_sysbios_interfaces_IHwi_Handle __inst, xdc_Int id )
{
    return __inst->__fxns->getHookContext((void*)__inst, id);
}

/* setHookContext */
static inline void ti_sysbios_interfaces_IHwi_setHookContext( ti_sysbios_interfaces_IHwi_Handle __inst, xdc_Int id, xdc_Ptr hookContext )
{
    __inst->__fxns->setHookContext((void*)__inst, id, hookContext);
}

/* getIrp */
static inline ti_sysbios_interfaces_IHwi_Irp ti_sysbios_interfaces_IHwi_getIrp( ti_sysbios_interfaces_IHwi_Handle __inst )
{
    return __inst->__fxns->getIrp((void*)__inst);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getStackInfo_{FxnT,fxnP} */
typedef xdc_Bool (*ti_sysbios_interfaces_IHwi_getStackInfo_FxnT)(ti_sysbios_interfaces_IHwi_StackInfo*, xdc_Bool);
static inline ti_sysbios_interfaces_IHwi_getStackInfo_FxnT ti_sysbios_interfaces_IHwi_getStackInfo_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_getStackInfo_FxnT)__inst->getStackInfo;
}

/* startup_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_startup_FxnT)(void);
static inline ti_sysbios_interfaces_IHwi_startup_FxnT ti_sysbios_interfaces_IHwi_startup_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_startup_FxnT)__inst->startup;
}

/* disable_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_interfaces_IHwi_disable_FxnT)(void);
static inline ti_sysbios_interfaces_IHwi_disable_FxnT ti_sysbios_interfaces_IHwi_disable_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_disable_FxnT)__inst->disable;
}

/* enable_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_interfaces_IHwi_enable_FxnT)(void);
static inline ti_sysbios_interfaces_IHwi_enable_FxnT ti_sysbios_interfaces_IHwi_enable_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_enable_FxnT)__inst->enable;
}

/* restore_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_restore_FxnT)(xdc_UInt);
static inline ti_sysbios_interfaces_IHwi_restore_FxnT ti_sysbios_interfaces_IHwi_restore_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_restore_FxnT)__inst->restore;
}

/* switchFromBootStack_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_switchFromBootStack_FxnT)(void);
static inline ti_sysbios_interfaces_IHwi_switchFromBootStack_FxnT ti_sysbios_interfaces_IHwi_switchFromBootStack_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_switchFromBootStack_FxnT)__inst->switchFromBootStack;
}

/* post_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_post_FxnT)(xdc_UInt);
static inline ti_sysbios_interfaces_IHwi_post_FxnT ti_sysbios_interfaces_IHwi_post_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_post_FxnT)__inst->post;
}

/* getTaskSP_{FxnT,fxnP} */
typedef xdc_Char* (*ti_sysbios_interfaces_IHwi_getTaskSP_FxnT)(void);
static inline ti_sysbios_interfaces_IHwi_getTaskSP_FxnT ti_sysbios_interfaces_IHwi_getTaskSP_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_getTaskSP_FxnT)__inst->getTaskSP;
}

/* disableInterrupt_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_interfaces_IHwi_disableInterrupt_FxnT)(xdc_UInt);
static inline ti_sysbios_interfaces_IHwi_disableInterrupt_FxnT ti_sysbios_interfaces_IHwi_disableInterrupt_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_disableInterrupt_FxnT)__inst->disableInterrupt;
}

/* enableInterrupt_{FxnT,fxnP} */
typedef xdc_UInt (*ti_sysbios_interfaces_IHwi_enableInterrupt_FxnT)(xdc_UInt);
static inline ti_sysbios_interfaces_IHwi_enableInterrupt_FxnT ti_sysbios_interfaces_IHwi_enableInterrupt_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_enableInterrupt_FxnT)__inst->enableInterrupt;
}

/* restoreInterrupt_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_restoreInterrupt_FxnT)(xdc_UInt, xdc_UInt);
static inline ti_sysbios_interfaces_IHwi_restoreInterrupt_FxnT ti_sysbios_interfaces_IHwi_restoreInterrupt_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_restoreInterrupt_FxnT)__inst->restoreInterrupt;
}

/* clearInterrupt_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_clearInterrupt_FxnT)(xdc_UInt);
static inline ti_sysbios_interfaces_IHwi_clearInterrupt_FxnT ti_sysbios_interfaces_IHwi_clearInterrupt_fxnP( ti_sysbios_interfaces_IHwi_Module __inst )
{
    return (ti_sysbios_interfaces_IHwi_clearInterrupt_FxnT)__inst->clearInterrupt;
}

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_IHwi_FuncPtr (*ti_sysbios_interfaces_IHwi_getFunc_FxnT)(void*, xdc_UArg*);
static inline ti_sysbios_interfaces_IHwi_getFunc_FxnT ti_sysbios_interfaces_IHwi_getFunc_fxnP( ti_sysbios_interfaces_IHwi_Handle __inst )
{
    return (ti_sysbios_interfaces_IHwi_getFunc_FxnT)__inst->__fxns->getFunc;
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_setFunc_FxnT)(void*, ti_sysbios_interfaces_IHwi_FuncPtr, xdc_UArg);
static inline ti_sysbios_interfaces_IHwi_setFunc_FxnT ti_sysbios_interfaces_IHwi_setFunc_fxnP( ti_sysbios_interfaces_IHwi_Handle __inst )
{
    return (ti_sysbios_interfaces_IHwi_setFunc_FxnT)__inst->__fxns->setFunc;
}

/* getHookContext_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_interfaces_IHwi_getHookContext_FxnT)(void*, xdc_Int);
static inline ti_sysbios_interfaces_IHwi_getHookContext_FxnT ti_sysbios_interfaces_IHwi_getHookContext_fxnP( ti_sysbios_interfaces_IHwi_Handle __inst )
{
    return (ti_sysbios_interfaces_IHwi_getHookContext_FxnT)__inst->__fxns->getHookContext;
}

/* setHookContext_{FxnT,fxnP} */
typedef void (*ti_sysbios_interfaces_IHwi_setHookContext_FxnT)(void*, xdc_Int, xdc_Ptr);
static inline ti_sysbios_interfaces_IHwi_setHookContext_FxnT ti_sysbios_interfaces_IHwi_setHookContext_fxnP( ti_sysbios_interfaces_IHwi_Handle __inst )
{
    return (ti_sysbios_interfaces_IHwi_setHookContext_FxnT)__inst->__fxns->setHookContext;
}

/* getIrp_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_IHwi_Irp (*ti_sysbios_interfaces_IHwi_getIrp_FxnT)(void*);
static inline ti_sysbios_interfaces_IHwi_getIrp_FxnT ti_sysbios_interfaces_IHwi_getIrp_fxnP( ti_sysbios_interfaces_IHwi_Handle __inst )
{
    return (ti_sysbios_interfaces_IHwi_getIrp_FxnT)__inst->__fxns->getIrp;
}


/*
 * ======== EPILOGUE ========
 */




/*
 * ======== PREFIX ALIASES ========
 */

/*
 *  @(#) ti.sysbios.interfaces; 2, 0, 0, 0,545; 3-20-2012 14:03:22; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 *  @(#) ti.sysbios.interfaces; 2, 0, 0, 0,545; 3-20-2012 14:03:22; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */



/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* FuncPtr */
typedef ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_HwiProxy_FuncPtr;

/* Irp */
typedef ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_HwiProxy_Irp;

/* HookSet */
typedef ti_sysbios_interfaces_IHwi_HookSet ti_sysbios_hal_Hwi_HwiProxy_HookSet;

/* MaskingOption */
typedef ti_sysbios_interfaces_IHwi_MaskingOption ti_sysbios_hal_Hwi_HwiProxy_MaskingOption;

/* StackInfo */
typedef ti_sysbios_interfaces_IHwi_StackInfo ti_sysbios_hal_Hwi_HwiProxy_StackInfo;


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_hal_Hwi_HwiProxy_Args__create {
    xdc_Int intNum;
    ti_sysbios_interfaces_IHwi_FuncPtr hwiFxn;
} ti_sysbios_hal_Hwi_HwiProxy_Args__create;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__diagsEnabled;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__diagsEnabled ti_sysbios_hal_Hwi_HwiProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__diagsIncluded;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__diagsIncluded ti_sysbios_hal_Hwi_HwiProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_hal_Hwi_HwiProxy_Module__diagsMask;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__diagsMask ti_sysbios_hal_Hwi_HwiProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_HwiProxy_Module__gateObj;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__gateObj ti_sysbios_hal_Hwi_HwiProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_HwiProxy_Module__gatePrms;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__gatePrms ti_sysbios_hal_Hwi_HwiProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_hal_Hwi_HwiProxy_Module__id;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__id ti_sysbios_hal_Hwi_HwiProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerDefined;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerDefined ti_sysbios_hal_Hwi_HwiProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerObj;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerObj ti_sysbios_hal_Hwi_HwiProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn0;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn0 ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn1;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn1 ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn2;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn2 ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn4;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn4 ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn8;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn8 ti_sysbios_hal_Hwi_HwiProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_hal_Hwi_HwiProxy_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Module__startupDoneFxn ti_sysbios_hal_Hwi_HwiProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_hal_Hwi_HwiProxy_Object__count;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Object__count ti_sysbios_hal_Hwi_HwiProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_hal_Hwi_HwiProxy_Object__heap;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Object__heap ti_sysbios_hal_Hwi_HwiProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_hal_Hwi_HwiProxy_Object__sizeof;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Object__sizeof ti_sysbios_hal_Hwi_HwiProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_HwiProxy_Object__table;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_Object__table ti_sysbios_hal_Hwi_HwiProxy_Object__table__C;

/* dispatcherAutoNestingSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherAutoNestingSupport;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherAutoNestingSupport ti_sysbios_hal_Hwi_HwiProxy_dispatcherAutoNestingSupport__C;

/* dispatcherSwiSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherSwiSupport;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherSwiSupport ti_sysbios_hal_Hwi_HwiProxy_dispatcherSwiSupport__C;

/* dispatcherTaskSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherTaskSupport;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherTaskSupport ti_sysbios_hal_Hwi_HwiProxy_dispatcherTaskSupport__C;

/* dispatcherIrpTrackingSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherIrpTrackingSupport;
extern far const CT__ti_sysbios_hal_Hwi_HwiProxy_dispatcherIrpTrackingSupport ti_sysbios_hal_Hwi_HwiProxy_dispatcherIrpTrackingSupport__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_hal_Hwi_HwiProxy_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_interfaces_IHwi_MaskingOption maskSetting;
    xdc_UArg arg;
    xdc_Bool enableInt;
    xdc_Int eventId;
    xdc_Int priority;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_hal_Hwi_HwiProxy_Struct {
    const ti_sysbios_hal_Hwi_HwiProxy_Fxns__* __fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_hal_Hwi_HwiProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*getStackInfo)(ti_sysbios_interfaces_IHwi_StackInfo*, xdc_Bool);
    void (*startup)(void);
    xdc_UInt (*disable)(void);
    xdc_UInt (*enable)(void);
    void (*restore)(xdc_UInt);
    void (*switchFromBootStack)(void);
    void (*post)(xdc_UInt);
    xdc_Char* (*getTaskSP)(void);
    xdc_UInt (*disableInterrupt)(xdc_UInt);
    xdc_UInt (*enableInterrupt)(xdc_UInt);
    void (*restoreInterrupt)(xdc_UInt, xdc_UInt);
    void (*clearInterrupt)(xdc_UInt);
    ti_sysbios_interfaces_IHwi_FuncPtr (*getFunc)(ti_sysbios_hal_Hwi_HwiProxy_Handle, xdc_UArg*);
    void (*setFunc)(ti_sysbios_hal_Hwi_HwiProxy_Handle, ti_sysbios_interfaces_IHwi_FuncPtr, xdc_UArg);
    xdc_Ptr (*getHookContext)(ti_sysbios_hal_Hwi_HwiProxy_Handle, xdc_Int);
    void (*setHookContext)(ti_sysbios_hal_Hwi_HwiProxy_Handle, xdc_Int, xdc_Ptr);
    ti_sysbios_interfaces_IHwi_Irp (*getIrp)(ti_sysbios_hal_Hwi_HwiProxy_Handle);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const ti_sysbios_hal_Hwi_HwiProxy_Fxns__ ti_sysbios_hal_Hwi_HwiProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_hal_Hwi_HwiProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_hal_Hwi_HwiProxy_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_hal_Hwi_HwiProxy_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_hal_Hwi_HwiProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_hal_Hwi_HwiProxy_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */

extern xdc_Bool ti_sysbios_hal_Hwi_HwiProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_Proxy__delegate__S( void );

/* getStackInfo__E */

extern xdc_Bool ti_sysbios_hal_Hwi_HwiProxy_getStackInfo__E( ti_sysbios_interfaces_IHwi_StackInfo* stkInfo, xdc_Bool computeStackDepth );

extern xdc_Bool ti_sysbios_hal_Hwi_HwiProxy_getStackInfo__R( ti_sysbios_interfaces_IHwi_StackInfo* stkInfo, xdc_Bool computeStackDepth );

/* startup__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_startup__E( void );

extern void ti_sysbios_hal_Hwi_HwiProxy_startup__R( void );

/* disable__E */

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_disable__E( void );

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_disable__R( void );

/* enable__E */

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_enable__E( void );

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_enable__R( void );

/* restore__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_restore__E( xdc_UInt key );

extern void ti_sysbios_hal_Hwi_HwiProxy_restore__R( xdc_UInt key );

/* switchFromBootStack__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_switchFromBootStack__E( void );

extern void ti_sysbios_hal_Hwi_HwiProxy_switchFromBootStack__R( void );

/* post__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_post__E( xdc_UInt intNum );

extern void ti_sysbios_hal_Hwi_HwiProxy_post__R( xdc_UInt intNum );

/* getTaskSP__E */

extern xdc_Char* ti_sysbios_hal_Hwi_HwiProxy_getTaskSP__E( void );

extern xdc_Char* ti_sysbios_hal_Hwi_HwiProxy_getTaskSP__R( void );

/* disableInterrupt__E */

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_disableInterrupt__E( xdc_UInt intNum );

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_disableInterrupt__R( xdc_UInt intNum );

/* enableInterrupt__E */

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_enableInterrupt__E( xdc_UInt intNum );

extern xdc_UInt ti_sysbios_hal_Hwi_HwiProxy_enableInterrupt__R( xdc_UInt intNum );

/* restoreInterrupt__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_restoreInterrupt__E( xdc_UInt intNum, xdc_UInt key );

extern void ti_sysbios_hal_Hwi_HwiProxy_restoreInterrupt__R( xdc_UInt intNum, xdc_UInt key );

/* clearInterrupt__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_clearInterrupt__E( xdc_UInt intNum );

extern void ti_sysbios_hal_Hwi_HwiProxy_clearInterrupt__R( xdc_UInt intNum );

/* getFunc__E */

extern ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_HwiProxy_getFunc__E( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, xdc_UArg* arg );

extern ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_HwiProxy_getFunc__R( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, xdc_UArg* arg );

/* setFunc__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_setFunc__E( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, ti_sysbios_interfaces_IHwi_FuncPtr fxn, xdc_UArg arg );

extern void ti_sysbios_hal_Hwi_HwiProxy_setFunc__R( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, ti_sysbios_interfaces_IHwi_FuncPtr fxn, xdc_UArg arg );

/* getHookContext__E */

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_getHookContext__E( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, xdc_Int id );

extern xdc_Ptr ti_sysbios_hal_Hwi_HwiProxy_getHookContext__R( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, xdc_Int id );

/* setHookContext__E */

extern void ti_sysbios_hal_Hwi_HwiProxy_setHookContext__E( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

extern void ti_sysbios_hal_Hwi_HwiProxy_setHookContext__R( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

/* getIrp__E */

extern ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_HwiProxy_getIrp__E( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst );

extern ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_HwiProxy_getIrp__R( ti_sysbios_hal_Hwi_HwiProxy_Handle __inst );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_IHwi_FuncPtr (*ti_sysbios_hal_Hwi_HwiProxy_getFunc_FxnT)(void*, xdc_UArg*);
static inline ti_sysbios_hal_Hwi_HwiProxy_getFunc_FxnT ti_sysbios_hal_Hwi_HwiProxy_getFunc_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_HwiProxy_getFunc_FxnT)ti_sysbios_hal_Hwi_HwiProxy_getFunc__E; 
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Hwi_HwiProxy_setFunc_FxnT)(void*, ti_sysbios_interfaces_IHwi_FuncPtr, xdc_UArg);
static inline ti_sysbios_hal_Hwi_HwiProxy_setFunc_FxnT ti_sysbios_hal_Hwi_HwiProxy_setFunc_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_HwiProxy_setFunc_FxnT)ti_sysbios_hal_Hwi_HwiProxy_setFunc__E; 
}

/* getHookContext_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_hal_Hwi_HwiProxy_getHookContext_FxnT)(void*, xdc_Int);
static inline ti_sysbios_hal_Hwi_HwiProxy_getHookContext_FxnT ti_sysbios_hal_Hwi_HwiProxy_getHookContext_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_HwiProxy_getHookContext_FxnT)ti_sysbios_hal_Hwi_HwiProxy_getHookContext__E; 
}

/* setHookContext_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Hwi_HwiProxy_setHookContext_FxnT)(void*, xdc_Int, xdc_Ptr);
static inline ti_sysbios_hal_Hwi_HwiProxy_setHookContext_FxnT ti_sysbios_hal_Hwi_HwiProxy_setHookContext_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_HwiProxy_setHookContext_FxnT)ti_sysbios_hal_Hwi_HwiProxy_setHookContext__E; 
}

/* getIrp_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_IHwi_Irp (*ti_sysbios_hal_Hwi_HwiProxy_getIrp_FxnT)(void*);
static inline ti_sysbios_hal_Hwi_HwiProxy_getIrp_FxnT ti_sysbios_hal_Hwi_HwiProxy_getIrp_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_HwiProxy_getIrp_FxnT)ti_sysbios_hal_Hwi_HwiProxy_getIrp__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sysbios_interfaces_IHwi_Module ti_sysbios_hal_Hwi_HwiProxy_Module_upCast( void )
{
    return (ti_sysbios_interfaces_IHwi_Module)ti_sysbios_hal_Hwi_HwiProxy_Proxy__delegate__S();
}

/* Module_to_ti_sysbios_interfaces_IHwi */

/* Handle_upCast */
static inline ti_sysbios_interfaces_IHwi_Handle ti_sysbios_hal_Hwi_HwiProxy_Handle_upCast( ti_sysbios_hal_Hwi_HwiProxy_Handle i )
{
    return (ti_sysbios_interfaces_IHwi_Handle)i;
}

/* Handle_to_ti_sysbios_interfaces_IHwi */

/* Handle_downCast */
static inline ti_sysbios_hal_Hwi_HwiProxy_Handle ti_sysbios_hal_Hwi_HwiProxy_Handle_downCast( ti_sysbios_interfaces_IHwi_Handle i )
{
    ti_sysbios_interfaces_IHwi_Handle i2 = (ti_sysbios_interfaces_IHwi_Handle)i;
if (ti_sysbios_hal_Hwi_HwiProxy_Proxy__abstract__S()) return (ti_sysbios_hal_Hwi_HwiProxy_Handle)i;
    return (void*)i2->__fxns == (void*)ti_sysbios_hal_Hwi_HwiProxy_Proxy__delegate__S() ? (ti_sysbios_hal_Hwi_HwiProxy_Handle)i : 0;
}

/* Handle_from_ti_sysbios_interfaces_IHwi */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_hal_Hwi_HwiProxy_Module__id ti_sysbios_hal_Hwi_HwiProxy_Module_id( void ) 
{
    return ti_sysbios_hal_Hwi_HwiProxy_Module__id__C;
}

/* Proxy_abstract */

/* Proxy_delegate */

/* Params_init */
static inline void ti_sysbios_hal_Hwi_HwiProxy_Params_init( ti_sysbios_hal_Hwi_HwiProxy_Params* prms ) 
{
    if (prms) {
        ti_sysbios_hal_Hwi_HwiProxy_Params__init__S(prms, 0, sizeof(ti_sysbios_hal_Hwi_HwiProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_hal_Hwi_HwiProxy_Params_copy( ti_sysbios_hal_Hwi_HwiProxy_Params* dst, const ti_sysbios_hal_Hwi_HwiProxy_Params* src ) 
{
    if (dst) {
        ti_sysbios_hal_Hwi_HwiProxy_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_hal_Hwi_HwiProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* create */
static inline ti_sysbios_hal_Hwi_HwiProxy_Handle ti_sysbios_hal_Hwi_HwiProxy_create( xdc_Int intNum, ti_sysbios_interfaces_IHwi_FuncPtr hwiFxn, const ti_sysbios_hal_Hwi_HwiProxy_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_hal_Hwi_HwiProxy_Args__create __args;
    __args.intNum = intNum;
    __args.hwiFxn = hwiFxn;
    return (ti_sysbios_hal_Hwi_HwiProxy_Handle)ti_sysbios_hal_Hwi_HwiProxy_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_hal_Hwi_HwiProxy_Params), __eb);
}

/* delete */
static inline void ti_sysbios_hal_Hwi_HwiProxy_delete( ti_sysbios_hal_Hwi_HwiProxy_Handle* instp )
{
    ti_sysbios_hal_Hwi_HwiProxy_Object__delete__S(instp);
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
typedef ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_FuncPtr;

/* Irp */
typedef ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_Irp;

/* HookSet */
typedef ti_sysbios_interfaces_IHwi_HookSet ti_sysbios_hal_Hwi_HookSet;

/* MaskingOption */
typedef ti_sysbios_interfaces_IHwi_MaskingOption ti_sysbios_hal_Hwi_MaskingOption;

/* StackInfo */
typedef ti_sysbios_interfaces_IHwi_StackInfo ti_sysbios_hal_Hwi_StackInfo;

/* MaskingOption_NONE */

/* MaskingOption_ALL */

/* MaskingOption_SELF */

/* MaskingOption_BITMASK */

/* MaskingOption_LOWER */


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct ti_sysbios_hal_Hwi_Args__create {
    xdc_Int intNum;
    ti_sysbios_hal_Hwi_FuncPtr hwiFxn;
} ti_sysbios_hal_Hwi_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_hal_Hwi_Module__diagsEnabled;
extern far const CT__ti_sysbios_hal_Hwi_Module__diagsEnabled ti_sysbios_hal_Hwi_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_hal_Hwi_Module__diagsIncluded;
extern far const CT__ti_sysbios_hal_Hwi_Module__diagsIncluded ti_sysbios_hal_Hwi_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_hal_Hwi_Module__diagsMask;
extern far const CT__ti_sysbios_hal_Hwi_Module__diagsMask ti_sysbios_hal_Hwi_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_Module__gateObj;
extern far const CT__ti_sysbios_hal_Hwi_Module__gateObj ti_sysbios_hal_Hwi_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_Module__gatePrms;
extern far const CT__ti_sysbios_hal_Hwi_Module__gatePrms ti_sysbios_hal_Hwi_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_hal_Hwi_Module__id;
extern far const CT__ti_sysbios_hal_Hwi_Module__id ti_sysbios_hal_Hwi_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_Module__loggerDefined;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerDefined ti_sysbios_hal_Hwi_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_Module__loggerObj;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerObj ti_sysbios_hal_Hwi_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_hal_Hwi_Module__loggerFxn0;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerFxn0 ti_sysbios_hal_Hwi_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_hal_Hwi_Module__loggerFxn1;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerFxn1 ti_sysbios_hal_Hwi_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_hal_Hwi_Module__loggerFxn2;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerFxn2 ti_sysbios_hal_Hwi_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_hal_Hwi_Module__loggerFxn4;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerFxn4 ti_sysbios_hal_Hwi_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_hal_Hwi_Module__loggerFxn8;
extern far const CT__ti_sysbios_hal_Hwi_Module__loggerFxn8 ti_sysbios_hal_Hwi_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_hal_Hwi_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_hal_Hwi_Module__startupDoneFxn ti_sysbios_hal_Hwi_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_hal_Hwi_Object__count;
extern far const CT__ti_sysbios_hal_Hwi_Object__count ti_sysbios_hal_Hwi_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_hal_Hwi_Object__heap;
extern far const CT__ti_sysbios_hal_Hwi_Object__heap ti_sysbios_hal_Hwi_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_hal_Hwi_Object__sizeof;
extern far const CT__ti_sysbios_hal_Hwi_Object__sizeof ti_sysbios_hal_Hwi_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_hal_Hwi_Object__table;
extern far const CT__ti_sysbios_hal_Hwi_Object__table ti_sysbios_hal_Hwi_Object__table__C;

/* dispatcherAutoNestingSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_dispatcherAutoNestingSupport;
extern far const CT__ti_sysbios_hal_Hwi_dispatcherAutoNestingSupport ti_sysbios_hal_Hwi_dispatcherAutoNestingSupport__C;

/* dispatcherSwiSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_dispatcherSwiSupport;
extern far const CT__ti_sysbios_hal_Hwi_dispatcherSwiSupport ti_sysbios_hal_Hwi_dispatcherSwiSupport__C;

/* dispatcherTaskSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_dispatcherTaskSupport;
extern far const CT__ti_sysbios_hal_Hwi_dispatcherTaskSupport ti_sysbios_hal_Hwi_dispatcherTaskSupport__C;

/* dispatcherIrpTrackingSupport */
typedef xdc_Bool CT__ti_sysbios_hal_Hwi_dispatcherIrpTrackingSupport;
extern far const CT__ti_sysbios_hal_Hwi_dispatcherIrpTrackingSupport ti_sysbios_hal_Hwi_dispatcherIrpTrackingSupport__C;

/* E_stackOverflow */
typedef xdc_runtime_Error_Id CT__ti_sysbios_hal_Hwi_E_stackOverflow;
extern far const CT__ti_sysbios_hal_Hwi_E_stackOverflow ti_sysbios_hal_Hwi_E_stackOverflow__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_sysbios_hal_Hwi_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_sysbios_interfaces_IHwi_MaskingOption maskSetting;
    xdc_UArg arg;
    xdc_Bool enableInt;
    xdc_Int eventId;
    xdc_Int priority;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_sysbios_hal_Hwi_Struct {
    const ti_sysbios_hal_Hwi_Fxns__* __fxns;
    ti_sysbios_hal_Hwi_HwiProxy_Handle __f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_hal_Hwi_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*getStackInfo)(ti_sysbios_interfaces_IHwi_StackInfo*, xdc_Bool);
    void (*startup)(void);
    xdc_UInt (*disable)(void);
    xdc_UInt (*enable)(void);
    void (*restore)(xdc_UInt);
    void (*switchFromBootStack)(void);
    void (*post)(xdc_UInt);
    xdc_Char* (*getTaskSP)(void);
    xdc_UInt (*disableInterrupt)(xdc_UInt);
    xdc_UInt (*enableInterrupt)(xdc_UInt);
    void (*restoreInterrupt)(xdc_UInt, xdc_UInt);
    void (*clearInterrupt)(xdc_UInt);
    ti_sysbios_interfaces_IHwi_FuncPtr (*getFunc)(ti_sysbios_hal_Hwi_Handle, xdc_UArg*);
    void (*setFunc)(ti_sysbios_hal_Hwi_Handle, ti_sysbios_interfaces_IHwi_FuncPtr, xdc_UArg);
    xdc_Ptr (*getHookContext)(ti_sysbios_hal_Hwi_Handle, xdc_Int);
    void (*setHookContext)(ti_sysbios_hal_Hwi_Handle, xdc_Int, xdc_Ptr);
    ti_sysbios_interfaces_IHwi_Irp (*getIrp)(ti_sysbios_hal_Hwi_Handle);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
extern const ti_sysbios_hal_Hwi_Fxns__ ti_sysbios_hal_Hwi_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int ti_sysbios_hal_Hwi_Module_startup__E( xdc_Int state );

extern xdc_Int ti_sysbios_hal_Hwi_Module_startup__F( xdc_Int state );

extern xdc_Int ti_sysbios_hal_Hwi_Module_startup__R( xdc_Int state );

/* Instance_init__F */

extern int ti_sysbios_hal_Hwi_Instance_init__F( ti_sysbios_hal_Hwi_Object*, xdc_Int intNum, ti_sysbios_hal_Hwi_FuncPtr hwiFxn, const ti_sysbios_hal_Hwi_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */

extern void ti_sysbios_hal_Hwi_Instance_finalize__F( ti_sysbios_hal_Hwi_Object* , int );

/* Instance_init__R */

extern int ti_sysbios_hal_Hwi_Instance_init__R( ti_sysbios_hal_Hwi_Object*, xdc_Int intNum, ti_sysbios_hal_Hwi_FuncPtr hwiFxn, const ti_sysbios_hal_Hwi_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */

extern void ti_sysbios_hal_Hwi_Instance_finalize__R( ti_sysbios_hal_Hwi_Object* , int );

/* Handle__label__S */

extern xdc_runtime_Types_Label* ti_sysbios_hal_Hwi_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_hal_Hwi_Module__startupDone__S( void );

/* Object__create__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */

extern void ti_sysbios_hal_Hwi_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */

extern void ti_sysbios_hal_Hwi_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_Object__first__S( void );

/* Object__next__S */

extern xdc_Ptr ti_sysbios_hal_Hwi_Object__next__S( xdc_Ptr obj );

/* Params__init__S */

extern void ti_sysbios_hal_Hwi_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* getStackInfo__E */

extern xdc_Bool ti_sysbios_hal_Hwi_getStackInfo__E( ti_sysbios_interfaces_IHwi_StackInfo* stkInfo, xdc_Bool computeStackDepth );

extern xdc_Bool ti_sysbios_hal_Hwi_getStackInfo__F( ti_sysbios_interfaces_IHwi_StackInfo* stkInfo, xdc_Bool computeStackDepth );
extern xdc_Bool ti_sysbios_hal_Hwi_getStackInfo__R( ti_sysbios_interfaces_IHwi_StackInfo* stkInfo, xdc_Bool computeStackDepth );

/* startup__E */

extern void ti_sysbios_hal_Hwi_startup__E( void );

extern void ti_sysbios_hal_Hwi_startup__F( void );
extern void ti_sysbios_hal_Hwi_startup__R( void );

/* switchFromBootStack__E */

extern void ti_sysbios_hal_Hwi_switchFromBootStack__E( void );

extern void ti_sysbios_hal_Hwi_switchFromBootStack__F( void );
extern void ti_sysbios_hal_Hwi_switchFromBootStack__R( void );

/* post__E */

extern void ti_sysbios_hal_Hwi_post__E( xdc_UInt intNum );

extern void ti_sysbios_hal_Hwi_post__F( xdc_UInt intNum );
extern void ti_sysbios_hal_Hwi_post__R( xdc_UInt intNum );

/* getTaskSP__E */

extern xdc_Char* ti_sysbios_hal_Hwi_getTaskSP__E( void );

extern xdc_Char* ti_sysbios_hal_Hwi_getTaskSP__F( void );
extern xdc_Char* ti_sysbios_hal_Hwi_getTaskSP__R( void );

/* disableInterrupt__E */

extern xdc_UInt ti_sysbios_hal_Hwi_disableInterrupt__E( xdc_UInt intNum );

extern xdc_UInt ti_sysbios_hal_Hwi_disableInterrupt__F( xdc_UInt intNum );
extern xdc_UInt ti_sysbios_hal_Hwi_disableInterrupt__R( xdc_UInt intNum );

/* enableInterrupt__E */

extern xdc_UInt ti_sysbios_hal_Hwi_enableInterrupt__E( xdc_UInt intNum );

extern xdc_UInt ti_sysbios_hal_Hwi_enableInterrupt__F( xdc_UInt intNum );
extern xdc_UInt ti_sysbios_hal_Hwi_enableInterrupt__R( xdc_UInt intNum );

/* restoreInterrupt__E */

extern void ti_sysbios_hal_Hwi_restoreInterrupt__E( xdc_UInt intNum, xdc_UInt key );

extern void ti_sysbios_hal_Hwi_restoreInterrupt__F( xdc_UInt intNum, xdc_UInt key );
extern void ti_sysbios_hal_Hwi_restoreInterrupt__R( xdc_UInt intNum, xdc_UInt key );

/* clearInterrupt__E */

extern void ti_sysbios_hal_Hwi_clearInterrupt__E( xdc_UInt intNum );

extern void ti_sysbios_hal_Hwi_clearInterrupt__F( xdc_UInt intNum );
extern void ti_sysbios_hal_Hwi_clearInterrupt__R( xdc_UInt intNum );

/* getFunc__E */

extern ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_getFunc__E( ti_sysbios_hal_Hwi_Handle __inst, xdc_UArg* arg );

extern ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_getFunc__F( ti_sysbios_hal_Hwi_Object* __inst, xdc_UArg* arg );
extern ti_sysbios_interfaces_IHwi_FuncPtr ti_sysbios_hal_Hwi_getFunc__R( ti_sysbios_hal_Hwi_Handle __inst, xdc_UArg* arg );

/* setFunc__E */

extern void ti_sysbios_hal_Hwi_setFunc__E( ti_sysbios_hal_Hwi_Handle __inst, ti_sysbios_interfaces_IHwi_FuncPtr fxn, xdc_UArg arg );

extern void ti_sysbios_hal_Hwi_setFunc__F( ti_sysbios_hal_Hwi_Object* __inst, ti_sysbios_interfaces_IHwi_FuncPtr fxn, xdc_UArg arg );
extern void ti_sysbios_hal_Hwi_setFunc__R( ti_sysbios_hal_Hwi_Handle __inst, ti_sysbios_interfaces_IHwi_FuncPtr fxn, xdc_UArg arg );

/* getIrp__E */

extern ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_getIrp__E( ti_sysbios_hal_Hwi_Handle __inst );

extern ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_getIrp__F( ti_sysbios_hal_Hwi_Object* __inst );
extern ti_sysbios_interfaces_IHwi_Irp ti_sysbios_hal_Hwi_getIrp__R( ti_sysbios_hal_Hwi_Handle __inst );

/* getHookContext__E */

extern xdc_Ptr ti_sysbios_hal_Hwi_getHookContext__E( ti_sysbios_hal_Hwi_Handle __inst, xdc_Int id );

extern xdc_Ptr ti_sysbios_hal_Hwi_getHookContext__F( ti_sysbios_hal_Hwi_Object* __inst, xdc_Int id );
extern xdc_Ptr ti_sysbios_hal_Hwi_getHookContext__R( ti_sysbios_hal_Hwi_Handle __inst, xdc_Int id );

/* setHookContext__E */

extern void ti_sysbios_hal_Hwi_setHookContext__E( ti_sysbios_hal_Hwi_Handle __inst, xdc_Int id, xdc_Ptr hookContext );

extern void ti_sysbios_hal_Hwi_setHookContext__F( ti_sysbios_hal_Hwi_Object* __inst, xdc_Int id, xdc_Ptr hookContext );
extern void ti_sysbios_hal_Hwi_setHookContext__R( ti_sysbios_hal_Hwi_Handle __inst, xdc_Int id, xdc_Ptr hookContext );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getFunc_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_IHwi_FuncPtr (*ti_sysbios_hal_Hwi_getFunc_FxnT)(void*, xdc_UArg*);
static inline ti_sysbios_hal_Hwi_getFunc_FxnT ti_sysbios_hal_Hwi_getFunc_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_getFunc_FxnT)ti_sysbios_hal_Hwi_getFunc__E; 
}

/* setFunc_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Hwi_setFunc_FxnT)(void*, ti_sysbios_interfaces_IHwi_FuncPtr, xdc_UArg);
static inline ti_sysbios_hal_Hwi_setFunc_FxnT ti_sysbios_hal_Hwi_setFunc_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_setFunc_FxnT)ti_sysbios_hal_Hwi_setFunc__E; 
}

/* getIrp_{FxnT,fxnP} */
typedef ti_sysbios_interfaces_IHwi_Irp (*ti_sysbios_hal_Hwi_getIrp_FxnT)(void*);
static inline ti_sysbios_hal_Hwi_getIrp_FxnT ti_sysbios_hal_Hwi_getIrp_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_getIrp_FxnT)ti_sysbios_hal_Hwi_getIrp__E; 
}

/* getHookContext_{FxnT,fxnP} */
typedef xdc_Ptr (*ti_sysbios_hal_Hwi_getHookContext_FxnT)(void*, xdc_Int);
static inline ti_sysbios_hal_Hwi_getHookContext_FxnT ti_sysbios_hal_Hwi_getHookContext_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_getHookContext_FxnT)ti_sysbios_hal_Hwi_getHookContext__E; 
}

/* setHookContext_{FxnT,fxnP} */
typedef void (*ti_sysbios_hal_Hwi_setHookContext_FxnT)(void*, xdc_Int, xdc_Ptr);
static inline ti_sysbios_hal_Hwi_setHookContext_FxnT ti_sysbios_hal_Hwi_setHookContext_fxnP( void )
{
    return (ti_sysbios_hal_Hwi_setHookContext_FxnT)ti_sysbios_hal_Hwi_setHookContext__E; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sysbios_interfaces_IHwi_Module ti_sysbios_hal_Hwi_Module_upCast( void )
{
    return (ti_sysbios_interfaces_IHwi_Module)&ti_sysbios_hal_Hwi_Module__FXNS__C;
}

/* Module_to_ti_sysbios_interfaces_IHwi */

/* Handle_upCast */
static inline ti_sysbios_interfaces_IHwi_Handle ti_sysbios_hal_Hwi_Handle_upCast( ti_sysbios_hal_Hwi_Handle i )
{
    return (ti_sysbios_interfaces_IHwi_Handle)i;
}

/* Handle_to_ti_sysbios_interfaces_IHwi */

/* Handle_downCast */
static inline ti_sysbios_hal_Hwi_Handle ti_sysbios_hal_Hwi_Handle_downCast( ti_sysbios_interfaces_IHwi_Handle i )
{
    ti_sysbios_interfaces_IHwi_Handle i2 = (ti_sysbios_interfaces_IHwi_Handle)i;
    return (void*)i2->__fxns == (void*)&ti_sysbios_hal_Hwi_Module__FXNS__C ? (ti_sysbios_hal_Hwi_Handle)i : 0;
}

/* Handle_from_ti_sysbios_interfaces_IHwi */


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_hal_Hwi_Module__id ti_sysbios_hal_Hwi_Module_id( void ) 
{
    return ti_sysbios_hal_Hwi_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_hal_Hwi_Module_hasMask( void ) 
{
    return ti_sysbios_hal_Hwi_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_hal_Hwi_Module_getMask( void ) 
{
    return ti_sysbios_hal_Hwi_Module__diagsMask__C != 0 ? *ti_sysbios_hal_Hwi_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_hal_Hwi_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_hal_Hwi_Module__diagsMask__C != 0) *ti_sysbios_hal_Hwi_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_sysbios_hal_Hwi_Params_init( ti_sysbios_hal_Hwi_Params* prms ) 
{
    if (prms) {
        ti_sysbios_hal_Hwi_Params__init__S(prms, 0, sizeof(ti_sysbios_hal_Hwi_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_sysbios_hal_Hwi_Params_copy( ti_sysbios_hal_Hwi_Params* dst, const ti_sysbios_hal_Hwi_Params* src ) 
{
    if (dst) {
        ti_sysbios_hal_Hwi_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_sysbios_hal_Hwi_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */

/* Object_sizeof */

/* Object_get */
static inline ti_sysbios_hal_Hwi_Handle ti_sysbios_hal_Hwi_Object_get( ti_sysbios_hal_Hwi_Instance_State* oarr, int i ) 
{
    return (ti_sysbios_hal_Hwi_Handle)ti_sysbios_hal_Hwi_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_sysbios_hal_Hwi_Handle ti_sysbios_hal_Hwi_Object_first( void )
{
    return (ti_sysbios_hal_Hwi_Handle)ti_sysbios_hal_Hwi_Object__first__S();
}

/* Object_next */
static inline ti_sysbios_hal_Hwi_Handle ti_sysbios_hal_Hwi_Object_next( ti_sysbios_hal_Hwi_Object* obj )
{
    return (ti_sysbios_hal_Hwi_Handle)ti_sysbios_hal_Hwi_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_sysbios_hal_Hwi_Handle_label( ti_sysbios_hal_Hwi_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_sysbios_hal_Hwi_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_sysbios_hal_Hwi_Handle_name( ti_sysbios_hal_Hwi_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_sysbios_hal_Hwi_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_sysbios_hal_Hwi_Handle ti_sysbios_hal_Hwi_create( xdc_Int intNum, ti_sysbios_hal_Hwi_FuncPtr hwiFxn, const ti_sysbios_hal_Hwi_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_hal_Hwi_Args__create __args;
    __args.intNum = intNum;
    __args.hwiFxn = hwiFxn;
    return (ti_sysbios_hal_Hwi_Handle)ti_sysbios_hal_Hwi_Object__create__S(0, 0, &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_hal_Hwi_Params), __eb);
}

/* construct */
static inline void ti_sysbios_hal_Hwi_construct( ti_sysbios_hal_Hwi_Struct* __obj, xdc_Int intNum, ti_sysbios_hal_Hwi_FuncPtr hwiFxn, const ti_sysbios_hal_Hwi_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_sysbios_hal_Hwi_Args__create __args;
    __args.intNum = intNum;
    __args.hwiFxn = hwiFxn;
    ti_sysbios_hal_Hwi_Object__create__S(__obj, sizeof (ti_sysbios_hal_Hwi_Struct), &__args, (const xdc_UChar*)__prms, sizeof(ti_sysbios_hal_Hwi_Params), __eb);
}

/* delete */
static inline void ti_sysbios_hal_Hwi_delete( ti_sysbios_hal_Hwi_Handle* instp )
{
    ti_sysbios_hal_Hwi_Object__delete__S(instp);
}

/* destruct */
static inline void ti_sysbios_hal_Hwi_destruct( ti_sysbios_hal_Hwi_Struct* obj )
{
    ti_sysbios_hal_Hwi_Object__destruct__S(obj);
}

/* handle */
static inline ti_sysbios_hal_Hwi_Handle ti_sysbios_hal_Hwi_handle( ti_sysbios_hal_Hwi_Struct* str )
{
    return (ti_sysbios_hal_Hwi_Handle)str;
}

/* struct */
static inline ti_sysbios_hal_Hwi_Struct* ti_sysbios_hal_Hwi_struct( ti_sysbios_hal_Hwi_Handle inst )
{
    return (ti_sysbios_hal_Hwi_Struct*)inst;
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
 * Use intrinsics for ALL C6x and ARM 32bit targets (excluding arm M3)
 */



/*
 *  ======== Hwi_disable ========
 */

/*
 *  ======== Hwi_enable ========
 */

/*
 *  ======== Hwi_restore ========
 */


/*
 *  @(#) ti.sysbios.hal; 2, 0, 0, 0,547; 3-20-2012 14:03:16; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

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
 * ======== PREFIX ALIASES ========
 */



/* module prefix */


/*
 *  @(#) ti.sysbios.hal; 2, 0, 0, 0,547; 3-20-2012 14:03:16; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

//#include <log.h>
//#include<xdc/runtime/LoggerBuf.h> // should be removed , this is not the required one
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

//#include <c64.h>
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
 *  @(#) ti.targets; 1, 0, 3,531; 4-27-2012 17:07:37; /db/ztree/library/trees/xdctargets/xdctargets-f21x/src/ xlibrary

 */

/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <IntrTable.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for creating 
//  and reading the Interrupt Table 
//
//  Dependencies, Limitations, and Design Notes:
//  	Interrupt module.
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/

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


//#include <csl_cic.h>//in CCS5 this include file is not present, that's why removed by remesh
//#include <csl_intcAux.h>//in CCS5 this include file is not present, that's why removed by remesh

typedef struct {
	CSL_IntcEventId 		nIntcEventId;
	CSL_IntcVectId 			eIntcVectorId;
	BOOL					bCicRequired;
//	CSL_CicEventId			nCicEventId; // not present in ccs5.2
//	CSL_CicEctlEvtId		eCicVectorId; // not present in ccs5.2
	CSL_CPINTCSystemInterrupt   SysInt;
	CSL_CPINTCHostInterrupt		HostInt;
} IntrTable;

//Add the New Interrupt Item name here
typedef enum {
	INTR_ITEM_GPIO_13 = 0,
	INTR_ITEM_ETH_TX,
	INTR_ITEM_ETH_RX,
	INTR_ITEM_RX_MCBSP_FLASH,
	INTR_ITEM_RX_MCBSP_FPGA,
//	INTR_ITEM_TIMER_1,
	INTR_ITEM_TIMER_2,
	INTR_ITEM_IPC,
	INTR_ITEM_TIMER_3,
	INTR_ITEM_SRIO_ERROR,
	INTR_ITEM_SRIO_LSU,
	INTR_ITEM_SRIO_DBELL,
	INTR_ITEM_TIMER_13,
	MAX_INTR_ITEM
} IntrItem;

extern void IntrDB_GetIntrTableParam(IntrTable *pThis, IntrItem eName);


/*************************************EOF*************************************/
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
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y22
 */



/*
 * ======== module ti.sysbios.family.c66.tci66xx.CpIntc ========
 */

typedef struct ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap;
typedef struct ti_sysbios_family_c66_tci66xx_CpIntc_DispatchTabElem ti_sysbios_family_c66_tci66xx_CpIntc_DispatchTabElem;
typedef struct ti_sysbios_family_c66_tci66xx_CpIntc_Module_State ti_sysbios_family_c66_tci66xx_CpIntc_Module_State;



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
typedef void (*ti_sysbios_family_c66_tci66xx_CpIntc_FuncPtr)(xdc_UArg);

/* RegisterMap */
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_5C;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_5C[9];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_5C __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_5C;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_98;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_98[26];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_98 __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_98;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PPMR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PPMR[64];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PPMR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PPMR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SRSR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SRSR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SRSR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SRSR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SECR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SECR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SECR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SECR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ESR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ESR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ESR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ESR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ECR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ECR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ECR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ECR;
typedef xdc_UInt8 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__CMR;
typedef xdc_UInt8 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__CMR[1024];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__CMR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__CMR;
typedef xdc_UInt8 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIMR;
typedef xdc_UInt8 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIMR[256];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIMR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIMR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPIR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPIR[256];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPIR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPIR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__TR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__TR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__TR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__TR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__WER;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__WER[64];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__WER __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__WER;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__DSR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__DSR[64];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__DSR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__DSR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SER;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SER[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SER __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SER;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SDR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SDR[32];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SDR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SDR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HINLR;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HINLR[256];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HINLR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HINLR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIER;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIER[8];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIER __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIER;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1520;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1520[56];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1520 __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1520;
typedef xdc_Ptr* __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPVR;
typedef xdc_Ptr* __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPVR[256];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPVR __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPVR;
typedef xdc_UInt32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1A00;
typedef xdc_UInt32 __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1A00[384];
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1A00 __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1A00;
struct ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap {
    xdc_UInt32 REV;
    xdc_UInt32 CR;
    xdc_UInt32 RES_08;
    xdc_UInt32 HCR;
    xdc_UInt32 GER;
    xdc_UInt32 RES_14;
    xdc_UInt32 RES_18;
    xdc_UInt32 GNLR;
    xdc_UInt32 SISR;
    xdc_UInt32 SICR;
    xdc_UInt32 EISR;
    xdc_UInt32 EICR;
    xdc_UInt32 GWER;
    xdc_UInt32 HIEISR;
    xdc_UInt32 HIDISR;
    xdc_UInt32 RES_3C;
    xdc_UInt32 PPR;
    xdc_UInt32 RES_44;
    xdc_UInt32 RES_48;
    xdc_UInt32 RES_4C;
    xdc_Ptr* VBR;
    xdc_UInt32 VSR;
    xdc_Ptr VNR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_5C RES_5C;
    xdc_Int32 GPIR;
    xdc_Ptr* GPVR;
    xdc_UInt32 RES_88;
    xdc_UInt32 RES_8C;
    xdc_UInt32 GSIER;
    xdc_UInt32 SPIR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES_98 RES_98;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PPMR PPMR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SRSR SRSR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SECR SECR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ESR ESR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__ECR ECR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__CMR CMR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIMR HIMR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPIR HIPIR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__PR PR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__TR TR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__WER WER;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__DSR DSR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SER SER;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__SDR SDR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HINLR HINLR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIER HIER;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1520 RES1520;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__HIPVR HIPVR;
    __TA_ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap__RES1A00 RES1A00;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* DispatchTabElem */
struct ti_sysbios_family_c66_tci66xx_CpIntc_DispatchTabElem {
    ti_sysbios_family_c66_tci66xx_CpIntc_FuncPtr fxn;
    xdc_UArg arg;
};

/* Module_State */
typedef volatile ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap* __T1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__controller;
typedef volatile ti_sysbios_family_c66_tci66xx_CpIntc_RegisterMap* *__ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__controller;
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__controller __TA_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__controller;
typedef xdc_Bits32 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__initSIER;
typedef xdc_Bits32 *__ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__initSIER;
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__initSIER __TA_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__initSIER;
typedef xdc_UInt8 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__hostIntToSysInt;
typedef xdc_UInt8 *__ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__hostIntToSysInt;
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__hostIntToSysInt __TA_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__hostIntToSysInt;
typedef ti_sysbios_family_c66_tci66xx_CpIntc_DispatchTabElem __T1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__dispatchTab;
typedef ti_sysbios_family_c66_tci66xx_CpIntc_DispatchTabElem *__ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__dispatchTab;
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__dispatchTab __TA_ti_sysbios_family_c66_tci66xx_CpIntc_Module_State__dispatchTab;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsEnabled;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsEnabled ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsIncluded;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsIncluded ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__gateObj;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__gateObj ti_sysbios_family_c66_tci66xx_CpIntc_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__gatePrms;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__gatePrms ti_sysbios_family_c66_tci66xx_CpIntc_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__id;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__id ti_sysbios_family_c66_tci66xx_CpIntc_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerDefined;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerDefined ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerObj;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerObj ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn0;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn0 ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn1;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn1 ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn2;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn2 ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn4;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn4 ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn8;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn8 ti_sysbios_family_c66_tci66xx_CpIntc_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__startupDoneFxn)(void);
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__startupDoneFxn ti_sysbios_family_c66_tci66xx_CpIntc_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__count;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__count ti_sysbios_family_c66_tci66xx_CpIntc_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__heap;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__heap ti_sysbios_family_c66_tci66xx_CpIntc_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__sizeof;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__sizeof ti_sysbios_family_c66_tci66xx_CpIntc_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__table;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_Object__table ti_sysbios_family_c66_tci66xx_CpIntc_Object__table__C;

/* E_unpluggedSysInt */
typedef xdc_runtime_Error_Id CT__ti_sysbios_family_c66_tci66xx_CpIntc_E_unpluggedSysInt;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_E_unpluggedSysInt ti_sysbios_family_c66_tci66xx_CpIntc_E_unpluggedSysInt__C;

/* numSysInts */
typedef xdc_UInt32 CT__ti_sysbios_family_c66_tci66xx_CpIntc_numSysInts;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_numSysInts ti_sysbios_family_c66_tci66xx_CpIntc_numSysInts__C;

/* numStatusRegs */
typedef xdc_Int CT__ti_sysbios_family_c66_tci66xx_CpIntc_numStatusRegs;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_numStatusRegs ti_sysbios_family_c66_tci66xx_CpIntc_numStatusRegs__C;

/* sysIntToHostInt */
typedef xdc_UInt8 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt;
typedef xdc_UInt8 *__ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt;
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt __TA_ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt;
typedef __TA_ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt CT__ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt ti_sysbios_family_c66_tci66xx_CpIntc_sysIntToHostInt__C;

/* hostIntToEventId */
typedef xdc_UInt8 __T1_ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId;
typedef xdc_UInt8 *__ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId;
typedef __ARRAY1_ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId __TA_ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId;
typedef __TA_ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId CT__ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId;
extern far const CT__ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId ti_sysbios_family_c66_tci66xx_CpIntc_hostIntToEventId__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */

extern xdc_Int ti_sysbios_family_c66_tci66xx_CpIntc_Module_startup__E( xdc_Int state );

extern xdc_Int ti_sysbios_family_c66_tci66xx_CpIntc_Module_startup__F( xdc_Int state );

extern xdc_Int ti_sysbios_family_c66_tci66xx_CpIntc_Module_startup__R( xdc_Int state );

/* Module__startupDone__S */

extern xdc_Bool ti_sysbios_family_c66_tci66xx_CpIntc_Module__startupDone__S( void );

/* clearSysInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_clearSysInt__E( xdc_UInt id, xdc_UInt sysInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_clearSysInt__F( xdc_UInt id, xdc_UInt sysInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_clearSysInt__R( xdc_UInt id, xdc_UInt sysInt );

/* disableAllHostInts__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableAllHostInts__E( xdc_UInt id );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableAllHostInts__F( xdc_UInt id );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableAllHostInts__R( xdc_UInt id );

/* disableHostInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableHostInt__E( xdc_UInt id, xdc_UInt hostInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableHostInt__F( xdc_UInt id, xdc_UInt hostInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableHostInt__R( xdc_UInt id, xdc_UInt hostInt );

/* disableSysInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableSysInt__E( xdc_UInt id, xdc_UInt sysInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableSysInt__F( xdc_UInt id, xdc_UInt sysInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_disableSysInt__R( xdc_UInt id, xdc_UInt sysInt );

/* dispatch__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_dispatch__E( xdc_UInt hostInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_dispatch__F( xdc_UInt hostInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_dispatch__R( xdc_UInt hostInt );

/* dispatchPlug__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_dispatchPlug__E( xdc_UInt sysInt, ti_sysbios_family_c66_tci66xx_CpIntc_FuncPtr fxn, xdc_UArg arg, xdc_Bool unmask );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_dispatchPlug__F( xdc_UInt sysInt, ti_sysbios_family_c66_tci66xx_CpIntc_FuncPtr fxn, xdc_UArg arg, xdc_Bool unmask );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_dispatchPlug__R( xdc_UInt sysInt, ti_sysbios_family_c66_tci66xx_CpIntc_FuncPtr fxn, xdc_UArg arg, xdc_Bool unmask );

/* enableAllHostInts__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableAllHostInts__E( xdc_UInt id );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableAllHostInts__F( xdc_UInt id );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableAllHostInts__R( xdc_UInt id );

/* enableHostInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableHostInt__E( xdc_UInt id, xdc_UInt hostInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableHostInt__F( xdc_UInt id, xdc_UInt hostInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableHostInt__R( xdc_UInt id, xdc_UInt hostInt );

/* enableSysInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableSysInt__E( xdc_UInt id, xdc_UInt sysInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableSysInt__F( xdc_UInt id, xdc_UInt sysInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_enableSysInt__R( xdc_UInt id, xdc_UInt sysInt );

/* getEventId__E */

extern xdc_Int ti_sysbios_family_c66_tci66xx_CpIntc_getEventId__E( xdc_UInt hostInt );

extern xdc_Int ti_sysbios_family_c66_tci66xx_CpIntc_getEventId__F( xdc_UInt hostInt );
extern xdc_Int ti_sysbios_family_c66_tci66xx_CpIntc_getEventId__R( xdc_UInt hostInt );

/* mapSysIntToHostInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_mapSysIntToHostInt__E( xdc_UInt id, xdc_UInt sysInt, xdc_UInt hostInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_mapSysIntToHostInt__F( xdc_UInt id, xdc_UInt sysInt, xdc_UInt hostInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_mapSysIntToHostInt__R( xdc_UInt id, xdc_UInt sysInt, xdc_UInt hostInt );

/* postSysInt__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_postSysInt__E( xdc_UInt id, xdc_UInt sysInt );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_postSysInt__F( xdc_UInt id, xdc_UInt sysInt );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_postSysInt__R( xdc_UInt id, xdc_UInt sysInt );

/* unused__E */

extern void ti_sysbios_family_c66_tci66xx_CpIntc_unused__E( xdc_UArg arg );

extern void ti_sysbios_family_c66_tci66xx_CpIntc_unused__F( xdc_UArg arg );
extern void ti_sysbios_family_c66_tci66xx_CpIntc_unused__R( xdc_UArg arg );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */

/* Object_heap */

/* Module_heap */

/* Module_id */
static inline CT__ti_sysbios_family_c66_tci66xx_CpIntc_Module__id ti_sysbios_family_c66_tci66xx_CpIntc_Module_id( void ) 
{
    return ti_sysbios_family_c66_tci66xx_CpIntc_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_family_c66_tci66xx_CpIntc_Module_hasMask( void ) 
{
    return ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask__C != 0;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_family_c66_tci66xx_CpIntc_Module_getMask( void ) 
{
    return ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask__C != 0 ? *ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline void ti_sysbios_family_c66_tci66xx_CpIntc_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask__C != 0) *ti_sysbios_family_c66_tci66xx_CpIntc_Module__diagsMask__C = mask;
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
 *  @(#) ti.sysbios.family.c66.tci66xx; 2, 0, 0, 0,153; 3-20-2012 14:02:46; /db/vtree/library/trees/avala/avala-q31x/src/ xlibrary

 */

typedef void (*Intr_Handler)(void *);

typedef struct{
	IntrTable					oIntrTableParam;
	//CSL_CicObj 					CicObj;     changed for new chip
	//CSL_CicHandle 				CicHandle;  //changed for new chip
	CSL_CPINTC_Handle          CicHandle;  // we are using old name even thoug the type is different for easy migration
	CSL_CPINTCSystemInterrupt   SysInt;		    //newly added for TRS by nachi
	CSL_CPINTCHostInterrupt		HostInt;	//newly added for TRS by nachi
	CSL_CPINTCChannel			Channel;			//newly added for TRS by nachi
//	VOID						*pIntrHandlerArg;
	//HWI_Attrs					oHwi; //DSP BIOS parameter
	ti_sysbios_hal_Hwi_Params					oHwi; // SYS BIOS parameter
	ti_sysbios_hal_Hwi_Handle 					oHwiHandle ;// SYS BIOS parameter
	xdc_runtime_Error_Block 				eb;
} Intr;

extern BOOL Intr_Init(Intr *pThis, IntrItem eIntrItem, Intr_Handler pfnIntr_Handler, void *pIntrHandlerArg);
extern BOOL Intr_EnableEvent(Intr *pThis);
extern BOOL Intr_DisableEvent(Intr *pThis);


/*************************************EOF*************************************/
//#include <DataType.h>
typedef struct {
	Intr			oIntr;
	CSL_TmrHandle 	oHandle;
	CSL_TmrObj		oObj;
	CSL_TmrEnamode	eCountMode;
	UINT64			nTimeUs;
	BOOL			bIntrMode;
} Timer;

extern BOOL Timer_Init(Timer *pThis, UINT8 nTimerNo, UINT64 nTimeUs, CSL_TmrEnamode eCountMode,		  				void (*pIntrHandler)(void *), void *Arg, IntrItem eIntrItemName);
extern void Timer_GetTicksUsec(Timer *pThis, UINT64 *pTimeUsec);
extern void Timer_GetTicksMsec(Timer *pThis, UINT64 *pTimeMsec);
extern void Timer_GetTicksSec(Timer *pThis, UINT64 *pTimeSec);
extern BOOL Timer_Start(Timer *pThis);
extern BOOL Timer_Stop(Timer *pThis);
extern void Timer_Add(Timer *pThis);
extern void Timer_Delete(Timer *pThis);
extern void Timer_Print(Timer *pThis);
extern void Timer_Restart(Timer *pThis, UINT32 nNewUsecs);


/*************************************EOF*************************************/



typedef struct SysTime
{
	UINT32		nSec;
	UINT32		nUSec;

}SysTime;

extern void SysTime_Init(INT8 nTimerNo);

/* Set the value to DSP Time */
extern void SysTime_Now( SysTime *pThis );
/* Set the value to DSP time + offset */
void SysTime_Future( SysTime *pThis, UINT32 nOffsetMS);

/* Return difference from other (other-self) in ms*/
INT32 SysTime_Delta(SysTime *pThis, SysTime *pOther );

/*Elapsed time in ms */
INT32 SysTime_Elapsed( SysTime *pThis);

/*Remaining time in ms */
INT32 SysTime_Remaining( SysTime *pThis);

/*Elapsed time in ms */
BOOL SysTime_Passed( SysTime *pThis);

/* Time in ms */
UINT32 SysTime_Get( SysTime *pThis );

void SysTime_Print( SysTime *pThis );

extern INT8 SysTime_Cmp(SysTime *pFirst, SysTime *pSecond, UINT64 *pDiffUsecs);
extern INT64 SysTime_DeltaUs(SysTime *pThis, SysTime *pOther);
extern void SysTime_AddUsecs( SysTime *pThis, INT32 nUSecs);
extern INT64 SysTime_RemainingUs(SysTime *pThis);
extern BOOL SysTime_isTimeOver( SysTime *pThis);


static Timer oTimer;

//#pragma CODE_SECTION(SysTime_Init,".textDDR")

void SysTime_Init(INT8 nTimerNo)
{
// ##################################### what count have to pass for initialization ?????????????
	Timer_Init(&oTimer, nTimerNo, 0x189374BC6A7EF9D, CSL_TMR_ENAMODE_CONT, 
												0, 0, INTR_ITEM_TIMER_3);
	Timer_Start(&oTimer);

}

#pragma CODE_SECTION(SysTime_Now, ".text")
/* Set the value to DSP Time  */
void SysTime_Now( SysTime *pThis )
{
	UINT64 nUSec;
	Timer_GetTicksUsec(&oTimer, &nUSec);


	pThis->nUSec	= (UINT32)(nUSec % 1000000);
	pThis->nSec		= (UINT32)(nUSec / 1000000);			
}

#pragma CODE_SECTION(SysTime_Now, ".text")
/* Set the value to DSP time + offset */
void SysTime_Future( SysTime *pThis, UINT32 nOffsetMSec)
{
	UINT32	nSec = nOffsetMSec/1000;
	UINT32  nMSec = nOffsetMSec%1000;
	SysTime_Now(pThis);
	pThis->nSec += nSec;
	pThis->nUSec += nMSec*1000;
	if( pThis->nUSec > 1000000 )
	{
		pThis->nUSec -= 1000000;
		pThis->nSec  += 1;
	}
}

/* Add Microseconds to the existing time */
void SysTime_AddUsecs( SysTime *pThis, INT32 nUSecs)
{
	
	INT64 t1;

	t1 = ((pThis->nSec * 1000000) + pThis->nUSec);

	t1+= nUSecs;

	pThis->nSec = (UINT32)t1/1000000;
	pThis->nUSec = (UINT32)t1%1000000;
	
}

#pragma CODE_SECTION(SysTime_Delta, ".text")
/* Return difference from other (other-self) in MS*/
INT32 SysTime_Delta(SysTime *pThis, SysTime *pOther )
{
	INT32	nDeltaSec = pOther->nSec - pThis->nSec;
	INT32	nDeltaUSec = pOther->nUSec - pThis->nUSec;

	return 1000*nDeltaSec + nDeltaUSec/1000;
}

/* Return difference from other (other-self) in US*/
INT64 SysTime_DeltaUs(SysTime *pThis, SysTime *pOther )
{
	UINT64	nUsec1, nUsec2;
	
	nUsec1 = (pThis->nSec * 1000000) + pThis->nUSec;
	nUsec2 = (pOther->nSec * 1000000) + pOther->nUSec;
	
	return (INT64)(nUsec2 - nUsec1);
}

// Returns 1 if First is bigger.
// Returns -1 if Second is bigger.
// Returns 0 if both are same.

INT8 SysTime_Cmp(SysTime *pFirst, SysTime *pSecond,UINT64 *nDiffUsecs)
{

	UINT64 nFirstAbs;
	UINT64 nSecondAbs;

	nFirstAbs = (pFirst->nSec * 1000000UL) + pFirst->nUSec;
	nSecondAbs = (pSecond->nSec * 1000000UL) + pSecond->nUSec;

	*nDiffUsecs = abs(nFirstAbs - nSecondAbs); 
	
	if (nFirstAbs > nSecondAbs)
	{
		return 1;
	}
	else if (nFirstAbs < nSecondAbs)
	{
		return -1;
	}
	else
	{
		return 0;
	}


}

#pragma CODE_SECTION(SysTime_Elapsed, ".text")

/*Elapsed time in ms */
INT32 SysTime_Elapsed( SysTime *pThis)
{
	SysTime Other;
	SysTime_Future(&Other, 0);
	return SysTime_Delta(pThis, &Other);
}

// Returns the Timeis over or not through BOOL variable.
BOOL SysTime_isTimeOver( SysTime *pThis)
{
	SysTime oNow;
	UINT8 retval;
	UINT64 Dummy;

	SysTime_Now(&oNow);

    retval = SysTime_Cmp(&oNow, pThis, &Dummy);
	if (retval == 1 )
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

#pragma CODE_SECTION(SysTime_Remaining, ".text")
/*Remaining time in ms */
INT32 SysTime_Remaining( SysTime *pThis)
{
	return -SysTime_Elapsed(pThis);
}

#pragma CODE_SECTION(SysTime_RemainingUs, ".text")

INT64 SysTime_RemainingUs(SysTime *pThis)
{
	SysTime now;
		
	SysTime_Now(&now);
	return SysTime_DeltaUs(&now, pThis);
}
/*Elapsed time in ms */
BOOL SysTime_Passed( SysTime *pThis)
{
	SysTime NowTime;
	SysTime_Now(&NowTime);
	if(NowTime.nSec < pThis->nSec ) return 0;
	if(NowTime.nSec > pThis->nSec ) return 1;
	if(NowTime.nUSec > pThis->nUSec ) return 1;
	return 0;

}


UINT32 SysTime_Get( SysTime *pThis )
{
	return pThis->nSec*1000 + pThis->nUSec/1000;
}

void SysTime_Print( SysTime *pThis )
{
	printf("Current Time in MS: %d \n", pThis->nSec*1000 + pThis->nUSec/1000);
}




