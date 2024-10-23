
 cd /d %~dp0
::应用xdelta补丁
 set releaseversion=v2.0.1
::使用方法：xdelta3 -v -d -s [原始rom文件] [补丁文件] [新rom文件] 
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_钻石_v2.0.0a.xdelta" ^
    ".\rom\new\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_珍珠_v2.0.0a.xdelta" ^
    ".\rom\new\Pokemon_P_chs_2.0.0a_yyjoy_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_白金_v2.0.0.xdelta" ^
    ".\rom\new\Pokemon_Pt_chs_2.0.0_acg_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_心金_v2.0.0.xdelta" ^
    ".\rom\new\Pokemon_HG_chs_2.0.0_acg_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\宝可梦3、4代汉化联动补丁_魂银_v2.0.0.xdelta" ^
    ".\rom\new\Pokemon_SS_chs_2.0.0_acg_xzonn_re.nds"

::tools文件夹内还放置了一个图形化gui界面的补丁工具deltapatcher，可供手动鼠标点击应用补丁
::
::3秒后自动关闭本窗口
@echo off
ping 127.0.0.1 -n 3 >nul