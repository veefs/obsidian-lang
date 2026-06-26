# build.ps1
$ErrorActionPreference = "Stop"

g++ -std=c++17 main.cpp Tokenize.cpp Interpret.cpp Compiler.cpp -o obsidian.exe
if ($LASTEXITCODE -ne 0) { Write-Host "g++ build failed" -ForegroundColor Red; exit 1 }

.\obsidian.exe example.obs
if ($LASTEXITCODE -ne 0) { Write-Host "obsidian.exe failed" -ForegroundColor Red; exit 1 }

