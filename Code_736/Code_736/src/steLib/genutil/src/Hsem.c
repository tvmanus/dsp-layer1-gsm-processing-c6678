#include<ti\sysbios\knl\Task.h>

#include <Hsem.h>
#include <Task.h>
//#include <log.h>
//#include<xdc/runtime/LoggerBuf.h> // should be removed this include file
#include<xdc/runtime/Log.h>

//CSL_SemContext  semcontext;
//CSL_Status      semstat;

extern far const int Core_Num;

#ifndef SINGLE_CORE_OPERATION

//#pragma CODE_SECTION(HSEM_ModuleInit,".textDDR")

void HSEM_ModuleInit()
{
	//Hsem oDummySem;
	//UINT8 nSemIndex = 0;
	Uint8 nSemIndex = 0;
	 Bool isFree;



	/*if (CSL_SOK != CSL_semInit(&semcontext))
	{
		LOG_TRACE0( "CSL_semInit error ");
	}

	HSEM_Init(&oDummySem, HSEM_LAST);

	for (nSemIndex = 0; nSemIndex <= HSEM_LAST ; ++nSemIndex)
	{
		oDummySem.hSemHandle->regs->DIRECT[nSemIndex] = 1; // Makes forcefull free
	}
	CSL_semClose(oDummySem.hSemHandle);*/ // not required in C6678

	for (nSemIndex = 0; nSemIndex <= HSEM_LAST ; ++nSemIndex)
	{
		// Check if Semaphore is Free or not.
		   isFree = CSL_semIsFree(nSemIndex);
		 // if the semaphore is not free, force the semaphore to free
		    if((!isFree))
		        {
		        // Release the semaphore.
		           CSL_semReleaseSemaphore(nSemIndex);

		        }

	}
}

//#pragma CODE_SECTION(HSEM_Init,".textDDR")

void HSEM_Init(Hsem *pThis, UINT8 nSemNum)
{
//	CSL_Status      semstat; // not required for C6678
	Bool isFree; // for c6678

	pThis->Sem_Number = (HSEM_NUM)nSemNum;  // for c6678

	if(nSemNum >= HSEM_INVALID)
	{
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code
		LOG_WARN( "Invalid Hsem %d", nSemNum);
#endif
		return;
	}
	else
	{

	LOG_TRACE1("HSEM_init - Sem number %d ", nSemNum);
//	pThis->oParam.flags = nSemNum; // not required for c6678 API
	
/*	pThis->hSemHandle = CSL_semOpen(&pThis->oSemObj, CSL_SEM, &pThis->oParam, &semstat);
	if (semstat != CSL_SOK)
	{
		LOG_TRACE0("Sem open error");

		// To Raise Exception
	}*/

	//pThis->hSemHandle->regs->DIRECT[nSemNum] = 1; // Makes forcefull free
//##############  above commented lines are not required for c6678 API #############
	 // Makes forcefull free


	 isFree = CSL_semIsFree (nSemNum); 	// Check if Semaphore is Free or not.
	 // if the semaphore is not free, forcefully make the semaphore to free
	  if((!isFree))
		{
		// Release the semaphore.
		  CSL_semReleaseSemaphore (nSemNum);

	    }

	}
//	HSEM_Unlock(pThis);

}

void HSEM_Lock(Hsem *pThis)
{
	//volatile CSL_SemVal semVal; // not required for C6678

	while(1)
	{
		/*if (CSL_SOK != CSL_semGetHwStatus(pThis->hSemHandle, CSL_SEM_QUERY_STATUS, (void *)&semVal ))
		{
			LOG_TRACE0("CSL_semGetHwStatus error");
		}

		if(semVal.semFree == CSL_SEM_FREE)
		{
			break;
		}*/
//##############  above commented lines are not required for c6678 API #############
		if(CSL_semIsFree (pThis->Sem_Number))
		{
			break;
		}
		else
		{
			//LOG_TRACE1( "lock waitng for sem %d ", pThis->hSemHandle->semNum); // old

	//		LOG_TRACE1( "lock waitng for sem %d ", pThis->Sem_Number); // new

			//TSK_yield();// DSPBIOS function
			Task_yield();// SYSBIOS function
		}

	}

	while(1)
	{
		//if (CSL_SOK != CSL_semHwControl(pThis->hSemHandle, CSL_SEM_CMD_WRITE_POST_DIRECT,(CSL_SemVal *) &semVal))
	//	{
	//		LOG_TRACE0("CSL_semHwControl error");
	//	}
         if(!CSL_semAcquireDirect(pThis->Sem_Number))
         {
        	 LOG_TRACE0("CSL_semHwControl error");
         }
	//	if (CSL_SOK != CSL_semGetHwStatus(pThis->hSemHandle, CSL_SEM_QUERY_STATUS,(CSL_SemVal *) &semVal))
	//	{
	//		LOG_TRACE0("CSL_semHwControl error");
	//	}

	//	if ((semVal.semFree != CSL_SEM_FREE) && (semVal.semOwner == Core_Num ))
	//	{
	//		break;
	//	}

         if((!CSL_semIsFree (pThis->Sem_Number)) &&(CSL_semGetResourceOwner(pThis->Sem_Number)== Core_Num))
         {
        	 break;
         }
		else
		{
			//LOG_TRACE1( "HSEM: lock acquiring sem %d ", pThis->hSemHandle->semNum);
			LOG_TRACE1( "HSEM: lock acquiring sem %d ", pThis->Sem_Number);
			//TSK_yield();// DSPBIOS function
			Task_yield();// SYSBIOS function

		}

	}
//	LOG_TRACE("HSem Locked %x", pThis->oParam.flags );
}


void HSEM_Unlock(Hsem *pThis)
{

	//volatile CSL_SemVal semVal; // not required for C6678

//	LOG_FATAL( "Testing HSem %x",pThis);

while(1)
	{
		//if (CSL_SOK != CSL_semHwControl(pThis->hSemHandle, CSL_SEM_CMD_FREE_DIRECT, NULL))
	//	{
		//	LOG_TRACE0("CSL_semGetHwStatus error");
	//	}
    //	if (CSL_SOK != CSL_semGetHwStatus(pThis->hSemHandle, CSL_SEM_QUERY_STATUS, (void *)&semVal ))
	//	{
		//	LOG_TRACE0("CSL_semGetHwStatus error");
	//	}
	//	if (semVal.semFree == CSL_SEM_FREE)
	if(CSL_semIsFree (pThis->Sem_Number))
		{
			break;
		}
		else
		{
			CSL_semReleaseSemaphore(pThis->Sem_Number);
			//LOG_TRACE1( "unlock waitng for sem %d" , pThis->hSemHandle->semNum);
	//		LOG_TRACE1( "unlock waitng for sem %d" , pThis->Sem_Number);
			//TSK_yield();// DSPBIOS function
	//		Task_yield();// SYSBIOS function

		}

		

	}



}
#else
void HSEM_ModuleInit(){}
void HSEM_Init(Hsem *pThis, UINT8 nSemNum){}
void HSEM_Lock(Hsem *pThis){}
void HSEM_Unlock(Hsem *pThis){}

#endif //#ifndef SINGLE_CORE_OPERATION
