$msbuild = "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe"
$sln = "Y:\develop\github\backmir\BMClient\BackMir13.sln"
$log = "Y:\develop\github\backmir\_b12.log"

& $msbuild $sln /t:BackMirClient /p:Configuration=Release /p:Platform=Win32 /verbosity:minimal /nologo "/flp:logfile=$log;errorsonly;verbosity=normal"
Write-Output "exit: $LASTEXITCODE"

if (Test-Path $log) {
    Write-Output "`n--- 错误日志 ---"
    Get-Content $log
}
