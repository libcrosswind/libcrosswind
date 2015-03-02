Requirements:

General:
CMake
http://www.cmake.org/download/
Download, install and ensure it is added to PATH

Windows:

MSYS (required for building sdl)
http://downloads.sourceforge.net/mingw/MSYS-1.0.11.exe
Download, install and add to PATH
(recommended installation dir is platform/windows/support/msys/1.0)

TDM-GCC
http://sourceforge.net/projects/tdm-gcc/files/TDM-GCC%20Installer/tdm64-gcc-4.9.2-3.exe/download

Download, install and ensure it is added to PATH
(recommended installation dir is platform/windows/compilers/x64/TDM-GCC-64)

Upgrade bash for MSYS

By default we'll this version since it can be integrated safely into MSYS:

http://sourceforge.net/projects/mingw/files/MSYS/Base/bash/bash-3.1.23-1/bash-3.1.23-1-msys-1.0.18-bin.tar.xz/download

The dependencies for upgrading bash are:

http://sourceforge.net/projects/mingw/files/MSYS/Base/regex/regex-1.20090805-2/libregex-1.20090805-2-msys-1.0.13-dll-1.tar.lzma/download
and
http://sourceforge.net/projects/mingw/files/MSYS/Base/termcap/termcap-0.20050421_1-2/libtermcap-0.20050421_1-2-msys-1.0.13-dll-0.tar.lzma/download

You can extract the content from the lzma files with tar --lzma -xvf file.tar.lzma

tar --lzma -xvf libregex-1.20090805-2-msys-1.0.13-dll-1.tar.lzma
tar --lzma -xvf libtermcap-0.20050421_1-2-msys-1.0.13-dll-0.tar.lzma

Once you downloaded and extracted the packages copy the content from the extracted folders folder into their respective place in platform/windows/support/msys/1.0 (or your specified MSYS path) and replace the files when prompted.