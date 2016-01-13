
/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Task.c> (Utilities.pjt)
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

/*
===============================================================================
**                             Include files                                 **
===============================================================================
*/
#include <DataType.h>
#include <string.h>
//#include <std.h>
//#include <xdc/std.h>
//#include <tsk.h>
#include<ti\sysbios\knl\Task.h>
#include <ti\csl\tistdtypes.h>


#include <Task.h>
#include <xdc/runtime/Error.h>
#include<ti\csl\csl_chipAux.h>


/*****************************************************************************
** Function name:  Task_Init1     
**
** Descriptions: 
**     			   Create a task in a non-running state    
** parameters:     Task *pThis, Task name, Task function, Task Fn Arg, Stack Size, 
				 Task Priority.
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		Task is just created, and it will not run until Task_Start
**                
******************************************************************************/
BOOL Task_Init1(Task *pThis, String sName, pfnTask pfn, VOID *pArg, TaskStack eStacksize, TaskPri ePriority  )
{
	Error_Block eb;

	//pThis->tskattrs = TSK_ATTRS;
	 Task_Params_init(&(pThis->tskattrs));
	 Error_init(&eb);

	//pThis->tskattrs.stacksize = eStacksize;

	pThis->tskattrs.stackSize= eStacksize;
	//Setting of Task name
	if (sName != NULL)
	{
		memcpy(pThis->Name, sName, TASK_NAME_SIZE);
		//pThis->tskattrs.name = (String )&pThis->Name[0];
		pThis->tskattrs.instance->name = (String )&pThis->Name[0];
	}
	else
	{
		//pThis->tskattrs.name = "DUMMY";
		pThis->tskattrs.instance->name ="DUMMY";
	}

	//Setting of Task priority
	pThis->tskattrs.priority = STE_TASK_SUSPEND; // Suspend the priority.
	pThis->hPriority = ePriority;
	//Setting argument
	//pThis->tskattrs.arg0 =*(xdc_UArg*)pArg;
	pThis->tskattrs.arg0 =(xdc_UArg)pArg;
	
	//pThis->Handle = TSK_create((Fxn)pfn, &pThis->tskattrs, pArg);
	pThis->Handle = Task_create((Task_FuncPtr)pfn, &pThis->tskattrs,&eb);

    if (pThis->Handle == NULL)
    {
			printf("TASK: Failed create thread");
			return FALSE;
            ///SYS_abort("Failed create thread");
			//Raise an exception.
    }

	return TRUE;

}

/*****************************************************************************
** Function name:  Task_Init      
**
** Descriptions: 
**     			   Create a task in a non-running state    
** parameters:     Task *pThis, Task name, Task function, Task Fn Arg, Stack Size, 
				 Task Priority.
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		Task is just created, and it will not run until Task_Start
**                
******************************************************************************/
BOOL Task_Init(Task *pThis, String sName, pfnTask pfn, VOID *pArg)
{

	//pThis->tskattrs = TSK_ATTRS;
	Error_Block eb;
	 Task_Params_init(&(pThis->tskattrs));
	 Error_init(&eb);

	//Setting of Task name
	if (sName != NULL)
	{
		memcpy(pThis->Name, sName, TASK_NAME_SIZE);
		//pThis->tskattrs.name = (String )&pThis->Name[0];
		pThis->tskattrs.instance->name = (String )&pThis->Name[0];
	}
	else
	{
		//pThis->tskattrs.name = "DUMMY";
		pThis->tskattrs.instance->name ="DUMMY";
	}

	//Setting of Task priority
	pThis->tskattrs.priority = STE_TASK_SUSPEND; // Suspend the priority.
	pThis->hPriority = STE_TASK_DEFAULT_PRI;
//	printf("task stacksize %d\n",pThis->tskattrs.stacksize);
	pThis->tskattrs.stackSize= 4*1024;
	//Setting argument
	//	pThis->tskattrs.arg0 =*(xdc_UArg*)pArg;
	pThis->tskattrs.arg0 =(xdc_UArg)pArg;
	
	//pThis->Handle = TSK_create((Fxn)pfn, &pThis->tskattrs, pArg);
	pThis->Handle = Task_create((Task_FuncPtr)pfn, &pThis->tskattrs,&eb);

    if (pThis->Handle == NULL)
    {
			printf("TASK: Failed create thread");
			return FALSE;
    }

	return TRUE;
}



/*****************************************************************************
** Function name:  Task_Start      
**
** Descriptions: 
**     			   Starts the Task with the pre-initialized priority.
** parameters:     Task *pThis 

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
**                
******************************************************************************/

