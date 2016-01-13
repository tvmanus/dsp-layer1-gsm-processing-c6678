/*
 * delay.c
 *
 *  Created on: Apr 30, 2014
 *      Author: lab3admin
 */
#include <xdc/std.h>
#include "csl_chip.h"
#include <DataType.h>

Void CycleDelay (Int32 count);
/** ============================================================================
 *   @n@b CycleDelay
 *
 *   @b Description
 *   @n This API implements a clock delay logic using the Time Stamp Counter (TSC)
 *      of the DSP.
 *
 *   @param[in]
 *   @n count               Number of delay cycles to wait.
 *
 *   @return
 *   @n None
 * =============================================================================
 */
Void CycleDelay (Int32 count)
{
    UInt32                  TSCLin;

    if (count <= 0)
        return;

    /* Get the current TSCL  */
    TSCLin = TSCL ;

    while ((TSCL - TSCLin) < (UInt32)count);
}



