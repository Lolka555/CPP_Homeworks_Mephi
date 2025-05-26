@echo off
setlocal enabledelayedexpansion

set includes=0

rem Loop through each line in task.cpp
for /f "usebackq delims=" %%i in ("task.cpp") do (
    rem Check if the line contains #include and does not contain task.h
    echo %%i | findstr /i "#include" | findstr /v /i "task.h" >nul
    if not errorlevel 1 (
        set /a includes+=1
    )
)

rem Check if includes is 0
if !includes! equ 0 (
    echo All includes are valid.
) else (
    echo Found !includes! invalid includes in task.cpp.
    exit /b 1
)

endlocal
