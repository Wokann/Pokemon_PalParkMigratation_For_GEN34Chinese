 cd /d %~dp0
 C:\devkitPro\devkitARM\bin\arm-none-eabi-gcc.exe -mabi=aapcs -std=c99 -w -nostartfiles -nodefaultlibs -Os -march=armv5te -mtune=arm946e-s -mthumb -Wl,--use-blx -I C:\devkitPro\libnds\include -c src\common\rs_migrate_string.c -o build\rs_migrate_string.o -DGEN4_JP
 C:\devkitPro\devkitARM\bin\arm-none-eabi-gcc.exe -mabi=aapcs -std=c99 -w -nostartfiles -nodefaultlibs -Os -march=armv5te -mtune=arm946e-s -mthumb -Wl,--use-blx -I C:\devkitPro\libnds\include -c src\common\conversion_table_quote.c -o build\conversion_table_quote.o
 C:\devkitPro\devkitARM\bin\arm-none-eabi-gcc.exe -mabi=aapcs -std=c99 -w -nostartfiles -nodefaultlibs -Os -march=armv5te -mtune=arm946e-s -mthumb -Wl,--use-blx -I C:\devkitPro\libnds\include -c src\common\conversion_table_chinese.c -o build\conversion_table_chinese.o -DGEN4_JP
  
 C:\devkitPro\devkitARM\bin\arm-none-eabi-objcopy.exe -O binary build\rs_migrate_string.o build\rs_migrate_string.bin
 C:\devkitPro\devkitARM\bin\arm-none-eabi-objcopy.exe -O binary build\conversion_table_quote.o build\conversion_table_quote.bin
 C:\devkitPro\devkitARM\bin\arm-none-eabi-objcopy.exe -O binary build\conversion_table_chinese.o build\conversion_table_chinese.bin
 if exist build\conversion_table_quote.o del build\conversion_table_quote.o
 if exist build\conversion_table_chinese.o del build\conversion_table_chinese.o

 for %%d in (D P Pt HG SS) do (
    if exist build\%%d ( rd /s /q build\%%d)
    mkdir build\%%d\root\ftc
    xcopy src\%%d\root build\%%d\root /e /h /i /y
 )
 for %%d in (HG SS) do (
    tools\cue\blz.exe -d build\%%d\root\ftc\overlay9_74
 )
