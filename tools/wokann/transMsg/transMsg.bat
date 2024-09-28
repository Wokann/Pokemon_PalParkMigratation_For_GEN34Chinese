:: 此指令用于转码二进制bin文件为明文文本
@echo on
setlocal enabledelayedexpansion
:: 设置指令路径、载入基础数据、返回当前路径
    set "WorkPath=%~dp0"
    cd /d %WorkPath%
:: 返回根目录
    cd ../../../
:: 设置工具及码表文件
    set tool_texttrans_1=.\tools\wokann\transMsg\transMsg.exe
    set charmap_jp=.\charmap_jp.txt
    set charmap_jp_reverse=.\charmap_jp_reverse.txt
    set charmap_jp_reverse_nochar=.\charmap_jp_reverse_nochar.txt
    set charmap_jp_reverse_widthchar=.\charmap_jp_reverse_widthchar.txt
    set charmap_chs=.\charmap_chs.txt
    set charmap_chs_reverse=.\charmap_chs_reverse.txt
    set charmap_chs_reverse_nochar=.\charmap_chs_reverse_nochar.txt

:: 转码文本
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfItemAttr.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfItemName.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfItemHelp.bin -c %charmap_chs% -h 3 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfItemName.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfItemType.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtCalendar.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtCardError.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtItemShop.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtLoadMsg.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtMenuFarm.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtMonsterAbility.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtMonsterKind.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtNameEntry.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtNameEntryDef.bin -c %charmap_chs_reverse_nochar% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtNameEntryInput.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtNPCName.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtSavePointName.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtSchedule.bin -c %charmap_chs% -h 4 -m 4 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal\rfTxtSynthesis.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfEvent\event.bin -c %charmap_chs% -h 2 -m 2 -f 0 -em 0x00


    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfItemAttr.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfItemName.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfItemHelp.bin -c %charmap_jp% -h 3 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfItemName.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfItemType.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtCalendar.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtCardError.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtItemShop.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtLoadMsg.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtMenuFarm.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtMonsterAbility.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtMonsterKind.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtNameEntry.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtNameEntryDef.bin -c %charmap_jp_reverse_nochar% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtNameEntryInput.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtNPCName.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtSavePointName.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtSchedule.bin -c %charmap_jp% -h 4 -m 4 -f 0 -em 0x00
    :: %tool_texttrans_1% -i .\strings\TextOfNormal_jp\rfTxtSynthesis.bin -c %charmap_jp% -h 2 -m 2 -f 0 -em 0x00
    %tool_texttrans_1% -i .\strings\TextOfEvent_jp\event.bin -c %charmap_jp_reverse_widthchar% -h 0 -m 5 -f 0 -em 0x00
endlocal

