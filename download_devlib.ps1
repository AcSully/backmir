$devlib = "$env:USERPROFILE\devlib"
$tmp = "$devlib\tmp"

Write-Host "BackMIR - 下载第三方库" -ForegroundColor Cyan
Write-Host "目标: $devlib" -ForegroundColor Cyan

$dirs = @(
    "Inc\luajit", "Inc\Sqlite", "Inc\Zlib", "Inc\curl", "Inc\fastdelegate",
    "Inc\hge", "Inc\DX8.1", "Inc\DuiLib", "Inc\fomdex", "Inc\ZipArchive",
    "Inc\protobuf", "Inc\tolua++", "Incvc12\DuiLib",
    "Libvc12\luajit", "Libvc12\DX8.1", "Libvc12\hge", "Libvc12\duilib",
    "Libvc12\fmodex", "Libvc12\sqlite3", "Libvc12\ziparchive",
    "Libvc12\zlib", "Libvc12\protobuf", "Libvc12\curl", "tmp"
)
foreach ($d in $dirs) {
    New-Item -ItemType Directory -Path "$devlib\$d" -Force | Out-Null
}

# 1. SQLite3
Write-Host "`n[1/4] SQLite3..." -ForegroundColor Yellow
Invoke-WebRequest "https://www.sqlite.org/2024/sqlite-amalgamation-3450100.zip" -OutFile "$tmp\sqlite3.zip"
Expand-Archive "$tmp\sqlite3.zip" "$tmp\sqlite3" -Force
Copy-Item "$tmp\sqlite3\sqlite-amalgamation-3450100\sqlite3.h" "$devlib\Inc\Sqlite\" -Force
Write-Host "  OK" -ForegroundColor Green

# 2. LuaJIT
Write-Host "`n[2/4] LuaJIT..." -ForegroundColor Yellow
Invoke-WebRequest "https://github.com/LuaJIT/LuaJIT/archive/refs/heads/v2.1.zip" -OutFile "$tmp\luajit.zip"
Expand-Archive "$tmp\luajit.zip" "$tmp\luajit" -Force
$lj = "$tmp\luajit\LuaJIT-2.1\src"
foreach ($h in @("lua.h","luaconf.h","lualib.h","lauxlib.h","luajit.h")) {
    if (Test-Path "$lj\$h") { Copy-Item "$lj\$h" "$devlib\Inc\luajit\" -Force }
}
Write-Host "  OK" -ForegroundColor Green

# 3. zlib (从 GitHub 下载)
Write-Host "`n[3/4] zlib..." -ForegroundColor Yellow
Invoke-WebRequest "https://github.com/madler/zlib/releases/download/v1.3.1/zlib131.zip" -OutFile "$tmp\zlib.zip"
if (Test-Path "$tmp\zlib.zip") {
    Expand-Archive "$tmp\zlib.zip" "$tmp\zlib" -Force
    $zd = Get-ChildItem "$tmp\zlib" -Directory | Select-Object -First 1
    if (Test-Path "$($zd.FullName)\zlib.h") {
        Copy-Item "$($zd.FullName)\zlib.h" "$devlib\Inc\Zlib\" -Force
        Copy-Item "$($zd.FullName)\zconf.h" "$devlib\Inc\Zlib\" -Force
    }
    Write-Host "  OK" -ForegroundColor Green
} else {
    Write-Host "  失败，请手动下载: https://zlib.net/" -ForegroundColor Red
}

# 4. DuiLib (从 GitHub clone)
Write-Host "`n[4/4] DuiLib..." -ForegroundColor Yellow
if (Get-Command git -ErrorAction SilentlyContinue) {
    git clone --depth 1 https://github.com/duilib/duilib.git "$tmp\DuiLib" 2>$null
    if (Test-Path "$tmp\DuiLib\DuiLib\UIlib.h") {
        Copy-Item "$tmp\DuiLib\DuiLib\*.h" "$devlib\Inc\DuiLib\" -Force
        Copy-Item "$tmp\DuiLib\DuiLib\*.h" "$devlib\Incvc12\DuiLib\" -Force
        Write-Host "  OK" -ForegroundColor Green
    } else {
        Write-Host "  clone 失败" -ForegroundColor Red
    }
} else {
    Write-Host "  需要 git, 请手动下载: https://github.com/nicenightcc/DuiLib" -ForegroundColor Red
}

Write-Host "`n================================================" -ForegroundColor Cyan
Write-Host "已下载: SQLite3, LuaJIT, zlib, DuiLib" -ForegroundColor Green
Write-Host ""
Write-Host "还需要手动下载和编译:" -ForegroundColor Yellow
Write-Host ""
Write-Host "  1. HGE (2D引擎)" -ForegroundColor White
Write-Host "     https://github.com/nicenightcc/hge" -ForegroundColor Gray
Write-Host "     用 VS2013 编译, 拷贝 mhge.lib 到 Libvc12\hge\" -ForegroundColor Gray
Write-Host ""
Write-Host "  2. DirectX 8.1 SDK" -ForegroundColor White
Write-Host "     搜索 dx81_sdk.exe 下载安装" -ForegroundColor Gray
Write-Host "     拷贝 d3d8.lib d3dx8.lib 到 Libvc12\DX8.1\" -ForegroundColor Gray
Write-Host ""
Write-Host "  3. FMOD Ex (音频)" -ForegroundColor White
Write-Host "     https://www.fmod.com/download (需注册)" -ForegroundColor Gray
Write-Host "     拷贝 fmodex.lib 到 Libvc12\fmodex\" -ForegroundColor Gray
Write-Host ""
Write-Host "  4. Protobuf" -ForegroundColor White
Write-Host "     https://github.com/protocolbuffers/protobuf/releases" -ForegroundColor Gray
Write-Host "     用 VS2013 编译, 拷贝 libprotobuf.lib 到 Libvc12\protobuf\" -ForegroundColor Gray
Write-Host ""
Write-Host "  5. libcurl" -ForegroundColor White
Write-Host "     vcpkg install curl:x86-windows" -ForegroundColor Gray
Write-Host "     或 https://curl.se/windows/ 下载 VS 版本" -ForegroundColor Gray
Write-Host ""
Write-Host "  6. ZipArchive" -ForegroundColor White
Write-Host "     https://github.com/nicenightcc/ZipArchive" -ForegroundColor Gray
Write-Host ""
Write-Host "  7. tolua++" -ForegroundColor White
Write-Host "     https://github.com/nicenightcc/tolua_ink" -ForegroundColor Gray
Write-Host ""
Write-Host "  8. FastDelegate (仅头文件)" -ForegroundColor White
Write-Host "     https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible" -ForegroundColor Gray
Write-Host ""
Write-Host "设置环境变量: set DEVLIB_DIR=$devlib" -ForegroundColor Cyan
Write-Host "然后打开 BMClient\BackMir13.sln 编译" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