VOID Task_Start(Task *pThis)
{
	LOG_TRACE2("\ninside Task_Start name: %d, Handle:%d .",pThis->hPriority,pThis->Handle);
	//TSK_setpri(pThis->Handle, pThis->hPriority);
	Task_setPri(pThis->Handle, pThis->hPriority);
	LOG_TRACE0("\n After Task_setpri");
}


/*****************************************************************************
** Function name:  Task_Stop      
**
** Descriptions: 
**     			   Stops the Task, and move to Suspend state 
** parameters:     Task *pThis 

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
**                
******************************************************************************/
VOID Task_Stop(Task *pThis)
{
	//TSK_setpri(pThis->Handle, STE_TASK_SUSPEND);
	Task_setPri(pThis->Handle, STE_TASK_SUSPEND);
}

/*****************************************************************************
** Function name:  Task_SetPri      
**
** Descriptions: 
**     			   Provision to Revise the priority of the mentioned task.
** parameters:     Task *pThis, Priority

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
**                
******************************************************************************/
VOID Task_SetPri(Task *pThis, TaskPri ePriority)
{
	pThis->hPriority = ePriority;
	//TSK_setpri(pThis->Handle, ePriority);
	Task_setPri(pThis->Handle, ePriority);
}

/*****************************************************************************
** Function name:  Mutex_Init      
**
** Descriptions: 
**     			   Creates a Mutex Lock using DSP/BIOS Sem obj.
** parameters:     Mutex *pThis, Name, Initial state

** Returned value: TRUE/FALSE  
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
BOOL Mutex_Init( Mutex *pThis , char *name, UINT8 InitState)
{
	//SEM_Attrs attrs = SEM_ATTRS;
	Error_Block eb;
	Semaphore_Params attrs;
	Semaphore_Params_init( &attrs);
	Error_init(&eb);
	attrs.mode= ti_sysbios_knl_Semaphore_Mode_BINARY ;


//Setting of Semaphore name
	if (name != NULL)
	{
		memcpy(pThis->Name, name, SEM_NAME_SIZE);
		//attrs.name = &pThis->Name[0];
		attrs.instance->name = &pThis->Name[0];
	}
	else
	{
		//attrs.name = "DUMMY";
		attrs.instance->name= "DUMMY";
	}

	//pThis->Handle = SEM_create(InitState, &attrs);
	pThis->Handle = Semaphore_create(InitState, &attrs,&eb);

	if (pThis->Handle == NULL) 
	{
		printf("TASK: Failed create Mutex");
     //   SYS_abort("Failed create Semaphore");
		return FALSE;
			//Raise an exception.
    }
	return TRUE;
}
/*****************************************************************************
** Function name:  Mutex_Init      
**
** Descriptions: 
**     			   Try to acquire lock, Will pend until it gets lock.
** parameters:     Mutex *pThis, Name

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
VOID Mutex_Lock( Mutex *pThis )
{
	//SEM_pendBinary(pThis->Handle, SYS_FOREVER);
	Semaphore_pend(pThis->Handle, BIOS_WAIT_FOREVER);
}
/*****************************************************************************
** Function name:  Mutex_Lock_Timeout      
**
** Descriptions: 
**     			   Tries to acquire lock, but will not pend if not available.
** parameters:     Mutex *pThis

** Returned value: TRUE/FALSE   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**			User has to check whether it acquired lock or not by retval.
*****************************************************************************/
BOOL Mutex_Lock_Timeout( Mutex *pThis)
{
	BOOL bStatus;

	//bStatus = SEM_pendBinary(pThis->Handle, 0);
	bStatus = Semaphore_pend(pThis->Handle, 0);

	return bStatus; // TRUE if available
	                // FALSE if timeout.
}

