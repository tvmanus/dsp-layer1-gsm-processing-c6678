/************************************************************************
 * File:
 *      $RCSfile: bits_pack_unpack.c,v $
 *      $Revision: 1.1.1.1 $
 *      $Date: 2007/04/15 03:00:30 $
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
 *      OR ANY PART THEREOF BE DEVELOPED WITHOUT WRITTEN AGREEMENT BY DelCom
 *      Systems, INC. 
 *
 * Purpose:
 *      This file contains the source code  for L2/RLC-MAC API's
 *
 * Operation:
 *      
 * Notes/Issues:
 *
 ************************************************************************/

  
#include "dcs_types.h"


void GSM_DCS_pack_bits(BIT_TYPE *in, OCTET *out, int N)
{

	int byte,bit;
	int i;
	
	for(i=0;i<N;i++){
		byte=i >> 3;
		bit=i & 7;
		if(bit ==0) out[byte] = in[i] & 1;
		else out[byte] |= in[i]<<bit;
	}		
	
}

void GSM_DCS_unpack_bits(OCTET *in, BIT_TYPE *out,  int N)
{

	int byte,bitpos;
	int i;
	int n=0;
	
	for(i=0;i<N;i++){
		byte=i >> 3;
		bitpos=i & 7;
		out[n++] = (in[byte] >> bitpos ) & 1;
		
	}		
	
}
