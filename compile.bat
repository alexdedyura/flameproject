@echo off
color 2
set scriptversion=v3.0
Title Pawn Compiler %scriptversion% by DeepFlame

echo.
echo	Pawn Compiler %scriptversion% by DeepFlame
echo.

set name=flame
qawno\pawncc.exe -;+ -(+ -i../compiler/includes sources\%name%.pwn
if exist %name%.amx ^
move %name%.amx gamemodes\
pause