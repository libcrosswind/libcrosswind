# libcrosswind 0.1
A modern C++14 Multipurpose library

Current status: 

- [x] Unstable
- [ ] Stable

Current modules:
- [ ] audio      - ogg
- [ ] concurrent - atomic_property, mutex_property, mutex_container, hollow_property, resource_property
- [ ] container  - cacheable
- [ ] crypto     - base64, sha1
- [ ] database   - sqlite
- [ ] drawing    - rgb, rgba
- [ ] event      - queue
- [ ] functional - delegate
- [ ] geometry   - point, rectangle, box
- [ ] javascript - json
- [ ] math       - clamp, vector2, vector 3
- [ ] network    - 
- [ ] platform   - application, filesystem
- [ ] simulation - stage, standard_image, interactive_image
- [ ] trivial    - this module is used internally by other modules
- [ ] video      -


Crosswind is a toolset that aims to integrate high level C++14 functions for fast app development.
Intended to be header-only with minimal dependencies. 

If you're on Windows, install the software tools from the 3rdparty directory.

Current dependencies:
- [x] ASIO
- [x] jsoncons
- [x] SDL2
- [x] SDL_image
- [x] SDL_ttf
- [x] SDL_mixer
- [x] SQLite3
- [ ] OpenCV
- [ ] Bullet3

ASIO, jsoncons and SQLite3 are not required to be built, they are configured to be header-only. For the rest of the dependencies you can run the build scripts from inside the setup folder via sh {script}.sh. 
SDL2 does not build with haptics support with mingw32, as it seems, you need to build with mingw64 for haptics to be enabled. Until a workaround is found you have to stick with mingw64 based builds.

The build script works for the windows platform at the moment and it will be tweaked in order to provide the building of the SDL2, OpenCV and Bullet3 libraries for the other platforms.

Current supported platforms:

- [x] Windows
- [x] Linux
- [x] Mac
- [ ] Android
- [ ] Tizen
- [ ] Windows Phone
- [ ] Blackberry

Roadmap:
- [x] GUI 		  
- [x] Delegates	
- [ ] Websockets   
- [x] Cryptography 
- [x] Filesystem   
- [x] JSON		   
- [x] Concurrency  
- [ ] Javascript
- [ ] 3D
- [ ] Peripherals
- [ ] Serial, I2C, GPIO, UART, SPI
- [x] Audio
- [ ] Video
- [ ] SRTP
- [x] DB 
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