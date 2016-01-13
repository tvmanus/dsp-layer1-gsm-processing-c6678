/*
 * Timestamp.c
 *
 *  Created on: Feb 26, 2014
 *      Author: nachiappanr
 */

#include "cslr_tmr.h"
#include "cslr_device.h"
#include "string.h"
#include "Timestamp.h"
#include "EthBuff.h"

CSL_TmrRegs*  TimerReg = (CSL_TmrRegs*) CSL_TIMER_11_REGS;

void Init_timestamp_obj(Timestamp_obj* pThis, char* name)
{
	strcpy(pThis->name, name);
	pThis->min_time =0xFFFFFFFF;
	pThis->max_time =0;
	pThis->avg_time =0;
	pThis->startiteration =0;
	pThis->stopiteration =0;
	pThis->timetaken = 0;
}

void START(Timestamp_obj* pThis)
{
	pThis->start_timestamp = *(uint32_t*) TimerReg->CNTLO;
	pThis->startiteration++;
	Eth_Debug((CHAR *)"S %d",pThis->start_timestamp);
}

void STOP(Timestamp_obj* pThis)
{
	pThis->stop_timestamp = *(uint32_t*) TimerReg->CNTLO;
	pThis->timetaken = (pThis->stop_timestamp>pThis->start_timestamp) ? (pThis->stop_timestamp - pThis->start_timestamp) : (pThis->start_timestamp- pThis->stop_timestamp);
	Eth_Debug((CHAR*)"TT: %lld P %d",pThis->timetaken,pThis->stop_timestamp);
	pThis->stopiteration++;
	if(pThis->startiteration == pThis->stopiteration)
	{
	calc_min_time(pThis,&pThis->timetaken);
	calc_max_time(pThis,&pThis->timetaken);
	calc_avg_time(pThis,&pThis->timetaken);
	}
	else
	{
		Eth_Debug((CHAR*)"Number of STOP didn't match with the START for the function %s\n",pThis->name);
		pThis->stopiteration = 0;
		return ;
	}

	if(pThis->startiteration == MAX_ITERATIONS)
	{
		Timestamp_flush_reset(pThis);
	}


}

void inline calc_min_time(Timestamp_obj * pThis,uint32_t* Timetaken)
{
	if(*Timetaken < pThis->min_time)
	{
		pThis->min_time = *Timetaken;
	}
}

void inline calc_max_time(Timestamp_obj * pThis,uint32_t* Timetaken)
{
	if(*Timetaken > pThis->max_time)
	{
		pThis->max_time = *Timetaken;
	}
}

void inline calc_avg_time(Timestamp_obj * pThis,uint32_t* Timetaken)
{

	if(pThis->stopiteration==1) //First iteration
	{
		pThis->avg_time = *Timetaken;
		return;
	}
	pThis->avg_time = ((pThis->avg_time * (pThis->stopiteration-1)) + (*Timetaken))/pThis->stopiteration; //weighted average function

}

void inline Timestamp_flush_reset(Timestamp_obj * pThis)
{
	Eth_Debug((CHAR*)"MAX, AVG, MIN of %s function is %llu %llu %llu",pThis->name,pThis->max_time,pThis->avg_time,pThis->min_time);

	pThis->min_time =0xFFFFFFFF;
	pThis->max_time =0;
	pThis->avg_time =0;
	pThis->startiteration =0;
	pThis->stopiteration =0;
	pThis->timetaken =0;
}
