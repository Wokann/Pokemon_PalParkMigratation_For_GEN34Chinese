
.nds
.include ".\src\HG\symbol.h"

.open ".\build\HG\root\ftc\overlay9_74", overlay9_74_start
 .org UnlockRegion
    .hword 0xD1FF
 .org GetOpeningQuote
 conversion_table_quote:
    .incbin ".\build\conversion_table_quote.bin"
 .org Label_ConvertRSStringToDPStringInternational
    .importobj ".\build\rs_migrate_string.o"
 .org conversion_table
    .hword 0x0001, 0x01DE
 .org overlay9_74_start + overlay9_74_size + overlay9_74_bss_size
 conversion_table_chinese:
    .incbin ".\build\conversion_table_chinese.bin"
 overlay9_74_end:
.close


.open ".\build\HG\root\ftc\y9.bin", 0
.org 74*0x20 + 8
    .word (overlay9_74_end - overlay9_74_start)
.close