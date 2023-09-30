C:\devkitPro\devkitARM\bin\arm-none-eabi-gcc.exe -mabi=aapcs -std=c99 -w -nostartfiles -nodefaultlibs -Os -march=armv5te -mtune=arm946e-s -mthumb -Wl,--use-blx -I C:\devkitPro/libnds/include -o rs_migrate_string.elf rs_migrate_string.c -T symbol.sym -T linker.ld

C:\devkitPro\devkitARM\bin\arm-none-eabi-objcopy.exe -O binary rs_migrate_string.elf rs_migrate_string.bin

pause