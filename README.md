# libcrosswind 0.2

[![Join the chat at https://gitter.im/libcrosswind/libcrosswind](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/libcrosswind/libcrosswind?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
A modern C++14 Multipurpose library

git clone https://github.com/libcrosswind/libcrosswind.git

git submodule init

git submodule update

Requirements:

Windows:

CMake:

Download and install in libcrosswind\platform\windows\support\cmake
http://www.cmake.org/download/

MSYS:

Download and install in libcrosswind\platform\windows\support\msys\1.0
http://downloads.sourceforge.net/mingw/MSYS-1.0.11.exe
Answer "n" when the post install prompts.

TDM-GCC:

Download and install in libcrosswind\platform\windows\compilers\x64\TDM-GCC-64
http://sourceforge.net/projects/tdm-gcc/files/TDM-GCC%20Installer/tdm64-gcc-4.9.2-3.exe

Bash upgrade for MSYS:

Download:

http://sourceforge.net/projects/mingw/files/MSYS/Base/bash/bash-3.1.23-1/bash-3.1.23-1-msys-1.0.18-bin.tar.xz
http://sourceforge.net/projects/mingw/files/MSYS/Base/regex/regex-1.20090805-2/libregex-1.20090805-2-msys-1.0.13-dll-1.tar.lzma
http://sourceforge.net/projects/mingw/files/MSYS/Base/termcap/termcap-0.20050421_1-2/libtermcap-0.20050421_1-2-msys-1.0.13-dll-0.tar.lzma


Extract into libcrosswind\platform\windows\support\msys\1.0 and override the existing files inside bin.

You can use 7-zip for this task.

After installation run libcrosswind\setup\win32\build.bat


Current status: 

- [x] Unstable
- [ ] Stable

Working on the production-ready version, meanwhile you can use the tag 0.2 version.