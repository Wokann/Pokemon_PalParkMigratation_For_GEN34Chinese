
.nds
.include ".\src\Pt\symbol.h"

.open ".\build\Pt\root\ftc\overlay9_97", overlay9_97_start
 .org UnlockRegion
    .hword 0xD1FF //0xD105
 .org Unlock24hourLimit
    .hword 0xE01E //0xD11E
 .org GetOpeningQuote
 conversion_table_quote:
    .incbin ".\build\conversion_table_quote.bin"
 .org Label_ConvertRSStringToDPStringInternational
    .importobj ".\build\rs_migrate_string.o"
 .org conversion_table
    .hword 0x0001, 0x01DE

 .org overlay9_97_start + overlay9_97_size + overlay9_97_bss_size
 conversion_table_chinese:
    .incbin ".\build\conversion_table_chinese.bin"
 overlay9_97_end:
.close


.open ".\build\Pt\root\ftc\y9.bin", 0
.org 97*0x20 + 8
    .word (overlay9_97_end - overlay9_97_start)
.close