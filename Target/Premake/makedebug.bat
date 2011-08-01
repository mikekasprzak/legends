
:prebuild

msbuild Build/MySolution.sln /property:Configuration=Debug

:postbuild

@if "%1" == "run"		goto :run
@goto :end

:run
@set OLDDIR=%CD%
@cd ..\..
%OLDDIR%\Build\Debug\Legends.exe -DIR .\
@chdir /d %OLDDIR%
@goto :end

@rem if not "%2" == "" goto IDunnoGoSomewhere

:end
