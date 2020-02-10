# SFML-VSCode
**is::Engine** for [Visual Studio Code](https://code.visualstudio.com/). This project was created with the template of **andrew-r-king**. For more information on this template [click here](https://github.com/andrew-r-king/sfml-vscode-boilerplate)

---

## Prerequisites

### Windows
* [SFML 2.5.1 - GCC 7.3.0 MinGW (DW2) 32-bit](https://www.sfml-dev.org/files/SFML-windows-gcc-7.3.0-mingw-32-bit.zip)
* [GCC 7.3.0 MinGW (DW2) 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)
* [Git Bash](https://git-scm.com/downloads)

### Linux
* Get SFML 2.5.1 from your distro if it has it, or compile from source

---

## Installation

### Windows

1. Download & Extract SFML 2.5.1 to **C:/SFML/** where the bin/lib/include folders are contained within
2. Download & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within

### Linux
1. Ensure the GCC Toolchain is installed (**sudo apt install build-essential**)
2. Run **sudo apt install libsfml-dev**. The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.