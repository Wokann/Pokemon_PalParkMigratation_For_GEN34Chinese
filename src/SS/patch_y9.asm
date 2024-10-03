
.nds
.include ".\src\SS\symbol.h"

.open ".\build\SS\root\ftc\y9.bin", 0
.org 74*0x20 + 0x1C
    .word filesize(".\build\SS\root\ftc\overlay9_74") | (1 << 24)
    //.byte 0,0,0
.close