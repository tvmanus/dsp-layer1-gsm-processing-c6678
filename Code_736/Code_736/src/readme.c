/*

1. Filling constants in scratch buffers should be done in respective managers (rx/tx)
   under power on condition
2. function 'RxManager_GetBand' should be made common to both rx/tx manager,
   can think of moving into trxcommon.c
3. need to move providing execution status details to the stack from 'onrxtunests' to when first packet is sent (only for configuration command)
4. need to remove onrxtunests function
5. logic for 'GSMTime_SubTime' and hence FNDelta need to be verified for corner cases.
6. HardCoded/Overrided the Band Information in RxManager_configure_Changes done.
*/

Most of the STE code are re used for TRS


 
