@echo off
REM Path to neat_code_gen.exe
set NEATGEN=D:\up2196013\MangoMilk\include\NeatReflection\tools\NeatReflectionCodeGen.exe

REM Path to IFC files (adjust to your build folder)
set IFC_DIR=D:\up2196013\MangoMilk\MangoMilk\x64\Debug

REM Output folder for generated reflection cpp files
set OUT_DIR=D:\up2196013\MangoMilk\Generated

REM Make sure output folder exists
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

REM Loop over all .ifc files and generate reflection
for %%F in ("%IFC_DIR%\*.ifc") do (
    echo Processing %%~nxF
    "%NEATGEN%" "%%F" "%OUT_DIR%\%%~nF_Reflection.cpp"
)

echo All reflection files generated!
pause