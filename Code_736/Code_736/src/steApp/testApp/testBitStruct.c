



#include <DataType.h>
#include <DataLoad.h>


typedef struct BitStruct
{

	unsigned  int nCmd0_2 : 3;
		unsigned  int nCmd0_3 : 5;
}BitStruct;

typedef struct BitStruct2
{

	unsigned  int nCmd0_2 : 3;
		unsigned  int nCmd0_3 : 13;
}BitStruct2;

typedef struct BitStruct4
{

	unsigned  int nCmd0_2 : 3;
		unsigned  int nCmd0_3 : 29;
}BitStruct4;

typedef struct BitStruct3
{

	unsigned  int nCmd0_2 : 3;
		unsigned  int nCmd0_3 : 21;
}BitStruct3;



typedef struct BitStruct18
{

	unsigned  int nCmd1 : 32;
	unsigned  int nCmd2 : 32;
		unsigned  int nCmd3 : 32;
			unsigned  int nCmd4 : 32;
				  short int nCmd5 : 16;


}BitStruct18;

typedef union pack123
{
	//BitStruct18 b;
	UINT8 B[18];
}pack123;

void test123( void )
{
	printf("%d %d %d %d %d %d \n",sizeof(BitStruct),sizeof(BitStruct2),sizeof(BitStruct3),sizeof(BitStruct4), sizeof(BitStruct18), sizeof(pack123));
}
