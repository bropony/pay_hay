echo off

cd ..
set WORKBASE=%cd%\
cd ..

set path=%path%;%WORKBASE%\Public\toolsexe

cd /d %WORKBASE%Public

set OUTCPPBASE=%WORKBASE%Cpp/Server/Message/
set SERVERBASE=%WORKBASE%Cpp/Server/
set INCLUDEDIR=%WORKBASE%Public/
set INCLUDEBASE=Message/
set TOOLDIR=%WORKBASE%Public/toolsexe/
set TOOLDIR_PUBLIC=%WORKBASE%Public/toolsexe_public/

set DBIP=112.74.102.141
set DB_PWD=root
set DB_VERSION=_0_0_1
set DB_BASE=pay_hay
set CONFIG_DB=%DB_BASE%_config%DB_VERSION%
set MAIN_DB=%DB_BASE%%DB_VERSION%
set LOG_DB=%DB_BASE%_log%DB_VERSION%

echo WORKBASE is %WORKBASE%
echo PWD is %cd%
echo on
