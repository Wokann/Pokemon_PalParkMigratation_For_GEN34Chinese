:: 此指令用于编译wokann文件夹内的工具
@echo on
setlocal enabledelayedexpansion
    set "WorkPath=%~dp0"
    cd /d %WorkPath%
    make clean
    make
endlocal