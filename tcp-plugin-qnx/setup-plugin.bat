REM Setup QNX Environmet variable
call %UserProfile%\qnx700\qnxsdp-env.bat

set CC=qcc
set CXX=q++

REM Create UNIX Makefiles with cmake
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .