#include "RFVector.h"


VOID Print_Complex( VOID *pVal )
{
   COMPLEX16   Complex2 = *(COMPLEX16*)(pVal);

   printf("%di+%dj ",Complex2.nReal, Complex2.nImage);
   
}



void main( void )
{

   RFVector RF1,RF2, RF3;
   SigVect  wSig1;
   GSMTime  wTime;
   COMPLEX16 Burst = { 1, 2};

   SigVect_Init_Empty(&wSig1, 4, NONE);

   Vector_Fill((Vector*)&wSig1, &Burst);

   GSMTime_Init(&wTime, 0,0);

   RFVector_Init(&RF1, wSig1, wTime);

   Vector_Print((Vector*)&RF1, Print_Complex);


}