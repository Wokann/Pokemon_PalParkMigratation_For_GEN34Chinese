 arm9_start                             equ 0x02000000

 overlay9_97_start                      equ 0x0222A260
 overlay9_97_size                       equ 0x010A60
 overlay9_97_bss_size                   equ 0x1980

 UnlockRegion                           equ 0x0223097A

.definelabel GetSpaceChar                                   ,0x022387D4
.definelabel GetOpeningQuote                                ,0x022387E8
.definelabel GetClosingQuote                                ,0x02238824
.definelabel Label_ConvertRSStringToDPStringInternational   ,0x0223885C
.definelabel conversion_table                               ,0x022396AC
