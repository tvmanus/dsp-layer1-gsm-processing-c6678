#include "GSMTime.h"
#include "TestFramework.h"


VOID Test_GSMTime( VOID )
{
	GSMTime	oTime;
	GSMTime	oOther;
	const UINT32 gHyperframe = 2048UL * 26UL * 51UL;

	INIT_TESTING(GSMTime);
	GSMTime_Init(&oTime, 12345, 5);
	TEST_IS_EQ(oTime.nFN, 12345);	
	TEST_IS_EQ(oTime.nTN, 5);

	GSMTime_Init(&oOther, 67890, 3);
	GSMTime_Copy(&oTime, &oOther);
	TEST_IS_EQ(oTime.nFN, 67890);
	TEST_IS_EQ(oTime.nTN, 3);

	GSMTime_SetFN(&oTime, 112233);
	GSMTime_SetTN(&oTime, 1);
	TEST_IS_EQ(GSMTime_FN(&oTime), 112233);
	TEST_IS_EQ(GSMTime_TN(&oTime), 1);

	GSMTime_SetFN(&oTime, 112233);
	GSMTime_SetTN(&oTime, 1);
	TEST_IS_EQ(GSMTime_FN(&oTime), 112233);
	TEST_IS_EQ(GSMTime_TN(&oTime), 1);

	GSMTime_SetFN(&oTime, 51);
	GSMTime_RollForward(&oTime, 10 , 51);
	TEST_IS_EQ(oTime.nFN, 51+10-(51%51));

	GSMTime_SetFN(&oTime, 53);
	GSMTime_RollForward(&oTime, 5 , 51);
	TEST_IS_EQ(oTime.nFN, 53+5-(53%51));

	GSMTime_SetFN(&oTime, 123456);
	GSMTime_RollForward(&oTime, 43 , 51);
	TEST_IS_EQ(oTime.nFN, 123456+43-(123456%51));

	GSMTime_SetFN(&oTime, 123456);
	GSMTime_Inc(&oTime, 10);
	TEST_IS_EQ(oTime.nFN, 123466);

	GSMTime_SetFN(&oTime, gHyperframe-1);
	GSMTime_Inc(&oTime, 10);
	TEST_IS_EQ(oTime.nFN, 9);

}






















#if 0
typedef struct Base2
{
	int b1;
	int b2;
}Base;

typedef struct Child
{
struct 
{
	int b1;
	int b2;
}_;
	int c1;
	int c2;
}Child;

void Base_Init(Base *pThis )
{
	pThis->b1 = 1;
	pThis->b2=2;
}
int Base_GetB1(Base *pThis)
{
	return pThis->b1;
}

void Child_Init(Child *pThis )
{
	Base_Init((Base*)pThis);
	pThis->c1 =3;
	pThis->c2 = 4;
}


VOID main( VOID )
{

	GSMTime Time1;
	GSMTime Time2;
	GSMTime Time3;
	GSMTime Time4;
	INT32	Diff;
	Child c;

	Child_Init(&c);

	Base_GetB1((Base*)&c);


	GSMTime_Init(&Time1, 10000, 5 );

	GSMTime_Print(&Time1);

	GSMTime_Init(&Time2, 20000, 6 );

	GSMTime_Print(&Time2);

	GSMTime_IncTN(&Time1, 2);
	GSMTime_Print(&Time1);

	GSMTime_DecTN(&Time1, 8);
	GSMTime_Print(&Time1);

	GSMTime_IncTN(&Time1, 2);
	GSMTime_Print(&Time1);

	GSMTime_Inc(&Time1, 1);
	GSMTime_Print(&Time1);

	Time3 = GSMTime_Add(&Time1, 1);
	GSMTime_Print(&Time1);
	GSMTime_Print(&Time3);

	GSMTime_IncTN(&Time1, 2);
	Diff = GSMTime_SubTime(&Time1, &Time3);
	GSMTime_Print(&Time1);
	GSMTime_Print(&Time3);
	printf("Diff %d\n",Diff);

	Time3 = GSMTime_Sub(&Time1, 1);
	GSMTime_Print(&Time1);
	GSMTime_Print(&Time3);

	Time4 = GSMTime_AddTime(&Time1, &Time3);
	GSMTime_Print(&Time1);
	GSMTime_Print(&Time3);
	GSMTime_Print(&Time4);

	printf("%d\n", GSMTime_IsLessThanTime(&Time1, &Time3));


	GSMTime_SetFN(&Time1, 81);
	GSMTime_SetTN(&Time1, 0);
	GSMTime_Print(&Time1);

	GSMTime_RollForward(&Time1, 40, 51 );
	GSMTime_Print(&Time1);

	GSMTime_RollForward(&Time1, 0, 51 );
	GSMTime_Print(&Time1);


}
#endif
