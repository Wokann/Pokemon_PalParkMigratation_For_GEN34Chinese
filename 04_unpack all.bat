
for %%d in (D P Pt HG SS) do (
    if exist .temp\%%d ( rd /s /q .temp\%%d)
)

 .\tools\tinke\Tinke.exe extract -f .\rom\Pokemon_D_chs_2.0.0a_yyjoy_xzonn.nds -o .\.temp\D
 .\tools\tinke\Tinke.exe extract -f .\rom\Pokemon_P_chs_2.0.0a_yyjoy_xzonn.nds -o .\.temp\P
 .\tools\tinke\Tinke.exe extract -f .\rom\Pokemon_Pt_chs_2.0.0_acg_xzonn.nds -o .\.temp\Pt
 .\tools\tinke\Tinke.exe extract -f .\rom\Pokemon_HG_chs_2.0.0_acg_xzonn.nds -o .\.temp\HG
 .\tools\tinke\Tinke.exe extract -f .\rom\Pokemon_SS_chs_2.0.0_acg_xzonn.nds -o .\.temp\SS