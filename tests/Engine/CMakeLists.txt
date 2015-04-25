cmake_minimum_required(VERSION 2.8.4)
project(Engine)

set(TOP_DIR "${PROJECT_SOURCE_DIR}/../..")
set(INTERNAL_DIR  "${TOP_DIR}/internal")
set(EXTERNAL_DIR  "${TOP_DIR}/external")
set(PLATFORM_DIR  "${TOP_DIR}/platform")
set(RESOURCES_DIR "${TOP_DIR}/resources")
set(OUTPUT_DIR    "${TOP_DIR}/output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}"
                            "${INTERNAL_DIR}/include"
                            "${EXTERNAL_DIR}/CImg-1.6.0/include"
                            "${EXTERNAL_DIR}/jsoncons/src"
                            "${EXTERNAL_DIR}/bullet3/src"
                            "${PLATFORM_DIR}/windows/build/include")


LINK_DIRECTORIES(${PLATFORM_DIR}/windows/build/lib)


include_directories(${INCLUDE_LIBRARY_PATH})

if( CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_options(-std=gnu++1y -g -Og -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS)

else( CMAKE_BUILD_TYPE STREQUAL "Release")

add_compile_options(-std=gnu++1y -O3 -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS -DNDEBUG)
#SET( GCC_COVERAGE_LINK_FLAGS    "-mwindows -Wl --large-address-aware --no-keep-memory")
SET( GCC_COVERAGE_LINK_FLAGS    "-mwindows")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

endif()

set(library ${INTERNAL_DIR}/src/crosswind/composition/actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/camera.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/core.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/group.cpp
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


set(PROJECT_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

add_executable(Engine ${sources})

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

file(COPY ${RESOURCES_DIR}/assets DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/scripts DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PLATFORM_DIR}/windows/build/lib/chaiscript/libchaiscript_stdlib-5.7.0.dll
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PLATFORM_DIR}/windows/build/lib/chaiscript/libstl_extra.dll
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
