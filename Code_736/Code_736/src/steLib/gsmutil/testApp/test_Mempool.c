#include "Mempool.h"


//BOOL Mempool_Alloc( VOID *pBuffer, UINT16 nSize );

//BOOL Mempool_Dealloc( VOID *pBuffer, UINT16 nSize );
void main( void )
{
   VOID *pBuffer1;
   VOID *pBuffer2;
   VOID *pBuffer3;
   VOID *pBuffer4;
   VOID *pBuffer5;
   VOID *pBuffer6;

   Mempool_Alloc(&pBuffer1, 257);
   printf("Allocating pBuffer1 2 blocks 0x%x\n", pBuffer1);
   Mempool_Alloc(&pBuffer2, 513);
   printf("Allocating pBuffer2 3 blocks 0x%x\n", pBuffer2);
   Mempool_Alloc(&pBuffer3, 256);
   printf("Allocating pBuffer3 1 blocks 0x%x\n", pBuffer3);
   Mempool_Dealloc(&pBuffer2, 513);
   printf("Deallocating pBuffer2 3 blocks 0x%x\n", pBuffer2);
   Mempool_Alloc(&pBuffer4, 1024);
   printf("Allocating pBuffer4 4 blocks 0x%x\n", pBuffer4);
   Mempool_Alloc(&pBuffer5, 256);
   printf("Allocating pBuffer5 1 blocks 0x%x\n", pBuffer5);
   Mempool_Alloc(&pBuffer6, 256);
   printf("Allocating pBuffer6 2 blocks 0x%x\n", pBuffer6);
   
}
