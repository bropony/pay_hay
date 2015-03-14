call SetPathCpp.bat


set DBURL=mysql://%DBIP%:3306/%CONFIG_DB%

%TOOLDIR%dbexport --db-type=mysql --db-url=%DBURL% --db-name=root --db-password=%DB_PWD% --output-dir=%WORKBASE%Workspace\config\data\ --lua-config-dir=%INCLUDEDIR% --output-lua-dir=%INCLUDEDIR%dummy/ --make-tables=

pause
exit
