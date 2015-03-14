call SetPathCpp.bat

set DBURL=mysql://%DBIP%:3306/%CONFIG_DB%


%TOOLDIR%dbtools --db-type=mysql --db-url=%DBURL% --db-name=root --db-password=%DB_PWD% --name-space=Message::Db::Tables --output-dir=%INCLUDEDIR%Message/Db/Tables/ --dao-tableinclude=Message/Db/Tables/ --table-include=%INCLUDEDIR% --table-outdir=%OUTCPPBASE%Db/Tables --load --make-tables=

pause