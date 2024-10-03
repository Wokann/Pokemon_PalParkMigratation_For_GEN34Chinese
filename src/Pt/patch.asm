
.nds
.include ".\src\Pt\symbol.h"

.open ".\build\Pt\root\ftc\arm9.bin", arm9_start
 .org GetOpeningQuote
 conversion_table_quote:
    .incbin ".\build\conversion_table_quote.bin"
 .org Label_ConvertRSStringToDPStringInternational
    .importobj ".\build\rs_migrate_string.o"
 .org conversion_table
    .hword 0x0001, 0x01DE
.close


.open ".\build\Pt\root\ftc\overlay9_97", overlay9_97_start
 .org UnlockRegion
    .hword 0xD1FF

 .org overlay9_97_start + overlay9_97_size + overlay9_97_bss_size
 conversion_table_chinese:
    .incbin ".\build\conversion_table_chinese.bin"
 overlay9_97_end:
.close


.open ".\build\Pt\root\ftc\y9.bin", 0
.org 97*0x20 + 8
    .word (overlay9_97_end - overlay9_97_start)
.close