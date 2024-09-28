setlocal enabledelayedexpansion
    set tool_ndstool=.\tools\ndstool\ndstool.exe
    set tool_tinkedsi=.\tools\tinke\Tinke.exe
    set tempfolder=.\.temp\Diamond
    set tempfolder_repack=.\.temp_repack\Diamond
    set originndsfile=.\rom\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds
    set newndsfile=.\rom\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds
    set repackndsfile=.\rom\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_repack.nds

    del %tempfolder%\root\ftc\arm9.bin.bak
    
    %tool_ndstool% -c %newndsfile% ^
        -9  %tempfolder%\root\ftc\arm9.bin ^
        -7  %tempfolder%\root\ftc\arm7.bin ^
        -y9 %tempfolder%\root\ftc\y9.bin ^
        -y7 %tempfolder%\root\ftc\y7.bin ^
        -d  %tempfolder%\root\data ^
        -y  %tempfolder%\root\overlay ^
        -t  %tempfolder%\root\ftc\banner.bin ^
        -h  %tempfolder%\root\ftc\header.bin

    if exist %tempfolder_repack% ( rd /s /q %tempfolder_repack%)
    %tool_tinkedsi% extract ^
        -f %newndsfile% ^
        -o %tempfolder_repack%
    %tool_tinkedsi% replace ^
        -f %newndsfile% ^
        -d %tempfolder_repack%\root ^
        -o %repackndsfile%
    move /Y %repackndsfile% %newndsfile%

endlocal