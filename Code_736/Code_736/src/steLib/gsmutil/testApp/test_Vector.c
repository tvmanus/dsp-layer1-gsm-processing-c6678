#include "Vector.h"

VOID print( VOID *pVal )
{
   float nVal = *((float*)(pVal));
   printf("%1.2f ", nVal);
}

VOID Test( VOID *pThis )
{
	Vector *pVector = pThis;
	Vector_Print(pVector, print);
}

void main ( void )
{

   Vector test1;
   Vector test2;
   Vector testC;
   Vector testCHead;
   Vector testCTail;
   Vector testCSegment;
   Vector testD;
   UINT16 nIndex;
   INT8 nVal;
   float fVal;

   Vector_Init_Empty(&test1, 5, sizeof(float) );
   Vector_Init_Empty(&test2, 5, sizeof(float) );
   
   for(nIndex = 0; nIndex<5; nIndex+=1)
   {
      fVal = nIndex;
      Vector_SetAt(&test1, nIndex, &(fVal));
   }
   
   for(nIndex = 0,nVal=nIndex+10; nIndex<5; nIndex++,nVal++ )
      Vector_SetAt(&test2, nIndex, &nVal);
   
   Test(&test1);
   Vector_Print(&test1, print);
   Vector_Print(&test2, print);

   Vector_PrintBytes(&test1 );
   Vector_PrintBytes(&test2 );

   Vector_Init_Concat(&testC, &test1, &test2);
   Vector_PrintBytes(&testC);

   Vector_Head(&testC, &testCHead, 3);
   Vector_PrintBytes(&testCHead);
   Vector_Tail(&testC, &testCTail, 3);
   Vector_PrintBytes(&testCTail);

   nVal = 8;
   Vector_Fill(&testC, &nVal);

   Vector_CopyToSegment(&test1, &testC, 3,Vector_GetSize(&test1));
   Vector_PrintBytes(&testC);
   Vector_Segment(&testC, &testCSegment, 4, 3 );
   Vector_Init_Shift(&testD, &testCSegment);
   Vector_PrintBytes(&testD);
   nVal = 9;
   Vector_Fill(&testD, &nVal);
   Vector_PrintBytes(&testC);
   Vector_PrintBytes(&testD);

#if 0
   
	
		testC.fill(8);
		cout << testC << endl;
		test1.copyToSegment(testC,3);
		cout << testC << endl;

		TestVector testD(testC.segment(4,3));
		cout << testD << endl;
		testD.fill(9);
		cout << testC << endl;
		cout << testD << endl;
	}

#endif
}
