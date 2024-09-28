:: 此指令用于测试.s文件转回bin
@echo on
setlocal enabledelayedexpansion
:: 设置指令路径、载入基础数据、返回当前路径
    set "WorkPath=%~dp0"
    cd /d %WorkPath%
:: 返回根目录
    cd ../../../
:: 设置工具及码表文件
    set tool_armips=.\tools\armips\armips.exe
    set asmFile1=.\tools\wokann\transMsg\testasmjoin.asm
    set asmFile2=.\tools\wokann\transMsg\testasmjoin_jp.asm

    :: %tool_armips% %asmFile1%
    %tool_armips% %asmFile2%
endlocal