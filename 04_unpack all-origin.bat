
for %%d in (D P Pt HG SS) do (
    if exist .temp\origin\%%d ( rd /s /q .temp\origin\%%d)
    tools\tinke\Tinke.exe extract -f rom\origin\%%d.nds -o .\.temp\origin\%%d
)
