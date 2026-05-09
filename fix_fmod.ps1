$fmod = "C:\Users\Administrator\devlib\Inc\fomdex\fmod.h"
$content = Get-Content $fmod -Raw
$content = $content -replace '#include "fmod_codec.h"', '//#include "fmod_codec.h"'
Set-Content $fmod $content -Encoding Default
Write-Host "Fixed fmod_codec.h"
