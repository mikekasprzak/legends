@echo off
echo Starting TinyWeb Server on port 8000 -- http://localhost:8000 -- Logs in bin/log/
cd %~dp0\bin\log
%~dp0\bin\TINY.EXE %~dp0\ 8000