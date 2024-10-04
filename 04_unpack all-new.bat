
for %%d in (D P Pt HG SS) do (
    if exist .temp\new\%%d ( rd /s /q .temp\new\%%d)
    tools\tinke\Tinke.exe extract -f rom\new\%%d_re.nds -o .\.temp\new\%%d
)
