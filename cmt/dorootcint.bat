REM do rootcint for Recon ROOT classes

REM Save the current directory, so we can return when finished
cd > dirstor.txt
copy %RECONROOTDATAROOT%\cmt\cd.cmd+dirstor.txt %RECONROOTDATAROOT%\changeDir.bat
del dirstor.txt

cd %RECONROOTDATAROOT%\reconRootData
REM Remove old cint files
del ReconCint.cxx
del ReconCint.h

%ROOT_PATH%\bin\rootcint -f ReconCint.cxx -c -I%DIGIROOTDATAROOT% CalCluster.h CalLogEne.h CalRecon.h Recon.h ReconHeader.h TkrGamma.h TkrHit.h TkrLocator.h TkrRecon.h TkrSiCluster.h TkrTrack.h ReconLinkDef.h

REM Return to the original directory
call %RECONROOTDATAROOT%\changeDir.bat
del %RECONROOTDATAROOT%\changeDir.bat
