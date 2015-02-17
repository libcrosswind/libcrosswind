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
SDL2 has not haptic support for mingw32, as it seems, you need to build with mingw64 for haptics to be enabled.

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
- [ ] Audio
- [ ] Video
- [ ] SRTP
- [ ] DB (SQLite will be provided soon)
- [ ] Bindings with other languages.

The API documentation will be ready once we reach stable.

Feel free to use the working modules. 