
for %%d in (D P Pt HG SS) do (
    if exist .temp\%%d ( rd /s /q .temp\%%d)
    tools\tinke\Tinke.exe extract -f rom\%%d.nds -o .\.temp\%%d
)
