#include "SigVect.h"

VOID Print_Complex( VOID *pVal )
{
   COMPLEX16   Complex2 = *(COMPLEX16*)(pVal);

   printf("%di+%dj ",Complex2.nReal, Complex2.nImage);
   
}
void main( void )
{

   SigVect Sig1;
   SigVect Sig2;
   SigVect Sig3;
   SigVect Sig4;
   SigVect Sig5;

   COMPLEX16 Burst1 ={ 128, 256 };

   SigVect_Init_Empty(&Sig1, 4, NONE);

   Vector_SetAt(&Sig1, 0, &Burst1);

   Vector_Print(&Sig1,Print_Complex);

   SigVect_Init_Empty(&Sig2, 4, NONE);

   Vector_Fill(&Sig2, &Burst1);

   Vector_Print(&Sig2,Print_Complex);

   SigVect_Init_Concat(&Sig3, &Sig1, &Sig2);

   Vector_Print(&Sig3,Print_Complex);

   SigVect_Init_CopyFrom(&Sig4,&Sig3);

   Vector_Print(&Sig4,Print_Complex);
   
   Vector_Segment(&Sig4, &Sig5, 1, 3);

   Vector_Print(&Sig5,Print_Complex);
}