#ifndef _DATATYPE_H_INCLUDED_H_
#define _DATATYPE_H_INCLUDED_H_

//#include <xdc\std.h> // new standard defenitions, delcome algo may create problems :(

#include "stdio.h"
#include "dcs_types.h"  // commented by remesh, its conflicting with xdc/std.h
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

#define BOTH_COREFLAG 8  //############# previously it was 3#############



#define VOID	void
#define CONST	const
//#define	TRUE	(BOOL)1
//#define FALSE	(BOOL)0
#define STE_ASSERT(x) if(!(x)) { printf("STE_ASSERT_FAILED at Line %d in File %s Expr: %s\n", __LINE__, __FILE__, #x); }

#include "UsrConfig.h"		//Should be below user datatypes(typedefs) due to compilation issues 
#endif  /* _DATATYPE_H_INCLUDED_H_ */
