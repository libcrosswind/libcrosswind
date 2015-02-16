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
Intended to be header-only with minimal dependencies. Expected non-header-only dependencies will be OpenCV and the video codecs. 

Current dependencies:
- [x] SDL2 (don't worry, it is pretty easy to build)

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