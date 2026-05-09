$devlib = "C:\Users\Administrator\devlib"
Write-Host "=== Check devlib ===" -ForegroundColor Cyan

$checks = @(
    "Inc\luajit\lua.h|LuaJIT header",
    "Inc\Sqlite\sqlite3.h|SQLite3 header",
    "Inc\Zlib\zlib.h|zlib header",
    "Inc\curl\curl.h|libcurl header",
    "Inc\DuiLib\UIlib.h|DuiLib header",
    "Inc\hge\hge.h|HGE header",
    "Inc\DX8.1\d3d8.h|DX8.1 header",
    "Inc\fomdex\fmod.h|FMOD header",
    "Inc\ZipArchive\ZipArchive.h|ZipArchive header",
    "Inc\fastdelegate\FastDelegate.h|FastDelegate header",
    "Inc\tolua++\tolua++.h|tolua++ header",
    "Libvc12\luajit\lua51.lib|LuaJIT lib",
    "Libvc12\DX8.1\d3d8.lib|DX8.1 lib",
    "Libvc12\DX8.1\d3dx8.lib|DX8.1 ext lib",
    "Libvc12\hge\mhge.lib|HGE lib",
    "Libvc12\hge\mhgehelp.lib|HGE helper lib",
    "Libvc12\duilib\duilib.lib|DuiLib lib",
    "Libvc12\fmodex\fmodex.lib|FMOD lib",
    "Libvc12\sqlite3\sqlite3.lib|SQLite3 lib",
    "Libvc12\ziparchive\ZipArchive.lib|ZipArchive lib",
    "Libvc12\zlib\zlibwapi.lib|zlib lib",
    "Libvc12\protobuf\libprotobuf.lib|Protobuf lib",
    "Libvc12\curl\libcurl.lib|libcurl lib"
)

$ok = 0
$missing = 0
foreach ($item in $checks) {
    $parts = $item -split "\|"
    $path = $parts[0]
    $name = $parts[1]
    $full = Join-Path $devlib $path
    if (Test-Path $full) {
        Write-Host "  [OK] $name" -ForegroundColor Green
        $ok++
    } else {
        Write-Host "  [!!] $name - MISSING" -ForegroundColor Red
        $missing++
    }
}
Write-Host ""
Write-Host "Result: $ok OK, $missing missing" -ForegroundColor Yellow
