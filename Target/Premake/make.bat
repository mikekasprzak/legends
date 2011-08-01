
:prebuild

msbuild Build\MySolution.sln /property:Configuration=Release

:postbuild

@if "%1" == "run"		goto :run
@goto :end

:run
@set OLDDIR=%CD%
@cd ..\..
%OLDDIR%\Build\Release\Legends.exe -DIR .\
@chdir /d %OLDDIR%
@goto :end

@rem if not "%2" == "" goto IDunnoGoSomewhere

:end
