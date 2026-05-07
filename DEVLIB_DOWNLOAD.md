# BackMIR 客户端第三方库下载指南

## 一键下载脚本

在 Windows 上运行 `setup_devlib.bat`，或按以下步骤手动下载。

## 各库下载地址

### 1. SQLite3 (必须)
```
下载: https://www.sqlite.org/download.html
文件: sqlite-dll-win32-x86-*.zip (DLL) + sqlite-amalgamation-*.zip (源码)
拷贝:
  sqlite3.h      → %DEVLIB_DIR%\Inc\Sqlite\
  sqlite3.lib    → %DEVLIB_DIR%\Libvc12\sqlite3\
  sqlite3.dll    → exe 同目录
```

### 2. zlib (必须)
```
下载: https://zlib.net/
文件: zlib131.zip
编译: 用 VS2013 打开 contrib\vstudio\vc12\zlibvc.sln 编译
拷贝:
  zlib.h, zconf.h → %DEVLIB_DIR%\Inc\Zlib\
  zlibwapi.lib    → %DEVLIB_DIR%\Libvc12\zlib\
  zlibwapi.dll    → exe 同目录
```

### 3. LuaJIT (必须)
```
下载: https://github.com/LuaJIT/LuaJIT/archive/refs/heads/v2.1.zip
编译:
  打开 VS2013 x86 Native Tools Command Prompt
  cd LuaJIT-2.1\src
  msvcbuild.bat
拷贝:
  lua.h, luaconf.h, lualib.h, lauxlib.h, luajit.h → %DEVLIB_DIR%\Inc\luajit\
  lua51.lib       → %DEVLIB_DIR%\Libvc12\luajit\
  lua51.dll       → exe 同目录
```

### 4. tolua++ (必须)
```
下载: https://github.com/nicenightcc/tolua_ink 或搜索 tolua++ Windows 编译
编译: 用 VS2013 编译为静态库
拷贝:
  tolua++.h       → %DEVLIB_DIR%\Inc\tolua++\
  libtolua.lib    → %DEVLIB_DIR%\Libvc12\luajit\ (与 lua51.lib 同目录)
```

### 5. libcurl (必须)
```
下载: https://curl.se/windows/
文件: curl-8.6.0-win32-mingw.zip 或 curl-8.6.0-win64-mingw.zip
注意: 需要 VS2013 编译的版本，mingw 版本可能不兼容
替代: 用 vcpkg 安装: vcpkg install curl:x86-windows
拷贝:
  curl\*.h        → %DEVLIB_DIR%\Inc\curl\
  libcurl.lib     → %DEVLIB_DIR%\Libvc12\curl\
  libcurl.dll     → exe 同目录
```

### 6. Protobuf (必须)
```
下载: https://github.com/protocolbuffers/protobuf/releases
文件: protobuf-cpp-3.21.12.zip (或更早版本，新版用 cmake)
编译: 用 VS2013 打开 vsprojects\protobuf.sln 编译
拷贝:
  google\protobuf\*.h → %DEVLIB_DIR%\Inc\protobuf\google\protobuf\
  libprotobuf.lib     → %DEVLIB_DIR%\Libvc12\protobuf\
```

### 7. DuiLib (必须)
```
下载: https://github.com/nicenightcc/DuiLib
      或 https://github.com/nicenightcc/duilib
编译: 用 VS2013 编译 DuiLib_Static 项目
拷贝:
  UIlib.h 等      → %DEVLIB_DIR%\Inc\DuiLib\  和  %DEVLIB_DIR%\Incvc12\DuiLib\
  duilib.lib      → %DEVLIB_DIR%\Libvc12\duilib\
```

### 8. HGE - Haaf's Game Engine (必须)
```
下载: https://github.com/nicenightcc/hge
      或 https://hge.relishgames.com/downloads.html
      或搜索 "HGE 1.81" 下载
编译: 用 VS2013 编译 (需要 DirectX 8.1 SDK)
拷贝:
  hge.h, hgeparticle.h 等 → %DEVLIB_DIR%\Inc\hge\
  mhge.lib, mhgehelp.lib  → %DEVLIB_DIR%\Libvc12\hge\
  mhge.dll, mhgehelp.dll  → exe 同目录
```

### 9. DirectX 8.1 SDK (必须)
```
下载: Microsoft 官方已归档
      搜索 "DirectX 8.1 SDK download" 或 "dx81_sdk.exe"
      https://www.microsoft.com/en-us/download/details.aspx?id=6812
安装后拷贝:
  d3d8.h, d3d8types.h, d3dx8.h, d3dx8math.h 等 → %DEVLIB_DIR%\Inc\DX8.1\
  d3d8.lib, d3dx8.lib                           → %DEVLIB_DIR%\Libvc12\DX8.1\
  d3d8.dll, d3dx8d.dll (或 d3dx8.dll)           → exe 同目录 (或系统目录)
```

### 10. FMOD Ex (必须)
```
下载: https://www.fmod.com/download (需要注册)
      或搜索 "fmodapi44431win32" (FMOD Ex 4.44.31)
拷贝:
  fmod.h, fmod.hpp → %DEVLIB_DIR%\Inc\fomdex\  (注意: 目录名是 fomdex 不是 fmodex)
  fmodex_vc.lib    → %DEVLIB_DIR%\Libvc12\fmodex\ (重命名为 fmodex.lib)
  fmodex.dll       → exe 同目录
```

### 11. FastDelegate (必须, 头文件库)
```
下载: https://github.com/nicenightcc/FastDelegate
      或搜索 "FastDelegate C++ download"
拷贝:
  FastDelegate.h   → %DEVLIB_DIR%\Inc\fastdelegate\
```

### 12. ZipArchive (必须)
```
下载: https://github.com/nicenightcc/ZipArchive
      或 https://www.artpol-software.com/ZipArchive
编译: 用 VS2013 编译静态库版本
拷贝:
  ZipArchive.h 等  → %DEVLIB_DIR%\Inc\ZipArchive\
  ZipArchive.lib   → %DEVLIB_DIR%\Libvc12\ziparchive\
```

## 运行时 DLL 清单

编译完成后，以下 DLL 需要放在 `BackMir.exe` 同目录：

```
BackMir.exe
fmodex.dll          # FMOD 音频
lua51.dll           # LuaJIT
sqlite3.dll         # SQLite3
zlibwapi.dll        # zlib
libcurl.dll         # libcurl (如果是动态链接)
d3d8.dll            # DirectX 8 (通常系统自带)
d3dx8d.dll          # DirectX 8 扩展 (Debug)
conf\               # 客户端配置目录 (自动创建)
Save\               # 存档目录 (自动创建)
UI\                 # UI XML 文件 (Release 模式)
```

## 快速方案 (使用 vcpkg)

如果你有 vcpkg，可以快速安装部分库：

```cmd
vcpkg install sqlite3:x86-windows
vcpkg install zlib:x86-windows
vcpkg install curl:x86-windows
vcpkg install protobuf:x86-windows
vcpkg install luajit:x86-windows
```

然后将 vcpkg 安装的文件拷贝到 `%DEVLIB_DIR%` 对应目录。
