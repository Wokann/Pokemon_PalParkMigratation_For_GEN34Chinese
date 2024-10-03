 arm9_start                             equ 0x02000000

 overlay9_83_start                      equ 0x0222F6E0
 overlay9_83_size                       equ 0xF5A0
 overlay9_83_bss_size                   equ 0x1980

 UnlockRegion                           equ 0x0223097A

.definelabel Label_ConvertRSStringToDPStringInternational   ,0x020164C0
.definelabel GetOpeningQuote                                ,0x02016574
.definelabel GetClosingQuote                                ,0x020165B0
.definelabel GetSpaceChar                                   ,0x020165EC
.definelabel conversion_table                               ,0x020EF7D4 //~0x020EFBAF (0x03DC=0xF7*2*2)
