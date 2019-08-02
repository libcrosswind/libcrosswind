                    ________________________________________
                  _/_                                      _\_
               __/__/  TDM-GCC Compiler Suite for Windows  \__\__
              | « « |             GCC 5 Series             | » » |
               ¯¯\¯¯\      MinGW-w64 64/32-bit Edition     /¯¯/¯¯
                  ¯\¯                                      ¯/¯
                    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯


This edition of TDM-GCC is a bi-arch bootstrap of GCC's x86_64-w64-mingw32
target, built to run on 32-bit or 64-bit Windows and generate binaries for
32-bit or 64-bit Windows.


BUGS:
Please do *not* report bugs in this edition of TDM-GCC to the standard MinGW
(32) mailing list or forums.

If you encounter any bugs with this edition of TDM-GCC, it is likely that they
will be inherent to the x86_64-w64-mingw32 GCC target or to the MinGW-w64
runtime API. As such, you are encouraged to report bugs to the tracker for the
MinGW-w64 project on SourceForge
(<https://sourceforge.net/p/mingw-w64/bugs/>). Once the issue has been
fixed in the mingw-w64 runtime or in GCC, file a feature request on the TDM-GCC
tracker (<https://sourceforge.net/p/tdm-gcc/feature-requests/>) to update to the
fixed version.


/=-=- ------------ -=-=\
|=|   INSTALLATION   |=|
\=-=- ------------ -=-=/

-=- TDM/MINGW INSTALLER -=-

Using the TDM/MinGW installer is highly recommended; it can automatically
install TDM-GCC (or the official MinGW GCC) as well as all supplementary base
system packages. The installer uses a standard wizard interface with reasonable
defaults.

-=- MANUAL INSTALLATION -=-

Do not install TDM-GCC packages on top of a previous GCC installation of any
kind.

You will need to download and unpack a set of archives. A minimal base set of
archives is required; there are also some additional components that are
optional, adding support for additional programming languages or GCC features.

TDM-GCC provides a ZIP-compressed version and a TAR.LZMA-compressed version of
each archive. Use whichever is easiest.

REQUIRED BASE:
 * gcc-core (gcc-5.1.0-tdm64-1-core)
 * binutils (binutils-2.24.51-20140703-tdm64-1)
 * mingw64-runtime (mingw64runtime-v3-git20141130-gcc49-tdm64-1)

OPTIONAL:
 * gcc-c++ (gcc-5.1.0-tdm64-1-c++) - C++ support
 * gcc-ada (gcc-5.1.0-tdm64-1-ada) - Ada support
 * gcc-fortran (gcc-5.1.0-tdm64-1-fortran) - Fortran support
 * gcc-objc (gcc-5.1.0-tdm64-1-objc) - Objective-C/C++ support
 * gcc-openmp (gcc-5.1.0-tdm64-1-openmp) - OpenMP support
 * mingw32-make (make-3.82.90-2-mingw32-cvs-20120902-bin,
     libintl-0.17-1-mingw32-dll-8, libiconv-1.13.1-1-mingw32-dll-2) - GNU make
     for *-mingw32 GCC
 * gdb (gdb-7.8.1-tdm64-4) - GNU source-level debugger, for x86_64-w64-mingw32
     GCC
You'll need GDB particularly if you want to use an IDE with debugging support.

Unpack all the archives to an empty directory. You may choose any path, though
it is recommended that you avoid a path with any spaces in the folder names.
Finally, consider adding the bin subdirectory to your Windows PATH environment
variable.


/=-=- ------- -=-=\
|=|   SUPPORT   |=|
\=-=- ------- -=-=/

Support for the x86_64-w64-mingw32 GCC target, as well as for any
incompatibilities in its runtime API, is provided where possible by the
MinGW-w64 project. The MinGW-w64 project provides multiple venues for support
including a mailing list, an IRC channel, a web-based discussion forum on
SourceForge, and a web-based issue tracker on SourceForge.

For more information about MinGW-w64, see the project's home page at
<http://mingw-w64.sourceforge.net/>.


/=-=- ----------- -=-=\
|=|   USAGE NOTES   |=|
\=-=- ----------- -=-=/

-=- GDB AND GDB32: TDM BUILDS OF THE GNU DEBUGGER -=-

The TDM "gdb" and "gdb32" packages are slightly-modified builds of GDB for
(respectively) 64-bit and 32-bit Windows that include Python support, enable
libstdc++ Python pretty printing by default, and use wrapper executables to
allow 64-bit and 32-bit cooperation in the "bin" directory. For more details,
see the separate README files (README-gdb32-tdm.txt, README-gdb-tdm64.txt).

-=- 32-BIT OR 64-BIT COMPILATION -=-

In this edition of TDM-GCC, you can use "-m32" and "-m64" to control whether
32-bit or 64-bit binaries are generated. By default (if neither -m32 nor -m64 is
specified), 64-bit binaries will be generated.

 * In a 64-bit binary, all pointer math is 64-bit by default, and the built-in
   "size_t" and "ptrdiff_t" types are 64 bits in size (some other types are
   larger also).

 * Additionally, the following preprocessor definitions will be in effect:
     #define _WIN64 1 (also WIN64, __WIN64, and __WIN64__)
     #define __MINGW64__ 1
     #define __x86_64 1 (also __x86_64__)
     #define __amd64 1 (also __amd64__)

Be sure to use "-m32" or "-m64" at both the compile stage and the link stage.

There are also two different exception handling mechanisms used in the generated
code, depending on whether you compile for 32-bit or 64-bit:

 * 32-bit programs compiled with this edition (TDM64) will use SJLJ (setjmp /
   longjmp) exception unwinding, which is somewhat compatible with Microsoft
   system DLLs and other MSVC-generated code. Cleanup code will not be executed
   when unwinding through MSVC function frames, you cannot throw language-
   specific exceptions and have them caught in MSVC code, and you cannot catch
   language-specific exceptions thrown by MSVC code. However, the exception
   unwinder can traverse MSVC function frames in the stack in order to reach GCC
   function frames.

 * 64-bit programs compiled with this edition (TDM64) will use 64-bit Windows
   SEH (Structured Exception Handling) exception unwinding, which has better
   MSVC compatibility. Cleanup code *will* be executed when unwinding through
   MSVC function frames, but you still can't catch language-specific exceptions
   from MSVC code or throw language-specific exceptions to MSVC code.

-=- POSIX THREADS, C++11 STD::THREAD AND OTHER SYNCHRONIZATION FEATURES -=-

As of the 4.8.1 TDM-GCC release, a significant change has been introduced which
allows you to use C++11 features such as std::thread that rely on the POSIX
threading library. TDM-GCC now includes a new pthreads compatibility layer
called "winpthreads" instead of the old "pthreads-w32".

"Winpthreads" is one of the libraries distributed by the MinGW-w64 project, and
it allows GCC to be compiled with full pthreads compatibility, which is
necessary to enable std::thread and other threading related functions in the
C++ runtime.

Because of TDM-GCC's continuing goal of minimizing extra DLLs, winpthreads has
been compiled statically. It will be statically linked with every program you
compile, which will increase your baseline executable size.

The same mechanism used in libgcc and libstdc++ to allow EXEs and DLLs to share
state for handling exceptions has also been patched into winpthreads to allow
your EXEs and DLLs to share C++11 thread handles via the underlying pthread
handles.

Because every program you compile will now rely on winpthreads, you should make
sure to read and comply with its MIT-style license, included in the file
"COPYING.winpthreads.txt".

-=- INLINE MEMBER FUNCTIONS AND DLLS -=-

[[[ IMPORTANT NOTE:
[[[ You will probably need to use "-fno-keep-inline-dllexport" when building
[[[ large DLLs with lots of inline member functions, such as the "wxWidgets"
[[[ library's monolithic DLL.

As of the 4.5 series, GCC conforms more closely to the behavior of MSVC on
Windows platforms by always emitting inline functions that are class members
when creating a DLL. This behavior doesn't necessarily conform to the
expectations of libraries that are used to the old behavior, however, and in
some cases can cause the linker to run out of memory when creating the DLL. If
necessary, use the "-fno-keep-inline-dllexport" flag to avoid emitting these
functions.

-=- LTO (LINK-TIME OPTIMIZATION) -=-

Every TDM-GCC release since 4.5.1 includes support for GCC's Link-Time
Optimizer. As long as GCC's own drivers (gcc, g++, etc.) are used at both
compile-time and link-time, and the "-flto" option is specified at both compile-
time and link-time, link-time optimization will be applied. See
<http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html> for further details.

-=- EXCEPTIONS AND DLLS -=-

[[[ IMPORTANT NOTE:
[[[ TDM-GCC uses a statically-linked libstdc++ by default! To use the libstdc++
[[[ DLL, specify "-shared-libstdc++" on the command line.

The TDM releases of x86_64-w64-mingw32 GCC support propagating exceptions out
of shared libraries (DLLs) whether you use DLL versions or statically-linked
versions of the GCC runtime libraries. The statically-linked runtimes utilize
shared memory regions that will allow all TDM-GCC-compiled executables and DLLs
(for the same architecture) to propagate exceptions correctly. This method
incurs a small execution overhead as compared to the shared library method, but
has the very important benefit of not requiring you to redistribute extra DLLs
with your program.

By default, TDM-GCC creates executables and DLLs that use the statically-linked
runtimes, and does not require you to redistribute further DLLs. If you would
like to use the shared runtimes, you should add "-shared-libgcc" to the command
line, to use a shared version of libgcc, and additionally ensure that the shared
version of your language-specific runtime is being used. For C++, add
"-shared-libstdc++".

You cannot use a shared version of libgcc with a static version of a language-
specific runtime. The reverse -- static libgcc with shared language-specific
runtime -- should work fine.

IMPORTANT NOTE:
There has been an update to the license exception clause that permits you to
distribute programs that make use of the GCC runtime libraries without requiring
you to license your programs under the GPLv3. As always, please be familiar with
the terms of GCC's GPLv3 license and exception clauses, and do not redistribute
any portion of GCC, including its runtime DLLs, in any way except as granted by
the license. If you are unclear about which permissions are granted by the
license, please consult a lawyer and/or the Free Software Foundation
(<http://www.fsf.org/>).

A copy of the GPLv3 may be found in the file
COPYING-gcc-tdm.txt, and a copy of the runtime library exception clause may be
found in COPYING.RUNTIME-gcc-tdm.txt. In general, the runtime library exception
clause probably applies to any file found in the "lib" directory or its
subdirectories, and any DLL found in the "bin" directory -- but you should
consult the sources, available for download from the TDM-GCC project site on
SourceForge, if you are unsure.

-=- OPENMP AND WINPTHREADS -=-

TDM-GCC has been built to allow the use of GCC's "-fopenmp" option for
generating parallel code as specified by the OpenMP API. (See
<http://gcc.gnu.org/onlinedocs/libgomp/> for details.) If you want to use
OpenMP in your programs, be sure to install the "openmp" optional package.

The OpenMP support in the TDM-GCC builds has received very little testing; if
you find build or packaging problems, please send a bug report (see BUGS above).

LibGOMP, GCC's implementation of OpenMP, currently only supports the use of the
POSIX Threads (pthreads) api for implementing its threading model. This edition
of TDM-GCC relies on the "winpthreads" library (part of the MinGW-w64 project
libraries and included in this distribution). The "winpthreads" library is
distributed under the terms of an MIT-style license; see
"COPYING.winpthreads.txt" for details.

In order to correctly compile code that utilizes OpenMP/libGOMP, you need to add
the "-fopenmp" option at compile time AND link time. By default, this will link
the static version of winpthreads to your program, and you should not need to
distribute any additional DLLs with your program. If you plan to distribute a
program that relies on OpenMP and winpthreads, be sure to understand and comply
with the terms of winpthreads' license (see COPYING.winpthreads.txt).

"libpthread.a" is included in the "lib" subdirectory of the openmp package along
with three other pthreads library files:
 - "libpthread_s.a" and "libwinpthread.dll.a" link to a DLL version of
     winpthreads - libwinpthread-1.dll.
 - "libwinpthread.a" is the same as "libpthread.a".

-=- WARNINGS AND ERRORS -=-

Recent GCC releases make significant strides in optimization capabilities, error
detection, and standards compliance. For you, the end user, this often means
that code which compiled and ran without problems on previous GCC releases will
exhibit some warnings and maybe even a few errors.

These meaningful warnings and errors are a very good thing, as they help the
programmer to write safer and more correct code. Unfortunately, there's also a
chance you might encounter incorrect warnings or errors, ICE's (internal
compiler errors, where the compiler makes a mistake and has to bail out), or
even miscompilations (where your code is incorrectly compiled and produces the
wrong result).

If you encounter an ICE while using a TDM-GCC build, feel free to file a bug
report (see BUGS above). With any other unexpected problem, you are urged to
work from the assumption that it stems from user error, and ensure that your
code is correct and standards-compliant.


/=-=- --------------------- -=-=\
|=|   BUGS AND KNOWN ISSUES   |=|
\=-=- --------------------- -=-=/

-- There are currently no known TDM64-GCC-specific bugs. --

TDM-GCC for the x86_64-w64-mingw32 target is based on the work of the MinGW-w64
project, which is somewhat younger and less stable than the standard MinGW
32-bit project. This being the case, some bugs are to be expected. If you
encounter a bug that you are certain is in the GCC sources (such as an ICE), or
that is due to an issue in the building or packaging process, you are encouraged
to report it. Please visit the TDM-GCC Bugs Page at
<http://tdm-gcc.tdragon.net/bugs> for bug reporting instructions.


/=-=- ----------------------- -=-=\
|=|   LOCAL FIXES AND CHANGES   |=|
\=-=- ----------------------- -=-=/

 - [make-rel-pref.patch] Includes a patch to keep GCC from erroneously using the
     CWD as the installation directory.
 - [libgomp.patch] Includes a patch to allow libgomp to interoperate correctly
     with user-generated pthreads. See
     <https://sourceforge.net/p/tdm-gcc/bugs/76/>.
 - [libgcceh.patch] Includes a patch which reintegrates the code from
     libgcc_eh.a into libgcc.a and the libgcc DLL. As long as the shared memory
     region is used to handle exceptions in the static runtimes, this library is
     unnecessary, and it causes multiple definition errors for the symbols in it
     because it hasn't been added to binutils' exception libraries yet.
 - [defstatic.patch] Includes a patch to make libgcc and libstdc++ link
     statically by default. The "-static-libgcc" and "-static-libstdc++"
     commands thereby do not have any effect; use "-shared-libgcc" and
     "-shared-libstdc++" to link your program to the corresponding DLLs.
 - [ada-lfs.patch] Includes a patch to allow Ada to build for older versions of
     the MSVCRT without a stat64 equivalent.
 - [ssp-mingw32.patch] Includes a patch to allow libssp to build for older
     versions of the MSVCRT without CryptAcquireContext.
 - [relocate.patch] Includes a patch to make all search paths for headers,
     libraries and helper executables relative to the installation directory of
     the driver executables -- in other words, TDM-GCC is fully relocatable and
     does not search any absolute system paths.
 - [eh_shmem.patch] Includes a patch to propagate C++ exceptions out of DLLs
     without the need for shared runtime libraries.
 - [threads.patch] Includes a patch to fix GCC & winpthreads interop for x86
     mingw32 and allow use of a fully static pthreads library.
 - [more-gnattools.patch] Includes a patch to enable extra tools in the Ada
     toolchain for mingw*.
 - [windows-lrealpath.patch] Includes a patch to allow forward slashes in
     libiberty as path separators on Windows, allowing build system integrations
     like map files to work better.
 - [mutex-leak.patch] Includes a patch to prevent pthreads mutexes from leaking
     in libstdc++.
 - [lto-binary.patch] Fix LTO reader to open files in binary mode.
 - [xmmintrin.patch] Add C++ include guards to xmmintrin.h.
 - [crtbegin.patch] Remove static modifier from __EH_FRAME_BEGIN__ to allow
     visibility across compilation units.
 - [gnat-implibs.patch] Create import libraries for the DLL versions of libgnat
     and libgnarl.
 - [mcrtdll.patch] Allow specifying newer MSVCRT versions with -mcrtdll=.
 - [dw2-reg-frame.patch] Prevent DW2 frame register/unregister from getting
     mistakenly stripped.
 - [libs64.patch] Includes a patch to differentiate DLL names between the 32-bit
     and 64-bit GCC runtime libraries.
 - Configured with "--enable-fully-dynamic-string", which fixes a bug when
     passing empty std::string objects between DLLs and EXEs.


/=-=- ----------- -=-=\
|=|   SOURCE CODE   |=|
\=-=- ----------- -=-=/

The source code for the TDM-GCC binary releases is available from the TDM-GCC
download page on SourceForge: <http://sourceforge.net/projects/tdm-gcc/files/>.
(The most up-to-date link to the download site will always be available at
<http://tdm-gcc.tdragon.net/>.)

The source is distributed in the form of the original ("vanilla") separate
source packages as downloaded, plus an additional "TDM Sources" package. The TDM
Sources package includes unified diffs of any changes made to the vanilla
sources, as well as the set of scripts used to build the binary releases.


/=-=- ------------------ -=-=\
|=|   COMPONENT LICENSES   |=|
\=-=- ------------------ -=-=/

This edition of TDM-GCC is comprised of several distinct parts with respect to
licensing, namely:
 * GCC proper and its various language components,
 * The GNU binutils package, and
 * The MinGW-w64 runtime API.

The GCC proper packages in TDM-GCC contain binary distributions constituting a
work based on GCC, ISL, MPC, libiconv, GMP, MPFR, and winpthreads.

* GCC itself is licensed under the GPLv3; for further details, see
  "COPYING3-gcc-tdm.txt". GCC's runtime libraries are licensed with an
  additional exception clause; see "COPYING.RUNTIME-gcc-tdm.txt".

* MPC, libiconv, GMP, and MPFR are each licensed under the LGPLv3, a somewhat
  more permissive version of the GPL; see "COPYING3.LIB-gcc-tdm.txt".

* ISL and winpthreads use an "MIT-style" license, reproduced in
  "COPYING.ISL.txt" and "COPYING.winpthreads.txt".

The GNU binutils package is a binary distribution licensed under the GPLv3; see
"COPYING3-gcc-tdm.txt".

The MinGW-w64 runtime API includes binary and source files that fall under a
variety of licenses (all of which are "GPLv3 compatible"); for further details,
see "COPYING.MinGW-w64.txt" (for non-runtime portions) and
"COPYING.MinGW-w64-runtime.txt" (for the runtime only).
