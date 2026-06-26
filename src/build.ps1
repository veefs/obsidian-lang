# build.ps1
$ErrorActionPreference = "Stop"

g++ -std=c++17 main.cpp Tokenize.cpp interpret.cpp compiler.cpp -o obsidian.exe
if ($LASTEXITCODE -ne 0) { Write-Host "g++ build failed" -ForegroundColor Red; exit 1 }

.\obsidian.exe example.obs
if ($LASTEXITCODE -ne 0) { Write-Host "obsidian.exe failed" -ForegroundColor Red; exit 1 }

if (-not (Test-Path .\example.exe)) {
    Write-Host "example.exe was not produced - nasm/gcc step failed, check output above" -ForegroundColor Red
    exit 1
}

Write-Host "`n--- running example.exe ---" -ForegroundColor Cyan
.\example.exe
Write-Host "exit code: $LASTEXITCODE" -ForegroundColor Cyan
