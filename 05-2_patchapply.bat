
 cd /d %~dp0
::Ӧ��xdelta����
 set releaseversion=v2.0.1
::ʹ�÷�����xdelta3 -v -d -s [ԭʼrom�ļ�] [�����ļ�] [��rom�ļ�] 
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\������3��4��������������_��ʯ_v2.0.0a.xdelta" ^
    ".\rom\new\Pokemon_D_chs_2.0.0a_yyjoy_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds" ^
    ".\release\%releaseversion%\������3��4��������������_����_v2.0.0a.xdelta" ^
    ".\rom\new\Pokemon_P_chs_2.0.0a_yyjoy_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\������3��4��������������_�׽�_v2.0.0.xdelta" ^
    ".\rom\new\Pokemon_Pt_chs_2.0.0_acg_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\������3��4��������������_�Ľ�_v2.0.0.xdelta" ^
    ".\rom\new\Pokemon_HG_chs_2.0.0_acg_xzonn_re.nds"
 ".\tools\xdelta3\xdelta3-3.1.0-i686.exe" -v -d -f -s ^
    ".\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds" ^
    ".\release\%releaseversion%\������3��4��������������_����_v2.0.0.xdelta" ^
    ".\rom\new\Pokemon_SS_chs_2.0.0_acg_xzonn_re.nds"

::tools�ļ����ڻ�������һ��ͼ�λ�gui����Ĳ�������deltapatcher���ɹ��ֶ������Ӧ�ò���
::
::3����Զ��رձ�����
@echo off
ping 127.0.0.1 -n 3 >nul