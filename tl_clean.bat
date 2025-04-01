@echo off

rem *********************************************************************************************
rem ** Usage
rem *********************************************************************************************
rem tl_clean               : Deletes all directories and files listed in this batch file, 
rem                          but ask the user for confirmation
rem tl_clean all           : Deletes all directories and files listed in this batch file.
rem                          but doesn't ask the user for confirmation
rem tl_clean <cguname>     : Deletes all directories and files listed in this batch file and related
rem                          to specified code generation unit; CGU name in lower case
rem tl_clean CGU_NAME_LIST : Lists the names of code generation units taken into account in this
rem                          batch file

if "%~1" == "" (
  call:ASK_USER
) else (
  SET _Mode=%~1
)

if "%_Mode%" == "abort" (
GOTO :EOF
)

if "%_Mode%" == "CGU_NAME_LIST" (
echo *PowerWindowController*
GOTO :EOF
)

if "%_Mode%" == "all" (

rem *********************************************************************************************
rem ** Cleanup all TargetLink predefined directories. 
rem *********************************************************************************************
if exist ".\TLProj" rmdir /s /q ".\TLProj"
if exist ".\CodeViewFiles" rmdir /s /q ".\CodeViewFiles"
if exist ".\CodeCoverageReport" rmdir /s /q ".\CodeCoverageReport"
if exist ".\TLSim" rmdir /s /q ".\TLSim"
if exist ".\TLBuild" rmdir /s /q ".\TLBuild"
if exist ".\TLMil" rmdir /s /q ".\TLMil"

rem *********************************************************************************************
rem ** Cleanup code generation unit specific directories. 
rem *********************************************************************************************
call:delete_powerwindowcontroller_files

rem *********************************************************************************************
rem ** cleanup ASAP2 files and files created during A2L file generation
rem *********************************************************************************************
if exist a2lexport.log                del a2lexport.log
if exist a2l_export_param.dd          del a2l_export_param.dd
if exist asap2_all_in_one.xsl         del asap2_all_in_one.xsl
if exist asap2_all_in_one_module.xsl  del asap2_all_in_one_module.xsl
if exist asap2_default.xsl            del asap2_default.xsl
if exist SymTabParser.cfg             del SymTabParser.cfg
if exist *.a2l                        del *.a2l

rem *********************************************************************************************
rem ** cleanup other files
rem *********************************************************************************************
if exist tl_autoscaling.log           del tl_autoscaling.log
if exist dsdd_validate.log            del dsdd_validate.log
if exist lnk*.tmp                     del lnk*.tmp
if exist make*.lck                    del make*.lck
if exist vc40.pdb                     del vc40.pdb
if exist vc50.pdb                     del vc50.pdb
if exist vc*.idb                      del vc*.idb
if exist NONE                         del NONE
if exist BS_Debug.txt                 del BS_Debug.txt
if exist hdi.hdc                      del hdi.hdc
if exist hdi.hds                      del hdi.hds
if exist tl_diff_cgopt_report.log     del tl_diff_cgopt_report.log

GOTO :EOF
)

if "%_Mode%" == "powerwindowcontroller" (

rem *********************************************************************************************
rem ** Cleanup files generated for code generation unit powerwindowcontroller. 
rem *********************************************************************************************
call:delete_powerwindowcontroller_files
GOTO :EOF
)

GOTO :EOF



rem *********************************************************************************************
rem ** Cleanup file related to code generation unit powerwindowcontroller
rem *********************************************************************************************


:delete_powerwindowcontroller_files
set tl_subsys=powerwindowcontroller
if exist %tl_subsys%_sf.c        del %tl_subsys%_sf.c
if exist %tl_subsys%_sf.mexw64   del %tl_subsys%_sf.mexw64
if exist %tl_subsys%_sfcn.c      del %tl_subsys%_sfcn.c
if exist %tl_subsys%_sfcn.mexw64 del %tl_subsys%_sfcn.mexw64
if exist %tl_subsys%_sf*.pdb     del %tl_subsys%_sf*.pdb
if exist %tl_subsys%_sf.ilk      del %tl_subsys%_sf.ilk

if exist ".\TLSim\PowerWindowController_fri.c" del ".\TLSim\PowerWindowController_fri.c" 
if exist ".\TLSim\PowerWindowController_fri.h" del ".\TLSim\PowerWindowController_fri.h" 
if exist ".\TLSim\powerwindowcontroller_sf.c" del ".\TLSim\powerwindowcontroller_sf.c" 
if exist ".\TLSim\powerwindowcontroller_pcf.c" del ".\TLSim\powerwindowcontroller_pcf.c" 
if exist ".\TLSim\powerwindowcontroller_frm.h" del ".\TLSim\powerwindowcontroller_frm.h" 
if exist ".\TLSim\powerwindowcontroller_frm.mat" del ".\TLSim\powerwindowcontroller_frm.mat" 
if exist ".\TLSim\globals_powerwindowcontroller.*" del ".\TLSim\globals_powerwindowcontroller.*" 
if exist ".\TLSim\tlsim_*_globals.c" del ".\TLSim\tlsim_*_globals.c" 
if exist ".\TLSim\tlsim_*_enums.c" del ".\TLSim\tlsim_*_enums.c" 
if exist ".\TLProj\PowerWindowController\Metadata\powerwindowcontroller_SubsystemObject.dd" del ".\TLProj\PowerWindowController\Metadata\powerwindowcontroller_SubsystemObject.dd" 
if exist ".\TLProj\PowerWindowController" rmdir /s /q ".\TLProj\PowerWindowController" 
if exist ".\TLSim\StubCode\PowerWindowController" rmdir /s /q ".\TLSim\StubCode\PowerWindowController" 
if exist ".\TLProj\PowerWindowController\CGReport" rmdir /s /q ".\TLProj\PowerWindowController\CGReport" 
if exist ".\TLProj\PowerWindowController\Metadata" call:DELETE_IF_EMPTY ".\TLProj\PowerWindowController\Metadata"
if exist ".\TLProj\PowerWindowController" call:DELETE_IF_EMPTY ".\TLProj\PowerWindowController"
if exist ".\TLSim\StubCode" call:DELETE_IF_EMPTY ".\TLSim\StubCode"
if exist ".\TLProj" call:DELETE_IF_EMPTY ".\TLProj"
if exist ".\TLSim" call:DELETE_IF_EMPTY ".\TLSim"
GOTO :EOF
)


:ASK_USER
echo All generated files in the directory
echo   %~dp0%
echo and the .\TLBuild, .\TLProj, .\TLSim, .\TLMil, .\CodeViewFiles and .\CodeCoverageFiles predefined subdirectories - if exist - will be deleted!
echo The files generated for the following code generation units:
echo - PowerWindowController
echo will be deleted!
echo\
set /P _inputname= Are you sure you want to delete these files [y/n]? ... 
echo\
if "%_inputname%" == "y" (
  echo invoking tl_clean.
  set _Mode=all
) else (
  if "%_inputname%" == "Y" (
    echo invoking tl_clean.
    set _Mode=all
    ) else (
      echo tl_clean aborted by the user.
      set _Mode=abort
    )
)
:DELETE_IF_EMPTY
set _TMP=
for /f "delims=" %%a in ('dir /b %1') do (
      if %%a NEQ tl_sim_types.h (set _TMP="%%a")
)
if {%_TMP%}=={} (
      set _empty=Empty
      if exist %1 rmdir /s /q %1
)
