/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Task.h> (Utilities.pjt)
//
//  Subsystem: 
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for creating 
//  tasks, Signals, Binary Sem Locks. This module shall be considered
//  as OS absraction.
//
//  Dependencies, Limitations, and Design Notes:
//  	
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/

#ifndef _TASK_H_INCLUDED_
#define _TASK_H_INCLUDED_

#include <DataType.h> // replace this path relative path
#include <ti\csl\tistdtypes.h>
// #include <xdc\std.h> // its included in DataType.h
//#include <tsk.h>

//D:\TInew\bios_6_33_04_39\packages\
#include <Task.h>
#include <string.h>
//#include <sys.h>
//#include<xdc\runtime\System.h>
//#include <sem.h>
#include<ti\sysbios\knl\Semaphore.h>
//D:\TInew\bios_6_33_04_39\packages
#include <ti/sysbios/BIOS.h>


#define STE_TASK_SUSPEND -1


#define TASK_NAME_SIZE 20
#define SEM_NAME_SIZE 20


typedef VOID (*pfnTask)(VOID *);

typedef enum TaskStack
{
	TSK_STACKSIZE_1024 = 1024,
	TSK_STACKSIZE_2048 = 2048,
	TSK_STACKSIZE_3072 = 3072,
	TSK_STACKSIZE_4096 = 4096,
	TSK_STACKSIZE_8192 = 8192
}TaskStack;

typedef enum TaskPri
{
	TSK_PRIORITY_0   = 0,
	TSK_PRIORITY_1,
	TSK_PRIORITY_2,
	TSK_PRIORITY_3,
	TSK_PRIORITY_4,
	TSK_PRIORITY_5,
	TSK_PRIORITY_6,
	TSK_PRIORITY_7,
	TSK_PRIORITY_8,
	TSK_PRIORITY_9,
	TSK_PRIORITY_10,
	TSK_PRIORITY_11,
	TSK_PRIORITY_12,
	TSK_PRIORITY_13,
	TSK_PRIORITY_14,
	TSK_PRIORITY_15
}TaskPri;

#define STE_TASK_SUSPEND     -1
#define STE_TASK_DEFAULT_PRI TSK_PRIORITY_2
#define STE_DEFAULT_STACK_SZ 12 
typedef struct stSteTask
{
	UINT8       Name[TASK_NAME_SIZE];
	TaskPri     hPriority;
	//TSK_Handle Handle;
	Task_Handle Handle;
	//TSK_Attrs  tskattrs;
	Task_Params tskattrs;
    VOID (*pfnTask)(VOID *);
}Task;

// Creates a task in a non-running state
extern BOOL Task_Init(Task *pThis, String sName,  pfnTask pfn , VOID *pArg);
// Creates a task in a non-running state - Different version has prio and stack size
extern BOOL Task_Init1(Task *pThis, String Name,  pfnTask pfn , VOID *pArg, TaskStack  eStacksize, TaskPri ePriority );

/* Start the Task */
VOID Task_Start(Task *pThis);

/* Stop the Task */
extern VOID Task_Stop(Task *pThis);

/*Given the task, Sets Task priority */
extern VOID Task_SetPri(Task *pThis, TaskPri ePriority);

/*Mutex and Sigal based on the Semaphore. */

typedef struct stMutex
{
	char Name[SEM_NAME_SIZE];
	//volatile SEM_Handle Handle;
	volatile Semaphore_Handle Handle;
}Mutex;


extern BOOL Mutex_Init( Mutex *pThis , char *name, UINT8 InitState);
extern VOID Mutex_Lock( Mutex *pThis );
extern VOID Mutex_Unlock( Mutex *pThis );
extern BOOL Mutex_Lock_Timeout( Mutex *pThis);


/* A wrapper intertask signal based on Semaphore variable */
typedef Mutex Signal;

extern BOOL Signal_Init( Signal *pThis, String name);
extern VOID Signal_Pend( Signal *pThis);
extern VOID Signal_Enable(Signal *pThis);
extern BOOL Signal_Poll( Signal *pThis, UINT16 nTimeout);
extern VOID Signal_Post( Signal *pThis );
extern BOOL CountingSem_Init(Signal *pThis, char *name, UINT32 count);

extern VOID Signal_Broadcast( Signal *pThis);

#endif //_TASK_H_INCLUDED_
