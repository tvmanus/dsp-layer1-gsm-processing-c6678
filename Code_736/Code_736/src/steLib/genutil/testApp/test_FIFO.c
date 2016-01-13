#include "FIFO.h"

VOID main( VOID )
{

	FIFO	Rx;
	CHAR	Val[10];

	FIFO_Init(&Rx);
	FIFO_Print(&Rx);

	FIFO_Put(&Rx, &Val[0]);
	FIFO_Print(&Rx);

	FIFO_Put(&Rx, &Val[1]);
	FIFO_Print(&Rx);

	FIFO_Put(&Rx, &Val[2]);
	FIFO_Print(&Rx);

	FIFO_Get(&Rx);
	FIFO_Print(&Rx);

	FIFO_Put(&Rx, &Val[3]);
	FIFO_Print(&Rx);

	FIFO_Get(&Rx);
	FIFO_Print(&Rx);

	FIFO_Get(&Rx);
	FIFO_Print(&Rx);

	FIFO_Put(&Rx, &Val[4]);
	FIFO_Print(&Rx);

	FIFO_Get(&Rx);
	FIFO_Print(&Rx);

	FIFO_Get(&Rx);
	FIFO_Print(&Rx);

	FIFO_Get(&Rx);
	FIFO_Print(&Rx);
}