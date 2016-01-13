/************************************************************************
 * File:
 *      $RCSfile: generic_pulse_shaper.c,v $
 *      $Revision: 1.2 $
 *      $Date: 2008/02/17 22:12:04 $
 *
 *      (c) 2007 DelCom Systems, Inc.
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
 **************************************************************************/

/*======== Include Files =========*/
#include "dcs_types.h"

#include "gsm_toolbox.h"
//#include "dsp_toolbox.h"

/*======== Global Variables =========*/
#define EDGE_SIM_NPTS_LAURENT_FILT 241
#define N_TAPS_IN_SYMBOLS 5
#define FILT_SAMPLE_RATE	48

extern const INT16 GSM_DCS_laurent_fir_filt[241];

INT16 interp_filt_cint16_int16(COMPLEX16 *data, INT16 npts_data, 
			       INT16 *filt, INT16 npts_filt,
			       INT16 num_phases, 
			       INT16 interp_rate, 
			       COMPLEX16 *data_filt) ;


INT16 generic_pulse_shaper( COMPLEX16 *in_syms, 
				COMPLEX16 *out_syms, 
			      INT16 npts_in, 	/*156 or 157 */
			      INT16 samps_per_symb)
{
  INT16 i;
  COMPLEX16 interp_in[2*(N_TAPS_IN_SYMBOLS-1)+157];


  /* Append (N_TAPS_IN_SYMBOLS-1) '0's at the begining and 
   * at the end to filter the edges of the burst. This also 
   * simplifies the implementation of the interpolation filter. 
   */
  for ( i=0; i<N_TAPS_IN_SYMBOLS-1; i++ ) {
    interp_in[i].r = 0;
    interp_in[i].i = 0;
  }
  for ( i=0; i<npts_in; i++ ) {
    interp_in[N_TAPS_IN_SYMBOLS-1+i] = in_syms[i];
  }

  for ( i=0; i<N_TAPS_IN_SYMBOLS-1; i++ ) {
    interp_in[N_TAPS_IN_SYMBOLS-1+npts_in+i].r = 0;
    interp_in[N_TAPS_IN_SYMBOLS-1+npts_in+i].i = 0;
  }

  /* filter the data with EDGE linear pulse shaping filter, i.e., the main component 
   * in a Laurent decomposition of the GMSK modulation, generating the baseband 
   * signal. (truncating the tail of the convolution) 
   */
  interp_filt_cint16_int16(&interp_in[N_TAPS_IN_SYMBOLS], npts_in, 
			   (INT16 *)&GSM_DCS_laurent_fir_filt[0], EDGE_SIM_NPTS_LAURENT_FILT, 
			   N_TAPS_IN_SYMBOLS, samps_per_symb, 
			   &out_syms[0]); 

  return (0);
}


/****************************************************************************************
 * FUNCTION: int interp_filt_cint16_int16(COMPLEX16 *data, int npts_data, 
 *                                        INT16 *filt, int npts_filt, 
 *                                        INT16 num_phases, INT16 interp_rate, 
 *                                        COMPLEX16 *data_filt)
 *           
 * INPUTS:
 *   data - complex INT16 data to be filtered
 *   npts_data - length of data
 *   filt - INT16 filter  
 *   npts_filt - length of 'filt'
 *   num_phases - Number of filter phases
 *   interp_rate - interpolation rate relative to filter
 *
 * OUTPUT:
 *   data_filt - filtered data 
 *
 * ABSTRACT: Interpolation filter using poly-phase filtering. This routine assumes that 
 *           the input is not upsamled, and (num_phases - 1) zeros are added at the
 *           begining and at the end of the input data to assure that the output 
 *           will be smooth (edges of the filter).
 ***********************************************************************************/
INT16 interp_filt_cint16_int16(COMPLEX16 *data, INT16 npts_data, 
			       INT16 *filt, INT16 npts_filt,
			       INT16 num_phases, 
			       INT16 interp_rate, 
			       COMPLEX16 *data_filt) 
{
  int i, j, k, out_cnt;
  long accum1, accum2;
  int step;

  step = FILT_SAMPLE_RATE / interp_rate;
  out_cnt = 0;

  for (i=0; i<npts_data; i++) {
    for (j=0; j<interp_rate; j++ ) {
      accum1 = 0; accum2 = 0;
      for (k=0; k<num_phases; k++) {
		/* real part ss0.30 */
		//printf(" %d  %d  %d\n",filt[(k*step*interp_rate)+j*step] , data[i-k].r,data[i-k].i);
		accum1 += filt[(k*step*interp_rate)+j*step] * data[i-k].r;
		/* imag part ss0.30 */
		accum2 += filt[(k*step*interp_rate)+j*step] * data[i-k].i;
      }
      /* rounding and shifting */       
      accum1 = (accum1 + 0x00004000) >> 15; 
      data_filt[out_cnt].r = accum1;

      accum2 = (accum2 + 0x00004000) >> 15; 
      data_filt[out_cnt++].i = accum2;
    }
	
  }

  return (0);
}


