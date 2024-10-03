#include "nds/ndstypes.h"

#define LANGUAGE_JAPANESE 1
#define LANGUAGE_ENGLISH 2
#define LANGUAGE_FRENCH 3
#define LANGUAGE_ITALIAN 4
#define LANGUAGE_GERMAN 5
#define LANGUAGE_SPANISH 7
#define LANGUAGE_KOREAN 8

#define EOS 0xFFFF

extern u16 conversion_table[][2];

static inline u16 GetOpeningQuote(u32 language)
{
    switch (language)
    {
    default:
        return 0xEA;
    case LANGUAGE_ENGLISH:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_SPANISH:
        return 0x1B4;
    case LANGUAGE_FRENCH:
        return 0x1B7;
    case LANGUAGE_GERMAN:
        return 0x1B6;
    }
}

static inline u16 GetClosingQuote(u32 language)
{
    switch (language)
    {
    default:
        return 0xEB;
    case LANGUAGE_ENGLISH:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_SPANISH:
        return 0x1B5;
    case LANGUAGE_FRENCH:
        return 0x1B8;
    case LANGUAGE_GERMAN:
        return 0x1B4;
    }
}

bool ConvertRSStringToDPStringInternational(const u8 *rs_str, u16 *dp_str, u32 length, u32 language)
{
    bool notFullWidth;
    u32 i;

    u16 *dp_str_orig = dp_str;

    notFullWidth = (language != LANGUAGE_JAPANESE);
    for (i = 0; i < length - 1; i++)
    {
        if (rs_str[i] == 0xFF) // RS: EOS
            break;
        if (rs_str[i] >= 0xF7) // RS: DYNAMIC
        {
            // If we're here, the provided name is corrupt.
            // Fill it with question marks.
            s32 r3 = (s32)((length - 1) < 10 ? (length - 1) : 10);
            s32 r1;
            for (r1 = 0; r1 < r3; r1++)
            {
                *dp_str_orig++ = 0x1AC; // DP: ?
            }
            *dp_str_orig++ = EOS;
            return FALSE;
        }
        if (language != LANGUAGE_JAPANESE && rs_str[i] >= 0x01 && rs_str[i] <= 0x1E && rs_str[i] != 0x06 && rs_str[i] != 0x1B)
        {
            u8 hi = rs_str[i++];
            if (hi > 0x6)
            {
                hi--;
            }
            if (hi > 0x1A)
            {
                hi--;
            }
            hi--;
            u8 lo = rs_str[i];
            u16 dpChar = hi * 0xF7 + lo;
            if (dpChar >= 3754)
            {
                dpChar += 5;
            }
            dpChar += 0x201;
            *dp_str++ = dpChar;
        }
        else
        {
            switch (conversion_table[rs_str[i]][notFullWidth])
            {
            case 0xEA: // RS: Opening double quote
                *dp_str++ = GetOpeningQuote(language);
                break;
            case 0xEB: // RS: Closing double quote
                *dp_str++ = GetClosingQuote(language);
                break;
            default:
                *dp_str++ = conversion_table[rs_str[i]][notFullWidth];
                break;
            }
        }
    }
    *dp_str++ = EOS;
    return TRUE;
}
