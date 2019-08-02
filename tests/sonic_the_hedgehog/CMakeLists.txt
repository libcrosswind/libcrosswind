cmake_minimum_required(VERSION 2.8.4)
project(sonic_the_hedgehog)


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

add_compile_options(-std=gnu++1y -O3 -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS)

endif()

set(library ${INTERNAL_DIR}/src/crosswind/composition/actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/animated_actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/text_actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/camera.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/core.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/scene.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/stage.cpp
            ${INTERNAL_DIR}/src/crosswind/configuration/settings.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/mesh.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/model.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/sprite.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/sprite_animation.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/text.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/vertex.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/render_batch.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/renderer.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/shader_program.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/sprite_batch.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/texture.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/window.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/sdl/font.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/sdl/surface.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/video.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/application.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/exception.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/filesystem.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/input.cpp
            ${INTERNAL_DIR}/src/crosswind/scripting/interpreter_a.cpp
            ${INTERNAL_DIR}/src/crosswind/scripting/interpreter_b.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/debug/opengl/drawer.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/debug/opengl/shader_program.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/debug/opengl/vertex.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/detail/body.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/detail/character.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/box.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/physics.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/plane.cpp
            ${INTERNAL_DIR}/src/crosswind/sound/chunk.cpp
            ${INTERNAL_DIR}/src/crosswind/sound/mixer.cpp
            ${INTERNAL_DIR}/src/crosswind/sound/music.cpp
            ${INTERNAL_DIR}/src/crosswind/engine.cpp)

set(sources ${library} main.cpp)

set(PROJECT_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

add_executable(sonic_the_hedgehog ${sources})

set_target_properties(sonic_the_hedgehog
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

set(SDL2_libs        SDL2main SDL2 winmm imm32 version)
set(SDL2_image_libs  SDL2_image jpeg png z)
set(SDL2_ttf_libs    SDL2_ttf freetype)
set(SDL2_mixer_libs  SDL2_mixer vorbisenc vorbisfile vorbis ogg)
set(win32_libs       winmm imm32 version)
set(bullet3_libbs    BulletDynamics BulletCollision LinearMath)
set(opengl_libs      glu32 opengl32)
set(opengl_ext_libs  glew)
set(perl_libs )

target_link_libraries (sonic_the_hedgehog LINK_PUBLIC mingw32
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
file(COPY ${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib/chaiscript/libchaiscript_stdlib-5.7.0.dll
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib/chaiscript/libstl_extra.dll
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PROJECT_SOURCE_DIR}/scripts
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)