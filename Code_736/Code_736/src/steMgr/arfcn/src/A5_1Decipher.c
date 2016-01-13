#include<ti\sysbios\knl\Task.h>
#include"L1Receiver.h"
#include"A5_1Decipher.h"

/* Calculate the parity of a 32-bit UINT32, i.e. the sum of its bits modulo 2 */
/*This is even parity, function returns 1 if no. 1's in the word is odd*/
UINT32 parity(UINT32 x) {
	x ^= x>>16;
	x ^= x>>8;
	x ^= x>>4;
	x ^= x>>2;
	x ^= x>>1;
	return x&1;                                                                                                                                                                                                                                                                                                                                                          
}

/* Clock one shift register */
UINT32 clockone(UINT32 reg, UINT32 mask, UINT32 taps) {
	UINT32 t = reg & taps;
	reg = (reg << 1) & mask;//To Make shifted out bit to zero, mask is applied
	reg |= parity(t);
	return reg;
}

/* The three shift registers.  They're in global variables to make the code
 * easier to understand.
 * A better implementation would not use global variables. */


/* Look at the middle bits of R1,R2,R3, take a vote, and
 * return the majority value of those 3 bits. */
UINT32 majority(LFSR_REGS *lfsr_r) {
	int sum;
	sum = parity(lfsr_r->R1&R1MID) + parity(lfsr_r->R2&R2MID) + parity(lfsr_r->R3&R3MID);
	if (sum >= 2)
		return 1;
	else
		return 0;
}

/* Clock two or three of R1,R2,R3, with clock control
 * according to their middle bits.
 * Specifically, we clock Ri whenever Ri's middle bit
 * agrees with the majority value of the three middle bits.*/
void clock(LFSR_REGS *lfsr_r) {
	UINT32 maj = majority(lfsr_r);//Either 1 or 0
	if (((lfsr_r->R1&R1MID)!=0) == maj){
		lfsr_r->R1 = clockone(lfsr_r->R1, R1MASK, R1TAPS);
	}
	if (((lfsr_r->R2&R2MID)!=0) == maj) {
		lfsr_r->R2 = clockone(lfsr_r->R2, R2MASK, R2TAPS);
	}
	if (((lfsr_r->R3&R3MID)!=0) == maj) {
		lfsr_r->R3 = clockone(lfsr_r->R3, R3MASK, R3TAPS);
	}
}

/* Clock all three of R1,R2,R3, ignoring their middle bits.
 * This is only used for key setup. */
void clockallthree(LFSR_REGS *lfsr_r) {
	lfsr_r->R1 = clockone(lfsr_r->R1, R1MASK, R1TAPS);
	lfsr_r->R2 = clockone(lfsr_r->R2, R2MASK, R2TAPS);
	lfsr_r->R3 = clockone(lfsr_r->R3, R3MASK, R3TAPS);
}

/* Generate an output bit from the current state.
 * You grab a bit from each register via the output generation taps;
 * then you XOR the resulting three bits. */
UINT32 getbit(LFSR_REGS *lfsr_r) {
	return parity(lfsr_r->R1&R1OUT)^parity(lfsr_r->R2&R2OUT)^parity(lfsr_r->R3&R3OUT); //Take the MSB of 3 LFSR's & XOR
}

#pragma CODE_SECTION(A5_1DecipherAlgo, ".text")
void A5_1DecipherAlgo(UINT8 *key, UINT32 frame1_no, LFSR_REGS *lfsr_r, UINT8 *cipher_in, UINT8 *decipher_out, DIRECTION eDir,CHANNEL_COMB eChannelComb)
{
 	int i;
	UINT32 keybit, framebit;
	UINT8 array114[114];
	UINT32 t1,t2,t3;
	UINT32 frame_no = 0x00000000;

   	/* Zero out the shift registers. */
	lfsr_r->R1 = 0;
	lfsr_r->R2 = 0;
	lfsr_r->R3 = 0;

	//Modified Frame numbers as per A5/1 requirement
	t1 = frame1_no/1326;
    t2 = frame1_no % 26;
    t3 = frame1_no % 51;
    frame_no = (t1<<11)|(t3<<5)|t2;

	/* Load the key into the shift registers,
	 * LSB of first UINT8 of key array first,
	 * clocking each register once for every
	 * key bit loaded.  (The usual clock
	 * control rule is temporarily disabled.) */
	for (i=0; i<64; i++) 
	{
		clockallthree(lfsr_r); /* always clock */
		keybit = (key[i/8] >> (i&7)) & 1; /* The i-th bit of the key */
		lfsr_r->R1 ^= keybit; 
		lfsr_r->R2 ^= keybit; 
		lfsr_r->R3 ^= keybit;
	}

	/* Load the frame number into the shift
	 * registers, LSB first,
	 * clocking each register once for every
	 * key bit loaded.  (The usual clock
	 * control rule is still disabled.) */
	for (i=0; i<22; i++) {
		clockallthree(lfsr_r); /* always clock */
		framebit = (frame_no >> i) & 1; /* The i-th bit of the frame # */
		lfsr_r->R1 ^= framebit; 
		lfsr_r->R2 ^= framebit; 
		lfsr_r->R3 ^= framebit;
	}

	/* Run the shift registers for 100 clocks
	 * to mix the keying material and frame number
	 * together with output generation disabled,
	 * so that there is sufficient avalanche.
	 * We re-enable the majority-based clock control
	 * rule from now on. */
	for (i=0; i<100; i++) {
		clock(lfsr_r);
	}
	
	/* Generate 114 bits of keystream for the
	 * A->B direction.  Store it, MSB first. */
	for (i=0; i<114; i++)
	{
		clock(lfsr_r);
		array114[i] = getbit(lfsr_r);		
	}

	if(eDir == DL)
	{
		if((eChannelComb == VII) || (eChannelComb == V))
		{
			for (i=0; i<114; i++)	
			{
				decipher_out[i] = cipher_in[i]^array114[i];
			}
		}
		else
		{
			for (i=0; i<114; i++)	
			{
				decipher_out[i] = array114[i];
			}
		}
		return;	    
	}
	// De-ciphering of UL
	if(eDir == UL)
	{	
		/* Generate 114 bits of keystream for the
		 * B->A direction.  Store it, MSB first. */
		if((eChannelComb == VII) || (eChannelComb == V))
		{
	    	for (i=0; i<114; i++)
	    	{
				clock(lfsr_r);
				array114[i] = getbit(lfsr_r);
				decipher_out[i] = cipher_in[i]^array114[i];		
			}
		}
		else
		{
			for (i=0; i<114; i++)
	    	{
				clock(lfsr_r);
				array114[i] = getbit(lfsr_r);
				decipher_out[i] = array114[i];		
			}
		}
		return;
	}
}



