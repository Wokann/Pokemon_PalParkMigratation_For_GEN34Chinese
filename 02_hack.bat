 cd /d %~dp0

 for %%d in (D P Pt HG SS) do (
    tools\armips\armips.exe src\%%d\patch.asm -sym src\%%d\patch.sym
 )
 for %%d in (HG SS) do (
    tools\cue\blz.exe -eo build\%%d\root\ftc\overlay9_74
    tools\armips\armips.exe src\%%d\patch_y9.asm
 )
