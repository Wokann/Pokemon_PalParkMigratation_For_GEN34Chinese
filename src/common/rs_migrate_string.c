//C:\devkitPro\devkitARM\bin\arm-none-eabi-gcc.exe -mabi=aapcs -std=c99 -w -nostartfiles -nodefaultlibs -Os -march=armv5te -mtune=arm946e-s -mthumb -Wl,--use-blx -I C:\devkitPro\libnds\include -c src\common\rs_migrate_string.c -o build\rs_migrate_string.o -DGEN4_JP
//注：主程序编译后的bin大小需要满足 ≤ 0xB0 方可在原函数位置上置入。
//以上为能满足此需求的一种编译指令。如您无法保证自行编写的编译指令满足生成大小要求，请继续使用以上指令进行编译。
//-DGEN4_JP用于主程序判断非法字符时填充的问号编码及填充长度。日版汉化使用GEN4_JP即可。
//若韩版开发者用于与3代韩化版联动可使用GEN4_KO替代
//其他语言GEN4_EN GEN4_FR GEN4_IT GEN4_DE GEN4_SP则默认为else

#include "nds/ndstypes.h"

#define LANGUAGE_JAPANESE 1
#define LANGUAGE_ENGLISH 2
#define LANGUAGE_FRENCH 3
#define LANGUAGE_ITALIAN 4
#define LANGUAGE_GERMAN 5
#define LANGUAGE_SPANISH 7
#define LANGUAGE_KOREAN 8

#define EOS 0xFFFF

#ifdef GEN4_JP
    #define QUESTION_MARK 0xE2
    #define ILLEGAL_PADDING_LEN 5
#elif defined(GEN4_KO)
    #define QUESTION_MARK 0x01AC
    #define ILLEGAL_PADDING_LEN 5
#else //GEN4_EN GEN4_FR GEN4_IT GEN4_DE GEN4_SP
    #define QUESTION_MARK 0x01AC
    #define ILLEGAL_PADDING_LEN 10
#endif

extern u16 conversion_table[][2];
extern u16 conversion_table_chinese[0x1E5E];
extern u16 conversion_table_quote[][8];
bool ConvertRSStringToDPStringInternational(const u8 *rs_str, u16 *dp_str, u32 length, u32 language)
{
    bool notFullWidth;
    u32 i;

    notFullWidth = (language != LANGUAGE_JAPANESE);
    for (i = 0; i < length - 1; i++)
    {
        if (rs_str[i] == 0xFF) // RS: EOS
            break;
        if (rs_str[i] >= 0xF7) // RS: DYNAMIC
        {
            // If we're here, the provided name is corrupt.
            // Fill it with question marks.
            s32 r3 = (s32)((length - 1) < ILLEGAL_PADDING_LEN ? (length - 1) : ILLEGAL_PADDING_LEN);
            s32 r1;
            for (r1 = 0; r1 < r3; r1++)
            {
                dp_str[r1] = QUESTION_MARK; // DP: ?
            }
            dp_str[r1] = EOS;
            return FALSE;
        }
        if (language != LANGUAGE_JAPANESE && rs_str[i] >= 0x01 && rs_str[i] <= 0x1E && rs_str[i] != 0x06 && rs_str[i] != 0x1B)
            *dp_str++ = conversion_table_chinese[((rs_str[i++] << 8) + rs_str[i])];
        else if(rs_str[i] == 0xEA || rs_str[i] == 0xEB)
            *dp_str++ = conversion_table_quote[rs_str[i]-0xEA][language];
        else
            *dp_str++ = conversion_table[rs_str[i]][notFullWidth];
    }
    *dp_str++ = EOS;
    return TRUE;
}
