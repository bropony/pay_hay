call SetPathCpp.bat

set DBURL=mysql://%DBIP%:3306/%MAIN_DB% 
@REM,mysql://%DBIP%:3306/%LOG_DB%

@REM svn update %INCLUDEDIR%Message

%TOOLDIR%dbtools --db-type=mysql --db-url=%DBURL% --db-name=root --db-password=%DB_PWD% --name-space=Message::Db::Tables --output-dir=%INCLUDEDIR%Message/Db/Tables/ --dao-dir=%SERVERBASE%Dao/ --dao-include=Dao/ --dao-tableinclude=Message/Db/Tables/ --table-include=%INCLUDEDIR% --table-outdir=%OUTCPPBASE%Db/Tables --make-tables=

pause
exit