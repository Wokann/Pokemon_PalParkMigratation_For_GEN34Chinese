 arm9_start                             equ 0x02000000

 overlay9_74_start                      equ 0x022265A0
 overlay9_74_size                       equ 0x012720
 overlay9_74_bss_size                   equ 0x1980
 overlay9_74_comp_size                  equ 0xE698

 UnlockRegion                           equ 0x02226BD8

.definelabel GetSpaceChar                                   ,0x02236528
.definelabel GetOpeningQuote                                ,0x0223653C
.definelabel GetClosingQuote                                ,0x02236578
.definelabel Label_ConvertRSStringToDPStringInternational   ,0x022365B0
.definelabel conversion_table                               ,0x0223742C
