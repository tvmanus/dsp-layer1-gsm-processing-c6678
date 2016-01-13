10:27 PM 6/11/2014


DDC optimization Code.

For boot issue :
~~~~~~~~~~~~~~~

Observed a Warning in appC0 Build,so changing the compiler version.
Changed Compiller version to 7.4.4 (All the Libraries and projects).


Booting and Working.

But HM is Not working.

Removed warning.

After Warning removal HM is working.

Changed fix_t2 to t2 in L1FEC.c

Removed most of the Logs.

Added logs for SACCH Decoding in Traffic.
____________________________________________________________________________________.

Removed Resync during network scan , Resync will not work for network scan.

____________________________________________________________________________________.

10:16 PM 7/9/2014
------------------

Full Rate Not hearing:
~~~~~~~~~~~~~~~~~~~~~~

  -- Removed nBurstStartIndex from adding it to NextBurstoffset.
  --  Full rate Calls Hearing and Ending properly.
  --  Other Codecs Also Working fine.
____________________________________________________________________________________.


9:44 PM 7/17/2014


FPGA Remote Upgrade Integrated.

HM and GPS Working properly.
____________________________________________________________________________________.

1:55 PM 8/2/2014

Removed HWI 14 from all the .cfg files(To solve core_0 exception).
Few Logs for Total L2Pkt,Response,HM from DSP to IPU.
Few Logs for SACCH Decoding count.

____________________________________________________________________________________.

ToDO:
~~~~

1. Core 0 Exception.(Removed HWI 14,Still CopySamples Assembly exception is there).
2. Ethernet not up.  (Hardware issue).
3. Packet List.

