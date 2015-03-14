call SetPathCpp.bat

%TOOLDIR%cdl2cpp -I%INCLUDEDIR% Message/Public/CdlPublic.cdl --output-dir=%OUTCPPBASE%Public --include-dir=%INCLUDEBASE%Public --output-regist=%OUTCPPBASE%

pause
exit

