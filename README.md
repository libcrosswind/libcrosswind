# Crosswind
A modern C++14 Multipurpose library

Current status: 

- [x] Unstable
- [ ] Stable

Current modules:
- [x] core (lacks javascript interpreter)
- [ ] platform (needs work with gui and widgets)
- [ ] standard (almost finished)
- [ ] trivial  (needs to be rearranged)

Expected time for 0.1: <= 1 week (2/21/15)

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

Current library capabilities:

- [x] GUI 		   (widget loading via json will be ready soon)
- [x] Delegates	
- [ ] Websockets   (ws will be ready soon)
- [x] Cryptography (base64 and sha1)
- [x] Filesystem   (concurrent filesystem utility)
- [x] JSON		   (fully concurrent for internal raw json)
- [x] Concurrency  (concurrent datatypes working)
- [ ] Javascript
- [ ] 3D
- [ ] Audio (Audio will be provided soon)
- [ ] Video
- [ ] SRTP
- [ ] DB (SQLite will be provided soon)
- [ ] Bindings with other languages.


Deliverables for 0.1
- [x] Delegates	
- [x] Cryptography 
- [x] Filesystem   
- [x] JSON		   
- [x] Concurrency  

Deliverables for 0.2
- [x] GUI

Deliverables for 0.3
- [x] Websockets  (ws only)
- [x] Audio (Audio will be provided soon)

Deliverables for 0.4
- [x] DB (SQLite)
- [x] 3D

Deliverables for 0.5
- [x] Video

Deliverables for 0.6
- [x] Websockets (wss)
- [x] SRTP

Deliverables for 0.7
- [x] Javascript (interpreter)

Deliverables for 0.8
- [x] Bindings with other languages.

The development will be done in that order. Further revisions will extend the support for each capability. Take in consideration that some modules could come before and that the version layout may change.


The API documentation will be ready once we reach stable (~0.6). 

Feel free to use the working modules. 