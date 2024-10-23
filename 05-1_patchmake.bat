
 cd /d %~dp0
::制作xdelta补丁
 set releaseversion=v2.0.1
::使用方法：xdelta3 -v -e -s [原始rom文件] [新rom文件] [补丁文件]
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\rom\new\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_钻石_v2.0.0a.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\rom\new\Pokemon_P_chs_2.0.0a_yyjoy_xzonn_re.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_珍珠_v2.0.0a.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds" ^
    ".\rom\new\Pokemon_Pt_chs_2.0.0_acg_xzonn_re.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_白金_v2.0.0.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds" ^
    ".\rom\new\Pokemon_HG_chs_2.0.0_acg_xzonn_re.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_心金_v2.0.0.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds" ^
    ".\rom\new\Pokemon_SS_chs_2.0.0_acg_xzonn_re.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_魂银_v2.0.0.xdelta"

::生成hash值
if not exist ".\release\%releaseversion%\宝可梦_钻石_yyjoy&xzonn_2.0.0a.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦_钻石_yyjoy&xzonn_2.0.0a.hash.txt")
if not exist ".\release\%releaseversion%\宝可梦_珍珠_yyjoy&xzonn_2.0.0a.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦_珍珠_yyjoy&xzonn_2.0.0a.hash.txt")
if not exist ".\release\%releaseversion%\宝可梦_白金_acg&xzonn_2.0.0.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦_白金_acg&xzonn_2.0.0.hash.txt")
if not exist ".\release\%releaseversion%\宝可梦_心金_acg&xzonn_2.0.0.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦_心金_acg&xzonn_2.0.0.hash.txt")
if not exist ".\release\%releaseversion%\宝可梦_魂银_acg&xzonn_2.0.0.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦_魂银_acg&xzonn_2.0.0.hash.txt")

".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds" ".\release\%releaseversion%\宝可梦_钻石_补丁后校验值.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_P_chs_2.0.0a_yyjoy_xzonn_re.nds" ".\release\%releaseversion%\宝可梦_珍珠_补丁后校验值.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_Pt_chs_2.0.0_acg_xzonn_re.nds" ".\release\%releaseversion%\宝可梦_白金_补丁后校验值.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_HG_chs_2.0.0_acg_xzonn_re.nds" ".\release\%releaseversion%\宝可梦_心金_补丁后校验值.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_SS_chs_2.0.0_acg_xzonn_re.nds" ".\release\%releaseversion%\宝可梦_魂银_补丁后校验值.hash.txt"

::tools文件夹内还放置了一个图形化gui界面的补丁工具deltapatcher，可供手动鼠标点击制作补丁
::
::3秒后自动关闭本窗口
@echo off
ping 127.0.0.1 -n 3 >nul