
 cd /d %~dp0
::����xdelta����
 set releaseversion=v2.0.1
::ʹ�÷�����xdelta3 -v -e -s [ԭʼrom�ļ�] [��rom�ļ�] [�����ļ�]
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\rom\new\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds" ^
    ".\release\%releaseversion%\������3��4��������������_��ʯ_v2.0.0a.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\rom\new\Pokemon_P_chs_2.0.0a_yyjoy_xzonn_re.nds" ^
    ".\release\%releaseversion%\������3��4��������������_����_v2.0.0a.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds" ^
    ".\rom\new\Pokemon_Pt_chs_2.0.0_acg_xzonn_re.nds" ^
    ".\release\%releaseversion%\������3��4��������������_�׽�_v2.0.0.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds" ^
    ".\rom\new\Pokemon_HG_chs_2.0.0_acg_xzonn_re.nds" ^
    ".\release\%releaseversion%\������3��4��������������_�Ľ�_v2.0.0.xdelta"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -e -f -s ^
    ".\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds" ^
    ".\rom\new\Pokemon_SS_chs_2.0.0_acg_xzonn_re.nds" ^
    ".\release\%releaseversion%\������3��4��������������_����_v2.0.0.xdelta"

::����hashֵ
if not exist ".\release\%releaseversion%\������_��ʯ_yyjoy&xzonn_2.0.0a.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\������_��ʯ_yyjoy&xzonn_2.0.0a.hash.txt")
if not exist ".\release\%releaseversion%\������_����_yyjoy&xzonn_2.0.0a.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\������_����_yyjoy&xzonn_2.0.0a.hash.txt")
if not exist ".\release\%releaseversion%\������_�׽�_acg&xzonn_2.0.0.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\������_�׽�_acg&xzonn_2.0.0.hash.txt")
if not exist ".\release\%releaseversion%\������_�Ľ�_acg&xzonn_2.0.0.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\������_�Ľ�_acg&xzonn_2.0.0.hash.txt")
if not exist ".\release\%releaseversion%\������_����_acg&xzonn_2.0.0.hash.txt" ( 
    ".\tools\wokann\hashCal\hashCal.exe" ".\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\������_����_acg&xzonn_2.0.0.hash.txt")

".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds" ".\release\%releaseversion%\������_��ʯ_������У��ֵ.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_P_chs_2.0.0a_yyjoy_xzonn_re.nds" ".\release\%releaseversion%\������_����_������У��ֵ.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_Pt_chs_2.0.0_acg_xzonn_re.nds" ".\release\%releaseversion%\������_�׽�_������У��ֵ.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_HG_chs_2.0.0_acg_xzonn_re.nds" ".\release\%releaseversion%\������_�Ľ�_������У��ֵ.hash.txt"
".\tools\wokann\hashCal\hashCal.exe" ".\rom\new\Pokemon_SS_chs_2.0.0_acg_xzonn_re.nds" ".\release\%releaseversion%\������_����_������У��ֵ.hash.txt"

::tools�ļ����ڻ�������һ��ͼ�λ�gui����Ĳ�������deltapatcher���ɹ��ֶ��������������
::
::3����Զ��رձ�����
@echo off
ping 127.0.0.1 -n 3 >nul