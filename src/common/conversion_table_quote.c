#include "nds/ndstypes.h"

#define LANGUAGE_JAPANESE 1
#define LANGUAGE_ENGLISH 2
#define LANGUAGE_FRENCH 3
#define LANGUAGE_ITALIAN 4
#define LANGUAGE_GERMAN 5
#define LANGUAGE_SPANISH 7
#define LANGUAGE_KOREAN 8

const u16 conversion_table_quote[][9] =
{
    {
        [LANGUAGE_JAPANESE - 1] = 0xEA,
        [LANGUAGE_ENGLISH  - 1] = 0x1B4,
        [LANGUAGE_FRENCH   - 1] = 0x1B7,
        [LANGUAGE_ITALIAN  - 1] = 0x1B4,
        [LANGUAGE_GERMAN   - 1] = 0x1B6,
        [6 - 1]                 = 0xEA,
        [LANGUAGE_SPANISH  - 1] = 0x1B4,
        [LANGUAGE_KOREAN   - 1] = 0xEA,
    },
    {
        [LANGUAGE_JAPANESE - 1] = 0xEB,
        [LANGUAGE_ENGLISH  - 1] = 0x1B5,
        [LANGUAGE_FRENCH   - 1] = 0x1B8,
        [LANGUAGE_ITALIAN  - 1] = 0x1B5,
        [LANGUAGE_GERMAN   - 1] = 0x1B4,
        [6 - 1]                 = 0xEB,
        [LANGUAGE_SPANISH  - 1] = 0x1B5,
        [LANGUAGE_KOREAN   - 1] = 0xEB,
    },
};
