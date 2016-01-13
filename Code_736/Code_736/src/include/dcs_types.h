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
#ifndef DCS_TYPES_H
#define DCS_TYPES_H

#if defined(__TMS320C55X__) | defined (_TMS320C5XX)

typedef short INT_NATIVE;
typedef unsigned short UINT_NATIVE;
typedef short INT16;
typedef unsigned short UINT16;
typedef long INT32;
typedef unsigned long  UINT32;
typedef          char  INT8;    /* 8 bit wide signed quantities */ 
typedef unsigned char  UINT8;   /* 8 bit wide unsigned quantities */
typedef int Flag;
typedef unsigned char  BIT_TYPE;/* 1 bit per element 0 or 1 only */
typedef unsigned char  OCTET;   /* 8 bits per element */
typedef unsigned char  SCRATCH; /* Scratch buffer pointer type */
typedef long long INT64;		  /*  WARNING: this is really 40 bits not correct */
typedef unsigned long long UINT64; /* WARNING: this is really 40 bits */
typedef  long long INT40;		  		  /*correct */
typedef  unsigned long long UINT40;		  /*correct */
/****** For C6000 *******/
#elif defined(_TMS320C6200) || defined(_TMS320C6400)
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


#else
typedef 	long long INT64;
typedef		unsigned long long UINT64;
typedef		long long INT40;
typedef	unsigned long long UINT40;
typedef int INT_NATIVE;
typedef unsigned int UINT_NATIVE;
typedef          short INT16;   /* 16 bit wide signed quantities */
typedef unsigned short UINT16;  /* 16 bit wide unsigned quantities */
typedef          long  INT32;   /* 32 bit wide signed quantities */
typedef unsigned long  UINT32;  /* 32 bit wide unsigned quantities */
typedef          char  INT8;    /* 8 bit wide signed quantities */ 
typedef unsigned char  UINT8;   /* 8 bit wide unsigned quantities */
typedef unsigned char  BIT_TYPE;/* 1 bit per element 0 or 1 only */
typedef unsigned char  OCTET;   /* 8 bits per element */
typedef unsigned char  SCRATCH; /* Scratch buffer pointer type */
typedef short Flag;
#endif




typedef struct complex16 {      /* 16 bit precision complex quantities */
  INT16 r; 
  INT16 i;
} COMPLEX16;


#if defined(_TMS320C6400) || defined(_TMS320C6200) 
#pragma STRUCT_ALIGN (complex16, 4);
#endif

typedef struct complex32 {      /* 32 bit precision complex quantities */
  INT32 r;
  INT32 i;
} COMPLEX32;
#if defined(_TMS320C6400)
#pragma STRUCT_ALIGN (complex32, 8);
#endif

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



#define ALIGN_TO(type, ptr) \
  ((type *)(((int)(ptr) + sizeof(type) - 1) & ~(sizeof(type) - 1)))
#define ALIGNMENT_ROUNDING(type) \
  ((sizeof(type) - 1))


#endif /* TYPES_H */



