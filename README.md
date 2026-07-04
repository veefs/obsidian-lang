# Obsidian Lang

**Toy programming language written in c++ and windows assembly aimed as a learning experience for myself to more understand how coding languages truly work** 

## What is Obsidian Lang?

- Obsidian Lang is a toy programming language written in c++ and windows assembly. The goal of this project for me was to better understand tokenizing, parsing, assembly, etc basically the list goes on of how much knowledge you can gain my doing a project like this.

### Important! Obsidian is currently in early development

- Obsidian Lang is currently in **very very very** early development so please not any bugs / issues **WILL** be fixed, but you just have to give it time because this is a somewhat more complicated project

## If you are from stardance

- Hello everyone from stardance, I just want to note that sadly this currently only works on windows, I'll eventually attempt to port this to linux with their assembly, but because im currently using **Windows direct api assembly** that just currently isn't realistic, sorry that you guys couldn't try it out ):

# How to install



- Please locate toward the most recent `releases` tab, there will be instructions on how exactly to run everything


## Dependcies

- You need to have CMAKE, G++, etc (your selected c++ / c compiler) as well as NASM x64 Direct Api assembly installed, please find a guide on line but note this is **requried** for the linker to actually work

### Installing NASM (windows)

- **Options one: use winget (reccomend + easiest)** 

```powershell
winget install NASM.NASM
```

- **Option 2: Manual installer**

1. Go to https://www.nasm.us/pub/nasm/releasebuilds/
2. Pick the latest stable release folder (avoid `rc` release-candidate builds unless you know you need them)
3. Download `nasm-<version>-installer-x64.exe`
4. Run the installer — it will add NASM to your `PATH` automatically
5. Verify it worked by opening a new terminal and running:
```powershell
   nasm -v
```
   You should see something like `NASM version 3.xx.xx`

- **Option 3: Chocolatey**
```powershell
choco install nasm
```

### Installing G++ (MinGW-w64)

**Option 1: Winget**
```powershell
winget install -e --id MSYS2.MSYS2
```
Then inside the MSYS2 shell:
```bash
pacman -S mingw-w64-x86_64-gcc
```
Add `C:\msys64\mingw64\bin` to your `PATH`.

**Option 2: MSYS2 manual install**
Download from https://www.msys2.org/, follow their setup instructions, then install the toolchain the same way as above.

### Installing CMake

**Option 1: Winget**
```powershell
winget install Kitware.CMake
```

**Option 2: Manual installer**
Download from https://cmake.org/download/ and make sure to check "Add CMake to system PATH" during install.

### Verifying everything is set up

Open a fresh terminal (so `PATH` changes apply) and run:
```powershell
nasm -v
g++ --version
cmake --version
```
