
.nds
.include ".\src\P\symbol.h"

.open ".\build\P\root\ftc\arm9.bin", arm9_start
 .org GetOpeningQuote
 conversion_table_quote:
    .incbin ".\build\conversion_table_quote.bin"
 .org Label_ConvertRSStringToDPStringInternational
    .importobj ".\build\rs_migrate_string.o"
 .org conversion_table
    .hword 0x0001, 0x01DE
.close


.open ".\build\P\root\ftc\overlay9_83", overlay9_83_start
 .org UnlockRegion
    .hword 0xD1FF

 .org overlay9_83_start + overlay9_83_size + overlay9_83_bss_size
 conversion_table_chinese:
    .incbin ".\build\conversion_table_chinese.bin"
 overlay9_83_end:
.close


.open ".\build\P\root\ftc\y9.bin", 0
.org 83*0x20 + 8
    .word (overlay9_83_end - overlay9_83_start)
.close