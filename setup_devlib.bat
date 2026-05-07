@echo off
REM ============================================================
REM  setup_devlib.bat - 下载并组织 BackMIR 客户端第三方库
REM  用法: setup_devlib.bat [目标目录]
REM  默认目标: %USERPROFILE%\devlib
REM ============================================================

setlocal enabledelayedexpansion

if "%~1"=="" (
    set "DEVLIB_DIR=%USERPROFILE%\devlib"
) else (
    set "DEVLIB_DIR=%~1"
)

echo ============================================================
echo  BackMIR Client - 第三方库下载脚本
echo  目标目录: %DEVLIB_DIR%
echo ============================================================
echo.

REM 创建目录结构
mkdir "%DEVLIB_DIR%" 2>nul
mkdir "%DEVLIB_DIR%\Inc" 2>nul
mkdir "%DEVLIB_DIR%\Inc\hge" 2>nul
mkdir "%DEVLIB_DIR%\Inc\DX8.1" 2>nul
mkdir "%DEVLIB_DIR%\Inc\DuiLib" 2>nul
mkdir "%DEVLIB_DIR%\Inc\fomdex" 2>nul
mkdir "%DEVLIB_DIR%\Inc\Sqlite" 2>nul
mkdir "%DEVLIB_DIR%\Inc\Zlib" 2>nul
mkdir "%DEVLIB_DIR%\Inc\ZipArchive" 2>nul
mkdir "%DEVLIB_DIR%\Inc\protobuf" 2>nul
mkdir "%DEVLIB_DIR%\Inc\curl" 2>nul
mkdir "%DEVLIB_DIR%\Inc\luajit" 2>nul
mkdir "%DEVLIB_DIR%\Inc\fastdelegate" 2>nul
mkdir "%DEVLIB_DIR%\Inc\tolua++" 2>nul
mkdir "%DEVLIB_DIR%\Incvc12\DuiLib" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\luajit" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\DX8.1" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\hge" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\duilib" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\fmodex" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\sqlite3" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\ziparchive" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\zlib" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\protobuf" 2>nul
mkdir "%DEVLIB_DIR%\Libvc12\curl" 2>nul
mkdir "%DEVLIB_DIR%\tmp" 2>nul

echo [1/8] 下载 SQLite3...
curl -L -o "%DEVLIB_DIR%\tmp\sqlite3.zip" "https://www.sqlite.org/2024/sqlite-dll-win32-x86-3450100.zip" 2>nul
curl -L -o "%DEVLIB_DIR%\tmp\sqlite3.h" "https://www.sqlite.org/2024/sqlite-amalgamation-3450100.zip" 2>nul
echo     需要手动解压 sqlite3.h 到 %DEVLIB_DIR%\Inc\Sqlite\
echo     和 sqlite3.lib 到 %DEVLIB_DIR%\Libvc12\sqlite3\

echo.
echo [2/8] 下载 zlib 1.3.1...
curl -L -o "%DEVLIB_DIR%\tmp\zlib131.zip" "https://zlib.net/zlib131.zip" 2>nul
echo     解压后将 zlib.h, zconf.h 拷贝到 %DEVLIB_DIR%\Inc\Zlib\
echo     编译 zlibwapi.dll/lib 拷贝到 %DEVLIB_DIR%\Libvc12\zlib\

echo.
echo [3/8] 下载 LuaJIT 2.1...
curl -L -o "%DEVLIB_DIR%\tmp\luajit.zip" "https://github.com/LuaJIT/LuaJIT/archive/refs/heads/v2.1.zip" 2>nul
echo     解压后用 VS2013 编译:
echo       cd LuaJIT-2.1\src
echo       msvcbuild.bat
echo     将 lua51.lib 拷贝到 %DEVLIB_DIR%\Libvc12\luajit\
echo     将 lua.h, luaconf.h, lualib.h, lauxlib.h, luajit.h 拷贝到 %DEVLIB_DIR%\Inc\luajit\

echo.
echo [4/8] 下载 libcurl (预编译)...
curl -L -o "%DEVLIB_DIR%\tmp\curl.zip" "https://curl.se/windows/dl-8.6.0/curl-8.6.0-win32-mingw.zip" 2>nul
echo     解压后将 include\curl\*.h 拷贝到 %DEVLIB_DIR%\Inc\curl\
echo     将 lib\libcurl.lib 拷贝到 %DEVLIB_DIR%\Libvc12\curl\

echo.
echo [5/8] 下载 Protobuf (预编译)...
echo     需要从 https://github.com/protocolbuffers/protobuf/releases 下载
echo     protobuf-cpp-X.Y.Z.zip, 用 VS2013 编译

echo.
echo [6/8] 下载 FMOD Ex...
echo     从 https://www.fmod.com/download 下载 FMOD Ex API
echo     将 fmod.h, fmod.hpp 拷贝到 %DEVLIB_DIR%\Inc\fomdex\
echo     将 fmodex.lib 拷贝到 %DEVLIB_DIR%\Libvc12\fmodex\
echo     将 fmodex.dll 放到 exe 同目录

echo.
echo [7/8] 下载 DuiLib...
git clone https://github.com/nicenightcc/DuiLib.git "%DEVLIB_DIR%\tmp\DuiLib" 2>nul
if exist "%DEVLIB_DIR%\tmp\DuiLib" (
    xcopy /E /Y "%DEVLIB_DIR%\tmp\DuiLib\DuiLib\*.*" "%DEVLIB_DIR%\Inc\DuiLib\" >nul
    echo     DuiLib 头文件已拷贝
) else (
    echo     从 https://github.com/nicenightcc/DuiLib 下载
)

echo.
echo [8/8] 下载 HGE...
echo     HGE (Haaf's Game Engine) 已停止维护
echo     从 https://github.com/nicenightcc/hge 或 https://hge.relishgames.com/ 下载
echo     将 hge.h, hgeparticle.h 等拷贝到 %DEVLIB_DIR%\Inc\hge\
echo     将 mhge.lib, mhgehelp.lib 拷贝到 %DEVLIB_DIR%\Libvc12\hge\

echo.
echo ============================================================
echo  下载完成！请手动完成以下步骤:
echo ============================================================
echo.
echo  1. 设置环境变量:
echo     set DEVLIB_DIR=%DEVLIB_DIR%
echo.
echo  2. 下载并编译以下库 (需要 VS2013):
echo     - HGE: https://github.com/nicenightcc/hge
echo     - DuiLib: https://github.com/nicenightcc/DuiLib
echo     - LuaJIT: https://github.com/LuaJIT/LuaJIT
echo     - Protobuf: https://github.com/protocolbuffers/protobuf
echo     - ZipArchive: https://github.com/nicenightcc/ZipArchive
echo     - FastDelegate: https://github.com/nicenightcc/FastDelegate
echo.
echo  3. 预编译库可从以下地址获取:
echo     - SQLite3: https://www.sqlite.org/download.html
echo     - zlib: https://zlib.net/
echo     - libcurl: https://curl.se/windows/
echo     - FMOD: https://www.fmod.com/
echo     - DirectX 8.1 SDK: Microsoft 官方存档
echo.
echo  4. 打开 BMClient\BackMir13.sln 编译
echo ============================================================

endlocal
