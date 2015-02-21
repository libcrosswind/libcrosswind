# libcrosswind 0.1
A modern C++14 Multipurpose library

Current status: 

- [x] Unstable
- [ ] Stable

Current modules:
- [x] core (lacks javascript interpreter)
- [ ] platform (needs work with gui and widgets)
- [ ] standard (almost finished)
- [ ] trivial  (needs to be rearranged)

Crosswind is a toolset that aims to integrate high level C++14 functions for fast app development.
Intended to be header-only with minimal dependencies. 

If you're on Windows, install the required dependencies from the 3rdparty directory.

Current dependencies:
- [x] SDL2
- [ ] OpenCV

Run the build scripts from inside the setup folder via sh {script}.sh. 
SDL2 does not build with haptics support with mingw32, as it seems, you need to build with mingw64 for haptics to be enabled. Until a workaround is found you have to stick with mingw64 based builds.

Current supported platforms:

- [x] Windows
- [x] Linux
- [x] Mac
- [ ] Android
- [ ] Tizen
- [ ] Windows Phone
- [ ] Blackberry

Roadmap:
- [ ] GUI 		  
- [x] Delegates	
- [ ] Websockets   
- [x] Cryptography 
- [x] Filesystem   
- [x] JSON		   
- [x] Concurrency  
- [ ] Javascript
- [ ] 3D
- [ ] Audio
- [ ] Video
- [ ] SRTP
- [ ] DB 
- [ ] Bindings with other languages.


Future releases:

0.2:
- [x] GUI

0.3: 
- [x] Websockets  (ws only)
- [x] Audio 

0.4:
- [x] DB (SQLite)
- [x] 3D

0.5:
- [x] Video

0.6:
- [x] Websockets (wss)
- [x] SRTP

0.7:
- [x] Javascript (interpreter)

0.8:
- [x] Bindings with other languages.


The API documentation will be ready once we reach a stable version (~0.6). 

Feel free to use the working modules. 