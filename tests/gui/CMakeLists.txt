cmake_minimum_required(VERSION 2.8.4)
project(gui)


set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}/../../internal/include"
                            "${PROJECT_SOURCE_DIR}/../../external/CImg-1.6.0/include"
                            "${PROJECT_SOURCE_DIR}/../../external/asio_standalone/asio/include"
                            "${PROJECT_SOURCE_DIR}/../../external/jsoncons/src"
                            "${PROJECT_SOURCE_DIR}/../../platform/windows/build/include")


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../platform/windows/build/lib)

set(PROJECT_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")


include_directories(${INCLUDE_LIBRARY_PATH})

if( CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_options(-std=gnu++1y -g -DASIO_STANDALONE -DASIO_SEPARATE_COMPILATION -D_WIN32_WINNT=0x0501)

elseif( CMAKE_BUILD_TYPE STREQUAL "Release")

add_compile_options(-std=c++1y)

endif()

file(GLOB sources main.cpp)

add_executable(gui ${sources})

set_target_properties(gui
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

target_link_libraries (gui LINK_PUBLIC mingw32 SDL2main SDL2 SDL2_image jpeg png z winmm imm32 version)

file(COPY ${PROJECT_SOURCE_DIR}/../../resources/assets DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/../../resources/tests DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)