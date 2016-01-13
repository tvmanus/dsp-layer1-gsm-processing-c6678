#include "ste_msgQ.h"
#include "types.h"
#include"DDCRx.h"
#include "UsrConfig.h"

/*
  NoBuffers  :  (allocIdx == freeIdx)
  QueueFull  :  ((freeIdx+1)%JOBLIST_QUEUE_SIZE == writeIdx);
  Size       :   freeIdx-AllocIdx or  JOBLIST_QUEUE_SIZE-(AllocIdx-freeIdx) based on Queue Wrap;
*/

VOID DDCRx_QueueInit( DDCRX_JobQueue *queue)
{
    UINT16 idx;
    struct jobList *n;
    queue->allocIdx = 0;
    queue->freeIdx  = 0;    		
   // n = (struct jobList *)malloc(sizeof (struct jobList) *(JOBLIST_QUEUE_SIZE-1));  //To be replaced with System Specific Alloc. check for error

    for(idx = 0; idx <JOBLIST_QUEUE_SIZE-1; idx++)
    {
    	n = Alloc(MSGTYPE_TRFRJOBLIST);
        queue->List[idx] = n;
        //n++;
    }
    queue->freeIdx  = idx; //should point the last entry.
}


struct jobList *DDCRx_JobAlloc( DDCRX_JobQueue *queue )
{
    
    struct jobList *n;
    if ( queue->allocIdx != queue->freeIdx )  //ensuring the most likely cases executes first unlikely cases further down.
    {
        //queue not empty
        n =  queue->List[queue->allocIdx];
        if ( queue->allocIdx != ( JOBLIST_QUEUE_SIZE -1 ) )
        {
            queue->allocIdx++;
            return n;
        }
        else 
        {
            //queuewrap
            queue->allocIdx = 0;
            return n;
        }
    }
    else 
    {	
       printf("No Bufferss\n\r");
       return NULL;
    }
}

VOID	DDCRx_JobFree(DDCRX_JobQueue *queue, struct jobList *n)
{
    if ((( queue->freeIdx+1 ) % JOBLIST_QUEUE_SIZE )  ==  queue->allocIdx )
    {   
        printf("Queue full.. Should not occur\n\r");
        return;
    }
    queue->List[queue->freeIdx] =  n;	
    if ( queue->freeIdx != ( JOBLIST_QUEUE_SIZE -1 ) ) 
    {
        queue->freeIdx++;
    }
    else 
    {
        queue->freeIdx = 0;
    }
}


UINT16 DDCRx_QueueGetSize( DDCRX_JobQueue *queue )
{
    if ( queue->freeIdx >= queue->allocIdx )
        return ( queue->freeIdx - queue->allocIdx );
    else 
        return (JOBLIST_QUEUE_SIZE - (queue->allocIdx - queue->freeIdx) ); //Queue wrap
}

#if 0
#include <stdio.h>
#include <stdlib.h>
typedef void VOID;
typedef unsigned short UINT16; 
struct jobList  
{
    VOID *pData;
    struct jobList  *next;
    struct jobList  *prev;
};


int main()
{
  DDCRX_JobQueue f;
  struct jobList *p1, *p2, *p3, *p4;

  DDCRx_QueueInit(&f);

  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  DDCRx_JobFree(&f, p1);
  DDCRx_JobFree(&f, p2);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p1 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p1);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p2 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p2);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p3 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p3);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p4 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p4);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));


  DDCRx_JobFree(&f, p3);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));
  DDCRx_JobFree(&f, p2);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));
  DDCRx_JobFree(&f, p1);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));


  p1 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p1);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p2 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p2);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p3 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p3);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));

  p4 = DDCRx_JobAlloc(&f);
  printf("%d ",(int)p4);
  printf("available %d\n\r", DDCRx_QueueGetSize(&f));
  return 0;
}
#endif
