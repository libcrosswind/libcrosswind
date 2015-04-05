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

add_compile_options(-std=gnu++1y -mwindows -O3 -DGLEW_STATIC -DCHAISCRIPT_NO_THREADS -DNDEBUG)
SET( GCC_COVERAGE_LINK_FLAGS    "-mwindows")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

endif()


set(PROJECT_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")
file(GLOB sources main.cpp)
add_executable(Engine ${sources})

set_target_properties(Engine
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
