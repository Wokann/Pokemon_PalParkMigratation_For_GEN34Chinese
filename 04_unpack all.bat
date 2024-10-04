
for %%d in (D P Pt HG SS) do (
    if exist .temp\chs\%%d ( rd /s /q .temp\chs\%%d)
)

 .\tools\tinke\Tinke.exe extract -f .\rom\chs\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds -o .\.temp\chs\D
 .\tools\tinke\Tinke.exe extract -f .\rom\chs\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds -o .\.temp\chs\P
 .\tools\tinke\Tinke.exe extract -f .\rom\chs\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds -o .\.temp\chs\Pt
 .\tools\tinke\Tinke.exe extract -f .\rom\chs\Pokemon_HG_chs_2.0.0_acg_xzonn.nds -o .\.temp\chs\HG
 .\tools\tinke\Tinke.exe extract -f .\rom\chs\Pokemon_SS_chs_2.0.0_acg_xzonn.nds -o .\.temp\chs\SS