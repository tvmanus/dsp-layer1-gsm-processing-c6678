DDCRX_STRUCT_SIZE		.SET		512
DDCRX_SIZE_ASM			.SET		1024


	.cdecls C;,NOLIST
%{
		#include"UsrConfig.h"
		//#include"maincfg.h62"
		//#include"../../../steapp/src/maincfg.h62"
%}
		.sect  .dataL2
		.if USE_ASSEMBLY_DDC_COPYSAMPLES;ASM_DDCRx_COPY
		.global	DDCRx_CopySamples
		
DDCRx_CopySamples:
		;a4-->pTgtPtr
		;b4-->pSrcPtr
		;a6-->nSymbols

	;	STDW	.D2T1	A11:A10,*--B15
	;	STDW	.D2T1	A13:A12,*--B15
	;	STDW	.D2T1	A15:A14,*--B15		
	;	STDW	.D2		B11:B10,*--B15
	;	STDW	.D2		B13:B12,*--B15
	;	STW		.D2		B14,*--B15
	;	STW		.D2		B3,*--B15	
	;	MVC		.S2		CSR,B8
	;	STW		.D2		B8,*--B15
	;	MVC		.S2		ILC,B9
	;	STW		.D2		B9,*--B15
	;	MVC		.S2		IRP,B16
	;	STW		.D2		B16,*--B15
	;	MVC		.S2		NRP,B17
	;	STW		.D2		B17,*--B15
	;	MVC		.S2		RILC,B18
	;	STW		.D2		B18,*--B15
	;	MVC		.S2		TSR,B19
	;	STW		.D2		B19,*--B15

	;	DINT
		
		CMPLT	.L1		A6,4,A0
	[A0]B				COPYSAMPLE_AFTERLOOP
	
	[A0]MV				B4,A5
	[A0]MV				A6,B0
	[A0]MV				A4,B9
	
		NOP				2

		MV		.D1X	B4,A5
||		MVKL	.S2		DDCRX_SIZE_ASM,B7
||		MVKL	.S1		DDCRX_SIZE_ASM,A7
||		MV		.D2X	A4,B9
		
		AND		.L2X	A6,0x3,B0		;ncount/4	reminder for loop unrolling	
||		MVKH	.S2		DDCRX_SIZE_ASM,B7
||		MVKH	.S1		DDCRX_SIZE_ASM,A7
||		ADD		.L1		A4,8,A9

		MVK		.L2		0,B2
||		ADDK	.S1		DDCRX_STRUCT_SIZE,A5

		SHR		.S1		A6,2,A0			;ncount/4
	;	SUB				A0,1,A0 

COPYSAMPLE_LOOP:

		LDNDW	.D2		*B4,B21:B20
||		ADD		.L2		B4,B7,B4		
;||[!B2]	SHR		.S1		A6,2,A0			;ncount/4  Quotient	for loop unrolling

		LDNDW	.D1		*A5,A21:A20
||  	ADD		.L1		A5,A7,A5
||[!B2]	ADD		.S2		B2,1,B2

		LDNDW	.D2		*B4,B23:B22
||		ADD		.L2		B4,B7,B4
||		SUB		.D1		A0,1,A0

		LDNDW	.D1		*A5,A23:A22
||		ADD		.L1		A5,A7,A5
||[A0]	B		.S1		COPYSAMPLE_LOOP

		NOP				1
		
		STNDW	.D2		B21:B20,*B9
||		ADDK	.S2		16,B9

		STNDW	.D1		A21:A20,*A9
||		ADDK	.S1		16,A9
||[!A0] MV      .L1X	B4,A5

		STNDW	.D2		B23:B22,*B9
||		ADDK	.S2		16,B9

		STNDW	.D1		A23:A22,*A9
||		ADDK	.S1		16,A9

COPYSAMPLE_AFTERLOOP:
  [B0]	LDNDW	.D1		*A5,A21:A20	
||[B0]	SUB		.L2		B0,1,B0
||		MV		.S2		B0,B2
||[B0]	ADDK	.S1		DDCRX_STRUCT_SIZE,A5

  [B0]	LDNDW	.D1		*A5,A23:A22	
||[B0]	SUB		.L2		B0,1,B0
||[B0]	ADDK	.S1		DDCRX_STRUCT_SIZE,A5

  [B0]	LDNDW	.D1		*A5,A25:A24	
||[B0]	SUB		.L2		B0,1,B0
;||		RET		.S2		B3

		MV		.L1X	B9,A9
		NOP		1

  [B2]	STNDW	.D1		A21:A20,*A9++
||[B2]	SUB		.L2		B2,1,B2
		
  [B2]	STNDW	.D1		A23:A22,*A9++
||[B2]	SUB		.L2		B2,1,B2
		
  [B2]	STNDW	.D1		A25:A24,*A9	
||[B2]	SUB		.L2		B2,1,B2	

;		LDW		.D2		*B15++,B8
;		LDW		.D2		*B15++,B9
;		LDW		.D2		*B15++,B16
;		LDW		.D2		*B15++,B17
;		LDW		.D2		*B15++,B18

;		MVC		.S2		B8,TSR
;||		LDW		.D2		*B15++,B19

;		LDW		.D2		*B15++,B3
;		MVC		.S2		B9,RILC		
;		MVC		.S2		B16,NRP		
;		MVC		.S2		B17,IRP		
;		MVC		.S2		B18,ILC
;		MVC		.S2		B19,CSR

;		LDW		.D2		*B15++,B14
	;	LDDW	.D2		*B15++,B13:B12
	;	LDDW	.D2		*B15++,B11:B10
	;	LDDW	.D2T1	*B15++,A15:A14
	;	LDDW	.D2T1	*B15++,A13:A12
	;	LDDW	.D2T1	*B15++,A11:A10

	;	NOP		4

		RET		B3

		NOP		5

	
	.endif