/*****************************************************************************
** Function name:  Mutex_Unlock      
**
** Descriptions: 
**     			   Releases Lock
** parameters:     Mutex *pThis

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
VOID Mutex_Unlock( Mutex *pThis )
{
	//SEM_postBinary(pThis->Handle);
	Semaphore_post(pThis->Handle);
}


/*****************************************************************************
** Function name:  Signal_Init      
**
** Descriptions: 
**     			   Creates a Signal (Actually a sync semaphore.
** parameters:     Signal *pThis, Name

** Returned value: TRUE/FALSE  
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		Basically Signal and Mutex are same (Semaphore)
**         - Semaphore as lock or sync makes the difference
*****************************************************************************/
BOOL Signal_Init( Signal *pThis, char *name)
{
	//SEM_Attrs attrs = SEM_ATTRS;
	Error_Block eb;
		Semaphore_Params attrs;
		Semaphore_Params_init( &attrs);
		Error_init(&eb);
		attrs.mode= ti_sysbios_knl_Semaphore_Mode_BINARY ;

//Setting of Semaphore name
	if (name != NULL)
	{
		memcpy(pThis->Name, name, SEM_NAME_SIZE);
		//attrs.name = &pThis->Name[0];
		attrs.instance->name = &pThis->Name[0];
	}
	else
	{
	//	attrs.name = "DUMMY";
		attrs.instance->name =  "DUMMY";
	}

	//pThis->Handle = SEM_create(0, &attrs);
	pThis->Handle = Semaphore_create(0, &attrs,&eb);
	if (pThis->Handle == NULL)
	{
		return FALSE;
    }

	return TRUE;
}

/*****************************************************************************
** Function name:  CountingSem_Init
**
** Descriptions:
**     			   Creates a Counting semaphore based Signal.
** parameters:     Signal *pThis, Name

** Returned value: TRUE/FALSE
**
** Dependencies/Limitations/Side Effects/Design Notes:
*****************************************************************************/
BOOL CountingSem_Init(Signal *pThis, char *name, UINT32 count)
{
	//SEM_Attrs attrs = SEM_ATTRS;
	Error_Block eb;
	Semaphore_Params attrs;

	Error_init(&eb);
	Semaphore_Params_init( &attrs);

	attrs.mode= ti_sysbios_knl_Semaphore_Mode_COUNTING ;

//Setting of Semaphore name
	if (name != NULL)
	{
		memcpy(pThis->Name, name, SEM_NAME_SIZE);
		//attrs.name = &pThis->Name[0];
		attrs.instance->name = &pThis->Name[0];
	}
	else
	{
	//	attrs.name = "DUMMY";
		attrs.instance->name =  "DUMMY";
	}

	//pThis->Handle = SEM_create(0, &attrs);
	pThis->Handle = Semaphore_create(0, &attrs,&eb);
	if (pThis->Handle == NULL)
	{
		return FALSE;
    }

	return TRUE;
}

/*****************************************************************************
** Function name:  Signal_Pend      
**
** Descriptions: 
**     			   Wait for Signal from external entity forever..
** parameters:     Mutex *pThis, Name

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
VOID Signal_Pend( Signal *pThis)
{
    // SEM_reset(pThis->Handle, 0);
	Semaphore_reset(pThis->Handle, 0);
	 //SEM_pendBinary(pThis->Handle, SYS_FOREVER);
     Semaphore_pend(pThis->Handle, BIOS_WAIT_FOREVER);
}


/*****************************************************************************
** Function name:  Signal_Enable      
**
** Descriptions: 
**     			   A provision to reset the Signal
** parameters:     Mutex *pThis, Name, Initial state

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
void Signal_Enable(Signal *pThis)
{
	//SEM_reset(pThis->Handle, 0);
	Semaphore_reset(pThis->Handle, 0);
}

// 
/*****************************************************************************
** Function name:  Signal_Poll      
**
** Descriptions: 
**     			   To test if any body sent a signal.
** parameters:     Mutex *pThis, Name, Initial state

** Returned value: TRUE/FALSE   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
BOOL Signal_Poll( Signal *pThis, UINT16 nTimeout)
{
	BOOL bStatus;

	//bStatus = SEM_pendBinary(pThis->Handle, 0);
	bStatus = Semaphore_pend(pThis->Handle, 0);
	return bStatus; // TRUE if available
	                // FALSE if timeout.
}

/*****************************************************************************
** Function name:  Signal_Post      
**
** Descriptions: 
**     			   Sends a Signal.
** parameters:     Signal *pThis

** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**		
*****************************************************************************/
#ifdef	ToFindExcpError
UINT32 NumSignal=0;
#endif

#pragma CODE_SECTION(Signal_Post,".text")

VOID Signal_Post( Signal *pThis )
{
	//SEM_postBinary(pThis->Handle);
#ifdef	ToFindExcpError
	//LOG_TRACE1("Inside signalpost pThis->Handle : 0x%x",pThis->Handle);
if(CSL_chipReadDNUM ()==1)
{
	NumSignal++;
		LOG_TRACE1("signal posting :%d ",NumSignal);
}


#endif

	Semaphore_post(pThis->Handle);
#ifdef	ToFindExcpError
//	LOG_TRACE0(" signal posted");
#endif
}
/*************************************EOF*************************************/


