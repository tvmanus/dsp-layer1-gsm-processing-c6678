echo off
echo "creating steappCx.prj's Hex files...."
cd ..\out
C:\CCStudio_v3.3\C6000\cgtools\bin\hex6x.exe -i -boot -romwidth 32 -memwidth 32 -e _c_int00 -order L -o AppC0.hex appc0.out
C:\CCStudio_v3.3\C6000\cgtools\bin\hex6x.exe -i -boot -romwidth 32 -memwidth 32 -e _c_int00 -order L -o AppC1.hex appc1.out
C:\CCStudio_v3.3\C6000\cgtools\bin\hex6x.exe -i -boot -romwidth 32 -memwidth 32 -e _c_int00 -order L -o AppC2.hex appc2.out
DEL ..\..\SteBoot\out\*.hex
move *.hex ..\..\SteBoot\out
