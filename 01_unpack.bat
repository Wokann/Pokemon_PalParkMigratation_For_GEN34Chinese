setlocal enabledelayedexpansion
    set tool_ndstool=.\tools\ndstool\ndstool.exe
    set tempfolder=.\.temp\Diamond-2
    set originndsfile=.\rom\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds

    if exist %tempfolder% ( rd /s /q %tempfolder%)
        md %tempfolder%\root\ftc
        %tool_ndstool% -x %originndsfile% ^
            -9  %tempfolder%\root\ftc\arm9.bin ^
            -7  %tempfolder%\root\ftc\arm7.bin ^
            -y9 %tempfolder%\root\ftc\y9.bin ^
            -y7 %tempfolder%\root\ftc\y7.bin ^
            -d  %tempfolder%\root\data ^
            -y  %tempfolder%\root\overlay ^
            -t  %tempfolder%\root\ftc\banner.bin ^
            -h  %tempfolder%\root\ftc\header.bin
        md %tempfolder%\root\data\zhn
endlocal