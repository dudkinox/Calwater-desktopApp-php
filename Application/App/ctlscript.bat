@echo off
rem START or STOP Services
rem ----------------------------------
rem Check if argument is STOP or START

if not ""%1"" == ""START"" goto stop

if exist C:\xampp\hypersonic\scripts\ctl.bat (start /MIN /B C:\xampp\server\hsql-sample-database\scripts\ctl.bat START)
if exist C:\xampp\ingres\scripts\ctl.bat (start /MIN /B C:\xampp\ingres\scripts\ctl.bat START)
if exist C:\xampp\mysql\scripts\ctl.bat (start /MIN /B C:\xampp\mysql\scripts\ctl.bat START)
if exist C:\xampp\postgresql\scripts\ctl.bat (start /MIN /B C:\xampp\postgresql\scripts\ctl.bat START)
if exist C:\xampp\apache\scripts\ctl.bat (start /MIN /B C:\xampp\apache\scripts\ctl.bat START)
if exist C:\xampp\openoffice\scripts\ctl.bat (start /MIN /B C:\xampp\openoffice\scripts\ctl.bat START)
if exist C:\xampp\apache-tomcat\scripts\ctl.bat (start /MIN /B C:\xampp\apache-tomcat\scripts\ctl.bat START)
if exist C:\xampp\resin\scripts\ctl.bat (start /MIN /B C:\xampp\resin\scripts\ctl.bat START)
if exist C:\xampp\jetty\scripts\ctl.bat (start /MIN /B C:\xampp\jetty\scripts\ctl.bat START)
if exist C:\xampp\subversion\scripts\ctl.bat (start /MIN /B C:\xampp\subversion\scripts\ctl.bat START)
rem RUBY_APPLICATION_START
if exist C:\xampp\lucene\scripts\ctl.bat (start /MIN /B C:\xampp\lucene\scripts\ctl.bat START)
if exist C:\xampp\third_application\scripts\ctl.bat (start /MIN /B C:\xampp\third_application\scripts\ctl.bat START)
goto end

:stop
echo "Stopping services ..."
if exist C:\xampp\third_application\scripts\ctl.bat (start /MIN /B C:\xampp\third_application\scripts\ctl.bat STOP)
if exist C:\xampp\lucene\scripts\ctl.bat (start /MIN /B C:\xampp\lucene\scripts\ctl.bat STOP)
rem RUBY_APPLICATION_STOP
if exist C:\xampp\subversion\scripts\ctl.bat (start /MIN /B C:\xampp\subversion\scripts\ctl.bat STOP)
if exist C:\xampp\jetty\scripts\ctl.bat (start /MIN /B C:\xampp\jetty\scripts\ctl.bat STOP)
if exist C:\xampp\hypersonic\scripts\ctl.bat (start /MIN /B C:\xampp\server\hsql-sample-database\scripts\ctl.bat STOP)
if exist C:\xampp\resin\scripts\ctl.bat (start /MIN /B C:\xampp\resin\scripts\ctl.bat STOP)
if exist C:\xampp\apache-tomcat\scripts\ctl.bat (start /MIN /B /WAIT C:\xampp\apache-tomcat\scripts\ctl.bat STOP)
if exist C:\xampp\openoffice\scripts\ctl.bat (start /MIN /B C:\xampp\openoffice\scripts\ctl.bat STOP)
if exist C:\xampp\apache\scripts\ctl.bat (start /MIN /B C:\xampp\apache\scripts\ctl.bat STOP)
if exist C:\xampp\ingres\scripts\ctl.bat (start /MIN /B C:\xampp\ingres\scripts\ctl.bat STOP)
if exist C:\xampp\mysql\scripts\ctl.bat (start /MIN /B C:\xampp\mysql\scripts\ctl.bat STOP)
if exist C:\xampp\postgresql\scripts\ctl.bat (start /MIN /B C:\xampp\postgresql\scripts\ctl.bat STOP)

:end

