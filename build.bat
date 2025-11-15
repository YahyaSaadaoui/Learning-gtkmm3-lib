@echo off
REM Cross-platform build setup script for GTKmm Domino Application (Windows)
REM Run this from MSYS2 MinGW terminal

echo GTKmm Domino Application - Setup
echo ==================================
echo.

echo Checking for MSYS2...
where bash >nul 2>nul
if errorlevel 1 (
    echo ERROR: MSYS2 not found. Install from https://www.msys2.org/
    echo This script must be run from MSYS2 MinGW terminal, not CMD.exe
    exit /b 1
)

echo Installing dependencies with pacman...
pacman -S --noconfirm mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtkmm3 make
if errorlevel 1 (
    echo ERROR: Dependency installation failed
    exit /b 1
)

echo Building with: make -f Makefile.windows
make -f Makefile.windows
if errorlevel 1 (
    echo ERROR: Build failed
    exit /b 1
)

echo.
echo Build complete!
echo Run:
echo   demo1.exe   - for basic drawing demo
echo   demo2.exe   - for interactive domino demo
