cmake_minimum_required(VERSION 2.8.4)
project(sonic_the_hedgehog)

set(TOP_DIR "${PROJECT_SOURCE_DIR}/../..")
set(INTERNAL_DIR  "${TOP_DIR}/internal")
set(EXTERNAL_DIR  "${TOP_DIR}/external")
set(PLATFORM_DIR  "${TOP_DIR}/platform")
set(RESOURCES_DIR "${TOP_DIR}/resources")
set(OUTPUT_DIR    "${TOP_DIR}/output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")




if (WIN32)
    set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}"
            "${INTERNAL_DIR}/include"
            "${EXTERNAL_DIR}/CImg-1.6.0/include"
            "${EXTERNAL_DIR}/jsoncons/include"
            "${EXTERNAL_DIR}/bullet3/src"
            "${PLATFORM_DIR}/windows/build/include")
endif (WIN32)

if (UNIX)
    set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}"
            "${INTERNAL_DIR}/include"
            "${EXTERNAL_DIR}/CImg-1.6.0/include"
            "${EXTERNAL_DIR}/jsoncons/include"
            "${EXTERNAL_DIR}/bullet3/src"
            "${PLATFORM_DIR}/linux/build/include")
endif (UNIX)



if (WIN32)
    LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib)
endif (WIN32)

if (UNIX)
    LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../platform/linux/build/lib)
endif (UNIX)

include_directories(${INCLUDE_LIBRARY_PATH})

if( CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_options(-std=gnu++1y -fpermissive -g -Og -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS)

else( CMAKE_BUILD_TYPE STREQUAL "Release")

add_compile_options(-std=gnu++1y -fpermissive -O3 -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS)

endif()

set(library
            ${INTERNAL_DIR}/src/crosswind/composition/graphics/animation_set.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/camera.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/core.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/scene.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/stage.cpp
            ${INTERNAL_DIR}/src/crosswind/configuration/settings.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/mesh.cpp
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


if (WIN32)
    set(SDL2_libs        SDL2main SDL2 winmm imm32 version hid setupapi)
    set(SDL2_image_libs  SDL2_image jpeg png z)
    set(SDL2_ttf_libs    SDL2_ttf freetype)
    set(SDL2_mixer_libs  SDL2_mixer vorbisenc vorbisfile vorbis ogg)
    set(win32_libs       winmm imm32 version hid setupapi)
    set(bullet3_libbs    BulletDynamics BulletCollision LinearMath)
    set(opengl_libs      glu32 opengl32)
    set(opengl_ext_libs  glew)
endif (WIN32)

if (UNIX)
    set(SDL2_libs        SDL2main SDL2)
    set(SDL2_image_libs  SDL2_image jpeg png z)
    set(SDL2_ttf_libs    SDL2_ttf freetype harfbuzz)
    set(SDL2_mixer_libs  SDL2_mixer vorbisenc vorbisfile vorbis ogg)
    set(unix_libs        pthread dl)
    set(bullet3_libbs    BulletDynamics BulletCollision LinearMath)
    set(opengl_libs      GLU GL)
    set(opengl_ext_libs  glew)
endif (UNIX)


if (WIN32)
    target_link_libraries (sonic_the_hedgehog
                            LINK_PUBLIC
                            mingw32
                            ${SDL2_libs}
                            ${SDL2_image_libs}
                            ${SDL2_ttf_libs}
                            ${SDL2_mixer_libs}
                            ${win32_libs}
                            ${bullet3_libbs}
                            ${opengl_ext_libs}
                            ${opengl_libs})
endif (WIN32)

if (UNIX)
    target_link_libraries (sonic_the_hedgehog
                            LINK_PUBLIC
                            ${SDL2_libs}

                            ${SDL2_ttf_libs}

                            ${SDL2_image_libs}

                            ${SDL2_mixer_libs}
                            ${unix_libs}
                            ${bullet3_libbs}
                            ${opengl_ext_libs}
                            ${opengl_libs})
endif (UNIX)


file(COPY ${PROJECT_SOURCE_DIR}/../../resources/assets DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
#file(COPY ${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib/chaiscript/libchaiscript_stdlib-5.7.0.dll
#     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

#file(COPY ${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib/chaiscript/libstl_extra.dll
#     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

file(COPY ${PROJECT_SOURCE_DIR}/scripts
     DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)