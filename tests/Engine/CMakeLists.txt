cmake_minimum_required(VERSION 2.8.4)
project(Engine)

set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/../../internal/include"
                            "${PROJECT_SOURCE_DIR}/../../external/CImg-1.6.0/include"
                            "${PROJECT_SOURCE_DIR}/../../external/jsoncons/src"
                            "${PROJECT_SOURCE_DIR}/../../external/bullet3/src"
                            "${PROJECT_SOURCE_DIR}/../../platform/windows/build/include")


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib)


include_directories(${INCLUDE_LIBRARY_PATH})

if( CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_options(-std=gnu++1y -g -Og -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS)

else( CMAKE_BUILD_TYPE STREQUAL "Release")

add_compile_options(-std=gnu++1y -O3 -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS -DNDEBUG)
#SET( GCC_COVERAGE_LINK_FLAGS    "-mwindows -Wl --large-address-aware --no-keep-memory")
SET( GCC_COVERAGE_LINK_FLAGS    "-mwindows")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

endif()

set(library ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/composition/actor.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/composition/camera.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/composition/core.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/composition/group.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/composition/scene.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/composition/stage.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/configuration/settings.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/object/mesh.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/object/model.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/object/sprite.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/object/sprite_animation.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/object/text.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/object/vertex.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/opengl/render_batch.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/opengl/renderer.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/opengl/shader_program.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/opengl/sprite_batch.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/opengl/texture.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/opengl/window.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/sdl/font.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/sdl/surface.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/graphical/video.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/platform/application.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/platform/exception.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/platform/filesystem.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/platform/input.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/scripting/interpreter_a.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/scripting/interpreter_b.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/debug/opengl/drawer.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/debug/opengl/shader_program.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/debug/opengl/vertex.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/detail/body.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/detail/character.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/box.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/physics.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/simulation/plane.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/sound/chunk.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/sound/mixer.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/sound/music.cpp
            ${PROJECT_SOURCE_DIR}/../../internal/src/crosswind/engine.cpp)

set(sources main.cpp)



set(PROJECT_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")
#file(GLOB sources main.cpp)
add_executable(Engine ${library} ${sources})

set_target_properties(Engine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

set(SDL2_libs        SDL2main SDL2 winmm imm32 version)
#set(SDL2_image_libs  SDL2_image jpeg png z)
set(SDL2_image_libs  SDL2_image png z)
set(SDL2_ttf_libs    SDL2_ttf freetype)
set(SDL2_mixer_libs  SDL2_mixer vorbisenc vorbisfile vorbis ogg)
set(win32_libs       winmm imm32 version)
set(bullet3_libbs    BulletDynamics BulletCollision LinearMath)
set(opengl_libs      glu32 opengl32)
set(opengl_ext_libs  glew)
set(perl_libs )


target_link_libraries (Engine LINK_PUBLIC mingw32
                                                ${SDL2_libs}
                                                ${SDL2_image_libs}
                                                ${SDL2_ttf_libs}
                                                ${SDL2_mixer_libs}
                                                ${win32_libs}
                                                ${bullet3_libbs}
                                                ${opengl_ext_libs}
                                                ${opengl_libs}
                                                ${perl_libs})

file(COPY ${PROJECT_SOURCE_DIR}/../../resources/assets DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/scripts DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib/chaiscript/libchaiscript_stdlib-5.7.0.dll
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib/chaiscript/libstl_extra.dll
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
