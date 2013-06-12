@echo off


SET AudioLoc="OUTPUT/Audio/"
SET VideoLoc="OUTPUT/Video/"
SET Finalloc="OUTPUT/Final/"
SET Logloc="logs/"
SET Toolsloc="Tools/"


Echo compiling...
g++ encode.cpp -Wall -o main
Echo Done!
Echo Running...
main %AudioLoc% %VideoLoc% %Finalloc% %Logloc% %Toolsloc%
Echo Done!
Echo Press Any Key
pause > nul